#include "Safri3Skin.h"
#include <QFile>
#include <QSize>
#include <QPainter>
#include <QtWidgets/qstyleoption.h>
#include <QApplication>

Safri3Skin::Safri3Skin()
{
    QFile file;
    file.setFileName(":stylesheet/stylesheet.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String( file.readAll() );
    file.close();
    style = styleSheet;

	iconMap.insert("TabPlayingIndicator", new QIcon(":/icons/SAFRI_UI/tab_playing_indicator.png"));
	iconMap.insert("TabPauseIndicator", new QIcon(":/icons/SAFRI_UI/tab_pause_indicator.png"));

    QPalette palette = qApp->palette();
    //ui->pLabel->setPalette(palette);
    palette.setColor(QPalette::ButtonText, QColor(45,45,46));
    palette.setColor(QPalette::Text, QColor("#2C2D2E"));
    palette.setColor(QPalette::WindowText, QColor(45,45,46));
    palette.setColor(QPalette::Highlight,QColor(229,204,128,40));
    palette.setColor(QPalette::HighlightedText,QColor("black"));
    palette.setColor(QPalette::Light,QColor(229,204,128));

    QIcon* note = new QIcon();
    note->addPixmap(QPixmap(":/icons/SAFRI_UI/music_icon.png"), QIcon::Normal);
    iconMap.insert("Note",note);

    qApp->setPalette(palette);
}

Safri3Skin::~Safri3Skin()
{
    QList<QIcon*> icons = iconMap.values();
    for(int i = 0; i < icons.size(); i++)
    {
        delete icons.at(i);
    }
}

QString Safri3Skin::getStyleSheet()
{
    return style;
}

QStyledItemDelegate *Safri3Skin::getSongTreeItemDelegate()
{
    return 0;
}

QStyledItemDelegate *Safri3Skin::getPlaylistItemDelegate()
{
    return 0;
}

void Safri3Skin::paintCurrentSongRowInPlaylist(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->fillRect(option.rect, QColor("#E1DBBD") );
    if (index.column() == 0)
    {
        painter->drawPixmap(option.rect.x()+5, option.rect.y() + 3, 13, 13, QPixmap(":/icons/SAFRI_UI/tab_playing_indicator.png"));
    }
    Q_UNUSED(option)
    Q_UNUSED(index)
}

void Safri3Skin::paintRowInPlaylist(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(index)
}

QIcon *Safri3Skin::getIcon(QString itemType)
{
    return iconMap.value(itemType, 0);
}

QString Safri3Skin::getName()
{
    return "Safri 3 Skin";
}

QSize Safri3Skin::playlistRowSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return QSize(option.rect.width(), 20);
}

void Safri3Skin::paintTreeItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(painter)
    Q_UNUSED(option)
    Q_UNUSED(index)
}

QSize Safri3Skin::treeViewSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED( option )
    Q_UNUSED( index )
    return QSize();
}
