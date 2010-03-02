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
