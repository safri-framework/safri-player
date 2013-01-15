#include "widget.h"
#include "ui_widget.h"
#include "QFile"
#include "icore.h"


Widget::Widget(QWidget *parent) :
    IPlayerWidget(parent),
    ui(new Ui::Widget),
    m_pbController(Core::ICore::playbackController())
{
    ui->setupUi(this);
    QFile file;
    file.setFileName(":/style/styles.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    this->setStyleSheet(styleSheet);

    connect(this->ui->next, SIGNAL(clicked()), m_pbController->nextAction(), SLOT(trigger()));
    connect(this->ui->play, SIGNAL(clicked()), m_pbController->playPauseAction(), SLOT(trigger()));
    connect(this->ui->previous, SIGNAL(clicked()), m_pbController->previousAction(), SLOT(trigger()));
    connect(m_pbController, SIGNAL(mediaChanged(Core::Media*)), this, SLOT(mediaChanged(Media*)));
    connect(m_pbController, SIGNAL(update(int)), this, SLOT(update(int)));
}

Widget::~Widget()
{
    delete ui;
}


IPlayerWidget::PlayerWidgetPosition  Widget::getPreferedPosition()
{
    return IPlayerWidget::BOTTOM;
}

void Widget::mediaChanged(Core::Media *media)
{
    int totalTime = m_pbController->getMediaTotalTime();
    ui->seek_slider->setMaximum(totalTime);
    ui->seek_slider->setValue(0);
}


void Widget::update(int currentTime)
{
    ui->seek_slider->setValue(currentTime);
}
