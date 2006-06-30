/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

// src/Inventor/Qt/SoQtCommon.cpp.  Generated from SoGuiCommon.cpp.in by configure.

/* For the Doxygen tool. */

/*! \defgroup misc Miscellaneous Classes */
/*! \defgroup devices Qt Device Classes */
/*! \defgroup components Qt Components */
/*! \defgroup viewers Qt Viewer Components */


// FIXME: the code example shouldn't be duplicated here -- it's
// already part of the SoQt mainpage-doc. 20020806 mortene.

/*!
  \class SoQt SoQt.h Inventor/Qt/SoQt.h
  \brief The SoQt class takes care of Qt initialization and event dispatching.
  \ingroup misc

  This is the "application-wide" class with solely static methods
  handling initialization and event processing tasks. You must use
  this class in any application built on top of the SoQt
  library.

  Typical usage is as follows (complete application code):

  \code
  #include <Inventor/Qt/SoQt.h>
  #include <Inventor/Qt/viewers/SoQtExaminerViewer.h>
  #include <Inventor/nodes/SoBaseColor.h>
  #include <Inventor/nodes/SoCone.h>
  #include <Inventor/nodes/SoSeparator.h>
  
  int
  main(int argc, char ** argv)
  {
    // Initialize SoQt and Inventor API libraries. This returns a main
    // window to use.
    QWidget * mainwin = SoQt::init(argc, argv, argv[0]);
  
    // Make a dead simple scene graph, only containing a single
    // yellow cone under the scenegraph root.
    SoSeparator * root = new SoSeparator;
    root->ref();

    SoBaseColor * col = new SoBaseColor;
    col->rgb = SbColor(1, 1, 0);
    root->addChild(col);

    root->addChild(new SoCone);
  
    // Use one of the convenient viewer classes.
    SoQtExaminerViewer * eviewer = new SoQtExaminerViewer(mainwin);
    eviewer->setSceneGraph(root);
    eviewer->show();
  
    // Pop up the main window.
    SoQt::show(mainwin);
    // Loop until exit.
    SoQt::mainLoop();

    // Clean up resources.
    delete eviewer;
    root->unref();

    return 0;
  }
  \endcode

  And voila:

  <center>
  <img src="http://doc.coin3d.org/images/SoLibs/general/sogui-class-example.png">
  </center>

  \sa SoQtComponent
*/

#include <stdlib.h>
#include <string.h>
#include <Inventor/Qt/SoQt.h>
#include <Inventor/Qt/SoGuiP.h>
#include <Inventor/Qt/SoAny.h>


// Default constructor and the destructor is private (SoQt class
// consists solely of static functions).
SoQt::SoQt(void) { }
SoQt::~SoQt() { }


// *************************************************************************

/*!
  This function initializes the SoQt library, as well as the
  Inventor API. The latter is done by calling \a SoDB::init(), \a
  SoNodeKit::init() and \a SoInteraction::init().

  The returned QWidget * is a toplevel shell widget for the
  application, which can be used as a shell for the main component.

  This method is provided for easier porting / compatibility with the
  original SGI Inventor InventorXt library. It just adds dummy \a argc
  and \a argv arguments and calls the SoQt::init() method below.
*/
QWidget *
SoQt::init(const char * appname, const char * classname)
{
  // If this is SoQt, Qt will keep a reference to the appname string
  // -- so make it guaranteed permanent.
  char * buf = NULL;
  if (appname != NULL) {
    buf = new char[strlen(appname) + 1]; // FIXME: minor memleak, free on app-exit. 20020117 mortene.
    (void)strcpy(buf, appname);
  }

  // Fake argc and argv setup, forward to real init routine.
  static char *array[1]; // use static array to avoid memory corruption in Qt
  array[0] = buf;
  int argc = (buf != NULL) ? 1 : 0;
  return SoQt::init(argc, array, appname, classname);
}

/*!
  \fn QWidget * SoQt::init(int & argc, char ** argv, const char * appname, const char * classname)

  This function initializes the SoQt library, as well as the
  Inventor API. The latter is done by calling \a SoDB::init(), \a
  SoNodeKit::init() and \a SoInteraction::init().

  Creates an application framework and constructs and returns a main
  widget for you.

  The returned QWidget * is a toplevel shell widget for the
  application, which can be used as a shell for the main component.
*/

/*!
  \fn void SoQt::init(QWidget * toplevelwidget)

  This function initializes the SoQt library, as well as the
  Inventor API. The latter is done by calling \a SoDB::init(), \a
  SoNodeKit::init() and \a SoInteraction::init().

  Assumes you are creating your own application framework and main
  widget.  \a toplevelwidget should be your application's main widget.
*/

/*!
  \fn void SoQt::done(void)

  Cleans up all static data allocated by the SoQt library on
  initialization.

  <!-- (Disabled: see FIXME in SoQt.cpp:855)
  Is called implicitly from the end of SoQt::mainLoop(), so the
  application programmer should not call it explicitly unless she
  has taken control over the native event loop herself, and is
  therefore not using SoQt::mainLoop().

  (Even then it is usually not necessary to call this method, as the
  operating system should take care of cleaning up resource use when
  an application exits. This method is mainly provided as a manner to
  be able to clean up in "unusual" run-time environments, for instance
  if SoQt is used as a component in a browser plug-in.)
  -->

  It should never be invoked more than \e once, and that
  is just before application exit, as it deallocates \e static data
  allocated as "one-off" operations in SoQt::init().

  NOTE: done() is not present in the original API for SGI's InventorXt
  library.
*/

/*!
  \fn void SoQt::mainLoop(void)

  This is the event dispatch loop.

  It doesn't return until application exit is somehow forced, either
  programmatically from the relevant API-call of the native toolkit,
  or when the user closes the application's main widget.

  An important note: be careful about how you handle
  SoQtComponent-derived objects after the application control returns
  from mainLoop(), as SoQt will then have been "cleaned up" with
  regards to various internal resources. So doing for instance
  something like this:

  \code
  SoQt::mainLoop();
  viewer->hide();
  \endcode

  ..spells "undefined behavior, expect a crash".

  \e Deleting a component after mainLoop() returns is allowed, though,
  and also necessary to avoid getting reports of possible memory leaks
  from memleak checkers.
*/

/*!
  \fn void SoQt::exitMainLoop(void)

  This function will make the main event loop finish looping.

  NOTE: exitMainLoop() is not present in the original API for SGI's
  InventorXt library.
*/

/*!
  \fn QWidget * SoQt::getTopLevelWidget(void)

  Returns the QWidget * which is the main widget for the
  application. When this widget gets closed, SoQt::mainLoop() will
  return (unless the close event is caught by the user).

  \sa getShellWidget()
*/

// *************************************************************************

/*!
  This method will fill in the integers pointed to by the arguments
  with the corresponding part of the version release number of the
  SoQt library.

  A \c NULL pointer will make that part of the version number be ignored.

  This method is not part of the original InventorXt API from SGI.
*/
void
SoQt::getVersionInfo(int * major, int * minor, int * micro)
{
  if (major) { *major = SOQT_MAJOR_VERSION; }
  if (minor) { *minor = SOQT_MINOR_VERSION; }
  if (micro) { *micro = SOQT_MICRO_VERSION; }
}

/*!
  This method returns a string containing the version id of the
  library.

  This method is not part of the original InventorXt API from SGI.
*/
const char *
SoQt::getVersionString(void)
{
  static const char version[] = SOQT_VERSION;
  return version;
}

// *************************************************************************

/*!
  \typedef void SoQt::FatalErrorCB(const SbString errmsg, SoQt::FatalErrors errcode, void * userdata)

  An application function callback for handling fatal errors should be
  of this type.

  The first argument is an error message in English describing the
  details of the error. The second argument is an error code used so
  the application can identify specific conditions. The third argument
  is the userdata pointer passed in to SoQt::setFatalErrorHandler().
*/

/*!
  \enum SoQt::FatalErrors
  Numerical identifiers for classifying the different kinds of possible
  fatal errors.
*/

/*!
  \var SoQt::FatalErrors SoQt::NO_OPENGL_CANVAS

  Could not construct \e any valid OpenGL canvas. Something is very
  wrong on the client system.
*/
/*!
  \var SoQt::FatalErrors SoQt::INTERNAL_ASSERT

  An internal error condition that should never happen was
  detected. The most likely cause of this is programmering errors
  within the SoQt library itself.
*/
/*!
  \var SoQt::FatalErrors SoQt::UNSPECIFIED_ERROR

  Signifies that we were not able to specify in any greater detail the
  error condition that came up.
*/

/*!
  Set up a callback to invoke in the case of unexpected fatal error
  conditions within the SoQt library.

  Almost any error condition within the library is handled in a robust
  way through return values indicating errors for the offending calls,
  but there are a few cases that are impossible to handle without
  seriously crippling the functionality.

  (One example is if we fail to find \e any way of making a valid
  OpenGL canvas. This is an indication that something is seriously
  wrong on the end-user's system, and the SoQt library will not work
  properly.)

  In the case of a fatal error, it is expected that the given
  application callback function communicates the problem to the
  end-user and then either exits the application or at least refrains
  from using any part of the SoQt library.

  If no callback is explicitly set up by the application, the SoQt
  library will display an error message to the end-user and then exit
  the application.

  When setting a callback, this method returns a pointer to the
  previous callback function, or \c NULL if none.

  (This is an extension versus the original SGI InventorXt library
  API.)


  On a related note, be aware that the end-user will still be notified
  about non-fatal errors and warning messages through a dialog box. If
  you want to handle these yourself, or if you don't want your
  end-user to see any of these non-critical messages, you will also
  need to install an error handler callback function on the Coin
  library itself:

  \code
    SoDebugError::setHandlerCallback(myErrorHandlerCB, myCBUserData);
  \endcode

  (Please also see the documentation of
  SoDebugError::setHandlerCallback().)

 */
SoQt::FatalErrorCB *
SoQt::setFatalErrorHandler(SoQt::FatalErrorCB * cb, void * userdata)
{
  return SoAny::si()->setFatalErrorHandler(cb, userdata);
}

// *************************************************************************

/*!
  Returns \c TRUE if this binary version of the SoQt library was
  compiled with debug settings on.

  This method was not part of the original SGI InventorXt library, but
  is an extension specific to the Coin project.
*/
SbBool
SoQt::isDebugLibrary(void)
{
  return SOQT_DEBUG != 0 ? TRUE : FALSE;
}

/*!
  Returns \c TRUE if this version of the SoQt library has an
  Application Binary Interface compatible with the given version.

  This method was not part of the original SGI InventorXt library, but
  is an extension specific to the Coin project.
*/
SbBool
SoQt::isCompatible(unsigned int major, unsigned int minor)
{
  if (major != SOQT_MAJOR_VERSION) { return FALSE; }
  if (minor > SOQT_MINOR_VERSION) { return FALSE; }
  return TRUE;
}

/*!
  \enum SoQt::ABIType
  Numerical identifiers to identify how the library was built.
*/
/*!
  \var SoQt::ABIType SoQt::DLL
  The SoQt library was built as a dynamic link library (aka "shared
  library").
*/
/*!
  \var SoQt::ABIType SoQt::LIB
  The SoQt library was built as a static library.
*/
/*!
  \var SoQt::ABIType SoQt::UNKNOWN
  The SoQt introspection mechanisms can not decide how the library
  was built.
*/


/*!
  Returns an indication on how the library was compiled: as a dynamic
  library, or as a static library.

  This method was not part of the original SGI InventorXt library, but
  is an extension specific to the Coin project.
*/
SoQt::ABIType
SoQt::getABIType(void)
{
  // FIXME: replace this ugly shit with a configure-check to test if
  // we're on a DLL-capable platform. 20020118 mortene.
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#ifdef SOQT_MAKE_DLL
  return SoQt::DLL;
#else
  return SoQt::LIB;
#endif
#endif
  // FIXME: this is rather lame, we have enough information in the
  // configure / build process to always know whether we're building
  // static or dynamic. 20020618 mortene.
  return SoQt::UNKNOWN;
}

#if 0 // FIXME: not in use, see larsa's FIXME below. 20020617 mortene.

// *************************************************************************
// These sanity checks are designed to detect common pitfall errors for
// Microsoft Windows linkage with SoQt and Coin.

// FIXME: use an "is-this-a-DLL-capable-platform" configure check
// and remove the system "#if defined" tests below. 20011203 mortene.
// FIXME: I disabled this because it wasn't inlined in the client app
// but compiled into the library by MSVC++ and with SOWIN_DLL undefined,
// the ABI test always tried the LIB_ABI path.  20020126 larsa
#if 0 && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#define SOQT_SANITY_CHECK(forward_call)                  \
  if (SoQt::isDebugLibrary() &&                       \
       SoDB::isInitialized())                          \
    SoDebugError::postWarning("SoQt::init",            \
      "unable to verify application linkage sanity "    \
      "because Open Inventor has already been "         \
      "initialized before SoQt::init call");           \
  SOQT_RUNTIME_SANITY_CHECK();                         \
  SOQT_LINKSTYLE_SANITY_CHECK();                       \
  forward_call;                                         \
  SOQT_LINKTIME_SANITY_CHECK()

#define SOQT_RUNTIME_SANITY_CHECK()                    \
  do {                                                  \
    if (!SoQt::isCompatible(SOQT_MAJOR_VERSION,      \
                            SOQT_MINOR_VERSION))      \
      SoQt::abort(SOQT_RUNTIME_MISMATCH);             \
  } while (FALSE)

#ifdef SOQT_DLL
#define SOQT_LINKSTYLE_SANITY_CHECK()                  \
  do {                                                  \
    if (SoQt::getABIType() != SOQT_DLL_ABI)         \
      SoQt::abort(SOQT_LINKSTYLE_MISMATCH);           \
  } while (FALSE)
#else
#define SOQT_LINKSTYLE_SANITY_CHECK()                  \
  do {                                                  \
    if (SoQt::getABIType() != SOQT_LIB_ABI)         \
      SoQt::abort(SOQT_LINKSTYLE_MISMATCH);           \
  } while (FALSE)
#endif

#define SOQT_LINKTIME_SANITY_CHECK()                   \
  do {                                                  \
    if (!SoDB::isInitialized())                       \
      SoQt::abort(SOQT_LINKTIME_MISMATCH);            \
  } while (FALSE)
#else /* ! MS Windows */
#define SOQT_SANITY_CHECK(forward_call)                \
  forward_call
#endif /* ! MS Windows */

#endif // OBSOLETED

#ifndef DOXYGEN_SKIP_THIS

// Abort the application due to some kind of mismatch in the ABI
// settings / configuration. This should hopefully help application
// programmers avoid shooting themselves in the foot by controlling
// certain run-time parameters in the client application versus what
// is expected by the SoQt library.
//
// If you're an application programmer, it is very likely that you
// only need to consider this an internal library method.
//
// This method was not part of the original SGI InventorXt library,
// but is an extension specific to the Coin project.
void
SoGuiP::abort(SoGuiP::ABIError error)
{
  switch (error) {
  case SoGuiP::LINKTIME_MISMATCH:
    SoQt::createSimpleErrorDialog(NULL, "Fatal Error",
                                     "Detected linktime mismatch error.");
    break;

  case SoGuiP::LINKSTYLE_MISMATCH:
    SoQt::createSimpleErrorDialog(NULL, "Fatal Error",
                                     "Detected linkstyle mismatch error (DLL vs. LIB).");
    break;

  case SoGuiP::RUNTIME_MISMATCH:
    SoQt::createSimpleErrorDialog(NULL, "Fatal Error",
                                     "Detected runtime mismatch error (versioning and ABI compatibility).");
    break;

  default:
    // FIXME: shouldn't this rather be an assert? 20020118 mortene.
    SoQt::createSimpleErrorDialog(NULL, "Fatal Error",
                                     "Unknown error in SoQt :(");
    break;
  }

  // FIXME: call fatal error handler in SoAny. 20020118 mortene.
  exit(-1);
}

#endif // DOXYGEN_SKIP_THIS

// *************************************************************************

/*!
  \fn void SoQt::createSimpleErrorDialog(QWidget * widget, const char * title, const char * string1, const char * string2)


  This is a convenient way for the application programmer to throw up
  an obtrusive application-global error dialog.

  If \a widget is \c NULL, the dialog will be modal for the whole
  application (all windows will be blocked for input). If not,
  only the window for the given \a widget will be blocked.

  \a title is the title of the dialog box. \a string1 and \a string2
  contains the text which will be shown in the dialog box.

  There will only be a single "Ok" button for the user to press and
  continue with the application.
*/

// *************************************************************************

// FIXME: Dummy implementation of sogui_atexit(). Replace with real
// implementation. kintel 20060209
void sogui_atexit(sogui_atexit_f * fp, int priority)
{
  // disabled this, as it is not safe to clean up SoQt after Coin
  // has been cleaned up. -mortene
  //
  // atexit(fp);
}
