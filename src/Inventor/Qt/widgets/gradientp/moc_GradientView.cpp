/****************************************************************************
** GradientView meta object code from reading C++ file 'GradientView.h'
**
** Created: on 17. sep 15:05:34 2003
**      by: The Qt MOC ($Id$)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "GradientView.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *GradientView::className() const
{
    return "GradientView";
}

QMetaObject *GradientView::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GradientView( "GradientView", &GradientView::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString GradientView::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GradientView", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GradientView::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GradientView", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GradientView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QCanvasView::staticMetaObject();
    static const QUMethod slot_0 = {"updateView", 0, 0 };
    static const QUMethod slot_1 = {"setColorRight", 0, 0 };
    static const QUMethod slot_2 = {"setColorLeft", 0, 0 };
    static const QUMethod slot_3 = {"chooseColorLeft", 0, 0 };
    static const QUMethod slot_4 = {"chooseColorRight", 0, 0 };
    static const QUMethod slot_5 = {"insertTick", 0, 0 };
    static const QUMethod slot_6 = {"centerTick", 0, 0 };
    static const QUMethod slot_7 = {"deleteTick", 0, 0 };
    static const QUMethod slot_8 = {"updateTicks", 0, 0 };
    static const QUParameter param_slot_9[] = {
	{ 0, &static_QUType_ptr, "QResizeEvent", QUParameter::In }
    };
    static const QUMethod slot_9 = {"viewportResizeEvent", 1, param_slot_9 };
    static const QMetaData slot_tbl[] = {
	{ "updateView()", &slot_0, QMetaData::Public },
	{ "setColorRight()", &slot_1, QMetaData::Public },
	{ "setColorLeft()", &slot_2, QMetaData::Public },
	{ "chooseColorLeft()", &slot_3, QMetaData::Public },
	{ "chooseColorRight()", &slot_4, QMetaData::Public },
	{ "insertTick()", &slot_5, QMetaData::Public },
	{ "centerTick()", &slot_6, QMetaData::Public },
	{ "deleteTick()", &slot_7, QMetaData::Public },
	{ "updateTicks()", &slot_8, QMetaData::Public },
	{ "viewportResizeEvent(QResizeEvent*)", &slot_9, QMetaData::Public }
    };
    static const QUMethod signal_0 = {"viewChanged", 0, 0 };
    static const QUMethod signal_1 = {"tickSelected", 0, 0 };
    static const QUParameter param_signal_2[] = {
	{ "x", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"mouseMoved", 1, param_signal_2 };
    static const QUMethod signal_3 = {"ticksChanged", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "viewChanged()", &signal_0, QMetaData::Public },
	{ "tickSelected()", &signal_1, QMetaData::Public },
	{ "mouseMoved(int)", &signal_2, QMetaData::Public },
	{ "ticksChanged()", &signal_3, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"GradientView", parentObject,
	slot_tbl, 10,
	signal_tbl, 4,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GradientView.setMetaObject( metaObj );
    return metaObj;
}

void* GradientView::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GradientView" ) )
	return this;
    return QCanvasView::qt_cast( clname );
}

// SIGNAL viewChanged
void GradientView::viewChanged()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

// SIGNAL tickSelected
void GradientView::tickSelected()
{
    activate_signal( staticMetaObject()->signalOffset() + 1 );
}

// SIGNAL mouseMoved
void GradientView::mouseMoved( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 2, t0 );
}

// SIGNAL ticksChanged
void GradientView::ticksChanged()
{
    activate_signal( staticMetaObject()->signalOffset() + 3 );
}

bool GradientView::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: updateView(); break;
    case 1: setColorRight(); break;
    case 2: setColorLeft(); break;
    case 3: chooseColorLeft(); break;
    case 4: chooseColorRight(); break;
    case 5: insertTick(); break;
    case 6: centerTick(); break;
    case 7: deleteTick(); break;
    case 8: updateTicks(); break;
    case 9: viewportResizeEvent((QResizeEvent*)static_QUType_ptr.get(_o+1)); break;
    default:
	return QCanvasView::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool GradientView::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: viewChanged(); break;
    case 1: tickSelected(); break;
    case 2: mouseMoved((int)static_QUType_int.get(_o+1)); break;
    case 3: ticksChanged(); break;
    default:
	return QCanvasView::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool GradientView::qt_property( int id, int f, QVariant* v)
{
    return QCanvasView::qt_property( id, f, v);
}

bool GradientView::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
