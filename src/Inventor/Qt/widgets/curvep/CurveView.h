#ifndef CURVEVIEW_H
#define CURVEVIEW_H

#include <qcanvas.h>
#include <qimage.h>
#include <Inventor/SbBasic.h>
#include <Inventor/Qt/widgets/SoQtCurveWidget.h>

class ColorCurve;
class QCanvasItemList;
class QMouseEvent;
class QCanvasItem;
class QPoint;
class QKeyEvent;
class QFocusEvent;
class QResizeEvent;

class CurveView : public QCanvasView 
{
    Q_OBJECT // for signals and slots

public:
  CurveView(QCanvas*, QWidget* parent=0, const char* name=0, WFlags f=0);
  ~CurveView();

  enum ColorMode {
    RED = 0,
    GREEN,
    BLUE,
    ALPHA,
    LUMINANCE,
  };  

  enum CurveMode { SMOOTH, FREE };
  
  void getColors(uint8_t * colors, int num, SoQtCurveWidget::Mode mode) const;
  void setColors(uint8_t * colors, int num, SoQtCurveWidget::Mode mode);
  void setCallBack(ColorCurve::ChangeCB * cb, void * userData);

public slots:
  void changeColorMode(int mode);
  void changeCurveMode(int mode);
  void setConstantValue(int value);
  void resetActive(void);

  QPixmap getPixmap(int width, int height) const;
  QPixmap getGradient(int width, int height) const;

signals:
  void curveChanged(void);
  
protected:
  void contentsMousePressEvent(QMouseEvent * e);
  void contentsMouseReleaseEvent(QMouseEvent * e);
  void contentsMouseMoveEvent(QMouseEvent * e);
  void drawContents(QPainter * p, int cx, int cy, int cw, int ch);

private:
  void interpolateFromColors();
  void initCurve(void);
  void insertGrid(void);
  void updateCurve(void);
  void hideUnselected(void);
  QPixmap makePixmap(int w, int h, const uint8_t * r, const uint8_t * g, const uint8_t * b, int num) const;
  QCanvasRectangle * newControlPoint(int x, int y);
  QCanvasItemList newCanvasCtrlPtList(void);
  QCanvasItem * smallestItem(QCanvasItemList * list);

  SbBool mousepressed;
  QPoint movingstart;
  QPoint lastpos;
  QCanvas * canvas;
  QCanvasItem * movingitem;

  ColorMode colormode;
  CurveMode curvemode;
  
  const int ptsize;

  QValueList<QCanvasItemList> canvasctrlpts;
  QValueList<ColorCurve*> colorcurves;
    
  QCanvasItemList curvesegments;
  QCanvasItemList grid;
};

#endif // CURVEVIEW_H