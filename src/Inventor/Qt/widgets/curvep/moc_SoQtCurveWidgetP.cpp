/****************************************************************************
** SoQtCurveWidgetP meta object code from reading C++ file 'SoQtCurveWidgetP.h'
**
** Created: to 16. okt 11:30:48 2003
**      by: The Qt MOC ($Id$)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "SoQtCurveWidgetP.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *SoQtCurveWidgetP::className() const
{
    return "SoQtCurveWidgetP";
}

QMetaObject *SoQtCurveWidgetP::metaObj = 0;
static QMetaObjectCleanUp cleanUp_SoQtCurveWidgetP( "SoQtCurveWidgetP", &SoQtCurveWidgetP::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString SoQtCurveWidgetP::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "SoQtCurveWidgetP", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString SoQtCurveWidgetP::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "SoQtCurveWidgetP", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* SoQtCurveWidgetP::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    static const QUMethod slot_0 = {"done", 0, 0 };
    static const QUMethod slot_1 = {"apply", 0, 0 };
    static const QUMethod slot_2 = {"reset", 0, 0 };
    static const QUMethod slot_3 = {"toggleUpdate", 0, 0 };
    static const QUParameter param_slot_4[] = {
	{ 0, &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_4 = {"changeCurveMode", 1, param_slot_4 };
    static const QUMethod slot_5 = {"setConstantValue", 0, 0 };
    static const QUMethod slot_6 = {"updateColorLabels", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "done()", &slot_0, QMetaData::Public },
	{ "apply()", &slot_1, QMetaData::Public },
	{ "reset()", &slot_2, QMetaData::Public },
	{ "toggleUpdate()", &slot_3, QMetaData::Public },
	{ "changeCurveMode(int)", &slot_4, QMetaData::Public },
	{ "setConstantValue()", &slot_5, QMetaData::Public },
	{ "updateColorLabels()", &slot_6, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"SoQtCurveWidgetP", parentObject,
	slot_tbl, 7,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_SoQtCurveWidgetP.setMetaObject( metaObj );
    return metaObj;
}

void* SoQtCurveWidgetP::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "SoQtCurveWidgetP" ) )
	return this;
    return QObject::qt_cast( clname );
}

bool SoQtCurveWidgetP::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: done(); break;
    case 1: apply(); break;
    case 2: reset(); break;
    case 3: toggleUpdate(); break;
    case 4: changeCurveMode((int)static_QUType_int.get(_o+1)); break;
    case 5: setConstantValue(); break;
    case 6: updateColorLabels(); break;
    default:
	return QObject::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool SoQtCurveWidgetP::qt_emit( int _id, QUObject* _o )
{
    return QObject::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool SoQtCurveWidgetP::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool SoQtCurveWidgetP::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
