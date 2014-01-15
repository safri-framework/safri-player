#include "pluginviewermodel.h"
#include "pluginmanager.h"
#include <QDebug>
using namespace PluginSystem;

PluginviewerModel::PluginviewerModel(QList<PluginSpec *> plugins, QHash<QString, bool> config,QObject *parent) :
    QAbstractTableModel(parent), plugins(plugins), config(config)
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
        return 4;
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
        if(role == Qt::CheckStateRole)
        {
            if(index.column() == 3)
            {
                QString string = plugins.at(index.row())->getVendor()+"."+plugins.at(index.row())->getName();
                return config.value(string, false) ? Qt::Checked : Qt::Unchecked;
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
            case 3:
                return "Enabled";

            default:
                return QVariant();
        }
    }

    return QVariant();
}

bool PluginviewerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid())
        return false;
    if (role == Qt::CheckStateRole)
    {
        if ((Qt::CheckState)value.toInt() == Qt::Checked)
        {
            QString string = plugins.at(index.row())->getVendor()+"."+plugins.at(index.row())->getName();
            PluginManager::instance()->setPluginEnabled(string, true);
            config.remove(string);
            config.insert(string, true);
            return true;
        }
        else
        {
            QString string = plugins.at(index.row())->getVendor()+"."+plugins.at(index.row())->getName();
            PluginManager::instance()->setPluginEnabled(string, false);
            config.remove(string);
            config.insert(string, false);
            return true;
        }
    }
    return false;
}

Qt::ItemFlags PluginviewerModel::flags(const QModelIndex &index) const
{
    if(index.column() == 3)
        return Qt::ItemIsUserCheckable | QAbstractTableModel::flags(index);
    return QAbstractTableModel::flags(index);
}
