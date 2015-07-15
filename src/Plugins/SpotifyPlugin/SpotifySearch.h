#ifndef SPOTIFYSEARCH_H
#define SPOTIFYSEARCH_H

#include <QtWidgets/QWidget>
#include "../libQtSpotify/QtSpotify"
#include "Interfaces/IMediaCollection.h"

using namespace Core;
namespace Ui {
class SpotifySearch;
}

class SpotifySearch : public QWidget
{
    Q_OBJECT
    
public:
    explicit SpotifySearch(QWidget *parent = 0);
    ~SpotifySearch();
    
private:
    Ui::SpotifySearch *ui;
    QSpotifySession* _session;
    QSpotifySearch* _search;
    IMediaCollection* _collection;

    bool addTrack(std::shared_ptr<QSpotifyTrack> ptr);

private slots:
    void tagTracklist(QSpotifyTrackList* list);
    void search();
    void loggedIn();
    void resultsChanged();
    void browseFinished();
};

#endif // SPOTIFYSEARCH_H
