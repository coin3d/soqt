/****************************************************************************
** GradientEditor meta object code from reading C++ file 'GradientEditor.h'
**
** Created: on 17. sep 13:22:18 2003
**      by: The Qt MOC ($Id$)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "GradientEditor.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *GradientEditor::className() const
{
    return "GradientEditor";
}

QMetaObject *GradientEditor::metaObj = 0;
static QMetaObjectCleanUp cleanUp_GradientEditor( "GradientEditor", &GradientEditor::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString GradientEditor::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GradientEditor", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString GradientEditor::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "GradientEditor", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* GradientEditor::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "min", &static_QUType_ptr, "float", QUParameter::In }
    };
    static const QUMethod slot_0 = {"setMin", 1, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "max", &static_QUType_ptr, "float", QUParameter::In }
    };
    static const QUMethod slot_1 = {"setMax", 1, param_slot_1 };
    static const QUMethod slot_2 = {"updateValueLabels", 0, 0 };
    static const QUMethod slot_3 = {"updateAll", 0, 0 };
    static const QUMethod slot_4 = {"accept", 0, 0 };
    static const QUMethod slot_5 = {"reject", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "setMin(float)", &slot_0, QMetaData::Public },
	{ "setMax(float)", &slot_1, QMetaData::Public },
	{ "updateValueLabels()", &slot_2, QMetaData::Public },
	{ "updateAll()", &slot_3, QMetaData::Public },
	{ "accept()", &slot_4, QMetaData::Public },
	{ "reject()", &slot_5, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out }
    };
    static const QUMethod signal_0 = {"accepted", 1, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ 0, &static_QUType_int, 0, QUParameter::Out }
    };
    static const QUMethod signal_1 = {"rejected", 1, param_signal_1 };
    static const QMetaData signal_tbl[] = {
	{ "accepted()", &signal_0, QMetaData::Public },
	{ "rejected()", &signal_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"GradientEditor", parentObject,
	slot_tbl, 6,
	signal_tbl, 2,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_GradientEditor.setMetaObject( metaObj );
    return metaObj;
}

void* GradientEditor::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "GradientEditor" ) )
	return this;
    return QWidget::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL accepted
int GradientEditor::accepted()
{
    int something;
    if ( signalsBlocked() )
	return something;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return something;
    QUObject o[1];
    static_QUType_int.set(o,something);
    activate_signal( clist, o );
    return static_QUType_int.get(o);
}

// SIGNAL rejected
int GradientEditor::rejected()
{
    int something;
    if ( signalsBlocked() )
	return something;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return something;
    QUObject o[1];
    static_QUType_int.set(o,something);
    activate_signal( clist, o );
    return static_QUType_int.get(o);
}

bool GradientEditor::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: setMin((float)(*((float*)static_QUType_ptr.get(_o+1)))); break;
    case 1: setMax((float)(*((float*)static_QUType_ptr.get(_o+1)))); break;
    case 2: updateValueLabels(); break;
    case 3: updateAll(); break;
    case 4: accept(); break;
    case 5: reject(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool GradientEditor::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: static_QUType_int.set(_o,accepted()); break;
    case 1: static_QUType_int.set(_o,rejected()); break;
    default:
	return QWidget::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool GradientEditor::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool GradientEditor::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
