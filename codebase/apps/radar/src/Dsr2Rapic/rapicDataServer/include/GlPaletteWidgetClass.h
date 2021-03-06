
//////////////////////////////////////////////////////////////
//
// Header file for GlPaletteWidgetClass
//
//    This file is generated by RapidApp 1.2
//
//    This class implements the user interface portion of a class
//
//    If you do modify this class, limit your changes to adding
//    members below the "//--- End generated code section" markers
//
//    This will allow RapidApp to integrate changes more easily
//
//    This class is a ViewKit user interface "component".
//    For more information on how components are used, see the
//    "ViewKit Programmers' Manual", and the RapidApp
//    User's Guide.
//
//////////////////////////////////////////////////////////////
#ifndef GLPALETTEWIDGETCLASS_H
#define GLPALETTEWIDGETCLASS_H
#include <Vk/VkComponent.h>


//---- End generated headers
#include "oglwid.h"

class GlPaletteWidgetClass : public VkComponent
{ 


  public:

    GlPaletteWidgetClass ( const char *, Widget );
    GlPaletteWidgetClass ( const char * );
    ~GlPaletteWidgetClass();
    void create ( Widget );
    const char *  className();

    static VkComponent *CreateGlPaletteWidgetClass( const char *name, Widget parent ); 

    //--- End generated code section



  protected:


    // Widgets created by this class

    Widget  _glPaletteWidgetClass1;


    // These virtual functions are called from the private callbacks (below)
    // Intended to be overriden in derived classes to define actions

    virtual void OGLWinExposed ( Widget, XtPointer );
    virtual void OGLWinGInit ( Widget, XtPointer );
    virtual void OGLWinInput ( Widget, XtPointer );
    virtual void OGLWinResized ( Widget, XtPointer );

    //--- End generated code section
    oglwid_props *oglwidProps;


  private: 

    // Array of default resources

    static String      _defaultGlPaletteWidgetClassResources[];


    // Callbacks to interface with Motif

    static void OGLWinExposedCallback ( Widget, XtPointer, XtPointer );
    static void OGLWinGInitCallback ( Widget, XtPointer, XtPointer );
    static void OGLWinInputCallback ( Widget, XtPointer, XtPointer );
    static void OGLWinResizedCallback ( Widget, XtPointer, XtPointer );

    //--- End generated code section
    Widget              createGlWidget(char *glWidName, Widget parentWid,
				       int rgba, int dblBuff, bool allocBG,
				       int alphaSize, int auxBuffs, int stencilSize);

};
//---- End of generated code

#endif

