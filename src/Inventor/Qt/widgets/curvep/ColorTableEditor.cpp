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
#include <Inventor/Qt/widgets/SoQtColorTableEditor.h>
#include "SoQtColorTableEditorP.h"
#include <Inventor/Qt/widgets/moc_SoQtColorTableEditorP.icc>

#define PRIVATE(p) p->pimpl
#define PUBLIC(p) p->publ

SoQtColorTableEditorP::SoQtColorTableEditorP(class SoQtColorTableEditor * publ)
{
  this->publ = publ;
}

SoQtColorTableEditorP::~SoQtColorTableEditorP()
{
  delete this->curveview;
}

void
SoQtColorTableEditorP::toggleUpdate()
{
  this->contupdate = this->instantupdate->isChecked();
  if (this->callBack) {
    this->callBack(PUBLIC(this), this->callbackData);
  }
}

void
SoQtColorTableEditorP::apply()
{
  if (this->callBack) {
    this->callBack(PUBLIC(this), this->callbackData);
  }
}

void
SoQtColorTableEditorP::done()
{
  if (!this->contupdate) {
    if (this->callBack) { this->callBack(PUBLIC(this), this->callbackData); }
  }
  PUBLIC(this)->close();
}

void
SoQtColorTableEditorP::reset()
{
  this->curvetypelist->setCurrentItem(CurveView::SMOOTH);
  this->curveview->resetActive();
  if (this->callBack) {
    this->callBack(PUBLIC(this), this->callbackData);
  }
}

void
SoQtColorTableEditorP::changeCurveMode(int i)
{
  this->curveview->changeCurveMode(i);
  if (this->callBack) {
    this->callBack(PUBLIC(this), this->callbackData);
  }
}

void
SoQtColorTableEditorP::curveCallBack(void * userData)
{
  SoQtColorTableEditorP * thisp = (SoQtColorTableEditorP*) userData;
  if (thisp->contupdate && thisp->callBack) {
    thisp->callBack(PUBLIC(thisp), thisp->callbackData);
  }
}

void
SoQtColorTableEditorP::updateColorLabels()
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
SoQtColorTableEditorP::setConstantValue()
{
  this->curveview->changeCurveMode(CurveView::FREE);
  this->curvetypelist->setCurrentItem(CurveView::FREE);
  int value = this->constantvalue->text().toInt();
  this->curveview->setConstantValue(value);
}

SoQtColorTableEditor::SoQtColorTableEditor(int numcolors, QWidget * parent, const char * name)
: QWidget(parent, name)
{
  this->pimpl = new SoQtColorTableEditorP(this);
  PRIVATE(this)->callBack = NULL;
  PRIVATE(this)->mode = SoQtColorTableEditor::RGB;
  
  QSizePolicy sizepolicy;
  sizepolicy.setVerData(QSizePolicy::MinimumExpanding);
  this->setSizePolicy(sizepolicy);

  QGridLayout * toplayout = new QGridLayout(this);
  toplayout->setMargin(10);
  QVBoxLayout * buttonlayout = new QVBoxLayout();

  QGroupBox * controlgroup = new QGroupBox(3, Qt::Horizontal, this);

  PRIVATE(this)->modetext = new QLabel(controlgroup);
  PRIVATE(this)->modetext->setText("Modify channel: ");

  PRIVATE(this)->colormodelist = new QComboBox(controlgroup);
  PRIVATE(this)->colormodelist->show();
  controlgroup->addSpace(1);
  
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
  PRIVATE(this)->constantvalue->setValidator(new QIntValidator(0, numcolors-1, this));
  controlgroup->addSpace(1);

  PRIVATE(this)->contupdate = FALSE;
  PRIVATE(this)->instantupdate = new QCheckBox(controlgroup);
  PRIVATE(this)->instantupdate->setChecked(FALSE);
  
  buttonlayout->setAlignment(Qt::AlignBottom);

  QWidget * curvewidget = new QWidget(this);
  curvewidget->setFixedSize(QSize(numcolors+40,numcolors+40));
  QGridLayout * curvelayout = new QGridLayout(curvewidget, 2, 2, 0);

  PRIVATE(this)->vertgrad = new QLabel(curvewidget);
  PRIVATE(this)->horgrad = new QLabel(curvewidget);
  PRIVATE(this)->vertgrad->setFixedSize(20, numcolors);
  PRIVATE(this)->horgrad->setFixedSize(numcolors, 20); 
  PRIVATE(this)->vertgrad->setFrameStyle(QFrame::Panel | QFrame::Sunken);
  PRIVATE(this)->horgrad->setFrameStyle(QFrame::Panel | QFrame::Sunken);

  curvelayout->addWidget(PRIVATE(this)->vertgrad, 0, 0);
  curvelayout->addWidget(PRIVATE(this)->horgrad, 1, 1);

  PRIVATE(this)->curveview = 
    new CurveView(numcolors, PRIVATE(this)->mode, new QCanvas, curvewidget);
  PRIVATE(this)->curveview->show();

  curvelayout->addWidget(PRIVATE(this)->curveview, 0, 1);

  PRIVATE(this)->vertgrad->setPixmap(PRIVATE(this)->curveview->getGradient(20, numcolors));
  PRIVATE(this)->horgrad->setPixmap(PRIVATE(this)->curveview->getPixmap(numcolors, 20));

  toplayout->addWidget(controlgroup, 0, 0);
  toplayout->addLayout(buttonlayout, 1, 1);
  toplayout->addWidget(curvewidget, 1, 0);

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

  this->setMode(PRIVATE(this)->mode);


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

SoQtColorTableEditor::~SoQtColorTableEditor()
{
  delete PRIVATE(this);
}

void 
SoQtColorTableEditor::getColors(uint8_t * color, int num) const
{
  PRIVATE(this)->curveview->getColors(color, num);
}

void 
SoQtColorTableEditor::setColors(uint8_t * color, int num)
{
  PRIVATE(this)->curvetypelist->setCurrentItem(CurveView::FREE);
  PRIVATE(this)->curveview->setColors(color, num);
  if (PRIVATE(this)->callBack) {
    PRIVATE(this)->callBack(this, PRIVATE(this)->callbackData);
  }
}

void
SoQtColorTableEditor::setChangeCallback(SoQtColorTableEditor::ChangeCB * cb,
                                        void * userData)
{
  PRIVATE(this)->callBack = cb;
  PRIVATE(this)->callbackData = userData;
  PRIVATE(this)->curveview->setCallBack(PRIVATE(this)->curveCallBack, PRIVATE(this));
  if (cb) { cb(this, userData); }
}

SoQtColorTableEditor::Mode
SoQtColorTableEditor::getMode() const
{
  return PRIVATE(this)->mode;
}

void
SoQtColorTableEditor::setMode(Mode mode) 
{
  QPixmap pm(16,16);
  PRIVATE(this)->mode = mode;
  PRIVATE(this)->curveview->setMode(mode);

  PRIVATE(this)->colormodelist->clear();

  switch(mode) {
  case SoQtColorTableEditor::LUMINANCE:
  case SoQtColorTableEditor::LUMINANCE_ALPHA:
    pm.fill(Qt::gray);
    PRIVATE(this)->colormodelist->insertItem(pm, "Gray");
    break;

  case SoQtColorTableEditor::RGB:
  case SoQtColorTableEditor::RGBA:
    pm.fill(Qt::red);
    PRIVATE(this)->colormodelist->insertItem(pm, "Red");
    pm.fill(Qt::green);
    PRIVATE(this)->colormodelist->insertItem(pm, "Green");
    pm.fill(Qt::blue);
    PRIVATE(this)->colormodelist->insertItem(pm, "Blue");
    break;
  }

  if ((mode == SoQtColorTableEditor::LUMINANCE_ALPHA) ||
      (mode == SoQtColorTableEditor::RGBA)) {
    pm.fill(Qt::white);
    PRIVATE(this)->colormodelist->insertItem(pm, "Alpha");
  }
}

#undef PRIVATE
#undef PUBLIC


