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

//  $Id$

#ifndef SOQT_COLORSLIDER_H
#define SOQT_COLORSLIDER_H

// FIXME: not in use yet. 19990620 mortene.

#include <qwidget.h>

class QLabel;
class QSlider;
class QLineEdit;
class QBoxLayout;
class QSize;
class QColor;

class SOQT_DLL_EXPORT _SoQtColorSlider : public QWidget
{
  Q_OBJECT

public:
  _SoQtColorSlider(int minValue, int maxValue, QWidget * parent = 0, const char * label = NULL);

  int getValue() const;
  void setColor(QColor col);
public slots:
  void setValue(int);
  void setValue(const char *);
  void setValue();

  QSize sizeHint() const;

  signals:
  void valueChanged(float value);

private:
  QLabel * title;
  QSlider * slider;
  QLineEdit * edit;
};

class SOQT_DLL_EXPORT _SoQtColorEditor : public QWidget
{
  Q_OBJECT

public:
  _SoQtColorEditor(QWidget * parent = NULL, const char * name = NULL);

};

#endif // ! SOQT_COLORSLIDER_H
