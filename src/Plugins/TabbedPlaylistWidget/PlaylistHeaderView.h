#ifndef PLAYLISTHEADERVIEW_H
#define PLAYLISTHEADERVIEW_H

#include <QHeaderView>
#include <QList>

class PlaylistHeaderView : public QHeaderView
{
    Q_OBJECT
    public:

        explicit PlaylistHeaderView(QWidget *parent = 0);
        ~PlaylistHeaderView();

        virtual void setModel(QAbstractItemModel *model);

    private slots:

        void onContextMenuRequested(QPoint pos);
        void toggleSectionVisibility(int section);
        void saveSectionVisibilitySettings();
        void settingsChanged(QString setting);

    private:

        void setSectionVisibilityFromSettings(QString selectedHeaders);
};

#endif // PLAYLISTHEADERVIEW_H
