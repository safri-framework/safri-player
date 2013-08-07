#include "DarkBlueSkin.h"
#include <QFile>
#include <QApplication>

DarkBlueSkin::DarkBlueSkin()
{
    QFile file;
    file.setFileName(":stylesheet/stylesheet.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String( file.readAll() );
    file.close();
    style = styleSheet;

    iconMap.insert("ArtistType", new QIcon(":icons/Ressources/Artist_16.png"));
    iconMap.insert("AlbumType", new QIcon(":icons/Ressources/Album_16.png"));
    iconMap.insert("SongType", new QIcon(":icons/Ressources/Song_16.png"));
    iconMap.insert("CollectionType", new QIcon(":icons/Ressources/Collection_16.png"));
    iconMap.insert("GenreType", new QIcon(":icons/Ressources/Genre_16.png"));

    QPalette palette = qApp->palette();
    //ui->pLabel->setPalette(palette);
    palette.setColor(QPalette::ButtonText, QColor("#DFDFDF"));
    palette.setColor(QPalette::Text, QColor("#DFDFDF"));
    palette.setColor(QPalette::WindowText, QColor("#DFDFDF"));
    palette.setColor(QPalette::Highlight,QColor(0,255,0));
    qApp->setPalette(palette);
}

DarkBlueSkin::~DarkBlueSkin()
{
    QList<QIcon*> icons = iconMap.values();
    for(int i = 0; i < icons.size(); i++)
    {
        delete icons.at(i);
    }

}

QString DarkBlueSkin::getStyleSheet()
{
    return style;
}

QStyledItemDelegate *DarkBlueSkin::getSongTreeItemDelegate()
{

}

QStyledItemDelegate *DarkBlueSkin::getPlaylistItemDelegate()
{

}

void DarkBlueSkin::paintCurrentSongRowInPlaylist(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    painter->setPen(QColor(47,47,47, 220));
    painter->drawLine(option.rect.x(), option.rect.height()-1+option.rect.y(), option.rect.width()+option.rect.x(), option.rect.height()-1+option.rect.y());
    painter->setPen(QColor(255,255,255,12));
    painter->drawLine(option.rect.x(), option.rect.y(), option.rect.width()+option.rect.x(), option.rect.y());
    painter->drawPixmap(option.rect.x()+5, option.rect.y() + 1, 13, 13, QPixmap(":images/ressources/play_icon.png"));
    painter->fillRect(option.rect, QColor(81,112,138, 255) );
}

void DarkBlueSkin::paintRowInPlaylist(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    painter->setPen(QColor(47,47,47, 220));
    painter->drawLine(option.rect.x(), option.rect.height()-1+option.rect.y(), option.rect.width()+option.rect.x(), option.rect.height()-1+option.rect.y());
    painter->setPen(QColor(255,255,255,12));
    painter->drawLine(option.rect.x(), option.rect.y(), option.rect.width()+option.rect.x(), option.rect.y());
    painter->fillRect(option.rect, QColor(0,0,0, 56) );
}

QIcon *DarkBlueSkin::getIcon(QString itemType)
{
    return iconMap.value(itemType, 0);
}

QString DarkBlueSkin::getName()
{
    return "DarkBlueSkin";
}

QSize DarkBlueSkin::playlistRowSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(option.rect.width(), 30);
}
