#include <RGBCubeEditorKit.h>

SO_KIT_SOURCE(RGBCubeEditorKit);


RGBCubeEditorKit::RGBCubeEditorKit(void)
{
  SO_KIT_CONSTRUCTOR(RGBCubeEditorKit);

  // FIXME: add all geometry nodes, draggers etc used for the RGB cube
  // interaction to the nodekit's catalog.

  // SO_KIT_ADD_CATALOG_ENTRY(...);

  SO_KIT_ADD_FIELD(rgb, (SbColor(0.8, 0.8, 0.8)));
  // FIXME: wire up the SoSFColor rgb field so it's automatically
  // updated on changes.

  SO_KIT_INIT_INSTANCE();
}

RGBCubeEditorKit::~RGBCubeEditorKit()
{
}

void
RGBCubeEditorKit::initClass(void)
{
  SO_KIT_INIT_CLASS(RGBCubeEditorKit, SoBaseKit, "BaseKit");
}

void
RGBCubeEditorKit::handleEvent(SoHandleEventAction * action)
{
  // FIXME: catch mousepicks on the cube to "quick-set" a color.
}
