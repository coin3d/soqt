#ifndef SoQtCurveWidgetP_H
#define SoQtCurveWidgetP_H

#include <qobject.h>
#include <Inventor/SbBasic.h>
#include "ColorCurve.h"

class QComboBox;
class CurveEditor;
class CurveView;
class QPushButton;
class QCheckBox; 
class QLabel;
class QLineEdit;

class SoQtCurveWidgetP : public QObject {

  Q_OBJECT

public:
  SoQtCurveWidgetP(class SoQtCurveWidget * publ);
  static void curveCallBack(void * userData);
  SoQtCurveWidget * publ;
  QLabel * modetext;
  QLabel * curvetypetext;
  QLabel * constanttext;
  QLabel * vertgrad;
  QLabel * horgrad;
  CurveView * curveview;
  QComboBox * colormodelist;
  QComboBox * curvetypelist;
  QLineEdit * constantvalue;
  QPushButton * applybutton;
  QPushButton * donebutton;
  QPushButton * resetbutton;
  QCheckBox * instantupdate;
  ColorCurve::ChangeCB * callBack;
  void * callbackData;
  SbBool contupdate;

public slots:
  void done(void);
  void apply(void);
  void reset(void);
  void toggleUpdate(void);
  void changeCurveMode(int);
  void setConstantValue(void);
  void updateColorLabels(void);
};

#endif // SoQtCurveWidgetP_H