/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) by Kongsberg Oil & Gas Technologies.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  ("GPL") version 2 as published by the Free Software Foundation.
 *  See the file LICENSE.GPL at the root directory of this source
 *  distribution for additional information about the GNU GPL.
 *
 *  For using Coin with software that can not be combined with the GNU
 *  GPL, and for taking advantage of the additional benefits of our
 *  support services, please contact Kongsberg Oil & Gas Technologies
 *  about acquiring a Coin Professional Edition License.
 *
 *  See http://www.coin3d.org/ for more information.
 *
 *  Kongsberg Oil & Gas Technologies, Bygdoy Alle 5, 0257 Oslo, NORWAY.
 *  http://www.sim.no/  sales@sim.no  coin-support@coin3d.org
 *
\**************************************************************************/

/*
  This is just a simple test application to try out the functionality
  of the SoQtThumbWheel widget.

  FIXME: this doesn't work at the moment (the SoQtThumbWheel API is
  not exported in the SoQt library). 20001125 mortene.
*/

#include <qapplication.h>
#include <Inventor/Qt/widgets/SoQtThumbWheel.h>

int
main( int argc, char **argv )
{
  QApplication a(argc,argv);

  SoQtThumbWheel wheel_h(SoQtThumbWheel::Horizontal);
  wheel_h.resize(200, 30);

  SoQtThumbWheel wheel_v(SoQtThumbWheel::Vertical);
  wheel_v.resize(30, 200);

  a.setMainWidget(&wheel_h);
  wheel_h.show();
  wheel_v.show();
  return a.exec();
}
