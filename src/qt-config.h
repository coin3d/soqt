#ifndef COIN_QTCONFIG_H
#define COIN_QTCONFIG_H

#ifndef SOQT_INTERNAL
#error this is a private header file
#endif /* !SOQT_INTERNAL */

/*
 * This header file is intended to describe differences in features
 * between various Qt versions in symbolic terms, so conditional code
 * can compile correctly, depending on which Qt version is used,
 * without the coder having to remember specific Qt versions while
 * writing code.
 *
 * This is a step back from using Autoconf for detecting these things
 * (which is what we did earlier), but has become necessary since we
 * deliver pre-generated config-files to be able to support the Visual
 * Studio C++ IDE in a decent way.
 *
 * NOTE: This header file is in its infancy, so it is unlikely that
 * the current versioning-granularity is correct and will work.
 * Give us feedback about how you needed to tweak this header file,
 * what platform it was for, and which version of Qt you use, and this
 * should be fixed over time...
 */

/* must be defined before including qglobal.h to get
   QT3_SUPPORT_CONSTRUCTOR and QT3_SUPPORT_VARIABLE defined */
/* FIXME: get rid of this define. We should fix up the compile issues
   wrt Qt 4 properly. 20050629 mortene. */
#define QT3_SUPPORT

#include <qglobal.h> /* QT_VERSION */

#if (QT_VERSION < 200)
#error your Qt version is way too old
#endif /* QT_VERSION < 200 */

/* FIXME: we will most likely need to access platform information
   defines in this header. */

// *************************************************************************

#if (QT_VERSION >= 0x040000) /* Qt 4.* - known to work with 4.0.1 */

/* Define this if QCoreApplication::hasPendingEvents() is available */
#define HAVE_QAPPLICATION_HASPENDINGEVENTS 1

/* Define this to 1 if operator==(QGLFormat&, QGLFormat&) is available */
#define HAVE_QGLFORMAT_EQ_OP 1

/* Define this to 1 if QGLFormat::setOverlay() is available */
#define HAVE_QGLFORMAT_SETOVERLAY 1

/* Define this to 1 if QGLWidget::setAutoBufferSwap() is available */
#define HAVE_QGLWIDGET_SETAUTOBUFFERSWAP 1

/* Define to 1 if you have the <qstylefactory.h> header file. */
/** QStyleFactory was added in Qt 3.0. */
#define HAVE_QSTYLEFACTORY_H 1

/* Define this if Qt::Keypad is available */
/* #undef HAVE_QT_KEYPAD_DEFINE */

/* Defined if qt_win_use_simple_timers is available */
/** We've had an external report about soqt.dll link failing due to
  missing the qt_win_use_simple_timers symbol in the installed Qt
  library. This was with Qt 3.3.1 MT under Windows. **/
/* #undef HAVE_QT_WIN_USE_SIMPLE_TIMERS */

/* Define this if QWidget::setWindowState() is available */
#define HAVE_QWIDGET_SETWINDOWSTATE 1

/* Define this if QWidget::showFullScreen() is available */
#define HAVE_QWIDGET_SHOWFULLSCREEN 1

/* ********************************************************************** */

#else
#if (QT_VERSION >= 0x030000) /* Qt 3.* - known to work with 3.3.1 */

/* Define this if QApplication::hasPendingEvents() is available */
#define HAVE_QAPPLICATION_HASPENDINGEVENTS 1

/* Define this to 1 if operator==(QGLFormat&, QGLFormat&) is available */
#define HAVE_QGLFORMAT_EQ_OP 1

/* Define this to 1 if QGLFormat::setOverlay() is available */
#define HAVE_QGLFORMAT_SETOVERLAY 1

/* Define this to 1 if QGLWidget::setAutoBufferSwap() is available */
#define HAVE_QGLWIDGET_SETAUTOBUFFERSWAP 1

/* Define to 1 if you have the <qstylefactory.h> header file. */
/** QStyleFactory was added in Qt 3.0. **/
#define HAVE_QSTYLEFACTORY_H 1

/* Define this if Qt::Keypad is available */
#define HAVE_QT_KEYPAD_DEFINE 1

/* Defined if qt_win_use_simple_timers is available */
/** We've had an external report about soqt.dll link failing due to
  missing the qt_win_use_simple_timers symbol in the installed Qt
  library. This was with Qt 3.3.1 MT under Windows. **/
#if (QT_VERSION == 0x030301) && defined(_MSC_VER)
#define HAVE_QT_WIN_USE_SIMPLE_TIMERS 1
#else
/* #undef HAVE_QT_WIN_USE_SIMPLE_TIMERS */
#endif

#if (QT_VERSION <= 0x030102) /*  known to be missing from Qt 3.1.2 */
/* #undef HAVE_QWIDGET_SETWINDOWSTATE */
#else /* QT_VERSION > 0x030102 (i.e. 3.1.2) */
/* Define this if QWidget::setWindowState() is available */
#define HAVE_QWIDGET_SETWINDOWSTATE 1
#endif

/* Define this if QWidget::showFullScreen() is available */
#define HAVE_QWIDGET_SHOWFULLSCREEN 1

/* ********************************************************************** */

#else
#if (QT_VERSION >= 200) /* Qt 2.* */

#error The SoQt developers have not had the chance to try Qt 2 compatibility for a while, and have not updated qt-config.h to supoprt Qt 2. You can proceed on your own by removing this error and duplicating the above define settings, toggling them the correct way. If you succeed, notify coin-support@coin3d.org and we will include your setup in the distribution.

#endif /* Qt 2.* */
#endif /* Qt 3.* (else clause) */
#endif /* Qt 4.* (else clause) */

#endif /* !COIN_QTCONFIG_H */
