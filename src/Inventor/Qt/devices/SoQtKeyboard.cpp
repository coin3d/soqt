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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H
#include <qt-config.h>

#include <qevent.h>
#include <qnamespace.h>

#include <Inventor/SbDict.h>
#include <Inventor/errors/SoDebugError.h>
#include <Inventor/events/SoKeyboardEvent.h>

#include <Inventor/Qt/devices/SoGuiKeyboardP.h>
#include <Inventor/Qt/devices/SoQtKeyboard.h>

// *************************************************************************

#if defined(Q_WS_MAC) || (defined(__APPLE__) && defined(Q_WS_X11))
#define QT_ON_MAC 1
#endif

/*
  The Qt::Keypad define was not added in Qt until version 2.2.0.

  We still want to use it when building against earlier versions, as
  SoQt would then be able to still work properly in this regard when
  built against earlier Qt 2-versions, while run on later Qt
  2-versions.

  (To keep ABI compatibility, it had to be the same for all 2.x.y
  releases.)
*/
#if (QT_VERSION >= 0x030000)
#define QT_KEYPAD_MASK Qt::Keypad
#else // Qt ver < 3.0.0
#define QT_KEYPAD_MASK 0x4000
#endif // Qt ver < 3.0.0

// *************************************************************************

class SoQtKeyboardP : public SoGuiKeyboardP {
public:
  struct key1map {
    int from;                // Qt val
    SoKeyboardEvent::Key to; // So val
    char printable;
  };

  static struct key1map QtToSoMapping[];
  static struct key1map QtToSoMapping_kp[];
  static SbDict * translatetable;
  static SbDict * kp_translatetable;
};

struct SoQtKeyboardP::key1map SoQtKeyboardP::QtToSoMapping[] = {
  {Qt::Key_Escape, SoKeyboardEvent::ESCAPE, '.'},
  {Qt::Key_Tab, SoKeyboardEvent::TAB, '.'},
  {Qt::Key_Backspace, SoKeyboardEvent::BACKSPACE, '.'},
  {Qt::Key_Return, SoKeyboardEvent::RETURN, '.'},
  {Qt::Key_Enter, SoKeyboardEvent::ENTER, '.'},
  {Qt::Key_Insert, SoKeyboardEvent::INSERT, '.'},
#ifdef HAVE_SOKEYBOARDEVENT_DELETE
  {Qt::Key_Delete, SoKeyboardEvent::DELETE, '.'},
#else
  {Qt::Key_Delete, SoKeyboardEvent::KEY_DELETE, '.'},
#endif
  {Qt::Key_Pause, SoKeyboardEvent::PAUSE, '.'},
  {Qt::Key_Print, SoKeyboardEvent::PRINT, '.'},
  {Qt::Key_Home, SoKeyboardEvent::HOME, '.'},
  {Qt::Key_End, SoKeyboardEvent::END, '.'},
  {Qt::Key_Left, SoKeyboardEvent::LEFT_ARROW, '.'},
  {Qt::Key_Up, SoKeyboardEvent::UP_ARROW, '.'},
  {Qt::Key_Right, SoKeyboardEvent::RIGHT_ARROW, '.'},
  {Qt::Key_Down, SoKeyboardEvent::DOWN_ARROW, '.'},
  {Qt::Key_PageUp, SoKeyboardEvent::PRIOR, '.'},
  {Qt::Key_PageUp, SoKeyboardEvent::PAGE_UP, '.'},
  {Qt::Key_PageDown, SoKeyboardEvent::NEXT, '.'},
  {Qt::Key_PageDown, SoKeyboardEvent::PAGE_DOWN, '.'},

  {Qt::Key_Shift, SoKeyboardEvent::LEFT_SHIFT, '.'},
  {Qt::Key_Control, SoKeyboardEvent::LEFT_CONTROL, '.'},
#if !(defined QT_ON_MAC && QT_VERSION >= 0x030100)
// Since Qt/Mac 3.1.x, the "ctrl" key is mapped to Qt::MetaButton (not
// Qt::ControlButton) => We must not handle META as ALT on Mac OS X.
  {Qt::Key_Meta, SoKeyboardEvent::LEFT_ALT, '.'},
#endif
  {Qt::Key_Alt, SoKeyboardEvent::LEFT_ALT, '.'},
  {Qt::Key_CapsLock, SoKeyboardEvent::CAPS_LOCK, '.'},
  {Qt::Key_NumLock, SoKeyboardEvent::NUM_LOCK, '.'},
  {Qt::Key_ScrollLock, SoKeyboardEvent::SCROLL_LOCK, '.'},

  {Qt::Key_F1, SoKeyboardEvent::F1, '.'},
  {Qt::Key_F2, SoKeyboardEvent::F2, '.'},
  {Qt::Key_F3, SoKeyboardEvent::F3, '.'},
  {Qt::Key_F4, SoKeyboardEvent::F4, '.'},
  {Qt::Key_F5, SoKeyboardEvent::F5, '.'},
  {Qt::Key_F6, SoKeyboardEvent::F6, '.'},
  {Qt::Key_F7, SoKeyboardEvent::F7, '.'},
  {Qt::Key_F8, SoKeyboardEvent::F8, '.'},
  {Qt::Key_F9, SoKeyboardEvent::F9, '.'},
  {Qt::Key_F10, SoKeyboardEvent::F10, '.'},
  {Qt::Key_F11, SoKeyboardEvent::F11, '.'},
  {Qt::Key_F12, SoKeyboardEvent::F12, '.'},
  {Qt::Key_Space, SoKeyboardEvent::SPACE, ' '},
  {Qt::Key_Exclam, SoKeyboardEvent::NUMBER_1, '!'},
  {Qt::Key_QuoteDbl, SoKeyboardEvent::APOSTROPHE, '\"'},
  {Qt::Key_NumberSign, SoKeyboardEvent::NUMBER_3, '#'},
  {Qt::Key_Dollar, SoKeyboardEvent::NUMBER_4, '$'},
  {Qt::Key_Percent, SoKeyboardEvent::NUMBER_5, '%'},
  {Qt::Key_Ampersand, SoKeyboardEvent::NUMBER_6, '^'},
  {Qt::Key_Apostrophe, SoKeyboardEvent::APOSTROPHE, '\''},
  {Qt::Key_ParenLeft, SoKeyboardEvent::NUMBER_9, '('},
  {Qt::Key_ParenRight, SoKeyboardEvent::NUMBER_0, ')'},
  {Qt::Key_Asterisk, SoKeyboardEvent::NUMBER_8, '*'},
  {Qt::Key_Plus, SoKeyboardEvent::EQUAL, '+'},
  {Qt::Key_Comma, SoKeyboardEvent::COMMA, ','},
  {Qt::Key_Minus, SoKeyboardEvent::MINUS, '-'},
  {Qt::Key_Period, SoKeyboardEvent::PERIOD, '.'},
  {Qt::Key_Slash, SoKeyboardEvent::SLASH, '/'},
  {Qt::Key_0, SoKeyboardEvent::NUMBER_0, '0'},
  {Qt::Key_1, SoKeyboardEvent::NUMBER_1, '1'},
  {Qt::Key_2, SoKeyboardEvent::NUMBER_2, '2'},
  {Qt::Key_3, SoKeyboardEvent::NUMBER_3, '3'},
  {Qt::Key_4, SoKeyboardEvent::NUMBER_4, '4'},
  {Qt::Key_5, SoKeyboardEvent::NUMBER_5, '5'},
  {Qt::Key_6, SoKeyboardEvent::NUMBER_6, '6'},
  {Qt::Key_7, SoKeyboardEvent::NUMBER_7, '7'},
  {Qt::Key_8, SoKeyboardEvent::NUMBER_8, '8'},
  {Qt::Key_9, SoKeyboardEvent::NUMBER_9, '9'},
  {Qt::Key_Colon, SoKeyboardEvent::SEMICOLON, ':'},
  {Qt::Key_Semicolon, SoKeyboardEvent::SEMICOLON, ';'},
  {Qt::Key_Less, SoKeyboardEvent::COMMA, '<'},
  {Qt::Key_Equal, SoKeyboardEvent::EQUAL, '='},
  {Qt::Key_Greater, SoKeyboardEvent::PERIOD, '>'},
  {Qt::Key_Question, SoKeyboardEvent::BACKSLASH, '?'},
  {Qt::Key_At, SoKeyboardEvent::NUMBER_2, '@'},

  // zero means let SoKeyboardEvent handle the printable character
  {Qt::Key_A, SoKeyboardEvent::A, 0},
  {Qt::Key_B, SoKeyboardEvent::B, 0},
  {Qt::Key_C, SoKeyboardEvent::C, 0},
  {Qt::Key_D, SoKeyboardEvent::D, 0},
  {Qt::Key_E, SoKeyboardEvent::E, 0},
  {Qt::Key_F, SoKeyboardEvent::F, 0},
  {Qt::Key_G, SoKeyboardEvent::G, 0},
  {Qt::Key_H, SoKeyboardEvent::H, 0},
  {Qt::Key_I, SoKeyboardEvent::I, 0},
  {Qt::Key_J, SoKeyboardEvent::J, 0},
  {Qt::Key_K, SoKeyboardEvent::K, 0},
  {Qt::Key_L, SoKeyboardEvent::L, 0},
  {Qt::Key_M, SoKeyboardEvent::M, 0},
  {Qt::Key_N, SoKeyboardEvent::N, 0},
  {Qt::Key_O, SoKeyboardEvent::O, 0},
  {Qt::Key_P, SoKeyboardEvent::P, 0},
  {Qt::Key_Q, SoKeyboardEvent::Q, 0},
  {Qt::Key_R, SoKeyboardEvent::R, 0},
  {Qt::Key_S, SoKeyboardEvent::S, 0},
  {Qt::Key_T, SoKeyboardEvent::T, 0},
  {Qt::Key_U, SoKeyboardEvent::U, 0},
  {Qt::Key_V, SoKeyboardEvent::V, 0},
  {Qt::Key_W, SoKeyboardEvent::W, 0},
  {Qt::Key_X, SoKeyboardEvent::X, 0},
  {Qt::Key_Y, SoKeyboardEvent::Y, 0},
  {Qt::Key_Z, SoKeyboardEvent::Z, 0},
  {Qt::Key_BracketLeft, SoKeyboardEvent::BRACKETLEFT, '['},
  {Qt::Key_Backslash, SoKeyboardEvent::BACKSLASH, '\\'},
  {Qt::Key_BracketRight, SoKeyboardEvent::BRACKETRIGHT, ']'},
  {Qt::Key_AsciiCircum, SoKeyboardEvent::NUMBER_7, '&'},
  {Qt::Key_Underscore, SoKeyboardEvent::MINUS, '_'},
  {Qt::Key_BraceLeft, SoKeyboardEvent::BRACKETLEFT, '{'},
  {Qt::Key_Bar, SoKeyboardEvent::BACKSLASH, '|'},
  {Qt::Key_BraceRight, SoKeyboardEvent::BRACKETRIGHT, '}'},
  {Qt::Key_AsciiTilde, SoKeyboardEvent::GRAVE, '~'},
  {Qt::Key_unknown, SoKeyboardEvent::ANY, 0}
};

struct SoQtKeyboardP::key1map SoQtKeyboardP::QtToSoMapping_kp[] = {
  {Qt::Key_Home, SoKeyboardEvent::PAD_7, '.'},
  {Qt::Key_End, SoKeyboardEvent::PAD_1, '.'},
  {Qt::Key_Left, SoKeyboardEvent::PAD_4, '.'},
  {Qt::Key_Up, SoKeyboardEvent::PAD_8, '.'},
  {Qt::Key_Right, SoKeyboardEvent::PAD_6, '.'},
  {Qt::Key_Down, SoKeyboardEvent::PAD_2, '.'},
  {Qt::Key_PageUp, SoKeyboardEvent::PAD_9, '.'},
  {Qt::Key_PageDown, SoKeyboardEvent::PAD_3, '.'},
  {Qt::Key_Enter, SoKeyboardEvent::PAD_ENTER, '.'},
  {Qt::Key_Delete, SoKeyboardEvent::PAD_DELETE, '.'},
  {Qt::Key_Insert, SoKeyboardEvent::PAD_INSERT, '.'},
  {Qt::Key_Plus, SoKeyboardEvent::PAD_ADD, '+'},
  {Qt::Key_Minus, SoKeyboardEvent::PAD_SUBTRACT, '-'},
  {Qt::Key_Period, SoKeyboardEvent::PAD_PERIOD, '.'},
  {Qt::Key_Asterisk, SoKeyboardEvent::PAD_MULTIPLY, '*'},
  {Qt::Key_Slash, SoKeyboardEvent::PAD_DIVIDE, '/'},
  {Qt::Key_Space, SoKeyboardEvent::PAD_SPACE, ' '},
  {Qt::Key_Tab, SoKeyboardEvent::PAD_TAB, '.'},
  {Qt::Key_F1, SoKeyboardEvent::PAD_F1, '.'},
  {Qt::Key_F2, SoKeyboardEvent::PAD_F2, '.'},
  {Qt::Key_F3, SoKeyboardEvent::PAD_F3, '.'},
  {Qt::Key_F4, SoKeyboardEvent::PAD_F4, '.'},
  {Qt::Key_0, SoKeyboardEvent::PAD_0, '0'},
  {Qt::Key_1, SoKeyboardEvent::PAD_1, '1'},
  {Qt::Key_2, SoKeyboardEvent::PAD_2, '2'},
  {Qt::Key_3, SoKeyboardEvent::PAD_3, '3'},
  {Qt::Key_4, SoKeyboardEvent::PAD_4, '4'},
  {Qt::Key_5, SoKeyboardEvent::PAD_5, '5'},
  {Qt::Key_6, SoKeyboardEvent::PAD_6, '6'},
  {Qt::Key_7, SoKeyboardEvent::PAD_7, '7'},
  {Qt::Key_8, SoKeyboardEvent::PAD_8, '8'},
  {Qt::Key_9, SoKeyboardEvent::PAD_9, '9'},
  {Qt::Key_unknown, SoKeyboardEvent::ANY, 0} // Ends table
};

SbDict * SoQtKeyboardP::translatetable = NULL;
SbDict * SoQtKeyboardP::kp_translatetable = NULL;

#define PRIVATE(obj) ((obj)->pimpl)
#define PUBLIC(obj) ((obj)->pub)

// *************************************************************************

static void
soqtkeyboard_cleanup(void)
{
  delete SoQtKeyboardP::translatetable;
  SoQtKeyboardP::translatetable = NULL;
  delete SoQtKeyboardP::kp_translatetable;
  SoQtKeyboardP::kp_translatetable = NULL;
}

// *************************************************************************

SoQtKeyboard::SoQtKeyboard(int mask)
{
  PRIVATE(this) = new SoQtKeyboardP;
  PRIVATE(this)->eventmask = mask;
}

SoQtKeyboard::~SoQtKeyboard()
{
  delete PRIVATE(this);
}

// *************************************************************************

void
SoQtKeyboard::enable(QWidget * widget, SoQtEventHandler * handler, void * closure)
{
  // FIXME: should add some magic here so Qt events are actually
  // enabled or disabled for the widget in question. 20020625 mortene.
}

void
SoQtKeyboard::disable(QWidget * widget, SoQtEventHandler * handler, void * closure)
{
  // FIXME: should add some magic here so Qt events are actually
  // enabled or disabled for the widget in question. 20020625 mortene.
}

// *************************************************************************

static void
make_translation_table(void)
{
  assert(SoQtKeyboardP::translatetable == NULL);
  SoQtKeyboardP::translatetable = new SbDict;
  SoQtKeyboardP::kp_translatetable = new SbDict;

  int i = 0;
  while (SoQtKeyboardP::QtToSoMapping[i].from != Qt::Key_unknown) {
    SoQtKeyboardP::translatetable->enter((unsigned long)SoQtKeyboardP::QtToSoMapping[i].from,
                                         (void *)&SoQtKeyboardP::QtToSoMapping[i]);
    i++;
  }

  i = 0;
  while (SoQtKeyboardP::QtToSoMapping_kp[i].from != Qt::Key_unknown) {
    SoQtKeyboardP::kp_translatetable->enter((unsigned long)SoQtKeyboardP::QtToSoMapping_kp[i].from,
                                            (void *)&SoQtKeyboardP::QtToSoMapping_kp[i]);
    i++;
  }
}

// *************************************************************************

const SoEvent *
SoQtKeyboard::translateEvent(QEvent * event)
{
  static SbBool verchk = FALSE;
  if (!verchk) {
    verchk = TRUE;
    // Qt v3.0.1 (at least) has a bug where the sequence SHIFT-PRESS +
    // CTRL-PRESS + CTRL-RELEASE results in that last key-event coming
    // out completely wrong under X11: as a press of key 0x1059
    // (Key_Direction_L). Known to be fixed in 3.0.3, unknown status
    // in 3.0.2 (so we warn anyway).
    //
    // For reference, here's a complete, minimal example which can be
    // used to demonstrate the bug:
    //
    // ---8<--- [snip] ------8<--- [snip] ------8<--- [snip] ---
    // #include <qapplication.h>
    //
    // class MyWidget : public QWidget {
    // public:
    //   MyWidget(void) : QWidget() {
    //     this->installEventFilter(this);
    //   }
    //
    //   bool eventFilter(QObject * obj, QEvent * e) {
    //     if ((e->type() == QEvent::KeyPress) || (e->type() == QEvent::KeyRelease)) {
    //       QKeyEvent * ke = (QKeyEvent *)e;
    //       printf("key %s: 0x%x  (\"%s\")\n",
    //              e->type() == QEvent::KeyPress ? "press" : "release",
    //              ke->key(),
    //              ke->text().latin1());
    //       ke->accept();
    //       return TRUE;
    //     }
    //   }
    // };
    //
    // int
    // main(int argc, char ** argv)
    // {
    //   QApplication app(argc, argv);
    //
    //   MyWidget * mw = new MyWidget();
    //   mw->show();
    //
    //   return app.exec();
    // }
    // ---8<--- [snip] ------8<--- [snip] ------8<--- [snip] ---
    //
    // 20020521 mortene.
    SbString s = qVersion();
#ifdef Q_WS_X11
    if (s == "3.0.0" || s == "3.0.1" || s == "3.0.2") {
      SoDebugError::postWarning("SoQtKeyboard::translateEvent",
                                "You are using Qt version %s, which is "
                                "known to contain keyboard handling bugs "
                                "under X11. Please upgrade.",
                                s.getString());
    }
#endif // Q_WS_X11
  }

  SbBool keypress = event->type() == QEvent::KeyPress;
  SbBool keyrelease = event->type() == QEvent::KeyRelease;

  SbBool keyevent = keypress || keyrelease;

  if (keyevent && (PRIVATE(this)->eventmask & (KEY_PRESS|KEY_RELEASE))) {

    if (!SoQtKeyboardP::translatetable) make_translation_table();

    QKeyEvent * keyevent = (QKeyEvent *)event;
    int key = keyevent->key();
    // Key code / sequence unknown to Qt.
    if (key == 0) return NULL;

    // Allocate system-neutral event object once and reuse.
    if (!PRIVATE(this)->kbdevent) PRIVATE(this)->kbdevent = new SoKeyboardEvent;

    // FIXME: check for Qt::Key_unknown. 19990212 mortene.
#if QT_VERSION >= 0x040000
    SbBool keypad = (keyevent->modifiers() & Qt::KeypadModifier) != 0;
#else
    SbBool keypad = (keyevent->state() & QT_KEYPAD_MASK) != 0;
#endif

    // Translate keycode Qt -> So
    void * table;
    if (keypad && SoQtKeyboardP::kp_translatetable->find(key, table)) {
      struct SoQtKeyboardP::key1map * map = (struct SoQtKeyboardP::key1map *)table;
      PRIVATE(this)->kbdevent->setKey(map->to);
#if 0 // disabled. Breaks build when compiling against OIV
      if (map->printable) PRIVATE(this)->kbdevent->setPrintableCharacter(map->printable);
#endif // disabled
    }
    else if (!keypad && SoQtKeyboardP::translatetable->find(key, table)) {
      struct SoQtKeyboardP::key1map * map = (struct SoQtKeyboardP::key1map *)table;
      PRIVATE(this)->kbdevent->setKey(map->to);
#if 0 // disabled. Breaks build when compiling against OIV
      if (map->printable) PRIVATE(this)->kbdevent->setPrintableCharacter(map->printable);
#endif // disabled
    }
    else {
#if 0 // disabled. Breaks build when compiling against OIV
      PRIVATE(this)->kbdevent->setKey(SoKeyboardEvent::UNDEFINED);
      PRIVATE(this)->kbdevent->setPrintableCharacter((char) keyevent->ascii());
#else // disabled
      return NULL;
#endif
    }

    // Press or release?
    if (keyrelease) PRIVATE(this)->kbdevent->setState(SoButtonEvent::UP);
    else PRIVATE(this)->kbdevent->setState(SoButtonEvent::DOWN);

#if QT_VERSION >= 0x040000
    Qt::KeyboardModifiers state = keyevent->modifiers();
#else
    Qt::ButtonState state = keyevent->state();
#endif

    // Modifiers
#if QT_VERSION >= 0x040000
    PRIVATE(this)->kbdevent->setShiftDown(state & Qt::ShiftModifier);
    PRIVATE(this)->kbdevent->setCtrlDown(state & Qt::ControlModifier);
    PRIVATE(this)->kbdevent->setAltDown(state & Qt::AltModifier);
#else
    PRIVATE(this)->kbdevent->setShiftDown(state & Qt::ShiftButton);
    PRIVATE(this)->kbdevent->setCtrlDown(state & Qt::ControlButton);
    PRIVATE(this)->kbdevent->setAltDown(state & Qt::AltButton);
#endif

    // FIXME: read QCursor::position() instead,
    // and clean up this mess. 19990222 mortene.
    this->setEventPosition(PRIVATE(this)->kbdevent,
                           SoQtDevice::getLastEventPosition()[0],
                           SoQtDevice::getLastEventPosition()[1]);

    // FIXME: wrong -- should be the time the Qt event happened. Can't
    // find support for getting hold of that information in
    // Qt. 19990211 mortene.
    PRIVATE(this)->kbdevent->setTime(SbTime::getTimeOfDay());
    return PRIVATE(this)->kbdevent;
  }

  return NULL;
}

// *************************************************************************

#undef PRIVATE
#undef PUBLIC
