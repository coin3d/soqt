#ifndef IMAGEITEM_H
#define IMAGEITEM_H

#include <qcanvas.h>
#include <qimage.h>

class QPainter;

class ImageItem: public QCanvasRectangle
{
public:
  enum { RTTI = 5675476 };

  ImageItem(QImage img, QCanvas *canvas);
  int rtti(void) const { return ImageItem::RTTI; }
protected:
  void drawShape(QPainter &);
private:
  QImage image;
  QPixmap pixmap;
};

#endif
