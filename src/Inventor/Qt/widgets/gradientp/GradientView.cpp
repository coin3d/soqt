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
#include <qlayout.h>
#include <qlabel.h>
#include <qstatusbar.h>

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
  this->mousePressed = FALSE;
  this->min = 0;
  this->max = 255;

  QVBoxLayout * topLayout = new QVBoxLayout(this);
  topLayout->setAlignment(Qt::AlignBottom);
  this->statusBar = new QStatusBar(this);
  this->statusBar->setMaximumHeight(15);

  this->selectionMarker = new ImageItem(this->canvas);
  this->gradItem = new ImageItem(this->canvas);
  this->gradItem->show();

  topLayout->addWidget(this->statusBar);

  connect(this, SIGNAL(viewChanged()), this, SLOT(updateView()));
  connect(this, SIGNAL(ticksChanged()), this, SLOT(updateTicks()));

  this->viewport()->setMouseTracking(TRUE);
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

  const QImage gradImage = this->grad.getImage(width, height-25, 32);
  this->gradItem->setImage(gradImage);
  // FIXME: tell the graditem to redraw all of itself
  // not just those parts that have been touched by another item
  // in a more elegant way. 20030910 frodo
  this->gradItem->setVisible(FALSE);
  this->gradItem->setVisible(TRUE);

  if (this->segmentidx != -1) {
    const int selectStart = (int) (this->tickMarks[this->segmentidx]->x());
    const int selectEnd = (int) (this->tickMarks[this->segmentidx + 1]->x());
  
    QImage selectedImage(selectEnd - selectStart, 10, 32);
    selectedImage.fill(QColor(100,100,245).rgb());
    
    this->selectionMarker->setImage(selectedImage);
    this->selectionMarker->move(selectStart, height-25);
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
  this->mousePressed = TRUE;
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
GradientView::contentsMouseReleaseEvent(QMouseEvent * e)
{
  this->mousePressed = FALSE;
}

void
GradientView::contentsMouseMoveEvent(QMouseEvent * e)
{
  if (this->mousePressed) {
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

      float value = t * (this->max - this->min);
      QString s;
      s.sprintf("%f", value);
      this->statusBar->message("Data Value: " + s);
      
      emit this->viewChanged();
    }
  } else {
    QPoint p = inverseWorldMatrix().map(e->pos());
    QRgb col = this->grad.eval((float)p.x() / (float)this->canvas->width());
    QString s;
    s.sprintf("0x%02x%02x%02x%02x", qRed(col), qGreen(col), qBlue(col), qAlpha(col));
    this->statusBar->message(QString("RBGA: ") + s);

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

void
GradientView::setDataLimits(float min, float max)
{
  this->min = min;
  this->max = max;
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
  i->move(0, this->canvas->height()-30);
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

// FIXME: this is _not_ good design -- it's potentially inefficient
// and bugridden. As an example, consider the synchronization problem
// if some other code adds or removes tickmarks in the Gradient
// object.
//
// We should probably rather just let the tickmarks be stored
// canonically in the Gradient class, and set up what we need to do
// around in the GradientView code on demand.
//
// 20031008 mortene.
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

// *************************************************************************

void
GradientView::setGradientColor(unsigned int tickmarkidx, Gradient::TickSide side, QRgb col)
{
  this->grad.setColor(tickmarkidx, side, col);
  emit this->viewChanged();
}

void
GradientView::setGradientColor(unsigned int tickmarkidx, Gradient::TickSide side)
{
  const QRgb initial = this->grad.getColor(tickmarkidx, side);
  const QRgb newcol = QColorDialog::getRgba(initial);
  if (newcol != initial) {
    this->setGradientColor(tickmarkidx, side, newcol);
  }
}

void
GradientView::deleteTick(void)
{
  assert(this->currenttick > 0);
  assert(this->currenttick < (int)(this->tickMarks.size() - 1));

  this->grad.removeTick(this->currenttick);
  this->updateTicks();
  this->segmentidx = -1;
  this->mousePressed = FALSE;
  emit this->viewChanged();
}

void
GradientView::copySegmentColorRight(void)
{
  this->setGradientColor(this->segmentidx + 1, Gradient::LEFT,
                         this->grad.getColor(this->segmentidx + 1, Gradient::RIGHT));
}

void
GradientView::copySegmentColorLeft(void)
{
  this->setGradientColor(this->segmentidx, Gradient::RIGHT,
                         this->grad.getColor(this->segmentidx, Gradient::LEFT));
}

void
GradientView::chooseSegmentColorLeft(void)
{  
  this->setGradientColor(this->segmentidx, Gradient::RIGHT);
}

void
GradientView::chooseSegmentColorRight(void)
{  
  this->setGradientColor(this->segmentidx + 1, Gradient::LEFT);
}

void
GradientView::chooseTickColorLeft(void)
{  
  this->setGradientColor(this->currenttick, Gradient::LEFT);
}

void
GradientView::chooseTickColorRight(void)
{  
  this->setGradientColor(this->currenttick, Gradient::RIGHT);
}

void
GradientView::copyTickColorLeft(void)
{  
  this->setGradientColor(this->currenttick, Gradient::RIGHT,
                         this->grad.getColor(this->currenttick, Gradient::LEFT));
}

void
GradientView::copyTickColorRight(void)
{  
  this->setGradientColor(this->currenttick, Gradient::LEFT,
                         this->grad.getColor(this->currenttick, Gradient::RIGHT));
}

// *************************************************************************

// FIXME: callback is not really used from this class, just passed on
// to the Gradient class. Should look into design to see if we can
// remove this method. 20031008 mortene.
void
GradientView::setChangeCallback(Gradient::ChangeCB * cb, void * userdata)
{
  this->grad.setChangeCallback(cb, userdata);
}

// *************************************************************************

void
GradientView::buildMenu(void)
{
  // FIXME: instead of building the menu each time, simply use
  // QPopupMenu::changeItem to change the color pixmaps. 20030925 frodo.
  assert(!this->menu);
  this->menu = new QPopupMenu(this);

  int id;

  // FIXME: use menu titles. 20031008 mortene.
  
  if (this->segmentidx != -1) {
    QPixmap pm(16,16);
    pm.fill(this->grad.getColor(this->segmentidx, Gradient::RIGHT));
    id = menu->insertItem(pm, "Change left-side color", this, SLOT(chooseSegmentColorLeft()));

    pm.fill(grad.getColor(this->segmentidx, Gradient::LEFT));
    id = menu->insertItem(pm, "Copy color from left neighbor", this, SLOT(copySegmentColorLeft()));
    if (this->grad.leftEqualsRight(this->segmentidx)) menu->setItemEnabled(id, FALSE);

    menu->insertSeparator();

    pm.fill(this->grad.getColor(this->segmentidx + 1, Gradient::LEFT));
    id = menu->insertItem(pm, "Change right-side color", this, SLOT(chooseSegmentColorRight()));

    pm.fill(this->grad.getColor(this->segmentidx + 1, Gradient::RIGHT));
    id = menu->insertItem(pm, "Copy color from right neighbor", this, SLOT(copySegmentColorRight()));
    if (this->grad.leftEqualsRight(this->segmentidx + 1)) menu->setItemEnabled(id, FALSE);

    menu->insertSeparator();

    id = menu->insertItem("Insert new tick", this, SLOT(insertTick()));
  }
  else if (this->currenttick != -1) {
    QPixmap pm(16,16);
    pm.fill(this->grad.getColor(this->currenttick, Gradient::LEFT));
    (void)menu->insertItem(pm, "Change left color", this, SLOT(chooseTickColorLeft()));

    pm.fill(this->grad.getColor(this->currenttick, Gradient::RIGHT));
    (void)menu->insertItem(pm, "Change right color", this, SLOT(chooseTickColorRight()));

    menu->insertSeparator();

    const bool lefteqright = this->grad.leftEqualsRight(this->currenttick);

    pm.fill(this->grad.getColor(this->currenttick, Gradient::LEFT));
    id = menu->insertItem(pm, "Copy left color to right", this, SLOT(copyTickColorLeft()));
    if (lefteqright) { menu->setItemEnabled(id, FALSE); }

    pm.fill(this->grad.getColor(this->currenttick, Gradient::RIGHT));
    id = menu->insertItem(pm, "Copy right color to left", this, SLOT(copyTickColorRight()));
    if (lefteqright) { menu->setItemEnabled(id, FALSE); }

    menu->insertSeparator();

    id = menu->insertItem("Delete tick", this, SLOT(deleteTick()));
    id = menu->insertItem("Center tick", this, SLOT(centerTick()));
  }
}
