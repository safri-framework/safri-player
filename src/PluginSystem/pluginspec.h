#ifndef PLUGINSPEC_H
#define PLUGINSPEC_H

#include "PluginSystem_global.h"
#include <QString>
#include <QList>

namespace PluginSystem
{
    class PluginDependency;
    class IPlugin;

    /**
        \brief  The PluginSpec class holds the information from the plugins
                specification XML file.
    */
    class PLUGINSYSTEMSHARED_EXPORT PluginSpec
    {
        public:

            explicit PluginSpec(QString xmlPath);

            /**
                    \brief	getter for PlugIn - Name.
                    \returns    PlugIn - Name as QString
            */
            QString getName();

            /**
                    \brief	getter for PlugIn - Version.
                    \returns    PlugIn - Version as QString
            */
            QString getVersion();

            /**
                    \brief	getter for PlugIn - Vendor.
                    \returns    PlugIn - Vendor as QString
            */
            QString getVendor();

            /**
                    \brief	getter for PlugIn - Copyright Info.
                    \returns    PlugIn - Copyright Info as QString
            */
            QString getCopyright();

            /**
                    \brief	getter for PlugIn - License Info.
                    \returns    PlugIn - License Info as QString
            */

            QString getLicense();

            /**
                    \brief	getter for PlugIn - Description.
                    \returns    PlugIn - Description as QString
            */
            QString getDescription();

            /**
                    \brief	getter for PlugIn - Url.
                    \returns    PlugIn - Url as QString
            */
            QString getUrl();

            /**
                    \brief	getter for PlugIn - Category.
                    \returns    PlugIn - Category as QString
            */
            QString getCategory();

            /**
                    \brief	getter for PlugIn - Instance.
                    \returns    Instance as IPlugin*
            */
            IPlugin* getPlugin();

            /**
                    \brief  Loads the shared library of the plugin
            */
            void loadLibrary();

        private:

            QString name;
            QString version;
            QString vendor;
            QString copyright;
            QString license;
            QString description;
            QString url;
            QString category;
            QList<PluginDependency*> dependencies;
            IPlugin* plugin;

            QString location;

            /**
                    \brief  Reads the given XML File and fills the Object with Data
                    \param  Path to the PlugIn Specification .xml File
            */
            void readXML(QString path);
    };
}

#endif // PLUGINSPEC_H
