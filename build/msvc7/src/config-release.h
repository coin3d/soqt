/* src/config.h.  Generated from config.h.in by configure.  */
/* src/config.h.in.  Generated from configure.ac by autoheader.  */


#ifndef SOQT_INTERNAL
#error this is a private header file
#endif


/* Open Inventor extensions */
#define COIN_IV_EXTENSIONS 

/* Version string for Qt */
#define GUI_TOOLKIT_VERSION "450"

/* The CPP compiler has a variable containing the current function name */
#define HAVE_CPP_COMPILER_FUNCTION_NAME_VAR __FUNCTION__

/* The C compiler has a variable containing the current function name */
#define HAVE_C_COMPILER_FUNCTION_NAME_VAR __FUNCTION__

/* Define to 1 if you have the <dlfcn.h> header file. */
/* #undef HAVE_DLFCN_H */

/* Define to use GetEnvironmentVariable() instead of getenv() */
#define HAVE_GETENVIRONMENTVARIABLE 1

/* define if you have GLX X11 OpenGL bindings */
/* #undef HAVE_GLX */

/* define if the GLU header should be included as GL/glu.h */
/* #undef HAVE_GL_GLU_H */

/* define if the GL header should be included as GL/gl.h */
#define HAVE_GL_GL_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
/* #undef HAVE_INTTYPES_H */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <netinet/in.h> header file. */
/* #undef HAVE_NETINET_IN_H */

/* define if the GLU header should be included as OpenGL/glu.h */
/* #undef HAVE_OPENGL_GLU_H */

/* define if the GL header should be included as OpenGL/gl.h */
/* #undef HAVE_OPENGL_GL_H */

/* define if pthread's struct timespec uses nsecs and not usecs */
/* #undef HAVE_PTHREAD_TIMESPEC_NSEC */

/* Define to enable use of Inventor feature */
#define HAVE_SBIMAGE_ADDREADIMAGECB 1

/* Define to enable use of Inventor feature */
#define HAVE_SOCAMERA_SETSTEREOMODE 1

/* Define to enable use of Inventor feature */
#define HAVE_SOCONTEXTHANDLER 1

/* Define to enable use of Inventor feature */
#define HAVE_SOKEYBOARDEVENT_DELETE 1

/* Define to enable use of Inventor feature */
#define HAVE_SOMOUSEBUTTONEVENT_BUTTON5 1

/* Define to enable use of the Open Inventor SoPolygonOffset node */
#define HAVE_SOPOLYGONOFFSET 1

/* Define to enable use of Inventor feature */
#define HAVE_SORTED_LAYERS_BLEND 1

/* Define to enable use of the Open Inventor SoVRMLBackground VRML node */
#define HAVE_SOVRMLBACKGROUND 1

/* Define to enable use of the Open Inventor SoVRMLFog VRML node */
#define HAVE_SOVRMLFOG 1

/* Define to enable use of the Open Inventor SoVRMLMaterial VRML node */
#define HAVE_SOVRMLMATERIAL 1

/* Define to enable use of the Open Inventor SoVRMLViewpoint VRML node */
#define HAVE_SOVRMLVIEWPOINT 1

/* Define to 1 if you have the <stdint.h> header file. */
/* #undef HAVE_STDINT_H */

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
/* #undef HAVE_STRINGS_H */

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
/* #undef HAVE_SYS_TIME_H */

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <tlhelp32.h> header file. */
#define HAVE_TLHELP32_H 1

/* Define to 1 if you have the <unistd.h> header file. */
/* #undef HAVE_UNISTD_H */

/* Define if the Win32 API is available */
#define HAVE_WIN32_API 1

/* Define to use Win32 LoadLibrary() */
#define HAVE_WIN32_LOADLIBRARY 1

/* Define to 1 if you have the <windows.h> header file. */
#define HAVE_WINDOWS_H 1

/* define if it is possible to build against X11 */
/* #undef HAVE_X11_AVAILABLE */

/* Define to 1 if you have the <X11/extensions/SGIMisc.h> header file. */
/* #undef HAVE_X11_EXTENSIONS_SGIMISC_H */

/* Define to 1 if you have the <X11/extensions/XInput.h> header file. */
/* #undef HAVE_X11_EXTENSIONS_XINPUT_H */

/* Define to 1 if you have the <X11/Xproto.h> header file. */
/* #undef HAVE_X11_XPROTO_H */

/* Name of package */
#define PACKAGE "SoQt"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "coin-support@coin3d.org"

/* Define to the full name of this package. */
#define PACKAGE_NAME "SoQt"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "SoQt 1.6.0a"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "soqt"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.6.0a"

/* define this to the SoQt beta version letter */
#define SOQT_BETA_VERSION a

/* Define to the major version of SoQt */
#define SOQT_MAJOR_VERSION 1

/* Define to the micro version of SoQt */
#define SOQT_MICRO_VERSION 0

/* Define to the minor version of SoQt */
#define SOQT_MINOR_VERSION 6

/* Version string for SoQt */
#define SOQT_VERSION "1.6.0a"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to make Coin use/catch exceptions at some particular places. */
#define USE_EXCEPTIONS 1

/* Version number of package */
#define VERSION "1.6.0a"

/* Define this if you want defaults to be linked into SoXt */
#define WITH_STATIC_DEFAULTS /**/

/* Define to 1 if the X Window System is missing or not being used. */
/* #undef X_DISPLAY_MISSING */
