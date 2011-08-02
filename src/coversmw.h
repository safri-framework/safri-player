#ifndef COVERSMW_H
#define COVERSMW_H

#include <QDebug>
#include "settingsmodulewidget.h"

#include <QStringList>
#include <QStringListModel>

namespace Ui
{
    class CoverSMW;
}

class CoverSMW : public SettingsModuleWidget
{
    Q_OBJECT

    public:
        explicit CoverSMW(SettingsModule* settingsModule, QWidget *parent = 0);
        ~CoverSMW();

    public slots:

        virtual void saveSettings();

    private slots:

        void on_addCoverFilePattern_clicked();
        void on_deleteCoverFilePattern_clicked();
        void on_editCoverFilePattern_clicked();

    private:

        Ui::CoverSMW *ui;
        QStringListModel *filenamePatternModel;
};

#endif // COVERSMW_H
