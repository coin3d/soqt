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

#include <qimage.h>
#include <qlayout.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qcheckbox.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qvalidator.h>
#include "CurveView.h"
#include <Inventor/Qt/widgets/SoQtCurveWidget.h>
#include "SoQtCurveWidgetP.h"

#define PRIVATE(p) p->pimpl
#define PUBLIC(p) p->publ

SoQtCurveWidgetP::SoQtCurveWidgetP(class SoQtCurveWidget * publ)
{
  this->publ = publ;
}

void
SoQtCurveWidgetP::toggleUpdate()
{
  this->contupdate = this->instantupdate->isChecked();
  if (this->callBack) {
    this->callBack(this->callbackData);
  }
}

void
SoQtCurveWidgetP::apply()
{
  if (this->callBack) {
    this->callBack(this->callbackData);
  }
}

void
SoQtCurveWidgetP::done()
{
  if (!this->contupdate) {
    this->callBack(this->callbackData);
  }
  PUBLIC(this)->close();
}

void
SoQtCurveWidgetP::reset()
{
  this->curvetypelist->setCurrentItem(CurveView::SMOOTH);
  this->curveview->resetActive();
  if (this->callBack) {
    this->callBack(this->callbackData);
  }
}

void
SoQtCurveWidgetP::changeCurveMode(int i)
{
  this->curveview->changeCurveMode(i);
  if (this->callBack) {
    this->callBack(this->callbackData);
  }
}

void
SoQtCurveWidgetP::curveCallBack(void * userData)
{
  SoQtCurveWidgetP * thisp = (SoQtCurveWidgetP*) userData;
  if (thisp->contupdate) {
    thisp->callBack(thisp->callbackData);
  }
}

void
SoQtCurveWidgetP::updateColorLabels()
{
  int width = this->horgrad->width();
  int height = this->horgrad->height();

  QPixmap pm = this->curveview->getPixmap(width-1, height-1);
  
  // flicker free drawing
  QPainter painter(&pm);
  painter.end();
  painter.begin(this->horgrad);
  painter.drawPixmap(1,1,pm);
}

void
SoQtCurveWidgetP::setConstantValue()
{
  this->curveview->changeCurveMode(CurveView::FREE);
  this->curvetypelist->setCurrentItem(CurveView::FREE);
  int value = this->constantvalue->text().toInt();
  this->curveview->setConstantValue(value);
}

SoQtCurveWidget::SoQtCurveWidget(QWidget * parent, const char * name)
: QWidget(parent, name)
{
  this->pimpl = new SoQtCurveWidgetP(this);
  PRIVATE(this)->callBack = NULL;
  
  QSizePolicy sizepolicy;
  sizepolicy.setVerData(QSizePolicy::MinimumExpanding);
  this->setSizePolicy(sizepolicy);

  QGridLayout * toplayout = new QGridLayout(this);
  toplayout->setMargin(10);
  QVBoxLayout * buttonlayout = new QVBoxLayout();

  QGroupBox * controlgroup = new QGroupBox(3, Qt::Horizontal, this);
  
  buttonlayout->setAlignment(Qt::AlignBottom);

  QWidget * curvewidget = new QWidget(this);
  curvewidget->setFixedSize(QSize(300,300));
  QGridLayout * curvelayout = new QGridLayout(curvewidget, 2, 2, 0);

  PRIVATE(this)->vertgrad = new QLabel(curvewidget);
  PRIVATE(this)->horgrad = new QLabel(curvewidget);
  PRIVATE(this)->vertgrad->setFixedSize(20, 256);
  PRIVATE(this)->horgrad->setFixedSize(256, 20); 
  PRIVATE(this)->vertgrad->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  PRIVATE(this)->horgrad->setFrameStyle(QFrame::Panel | QFrame::Sunken);

  curvelayout->addWidget(PRIVATE(this)->vertgrad, 0, 0);
  curvelayout->addWidget(PRIVATE(this)->horgrad, 1, 1);

  QCanvas * canvas = new QCanvas(256,256);
  PRIVATE(this)->curveview = new CurveView(canvas, curvewidget);
  PRIVATE(this)->curveview->setVScrollBarMode(QScrollView::AlwaysOff);
  PRIVATE(this)->curveview->setHScrollBarMode(QScrollView::AlwaysOff);
  PRIVATE(this)->curveview->setFixedSize(258,258); // need to make room for the border

  PRIVATE(this)->curveview->show();

  curvelayout->addWidget(PRIVATE(this)->curveview, 0, 1);

  PRIVATE(this)->vertgrad->setPixmap(PRIVATE(this)->curveview->getGradient(20, 256));
  PRIVATE(this)->horgrad->setPixmap(PRIVATE(this)->curveview->getPixmap(256, 20));

  toplayout->addWidget(controlgroup, 0, 0);
  toplayout->addLayout(buttonlayout, 1, 1);
  toplayout->addWidget(curvewidget, 1, 0);

  PRIVATE(this)->modetext = new QLabel(controlgroup);
  PRIVATE(this)->modetext->setText("Modify channel: ");

  PRIVATE(this)->colormodelist = new QComboBox(controlgroup);
  PRIVATE(this)->colormodelist->show();
  controlgroup->addSpace(1);

  QPixmap pm(16,16);
  pm.fill(Qt::red);
  PRIVATE(this)->colormodelist->insertItem(pm, "Red", CurveView::RED);
  pm.fill(Qt::green);
  PRIVATE(this)->colormodelist->insertItem(pm, "Green", CurveView::GREEN);
  pm.fill(Qt::blue);
  PRIVATE(this)->colormodelist->insertItem(pm, "Blue", CurveView::BLUE);
  pm.fill(Qt::white);
  PRIVATE(this)->colormodelist->insertItem(pm, "Alpha", CurveView::ALPHA);
  pm.fill(Qt::gray);
  PRIVATE(this)->colormodelist->insertItem(pm, "RGB", CurveView::LUMINANCE);

  PRIVATE(this)->curvetypetext = new QLabel(controlgroup);
  PRIVATE(this)->curvetypetext->setText("Curve Type: ");
 
  PRIVATE(this)->curvetypelist = new QComboBox(controlgroup);
  PRIVATE(this)->curvetypelist->show();
  PRIVATE(this)->curvetypelist->insertItem("Smooth");
  PRIVATE(this)->curvetypelist->insertItem("Free");
  controlgroup->addSpace(1);

  PRIVATE(this)->constanttext = new QLabel(controlgroup);
  PRIVATE(this)->constanttext->setText(" Set constant value: ");
  PRIVATE(this)->constantvalue = new QLineEdit(controlgroup);
  PRIVATE(this)->constantvalue->setMaxLength(3);
  PRIVATE(this)->constantvalue->setValidator(new QIntValidator(0, 255, this));
  controlgroup->addSpace(1);

  PRIVATE(this)->contupdate = FALSE;
  PRIVATE(this)->instantupdate = new QCheckBox(controlgroup);
  PRIVATE(this)->instantupdate->setChecked(FALSE);
  PRIVATE(this)->applybutton = new QPushButton(this);
  PRIVATE(this)->donebutton = new QPushButton(this);
  PRIVATE(this)->resetbutton = new QPushButton(this);

  PRIVATE(this)->applybutton->setAutoDefault(FALSE);
  PRIVATE(this)->resetbutton->setAutoDefault(FALSE);
  PRIVATE(this)->donebutton->setAutoDefault(FALSE);

  buttonlayout->addWidget(PRIVATE(this)->applybutton);
  buttonlayout->addWidget(PRIVATE(this)->resetbutton);
  buttonlayout->addWidget(PRIVATE(this)->donebutton);

  PRIVATE(this)->instantupdate->setText("Continuous update");
  PRIVATE(this)->applybutton->setText("Apply");
  PRIVATE(this)->donebutton->setText("Done");
  PRIVATE(this)->resetbutton->setText("Reset");

  connect(PRIVATE(this)->colormodelist, SIGNAL(activated(int)), 
          PRIVATE(this)->curveview, SLOT(changeColorMode(int)));
  connect(PRIVATE(this)->curvetypelist, SIGNAL(activated(int)),
          PRIVATE(this), SLOT(changeCurveMode(int)));
  connect(PRIVATE(this)->constantvalue, SIGNAL(returnPressed(void)),
          PRIVATE(this), SLOT(setConstantValue(void)));

  connect(PRIVATE(this)->instantupdate, SIGNAL(clicked()), 
          PRIVATE(this), SLOT(toggleUpdate()));
  connect(PRIVATE(this)->applybutton, SIGNAL(clicked(void)), 
          PRIVATE(this), SLOT(apply(void)));
  connect(PRIVATE(this)->donebutton, SIGNAL(clicked(void)), 
          PRIVATE(this), SLOT(done(void)));
  connect(PRIVATE(this)->curveview, SIGNAL(curveChanged(void)),
          PRIVATE(this), SLOT(updateColorLabels(void)));
  connect(PRIVATE(this)->resetbutton, SIGNAL(clicked()), 
          PRIVATE(this), SLOT(reset(void)));
}

SoQtCurveWidget::~SoQtCurveWidget()
{
  delete this->pimpl;
}

void 
SoQtCurveWidget::getColors(uint8_t * color, int num, Mode mode) const
{
  PRIVATE(this)->curveview->getColors(color, num, mode);
}

void 
SoQtCurveWidget::setColors(uint8_t * color, int num, Mode mode)
{
  switch (mode) {
  case SoQtCurveWidget::LUMINANCE:
  case SoQtCurveWidget::LUMINANCE_ALPHA:
    PRIVATE(this)->colormodelist->setCurrentItem(CurveView::LUMINANCE);
    PRIVATE(this)->curveview->changeColorMode(CurveView::LUMINANCE);
    break;
  default:
    // do nothing
    break;
  }
  PRIVATE(this)->curvetypelist->setCurrentItem(CurveView::FREE);

  PRIVATE(this)->curveview->setColors(color, num, mode);
  if (PRIVATE(this)->callBack) {
    PRIVATE(this)->callBack(PRIVATE(this));
  }
}

void
SoQtCurveWidget::setCallBack(ColorCurve::ChangeCB * cb, void * userData)
{
  PRIVATE(this)->callBack = cb;
  PRIVATE(this)->callbackData = userData;
  PRIVATE(this)->curveview->setCallBack(PRIVATE(this)->curveCallBack, PRIVATE(this));
  PRIVATE(this)->callBack(PRIVATE(this));
}

#undef PRIVATE
#undef PUBLIC


