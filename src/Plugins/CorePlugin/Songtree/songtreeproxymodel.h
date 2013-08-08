#ifndef SONGTREEPROXYMODEL_H
#define SONGTREEPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "../CorePlugin_global.h"
#include "../icore.h"
#include <QColor>

using namespace Core;
class COREPLUGINSHARED_EXPORT SongtreeProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit SongtreeProxyModel(QObject *parent = 0);

public slots:
    void expandIndex(QModelIndex index);


protected:
     bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

signals:
     void expandIndex(const QModelIndex index) const;
     void expandAll() const;


private:
     QVariant data( const QModelIndex & index, int role ) const;
     QColor textColor;
     QColor disabledTextColor;
};

#endif // SONGTREEPROXYMODEL_H
