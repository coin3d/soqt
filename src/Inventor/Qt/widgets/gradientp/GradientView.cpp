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
#include "Gradient.h"
#include "GradientView.h"
#include "ImageItem.h"
#include "TickMark.h"

#include <Inventor/Qt/widgets/moc_GradientView.icc>


GradientView::GradientView(QCanvas * c, 
                           Gradient * g, 
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
  delete this->grad;
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

  QImage gradImage(width, height-10, 32);
  gradImage.fill(0);

  // FIXME: this can be made more efficient, but i'll leave it
  // for now since the performance seems to be acceptable. 20030925 frodo.

  QRgb * colors = new QRgb[width];
  this->grad->getColorArray(colors, width);
  for (int i = 0; i < width; i ++) {
    float alpha = float(qAlpha(colors[i])) / 255.0f;
    for (int j = 0; j < height - 10; j++) {
      // produces a checkerboard pattern of black and white
      QRgb background = 0;
      if (((i & 0x8) == 0) ^ ((j & 0x8) == 0)) {
        background = 255;
      }
      int bg = int((1.0f - alpha) * float(background));
      int r = alpha * float(qRed(colors[i]) + bg);
      int g = alpha * float(qGreen(colors[i]) + bg);
      int b = alpha * float(qBlue(colors[i]) + bg);
      gradImage.setPixel(i, j, qRgb(r, g, b));
    }
  }
  delete [] colors;

  if (this->gradItem)
    delete this->gradItem;
  this->gradItem = new ImageItem(gradImage, this->canvas);

  this->gradItem->show();

  int selectStart = (int) this->tickMarks[this->startIndex]->x();
  int selectEnd = (int) this->tickMarks[this->endIndex]->x();

  QImage selectedImage(selectEnd - selectStart, 10, 32);
  selectedImage.fill(QColor(100,100,245).rgb());

  if (this->selectionMarker)
    delete this->selectionMarker;

  this->selectionMarker = new ImageItem(selectedImage, this->canvas);
  this->selectionMarker->moveBy(selectStart, height-10);
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
          SbBool selected = this->movingItem->isSelected();
          this->unselectAll();
          this->movingItem->setZ(3);
          this->selectedMark = this->movingItem;
          this->selectedMark->setSelected(selected ? FALSE : TRUE);
          this->selectedMark->setBrush(QColor(0,0,255));
          this->canvas->update();
          return;
        } else {
          this->startIndex = -1;
          while (this->tickMarks[++this->startIndex]->x() < p.x());
          this->startIndex--;
          this->endIndex = this->startIndex + 1;
          
          this->tickMarks[this->startIndex]->isStart = TRUE;
          this->tickMarks[this->endIndex]->isEnd = TRUE;
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

void GradientView::contentsMouseReleaseEvent(QMouseEvent * e)
{
  QValueList<TickMark*>::Iterator it = this->tickMarks.begin();
  for (; it != this->tickMarks.end(); ++it) {
    if((*it) != this->movingItem)
      (*it)->setZ(2);
    else (*it)->setZ(1);
  }
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
          this->grad->moveTick(index, t);
      
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
      return this->grad->getParameter(i);
  }
  return 0;
}

void GradientView::unselectAll()
{
  QValueList<TickMark*>::Iterator it = this->tickMarks.begin();
  for (; it != tickMarks.end(); ++it) {
    (*it)->setSelected(FALSE);
    (*it)->setBrush(QColor(0,0,0));
    (*it)->setZ(2);
    this->selectedMark = NULL;
  }
}

void GradientView::setGradient(Gradient * grad)
{
  this->grad = grad;
  emit this->viewChanged();
}

void GradientView::centerTick()
{
  unsigned int i = this->tickMarks.findIndex(this->selectedMark);
  
  if ((i > 0) && (i < this->tickMarks.size() - 1)) {

    float left = (float)this->tickMarks[i-1]->x();
    float right = (float)this->tickMarks[i+1]->x();
    float center = (right - left) / 2.0f + left;

    this->grad->moveTick(i, center / (float)this->canvas->width());

    this->updateTicks();
    emit this->viewChanged();
  }
}

TickMark * GradientView::getTick(int x)
{
  TickMark* i = new TickMark(this->canvas);
  i->setBrush(QColor(0,0,0));
  i->move(0, this->canvas->height()-15);
  i->setX(x);
  i->setZ(2);
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
  int i = this->grad->insertTick(t);

  QValueList<TickMark *>::Iterator it = this->tickMarks.begin();
#if QT_VERSION >= 310
  it += i;
#else // QT_VERSION >= 3.1
  // the += operator wasn't available until Qt 3.1.0.
  for (unsigned int j = 0; j < i; j++) {
    it++;
  }
#endif // QT_VERSION < 3.1
  this->tickMarks.insert(it, this->getTick(x));

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

  for (int i = 0; i < this->grad->numTicks(); i++) {
    float t = this->grad->getParameter(i);
    int x = (int) (t * (float)this->canvas->width() + 0.5f);
    TickMark * tick = this->getTick(x);
    this->tickMarks.append(tick);
  }
}

void GradientView::deleteTick()
{
  int i = (int) this->tickMarks.findIndex(this->selectedMark);
  this->selectedMark = NULL;

  if ((i > 0) && (i < this->tickMarks.size() - 1)) {
    this->grad->removeTick(i);
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
  this->grad->setColor(this->endIndex, TRUE, this->rightcolor);
  emit this->viewChanged();
}

void GradientView::setColorLeft()
{
  this->grad->setColor(this->startIndex, FALSE, this->leftcolor);
  emit this->viewChanged();
}

void GradientView::chooseColorLeft()
{  
  QRgb initial = grad->getColor(this->startIndex, FALSE);
  this->leftcolor = QColorDialog::getRgba(initial);
  if (this->leftcolor != initial) {
    this->setColorLeft();
  }
}

void GradientView::chooseColorRight()
{  
  QRgb initial = this->grad->getColor(this->endIndex, TRUE);
  this->rightcolor = QColorDialog::getRgba(initial);
  if (this->rightcolor != initial) {
    this->setColorRight();
  }
}

// FIXME: instead of building the menu each time, simply use QPopupMenu::changeItem
// to change the color pixmaps. 20030925 frodo.
void GradientView::buildMenu()
{
  if (!this->menu)
    this->menu = new QPopupMenu(this);

  QPixmap left(16,16);
  left.fill(this->grad->getColor(this->startIndex, FALSE));
  menu->insertItem(left, "Left endpoints color", this, SLOT(chooseColorLeft()));

  QPixmap pmleft(16,16);
  this->leftcolor = grad->getColor(this->startIndex, TRUE);
 
  pmleft.fill(this->leftcolor);
  menu->insertItem(pmleft, "Same as left neighbors right endpoint", this, SLOT(setColorLeft()));

  menu->insertSeparator();

  QPixmap right(16,16);
  right.fill(this->grad->getColor(this->endIndex, TRUE));
  menu->insertItem(right, "Right endpoints color", this, SLOT(chooseColorRight()));

  QPixmap pmright(16,16);
  this->rightcolor = this->grad->getColor(this->endIndex, FALSE);

  pmright.fill(this->rightcolor);
  menu->insertItem(pmright, "Same as right neighbors left endpoint", this, SLOT(setColorRight()));

  menu->insertSeparator();
  menu->insertItem("Insert tick", this, SLOT(insertTick()));
  menu->insertItem("Center tick", this, SLOT(centerTick()));
  menu->insertItem("Delete tick", this, SLOT(deleteTick()));
}
