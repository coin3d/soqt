#ifndef CURVEDIALOG_H
#define CURVEDIALOG_H

#include <QWidget.h>
#include <Inventor/system/inttypes.h>
#include "ColorCurve.h"

class SoQtCurveWidget : public QWidget {

public:
  SoQtCurveWidget(QWidget * parent = 0, const char * name = 0);
  ~SoQtCurveWidget(void);

  enum Mode {
    LUMINANCE = 1,
    LUMINANCE_ALPHA,
    RGB,
    RGBA
  };

  void setMode(Mode mode);
  void setColors(uint8_t * color, int num, Mode mode);
  void getColors(uint8_t * color, int num, Mode mode) const;
  void setCallBack(ColorCurve::ChangeCB * cb, void * userData);

private:
  class SoQtCurveWidgetP * pimpl;
};

#endif // CURVEDIALOG_H