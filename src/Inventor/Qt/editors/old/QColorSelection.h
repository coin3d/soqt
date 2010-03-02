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

#ifndef SOQT_QCOLORSELECTION_H
#define SOQT_QCOLORSELECTION_H

// FIXME: not in use yet. 19990620 mortene.

#include <qwidget.h>

class QSlider;

class QColorSelection : public QWidget
{
  Q_OBJECT

public:
  enum { MAX_TITLE = 60 };
  QColorSelection(QWidget * parent = NULL, const char * name = NULL,
                  QColor * col = NULL);

  void setColor(QColor col);
  void setType(const char * typeString);

public slots:
  void valueChanged();

signals:
  void colorChanged(QColor & col);
  void closed();

protected:
  void closeEvent(QCloseEvent * e);

private:
  QSlider * red, * green, * blue;
  QWidget * color;
  char titleString[MAX_TITLE + 1];
};

#endif // !SOQT_QCOLORSELECTION_H
