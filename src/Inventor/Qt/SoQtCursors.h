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

//  $Id$

#ifndef __SOQT_CURSORS_H__
#define __SOQT_CURSORS_H__

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

#endif // ! __SOQT_CURSORS_H__
