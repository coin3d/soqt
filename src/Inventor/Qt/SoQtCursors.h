/**************************************************************************
 *
 *  This file is part of the Coin SoQt GUI binding library.
 *  Copyright (C) 1998-2000 by Systems in Motion.  All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License version
 *  2.1 as published by the Free Software Foundation.  See the file
 *  LICENSE.LGPL at the root directory of the distribution for all the
 *  details.
 *
 *  If you want to use Coin SoQt for applications not compatible with the
 *  LGPL, please contact SIM to acquire a Professional Edition License.
 *
 *  Systems in Motion, Prof Brochs gate 6, N-7030 Trondheim, NORWAY
 *  http://www.sim.no/ support@sim.no Voice: +47 22114160 Fax: +47 22207097
 *
 **************************************************************************/

//  $Id$

#ifndef SOQT_CURSORS_H
#define SOQT_CURSORS_H

#define so_qt_zoom_width 32
#define so_qt_zoom_height 32
#define so_qt_zoom_x_hot 5
#define so_qt_zoom_y_hot 7
extern unsigned char so_qt_zoom_bitmap[];
extern unsigned char so_qt_zoom_mask_bitmap[];

#define so_qt_pan_width 32
#define so_qt_pan_height 32
#define so_qt_pan_x_hot 7
#define so_qt_pan_y_hot 7
extern unsigned char so_qt_pan_bitmap[];
extern unsigned char so_qt_pan_mask_bitmap[];

#define so_qt_rotate_width 32
#define so_qt_rotate_height 32
#define so_qt_rotate_x_hot 6
#define so_qt_rotate_y_hot 8
extern unsigned char so_qt_rotate_bitmap[];
extern unsigned char so_qt_rotate_mask_bitmap[];

#endif // ! SOQT_CURSORS_H
