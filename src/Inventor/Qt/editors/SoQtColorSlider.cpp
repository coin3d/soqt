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

static const char rcsid[] =
  "$Id$";

// FIXME: not in use yet. 19990620 mortene.

#include <stdlib.h>
#include <stdio.h>

#include <qslider.h>
#include <qlabel.h>
#include <qlined.h>
#include <qlayout.h>

#include <soqtdefs.h>
#include <Inventor/Qt/editors/SoQtColorSlider.h>

_SoQtColorSlider::_SoQtColorSlider(int minValue, int maxValue, QWidget *parent, const char *label) : QWidget(parent)
{
  QGridLayout *form = new QGridLayout(this, 1, 3);

  title = new QLabel(label, this, "sliderTitle");
  slider = new QSlider(QSlider::Horizontal, this);
  edit = new QLineEdit(this);

  title->setAlignment(AlignRight | AlignVCenter);
//  title->setBackgroundColor(QColor("blue"));
  // setMargin() in Qt1.x has been renamed to setIndent() in Qt2.x
  title->setMargin(3);
  slider->setRange(minValue, maxValue);
  slider->setTickmarks(QSlider::Below);
  slider->setTickInterval(10);
  edit->setFixedWidth(edit->fontMetrics().width("0.000") + 2);

  form->setColStretch(0, 1);
  form->setColStretch(1, 4);
  form->setColStretch(2, 2);
  form->addWidget(title, 0, 0, AlignRight);
//  form->addMultiCellWidget(slider, 0, 0, 1, 2);
  form->addWidget(slider, 0, 1);
  form->addWidget(edit, 0, 2);


  QObject::connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
  QObject::connect(edit, SIGNAL(returnPressed()), this, SLOT(setValue()));

  setValue(slider->value());

}

void _SoQtColorSlider::setValue(int value)
{
        char temp[20];
#ifdef linux
        snprintf(temp, 19, "%1.2f", (float) value / 100.0);
#else
        sprintf(temp, "%1.2f", (float) value / 100.0);
#endif
        edit->setText(temp);

        disconnect(slider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
        slider->setValue(value);
        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
        printf("emit valueChanged...");
        emit valueChanged((float) value / 100.0);
        printf("done\n");
}

void _SoQtColorSlider::setValue(const char *text)
{
        double temp;
        temp = strtod(text, NULL);
        disconnect(slider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
        slider->setValue((int) (temp * 100.0f));
        connect(slider, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));
        emit valueChanged(temp);
}

void _SoQtColorSlider::setValue()
{
        setValue(edit->text());
}

QSize _SoQtColorSlider::sizeHint() const
{
  QSize size;
  size.setWidth(title->width() + slider->width() + edit->width() + 15);
  size.setHeight(edit->height() + 2);
  printf("width = %i, height = %i\n", size.width(), size.height());
  return size;
}

void _SoQtColorSlider::setColor(QColor col)
{
  QColorGroup cgrp;
  QPalette palette;
  palette = slider->palette();
  cgrp = slider->colorGroup();

  QColorGroup *newgrp;
  if (cgrp == palette.normal()) {
    newgrp = new QColorGroup(cgrp.foreground(), cgrp.background(),
        cgrp.light(), cgrp.dark(), col, cgrp.text(), cgrp.base());
    palette.setNormal(*newgrp);
  }
  slider->setPalette(palette);
}

int _SoQtColorSlider::getValue() const
{
  return slider->value();
}
