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

/*!
  \class GradientView GradientView.h Inventor/Qt/widgets/GradientView.h
  \brief The GradientView class wraps a Gradient in UI controls.
  \ingroup components

  Provides visualization of and controls on a Gradient object. The UI
  controls makes it possible to change the color values of the
  underlying gradient.
*/

// FIXME: I wonder if this shouldn't rather just have been a class for
// displaying a gradient, and the actual UI controls better be placed
// in the GradientEditor class. Discuss with frodo. 20031008 mortene.

// *************************************************************************

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

// *************************************************************************

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
  this->currenttick = -1;
  this->menu = NULL;
  this->segmentidx = 0;

  // FIXME: this looks bogus -- why not just use the default
  // background color?  20031008 mortene.
  this->canvas->setBackgroundColor(Qt::lightGray);

  connect(this, SIGNAL(viewChanged()), this, SLOT(updateView()));
  connect(this, SIGNAL(ticksChanged()), this, SLOT(updateTicks()));

  this->updateTicks();
  emit this->viewChanged();
}

GradientView::~GradientView()
{
  delete this->canvas;
  delete this->gradItem;
  delete this->selectionMarker;
  delete this->menu;
}

void
GradientView::viewportResizeEvent(QResizeEvent * e)
{
  this->canvas->resize(e->size().width(), this->canvas->height());
  this->updateTicks();
  emit this->viewChanged();
}

void
GradientView::updateView(void)
{
  const int width = this->canvas->width();
  const int height = this->canvas->height();

  QImage gradImage = this->grad.getImage(width, height-10, 32);

  if (this->gradItem) { delete this->gradItem; }
  this->gradItem = new ImageItem(gradImage, this->canvas);
  this->gradItem->show();

  if (this->segmentidx != -1) {
    const int selectStart = (int) (this->tickMarks[this->segmentidx]->x());
    const int selectEnd = (int) (this->tickMarks[this->segmentidx + 1]->x());
  
    QImage selectedImage(selectEnd - selectStart, 10, 32);
    selectedImage.fill(QColor(100,100,245).rgb());

    // FIXME: inefficient! *ugh*  20031008 mortene.
    if (this->selectionMarker) { delete this->selectionMarker; }
    this->selectionMarker = new ImageItem(selectedImage, this->canvas);
    this->selectionMarker->moveBy(selectStart, height-10);
    this->selectionMarker->setZ(2);
    this->selectionMarker->show();
  }
  else {
    this->selectionMarker->hide();
  }

  this->canvas->update();
}

void
GradientView::contentsMousePressEvent(QMouseEvent * e)
{
  QPoint p = inverseWorldMatrix().map(e->pos());
 
  switch (e->button()) {
  case Qt::LeftButton: 
    {
      this->currenttick = -1;
      this->segmentidx = -1;

      QValueList<TickMark *>::Iterator it = this->tickMarks.begin();
      for (unsigned int idx = 0; idx < this->tickMarks.size(); idx++) {
        if (this->tickMarks[idx]->hit(p)) {
          this->moving_start = p;
          this->unselectAll();
          this->currenttick = idx;
          this->segmentidx = -1;
          this->tickMarks[idx]->setBrush(Qt::blue);
          break;
        }

        if (this->tickMarks[idx]->x() < p.x()) { this->segmentidx++; }
      }
      emit this->viewChanged();
    }
    break;

  case Qt::RightButton: 
    if ((this->currenttick != -1) || (this->segmentidx != -1)) {
      this->buildMenu();
      if (this->menu->exec(e->globalPos())) {
        // FIXME: this seems unnecessary. 20031008 mortene.
        delete this->menu;
        this->menu = NULL;
      }
    }
    break;

  default: // do nothing
    break;
  }
}

void
GradientView::contentsMouseMoveEvent(QMouseEvent * e)
{
  if (this->currenttick == -1) { return; }

  QPoint p = inverseWorldMatrix().map(e->pos());
  int x = p.x();

  assert(this->currenttick > 0);
  assert(this->currenttick < (int)(this->tickMarks.size() - 1));

  TickMark * left = this->tickMarks[this->currenttick - 1];
  TickMark * current = this->tickMarks[this->currenttick];
  TickMark * right = this->tickMarks[this->currenttick + 1];

  const int movex = x - this->moving_start.x();
  const int newpos = (int) (current->x() + movex);
    
  if ((newpos >= left->x()) && newpos <= right->x()) {
    current->moveBy(movex, 0);
    this->moving_start = QPoint(x, p.y());
      
    const float t = current->getPos();
    this->grad.moveTick(this->currenttick, t);
      
    emit this->viewChanged();
  }
}

void GradientView::keyPressEvent(QKeyEvent * e)
{
  switch (e->key()) {
  case Qt::Key_Delete: if (this->currenttick != -1) { this->deleteTick(); } break;
  default: break;
  }
}

float
GradientView::getSelectedPos(void)
{
  if (this->currenttick > 0) {
    return this->grad.getParameter(this->currenttick);
  }
  // FIXME: does it make sense to call this function without a current
  // tick selection? If not, use an assert. 20031008 mortene.
  return 0.0f;
}

void
GradientView::unselectAll(void)
{
  QValueList<TickMark*>::Iterator it = this->tickMarks.begin();
  for (; it != tickMarks.end(); ++it) {
    (*it)->setBrush(Qt::black);
  }
  this->currenttick = -1;
}


void
GradientView::setGradient(const Gradient & grad)
{
  this->grad = grad;
  this->currenttick = -1;
  this->segmentidx = -1;
  this->updateTicks();
  emit this->viewChanged();
}

const Gradient &
GradientView::getGradient(void) const
{
  return this->grad;
}

void
GradientView::centerTick(void)
{
  assert(this->currenttick > 0);
  assert(this->currenttick < (int)(this->tickMarks.size() - 1));

  const double left = this->tickMarks[this->currenttick - 1]->x();
  const double right = this->tickMarks[this->currenttick + 1]->x();
  const double center = (right - left) / 2.0 + left;

  this->grad.moveTick(this->currenttick, center / this->canvas->width());

  this->updateTicks();
  emit this->viewChanged();
}

TickMark *
GradientView::newTick(int x)
{
  TickMark* i = new TickMark(this->canvas);
  i->setBrush(QColor(0,0,0));
  i->move(0, this->canvas->height()-15);
  i->setZ(3);
  i->setX(x);
  i->show();
  return i;
}

void
GradientView::insertTick(void)
{
  assert(this->segmentidx != -1);
  const float selectStart = this->tickMarks[this->segmentidx]->x();
  const float selectEnd = this->tickMarks[this->segmentidx + 1]->x();

  // x == midpoint of selected section
  const float x = ((selectEnd - selectStart)/2.0f + selectStart);

  const float t = x / (float)this->canvas->width();
  const int i = this->grad.insertTick(t);

  QValueList<TickMark*>::Iterator it = this->tickMarks.begin();
  // the += operator wasn't available until Qt 3.1.0. Just iterate
  // and use ++. pederb, 2003-09-22
  for (int j = 0; j < i; j++) { it++; }
  this->tickMarks.insert(it, this->newTick(x));

  this->segmentidx = -1;

  emit this->viewChanged();
}

void
GradientView::updateTicks(void)
{
  QValueList<TickMark*>::Iterator it = this->tickMarks.begin();
  for (; it != tickMarks.end(); ++it) { delete (*it); }

  this->tickMarks.clear();

  for (unsigned int i = 0; i < this->grad.numTicks(); i++) {
    float t = this->grad.getParameter(i);
    int x = (int) (t * (float)this->canvas->width() + 0.5f);
    TickMark * tick = this->newTick(x);
    this->tickMarks.append(tick);
  }
  this->tickMarks[0]->setVisible(FALSE);
  this->tickMarks[this->tickMarks.size()-1]->setVisible(FALSE);
}

void
GradientView::deleteTick(void)
{
  assert(this->currenttick > 0);
  assert(this->currenttick < (int)(this->tickMarks.size() - 1));

  this->grad.removeTick(this->currenttick);
  this->updateTicks();
    
  this->segmentidx = -1;
  emit this->viewChanged();
}

void
GradientView::setColorRight(void)
{
  this->grad.setColor(this->segmentidx + 1, TRUE, this->rightcolor);
  emit this->viewChanged();
}

void
GradientView::setColorLeft(void)
{
  this->grad.setColor(this->segmentidx, FALSE, this->leftcolor);
  emit this->viewChanged();
}

void
GradientView::chooseColorLeft(void)
{  
  const QRgb initial = this->grad.getColor(this->segmentidx, FALSE);
  this->leftcolor = QColorDialog::getRgba(initial);
  if (this->leftcolor != initial) { this->setColorLeft(); }
}

void
GradientView::chooseColorRight(void)
{  
  QRgb initial = this->grad.getColor(this->segmentidx + 1, TRUE);
  this->rightcolor = QColorDialog::getRgba(initial);
  if (this->rightcolor != initial) {
    this->setColorRight();
  }
}

// FIXME: callback is not really used from this class, just passed on
// to the Gradient class. Should look into design to see if we can
// remove this method. 20031008 mortene.
void
GradientView::setChangeCallback(Gradient::ChangeCB * cb, void * userdata)
{
  this->grad.setChangeCallback(cb, userdata);
}

void
GradientView::buildMenu(void)
{
  // FIXME: instead of building the menu each time, simply use
  // QPopupMenu::changeItem to change the color pixmaps. 20030925 frodo.
  assert(!this->menu);
  this->menu = new QPopupMenu(this);

  int id;
  
  if (this->segmentidx != -1) {
    QPixmap left(16,16);
    left.fill(this->grad.getColor(this->segmentidx, FALSE));
    id = menu->insertItem(left, "Left endpoint's color", this, SLOT(chooseColorLeft()));

    QPixmap pmleft(16,16);
    this->leftcolor = grad.getColor(this->segmentidx, TRUE);
 
    pmleft.fill(this->leftcolor);
    id = menu->insertItem(pmleft, "Same as left neighbor's right endpoint", this, SLOT(setColorLeft()));
    if (this->grad.leftEqualsRight(this->segmentidx)) menu->setItemEnabled(id, FALSE);

    menu->insertSeparator();

    QPixmap right(16,16);
    right.fill(this->grad.getColor(this->segmentidx + 1, TRUE));
    id = menu->insertItem(right, "Right endpoint's color", this, SLOT(chooseColorRight()));

    QPixmap pmright(16,16);
    this->rightcolor = this->grad.getColor(this->segmentidx + 1, FALSE);

    pmright.fill(this->rightcolor);
    id = menu->insertItem(pmright, "Same as right neighbor's left endpoint", this, SLOT(setColorRight()));
    if (this->grad.leftEqualsRight(this->segmentidx + 1)) menu->setItemEnabled(id, FALSE);

    menu->insertSeparator();
    id = menu->insertItem("Insert new tick", this, SLOT(insertTick()));
  }
  else if (this->currenttick != -1) {
    // FIXME: more functionality, like: "change left color", "change
    // right color", "copy left color to right", "copy right color to
    // left", etc. 20031008 mortene.

    id = menu->insertItem("Center tick", this, SLOT(centerTick()));
    id = menu->insertItem("Delete tick", this, SLOT(deleteTick()));
  }
}
