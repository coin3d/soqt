/**************************************************************************\
 *
 *  Copyright (C) 1998-1999 by Systems in Motion.  All rights reserved.
 *
 *  This file is part of the Coin library.
 *
 *  This file may be distributed under the terms of the Q Public License
 *  as defined by Troll Tech AS of Norway and appearing in the file
 *  LICENSE.QPL included in the packaging of this file.
 *
 *  If you want to use Coin in applications not covered by licenses
 *  compatible with the QPL, you can contact SIM to aquire a
 *  Professional Edition license for Coin.
 *
 *  Systems in Motion AS, Prof. Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ sales@sim.no Voice: +47 22114160 Fax: +47 67172912
 *
\**************************************************************************/

/*
  This is just a simple test application to try out the functionality
  of the SoQtThumbWheel widget.
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
