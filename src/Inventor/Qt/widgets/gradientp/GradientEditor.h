#ifndef GRADIENT_EDITOR_H
#define GRADIENT_EDITOR_H

#include <qwidget.h>

class Gradient;
class GradientView;
class QSlider;
class QLabel;
class QLineEdit;
class QCheckBox;
class QResizeEvent;

class GradientEditor : public QWidget
{
  Q_OBJECT
public:
  GradientEditor(Gradient * grad = NULL, QWidget* parent=0, bool modal = FALSE, const char* name=0, WFlags f=0);
  ~GradientEditor();

  Gradient * getGradient(void) const;
  void setGradient(Gradient * grad);
  void resizeEvent(QResizeEvent *);

signals:
  void accepted(void);
  void rejected(void);

public slots:
  void setMin(float min);
  void setMax(float max);
  void updateValueLabels(void);
  void updateAll(void);
  void accept(void);
  void reject(void);
  
private:
  GradientView * gradView;
  QWidget * gradientWidget;
  Gradient * grad;
  Gradient * originalGradient;
  QSlider * slider;
  QLabel * paramValue;
  QLabel * dataValue;
  QLabel * colorLabel;
  float min, max;
  float minTemp, maxTemp;
};

#endif
