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
#include <qcombobox.h>
#include <qvaluelist.h>
#include <qfiledialog.h>
#include <qpushbutton.h>

#include "gradientp/GradientEditor.h"
#include "SoQtGradientDialog.h"

#include <Inventor/Qt/widgets/moc_SoQtGradientDialog.icc>

class SoQtGradientDialogP
{
public:
  SoQtGradientDialogP(SoQtGradientDialog * publ);
  SoQtGradientDialog * pub;
  GradientEditor * gradEdit;
  QValueList<Gradient> gradients;
  Gradient::ChangeCB * changeCallBack;
  QComboBox * gradientList;
  int old_index;
  void saveCurrent();
};

void SoQtGradientDialogP::saveCurrent()
{
  const Gradient & grad = this->gradEdit->getGradient();
  QString description = this->gradientList->text(this->old_index);
  this->gradientList->changeItem(grad.getImage(60, 16, 32), description, this->old_index);
  this->gradients[old_index] = grad;
}

SoQtGradientDialogP::SoQtGradientDialogP(SoQtGradientDialog * publ)
{
  PUBLIC(this) = publ;
  this->changeCallBack = NULL;
}

SoQtGradientDialog::SoQtGradientDialog(const Gradient & grad,
                                       QWidget * parent, 
                                       bool modal, 
                                       const char* name)
: QDialog(parent, name, modal)
{
  this->pimpl = new SoQtGradientDialogP(this);

  PRIVATE(this)->gradEdit = new GradientEditor(grad, this, "gradEdit");
  PRIVATE(this)->gradientList = new QComboBox(this, "gradientList");
  PRIVATE(this)->old_index = 0;
  this->addGradient(grad, "description");
  PRIVATE(this)->gradientList->hide();

  QVBoxLayout * topLayout = new QVBoxLayout(this);
  topLayout->setMargin(10);
  topLayout->addWidget(PRIVATE(this)->gradEdit);

  QHBoxLayout * buttonLayout = new QHBoxLayout();
  topLayout->addLayout(buttonLayout);

  buttonLayout->setAlignment(Qt::AlignLeft | Qt::AlignBottom);

  QPushButton * loadButton = new QPushButton(this, "loadButton");
  loadButton->setText("Load");
  buttonLayout->addWidget(loadButton, 0, 1);

  QPushButton * saveButton = new QPushButton(this, "saveButton");
  saveButton->setText("Save");
  buttonLayout->addWidget(saveButton, 0, 1);

  buttonLayout->addWidget(PRIVATE(this)->gradientList, 0, 1);

  connect(loadButton, SIGNAL(clicked()), this, SLOT(loadGradient()));
  connect(saveButton, SIGNAL(clicked()), this, SLOT(saveGradient()));

  connect(PRIVATE(this)->gradientList, SIGNAL(activated(int)), this, SLOT(chooseGradient(int)));
  
  connect(PRIVATE(this)->gradEdit, SIGNAL(accepted()), this, SLOT(accept()));
  connect(PRIVATE(this)->gradEdit, SIGNAL(rejected()), this, SLOT(reject()));
}

SoQtGradientDialog::~SoQtGradientDialog()
{
  delete this->pimpl;
}

void SoQtGradientDialog::addGradient(const Gradient & grad, QString description)
{
  Gradient gradientcopy = grad;

  if (PRIVATE(this)->changeCallBack)
    gradientcopy.setChangeCallback(PRIVATE(this)->changeCallBack);

  PRIVATE(this)->gradients.append(gradientcopy);
  PRIVATE(this)->gradientList->insertItem(gradientcopy.getImage(60, 16, 32), description);
  PRIVATE(this)->old_index = PRIVATE(this)->gradientList->count() - 1;
  
  PRIVATE(this)->gradientList->setCurrentItem(PRIVATE(this)->old_index);
  PRIVATE(this)->gradEdit->setGradient(gradientcopy);
  PRIVATE(this)->gradientList->show();
}

void SoQtGradientDialog::loadGradient()
{
  QStringList filenames = 
    QFileDialog::getOpenFileNames("Gradients (*.grad)",
                                  "gradients/",
                                  this,
                                  "Open Gradient Dialog",
                                  "Choose a Gradient to load");
  if (!filenames.isEmpty()) {
    PRIVATE(this)->saveCurrent();
    for (unsigned int i = 0; i < filenames.size(); i++) {
      Gradient grad(filenames[i]);
      this->addGradient(grad, filenames[i]);
    }
  }
}

void SoQtGradientDialog::saveGradient()
{
  QString filename = 
    QFileDialog::getSaveFileName("gradients/",
                                 "*.grad",
                                 this,
                                 "Save Gradient Dialog",
                                 "Choose a filename");

  Gradient grad = PRIVATE(this)->gradEdit->getGradient();
  grad.save(filename);
}

void SoQtGradientDialog::chooseGradient(int i)
{
  PRIVATE(this)->saveCurrent();
  PRIVATE(this)->gradEdit->setGradient(PRIVATE(this)->gradients[i]);
  PRIVATE(this)->old_index = i;
  PRIVATE(this)->gradEdit->updateAll();
}

const Gradient & SoQtGradientDialog::getGradient() const
{
  return PRIVATE(this)->gradEdit->getGradient();
}

void SoQtGradientDialog::setDataLimits(float min, float max)
{
  PRIVATE(this)->gradEdit->setMin(min);
  PRIVATE(this)->gradEdit->setMax(max);
}

void SoQtGradientDialog::setChangeCallback(Gradient::ChangeCB * cb)
{
  PRIVATE(this)->changeCallBack = cb;
  PRIVATE(this)->gradEdit->setChangeCallback(cb);
}

#undef PRIVATE
#undef PUBLIC
