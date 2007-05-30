#ifndef SOQT_DEBUG
#error The define SOQT_DEBUG needs to be defined to true or false
#endif

#if SOQT_DEBUG
#include "config-debug.h"
#else /* !SOQT_DEBUG */
#include "config-release.h"
#endif /* !SOQT_DEBUG */
