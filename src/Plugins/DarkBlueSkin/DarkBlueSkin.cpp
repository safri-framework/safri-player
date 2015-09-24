#include "DarkBlueSkin.h"
#include <QFile>
#include <QApplication>
#include "Songtree/SongTreeItem.h"
#include <QProxyStyle>

class Style_tweaks : public QProxyStyle
{
    public:
        Style_tweaks(QString str):QProxyStyle(str)
        {

        }
        void drawItemText(QPainter *painter, const QRect &rect, int flags, const QPalette &pal, bool enabled, const QString &text, QPalette::ColorRole textRole) const
        {
            Q_UNUSED(textRole)
            QProxyStyle::drawItemText(painter, rect, flags, pal, enabled, text);
        }
        void drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
        {
            /* do not draw focus rectangles - this permits modern styling */
            if (element == QStyle::PE_FrameFocusRect)
                return;

            if(element == QStyle::PE_IndicatorItemViewItemDrop)
            {
                if(!widget->property("indicator").isValid())
                    return;

                painter->setPen(qApp->palette().color(QPalette::Light));
                painter->drawLine(0, option->rect.y(), option->rect.x()+option->rect.width(), option->rect.y());
                return;
            }

            QProxyStyle::drawPrimitive(element, option, painter, widget);
        }
};

DarkBlueSkin::DarkBlueSkin()
{
    QFile file;
    #ifdef __APPLE__
     file.setFileName(":stylesheet/stylesheet_mac.css");
         qApp->setStyle(new Style_tweaks("windows"));
    #else
    file.setFileName(":stylesheet/stylesheet.css");
    qApp->setStyle(new Style_tweaks("macintosh"));
    #endif

    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String( file.readAll() );
    file.close();
    style = styleSheet;


    iconMap.insert("ArtistType", new QIcon(":icons/artist"));
    iconMap.insert("AlbumType", new QIcon(":icons/album"));
    iconMap.insert("SongType", new QIcon(":icons/song"));
    iconMap.insert("MediaCollectionType", new QIcon(":icons/collection"));
    iconMap.insert("CollectionType", new QIcon(":icons/collection"));
    iconMap.insert("GenreType", new QIcon(":icons/genre"));
    iconMap.insert("DecadeType", new QIcon(":icons/genre"));

    iconMap.insert("TabPlayingIndicator", new QIcon(":/icons/Ressources/tab_playing_indicator.png"));
    iconMap.insert("TabPauseIndicator", new QIcon(":/icons/Ressources/tab_pause_indicator.png"));
    iconMap.insert("NoCoverCover", new QIcon(":icons/Ressources/no_cover.png"));

     QIcon* note = new QIcon();
     note->addPixmap(QPixmap(":/icons/Ressources/note_highlight.png"), QIcon::Normal, QIcon::On);
     note->addPixmap(QPixmap(":/icons/Ressources/note_passive.png"),QIcon::Normal, QIcon::Off);
     iconMap.insert("Note",note);

    QPalette palette = qApp->palette();
    //ui->pLabel->setPalette(palette);
    palette.setColor(QPalette::ButtonText, QColor("#DFDFDF"));
    palette.setColor(QPalette::Text, QColor("#DFDFDF"));
    palette.setColor(QPalette::WindowText, QColor("#DFDFDF"));
    palette.setColor(QPalette::Highlight,QColor(132,195,237));
    palette.setColor(QPalette::HighlightedText,QColor(255,255,255));
    palette.setColor(QPalette::Light,QColor(132,195,237));



    qApp->setPalette(palette);
   // qApp->setFont(QFont("Entypo Social"));
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
    return 0;
}

QStyledItemDelegate *DarkBlueSkin::getPlaylistItemDelegate()
{
    return 0;
}

void DarkBlueSkin::paintCurrentSongRowInPlaylist(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    painter->fillRect(option.rect, QColor(81,112,138, 255) );

    painter->setPen(QColor(47,47,47, 220));
    painter->drawLine(option.rect.x(), option.rect.height()-1+option.rect.y(), option.rect.width()+option.rect.x(), option.rect.height()-1+option.rect.y());
    painter->setPen(QColor(255,255,255,12));
    painter->drawLine(option.rect.x(), option.rect.y(), option.rect.width()+option.rect.x(), option.rect.y());

    if (index.column() == 0)
    {
        painter->drawPixmap(option.rect.x()+5, option.rect.y() + 8, 13, 13, QPixmap(":/icons/Ressources/playlist_playing_indicator.png"));
    }
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
    Q_UNUSED( index )
    return QSize(option.rect.width(), 30);
}

void DarkBlueSkin::paintTreeItem(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED( index )
    if(option.features && QStyleOptionViewItem::Alternate)
        painter->fillRect(option.rect, QColor(255,255,255,7));
}

QSize DarkBlueSkin::treeViewSizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED( index )
    return QSize(option.rect.width(), 25);
}
