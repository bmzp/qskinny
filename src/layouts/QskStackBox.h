/******************************************************************************
 * QSkinny - Copyright (C) 2016 Uwe Rathmann
 * This file may be used under the terms of the QSkinny License, Version 1.0
 *****************************************************************************/

#ifndef QSK_STACK_BOX_H
#define QSK_STACK_BOX_H

#include "QskIndexedLayoutBox.h"

class QskStackBoxAnimator;

class QSK_EXPORT QskStackBox : public QskIndexedLayoutBox
{
    Q_OBJECT

    Q_PROPERTY( int currentIndex READ currentIndex
        WRITE setCurrentIndex NOTIFY currentIndexChanged )

    Q_PROPERTY( QQuickItem* currentItem READ currentItem
        WRITE setCurrentItem NOTIFY currentItemChanged )

    using Inherited = QskBox;

  public:
    explicit QskStackBox( QQuickItem* parent = nullptr );
    QskStackBox( bool autoAddChildren, QQuickItem* parent = nullptr );

    ~QskStackBox() override;

    bool isEmpty() const;

    int itemCount() const;
    QQuickItem* itemAtIndex( int index ) const;
    int indexOf( const QQuickItem* ) const;

    void addItem(
        QQuickItem*, Qt::Alignment alignment = Qt::Alignment() );

    void insertItem(
        int index, QQuickItem*, Qt::Alignment alignment = Qt::Alignment() );

    void removeItem( const QQuickItem* );
    void removeAt( int index );

    QQuickItem* currentItem() const;
    int currentIndex() const;

    void setDefaultAlignment( Qt::Alignment );
    Qt::Alignment defaultAlignment() const;

    void setAlignmentAt( int index, Qt::Alignment );
    Qt::Alignment alignmentAt( int index ) const;

    void setAlignment( const QQuickItem*, Qt::Alignment );
    Qt::Alignment alignment( const QQuickItem* ) const;

    void setAnimator( QskStackBoxAnimator* );
    const QskStackBoxAnimator* animator() const;
    QskStackBoxAnimator* animator();

    QSizeF contentsSizeHint() const override;
    qreal heightForWidth( qreal width ) const override;
    qreal widthForHeight( qreal height ) const override;

    QRectF geometryForItemAt( int index ) const;

  Q_SIGNALS:
    void defaultAlignmentChanged( Qt::Alignment );

  public Q_SLOTS:
    void setCurrentIndex( int index );
    void setCurrentItem( const QQuickItem* );
    void clear( bool autoDelete = false );

  Q_SIGNALS:
    void currentIndexChanged( int index );
    void currentItemChanged( QQuickItem* );

  protected:
    bool event( QEvent* ) override;
    void updateLayout() override;

    void autoAddItem( QQuickItem* ) override final;
    void autoRemoveItem( QQuickItem* ) override final;

    QskStackBoxAnimator* effectiveAnimator();

  private:
    void removeItemInternal( int index, bool autoDelete );

    class PrivateData;
    std::unique_ptr< PrivateData > m_data;
};

inline bool QskStackBox::isEmpty() const
{
    return itemCount() <= 0;
}

#endif
