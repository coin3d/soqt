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
 *  http://www.sim.no/ sales@sim.no Voice: +47 73540378 Fax: +47 73943861
 *
\**************************************************************************/

#ifndef __SOQTCOLORSLIDER_H__
#define __SOQTCOLORSLIDER_H__

// FIXME: not in use yet. 19990620 mortene.
 
# include <qwidget.h> 

class QLabel;
class QSlider;
class QLineEdit;
class QBoxLayout;
class QSize;
class QColor;

class _SoQtColorSlider : public QWidget {
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

class _SoQtColorEditor : public QWidget {
public:
  _SoQtColorEditor(QWidget * parent = NULL, const char * name = NULL);
};

#endif // !__SOQTCOLORSLIDER_H__
