/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
\**************************************************************************/

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
