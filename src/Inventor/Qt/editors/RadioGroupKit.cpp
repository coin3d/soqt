#include <RadioGroupKit.h>

SO_KIT_SOURCE(RadioGroupKit);


RadioGroupKit::RadioGroupKit(void)
{
  SO_KIT_CONSTRUCTOR(RadioGroupKit);

  // FIXME: add all "radiobutton" indicators etc to the nodekit's
  // catalog.

  // SO_KIT_ADD_CATALOG_ENTRY(...);

  SO_KIT_ADD_FIELD(selected, -1);
  SO_KIT_ADD_FIELD(labels, "");

  SO_KIT_INIT_INSTANCE();
}

RadioGroupKit::~RadioGroupKit()
{
}

void
RadioGroupKit::initClass(void)
{
  SO_KIT_INIT_CLASS(RadioGroupKit, SoBaseKit, "BaseKit");
}

void
RadioGroupKit::handleEvent(SoHandleEventAction * action)
{
  // FIXME: catch mousepicks.
}
