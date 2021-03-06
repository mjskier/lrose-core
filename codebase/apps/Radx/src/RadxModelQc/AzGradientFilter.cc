#include "AzGradientFilter.hh"
#include "AzGradientStateSpecialData.hh"
#include "RayData.hh"
#include <Radx/RadxRay.hh>
#include <Radx/RayxData.hh>
#include <radar/RadxApp.hh>
#include <toolsa/LogStream.hh>
#include <vector>
#include <string>

//----------------------------------------------------------------------
AzGradientFilter::AzGradientFilter(void) {}

//----------------------------------------------------------------------
AzGradientFilter::~AzGradientFilter(void) {}

//----------------------------------------------------------------------
bool AzGradientFilter::filter(const AzGradientStateSpecialData &state, double v,
			      const std::string &name, const RadxRay *ray0,
			      const RadxRay *ray1, const RadxRay *ray,
			      const std::vector<RayLoopData> &_data,
			      RayLoopData *output)
{
  _state = &state;

  // get the field from the center ray
  RayxData r, r0, r1;
  if (!RayData::retrieveRay(name, *ray, _data, r, true))
  {
    return false;
  }

  const RadxRay *lray0 = NULL;
  const RadxRay *lray1 = NULL;

  // see if can proceed or not
  bool ok = _set2Rays(ray0, ray1, *ray, &lray0, &lray1);
  if (ok)
  {
    if (!RayData::retrieveRay(name, *lray0, _data, r0))
    {
      return false;
    }
    if (!RayData::retrieveRay(name, *lray1, _data, r1))
    {
      return false;
    }
    int n = r.getNpoints();
    int n0 = r0.getNpoints();
    int n1 = r1.getNpoints();
    int nend = n;
    double a0 = r0.getAzimuth();
    double a1 = r1.getAzimuth();
    if (n0 < nend) nend = n0;
    if (n1 < nend) nend = n1;

    if (v > 0)
    {
      r.inc(v);
      r0.inc(v);
      r1.inc(v);
    }
    
    for (int i=0; i<nend; ++i)
    {
      double v0, v1;
      if (r0.getV(i, v0) && r1.getV(i, v1))
      {
	output->setVal(i, (v1 - v0)/(a1-a0)/2.0);
      }
      else
      {
	output->setVal(i, output->getMissingValue());
      }
    }
    for (int i=nend; i<n; ++i)
    {
      output->setVal(i, output->getMissingValue());
    }
  }
  else
  {
    output->setAllToValue(output->getMissingValue());
  }
  return true;
}

//------------------------------------------------------------------
bool AzGradientFilter::_set2Rays(const RadxRay *ray0, const RadxRay *ray1,
				 const RadxRay &ray, const RadxRay **lray0,
				 const RadxRay **lray1) const
{
  if (ray0 == NULL && ray1 == NULL)
  {
    // don't know what this is
    LOG(ERROR) << "Missing two of 3 inputs, not expected";
    return false;
  }
  else if (ray0 == NULL && ray1 != NULL)
  {
    return _veryFirstRay(ray, ray1, lray0, lray1);
  }
  else if (ray0 != NULL && ray1 == NULL)
  {
    return _veryLastRay(ray0, ray, lray0, lray1);
  }
  else 
  {
    *lray0 = ray0;
    *lray1 = ray1;
    // check for sweep boundary 
    int s0 = (*lray0)->getSweepNumber();
    int s1 = (*lray1)->getSweepNumber();
    int s = ray.getSweepNumber();
    if (s0 != s && s1 == s)
    {
      // current starts a new sweep
      return _setPreviousRayWhenNewSweep(s0, s, lray0, lray1);
    }
    else if (s0 == s && s1 != s)
    {
      // current ends a new sweep
      return _setNextRayWhenEndSweep(s, s1, lray0, lray1);
    }
    else
    {
      return true;
    }
  }
}

//------------------------------------------------------------------
bool AzGradientFilter::_setPreviousRayWhenNewSweep(int oldSweep, int sweep,
						   const RadxRay **lray0,
						   const RadxRay **lray1) const
{
  if (oldSweep >= sweep)
  {
    LOG(ERROR) << "Sweep indices did not increase";
    return false;
  }

  // crossed the boundary with s, if 360 can use last ray
  int nState = static_cast<int>(_state->size());
  for (int j=0; j<nState; ++j)
  {
    if ((*_state)[j]._sweepNumber == sweep && (*_state)[j]._is360)
    {
      *lray0 = (*_state)[j]._ray1;
      LOG(DEBUG_VERBOSE) << "new sweep starts now " << sweep
			 << "full 360 so prev=last in sweep";
      return true;
    }
  }
  LOG(WARNING) << "new sweep starts now " <<  sweep
	       << " not full 360, leave gap here";
  return false;
}


//------------------------------------------------------------------
bool AzGradientFilter::_setNextRayWhenEndSweep(int sweep, int nextSweep,
					     const RadxRay **lray0,
					     const RadxRay **lray1) const
{
  if (sweep >= nextSweep)
  {
    LOG(ERROR) << "Sweep indices did not increase";
    return false;
  }

  // crossed boundary when look to next ray, of 360 can use 0th ray as next one
  int nState = static_cast<int>(_state->size());
  for (int j=0; j<nState; ++j)
  {
    if ((*_state)[j]._sweepNumber == sweep && (*_state)[j]._is360)
    {
      *lray1 = (*_state)[j]._ray0;
      LOG(DEBUG_VERBOSE) << "last ray in sweep "<<  sweep
			 << " full 360, so next = 0th in sweep";
      return true;
    }
  }
  LOG(WARNING) << "last ray in sweep" <<  sweep
	       << " not full 360, leave gap";
  return false;
}


//------------------------------------------------------------------
bool AzGradientFilter::_veryFirstRay(const RadxRay &ray, const RadxRay *ray1,
				   const RadxRay **lray0,
				   const RadxRay **lray1) const
{
  // case of no previous ray, should be the 0th ray in the 0th sweep.  
  // if so, if 360, can use the last ray in the 0th sweep as ray0
  int s = ray.getSweepNumber();
  if (s == (*_state)[0]._sweepNumber && (*_state)[0]._is360)
  {
    LOG(DEBUG_VERBOSE) << 
      "First ray in vol, 360, set previous to last in sweep";
    *lray0 = (*_state)[0]._ray1;
    *lray1 = ray1;
    return true;
  }
  else
  {
    LOG(DEBUG_VERBOSE) << "First ray and not 360, leave a gap at 0";
    return false;
  }
}

//------------------------------------------------------------------
bool AzGradientFilter::_veryLastRay(const RadxRay *ray0, const RadxRay &ray,
				  const RadxRay **lray0,
				  const RadxRay **lray1) const
{
  // case of no next ray, should be last ray in last sweep.  If so, if 360,
  // can use first ray in last weep as ray1
  int s = ray.getSweepNumber();
  int nState = static_cast<int>(_state->size());
  if (s == (*_state)[nState-1]._sweepNumber && (*_state)[nState-1]._is360)
  {
    LOG(DEBUG_VERBOSE) << "Last ray in vol, 360, set next to 0th in sweep";
    *lray0 = ray0;
    *lray1 = (*_state)[nState-1]._ray0;
    return true;
  }
  else
  {
    LOG(DEBUG_VERBOSE) << "Last ray and not 360, leave a gap at last position";
    return false;
  }
}
