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

#include <stdlib.h>
#include <assert.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <qvaluelist.h>
#include <qpopupmenu.h>
#include <qcolordialog.h>
#include <Inventor/Qt/widgets/Gradient.h>
#include "GradientView.h"
#include "TickMark.h"
#include "ImageItem.h"

#include <Inventor/Qt/widgets/moc_GradientView.icc>


GradientView::GradientView(QCanvas * c,
                           const Gradient & g,
                           QWidget * parent, 
                           const char * name,
                           WFlags f)
                           
  : QCanvasView(c, parent, name, f)
{
  this->canvas = c;
  this->grad = g;
  this->gradItem = NULL;
  this->selectionMarker = NULL;
  this->selectedMark = NULL;
  this->movingItem = NULL;
  this->menu = NULL;
  this->startIndex = 0;
  this->endIndex = 1;
  this->canvas->setBackgroundColor(Qt::lightGray);

  connect(this, SIGNAL(viewChanged()), this, SLOT(updateView()));
  connect(this, SIGNAL(ticksChanged()), this, SLOT(updateTicks()));

  this->updateTicks();
  this->updateView();
}

GradientView::~GradientView()
{
  delete this->canvas;
  delete this->gradItem;
  delete this->selectionMarker;
  delete this->menu;
  delete this->movingItem;
  delete this->selectedMark;
}

void GradientView::viewportResizeEvent(QResizeEvent * e)
{
  this->canvas->resize(e->size().width(), this->canvas->height());
  this->updateTicks();
  emit this->viewChanged();
}

void GradientView::updateView()
{
  int width = this->canvas->width();
  int height = this->canvas->height();

  QImage gradImage = this->grad.getImage(width, height-10, 32);

  if (this->gradItem)
    delete this->gradItem;
  this->gradItem = new ImageItem(gradImage, this->canvas);
  this->gradItem->show();

  int selectStart = (int) (this->tickMarks[this->startIndex]->x());
  int selectEnd = (int) (this->tickMarks[this->endIndex]->x());

  QImage selectedImage(selectEnd - selectStart, 10, 32);
  selectedImage.fill(QColor(100,100,245).rgb());

  if (this->selectionMarker)
    delete this->selectionMarker;

  this->selectionMarker = new ImageItem(selectedImage, this->canvas);
  this->selectionMarker->moveBy(selectStart, height-10);
  this->selectionMarker->setZ(2);
  this->selectionMarker->show();

  this->canvas->update();
}

void GradientView::contentsMousePressEvent(QMouseEvent * e)
{
  QPoint p = inverseWorldMatrix().map(e->pos());
 
  switch (e->button()) {
  case Qt::LeftButton: 
    {
      QValueList<TickMark *>::Iterator it = this->tickMarks.begin();
      for (; it != this->tickMarks.end(); ++it) {
        if ((*it)->hit(p)) {
          this->movingItem = (*it);
          this->moving_start = p;
          this->unselectAll();
          this->selectedMark = this->movingItem;
          this->selectedMark->setBrush(Qt::blue);
          emit this->viewChanged();
          return;
        } else {
          this->startIndex = -1;
          while (this->tickMarks[++this->startIndex]->x() < p.x());
          this->startIndex--;
          this->endIndex = this->startIndex + 1;
          emit this->viewChanged();
        }
      }
      break;
    }
  case Qt::RightButton: 
    this->buildMenu();
    if (this->menu->exec(e->globalPos())) {
      delete this->menu;
      this->menu = NULL;
    }
    break;
  default:
    // do nothing
    break;
  }
  this->movingItem = 0;
}

void GradientView::contentsMouseMoveEvent(QMouseEvent * e)
{
  QPoint p = inverseWorldMatrix().map(e->pos());
  int x = p.x();

  if (this->movingItem && 
      (this->movingItem != this->tickMarks[0]) &&  
      (this->movingItem != this->tickMarks[this->tickMarks.size()-1]))
  {   
    int index = this->tickMarks.findIndex(this->movingItem);
    if (index > 0) {
      assert((index < (int)this->tickMarks.size() - 1) && (index >= 1));

      TickMark * left = this->tickMarks[index - 1];
      TickMark * right = this->tickMarks[index + 1];

      int movex = x - this->moving_start.x();
      int newpos = (int) (this->movingItem->x() + movex);

      if ((newpos >= left->x()) && newpos <= right->x()) {
        this->movingItem->moveBy(movex, 0);
        this->moving_start = QPoint(x, p.y());

        float t = this->movingItem->getPos();
        this->grad.moveTick(index, t);
    
        emit this->viewChanged();
      }
    }
  }
}

void GradientView::keyPressEvent(QKeyEvent * e)
{
  switch (e->key()) {
  case Qt::Key_Delete:
    this->deleteTick();
    break;
  default: 
    break;
  }
}

float GradientView::getSelectedPos()
{
  if (this->selectedMark) {
    int i = this->tickMarks.findIndex(this->selectedMark);
    if (i > 0)
      return this->grad.getParameter(i);
  }
  return 0;
}

void GradientView::unselectAll()
{
  QValueList<TickMark*>::Iterator it = this->tickMarks.begin();
  for (; it != tickMarks.end(); ++it) {
    (*it)->setBrush(Qt::black);
  }
  this->selectedMark = NULL;
}


void GradientView::setGradient(const Gradient & grad)
{
  this->grad = grad;
  this->selectedMark = NULL;
  this->startIndex = 0;
  this->endIndex = 1;
  this->updateTicks();
  emit this->viewChanged();
}

const Gradient & GradientView::getGradient() const
{
  return this->grad;
}

void GradientView::centerTick()
{
  unsigned int i = this->tickMarks.findIndex(this->selectedMark);
  
  if ((i > 0) && (i < this->tickMarks.size() - 1)) {

    float left = (float)this->tickMarks[i-1]->x();
    float right = (float)this->tickMarks[i+1]->x();
    float center = (right - left) / 2.0f + left;

    this->grad.moveTick(i, center / (float)this->canvas->width());

    this->updateTicks();
    emit this->viewChanged();
  }
}

TickMark * GradientView::newTick(int x)
{
  TickMark* i = new TickMark(this->canvas);
  i->setBrush(QColor(0,0,0));
  i->move(0, this->canvas->height()-15);
  i->setZ(3);
  i->setX(x);
  i->show();
  return i;
}

void GradientView::insertTick()
{
  // x == midpoint of selected section
  float selectStart = this->tickMarks[this->startIndex]->x();
  float selectEnd = this->tickMarks[this->endIndex]->x();

  float x = ((selectEnd - selectStart)/2.0f
             + selectStart);

  float t = x / (float)this->canvas->width();
  int i = this->grad.insertTick(t);

  QValueList<TickMark*>::Iterator it = this->tickMarks.begin();
  // the += operator wasn't available until Qt 3.1.0. Just iterate
  // and use ++. pederb, 2003-09-22
  for (int j = 0; j < i; j++) {
    it++;
  }
  this->tickMarks.insert(it, this->newTick(x));
  this->endIndex = i;
  this->updateTicks();
  emit this->viewChanged();
}

void GradientView::updateTicks()
{
  QValueList<TickMark*>::Iterator it = this->tickMarks.begin();
  for (; it != tickMarks.end(); ++it) {
      delete (*it);
  }

  this->tickMarks.clear();

  for (int i = 0; i < this->grad.numTicks(); i++) {
    float t = this->grad.getParameter(i);
    int x = (int) (t * (float)this->canvas->width() + 0.5f);
    TickMark * tick = this->newTick(x);
    this->tickMarks.append(tick);
  }
  this->tickMarks[0]->setVisible(FALSE);
  this->tickMarks[this->tickMarks.size()-1]->setVisible(FALSE);
}

void GradientView::deleteTick()
{
  int i = (int) this->tickMarks.findIndex(this->selectedMark);
  this->selectedMark = NULL;

  if ((i > 0) && (i < (int) this->tickMarks.size() - 1)) {
    this->grad.removeTick(i);
    this->updateTicks();
    
    if (this->endIndex == i) {
      this->endIndex = i+1;
      this->startIndex = i;
    }

    if (this->startIndex == i) {
      this->startIndex = i-1;
      this->endIndex = i;
    }
    emit this->viewChanged();
  }
}

void GradientView::setColorRight()
{
  this->grad.setColor(this->endIndex, TRUE, this->rightcolor);
  emit this->viewChanged();
}

void GradientView::setColorLeft()
{
  this->grad.setColor(this->startIndex, FALSE, this->leftcolor);
  emit this->viewChanged();
}

void GradientView::chooseColorLeft()
{  
  QRgb initial = grad.getColor(this->startIndex, FALSE);
  this->leftcolor = QColorDialog::getRgba(initial);
  if (this->leftcolor != initial) {
    this->setColorLeft();
  }
}

void GradientView::chooseColorRight()
{  
  QRgb initial = this->grad.getColor(this->endIndex, TRUE);
  this->rightcolor = QColorDialog::getRgba(initial);
  if (this->rightcolor != initial) {
    this->setColorRight();
  }
}

void GradientView::setChangeCallback(changeCB * cb)
{
  this->grad.setChangeCallback(cb);
}

// FIXME: instead of building the menu each time, simply use QPopupMenu::changeItem
// to change the color pixmaps. 20030925 frodo.
void GradientView::buildMenu()
{
  if (!this->menu)
    this->menu = new QPopupMenu(this);

  int id;
  
  QPixmap left(16,16);
  left.fill(this->grad.getColor(this->startIndex, FALSE));
  id = menu->insertItem(left, "Left endpoints color", this, SLOT(chooseColorLeft()));

  QPixmap pmleft(16,16);
  this->leftcolor = grad.getColor(this->startIndex, TRUE);
 
  pmleft.fill(this->leftcolor);
  id = menu->insertItem(pmleft, "Same as left neighbor's right endpoint", this, SLOT(setColorLeft()));
  if (this->grad.leftEqualsRight(this->startIndex)) menu->setItemEnabled(id, FALSE);

  menu->insertSeparator();

  QPixmap right(16,16);
  right.fill(this->grad.getColor(this->endIndex, TRUE));
  id = menu->insertItem(right, "Right endpoints color", this, SLOT(chooseColorRight()));

  QPixmap pmright(16,16);
  this->rightcolor = this->grad.getColor(this->endIndex, FALSE);

  pmright.fill(this->rightcolor);
  id = menu->insertItem(pmright, "Same as right neighbor's left endpoint", this, SLOT(setColorRight()));
  if (this->grad.leftEqualsRight(this->endIndex)) menu->setItemEnabled(id, FALSE);

  menu->insertSeparator();
  id = menu->insertItem("Insert tick", this, SLOT(insertTick()));

  bool tickSelected = (this->selectedMark != NULL);

  id = menu->insertItem("Center tick", this, SLOT(centerTick()));
  if (!tickSelected) menu->setItemEnabled(id, FALSE);
  
  id = menu->insertItem("Delete tick", this, SLOT(deleteTick()));
  if (!tickSelected) menu->setItemEnabled(id, FALSE);
}
