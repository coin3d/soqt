#include <qpainter.h>
#include "ImageItem.h"

ImageItem::ImageItem(QImage img, QCanvas *canvas)
: QCanvasRectangle(canvas), image(img)
{
  this->setSize(canvas->width(), canvas->height());
  if (!image.isNull()) {
    this->pixmap.convertFromImage(image, Qt::OrderedAlphaDither);
  }
}

void ImageItem::drawShape(QPainter &p)
{
  p.drawPixmap(int(x()), int(y()), this->pixmap);
}
