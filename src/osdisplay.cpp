#include "osdisplay.h"
#include "ui_osdisplay.h"

#include "audiofile.h"
#include "databasedao.h"
#include "settingsmanager.h"
#include "settingsmodule.h"

#include <QTimer>
#include <QMouseEvent>

OSDisplay::OSDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OSDisplay)
{
    ui->setupUi(this);

    timer = new QTimer(0);
}

OSDisplay::~OSDisplay()
{
    delete ui;
}

void OSDisplay::showCurrentSong(AudioFile* af)
{
    this->setMask(roundedRect(this->rect(), 20));
    this->move(512 - (this->width() / 2), 750 - this->height());

    QString cover = DatabaseDAO::getAlbumCoverByAudioFile(af);

    ui->label->setPixmap(QPixmap(cover).scaled(80, 80, Qt::IgnoreAspectRatio, Qt::FastTransformation));

    ui->label_2->setText("<span style=\"color: white;\"><h2>" + af->getArtist() + "</h2><h3>" + af->getTitle() + "</h3><h3>" + af->getAlbum() + " (" + QString::number(af->getYear()) + ")</h3></span>");

    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    this->show();

    int displayTime = SettingsManager::getInstance()->getModule("core.view")->getSetting("nowplayingDisplayTime").toInt();


    timer->setSingleShot(true);
    timer->setInterval(displayTime * 1000);

    connect(timer, SIGNAL(timeout()), this, SLOT(hide()));

    timer->start();

}

QRegion OSDisplay::roundedRect(const QRect& rect, int r)
{
        QRegion region;
        // middle and borders
        region += rect.adjusted(r, 0, -r, 0);
        region += rect.adjusted(0, r, 0, -r);
        // top left
        QRect corner(rect.topLeft(), QSize(r*2, r*2));
        region += QRegion(corner, QRegion::Ellipse);
        // top right
        corner.moveTopRight(rect.topRight());
        region += QRegion(corner, QRegion::Ellipse);
        // bottom left
        corner.moveBottomLeft(rect.bottomLeft());
        region += QRegion(corner, QRegion::Ellipse);
        // bottom right
        corner.moveBottomRight(rect.bottomRight());
        region += QRegion(corner, QRegion::Ellipse);
        return region;
}

void OSDisplay::mousePressEvent(QMouseEvent*)
{
    hide();
}
