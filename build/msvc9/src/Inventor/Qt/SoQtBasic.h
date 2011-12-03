/* src/Inventor/Qt/SoQtBasic.h.  Generated from - by configure.  */
#ifndef SOQT_BASIC_H
#define SOQT_BASIC_H

// NB: this is not a pure configure-input file, it's also a config header...

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

// *************************************************************************

/* Some useful inline template functions:
 *   SoQtMin(Val1, Val2)       - returns minimum value
 *   SoQtMax(Val1, Val2)       - returns maximum value
 *   SoQtClamp(Val, Min, Max)  - returns clamped value
 *   SoQtSwap(Val1, Val2)      - swaps the two values (no return value)
 */

template <class Type>
inline Type SoQtAbs(Type Val) {
  return (Val < 0) ? -Val : Val;
}

template <class Type>
inline Type SoQtMin(Type a, Type b) {
  return (b < a) ? b : a;
}

template <class Type>
inline Type SoQtMax(Type a, Type b) {
  return (b > a) ? b : a;
}

template <class Type>
inline Type SoQtClamp(Type val, Type min, Type max) {
  return SoQtMax(min, SoQtMin(max, val));
}

template <class Type>
inline void SoQtSwap(Type & a, Type & b) {
  Type t = a; a = b; b = t;
}

// *************************************************************************

#define __COIN_SOQT__

#if ! defined(SOQT_MAJOR_VERSION)
#define SOQT_MAJOR_VERSION 1
#endif /* ! SOQT_MAJOR_VERSION */
#if ! defined(SOQT_MINOR_VERSION)
#define SOQT_MINOR_VERSION 6
#endif /* ! SOQT_MINOR_VERSION */
#if ! defined(SOQT_MICRO_VERSION)
#define SOQT_MICRO_VERSION 0
#endif /* ! SOQT_MICRO_VERSION */
#if ! defined(SOQT_BETA_VERSION)
#define SOQT_BETA_VERSION a
#endif /* ! SOQT_BETA_VERSION */
#if ! defined(SOQT_VERSION)
#define SOQT_VERSION "1.6.0a"
#endif /* ! SOQT_VERSION */

// *************************************************************************

/* Precaution to avoid an error easily made by the application programmer. */
#ifdef SOQT_DLL_API
# error Leave the internal SOQT_DLL_API define alone.
#endif /* SOQT_DLL_API */

/*
  On MSWindows platforms, one of these defines must always be set when
  building application programs:

   - "SOQT_DLL", when the application programmer is using the
     library in the form of a dynamic link library (DLL)

   - "SOQT_NOT_DLL", when the application programmer is using the
     library in the form of a static object library (LIB)

  Note that either SOQT_DLL or SOQT_NOT_DLL _must_ be defined by
  the application programmer on MSWindows platforms, or else the
  #error statement will hit. Set up one or the other of these two
  defines in your compiler environment according to how the library
  was built -- as a DLL (use "SOQT_DLL") or as a LIB (use
  "SOQT_NOT_DLL").

  (Setting up defines for the compiler is typically done by either
  adding something like "/DSOQT_DLL" to the compiler's argument
  line (for command-line build processes), or by adding the define to
  the list of preprocessor symbols in your IDE GUI (in the MSVC IDE,
  this is done from the "Project"->"Settings" menu, choose the "C/C++"
  tab, then "Preprocessor" from the dropdown box and add the
  appropriate define)).

  It is extremely important that the application programmer uses the
  correct define, as using "SOQT_NOT_DLL" when "SOQT_DLL" is
  correct is likely to cause mysterious crashes.
 */
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
# ifdef SOQT_INTERNAL
#  ifdef SOQT_MAKE_DLL
#   define SOQT_DLL_API __declspec(dllexport)
#  endif /* SOQT_MAKE_DLL */
# else /* !SOQT_INTERNAL */
#  ifdef SOQT_DLL
#   define SOQT_DLL_API __declspec(dllimport)
#  else /* !SOQT_DLL */
#   ifndef SOQT_NOT_DLL
#    error Define either SOQT_DLL or SOQT_NOT_DLL as appropriate for your linkage! See Inventor/Qt/SoQtBasic.h for further instructions.
#   endif /* SOQT_NOT_DLL */
#  endif /* !SOQT_DLL */
# endif /* !SOQT_MAKE_DLL */
#endif /* Microsoft Windows */

/* Empty define to avoid errors when _not_ compiling an MSWindows DLL. */
#ifndef SOQT_DLL_API
# define SOQT_DLL_API
#endif /* !SOQT_DLL_API */

#ifndef GUI_TOOLKIT_VERSION
#define GUI_TOOLKIT_VERSION "450"
#endif /* GUI_TOOLKIT_VERSION */

#endif // ! SOQT_BASIC_H
