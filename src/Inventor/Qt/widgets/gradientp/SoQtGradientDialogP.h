#ifndef SOQTGRADIENTDIALOGP_H
#define SOQTGRADIENTDIALOGP_H

/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2003 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Systems in Motion about acquiring
 *  a Coin Professional Edition License.
 *
 *  See <URL:http://www.coin3d.org> for more information.
 *
 *  Systems in Motion, Teknobyen, Abels Gate 5, 7030 Trondheim, NORWAY.
 *  <URL:http://www.sim.no>.
 *
\**************************************************************************/

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

  static void gradientCallBack(const Gradient & thisp, void * userData);
  void saveCurrent();

  QFileDialog * fileDialog;
  GradientView * gradView;
  QValueList<Gradient> gradients;
  QComboBox * gradientList;
  QCheckBox * contupdate;
  Gradient gradientcopy;
  static Gradient::ChangeCB * changeCallBack;
  void * changeCallBackData;
  int old_index;
  void * callBackData;
  // FIXME: static? This looks fishy, as it's a per-instance
  // setting. 20031012 mortene.
  static SbBool updateContinuously;

  QLabel * contupdateLabel;
  QPushButton * applyButton;
  

public slots:
  void loadGradient(void);
  void saveGradient(void);
  void chooseGradient(int i);
  void contupdateClicked(void);
  void callGradientUpdate(void);
  void resetGradient(void);
};

#endif // ! SOQTGRADIENTDIALOGP_H
