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
#define PRIVATE(p) (p->pimpl)
#define PUBLIC(p) (p->pub)

#include <qlayout.h>
#include <qimage.h>
#include <qcanvas.h>
#include <qcombobox.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qvaluelist.h>
#include <qfiledialog.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>

#include "gradientp/GradientView.h"
#include "gradientp/SoQtGradientDialogP.h"
#include "SoQtGradientDialog.h"

#include <Inventor/Qt/widgets/moc_SoQtGradientDialogP.icc>

QString * SoQtGradientDialogP::defaultdir = NULL;

SoQtGradientDialogP::SoQtGradientDialogP(SoQtGradientDialog * publ)
{
  PUBLIC(this) = publ;
  this->updatecontinuously = FALSE;
}

void
SoQtGradientDialogP::contupdateClicked()
{
  this->updatecontinuously = this->contupdate->isChecked();
  if (this->changeCallBack) {
    this->changeCallBack(this->gradview->getGradient(), this->changeCallBackData);
  }
}

void
SoQtGradientDialogP::callGradientUpdate()
{  
  if (this->changeCallBack) {
    this->changeCallBack(this->gradview->getGradient(), this->changeCallBackData);
  }
}

void
SoQtGradientDialogP::gradientCallBack(const Gradient & g, void * userData)
{
  SoQtGradientDialogP * thisp = (SoQtGradientDialogP *)userData;
  if (thisp->updatecontinuously) {
    if (thisp->changeCallBack) { thisp->changeCallBack(g, thisp->changeCallBackData); }
  }
}

void
SoQtGradientDialogP::done()
{
  if (this->changeCallBack && !this->updatecontinuously) {
    this->changeCallBack(this->gradview->getGradient(), this->changeCallBackData);
  }
}

void
SoQtGradientDialogP::resetGradient()
{
  this->gradview->setGradient(this->gradientcopy);
  this->saveCurrent();
  if (this->changeCallBack) {
    this->changeCallBack(this->gradview->getGradient(), this->changeCallBackData);
  }
}

void 
SoQtGradientDialogP::loadGradient()
{
  this->filedialog->setMode(QFileDialog::ExistingFile);

  if (this->filedialog->exec()) {
    QString filename = this->filedialog->selectedFile();
    if (!filename.isEmpty()) {
      this->saveCurrent();
      Gradient grad(filename);
      QString dir = this->filedialog->dirPath();

      QString description = filename.remove(0, dir.length() + 1);
      PUBLIC(this)->addGradient(grad, description);

      if (SoQtGradientDialogP::defaultdir == NULL) { // set the static defaultdir to the first dir chosen
        SoQtGradientDialogP::defaultdir = new QString(dir);
      }
    }
  }
}

void 
SoQtGradientDialogP::saveGradient()
{
  this->filedialog->setMode(QFileDialog::AnyFile);

  if (this->filedialog->exec()) {
    QString filename = this->filedialog->selectedFile();
    if (!filename.isEmpty()) {
      if (!filename.contains(this->filetype)) {
        filename.append(this->filetype);
      }
      Gradient grad = this->gradview->getGradient();
      grad.save(filename);
    
      QString dir = this->filedialog->dirPath();
      QString description = filename.remove(0, dir.length() + 1);
      this->gradientlist->changeItem(grad.getImage(60, 16, 32), description, this->old_index);

      if (SoQtGradientDialogP::defaultdir == NULL) { // set the static defaultdir to the first dir chosen
        SoQtGradientDialogP::defaultdir = new QString(dir);
      }
    }
  }
}

void 
SoQtGradientDialogP::chooseGradient(int i)
{
  this->saveCurrent();
  this->gradview->setGradient(this->gradients[i]);
  this->gradientcopy = this->gradients[i];
  this->old_index = i;
  if (this->changeCallBack) {
    this->changeCallBack(this->gradview->getGradient(), this->changeCallBackData);
  }

}

void SoQtGradientDialogP::saveCurrent()
{
  const Gradient & grad = this->gradview->getGradient();
  QString description = this->gradientlist->text(this->old_index);
  this->gradientlist->changeItem(grad.getImage(60, 16, 32), description, this->old_index);
  this->gradients[old_index] = grad;
}

SoQtGradientDialog::SoQtGradientDialog(const Gradient & grad,
                                       QWidget * parent, 
                                       bool modal,
                                       const char* name)
: QDialog(parent, name, modal)
{
  PRIVATE(this) = new SoQtGradientDialogP(this);
  PRIVATE(this)->changeCallBack = NULL;
  PRIVATE(this)->changeCallBackData = NULL;

  QSizePolicy sizepolicy;
  sizepolicy.setVerData(QSizePolicy::MinimumExpanding);
  this->setSizePolicy(sizepolicy);

  PRIVATE(this)->filetype = ".grad";
  PRIVATE(this)->filedialog = new QFileDialog(this);
  if (SoQtGradientDialogP::defaultdir) {
    PRIVATE(this)->filedialog->setDir(*SoQtGradientDialogP::defaultdir);
  }
  
  PRIVATE(this)->gradview = new GradientView(new QCanvas(), grad, this, "GradientView");
  PRIVATE(this)->gradview->setFrameStyle(QFrame::Sunken);

  PRIVATE(this)->gradientlist = new QComboBox(this, "gradientlist");
  PRIVATE(this)->old_index = 0;
  this->addGradient(grad, "no filename specified");
  PRIVATE(this)->gradientlist->hide();

  QGridLayout * toplayout = new QGridLayout(this, 3, 2);
  toplayout->setSpacing(5);
  toplayout->setMargin(10);
  toplayout->addMultiCellWidget(PRIVATE(this)->gradview, 0, 0, 0, 2);

  QHBoxLayout * buttonlayout = new QHBoxLayout();
  toplayout->addLayout(buttonlayout, 2, 0);

  QVBoxLayout * loadsaveLayout = new QVBoxLayout();
  buttonlayout->addLayout(loadsaveLayout);

  QHBoxLayout * contupdatelayout = new QHBoxLayout();
  contupdatelayout->setAlignment(Qt::AlignRight | Qt::AlignBottom);
  toplayout->addLayout(contupdatelayout, 1, 2);

  QHBoxLayout * applyresetLayout = new QHBoxLayout();
  applyresetLayout->setAlignment(Qt::AlignBottom | Qt::AlignRight);
  toplayout->addLayout(applyresetLayout, 2, 2);

  loadsaveLayout->setAlignment(Qt::AlignLeft | Qt::AlignBottom);
  loadsaveLayout->addWidget(PRIVATE(this)->gradientlist, 0, 1);

  QPushButton * loadbutton = new QPushButton(this, "loadbutton");
  loadbutton->setText("Load");
  loadsaveLayout->addWidget(loadbutton, 0, 1);

  QPushButton * savebutton = new QPushButton(this, "savebutton");
  savebutton->setText("Save");
  loadsaveLayout->addWidget(savebutton, 0, 1);

  PRIVATE(this)->contupdate = new QCheckBox(this);
  PRIVATE(this)->contupdate->setChecked(FALSE);

  PRIVATE(this)->contupdatelabel = new QLabel(this);
  PRIVATE(this)->contupdatelabel->setText("Continuous update ");
  PRIVATE(this)->contupdatelabel->setBuddy(PRIVATE(this)->contupdate);
  
  contupdatelayout->addWidget(PRIVATE(this)->contupdatelabel);
  contupdatelayout->addWidget(PRIVATE(this)->contupdate);

  PRIVATE(this)->applybutton = new QPushButton(this);
  PRIVATE(this)->applybutton->setText("Apply");
  applyresetLayout->addWidget(PRIVATE(this)->applybutton);

  QPushButton * resetbutton = new QPushButton(this);
  resetbutton->setText("Reset");
  applyresetLayout->addWidget(resetbutton);

  QPushButton * donebutton = new QPushButton(this);
  donebutton->setText("Done");
  applyresetLayout->addWidget(donebutton);

  connect(loadbutton, SIGNAL(clicked()), PRIVATE(this), SLOT(loadGradient()));
  connect(savebutton, SIGNAL(clicked()), PRIVATE(this), SLOT(saveGradient()));
  connect(PRIVATE(this)->applybutton, SIGNAL(clicked()), PRIVATE(this), SLOT(callGradientUpdate()));
  connect(resetbutton, SIGNAL(clicked()), PRIVATE(this), SLOT(resetGradient()));
  connect(donebutton, SIGNAL(clicked()), PRIVATE(this), SLOT(done()));
  connect(donebutton, SIGNAL(clicked()), this, SLOT(accept()));
  connect(PRIVATE(this)->gradientlist, SIGNAL(activated(int)), PRIVATE(this), SLOT(chooseGradient(int)));
  connect(PRIVATE(this)->contupdate, SIGNAL(clicked()), PRIVATE(this), SLOT(contupdateClicked()));
}

SoQtGradientDialog::~SoQtGradientDialog()
{
  delete this->pimpl;
}

void SoQtGradientDialog::addGradient(const Gradient & grad, QString description)
{
  PRIVATE(this)->gradientcopy = grad;

  if (PRIVATE(this)->changeCallBack) {
    PRIVATE(this)->gradientcopy.setChangeCallback(PRIVATE(this)->gradientCallBack,
                                                  PRIVATE(this));
  }

  PRIVATE(this)->gradients.append(PRIVATE(this)->gradientcopy);
  PRIVATE(this)->gradientlist->insertItem(PRIVATE(this)->gradientcopy.getImage(60, 16, 32), description);
  PRIVATE(this)->old_index = PRIVATE(this)->gradientlist->count() - 1;
  
  PRIVATE(this)->gradientlist->setCurrentItem(PRIVATE(this)->old_index);
  PRIVATE(this)->gradview->setGradient(PRIVATE(this)->gradientcopy);
  PRIVATE(this)->gradientlist->show();
}

const Gradient & SoQtGradientDialog::getGradient() const
{
  return PRIVATE(this)->gradview->getGradient();
}

void SoQtGradientDialog::setDataLimits(float min, float max)
{
  PRIVATE(this)->gradview->setDataLimits(min, max);
}

void SoQtGradientDialog::setChangeCallback(Gradient::ChangeCB * cb, void * userdata)
{
  PRIVATE(this)->changeCallBack = cb;
  PRIVATE(this)->changeCallBackData = userdata;
  PRIVATE(this)->gradview->setChangeCallback(PRIVATE(this)->gradientCallBack, PRIVATE(this));
}

void 
SoQtGradientDialog::setContinuousNotification(SbBool yes)
{
  PRIVATE(this)->contupdate->setChecked(yes);
  PRIVATE(this)->updatecontinuously = yes;
}

SbBool 
SoQtGradientDialog::getContinuousNotification(void) const
{
  return PRIVATE(this)->updatecontinuously;
}

void 
SoQtGradientDialog::alwaysContinuousUpdates(SbBool yes)
{
  PRIVATE(this)->updatecontinuously = yes;
  PRIVATE(this)->contupdate->setChecked(yes);

  if (yes) {
    PRIVATE(this)->contupdate->hide();
    PRIVATE(this)->contupdatelabel->hide();
    PRIVATE(this)->applybutton->hide();
  }
  else {
    PRIVATE(this)->contupdate->show();
    PRIVATE(this)->contupdatelabel->show();
    PRIVATE(this)->applybutton->show();
  }
}

#undef PRIVATE
#undef PUBLIC
