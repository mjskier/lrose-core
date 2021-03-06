/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
/* ** Copyright UCAR                                                         */
/* ** University Corporation for Atmospheric Research (UCAR)                 */
/* ** National Center for Atmospheric Research (NCAR)                        */
/* ** Boulder, Colorado, USA                                                 */
/* ** BSD licence applies - redistribution and use in source and binary      */
/* ** forms, with or without modification, are permitted provided that       */
/* ** the following conditions are met:                                      */
/* ** 1) If the software is modified to produce derivative works,            */
/* ** such modified software should be clearly marked, so as not             */
/* ** to confuse it with the version available from UCAR.                    */
/* ** 2) Redistributions of source code must retain the above copyright      */
/* ** notice, this list of conditions and the following disclaimer.          */
/* ** 3) Redistributions in binary form must reproduce the above copyright   */
/* ** notice, this list of conditions and the following disclaimer in the    */
/* ** documentation and/or other materials provided with the distribution.   */
/* ** 4) Neither the name of UCAR nor the names of its contributors,         */
/* ** if any, may be used to endorse or promote products derived from        */
/* ** this software without specific prior written permission.               */
/* ** DISCLAIMER: THIS SOFTWARE IS PROVIDED 'AS IS' AND WITHOUT ANY EXPRESS  */
/* ** OR IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED      */
/* ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.    */
/* *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* */
////////////////////////////////////////////
// Params.cc
//
// TDRP C++ code file for class 'Params'.
//
// Code for program NidsVad2Spdb
//
// This file has been automatically
// generated by TDRP, do not modify.
//
/////////////////////////////////////////////

/**
 *
 * @file Params.cc
 *
 * @class Params
 *
 * This class is automatically generated by the Table
 * Driven Runtime Parameters (TDRP) system
 *
 * @note Source is automatically generated from
 *       paramdef file at compile time, do not modify
 *       since modifications will be overwritten.
 *
 *
 * @author Automatically generated
 *
 */
#include "Params.hh"
#include <cstring>

  ////////////////////////////////////////////
  // Default constructor
  //

  Params::Params()

  {

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // class name

    _className = "Params";

    // initialize table

    _init();

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = false;

  }

  ////////////////////////////////////////////
  // Copy constructor
  //

  Params::Params(const Params& source)

  {

    // sync the source object

    source.sync();

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // class name

    _className = "Params";

    // copy table

    tdrpCopyTable((TDRPtable *) source._table, _table);

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = false;

  }

  ////////////////////////////////////////////
  // Destructor
  //

  Params::~Params()

  {

    // free up

    freeAll();

  }

  ////////////////////////////////////////////
  // Assignment
  //

  void Params::operator=(const Params& other)

  {

    // sync the other object

    other.sync();

    // free up any existing memory

    freeAll();

    // zero out table

    memset(_table, 0, sizeof(_table));

    // zero out members

    memset(&_start_, 0, &_end_ - &_start_);

    // copy table

    tdrpCopyTable((TDRPtable *) other._table, _table);

    // set members

    tdrpTable2User(_table, &_start_);

    _exitDeferred = other._exitDeferred;

  }

  ////////////////////////////////////////////
  // loadFromArgs()
  //
  // Loads up TDRP using the command line args.
  //
  // Check usage() for command line actions associated with
  // this function.
  //
  //   argc, argv: command line args
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   char **params_path_p:
  //     If this is non-NULL, it is set to point to the path
  //     of the params file used.
  //
  //   bool defer_exit: normally, if the command args contain a 
  //      print or check request, this function will call exit().
  //      If defer_exit is set, such an exit is deferred and the
  //      private member _exitDeferred is set.
  //      Use exidDeferred() to test this flag.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadFromArgs(int argc, char **argv,
                           char **override_list,
                           char **params_path_p,
                           bool defer_exit)
  {
    int exit_deferred;
    if (_tdrpLoadFromArgs(argc, argv,
                          _table, &_start_,
                          override_list, params_path_p,
                          _className,
                          defer_exit, &exit_deferred)) {
      return (-1);
    } else {
      if (exit_deferred) {
        _exitDeferred = true;
      }
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadApplyArgs()
  //
  // Loads up TDRP using the params path passed in, and applies
  // the command line args for printing and checking.
  //
  // Check usage() for command line actions associated with
  // this function.
  //
  //   const char *param_file_path: the parameter file to be read in
  //
  //   argc, argv: command line args
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   bool defer_exit: normally, if the command args contain a 
  //      print or check request, this function will call exit().
  //      If defer_exit is set, such an exit is deferred and the
  //      private member _exitDeferred is set.
  //      Use exidDeferred() to test this flag.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadApplyArgs(const char *params_path,
                            int argc, char **argv,
                            char **override_list,
                            bool defer_exit)
  {
    int exit_deferred;
    if (tdrpLoadApplyArgs(params_path, argc, argv,
                          _table, &_start_,
                          override_list,
                          _className,
                          defer_exit, &exit_deferred)) {
      return (-1);
    } else {
      if (exit_deferred) {
        _exitDeferred = true;
      }
      return (0);
    }
  }

  ////////////////////////////////////////////
  // isArgValid()
  // 
  // Check if a command line arg is a valid TDRP arg.
  //

  bool Params::isArgValid(const char *arg)
  {
    return (tdrpIsArgValid(arg));
  }

  ////////////////////////////////////////////
  // load()
  //
  // Loads up TDRP for a given class.
  //
  // This version of load gives the programmer the option to load
  // up more than one class for a single application. It is a
  // lower-level routine than loadFromArgs, and hence more
  // flexible, but the programmer must do more work.
  //
  //   const char *param_file_path: the parameter file to be read in.
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   expand_env: flag to control environment variable
  //               expansion during tokenization.
  //               If TRUE, environment expansion is set on.
  //               If FALSE, environment expansion is set off.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::load(const char *param_file_path,
                   char **override_list,
                   int expand_env, int debug)
  {
    if (tdrpLoad(param_file_path,
                 _table, &_start_,
                 override_list,
                 expand_env, debug)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadFromBuf()
  //
  // Loads up TDRP for a given class.
  //
  // This version of load gives the programmer the option to
  // load up more than one module for a single application,
  // using buffers which have been read from a specified source.
  //
  //   const char *param_source_str: a string which describes the
  //     source of the parameter information. It is used for
  //     error reporting only.
  //
  //   char **override_list: A null-terminated list of overrides
  //     to the parameter file.
  //     An override string has exactly the format of an entry
  //     in the parameter file itself.
  //
  //   const char *inbuf: the input buffer
  //
  //   int inlen: length of the input buffer
  //
  //   int start_line_num: the line number in the source which
  //     corresponds to the start of the buffer.
  //
  //   expand_env: flag to control environment variable
  //               expansion during tokenization.
  //               If TRUE, environment expansion is set on.
  //               If FALSE, environment expansion is set off.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadFromBuf(const char *param_source_str,
                          char **override_list,
                          const char *inbuf, int inlen,
                          int start_line_num,
                          int expand_env, int debug)
  {
    if (tdrpLoadFromBuf(param_source_str,
                        _table, &_start_,
                        override_list,
                        inbuf, inlen, start_line_num,
                        expand_env, debug)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // loadDefaults()
  //
  // Loads up default params for a given class.
  //
  // See load() for more detailed info.
  //
  //  Returns 0 on success, -1 on failure.
  //

  int Params::loadDefaults(int expand_env)
  {
    if (tdrpLoad(NULL,
                 _table, &_start_,
                 NULL, expand_env, FALSE)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // sync()
  //
  // Syncs the user struct data back into the parameter table,
  // in preparation for printing.
  //
  // This function alters the table in a consistent manner.
  // Therefore it can be regarded as const.
  //

  void Params::sync(void) const
  {
    tdrpUser2Table(_table, (char *) &_start_);
  }

  ////////////////////////////////////////////
  // print()
  // 
  // Print params file
  //
  // The modes supported are:
  //
  //   PRINT_SHORT:   main comments only, no help or descriptions
  //                  structs and arrays on a single line
  //   PRINT_NORM:    short + descriptions and help
  //   PRINT_LONG:    norm  + arrays and structs expanded
  //   PRINT_VERBOSE: long  + private params included
  //

  void Params::print(FILE *out, tdrp_print_mode_t mode)
  {
    tdrpPrint(out, _table, _className, mode);
  }

  ////////////////////////////////////////////
  // checkAllSet()
  //
  // Return TRUE if all set, FALSE if not.
  //
  // If out is non-NULL, prints out warning messages for those
  // parameters which are not set.
  //

  int Params::checkAllSet(FILE *out)
  {
    return (tdrpCheckAllSet(out, _table, &_start_));
  }

  //////////////////////////////////////////////////////////////
  // checkIsSet()
  //
  // Return TRUE if parameter is set, FALSE if not.
  //
  //

  int Params::checkIsSet(const char *paramName)
  {
    return (tdrpCheckIsSet(paramName, _table, &_start_));
  }

  ////////////////////////////////////////////
  // freeAll()
  //
  // Frees up all TDRP dynamic memory.
  //

  void Params::freeAll(void)
  {
    tdrpFreeAll(_table, &_start_);
  }

  ////////////////////////////////////////////
  // usage()
  //
  // Prints out usage message for TDRP args as passed
  // in to loadFromArgs().
  //

  void Params::usage(ostream &out)
  {
    out << "TDRP args: [options as below]\n"
        << "   [ -params/--params path ] specify params file path\n"
        << "   [ -check_params/--check_params] check which params are not set\n"
        << "   [ -print_params/--print_params [mode]] print parameters\n"
        << "     using following modes, default mode is 'norm'\n"
        << "       short:   main comments only, no help or descr\n"
        << "                structs and arrays on a single line\n"
        << "       norm:    short + descriptions and help\n"
        << "       long:    norm  + arrays and structs expanded\n"
        << "       verbose: long  + private params included\n"
        << "       short_expand:   short with env vars expanded\n"
        << "       norm_expand:    norm with env vars expanded\n"
        << "       long_expand:    long with env vars expanded\n"
        << "       verbose_expand: verbose with env vars expanded\n"
        << "   [ -tdrp_debug] debugging prints for tdrp\n"
        << "   [ -tdrp_usage] print this usage\n";
  }

  ////////////////////////////////////////////
  // arrayRealloc()
  //
  // Realloc 1D array.
  //
  // If size is increased, the values from the last array 
  // entry is copied into the new space.
  //
  // Returns 0 on success, -1 on error.
  //

  int Params::arrayRealloc(const char *param_name, int new_array_n)
  {
    if (tdrpArrayRealloc(_table, &_start_,
                         param_name, new_array_n)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // array2DRealloc()
  //
  // Realloc 2D array.
  //
  // If size is increased, the values from the last array 
  // entry is copied into the new space.
  //
  // Returns 0 on success, -1 on error.
  //

  int Params::array2DRealloc(const char *param_name,
                             int new_array_n1,
                             int new_array_n2)
  {
    if (tdrpArray2DRealloc(_table, &_start_, param_name,
                           new_array_n1, new_array_n2)) {
      return (-1);
    } else {
      return (0);
    }
  }

  ////////////////////////////////////////////
  // _init()
  //
  // Class table initialization function.
  //
  //

  void Params::_init()

  {

    TDRPtable *tt = _table;

    // Parameter 'Comment 0'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 0");
    tt->comment_hdr = tdrpStrDup("NidsVad2Spdb is a small program to read NIDS VAD sounding\ndata and produce an SPDB database of soundings. The input\nfiles look something like this :\n\n# NIDS VAD data for:\n# /nids/raw/nids/FTG/VAD/19990525/19990525.2115.VAD\n# Julian Date : 2451324\n# Calendar Date: 5 25 1999\n# Time: 21:22:1\n# Radar Latitude: 39.786\n# Radar Longitude: 4294862.751\n# Radar Altitude: 5610\n# Radar Operating in Precipitation Mode\n# Radar Scan Coverage Pattern: 21\n# Max Wind Speed (kts): 12\n# Max Wind Direction (deg): 83\n# Max Wind Altitude (ft): 12000\n#\n# Alt (m) DIR/SPD(m/s)  Time (gmt)\n\n1829    162   3      2117\n2134    139   5      2117\n2439    138   5      2117\n2743    141   5      2117\n\nNote that at least one entry in the header (the longitude)\nseems deeply suspect. As a result, the header is not read.\nThe time is parsed from the file name, which should\nbe something like FTG/19990525/19990525.2055.VAD - in\nthis case the three letter FTG code indicates the radar\nsite. This is used to look up the VAD location (lat, lon and\naltitude) from the parameter file.\n\n\nNOTE that it is assumed that a _latest_data_info file\nwill be generated for the input files. At the time\nof writing the getNIDSvad.pl script that generates the\ninput files will do this if the -l option is specified for it.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'debug'
    // ctype is 'tdrp_bool_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = BOOL_TYPE;
    tt->param_name = tdrpStrDup("debug");
    tt->descr = tdrpStrDup("Debug option");
    tt->help = tdrpStrDup("If set, debug messages will be printed.");
    tt->val_offset = (char *) &debug - &_start_;
    tt->single_val.b = pFALSE;
    tt++;
    
    // Parameter 'instance'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("instance");
    tt->descr = tdrpStrDup("Process instance");
    tt->help = tdrpStrDup("Used for registration with procmap.");
    tt->val_offset = (char *) &instance - &_start_;
    tt->single_val.s = tdrpStrDup("primary");
    tt++;
    
    // Parameter 'mode'
    // ctype is '_op_mode'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = ENUM_TYPE;
    tt->param_name = tdrpStrDup("mode");
    tt->descr = tdrpStrDup("Operation mode");
    tt->help = tdrpStrDup("Program may be run in two modes, archive and realtime. In realtime mode, the conversion is performed for each input file as it becomes available. In archive mode, the file list is obtained from the command line.");
    tt->val_offset = (char *) &mode - &_start_;
    tt->enum_def.name = tdrpStrDup("op_mode");
    tt->enum_def.nfields = 2;
    tt->enum_def.fields = (enum_field_t *)
        tdrpMalloc(tt->enum_def.nfields * sizeof(enum_field_t));
      tt->enum_def.fields[0].name = tdrpStrDup("ARCHIVE");
      tt->enum_def.fields[0].val = ARCHIVE;
      tt->enum_def.fields[1].name = tdrpStrDup("REALTIME");
      tt->enum_def.fields[1].val = REALTIME;
    tt->single_val.e = REALTIME;
    tt++;
    
    // Parameter 'Comment 1'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 1");
    tt->comment_hdr = tdrpStrDup("DATA INPUT.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'InDirs'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("InDirs");
    tt->descr = tdrpStrDup("Input directories in which data appear.\nUsed in realtime mode only.");
    tt->help = tdrpStrDup("Directory path for input data files.");
    tt->array_offset = (char *) &_InDirs - &_start_;
    tt->array_n_offset = (char *) &InDirs_n - &_start_;
    tt->is_array = TRUE;
    tt->array_len_fixed = FALSE;
    tt->array_elem_size = sizeof(char*);
    tt->array_n = 11;
    tt->array_vals = (tdrpVal_t *)
        tdrpMalloc(tt->array_n * sizeof(tdrpVal_t));
      tt->array_vals[0].s = tdrpStrDup("$(RAP_DATA_DIR)/$(PROJECT)/other/vad/DMX");
      tt->array_vals[1].s = tdrpStrDup("$(RAP_DATA_DIR)/$(PROJECT)/other/vad/DVN");
      tt->array_vals[2].s = tdrpStrDup("$(RAP_DATA_DIR)/$(PROJECT)/other/vad/GRR");
      tt->array_vals[3].s = tdrpStrDup("$(RAP_DATA_DIR)/$(PROJECT)/other/vad/ILN");
      tt->array_vals[4].s = tdrpStrDup("$(RAP_DATA_DIR)/$(PROJECT)/other/vad/ILX");
      tt->array_vals[5].s = tdrpStrDup("$(RAP_DATA_DIR)/$(PROJECT)/other/vad/IND");
      tt->array_vals[6].s = tdrpStrDup("$(RAP_DATA_DIR)/$(PROJECT)/other/vad/IWX");
      tt->array_vals[7].s = tdrpStrDup("$(RAP_DATA_DIR)/$(PROJECT)/other/vad/LOT");
      tt->array_vals[8].s = tdrpStrDup("$(RAP_DATA_DIR)/$(PROJECT)/other/vad/LSX");
      tt->array_vals[9].s = tdrpStrDup("$(RAP_DATA_DIR)/$(PROJECT)/other/vad/LVX");
      tt->array_vals[10].s = tdrpStrDup("$(RAP_DATA_DIR)/$(PROJECT)/other/vad/MKX");
    tt++;
    
    // Parameter 'fileExtension'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("fileExtension");
    tt->descr = tdrpStrDup("Input file extension.");
    tt->help = tdrpStrDup("Default is to search for *.gms - if string is NULL, all extensions are valid.");
    tt->val_offset = (char *) &fileExtension - &_start_;
    tt->single_val.s = tdrpStrDup("VAD");
    tt++;
    
    // Parameter 'max_realtime_valid_age'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("max_realtime_valid_age");
    tt->descr = tdrpStrDup("Max age of input data");
    tt->help = tdrpStrDup("For realtime only - max age of input data for it to be valid.\nNOTE : NOT IMPLEMENTED FOR CURRENT MODE OF REALTIME TRIGGERING.");
    tt->val_offset = (char *) &max_realtime_valid_age - &_start_;
    tt->single_val.i = 7200;
    tt++;
    
    // Parameter 'siteMap'
    // ctype is '_id_t'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRUCT_TYPE;
    tt->param_name = tdrpStrDup("siteMap");
    tt->descr = tdrpStrDup("Map that relates the three character radar\nIDs to locations (lat, lon, alt in meters).\nCan be set up from the US_Nexrad.map file and\nthe /weather/include/stations.new file. Default\nis suitable for Sterling nowcaster project.\nSounding site IDs are somewhat arbitrary.");
    tt->help = tdrpStrDup("The three character ID is parsed from the filename.\nIf an ID is encountered that is not in this list it is not processed.");
    tt->array_offset = (char *) &_siteMap - &_start_;
    tt->array_n_offset = (char *) &siteMap_n - &_start_;
    tt->is_array = TRUE;
    tt->array_len_fixed = FALSE;
    tt->array_elem_size = sizeof(id_t);
    tt->array_n = 9;
    tt->struct_def.name = tdrpStrDup("id_t");
    tt->struct_def.nfields = 5;
    tt->struct_def.fields = (struct_field_t *)
        tdrpMalloc(tt->struct_def.nfields * sizeof(struct_field_t));
      tt->struct_def.fields[0].ftype = tdrpStrDup("string");
      tt->struct_def.fields[0].fname = tdrpStrDup("vadID");
      tt->struct_def.fields[0].ptype = STRING_TYPE;
      tt->struct_def.fields[0].rel_offset = 
        (char *) &_siteMap->vadID - (char *) _siteMap;
      tt->struct_def.fields[1].ftype = tdrpStrDup("double");
      tt->struct_def.fields[1].fname = tdrpStrDup("lat");
      tt->struct_def.fields[1].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[1].rel_offset = 
        (char *) &_siteMap->lat - (char *) _siteMap;
      tt->struct_def.fields[2].ftype = tdrpStrDup("double");
      tt->struct_def.fields[2].fname = tdrpStrDup("lon");
      tt->struct_def.fields[2].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[2].rel_offset = 
        (char *) &_siteMap->lon - (char *) _siteMap;
      tt->struct_def.fields[3].ftype = tdrpStrDup("double");
      tt->struct_def.fields[3].fname = tdrpStrDup("alt");
      tt->struct_def.fields[3].ptype = DOUBLE_TYPE;
      tt->struct_def.fields[3].rel_offset = 
        (char *) &_siteMap->alt - (char *) _siteMap;
      tt->struct_def.fields[4].ftype = tdrpStrDup("int");
      tt->struct_def.fields[4].fname = tdrpStrDup("soundingSiteId");
      tt->struct_def.fields[4].ptype = INT_TYPE;
      tt->struct_def.fields[4].rel_offset = 
        (char *) &_siteMap->soundingSiteId - (char *) _siteMap;
    tt->n_struct_vals = 45;
    tt->struct_vals = (tdrpVal_t *)
        tdrpMalloc(tt->n_struct_vals * sizeof(tdrpVal_t));
      tt->struct_vals[0].s = tdrpStrDup("AKQ");
      tt->struct_vals[1].d = 36.9839;
      tt->struct_vals[2].d = -77.007;
      tt->struct_vals[3].d = 34;
      tt->struct_vals[4].i = 1;
      tt->struct_vals[5].s = tdrpStrDup("CCX");
      tt->struct_vals[6].d = 40.9231;
      tt->struct_vals[7].d = -78.003;
      tt->struct_vals[8].d = 733;
      tt->struct_vals[9].i = 2;
      tt->struct_vals[10].s = tdrpStrDup("DIX");
      tt->struct_vals[11].d = 39.9469;
      tt->struct_vals[12].d = -74.41;
      tt->struct_vals[13].d = 45;
      tt->struct_vals[14].i = 3;
      tt->struct_vals[15].s = tdrpStrDup("DOX");
      tt->struct_vals[16].d = 38.8256;
      tt->struct_vals[17].d = -75.44;
      tt->struct_vals[18].d = 15;
      tt->struct_vals[19].i = 4;
      tt->struct_vals[20].s = tdrpStrDup("FCX");
      tt->struct_vals[21].d = 37.0244;
      tt->struct_vals[22].d = -80.273;
      tt->struct_vals[23].d = 874;
      tt->struct_vals[24].i = 5;
      tt->struct_vals[25].s = tdrpStrDup("FTG");
      tt->struct_vals[26].d = 39.7867;
      tt->struct_vals[27].d = -104.545;
      tt->struct_vals[28].d = 1675;
      tt->struct_vals[29].i = 6;
      tt->struct_vals[30].s = tdrpStrDup("LWX");
      tt->struct_vals[31].d = 38.9753;
      tt->struct_vals[32].d = -77.477;
      tt->struct_vals[33].d = 83;
      tt->struct_vals[34].i = 7;
      tt->struct_vals[35].s = tdrpStrDup("PBZ");
      tt->struct_vals[36].d = 40.5317;
      tt->struct_vals[37].d = -80.218;
      tt->struct_vals[38].d = 361;
      tt->struct_vals[39].i = 8;
      tt->struct_vals[40].s = tdrpStrDup("RLX");
      tt->struct_vals[41].d = 38.3111;
      tt->struct_vals[42].d = -81.723;
      tt->struct_vals[43].d = 329;
      tt->struct_vals[44].i = 9;
    tt++;
    
    // Parameter 'Comment 2'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = COMMENT_TYPE;
    tt->param_name = tdrpStrDup("Comment 2");
    tt->comment_hdr = tdrpStrDup("DATA OUTPUT.");
    tt->comment_text = tdrpStrDup("");
    tt++;
    
    // Parameter 'OutUrl'
    // ctype is 'char*'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = STRING_TYPE;
    tt->param_name = tdrpStrDup("OutUrl");
    tt->descr = tdrpStrDup("URL for output SPDB data.");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &OutUrl - &_start_;
    tt->single_val.s = tdrpStrDup("spdbp:://localhost::$(PROJECT)/spdb/VadSoundings");
    tt++;
    
    // Parameter 'expiry'
    // ctype is 'int'
    
    memset(tt, 0, sizeof(TDRPtable));
    tt->ptype = INT_TYPE;
    tt->param_name = tdrpStrDup("expiry");
    tt->descr = tdrpStrDup("How long data are valid, seconds.");
    tt->help = tdrpStrDup("");
    tt->val_offset = (char *) &expiry - &_start_;
    tt->single_val.i = 1800;
    tt++;
    
    // trailing entry has param_name set to NULL
    
    tt->param_name = NULL;
    
    return;
  
  }
