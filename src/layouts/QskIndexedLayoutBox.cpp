/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the QSkinny License, Version 1.0
 *****************************************************************************/

#include "QskIndexedLayoutBox.h"
#include "QskQuick.h"

class QskIndexedLayoutBox::PrivateData
{
  public:
    PrivateData()
        : autoAddChildren( true )
        , blockChildAdded( false )
    {
    }

    bool autoAddChildren : 1;
    bool blockChildAdded : 1;
};

QskIndexedLayoutBox::QskIndexedLayoutBox( QQuickItem* parent )
    : QskBox( false, parent )
    , m_data( new PrivateData() )
{
    // classBegin/componentComplete -> setActive( false/true ) ?
}

QskIndexedLayoutBox::~QskIndexedLayoutBox()
{
}

void QskIndexedLayoutBox::setAutoAddChildren( bool on )
{
    if ( on != m_data->autoAddChildren )
    {
        m_data->autoAddChildren = on;
        Q_EMIT autoAddChildrenChanged();
    }
}

bool QskIndexedLayoutBox::autoAddChildren() const
{
    return m_data->autoAddChildren;
}

void QskIndexedLayoutBox::itemChange(
    QQuickItem::ItemChange change, const QQuickItem::ItemChangeData& value )
{
    switch ( change )
    {
        case QQuickItem::ItemChildAddedChange:
        {
            if ( m_data->autoAddChildren && !m_data->blockChildAdded )
            {
                if ( !qskIsTransparentForPositioner( value.item ) )
                    autoAddItem( value.item );
            }

            break;
        }
        case QQuickItem::ItemChildRemovedChange:
        {
            autoRemoveItem( value.item );
            break;
        }
#if 1
        case QQuickItem::ItemSceneChange:
        {
            // when changing the window we should run into polish anyway
            if ( value.window )
                polish();

            break;
        }
#endif

        default:
        {
            break;
        }
    }

    return Inherited::itemChange( change, value );
}

void QskIndexedLayoutBox::reparentItem( QQuickItem* item )
{
    if ( item->parent() == nullptr )
        item->setParent( this );

    if ( item->parentItem() != this )
    {
        m_data->blockChildAdded = true;
        item->setParentItem( this );
        m_data->blockChildAdded = false;
    }
}

#include "moc_QskIndexedLayoutBox.cpp"
