#include <qlayout.h>
#include <qfiledialog.h>
#include <qcombobox.h>
#include <qimage.h>
#include <qpushbutton.h>

#include "SoQtGradientDialog.h"
#include "gradientp/GradientEditor.h"
#include "gradientp/Gradient.h"

#include <Inventor/Qt/widgets/moc_SoQtGradientDialog.icc>


SoQtGradientDialog::SoQtGradientDialog(Gradient * grad, QWidget * parent, bool modal, const char* name)
: QDialog(parent, name, modal)
{
  this->gradEdit = new GradientEditor(grad, this, "gradEdit");

  QVBoxLayout * topLayout = new QVBoxLayout(this);
  topLayout->addWidget(this->gradEdit);

  QHBoxLayout * buttonLayout = new QHBoxLayout();
  topLayout->addLayout(buttonLayout);

  buttonLayout->setAlignment(Qt::AlignLeft);

  QPushButton * loadButton = new QPushButton(this, "loadButton");
  loadButton->setText("Load");
  buttonLayout->addWidget(loadButton, 0, 1);

  QPushButton * saveButton = new QPushButton(this, "saveButton");
  saveButton->setText("Save");
  buttonLayout->addWidget(saveButton, 0, 1);

  this->gradientList = new QComboBox(this, "gradientList");
 // this->addGradient(grad);

  buttonLayout->addWidget(gradientList, 0, 1);

  connect(loadButton, SIGNAL(clicked()), this, SLOT(loadGradient()));
  connect(saveButton, SIGNAL(clicked()), this, SLOT(saveGradient()));

  connect(this->gradientList, SIGNAL(activated(int)), this, SLOT(chooseGradient(int)));
  
  connect(this->gradEdit, SIGNAL(accepted()), this, SLOT(accept()));
  connect(this->gradEdit, SIGNAL(rejected()), this, SLOT(reject()));
}

SoQtGradientDialog::~SoQtGradientDialog()
{
}

void SoQtGradientDialog::addGradient(Gradient * grad)
{
  this->gradients.append(grad);
  this->gradientList->insertItem(this->makePixmap(grad), "description");
}

void SoQtGradientDialog::loadGradient()
{
  QString filename = QFileDialog::getOpenFileName();
  const char * string = filename.ascii();  
  Gradient * grad = new Gradient(string);
  this->gradients.append(grad);
  this->gradEdit->setGradient(grad);
  gradientList->insertItem(this->makePixmap(grad), "description");
}

void SoQtGradientDialog::saveGradient()
{
  QString filename = QFileDialog::getSaveFileName();
  this->gradEdit->getGradient()->save(filename.ascii());
}

void SoQtGradientDialog::chooseGradient(int i)
{
  this->gradEdit->setGradient(this->gradients[i]);
  this->gradEdit->updateAll();
}

Gradient * SoQtGradientDialog::getGradient() const
{
  return this->gradEdit->getGradient();
}

QPixmap SoQtGradientDialog::makePixmap(const Gradient * grad)
{
  int width = 60;
  int height = 16;
  QImage img(width, height, 32);

  SbColor4f * colorArray = new SbColor4f[width];
  grad->getColorArray(colorArray, width);

  for (int i = 0; i < width; i++) {
    uint32_t pixel = colorArray[i].getPackedValue()>>8;
    for (int j = 0; j < height; j++) {
      img.setPixel(i, j, pixel);
    }
  }
  QPixmap pm;
  pm.convertFromImage(img,  Qt::OrderedAlphaDither);
  return pm;
}
