/**************************************************************************\
 *
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

static const char rcsid[] =
  "$Id$";

/*!
  \class SoQtKeyboard SoQtKeyboard.h Inventor/Qt/devices/SoQtKeyboard.h
  \brief The SoQtKeyboard class ...
  \ingroup qtdevices

  FIXME: write class doc
*/

#include <assert.h>
#include <qevent.h>
#include <qkeycode.h>
#if QT_VERSION >= 200
#include <q1xcompatibility.h>
#endif // Qt v2.0

#if SOGUI_DEBUG
#include <Inventor/errors/SoDebugError.h>
#endif // SOGUI_DEBUG
#include <Inventor/events/SoKeyboardEvent.h>

#include <Inventor/Qt/devices/SoQtKeyboard.h>


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
};

static struct key1map QtToSoMapping[] = {
  {Key_Escape, SoKeyboardEvent::ESCAPE},
  {Key_Tab, SoKeyboardEvent::TAB},
//    {Key_Backtab, SoKeyboardEvent::}, // FIXME
  {Key_Backspace, SoKeyboardEvent::BACKSPACE},
  {Key_Return, SoKeyboardEvent::RETURN},
  {Key_Enter, SoKeyboardEvent::ENTER},
  {Key_Insert, SoKeyboardEvent::INSERT},
#ifdef WIN32
  {Key_Delete, SoKeyboardEvent::KEY_DELETE},
#else
  {Key_Delete, SoKeyboardEvent::DELETE},
#endif
  {Key_Pause, SoKeyboardEvent::PAUSE},
  {Key_Print, SoKeyboardEvent::PRINT},
//    {Key_SysReq, SoKeyboardEvent::}, // FIXME
  {Key_Home, SoKeyboardEvent::HOME},
  {Key_End, SoKeyboardEvent::END},
  {Key_Left, SoKeyboardEvent::LEFT_ARROW},
  {Key_Up, SoKeyboardEvent::UP_ARROW},
  {Key_Right, SoKeyboardEvent::RIGHT_ARROW},
  {Key_Down, SoKeyboardEvent::DOWN_ARROW},
  {Key_Prior, SoKeyboardEvent::PRIOR},
  {Key_PageUp, SoKeyboardEvent::PAGE_UP},
  {Key_Next, SoKeyboardEvent::NEXT},
  {Key_PageDown, SoKeyboardEvent::PAGE_DOWN},

  {Key_Shift, SoKeyboardEvent::LEFT_SHIFT},
  {Key_Control, SoKeyboardEvent::LEFT_CONTROL},
  {Key_Meta, SoKeyboardEvent::LEFT_ALT},
  {Key_Alt, SoKeyboardEvent::LEFT_ALT},
  {Key_CapsLock, SoKeyboardEvent::CAPS_LOCK},
  {Key_NumLock, SoKeyboardEvent::NUM_LOCK},
  {Key_ScrollLock, SoKeyboardEvent::SCROLL_LOCK},

  {Key_F1, SoKeyboardEvent::F1},
  {Key_F2, SoKeyboardEvent::F2},
  {Key_F3, SoKeyboardEvent::F3},
  {Key_F4, SoKeyboardEvent::F4},
  {Key_F5, SoKeyboardEvent::F5},
  {Key_F6, SoKeyboardEvent::F6},
  {Key_F7, SoKeyboardEvent::F7},
  {Key_F8, SoKeyboardEvent::F8},
  {Key_F9, SoKeyboardEvent::F9},
  {Key_F10, SoKeyboardEvent::F10},
  {Key_F11, SoKeyboardEvent::F11},
  {Key_F12, SoKeyboardEvent::F12},
//    {Key_F13, SoKeyboardEvent::}, // FIXME
//    {Key_F14, SoKeyboardEvent::}, // FIXME
//    {Key_F15, SoKeyboardEvent::}, // FIXME
//    {Key_F16, SoKeyboardEvent::}, // FIXME
//    {Key_F17, SoKeyboardEvent::}, // FIXME
//    {Key_F18, SoKeyboardEvent::}, // FIXME
//    {Key_F19, SoKeyboardEvent::}, // FIXME
//    {Key_F20, SoKeyboardEvent::}, // FIXME
//    {Key_F21, SoKeyboardEvent::}, // FIXME
//    {Key_F22, SoKeyboardEvent::}, // FIXME
//    {Key_F23, SoKeyboardEvent::}, // FIXME
//    {Key_F24, SoKeyboardEvent::}, // FIXME
//    {Key_F25, SoKeyboardEvent::}, // FIXME
//    {Key_F26, SoKeyboardEvent::}, // FIXME
//    {Key_F27, SoKeyboardEvent::}, // FIXME
//    {Key_F28, SoKeyboardEvent::}, // FIXME
//    {Key_F29, SoKeyboardEvent::}, // FIXME
//    {Key_F30, SoKeyboardEvent::}, // FIXME
//    {Key_F31, SoKeyboardEvent::}, // FIXME
//    {Key_F32, SoKeyboardEvent::}, // FIXME
//    {Key_F33, SoKeyboardEvent::}, // FIXME
//    {Key_F34, SoKeyboardEvent::}, // FIXME
//    {Key_F35, SoKeyboardEvent::}, // FIXME

//    {Key_Super, SoKeyboardEvent::}, // FIXME
//    {Key_Super, SoKeyboardEvent::}, // FIXME
//    {Key_Menu, SoKeyboardEvent::}, // FIXME


  {Key_Space, SoKeyboardEvent::SPACE},
//    {Key_Exclam, SoKeyboardEvent::}, // FIXME
//    {Key_QuoteDbl, SoKeyboardEvent::}, // FIXME
//    {Key_NumberSign, SoKeyboardEvent::}, // FIXME
//    {Key_Dollar, SoKeyboardEvent::}, // FIXME
//    {Key_Percent, SoKeyboardEvent::}, // FIXME
//    {Key_Ampersand, SoKeyboardEvent::}, // FIXME
  {Key_Apostrophe, SoKeyboardEvent::APOSTROPHE},
//    {Key_ParenLeft, SoKeyboardEvent::}, // FIXME
//    {Key_ParenRight, SoKeyboardEvent::}, // FIXME
//    {Key_Asterisk, SoKeyboardEvent::}, // FIXME
//    {Key_Plus, SoKeyboardEvent::}, // FIXME
  {Key_Comma, SoKeyboardEvent::COMMA},
  {Key_Minus, SoKeyboardEvent::MINUS},
  {Key_Period, SoKeyboardEvent::PERIOD},
  {Key_Slash, SoKeyboardEvent::SLASH},
  {Key_0, SoKeyboardEvent::NUMBER_0},
  {Key_1, SoKeyboardEvent::NUMBER_1},
  {Key_2, SoKeyboardEvent::NUMBER_2},
  {Key_3, SoKeyboardEvent::NUMBER_3},
  {Key_4, SoKeyboardEvent::NUMBER_4},
  {Key_5, SoKeyboardEvent::NUMBER_5},
  {Key_6, SoKeyboardEvent::NUMBER_6},
  {Key_7, SoKeyboardEvent::NUMBER_7},
  {Key_8, SoKeyboardEvent::NUMBER_8},
  {Key_9, SoKeyboardEvent::NUMBER_9},
//    {Key_Colon, SoKeyboardEvent::}, // FIXME
  {Key_Semicolon, SoKeyboardEvent::SEMICOLON},
//    {Key_Less, SoKeyboardEvent::}, // FIXME
  {Key_Equal, SoKeyboardEvent::EQUAL},
//    {Key_Greater, SoKeyboardEvent::}, // FIXME
//    {Key_Question, SoKeyboardEvent::}, // FIXME
//    {Key_At, SoKeyboardEvent::}, // FIXME
  {Key_A, SoKeyboardEvent::A},
  {Key_B, SoKeyboardEvent::B},
  {Key_C, SoKeyboardEvent::C},
  {Key_D, SoKeyboardEvent::D},
  {Key_E, SoKeyboardEvent::E},
  {Key_F, SoKeyboardEvent::F},
  {Key_G, SoKeyboardEvent::G},
  {Key_H, SoKeyboardEvent::H},
  {Key_I, SoKeyboardEvent::I},
  {Key_J, SoKeyboardEvent::J},
  {Key_K, SoKeyboardEvent::K},
  {Key_L, SoKeyboardEvent::L},
  {Key_M, SoKeyboardEvent::M},
  {Key_N, SoKeyboardEvent::N},
  {Key_O, SoKeyboardEvent::O},
  {Key_P, SoKeyboardEvent::P},
  {Key_Q, SoKeyboardEvent::Q},
  {Key_R, SoKeyboardEvent::R},
  {Key_S, SoKeyboardEvent::S},
  {Key_T, SoKeyboardEvent::T},
  {Key_U, SoKeyboardEvent::U},
  {Key_V, SoKeyboardEvent::V},
  {Key_W, SoKeyboardEvent::W},
  {Key_X, SoKeyboardEvent::X},
  {Key_Y, SoKeyboardEvent::Y},
  {Key_Z, SoKeyboardEvent::Z},
  {Key_BracketLeft, SoKeyboardEvent::BRACKETLEFT},
  {Key_Backslash, SoKeyboardEvent::BACKSLASH},
  {Key_BracketRight, SoKeyboardEvent::BRACKETRIGHT},
//    {Key_AsciiCircum, SoKeyboardEvent::}, // FIXME
//    {Key_Underscore, SoKeyboardEvent::}, // FIXME
//    {Key_QuoteLeft, SoKeyboardEvent::}, // FIXME
//    {Key_BraceLeft, SoKeyboardEvent::}, // FIXME
//    {Key_Bar, SoKeyboardEvent::}, // FIXME
//    {Key_BraceRight, SoKeyboardEvent::}, // FIXME
  {Key_AsciiTilde, SoKeyboardEvent::GRAVE}, // FIXME: is this correct?

  // Latin-1
//    {Key_nobreakspace, SoKeyboardEvent::}, // FIXME
//    {Key_exclamdown, SoKeyboardEvent::}, // FIXME
//    {Key_cent, SoKeyboardEvent::}, // FIXME
//    {Key_sterling, SoKeyboardEvent::}, // FIXME
//    {Key_currency, SoKeyboardEvent::}, // FIXME
//    {Key_yen, SoKeyboardEvent::}, // FIXME
//    {Key_brokenbar, SoKeyboardEvent::}, // FIXME
//    {Key_section, SoKeyboardEvent::}, // FIXME
//    {Key_diaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_copyright, SoKeyboardEvent::}, // FIXME
//    {Key_ordfeminine, SoKeyboardEvent::}, // FIXME
//    {Key_guillemotleft, SoKeyboardEvent::}, // FIXME
//    {Key_notsign, SoKeyboardEvent::}, // FIXME
//    {Key_hyphen, SoKeyboardEvent::}, // FIXME
//    {Key_registered, SoKeyboardEvent::}, // FIXME
//    {Key_macron, SoKeyboardEvent::}, // FIXME
//    {Key_degree, SoKeyboardEvent::}, // FIXME
//    {Key_plusminus, SoKeyboardEvent::}, // FIXME
//    {Key_twosuperior, SoKeyboardEvent::}, // FIXME
//    {Key_threesuperior, SoKeyboardEvent::}, // FIXME
//    {Key_acute, SoKeyboardEvent::}, // FIXME
//    {Key_mu, SoKeyboardEvent::}, // FIXME
//    {Key_paragraph, SoKeyboardEvent::}, // FIXME
//    {Key_periodcentered, SoKeyboardEvent::}, // FIXME
//    {Key_cedilla, SoKeyboardEvent::}, // FIXME
//    {Key_onesuperior, SoKeyboardEvent::}, // FIXME
//    {Key_masculine, SoKeyboardEvent::}, // FIXME
//    {Key_guillemotright, SoKeyboardEvent::}, // FIXME
//    {Key_onequarter, SoKeyboardEvent::}, // FIXME
//    {Key_onehalf, SoKeyboardEvent::}, // FIXME
//    {Key_threequarters, SoKeyboardEvent::}, // FIXME
//    {Key_questiondown, SoKeyboardEvent::}, // FIXME
//    {Key_Agrave, SoKeyboardEvent::}, // FIXME
//    {Key_Aacute, SoKeyboardEvent::}, // FIXME
//    {Key_Acircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_Atilde, SoKeyboardEvent::}, // FIXME
//    {Key_Adiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_Aring, SoKeyboardEvent::}, // FIXME
//    {Key_AE, SoKeyboardEvent::}, // FIXME
//    {Key_Ccedilla, SoKeyboardEvent::}, // FIXME
//    {Key_Egrave, SoKeyboardEvent::}, // FIXME
//    {Key_Eacute, SoKeyboardEvent::}, // FIXME
//    {Key_Ecircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_Ediaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_Igrave, SoKeyboardEvent::}, // FIXME
//    {Key_Iacute, SoKeyboardEvent::}, // FIXME
//    {Key_Icircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_Idiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_ETH, SoKeyboardEvent::}, // FIXME
//    {Key_Ntilde, SoKeyboardEvent::}, // FIXME
//    {Key_Ograve, SoKeyboardEvent::}, // FIXME
//    {Key_Oacute, SoKeyboardEvent::}, // FIXME
//    {Key_Ocircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_Otilde, SoKeyboardEvent::}, // FIXME
//    {Key_Odiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_multiply, SoKeyboardEvent::}, // FIXME
//    {Key_Ooblique, SoKeyboardEvent::}, // FIXME
//    {Key_Ugrave, SoKeyboardEvent::}, // FIXME
//    {Key_Uacute, SoKeyboardEvent::}, // FIXME
//    {Key_Ucircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_Udiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_Yacute, SoKeyboardEvent::}, // FIXME
//    {Key_THORN, SoKeyboardEvent::}, // FIXME
//    {Key_ssharp, SoKeyboardEvent::}, // FIXME
//    {Key_agrave, SoKeyboardEvent::}, // FIXME
//    {Key_aacute, SoKeyboardEvent::}, // FIXME
//    {Key_acircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_atilde, SoKeyboardEvent::}, // FIXME
//    {Key_adiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_aring, SoKeyboardEvent::}, // FIXME
//    {Key_ae, SoKeyboardEvent::}, // FIXME
//    {Key_ccedilla, SoKeyboardEvent::}, // FIXME
//    {Key_egrave, SoKeyboardEvent::}, // FIXME
//    {Key_eacute, SoKeyboardEvent::}, // FIXME
//    {Key_ecircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_ediaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_igrave, SoKeyboardEvent::}, // FIXME
//    {Key_iacute, SoKeyboardEvent::}, // FIXME
//    {Key_icircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_idiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_eth, SoKeyboardEvent::}, // FIXME
//    {Key_ntilde, SoKeyboardEvent::}, // FIXME
//    {Key_ograve, SoKeyboardEvent::}, // FIXME
//    {Key_oacute, SoKeyboardEvent::}, // FIXME
//    {Key_ocircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_otilde, SoKeyboardEvent::}, // FIXME
//    {Key_odiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_division, SoKeyboardEvent::}, // FIXME
//    {Key_oslash, SoKeyboardEvent::}, // FIXME
//    {Key_ugrave, SoKeyboardEvent::}, // FIXME
//    {Key_uacute, SoKeyboardEvent::}, // FIXME
//    {Key_ucircumflex, SoKeyboardEvent::}, // FIXME
//    {Key_udiaeresis, SoKeyboardEvent::}, // FIXME
//    {Key_yacute, SoKeyboardEvent::}, // FIXME
//    {Key_thorn, SoKeyboardEvent::}, // FIXME
//    {Key_ydiaeresis, SoKeyboardEvent::}, // FIXME

  {Key_unknown, SoKeyboardEvent::ANY} // Ends table
};


// FIXME: use a dict class from Qt instead? 19990213 mortene.
SbDict * SoQtKeyboard::translatetable = NULL;

/*!
  Constructor.
*/
SoQtKeyboard::SoQtKeyboard(soqtEventMask mask)
{
  this->eventmask = mask;
  this->kbdevent = NULL;
}

/*!
  Destructor.
*/
SoQtKeyboard::~SoQtKeyboard()
{
  delete this->kbdevent;
}

/*!
  FIXME: write function documentation
*/
void
SoQtKeyboard::enable(QWidget * /*w*/, SoQtEventHandler /*f*/, void * /*data*/)
{
  // TODO: implement
}

/*!
  FIXME: write function documentation
*/
void
SoQtKeyboard::disable(QWidget * /*w*/, SoQtEventHandler /*f*/, void * /*data*/)
{
  // TODO: implement
}

/*!
  FIXME: write function documentation
*/
void
SoQtKeyboard::makeTranslationTable(void)
{
  assert(SoQtKeyboard::translatetable == NULL);
  // FIXME: deallocate on exit. 20000311 mortene.
  SoQtKeyboard::translatetable = new SbDict;

  int i=0;
  while (QtToSoMapping[i].from != Key_unknown) {
    // FIXME: nasty casting going on -- design broken, should be
    // repaired somehow. 990212 mortene.
    SoQtKeyboard::translatetable->enter(QtToSoMapping[i].from,
                                        (void *)QtToSoMapping[i].to);
    i++;
  }
}

/*!
  FIXME: write function documentation
*/
const SoEvent *
SoQtKeyboard::translateEvent(QEvent * event)
{
  SbBool keypress = event->type() == Event_KeyPress;
  SbBool keyrelease = event->type() == Event_KeyRelease;

#if QT_VERSION >= 200
  // Qt 2 introduced "accelerator" type keyboard events.
  keypress = keypress || (event->type() == QEvent::Accel);
  keyrelease = keyrelease || (event->type() == QEvent::AccelAvailable);
#endif // Qt v2.0

  SbBool keyevent = keypress || keyrelease;

  if (keyevent && (this->eventmask & (soqtKeyPressMask|soqtKeyReleaseMask))) {

    if (!SoQtKeyboard::translatetable) SoQtKeyboard::makeTranslationTable();

    QKeyEvent * keyevent = (QKeyEvent *)event;

    // Allocate system-neutral event object once and reuse.
    if (!this->kbdevent) this->kbdevent = new SoKeyboardEvent;

    // FIXME: check for Key_unknown. 990212 mortene.


    // Translate keycode Qt -> So
    void * sokey;
    if (SoQtKeyboard::translatetable->find(keyevent->key(), sokey)) {
      this->kbdevent->setKey((SoKeyboardEvent::Key)(int)sokey);
    }
    else {
#if SOGUI_DEBUG
      SoDebugError::postWarning("SoQtKeyboard::translateEvent",
                                "couldn't translate key 0x%04x '%c' from "
                                "Qt -- please report",
                                keyevent->key(),
                                keyevent->ascii());
#endif // SOGUI_DEBUG
      return NULL;
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

    this->setEventPosition(this->kbdevent,
                           // FIXME: read QCursor::position() instead,
                           // and clean up this mess. 990222 mortene.
                           SoQtDevice::getLastEventPosition().x(),
                           SoQtDevice::getLastEventPosition().y());

    // FIXME: wrong -- should be the time the Qt event happened. Can't
    // find support for getting hold of that information in Qt. 990211
    // mortene.
    this->kbdevent->setTime(SbTime::getTimeOfDay());

    return this->kbdevent;
  }

  return NULL;
}
