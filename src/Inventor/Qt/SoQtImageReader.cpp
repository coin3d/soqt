/**************************************************************************\
 * Copyright (c) Kongsberg Oil & Gas Technologies AS
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 
 * Neither the name of the copyright holder nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
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
#if QT_VERSION >= 0x040000
      c = image.hasAlphaChannel() ? 4 : 3;
      image = image.convertToFormat(image.hasAlphaChannel() ?
                                    QImage::Format_ARGB32 : QImage::Format_RGB32);
#else
      c = image.hasAlphaBuffer() ? 4 : 3;
      image = image.convertDepth(32);
#endif
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
