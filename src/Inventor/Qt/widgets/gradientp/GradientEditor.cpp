#include <qslider.h>
#include <qpushbutton.h>
#include <qgroupbox.h>
#include <qslider.h>
#include <qlayout.h>
#include <qcolordialog.h>
#include <qcheckbox.h>
#include <qlineedit.h>
#include <qslider.h>
#include <qlabel.h>
#include <Inventor/SbColor4f.h>
#include <qcanvas.h>
#include <qframe.h>
  
#include "GradientEditor.h"
#include "GradientView.h"
#include "Gradient.h"

#include <Inventor/Qt/widgets/moc_GradientEditor.icc>


GradientEditor::GradientEditor(Gradient * grad, QWidget * parent, bool modal, const char* name, WFlags f)
: QWidget(parent, name, f)
{
  if (grad != NULL) {
    this->grad = grad;
  }
  else {
    this->grad = new Gradient();
  }

  this->originalGradient = new Gradient(*this->grad);

  this->min = -20.0f;
  this->max = 221.0f;
  this->minTemp = this->min;
  this->maxTemp = this->max;

  QVBoxLayout * topLayout = new QVBoxLayout(this);
  QHBoxLayout * buttonOutputLayout = new QHBoxLayout();
  QVBoxLayout * outputLayout = new QVBoxLayout();
  QHBoxLayout * buttonLayout = new QHBoxLayout();

  buttonOutputLayout->addLayout(outputLayout);
  buttonOutputLayout->addLayout(buttonLayout);

  this->gradientWidget = new QWidget(this, "gradientWidget");
  this->gradientWidget->setMinimumHeight(80);
  topLayout->addWidget(this->gradientWidget);
  topLayout->addLayout(buttonOutputLayout);

  QCanvas * canvas = new QCanvas(450,58);
  this->gradView = new GradientView(canvas, this->grad, gradientWidget, "GradientView");
  this->gradView->setMargin(10);
  this->gradView->setFrameStyle(QFrame::Sunken);

  QGroupBox * dataValues = new QGroupBox(this, "dataValues");
  dataValues->setTitle("Data Values");
  dataValues->setColumns(3);
  dataValues->setOrientation(Qt::Vertical);
  outputLayout->addWidget(dataValues);

  this->paramValue = new QLabel(dataValues, "paramValue");
  this->dataValue = new QLabel(dataValues, "dataValue");
  this->colorLabel = new QLabel(dataValues, "colorLabel");

  buttonLayout->setAlignment(Qt::AlignRight);

  QPushButton * okButton = new QPushButton(this, "okButton");
  okButton->setText("OK");
  buttonLayout->addWidget(okButton, 0, 1);

  QPushButton * cancelButton = new QPushButton(this, "cancelButton");
  cancelButton->setText("Cancel");
  buttonLayout->addWidget(cancelButton, 0, 1);

  connect(this->gradView, SIGNAL(viewChanged()), this, SLOT(updateValueLabels()));
  connect(this->gradView, SIGNAL(tickSelected()), this, SLOT(updateValueLabels()));

  connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
  connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));

  this->updateValueLabels();
}

GradientEditor::~GradientEditor()
{
}

void GradientEditor::resizeEvent(QResizeEvent * e)
{
  this->gradientWidget->resize(QSize(e->size().width(), 80));
  this->gradView->resize(QSize(e->size().width(), 80));
  this->repaint();
}

void GradientEditor::setMin(float min)
{
  this->min = min;
}

void GradientEditor::setMax(float max)
{
  this->max = max;
}

void GradientEditor::updateValueLabels()
{
  float t = this->gradView->getSelectedPos();
  float value = t * (this->maxTemp - this->minTemp) + this->minTemp;

  SbColor4f col = this->grad->eval(t);


  this->paramValue->setText(QString(" Parameter value: ") + QString().setNum(t));

  this->dataValue->setText(QString(" Data value: ") + QString().setNum(value));

  this->colorLabel->setText(QString(" Color: ") + 
                      QString(" R: ") + QString().setNum(int(col[0] * 255.0f)) +
                      QString(" G: ") + QString().setNum(int(col[1] * 255.0f)) +
                      QString(" B: ") + QString().setNum(int(col[2] * 255.0f)));
}

Gradient * GradientEditor::getGradient() const
{
  return this->grad;
}

void GradientEditor::setGradient(Gradient * grad)
{
  *this->grad = *grad;
  this->gradView->updateTicks();
  this->gradView->updateView();
}

void GradientEditor::updateAll()
{  
  this->gradView->updateTicks();
  this->gradView->updateView();
}

void GradientEditor::accept()
{
  *this->originalGradient = *this->grad;
  emit this->accepted();
}

void GradientEditor::reject()
{
  *this->grad = *this->originalGradient;
  this->gradView->updateTicks();
  this->gradView->updateView();
  emit this->rejected();
}
