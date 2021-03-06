#include "RayData.hh"
#include "RayData1.hh"
#include "RayData2.hh"
#include "RayUnaryFilter.hh"
#include "AzGradientFilter.hh"
#include "AzGradientStateSpecialData.hh"
#include "CircularLookupHandler.hh"
#include "RayLoopData.hh"
#include <rapmath/ProcessingNode.hh>
#include <rapmath/UnaryNode.hh>
#include <rapmath/FloatUserData.hh>
#include <rapmath/MathUserData.hh>
#include <radar/RadxApp.hh>
#include <Radx/RadxRay.hh>
#include <Radx/RadxSweep.hh>
#include <Radx/RadxFuzzyF.hh>
#include <toolsa/LogStream.hh>
#include <algorithm>

//------------------------------------------------------------------
RayData::RayData(const RadxVol *vol, const CircularLookupHandler *lookup) :

  VolumeData(),_lookup(lookup), _vol(vol), _rays(vol->getRays()),
  _sweeps(vol->getSweeps()), _ray(NULL)
{
  if (!_rays.empty())
  {
    // just to have something around
    _ray = _rays[0];
  }
}  

//------------------------------------------------------------------
RayData::~RayData(void)
{
  for (size_t i=0; i<_specialValue.size(); ++i)
  {
    delete _specialValue[i];
  }
  _specialValue.clear();
  _rayDataNames.clear();
}

//------------------------------------------------------------------
// virtual
MathData *RayData::initializeProcessingNode(int index, bool twoD) const
{
  MathData *ret=NULL;
  if (twoD)
  {
    RayData2 *rd = new RayData2(*this, index, _lookup);
    ret = (MathData *)rd;
  }
  else
  {
    RayData1 *rd = new RayData1(*this, index);
    ret = (MathData *)rd;
  }
  return ret;
}

//------------------------------------------------------------------
// virtual
bool RayData::synchUserDefinedInputs(const std::string &userKey,
				     const std::vector<std::string> &names)
{
  if (!_needToSynch(userKey))
  {
    return true;
  }
  for (size_t i=0; i<names.size(); ++i)
  {
    if (!_hasData(userKey, names[i], false))
    {
      LOG(ERROR) << "Cannot synch";
      return false;
    }
  }
  return true;
}

//------------------------------------------------------------------
// virtual
MathUserData *RayData::processUserVolumeFunction(const UnaryNode &p) //const
{
  // pull out the keyword
  string keyword;
  if (!p.getUserUnaryKeyword(keyword))
  {
    return NULL;
  }
  vector<string> args = p.getUnaryNodeArgStrings();
  
  if (keyword == "VolAverage")
  {
    // expect one string argument which is either Prt or NSamples
    if (args.size() != 1)
    {
      LOG(ERROR) << "Wrong number of args want one got " << args.size();
      return NULL;
    }
    return _volumeAverage(args[0]);
  }
  else if (keyword == "VolAzGradientState")
  {
    // no arguments, can just go for it
    return _volumeAzGradientState();
  }
  else
  {
    LOG(ERROR) << "Keyword is invalid " << keyword;
    return NULL;
  }
}

//------------------------------------------------------------------
// virtual
bool RayData::storeMathUserData(const std::string &name, MathUserData *s)
{
  if (find(_specialName.begin(), _specialName.end(), name) !=
      _specialName.end())
  {
    printf("ERROR double storing of %s\n", name.c_str());
    return false;
  }
  else
  {
    _specialName.push_back(name);
    _specialValue.push_back(s);
    return true;
  }
}


//------------------------------------------------------------------
int RayData::numProcessingNodes(bool twoD) const
{
  if (twoD)
  {
    return (int)_sweeps.size();
  }
  else
  {
    return (int)_rays.size();
  }
}


//------------------------------------------------------------------
int RayData::numRays(void) const
{
  return (int)_rays.size();
}

//------------------------------------------------------------------
int RayData::numSweeps(void) const
{
  return (int)_sweeps.size();
}

//------------------------------------------------------------------
bool RayData::retrieveRay(const std::string &name, const RadxRay &ray,
                          const std::vector<RayLoopData> &data, RayxData &r,
			  bool showError)
{
  // try to find the field in the ray first
  if (RadxApp::retrieveRay(name, ray, r, false))
  {
    return true;
  }

  // try to find the field in the data vector
  for (size_t i=0; i<data.size(); ++i)
  {
    if (data[i].getName() == name)
    {
      // return a copy of that ray (base class)
      r = data[i];
      return true;
    }
  }
    
  if (showError)
  {
    LOG(ERROR) << "Field " << name << " never found";
  }
  return false;
}  

//------------------------------------------------------------------
void RayData::trim(const std::vector<std::string> &outputKeep, bool outputAll)
{
  if (outputAll)
  {
    return;
  }
  for (size_t i=0; i<_rays.size(); ++i)
  {
    _rays[i]->trimToWantedFields(outputKeep);
  }
}

//------------------------------------------------------------------
bool RayData::_hasData(const std::string &userKey,
		      const std::string &name, bool suppressWarn)
{
  if (userKey == "VolAverage")
  {
    // special case
    LOG(DEBUG) << "Special case? ";
    return false;
  }
  else if (userKey == "VolAzGradientState")
  {
    // there should be no args so not here
    LOG(ERROR) << "should not be here";
    return false;
  }

  // try to pull out of existing rays in data
  if (find(_rayDataNames.begin(), _rayDataNames.end(), name) !=
      _rayDataNames.end())
  {
    return true;
  }
      
  // try to pull out of input ray
  RayxData r;
  if (RadxApp::retrieveRay(name, *_ray, r, false))
  {
    // add this ray to the data state and return that
    _rayDataNames.push_back(name);
    return true;
  }

  // can't pull out of state, not in _ray and not in _data
  if (!suppressWarn)
  {
    LOG(ERROR) << "retrieving data for "<< name;
  }
  return NULL;
}    


//------------------------------------------------------------------
MathUserData *RayData::_volumeAverage(const std::string &name) const
{
  double mean = 0.0;
  if (name == "Prt")
  {
    for (size_t i=0; i<_rays.size(); ++i)
    {
      mean += _rays[i]->getPrtSec();
    }
  }
  else if (name == "NSamples")
  {
    for (size_t i=0; i<_rays.size(); ++i)
    {
      mean += _rays[i]->getNSamples();
    }
  }
  else
  {
    printf("ERROR unknown volume variable %s, want Prt or NSamples\n",
	   name.c_str());
    return NULL;
  }
  if (!_rays.empty())
  {
    double v = mean/static_cast<double>(_rays.size());
    FloatUserData *ret = new FloatUserData(v);
    return (MathUserData *)ret;
  }
  else
  {
    printf("ERROR no data\n");
    return NULL;
  }
}

//------------------------------------------------------------------
MathUserData *RayData::_volumeAzGradientState(void) const
{
  AzGradientStateSpecialData *a = new AzGradientStateSpecialData(*_vol);
  return (MathUserData *)a;
}

//------------------------------------------------------------------
bool RayData::_needToSynch(const std::string &userKey) const
{
  if (userKey == "VolAverage")
  {
    // the input name is not something to synch to
    return false;
  }
  else if (userKey == "VolAzGradientState")
  {
    // there should be no args so not here
    return false;
  }
  else if (userKey == "AzGradient")
  {
    // this loop filter has inputs
    return true;
  }

  // everything else has inputs
  return true;
}

