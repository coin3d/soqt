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
