/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 as published by the Free Software Foundation.  See the file
 *  LICENSE.LGPL at the root directory of the distribution for all the
 *  details.
 *
 *  If you want to use Coin SoQt for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

#if SOQT_DEBUG
static const char rcsid[] =
  "$Id$";
#endif // SOQT_DEBUG

#include <qevent.h>
#include <qkeycode.h>
#if QT_VERSION >= 200
#include <q1xcompatibility.h>
#endif // Qt v2.0

#include <Inventor/SbDict.h>
#include <Inventor/events/SoKeyboardEvent.h>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtBasic.h>
#include <Inventor/Qt/devices/SoQtKeyboard.h>

#if HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

#include <stdlib.h> // atexit

/*!
  \class SoQtKeyboard SoQtKeyboard.h Inventor/Qt/devices/SoQtKeyboard.h
  \brief The SoQtKeyboard class ...
  \ingroup devices

  FIXME: write class doc
*/

// *************************************************************************

SOQT_OBJECT_SOURCE(SoQtKeyboard);

// *************************************************************************

/*!
  \enum SoQtKeyboard::Events
  FIXME: write doc
*/

/*!
  \var SoQtKeyboard::Events SoQtKeyboard::KEY_PRESS
  FIXME: write doc
*/

/*!
  \var SoQtKeyboard::Events SoQtKeyboard::KEY_RELEASE
  FIXME: write doc
*/

/*!
  \var SoQtKeyboard::Events SoQtKeyboard::ALL_EVENTS
  FIXME: write doc
*/

// *************************************************************************

// FIXME: get rid of this before 1.0 release (convert everything to Qt
// version 2.x API). 19990630 mortene.
#if QT_VERSION >= 200
#define Key_Escape Qt::Key_Escape
#define Key_Tab Qt::Key_Tab
#define Key_Backtab Qt::Key_Backtab
#define Key_BackTab Qt::Key_BackTab
#define Key_Backspace Qt::Key_Backspace
#define Key_BackSpace Qt::Key_BackSpace
#define Key_Return Qt::Key_Return
#define Key_Enter Qt::Key_Enter
#define Key_Insert Qt::Key_Insert
#define Key_Delete Qt::Key_Delete
#define Key_Pause Qt::Key_Pause
#define Key_Print Qt::Key_Print
#define Key_SysReq Qt::Key_SysReq
#define Key_Home Qt::Key_Home
#define Key_End Qt::Key_End
#define Key_Left Qt::Key_Left
#define Key_Up Qt::Key_Up
#define Key_Right Qt::Key_Right
#define Key_Down Qt::Key_Down
#define Key_Prior Qt::Key_Prior
#define Key_PageUp Qt::Key_PageUp
#define Key_Next Qt::Key_Next
#define Key_PageDown Qt::Key_PageDown
#define Key_Shift Qt::Key_Shift
#define Key_Control Qt::Key_Control
#define Key_Meta Qt::Key_Meta
#define Key_Alt Qt::Key_Alt
#define Key_CapsLock Qt::Key_CapsLock
#define Key_NumLock Qt::Key_NumLock
#define Key_ScrollLock Qt::Key_ScrollLock
#define Key_F1 Qt::Key_F1
#define Key_F2 Qt::Key_F2
#define Key_F3 Qt::Key_F3
#define Key_F4 Qt::Key_F4
#define Key_F5 Qt::Key_F5
#define Key_F6 Qt::Key_F6
#define Key_F7 Qt::Key_F7
#define Key_F8 Qt::Key_F8
#define Key_F9 Qt::Key_F9
#define Key_F10 Qt::Key_F10
#define Key_F11 Qt::Key_F11
#define Key_F12 Qt::Key_F12
#define Key_F13 Qt::Key_F13
#define Key_F14 Qt::Key_F14
#define Key_F15 Qt::Key_F15
#define Key_F16 Qt::Key_F16
#define Key_F17 Qt::Key_F17
#define Key_F18 Qt::Key_F18
#define Key_F19 Qt::Key_F19
#define Key_F20 Qt::Key_F20
#define Key_F21 Qt::Key_F21
#define Key_F22 Qt::Key_F22
#define Key_F23 Qt::Key_F23
#define Key_F24 Qt::Key_F24
#define Key_F25 Qt::Key_F25
#define Key_F26 Qt::Key_F26
#define Key_F27 Qt::Key_F27
#define Key_F28 Qt::Key_F28
#define Key_F29 Qt::Key_F29
#define Key_F30 Qt::Key_F30
#define Key_F31 Qt::Key_F31
#define Key_F32 Qt::Key_F32
#define Key_F33 Qt::Key_F33
#define Key_F34 Qt::Key_F34
#define Key_F35 Qt::Key_F35
#define Key_Super_L Qt::Key_L
#define Key_Super_R Qt::Key_R
#define Key_Menu Qt::Key_Menu
#define Key_Hyper_L Qt::Key_L
#define Key_Hyper_R Qt::Key_R
#define Key_Space Qt::Key_Space
#define Key_Any Qt::Key_Any
#define Key_Exclam Qt::Key_Exclam
#define Key_QuoteDbl Qt::Key_QuoteDbl
#define Key_NumberSign Qt::Key_NumberSign
#define Key_Dollar Qt::Key_Dollar
#define Key_Percent Qt::Key_Percent
#define Key_Ampersand Qt::Key_Ampersand
#define Key_Apostrophe Qt::Key_Apostrophe
#define Key_ParenLeft Qt::Key_ParenLeft
#define Key_ParenRight Qt::Key_ParenRight
#define Key_Asterisk Qt::Key_Asterisk
#define Key_Plus Qt::Key_Plus
#define Key_Comma Qt::Key_Comma
#define Key_Minus Qt::Key_Minus
#define Key_Period Qt::Key_Period
#define Key_Slash Qt::Key_Slash
#define Key_0 Qt::Key_0
#define Key_1 Qt::Key_1
#define Key_2 Qt::Key_2
#define Key_3 Qt::Key_3
#define Key_4 Qt::Key_4
#define Key_5 Qt::Key_5
#define Key_6 Qt::Key_6
#define Key_7 Qt::Key_7
#define Key_8 Qt::Key_8
#define Key_9 Qt::Key_9
#define Key_Colon Qt::Key_Colon
#define Key_Semicolon Qt::Key_Semicolon
#define Key_Less Qt::Key_Less
#define Key_Equal Qt::Key_Equal
#define Key_Greater Qt::Key_Greater
#define Key_Question Qt::Key_Question
#define Key_At Qt::Key_At
#define Key_A Qt::Key_A
#define Key_B Qt::Key_B
#define Key_C Qt::Key_C
#define Key_D Qt::Key_D
#define Key_E Qt::Key_E
#define Key_F Qt::Key_F
#define Key_G Qt::Key_G
#define Key_H Qt::Key_H
#define Key_I Qt::Key_I
#define Key_J Qt::Key_J
#define Key_K Qt::Key_K
#define Key_L Qt::Key_L
#define Key_M Qt::Key_M
#define Key_N Qt::Key_N
#define Key_O Qt::Key_O
#define Key_P Qt::Key_P
#define Key_Q Qt::Key_Q
#define Key_R Qt::Key_R
#define Key_S Qt::Key_S
#define Key_T Qt::Key_T
#define Key_U Qt::Key_U
#define Key_V Qt::Key_V
#define Key_W Qt::Key_W
#define Key_X Qt::Key_X
#define Key_Y Qt::Key_Y
#define Key_Z Qt::Key_Z
#define Key_BracketLeft Qt::Key_BracketLeft
#define Key_Backslash Qt::Key_Backslash
#define Key_BracketRight Qt::Key_BracketRight
#define Key_AsciiCircum Qt::Key_AsciiCircum
#define Key_Underscore Qt::Key_Underscore
#define Key_QuoteLeft Qt::Key_QuoteLeft
#define Key_BraceLeft Qt::Key_BraceLeft
#define Key_Bar Qt::Key_Bar
#define Key_BraceRight Qt::Key_BraceRight
#define Key_AsciiTilde Qt::Key_AsciiTilde
#define Key_unknown Qt::Key_unknown
#endif // Qt v2.x

struct key1map {
  int from;                // Qt val
  SoKeyboardEvent::Key to; // So val
  char printable;
};

static struct key1map QtToSoMapping[] = {
  {Key_Escape, SoKeyboardEvent::ESCAPE, '.'},
  {Key_Tab, SoKeyboardEvent::TAB, '.'},
  {Key_Backspace, SoKeyboardEvent::BACKSPACE, '.'},
  {Key_Return, SoKeyboardEvent::RETURN, '.'},
  {Key_Enter, SoKeyboardEvent::ENTER, '.'},
  {Key_Insert, SoKeyboardEvent::INSERT, '.'},
#ifdef HAVE_SOKEYBOARDEVENT_DELETE
  {Key_Delete, SoKeyboardEvent::DELETE, '.'},
#else
  {Key_Delete, SoKeyboardEvent::KEY_DELETE, '.'},
#endif
  {Key_Pause, SoKeyboardEvent::PAUSE, '.'},
  {Key_Print, SoKeyboardEvent::PRINT, '.'},
  {Key_Home, SoKeyboardEvent::HOME, '.'},
  {Key_End, SoKeyboardEvent::END, '.'},
  {Key_Left, SoKeyboardEvent::LEFT_ARROW, '.'},
  {Key_Up, SoKeyboardEvent::UP_ARROW, '.'},
  {Key_Right, SoKeyboardEvent::RIGHT_ARROW, '.'},
  {Key_Down, SoKeyboardEvent::DOWN_ARROW, '.'},
  {Key_Prior, SoKeyboardEvent::PRIOR, '.'},
  {Key_PageUp, SoKeyboardEvent::PAGE_UP, '.'},
  {Key_Next, SoKeyboardEvent::NEXT, '.'},
  {Key_PageDown, SoKeyboardEvent::PAGE_DOWN, '.'},

  {Key_Shift, SoKeyboardEvent::LEFT_SHIFT, '.'},
  {Key_Control, SoKeyboardEvent::LEFT_CONTROL, '.'},
  {Key_Meta, SoKeyboardEvent::LEFT_ALT, '.'},
  {Key_Alt, SoKeyboardEvent::LEFT_ALT, '.'},
  {Key_CapsLock, SoKeyboardEvent::CAPS_LOCK, '.'},
  {Key_NumLock, SoKeyboardEvent::NUM_LOCK, '.'},
  {Key_ScrollLock, SoKeyboardEvent::SCROLL_LOCK, '.'},

  {Key_F1, SoKeyboardEvent::F1, '.'},
  {Key_F2, SoKeyboardEvent::F2, '.'},
  {Key_F3, SoKeyboardEvent::F3, '.'},
  {Key_F4, SoKeyboardEvent::F4, '.'},
  {Key_F5, SoKeyboardEvent::F5, '.'},
  {Key_F6, SoKeyboardEvent::F6, '.'},
  {Key_F7, SoKeyboardEvent::F7, '.'},
  {Key_F8, SoKeyboardEvent::F8, '.'},
  {Key_F9, SoKeyboardEvent::F9, '.'},
  {Key_F10, SoKeyboardEvent::F10, '.'},
  {Key_F11, SoKeyboardEvent::F11, '.'},
  {Key_F12, SoKeyboardEvent::F12, '.'},
  {Key_Space, SoKeyboardEvent::SPACE, ' '},
  {Key_Exclam, SoKeyboardEvent::NUMBER_1, '!'},
  {Key_QuoteDbl, SoKeyboardEvent::APOSTROPHE, '\"'},
  {Key_NumberSign, SoKeyboardEvent::NUMBER_3, '#'},
  {Key_Dollar, SoKeyboardEvent::NUMBER_4, '$'},
  {Key_Percent, SoKeyboardEvent::NUMBER_5, '%'},
  {Key_Ampersand, SoKeyboardEvent::NUMBER_6, '^'},
  {Key_Apostrophe, SoKeyboardEvent::APOSTROPHE, '\''},
  {Key_ParenLeft, SoKeyboardEvent::NUMBER_9, '('},
  {Key_ParenRight, SoKeyboardEvent::NUMBER_0, ')'},
  {Key_Asterisk, SoKeyboardEvent::NUMBER_8, '*'},
  {Key_Plus, SoKeyboardEvent::EQUAL, '+'},
  {Key_Comma, SoKeyboardEvent::COMMA, ','},
  {Key_Minus, SoKeyboardEvent::MINUS, '-'},
  {Key_Period, SoKeyboardEvent::PERIOD, '.'},
  {Key_Slash, SoKeyboardEvent::SLASH, '/'},
  {Key_0, SoKeyboardEvent::NUMBER_0, '0'},
  {Key_1, SoKeyboardEvent::NUMBER_1, '1'},
  {Key_2, SoKeyboardEvent::NUMBER_2, '2'},
  {Key_3, SoKeyboardEvent::NUMBER_3, '3'},
  {Key_4, SoKeyboardEvent::NUMBER_4, '4'},
  {Key_5, SoKeyboardEvent::NUMBER_5, '5'},
  {Key_6, SoKeyboardEvent::NUMBER_6, '6'},
  {Key_7, SoKeyboardEvent::NUMBER_7, '7'},
  {Key_8, SoKeyboardEvent::NUMBER_8, '8'},
  {Key_9, SoKeyboardEvent::NUMBER_9, '9'},
  {Key_Colon, SoKeyboardEvent::SEMICOLON, ':'},
  {Key_Semicolon, SoKeyboardEvent::SEMICOLON, ';'},
  {Key_Less, SoKeyboardEvent::COMMA, '<'},
  {Key_Equal, SoKeyboardEvent::EQUAL, '='},
  {Key_Greater, SoKeyboardEvent::PERIOD, '>'},
  {Key_Question, SoKeyboardEvent::BACKSLASH, '?'},
  {Key_At, SoKeyboardEvent::NUMBER_2, '@'},

  // zero means let SoKeyboardEvent handle the printable character
  {Key_A, SoKeyboardEvent::A, 0},
  {Key_B, SoKeyboardEvent::B, 0},
  {Key_C, SoKeyboardEvent::C, 0},
  {Key_D, SoKeyboardEvent::D, 0},
  {Key_E, SoKeyboardEvent::E, 0},
  {Key_F, SoKeyboardEvent::F, 0},
  {Key_G, SoKeyboardEvent::G, 0},
  {Key_H, SoKeyboardEvent::H, 0},
  {Key_I, SoKeyboardEvent::I, 0},
  {Key_J, SoKeyboardEvent::J, 0},
  {Key_K, SoKeyboardEvent::K, 0},
  {Key_L, SoKeyboardEvent::L, 0},
  {Key_M, SoKeyboardEvent::M, 0},
  {Key_N, SoKeyboardEvent::N, 0},
  {Key_O, SoKeyboardEvent::O, 0},
  {Key_P, SoKeyboardEvent::P, 0},
  {Key_Q, SoKeyboardEvent::Q, 0},
  {Key_R, SoKeyboardEvent::R, 0},
  {Key_S, SoKeyboardEvent::S, 0},
  {Key_T, SoKeyboardEvent::T, 0},
  {Key_U, SoKeyboardEvent::U, 0},
  {Key_V, SoKeyboardEvent::V, 0},
  {Key_W, SoKeyboardEvent::W, 0},
  {Key_X, SoKeyboardEvent::X, 0},
  {Key_Y, SoKeyboardEvent::Y, 0},
  {Key_Z, SoKeyboardEvent::Z, 0},
  {Key_BracketLeft, SoKeyboardEvent::BRACKETLEFT, '['},
  {Key_Backslash, SoKeyboardEvent::BACKSLASH, '\\'},
  {Key_BracketRight, SoKeyboardEvent::BRACKETRIGHT, ']'},
  {Key_AsciiCircum, SoKeyboardEvent::NUMBER_7, '&'},
  {Key_Underscore, SoKeyboardEvent::MINUS, '_'},
  {Key_BraceLeft, SoKeyboardEvent::BRACKETLEFT, '{'},
  {Key_Bar, SoKeyboardEvent::BACKSLASH, '|'},
  {Key_BraceRight, SoKeyboardEvent::BRACKETRIGHT, '}'},
  {Key_AsciiTilde, SoKeyboardEvent::GRAVE, '~'},
  {Key_unknown, SoKeyboardEvent::ANY, 0}
};

static struct key1map QtToSoMapping_kp[] = {
  {Key_Home, SoKeyboardEvent::PAD_7, '.'},
  {Key_End, SoKeyboardEvent::PAD_1, '.'},
  {Key_Left, SoKeyboardEvent::PAD_4, '.'},
  {Key_Up, SoKeyboardEvent::PAD_8, '.'},
  {Key_Right, SoKeyboardEvent::PAD_6, '.'},
  {Key_Down, SoKeyboardEvent::PAD_2, '.'},
  {Key_PageUp, SoKeyboardEvent::PAD_9, '.'},
  {Key_PageDown, SoKeyboardEvent::PAD_3, '.'},
  {Key_Enter, SoKeyboardEvent::PAD_ENTER, '.'},
  {Key_Delete, SoKeyboardEvent::PAD_DELETE, '.'},
  {Key_Insert, SoKeyboardEvent::PAD_INSERT, '.'},
  {Key_Plus, SoKeyboardEvent::PAD_ADD, '+'},
  {Key_Minus, SoKeyboardEvent::PAD_SUBTRACT, '-'},
  {Key_Period, SoKeyboardEvent::PAD_PERIOD, '.'},
  {Key_Asterisk, SoKeyboardEvent::PAD_MULTIPLY, '*'},
  {Key_Slash, SoKeyboardEvent::PAD_DIVIDE, '/'},
  {Key_Space, SoKeyboardEvent::PAD_SPACE, ' '},
  {Key_Tab, SoKeyboardEvent::PAD_TAB, '.'},
  {Key_F1, SoKeyboardEvent::PAD_F1, '.'},
  {Key_F2, SoKeyboardEvent::PAD_F2, '.'},
  {Key_F3, SoKeyboardEvent::PAD_F3, '.'},
  {Key_F4, SoKeyboardEvent::PAD_F4, '.'},
  {Key_0, SoKeyboardEvent::PAD_0, '0'},
  {Key_1, SoKeyboardEvent::PAD_1, '1'},
  {Key_2, SoKeyboardEvent::PAD_2, '2'},
  {Key_3, SoKeyboardEvent::PAD_3, '3'},
  {Key_4, SoKeyboardEvent::PAD_4, '4'},
  {Key_5, SoKeyboardEvent::PAD_5, '5'},
  {Key_6, SoKeyboardEvent::PAD_6, '6'},
  {Key_7, SoKeyboardEvent::PAD_7, '7'},
  {Key_8, SoKeyboardEvent::PAD_8, '8'},
  {Key_9, SoKeyboardEvent::PAD_9, '9'},
  {Key_unknown, SoKeyboardEvent::ANY, 0} // Ends table
};

static SbDict * translatetable = NULL;
static SbDict * kp_translatetable = NULL;

static void
soqtkeyboard_cleanup(void)
{
  delete translatetable;
  delete kp_translatetable;
}

// *************************************************************************

/*!
  Constructor.
*/

SoQtKeyboard::SoQtKeyboard(
  int mask )
{
  this->eventmask = mask;
  this->kbdevent = NULL;
} // SoQtKeyboard()

/*!
  Destructor.
*/

SoQtKeyboard::~SoQtKeyboard(
  void )
{
  delete this->kbdevent;
} // ~SoQtKeyboard()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

void
SoQtKeyboard::enable(
  QWidget *, // widget,
  SoQtEventHandler *, // handler,
  void * ) // closure )
{
// FIXME: SOQT_STUB();
} // enable()

/*!
  FIXME: write function documentation
*/

void
SoQtKeyboard::disable(
  QWidget *, // widget,
  SoQtEventHandler *, // handler,
  void * ) // closure )
{
// FIXME: SOQT_STUB();
} // disable()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

static void
makeTranslationTable(void)
{
  assert(translatetable == NULL);
  translatetable = new SbDict;
  kp_translatetable = new SbDict;

  int i = 0;
  while (QtToSoMapping[i].from != Key_unknown) {
    translatetable->enter((unsigned long)QtToSoMapping[i].from,
                          (void *)&QtToSoMapping[i]);
    i++;
  }

  i = 0;
  while (QtToSoMapping_kp[i].from != Key_unknown) {
    kp_translatetable->enter((unsigned long)QtToSoMapping_kp[i].from,
                             (void *)&QtToSoMapping_kp[i]);
    i++;
  }
} // makeTranslationTable()

// *************************************************************************

/*!
  FIXME: write function documentation
*/

const SoEvent *
SoQtKeyboard::translateEvent(
  QEvent * event )
{
  SbBool keypress = event->type() == Event_KeyPress;
  SbBool keyrelease = event->type() == Event_KeyRelease;

#if QT_VERSION >= 200
  // Qt 2 introduced "accelerator" type keyboard events.
  keypress = keypress || (event->type() == QEvent::Accel);
  keyrelease = keyrelease || (event->type() == QEvent::AccelAvailable);
#endif // Qt v2.0

  SbBool keyevent = keypress || keyrelease;

  if (keyevent && (this->eventmask & (KEY_PRESS|KEY_RELEASE))) {

    if (!translatetable) makeTranslationTable();

    QKeyEvent * keyevent = (QKeyEvent *)event;
    int key = keyevent->key();
    // Key code / sequence unknown to Qt.
    if (key == 0) return NULL;
    
    // Allocate system-neutral event object once and reuse.
    if (!this->kbdevent) this->kbdevent = new SoKeyboardEvent;

    // FIXME: check for Key_unknown. 19990212 mortene.
    SbBool keypad = (keyevent->state() & Qt::Keypad) != 0;

    // Translate keycode Qt -> So
    void * table;
    if (keypad && kp_translatetable->find(key, table)) {
      struct key1map * map = (struct key1map*) table;
      this->kbdevent->setKey(map->to);
#if 0 // disabled. Breaks build when compiling against OIV
      if (map->printable) this->kbdevent->setPrintableCharacter(map->printable);
#endif // disabled
    } 
    else if (!keypad && translatetable->find(key, table)) {
      struct key1map * map = (struct key1map*) table;
      this->kbdevent->setKey(map->to);
#if 0 // disabled. Breaks build when compiling against OIV
      if (map->printable) this->kbdevent->setPrintableCharacter(map->printable);
#endif // disabled
    }
    else {
      this->kbdevent->setKey(SoKeyboardEvent::UNDEFINED);
#if 0 // disabled. Breaks build when compiling against OIV
      this->kbdevent->setPrintableCharacter((char) keyevent->ascii());
#endif // disabled
    }

    // Press or release?
    if (keyrelease) this->kbdevent->setState(SoButtonEvent::UP);
    else this->kbdevent->setState(SoButtonEvent::DOWN);

    // Need to mask in or out modifiers to get the correct state, as
    // the state() function gives us the situation immediately
    // _before_ the event happened.
    int state = keyevent->state();
    if (keypress) {
      switch (keyevent->key()) {
      case Key_Shift: state |= ShiftButton; break;
      case Key_Control: state |= ControlButton; break;
      case Key_Alt: state |= AltButton; break;
      case Key_Meta: state |= AltButton; break;
      }
    }
    else {
      switch (keyevent->key()) {
      case Key_Shift: state &= ~ShiftButton; break;
      case Key_Control: state &= ~ControlButton; break;
      case Key_Alt: state &= ~AltButton; break;
      case Key_Meta: state &= ~AltButton; break;
      }
    }

    // Modifiers
    this->kbdevent->setShiftDown(state & ShiftButton);
    this->kbdevent->setCtrlDown(state & ControlButton);
    this->kbdevent->setAltDown(state & AltButton);

    // FIXME: read QCursor::position() instead,
    // and clean up this mess. 19990222 mortene.
    this->setEventPosition( this->kbdevent,
                            SoQtDevice::getLastEventPosition().x(),
                            SoQtDevice::getLastEventPosition().y() );

    // FIXME: wrong -- should be the time the Qt event happened. Can't
    // find support for getting hold of that information in
    // Qt. 19990211 mortene.
    this->kbdevent->setTime(SbTime::getTimeOfDay());
    return this->kbdevent;
  }

  return NULL;
} // translateEvent()

// *************************************************************************

#if SOQT_DEBUG
static const char * getSoQtKeyboardRCSId(void) { return rcsid; }
#endif // SOQT_DEBUG

