/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the QSkinny License, Version 1.0
 *****************************************************************************/

#include "QskLayoutHint.h"
#include "QskControl.h"
#include <qnamespace.h>

QskLayoutHint::QskLayoutHint()
    : QskLayoutHint( 0.0, 0.0, QskLayoutHint::unlimited )
{
}

QskLayoutHint::QskLayoutHint( qreal minimum, qreal preferred, qreal maximum )
    : m_minimum( minimum )
    , m_preferred( preferred )
    , m_maximum( maximum )
{
}

qreal QskLayoutHint::size( int which ) const
{
    switch( which )
    {
        case Qt::MinimumSize:
            return m_minimum;

        case Qt::PreferredSize:
            return m_preferred;

        case Qt::MaximumSize:
            return m_maximum;

        default:
            return 0.0;
    }
}

void QskLayoutHint::setSize( int which, qreal size )
{
    switch (which)
    {
        case Qt::MinimumSize:
            m_minimum = size;
            break;

        case Qt::PreferredSize:
            m_preferred = size;
            break;

        case Qt::MaximumSize:
            m_maximum = size;
            break;

        default:
            break;
    }
}

void QskLayoutHint::expandTo( const QskLayoutHint& other )
{
    m_minimum = qMax( m_minimum, other.m_minimum );
    m_preferred = qMax( m_preferred, other.m_preferred );
    m_maximum = qMax( m_maximum, other.m_maximum );
}

void QskLayoutHint::normalize()
{
    m_minimum = qMax( m_minimum, qreal( 0.0 ) );
    m_maximum = qMax( m_minimum, m_maximum );
    m_preferred = qBound( m_minimum, m_preferred, m_maximum );
}

bool QskLayoutHint::isDefault() const
{
    return ( m_minimum == 0.0 ) && ( m_preferred == 0.0 )
        && ( m_maximum == QskLayoutHint::unlimited );
}

qreal QskLayoutHint::combined( int which, qreal value1, qreal value2 )
{
    if ( which == Qt::MaximumSize )
    {
        if ( value1 < 0.0 )
            return value2;

        if ( value2 < 0.0 )
            return value1;

        return qMin( value1, value2 );
    }

    return qMax( value1, value2 );
}

#ifndef QT_NO_DEBUG_STREAM

#include <qdebug.h>

static inline QString qskHintValueString( qreal value )
{
    if ( value >= QskLayoutHint::unlimited )
        return QStringLiteral( "unlimited" );
    else
        return QString::number( value );
}

QDebug operator<<( QDebug debug, const QskLayoutHint& hint )
{
    QDebugStateSaver saver( debug );
    debug.nospace();

    debug << "LayoutHint" << "( "
        << qskHintValueString( hint.minimum() ) << ", "
        << qskHintValueString( hint.preferred() ) << ", "
        << qskHintValueString( hint.maximum() ) << " )";

    return debug;
}

#endif
