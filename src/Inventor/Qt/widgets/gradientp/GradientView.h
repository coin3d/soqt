#ifndef GRADIENT_VIEW_H
#define GRADIENT_VIEW_H

#include <qcanvas.h>
#include <Inventor/lists/SbList.h>
#include <Inventor/system/inttypes.h>

class TickMark;
class QSize;
class QMouseEvent;
class QPaintEvent;
class QResizeEvent;
class Gradient;
class ImageItem;
class QPopupMenu;

class GradientView : public QCanvasView
{
  Q_OBJECT

public:
  GradientView(QCanvas * c = 0, 
               Gradient * g = 0, 
               QWidget * parent = 0, 
               const char * name = 0, 
               WFlags f = 0);
  
  ~GradientView();

  void setGradient(Gradient * grad);
  void insertTick(float t);
  float getSelectedPos(void);

public slots:
  void updateView(void);
  void setColorRight(void);
  void setColorLeft(void);
  void chooseColorLeft(void);
  void chooseColorRight(void);
  void insertTick(void);
  void centerTick(void);
  void deleteTick(void);
  void updateTicks(void);
  void viewportResizeEvent(QResizeEvent *);

signals:
  void viewChanged(void);
  void tickSelected(void);
  void mouseMoved(int x);
  void ticksChanged(void);

protected:
  void contentsMousePressEvent(QMouseEvent *);
  void contentsMouseReleaseEvent(QMouseEvent *);
  void contentsMouseMoveEvent(QMouseEvent *);
  void keyPressEvent(QKeyEvent * e);
  void buildMenu();
  TickMark * getTick(int x);
  void unselectAll(void);

private:
  inline
  uint32_t getQtColor(const unsigned int color); 

  QCanvas * canvas;
  Gradient * grad;
  ImageItem * gradItem;
  ImageItem * selectionMarker;
  QPopupMenu * menu;
  TickMark * movingItem;
  TickMark * selectedMark;
  SbList<TickMark *> tickMarks;
  int startIndex;
  int endIndex;
  QPoint moving_start;
  uint32_t leftcolor;
  uint32_t rightcolor;
};

inline
unsigned int GradientView::getQtColor(const unsigned int color)
{
  return qRgba(qAlpha(color), qRed(color),
               qGreen(color), qBlue(color));
}


#endif // GRADIENT_EDITOR_H