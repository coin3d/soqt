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

// FIXME: not in use yet. 19990620 mortene.

#include <stdio.h>

#include <qslider.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qframe.h>

#include <soqtdefs.h>
#include <Inventor/Qt/QColorSelection.h>


QColorSelection::QColorSelection(QWidget *parent, const char *name, QColor *col) : QWidget(parent, name)
{
  if (col == NULL) {
    QColor tempcol(0, 0, 0);
    col = &tempcol;
  }

  QGridLayout* grid = new QGridLayout(this, 4, 2);

  red   = new QSlider(0, 255, 1, col->red(),   QSlider::Horizontal, this);
  green = new QSlider(0, 255, 1, col->green(), QSlider::Horizontal, this);
  blue  = new QSlider(0, 255, 1, col->blue(),  QSlider::Horizontal, this);

  QFrame* frame = new QFrame(this);
  color = new QWidget(frame);

  QLabel* rgblabels[3];
  rgblabels[0] = new QLabel("R:", this);
  rgblabels[1] = new QLabel("G:", this);
  rgblabels[2] = new QLabel("B:", this);
  rgblabels[0]->setMinimumSize(rgblabels[0]->sizeHint());
  rgblabels[1]->setMinimumSize(rgblabels[1]->sizeHint());
  rgblabels[2]->setMinimumSize(rgblabels[2]->sizeHint());
  rgblabels[0]->setAlignment(AlignRight);
  rgblabels[1]->setAlignment(AlignRight);
  rgblabels[2]->setAlignment(AlignRight);

  grid->addMultiCellWidget(frame, 0, 0, 0, 1);
  grid->addMultiCellWidget(color, 0, 0, 0, 1);

  grid->addWidget(rgblabels[0], 1, 0);
  grid->addWidget(rgblabels[1], 2, 0);
  grid->addWidget(rgblabels[2], 3, 0);

  grid->addWidget(red,   1, 1);
  grid->addWidget(green, 2, 1);
  grid->addWidget(blue,  3, 1);

  grid->setColStretch(0, 1);
  grid->setColStretch(1, 10);

  valueChanged();

  QObject::connect(red, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));
  QObject::connect(green, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));
  QObject::connect(blue, SIGNAL(valueChanged(int)), this, SLOT(valueChanged()));


}

void QColorSelection::valueChanged()
{
  QColor col(red->value(), green->value(), blue->value());
  color->setBackgroundColor(col);
  emit colorChanged(col);
}

void QColorSelection::setType(const char *typeString)
{
#ifdef linux
  snprintf(titleString, MAX_TITLE, "%sColorEditor", typeString);
#else
  sprintf(titleString, "%sColorEditor", typeString);
#endif
  this->setCaption(titleString);
}

void QColorSelection::setColor(QColor col)
{
  printf("Setting color %i, %i, %i\n", col.red(), col.green(), col.blue());
  red->setValue(col.red());
  green->setValue(col.green());
  blue->setValue(col.blue());
}

void QColorSelection::closeEvent(QCloseEvent *e)
{
  e->accept();
  emit closed();
}
