/****************************************************************************
** CurveView meta object code from reading C++ file 'CurveView.h'
**
** Created: to 16. okt 11:33:33 2003
**      by: The Qt MOC ($Id$)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "CurveView.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#include <qvariant.h>
const char *CurveView::className() const
{
    return "CurveView";
}

QMetaObject *CurveView::metaObj = 0;
static QMetaObjectCleanUp cleanUp_CurveView( "CurveView", &CurveView::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString CurveView::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CurveView", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString CurveView::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "CurveView", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* CurveView::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QCanvasView::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "mode", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"changeColorMode", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "mode", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"changeCurveMode", 1, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "value", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"setConstantValue", 1, param_slot_2 };
    static const QUMethod slot_3 = {"resetActive", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_QVariant, "\x06", QUParameter::Out },
	{ "width", &static_QUType_int, 0, QUParameter::In },
	{ "height", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"getPixmap", 3, param_slot_4 };
    static const QUParameter param_slot_5[] = {
	{ 0, &static_QUType_QVariant, "\x06", QUParameter::Out },
	{ "width", &static_QUType_int, 0, QUParameter::In },
	{ "height", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"getGradient", 3, param_slot_5 };
    static const QMetaData slot_tbl[] = {
	{ "changeColorMode(int)", &slot_0, QMetaData::Public },
	{ "changeCurveMode(int)", &slot_1, QMetaData::Public },
	{ "setConstantValue(int)", &slot_2, QMetaData::Public },
	{ "resetActive()", &slot_3, QMetaData::Public },
	{ "getPixmap(int,int)", &slot_4, QMetaData::Public },
	{ "getGradient(int,int)", &slot_5, QMetaData::Public }
    };
    static const QUMethod signal_0 = {"curveChanged", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "curveChanged()", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"CurveView", parentObject,
	slot_tbl, 6,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_CurveView.setMetaObject( metaObj );
    return metaObj;
}

void* CurveView::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "CurveView" ) )
	return this;
    return QCanvasView::qt_cast( clname );
}

// SIGNAL curveChanged
void CurveView::curveChanged()
{
    activate_signal( staticMetaObject()->signalOffset() + 0 );
}

bool CurveView::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: changeColorMode((int)static_QUType_int.get(_o+1)); break;
    case 1: changeCurveMode((int)static_QUType_int.get(_o+1)); break;
    case 2: setConstantValue((int)static_QUType_int.get(_o+1)); break;
    case 3: resetActive(); break;
    case 4: static_QUType_QVariant.set(_o,QVariant(getPixmap((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)))); break;
    case 5: static_QUType_QVariant.set(_o,QVariant(getGradient((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2)))); break;
    default:
	return QCanvasView::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool CurveView::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: curveChanged(); break;
    default:
	return QCanvasView::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool CurveView::qt_property( int id, int f, QVariant* v)
{
    return QCanvasView::qt_property( id, f, v);
}

bool CurveView::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
