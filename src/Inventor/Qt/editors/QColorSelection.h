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

#ifndef __QCOLORSELECTION_H__
#define __QCOLORSELECTION_H__

// FIXME: not in use yet. 19990620 mortene.

#include <qwidget.h>

class QSlider;

class QColorSelection : public QWidget {
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

#endif // !__QCOLORSELECTION_H__
