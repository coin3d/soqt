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
