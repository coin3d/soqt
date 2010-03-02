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

#include <qlayout.h>
#include <qbutton.h>
#include <qchkbox.h>
#include <qradiobt.h>
#include <qlabel.h>
#include <qbttngrp.h>
#include <qpopmenu.h>
#include <qpushbt.h>
#include <qmenubar.h>
#include <qgl.h>

#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/fields/SoField.h>
#include <Inventor/fields/SoMFColor.h>

#include <soqtdefs.h>
#include <Inventor/Qt/SoQtColorSlider.h>
#include <Inventor/Qt/SoGLMaterialSphere.h>
#include <Inventor/Qt/QColorSelection.h>
#include <Inventor/Qt/SoQtMaterialList.h>

#include <Inventor/Qt/SoQtMaterialEditor.h>

static char * colorStrings[] = {
  "Ambient", "Diffuse", "Specular", "Emission"
};

#ifndef _GCC_
# define true TRUE
# define false FALSE
#endif

#define colors2QColor(index)                                            \
    QColor((int)(colors[index]->getValues(0)->getValue()[0] * 255.0),       \
        (int)(colors[index]->getValues(0)->getValue()[1] * 255.0),              \
        (int) (colors[index]->getValues(0)->getValue()[2] * 255.0))

SoQtMaterialEditor::SoQtMaterialEditor(QWidget *parent, const char *name, SbBool buildInsideParent) : SoQtComponent(parent)
{
  materialList = NULL;

  mgrWidget = new QWidget(buildInsideParent ? parent : (QWidget*) NULL, name);
  widget = mgrWidget;

  QHBoxLayout* hbox = new QHBoxLayout(widget, 5);

  /*
   *  The Menu
   */
  menu = new QPopupMenu;

  menu->insertItem("Material List", this, SLOT(material_list()));
  menu->insertSeparator();
  contId = menu->insertItem("Continuous", this, SLOT(continuous()));
  menu->setItemChecked(contId, true);
  manuId = menu->insertItem("Manual", this, SLOT(manual()));

  QMenuBar* bar = new QMenuBar(widget);
  bar->insertItem("&Edit", menu);

  hbox->setMenuBar(bar);

  /*
   *  The Sphere and Accept-button
   */
  QVBoxLayout *bbox = new QVBoxLayout/*(widget)*/;
  hbox->addLayout(bbox);
  QFrame* frame = new QFrame(widget, NULL, QFrame::Panel | QFrame::Sunken);
//  frame->setMidLineWidth(2);
//  frame->setLineWidth(3);
  frame->setBackgroundColor(QColor("blue"));

  ball = new SoGLMaterialSphere(frame);
  ball->setFixedSize(150, 150);
  frame->setFixedSize(ball->size());

//  frame->setMinimumSize(frame->sizeHint());

  bbox->addStretch(5);
  bbox->addWidget(frame);

  acceptButton = new QPushButton("Accept", widget);
  acceptButton->setFixedSize(acceptButton->sizeHint());
  connect(acceptButton, SIGNAL(pressed()), this, SLOT(accept()));


  bbox->addStretch(4);
  bbox->addWidget(acceptButton);
  bbox->addStretch(5);

  acceptButton->hide();



  /*
   *  Sliders and checkboxes
   */

#if 0
  QGridLayout *grid;
  grid = new QGridLayout(7, 3, 5);
#else
  QVBoxLayout *grid;
  grid = new QVBoxLayout(widget, 0, -1, "grid");
#endif

#if 0
  grid->setColStretch(0, 1);
  grid->setColStretch(1, 1);
  grid->setColStretch(2, 10);
#endif

  QLabel * lab =  new QLabel("Edit Color", widget);
  lab->setMinimumSize(lab->sizeHint());
#if 0
  grid->addMultiCellWidget(lab, 0, 0, 0, 2);
#else
  grid->addWidget(lab, AlignLeft);
#endif

  QButtonGroup *buttonGroup;
  buttonGroup = new QButtonGroup;

#if 0
  radioButtons[0] = new QRadioButton(widget);
  radioButtons[0]->setMinimumSize(radioButtons[0]->sizeHint());
  grid->addWidget(radioButtons[0], 1, 0);
  buttonGroup->insert(radioButtons[0]);

  radioButtons[1] = new QRadioButton(widget);
  radioButtons[1]->setMinimumSize(radioButtons[1]->sizeHint());
  grid->addWidget(radioButtons[1], 2, 0);
  buttonGroup->insert(radioButtons[1]);

  radioButtons[2] = new QRadioButton(widget);
  radioButtons[2]->setMinimumSize(radioButtons[2]->sizeHint());
  grid->addWidget(radioButtons[2], 3, 0);
  buttonGroup->insert(radioButtons[2]);

  radioButtons[3] = new QRadioButton(widget);
  radioButtons[3]->setMinimumSize(radioButtons[3]->sizeHint());
  grid->addWidget(radioButtons[3], 4, 0);
  buttonGroup->insert(radioButtons[3]);
#else
  for (int i = 0; i < 4; i++) {
    radioButtons[i] = new QRadioButton(widget);
    radioButtons[i]->setMinimumSize(radioButtons[i]->sizeHint());
    buttonGroup->insert(radioButtons[i]);
#if 0
    grid->addWidget(radioButtons[i], i + 1, 0);
#endif
  }
#endif


#if 0
  checkButtons[0] = new QCheckBox(widget);
  checkButtons[0]->setMinimumSize(checkButtons[0]->sizeHint());
  grid->addWidget(checkButtons[0], 1, 1);
  checkButtons[1] = new QCheckBox(widget);
  checkButtons[1]->setMinimumSize(checkButtons[1]->sizeHint());
  grid->addWidget(checkButtons[1], 2, 1);
  checkButtons[2] = new QCheckBox(widget);
  checkButtons[2]->setMinimumSize(checkButtons[2]->sizeHint());
  grid->addWidget(checkButtons[2], 3, 1);
  checkButtons[3] = new QCheckBox(widget);
  checkButtons[3]->setMinimumSize(checkButtons[3]->sizeHint());
  grid->addWidget(checkButtons[3], 4, 1);
#else
  for (int i = 0; i < 4; i++) {
    checkButtons[i] = new QCheckBox(widget);
    checkButtons[i]->setMinimumSize(checkButtons[i]->sizeHint());
#if 0
    grid->addWidget(checkButtons[i], i+1, 1);
#endif
  }
#endif


  sliders[0] = new _SoQtColorSlider(0, 100, widget, "Amb:");
  sliders[0]->setMinimumSize( sliders[0]->sizeHint());
  sliders[0]->setFixedHeight(sliders[0]->sizeHint().height());
  sliders[1] = new _SoQtColorSlider(0, 100, widget, "Diff:");
  sliders[1]->setMinimumSize( sliders[1]->sizeHint());
  sliders[1]->setFixedHeight(sliders[1]->sizeHint().height());
  sliders[2] = new _SoQtColorSlider(0, 100, widget, "Spec:");
  sliders[2]->setMinimumSize( sliders[2]->sizeHint());
  sliders[2]->setFixedHeight(sliders[2]->sizeHint().height());
  sliders[3] = new _SoQtColorSlider(0, 100, widget, "Emis:");
  sliders[3]->setMinimumSize( sliders[3]->sizeHint());
  sliders[3]->setFixedHeight(sliders[3]->sizeHint().height());
  sliders[4] = new _SoQtColorSlider(0, 100, widget, "Shininess:");
  sliders[4]->setMinimumSize( sliders[0]->sizeHint());
  sliders[4]->setFixedHeight(sliders[0]->height());
  sliders[5] = new _SoQtColorSlider(0, 100, widget, "Transp:");
  sliders[5]->setMinimumSize( sliders[0]->sizeHint());
  sliders[5]->setFixedHeight(sliders[0]->height());

#if 0
  grid->addWidget(sliders[0], 1, 2);
  grid->addWidget(sliders[1], 2, 2);
  grid->addWidget(sliders[2], 3, 2);
  grid->addWidget(sliders[3], 4, 2);
  grid->addWidget(sliders[4], 5, 2);
  grid->addWidget(sliders[5], 6, 2);
#endif
  QHBoxLayout *tempBox;
  for (int i = 0; i < 4; i++) {
    tempBox = new QHBoxLayout(5, "tempBox");
    grid->addLayout(tempBox, 10);
    tempBox->addWidget(radioButtons[i]);
    tempBox->addWidget(checkButtons[i]);
    tempBox->addWidget(sliders[i], 10, AlignRight);
  }
  grid->addStretch(5);
  tempBox = new QHBoxLayout(5, "lastBox");
  grid->addLayout(tempBox, 10);
  tempBox->addStretch(1);
  tempBox->addWidget(sliders[4], 10, AlignRight);
  tempBox = new QHBoxLayout(5, "lastBox");
  grid->addLayout(tempBox, 10);
  tempBox->addStretch(1);
  tempBox->addWidget(sliders[5], 10, AlignRight);

  hbox->addLayout(grid, 10);
  hbox->activate();

  widget->setMinimumHeight(sliders[0]->sizeHint().height() * 6 + lab->sizeHint().height());
  widget->setMinimumWidth(150 + lab->width());

  colorSelection = new QColorSelection;
  colorSelection->hide();
  QObject::connect(colorSelection, SIGNAL(closed()), this, SLOT(clearAllButtons()));

  for (int i = 0; i < 4; i++) {
    QObject::connect(radioButtons[i], SIGNAL(clicked()), this, SLOT(rButtonPressed()));
    QObject::connect(checkButtons[i], SIGNAL(clicked()), this, SLOT(cButtonPressed()));
  }

  QObject::connect(colorSelection, SIGNAL(colorChanged(QColor&)), this, SLOT(colorChanged(QColor&)));

  connectUpdaters();

  dummyMaterial = new SoMaterial;
//  dummyMaterial->setToDefaults(); <--- causes a segfault
  attach(dummyMaterial);

}

SoQtMaterialEditor::~SoQtMaterialEditor()
{
//  delete dummyMaterial;
}

const char* SoQtMaterialEditor::componentClassName() const
{
  return "SoQtMaterialEditor";
}

void SoQtMaterialEditor::material_list()
{
  menu->hide();
  if (materialList == NULL) {
    materialList = new SoQtMaterialList;
    QObject::connect(materialList, SIGNAL(materialSelected(SoMaterial *)),
        this, SLOT(setMaterial(SoMaterial *)));
  }
  materialList->show();
}

void SoQtMaterialEditor::continuous()
{
  menu->hide();
  if (updatefreq == SoQtMaterialEditor::CONTINUOUS) return;
  updatefreq = SoQtMaterialEditor::CONTINUOUS;

  menu->setItemChecked(contId, true);
  menu->setItemChecked(manuId, false);
  acceptButton->hide();
  connectUpdaters();
}

void SoQtMaterialEditor::manual()
{
  menu->hide();
  if (updatefreq == SoQtMaterialEditor::AFTER_ACCEPT) return;
  updatefreq = SoQtMaterialEditor::AFTER_ACCEPT;
  if (menu->isItemChecked(manuId)) return;
  menu->setItemChecked(contId, false);
  menu->setItemChecked(manuId, true);
  acceptButton->show();
  connectUpdaters(false);
}

void SoQtMaterialEditor::accept()
{
  ball->setAmbient(sliders[0]->getValue() / 100.0);
  ball->setDiffuse(sliders[1]->getValue() / 100.0);
  ball->setSpecular(sliders[2]->getValue() / 100.0);
  ball->setEmission(sliders[3]->getValue() / 100.0);
  ball->setShininess(sliders[4]->getValue() / 100.0);
  ball->setTransparency(sliders[5]->getValue() / 100.0);
  emit materialChanged();
}

void SoQtMaterialEditor::menu_popup()
{
  QPoint pos;
  pos = menuButton->mapToGlobal(menuButton->pos());
  pos.setY(pos.y() + menuButton->height());
  menu->popup(pos);
}

void SoQtMaterialEditor::attach(SoMaterial *mat, int index)
{
  printf("attach %p\n", mat);
  material = mat;
  printf("ball->setMaterial...");
  ball->setMaterial(material);
  printf("done\n");
  colors[0] = &(material->ambientColor);
  colors[1] = &(material->diffuseColor);
  colors[2] = &(material->specularColor);
  colors[3] = &(material->emissiveColor);

  ball->setRepaint(false);
  printf("sliders - setvalues...");
  sliders[0]->setValue((int) (colors[0]->getValues(0)->getValue()[0] * 100.0f));
  sliders[1]->setValue((int) (colors[1]->getValues(0)->getValue()[0] * 100.0f));
  sliders[2]->setValue((int) (colors[2]->getValues(0)->getValue()[0] * 100.0f));
  sliders[3]->setValue((int) (colors[3]->getValues(0)->getValue()[0] * 100.0f));
  sliders[4]->setValue((int) (material->shininess[0] * 100.0f));
  printf("transparency = %f\n", material->transparency[0]);
  if (material != dummyMaterial) {
  printf("\tsetValue sliders[5]...");
  sliders[5]->setValue((int) (material->transparency[0] * 100.0f));
  printf("\tdone\n");
  }
  printf("done\n");
//  ball->setRepaint(true);
//  ball->repaintSphere();

  printf("sliders - setcolor...");
  sliders[0]->setColor(colors2QColor(0));
  sliders[1]->setColor(colors2QColor(1));
  sliders[2]->setColor(colors2QColor(2));
  sliders[3]->setColor(colors2QColor(3));
  printf("done\n");
}

void SoQtMaterialEditor::detach()
{
  attach(dummyMaterial);
}

SbBool SoQtMaterialEditor::isAttached()
{
  if (material == dummyMaterial) return false;
  else return true;
}

void SoQtMaterialEditor::setUpdateFrequency(
        SoQtMaterialEditor::UpdateFrequency freq)
{
  switch (freq) {
    case SoQtMaterialEditor::CONTINUOUS:
        continuous();
        break;
    case SoQtMaterialEditor::AFTER_ACCEPT:
        manual();
        break;
  }
}

SoQtMaterialEditor::UpdateFrequency SoQtMaterialEditor::getUpdateFrequency()
{
  return updatefreq;
}

void SoQtMaterialEditor::setMaterial(SoMaterial *mat)
{
  printf("setMaterial\n");
  attach(mat);
}

const SoMaterial& SoQtMaterialEditor::getMaterial() const
{
  return *material;
}


void SoQtMaterialEditor::rButtonPressed()
{
  int i;
  for (i = 0; i < 4; i++) {
    if (((QRadioButton*)(radioButtons[i]))->isChecked()) break;
  }
  if (i == 4) {
    /*
     *  No button is checked, remove dialog if present.
     */
    if (colorSelection->isVisible()) colorSelection->hide();
    clearAllButtons();
  } else {
    for (int j = 0; j < 4; j++) {
      checkButtons[j]->setChecked(j == i ? true : false);
    }
    colorSelection->setType(colorStrings[i]);
//    colorSelection->setColor(QColor((int)colors[i]->getValues(0)->getValue()[0] * 255, (int)colors[i]->getValues(0)->getValue()[1] * 255, (int) colors[i]->getValues(0)->getValue()[2] * 255));
        printf("color2QColor\n");                                       \
    colorSelection->setColor(colors2QColor(i));
    colorSelection->show();
  }
}

void SoQtMaterialEditor::cButtonPressed()
{
  bool pressed[] = { false, false, false, false };
  int numPressed = 0;
  int i;
  for (i = 0; i < 4; i++) {
    if (checkButtons[i]->isChecked()) {
      pressed[i] = true;
      numPressed++;
    }
  }
  if (numPressed == 0) {
    clearAllButtons();
    colorSelection->hide();
  } else if (numPressed == 1) {
    for (i = 0; pressed[i] == false; i++);
    radioButtons[i]->setChecked(true);
    if (colorSelection->isVisible() == false) colorSelection->show();
    colorSelection->setType(colorStrings[i]);
        printf("color2QColor\n");                                       \
    colorSelection->setColor(colors2QColor(i));
  } else {
    char colorString[41];
    int length = 0;
    for (i = 0; i < 4; i++) {
      radioButtons[i]->setChecked(false);
      if (pressed[i]) {
#ifdef linux
        snprintf(colorString + length, 40 - length, "%s", colorStrings[i]);
#else
        sprintf(colorString + length, "%s", colorStrings[i]);
#endif
        length += strlen(colorStrings[i]);
      }
      colorString[length] = '\0';
    }
    colorSelection->setType(colorString);
    if (colorSelection->isVisible() == false) colorSelection->show();
  }
}

void SoQtMaterialEditor::clearAllButtons()
{
  for (int i = 0; i < 4; i++) {
    radioButtons[i]->setChecked(false);
    checkButtons[i]->setChecked(false);
  }
}

void SoQtMaterialEditor::colorChanged(QColor &col)
{
  printf("colorChanged(%i, %i, %i)\n", col.red(), col.green(), col.blue());
  bool pressed[] = { false, false, false, false };
  for (int i = 0; i < 4; i++) {
    if (checkButtons[i]->isChecked()) {
      pressed[i] = true;
      float cols[3];
      float factor;
      cols[0] = (float) col.red() / 255.0f;
      cols[1] = (float) col.green() / 255.0f;
      cols[2] = (float) col.blue() / 255.0f;
      printf("colors[%i] = %f, %f, %f\n", i, cols[0], cols[1], cols[2]);
#if 0
      factor = cols[0];
      if (factor == 0.0f) {
        factor = 1.0f;
        cols[0] = 0.0f;
      } else {
        cols[0] = 1.0f;
        cols[1] = cols[1] / factor;
        cols[2] = cols[2] / factor;
      }
      sliders[i]->setValue((int)(factor * 100.f));
#endif
      printf("cols[%i] = %f, %f, %f, factor = %f\n", i, cols[0], cols[1], cols[2], factor);
      colors[i]->setValue(cols);
      sliders[i]->setColor(col);
    }
  }
  emit materialChanged();
}

void SoQtMaterialEditor::connectUpdaters(bool connect)
{
  bool (*connectFunc) (const QObject *, const char *, const QObject *, const char*);

  if (connect) connectFunc = &QObject::connect;
  else connectFunc = &QObject::disconnect;
  (*connectFunc)(sliders[0], SIGNAL(valueChanged(float)), ball, SLOT(setAmbient(float)));
  (*connectFunc)(sliders[1], SIGNAL(valueChanged(float)), ball, SLOT(setDiffuse(float)));
  (*connectFunc)(sliders[2], SIGNAL(valueChanged(float)), ball, SLOT(setSpecular(float)));
  (*connectFunc)(sliders[3], SIGNAL(valueChanged(float)), ball, SLOT(setEmission(float)));
  (*connectFunc)(sliders[4], SIGNAL(valueChanged(float)), ball, SLOT(setShininess(float)));
  (*connectFunc)(sliders[5], SIGNAL(valueChanged(float)), ball, SLOT(setTransparency(float)));

  (*connectFunc)(sliders[0], SIGNAL(valueChanged(float)), this, SIGNAL(materialChanged()));
  (*connectFunc)(sliders[1], SIGNAL(valueChanged(float)), this, SIGNAL(materialChanged()));
  (*connectFunc)(sliders[2], SIGNAL(valueChanged(float)), this, SIGNAL(materialChanged()));
  (*connectFunc)(sliders[3], SIGNAL(valueChanged(float)), this, SIGNAL(materialChanged()));
  (*connectFunc)(sliders[4], SIGNAL(valueChanged(float)), this, SIGNAL(materialChanged()));
  (*connectFunc)(sliders[5], SIGNAL(valueChanged(float)), this, SIGNAL(materialChanged()));
  (*connectFunc)(this, SIGNAL(materialChanged()), ball, SLOT(repaintSphere()));
}
