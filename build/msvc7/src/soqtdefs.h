#ifndef SOQT_INTERNALDEFS_H
#define SOQT_INTERNALDEFS_H

// src/soqtdefs.h.  Generated from soguidefs.h.in by configure.

/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
