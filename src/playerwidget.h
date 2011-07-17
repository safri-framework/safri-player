#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H
#include "playlist.h"
#include <QWidget>
#include <phonon>
#include <QStateMachine>
#include <QStyle>
#include <QToolBar>
#include <QTime>
#include <QxtGlobalShortcut>

namespace Ui {
    class PlayerWidget;
}

class PlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = 0);
    ~PlayerWidget();
    void setPlaylist(Playlist* value);
    Playlist *getPlaylist();

    void playSongAt(int value);
    void mouseDoubleClickEvent(QMouseEvent * event);


    void dragEnterEvent(QDragEnterEvent *event);
    //void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);


private:

    Ui::PlayerWidget *ui;
    Playlist *playlist;

    Phonon::MediaObject *mediaObject;
    Phonon::AudioOutput *audioOutput;

    AudioFile *currentSong;

    QxtGlobalShortcut* shortcut_play;
    QxtGlobalShortcut* shortcut_next;
    QxtGlobalShortcut* shortcut_previous;






    bool stopped;
    QStateMachine *machine;
    QState *play ;
    QState *pause ;
    QState *stop ;
    QState *noData;

    QToolBar *bar;
    QAction *playAction;

    QAction *stopAction;
    QAction *nextAction;
    QAction *previousAction;

    void setupActions();



public slots:

    void playStateSlot();
    void pauseStateSlot();
    void stopStateSlot();
    void currentSongFinished();
    void nextActionSlot();
    void previousActionSlot();
    void noDataSlot();

    void currentSourceChanged(Phonon::MediaSource);

    void updateInfo();

 signals:

    void viewModeChanged();
    void currentSourceChanged(AudioFile*);
};

#endif // PLAYERWIDGET_H
