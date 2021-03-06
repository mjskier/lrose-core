
//////////////////////////////////////////////////////////////
//
// Header file for CommRxDevAlertFormClass
//
//    This file is generated by RapidApp 1.2
//
//    This class is derived from CommRxDevAlertFormClassUI which 
//    implements the user interface created in 
//    RapidApp. This class contains virtual
//    functions that are called from the user interface.
//
//    When you modify this header file, limit your changes to those
//    areas between the "//---- Start/End editable code block" markers
//
//    This will allow RapidApp to integrate changes more easily
//
//    This class is a ViewKit user interface "component".
//    For more information on how components are used, see the
//    "ViewKit Programmers' Manual", and the RapidApp
//    User's Guide.
//////////////////////////////////////////////////////////////
#ifndef COMMRXDEVALERTFORMCLASS_H
#define COMMRXDEVALERTFORMCLASS_H
#include "CommRxDevAlertFormClassUI.h"
//---- Start editable code block: headers and declarations


//---- End editable code block: headers and declarations


//---- CommRxDevAlertFormClass class declaration

class CommRxDevAlertFormClass : public CommRxDevAlertFormClassUI
{

  public:

    CommRxDevAlertFormClass ( const char *, Widget );
    CommRxDevAlertFormClass ( const char * );
    ~CommRxDevAlertFormClass();
    const char *  className();

    static VkComponent *CreateCommRxDevAlertFormClass( const char *name, Widget parent ); 

    //---- Start editable code block: CommRxDevAlertFormClass public


    //---- End editable code block: CommRxDevAlertFormClass public



  protected:


    // These functions will be called as a result of callbacks
    // registered in CommRxDevAlertFormClassUI

    virtual void acknowleged ( Widget, XtPointer );
    virtual void newAlertPeriod ( Widget, XtPointer );

    //---- Start editable code block: CommRxDevAlertFormClass protected


    //---- End editable code block: CommRxDevAlertFormClass protected



  private:

    static void* RegisterCommRxDevAlertFormClassInterface();

    //---- Start editable code block: CommRxDevAlertFormClass private


    //---- End editable code block: CommRxDevAlertFormClass private


};
//---- Start editable code block: End of generated code


//---- End editable code block: End of generated code

#endif

