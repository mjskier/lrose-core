# *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 
# ** Copyright UCAR (c) 1992 - 2012 
# ** University Corporation for Atmospheric Research(UCAR) 
# ** National Center for Atmospheric Research(NCAR) 
# ** Research Applications Laboratory(RAL) 
# ** P.O.Box 3000, Boulder, Colorado, 80307-3000, USA 
# ** 2012/9/18 21:3:20 
# *=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=* 

#
# Recursive make - makes the subdirectory code
#

include $(RAP_MAKE_INC_DIR)/rap_make_macros

TARGETS = $(GENERAL_TARGETS)

MODULE_NAME = rapplot

LIBNAME = lib$(MODULE_NAME).a

SUB_DIRS = \
	gplot \
	xutils \
	FirLoc \
	StationLoc

include $(RAP_MAKE_INC_DIR)/rap_make_recursive_dir_targets

include $(RAP_MAKE_INC_DIR)/rap_make_lib_targets

# -------------------------------------------------------
# This is a special case due to multiple include subdirectories
#

install_include: mk_inc_dir FORCE
	$(CP) include/rapplot/*.h  $(RAP_INC_DIR)/rapplot
	$(CP) include/rapplot/*.hh $(RAP_INC_DIR)/rapplot
	$(CP) include/prologues/*.ps $(RAP_INC_DIR)/prologues

mk_inc_dir:
	if $(TEST) -d $(RAP_INC_DIR)/rapplot; then :; else \
		$(MKDIR) $(RAP_INC_DIR)/rapplot; fi
	if $(TEST) -d $(RAP_INC_DIR)/prologues; then :; else \
		$(MKDIR) $(RAP_INC_DIR)/prologues; fi






