/**************************************************************************\
 *
 *  This file is part of the Coin GUI toolkit libraries.
 *  Copyright (C) 1998-2002 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  version 2.1 as published by the Free Software Foundation.  See the
 *  file LICENSE.LGPL at the root directory of this source distribution
 *  for more details.
 *
 *  If you want to use this library with software that is incompatible
 *  licensewise with the LGPL, and / or you would like to take
 *  advantage of the additional benefits with regard to our support
 *  services, please contact Systems in Motion about acquiring a Coin
 *  Professional Edition License.  See <URL:http://www.coin3d.org> for
 *  more information.
 *
 *  Systems in Motion, Prof Brochs gate 6, 7030 Trondheim, NORWAY
 *  <URL:http://www.sim.no>, <mailto:support@sim.no>
 *
\**************************************************************************/

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

class SOQT_DLL_API _SoQtColorSlider : public QWidget
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

class SOQT_DLL_API _SoQtColorEditor : public QWidget
{
  Q_OBJECT

public:
  _SoQtColorEditor(QWidget * parent = NULL, const char * name = NULL);

};

#endif // ! SOQT_COLORSLIDER_H
