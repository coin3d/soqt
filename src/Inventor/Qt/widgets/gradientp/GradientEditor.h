#ifndef GRADIENT_EDITOR_H
#define GRADIENT_EDITOR_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org> for more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
\**************************************************************************/

#include <qwidget.h>

class Gradient;
class GradientView;
class QSlider;
class QLabel;
class QLineEdit;
class QCheckBox;
class QResizeEvent;

class GradientEditor : public QWidget
{
  Q_OBJECT
public:
  GradientEditor(Gradient * grad = NULL, QWidget* parent=0, bool modal = FALSE, const char* name=0, WFlags f=0);
  ~GradientEditor();

  Gradient * getGradient(void) const;
  void setGradient(Gradient * grad);
  void resizeEvent(QResizeEvent *);

signals:
  void accepted(void);
  void rejected(void);

public slots:
  void setMin(float min);
  void setMax(float max);
  void updateValueLabels(void);
  void updateAll(void);
  void accept(void);
  void reject(void);
  
private:
  GradientView * gradView;
  QWidget * gradientWidget;
  Gradient * grad;
  Gradient * originalGradient;
  QSlider * slider;
  QLabel * paramValue;
  QLabel * dataValue;
  QLabel * colorLabel;
  float min, max;
  float minTemp, maxTemp;
};

#endif
