
#include <assert.h>

#include <Inventor/Qt/SoQtTypedObject.h>
#include <Inventor/Qt/devices/SoQtDevice.h>
#include <Inventor/Qt/SoQtComponent.h>

SoType SoQtTypedObject::classTypeId; // static

void
SoQtTypedObject::init( // static
  void )
{
  SoQtTypedObject::initClass();
  SoQtDevice::initClasses();
  SoQtComponent::initClasses();
} // init()

void
SoQtTypedObject::initClass( // static
  void )
{
  assert( SoQtTypedObject::classTypeId == SoType::badType() );
  SoQtTypedObject::classTypeId =
    SoType::createType( SoType::badType(), "SoQtTypedObject");
} // initClass()

SbBool
SoQtTypedObject::isOfType(
  SoType type ) const
{
  return this->getTypeId().isDerivedFrom(type);
} // isOfType()

SoType
SoQtTypedObject::getClassTypeId( // static
  void ) 
{
  return SoQtTypedObject::classTypeId;
} // getClassTypeId()

