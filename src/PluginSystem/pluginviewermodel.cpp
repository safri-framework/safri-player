#include "pluginviewermodel.h"

using namespace PluginSystem;

PluginviewerModel::PluginviewerModel(QList<PluginSpec*> &plugins, QObject *parent) :
    QAbstractTableModel(parent), plugins(plugins)
{
}

int PluginSystem::PluginviewerModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    else
    {
        return plugins.size();
    }
}

int PluginSystem::PluginviewerModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }
    else
    {
        return 3;
    }
}

QVariant PluginSystem::PluginviewerModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
    {
        if (role == Qt::DisplayRole)
        {
            switch (index.column())
            {
                case 0:
                    return plugins.at(index.row())->getName();

                case 1:
                    return plugins.at(index.row())->getVersion();

                case 2:
                    return plugins.at(index.row())->getVendor();

                default:
                    return QVariant();
            }
        }
    }

    return QVariant();
}

QVariant PluginviewerModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return "Name";

            case 1:
                return "Version";

            case 2:
                return "Anbieter";

            default:
                return QVariant();
        }
    }

    return QVariant();
}
