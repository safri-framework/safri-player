#ifndef PLUGINVIEWERMODEL_H
#define PLUGINVIEWERMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <pluginspec.h>

namespace PluginSystem
{
    class PluginviewerModel : public QAbstractTableModel
    {
        Q_OBJECT
        public:
            explicit PluginviewerModel(QList<PluginSpec*> plugins, QHash<QString, bool> config, QObject *parent = 0);

            int rowCount(const QModelIndex &parent) const;
            int columnCount(const QModelIndex &parent) const;
            QVariant data(const QModelIndex &index, int role) const;
            QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
            bool setData(const QModelIndex &index, const QVariant &value, int role);
            Qt::ItemFlags flags(const QModelIndex &index) const;
        private:

            QList<PluginSpec*> plugins;
            QHash<QString, bool> config;
    };
}
#endif // PLUGINVIEWERMODEL_H
