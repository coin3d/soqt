#ifndef SOQTGRADIENTDIALOGP_H
#define SOQTGRADIENTDIALOGP_H

#include <qvaluelist.h>
#include <qobject.h>
#include "../Gradient.h"

class SoQtGradientDialog;
class GradientView;
class QComboBox;
class QCheckBox;

class SoQtGradientDialogP : public QObject {

  Q_OBJECT

public:
  SoQtGradientDialogP(SoQtGradientDialog * publ);
  SoQtGradientDialog * pub;
  GradientView * gradView;
  QValueList<Gradient> gradients;
  QComboBox * gradientList;
  QCheckBox * contupdate;
  Gradient gradientcopy;
  static Gradient::ChangeCB * changeCallBack;
  void * changeCallBackData;
  int old_index;
  void * callBackData;
  static SbBool updateContinuously;
  static void gradientCallBack(const Gradient & thisp, void * userData);
  void saveCurrent();

public slots:
  void loadGradient(void);
  void saveGradient(void);
  void chooseGradient(int i);
  void contupdateClicked(void);
  void callGradientUpdate(void);
  void resetGradient(void);
};

#endif // SOQTGRADIENTDIALOGP_H