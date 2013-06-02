#ifndef COVERSETTINGSWIDGET_H
#define COVERSETTINGSWIDGET_H

#include "Interfaces/ISettingsModuleWidget.h"
#include <QWidget>

namespace Ui {
class CoverSettingsWidget;
}

class CoverSettingsWidget : public Core::ISettingsModuleWidget
{
    Q_OBJECT
    
public:
    explicit            CoverSettingsWidget(QWidget *parent = 0);
                        ~CoverSettingsWidget();
    virtual QString     getTitle();
    virtual QIcon       getIcon();

public slots:

    virtual void        transferSettings();
    virtual bool        isModified();
    
private:
    Ui::CoverSettingsWidget *ui;

signals:
    void updateCovers();
};

#endif // COVERSETTINGSWIDGET_H
