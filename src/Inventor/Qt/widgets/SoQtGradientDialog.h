#ifndef GRADIENTDIALOG_H
#define GRADIENTDIALOG_H

#include <qdialog.h>
#include <qpixmap.h>

#include <Inventor/lists/SbList.h>

#include <Inventor/Qt/SoQtBasic.h>

class Gradient;
class GradientEditor;
class QComboBox;  


class SOQT_DLL_API SoQtGradientDialog : public QDialog
{
  Q_OBJECT

public:
  SoQtGradientDialog(Gradient * grad = NULL, QWidget * parent=0, bool modal = FALSE, const char* name=0);
  ~SoQtGradientDialog();

  Gradient * getGradient(void) const;
  void addGradient(Gradient * grad);
  
public slots:
  void loadGradient(void);
  void saveGradient(void);
  void chooseGradient(int i);

private:
  void loadGradients(void);
  QPixmap makePixmap(const Gradient * grad);
  GradientEditor * gradEdit;
  QComboBox * gradientList;
  SbList<Gradient*> gradients;
};








#endif // GRADIENTDIALOG_H
