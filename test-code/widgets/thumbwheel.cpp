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
