#ifndef SOQT_INTERNALDEFS_H
#define SOQT_INTERNALDEFS_H

// src/soqtdefs.h.  Generated from soguidefs.h.in by configure.

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

/* ********************************************************************** */

#ifndef SOQT_INTERNAL
#error this is a private header file
#endif /* !SOQT_INTERNAL */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

/* ********************************************************************** */

#ifdef __FILE__
#define SOQT_STUB_FILE __FILE__
#else
/* FIXME: avoid this case by redefining the compilation rules to define the
   current filename in some variable.  [20010919 larsa] */
#define SOQT_STUB_FILE ((char *)0L)
#endif

#ifdef __LINE__
#define SOQT_STUB_LINE __LINE__
#else
#define SOQT_STUB_LINE 0
#endif

#ifdef __cplusplus
#ifdef HAVE_CPP_COMPILER_FUNCTION_NAME_VAR
#define SOQT_STUB_FUNC HAVE_CPP_COMPILER_FUNCTION_NAME_VAR
#else
#define SOQT_STUB_FUNC ((const char *)0L)
#endif
#else /* !__cplusplus */
#ifdef HAVE_C_COMPILER_FUNCTION_NAME_VAR
#define SOQT_STUB_FUNC HAVE_C_COMPILER_FUNCTION_NAME_VAR
#else
#define SOQT_STUB_FUNC ((const char *)0L)
#endif
#endif /* !__cplusplus */

#if SOQT_DEBUG

#include <Inventor/errors/SoDebugError.h>

/*
  This stupid thing is here to silence some compilers that complain on
  constant if-expressions.
*/

inline int soqt_not_null(const void * arg) { return (arg != NULL) ? 1 : 0; }


/* Collects common code from SOQT_STUB(), SOQT_STUB()_ONCE and
   SOQT_OBSOLETED(). */

#define SOQT_FUNCTIONIDENTIFIER(SOQTSTR) \
    SbString SOQTSTR(soqt_not_null(SOQT_STUB_FILE) ? SOQT_STUB_FILE : ""); \
    if (SOQTSTR.getLength() > 0) { SOQTSTR += ':'; } \
    SOQTSTR += SbString((int)SOQT_STUB_LINE); SOQTSTR += ':'; \
    SOQTSTR += soqt_not_null(SOQT_STUB_FUNC) ? SOQT_STUB_FUNC : ""

/*
  SOQT_STUB(): a macro that prints out stub information.
  Used where there is functionality missing.
*/

#define SOQT_STUB() \
  do { \
    SOQT_FUNCTIONIDENTIFIER(s); \
    SoDebugError::postWarning(s.getString(), \
                              "STUB: functionality not yet completed"); \
  } while (0)

/*
  SOQT_STUB_ONCE(): a macro that prints out stub information, but only on
  the first pass.  Used where there is functionality missing that may be
  called hundreds of times.
*/

#define SOQT_STUB_ONCE() \
  do { \
    static int first = 1; \
    if (first) { \
      SOQT_FUNCTIONIDENTIFIER(s); \
      SoDebugError::postWarning(s.getString(), \
                                "STUB: functionality not yet completed " \
                                "(first and last warning)"); \
      first = 0; \
    } \
  } while (0)

/*
  SOQT_OBSOLETED(): a macro that prints out information about an obsoleted
  function still being in use.
*/

#define SOQT_OBSOLETED() \
  do { \
    SOQT_FUNCTIONIDENTIFIER(s); \
    SoDebugError::post(s.getString(), \
                       "OBSOLETED: functionality no longer supported"); \
  } while (0)

#else /* !SOQT_DEBUG */

/* snub the stubs */
#define SOQT_STUB()      do { } while (0)
#define SOQT_STUB_ONCE() do { } while (0)
#define SOQT_OBSOLETED() do { } while (0)

#endif /* !SOQT_DEBUG */

/*
  GETTEXT support
*/

#if defined(ENABLE_NLS) && defined(HAVE_GETTEXT)
#include <libintl.h>
#define _(String) dgettext (PACKAGE, String)
#define N_(String) (String)
#else
#define _(String) (String)
#define N_(String) (String)
#endif /* HAVE_GETTEXT && ENABLE_NLS */

/* ********************************************************************** */

#endif /* ! SOQT_INTERNALDEFS_H */
