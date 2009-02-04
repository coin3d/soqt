/**************************************************************************\
 *
 *  This file is part of the Coin 3D visualization library.
 *  Copyright (C) 1998-2005 by Systems in Motion.  All rights reserved.
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
 *  See <URL:http://www.coin3d.org/> for more information.
 *
 *  Systems in Motion, Postboks 1283, Pirsenteret, 7462 Trondheim, NORWAY.
 *  <URL:http://www.sim.no/>.
 *
\**************************************************************************/

// FIXME: this image reader is also present in Quarter. If you do any
// fixes/changes here you should look into updating the Quarter
// version as well.  pederb, 2009-02-04

#include <Inventor/Qt/SoQtImageReader.h>
#include <Inventor/SbImage.h>
#include <qimage.h>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif // HAVE_CONFIG_H

SoQtImageReader::SoQtImageReader(void)
{
#if HAVE_SBIMAGE_ADDREADIMAGECB
  SbImage::addReadImageCB(SoQtImageReader::readImageCB, this);
#endif // HAVE_SBIMAGE_ADDREADIMAGECB
}

SoQtImageReader::~SoQtImageReader(void)
{
#if HAVE_SBIMAGE_ADDREADIMAGECB
  SbImage::removeReadImageCB(SoQtImageReader::readImageCB, this);
#endif // HAVE_SBIMAGE_ADDREADIMAGECB
}

SbBool
SoQtImageReader::readImage(const SbString & filename, SbImage * sbimage) const
{
  QImage image;
  if (image.load(filename.getString())) {
    int c;
    int w = image.width();
    int h = image.height();

    // Keep in 8-bits mode if that was what we read
    if (image.depth() == 8 && image.isGrayscale()) {
      c = 1;
    }
    else {
      // FIXME: consider if we should detect allGrayscale() and alpha (c = 2)
      c = image.hasAlphaChannel() ? 4 : 3;
      image = image.convertToFormat(image.hasAlphaChannel() ?
                                    QImage::Format_ARGB32 : QImage::Format_RGB32);
    }

    SbVec2s size((short) w, (short) h);
    sbimage->setValue(size, c, NULL);
    unsigned char * buffer = sbimage->getValue(size, c);

    if (c == 1) {
      for (int i = 0; i < h; i++) {
        memcpy(buffer + i*w, image.scanLine(h-(i+1)), w);
      }
    }
    else { // (c == 3 || c == 4)
      QRgb * bits = (QRgb*) image.bits();
      for (int y = 0; y < h; y++) {
        unsigned char * line = &buffer[c*w*(h-(y+1))];
        for (int x = 0; x < w; x++) {
          *line++ = qRed(*bits);
          *line++ = qGreen(*bits);
          *line++ = qBlue(*bits);
          if (c == 4) {
            *line++ = qAlpha(*bits);
          }
          bits++;
        }
      }
    }
    return TRUE;
  }
  return FALSE;
}

SbBool
SoQtImageReader::readImageCB(const SbString & filename, SbImage * image, void * closure)
{
  return ((SoQtImageReader*)closure)->readImage(filename, image);
}
