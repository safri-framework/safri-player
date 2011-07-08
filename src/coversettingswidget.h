#ifndef COVERSETTINGSWIDGET_H
#define COVERSETTINGSWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QStringList>
#include <QStringListModel>

#include "databasedao.h"

namespace Ui {
    class CoverSettingsWidget;
}

class CoverSettingsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CoverSettingsWidget(QWidget *parent = 0);
    ~CoverSettingsWidget();

private:
    Ui::CoverSettingsWidget *ui;
    QStringListModel *filenamePatternModel;

private slots:
    void on_addCoverFilePattern_clicked();
};

#endif // COVERSETTINGSWIDGET_H
