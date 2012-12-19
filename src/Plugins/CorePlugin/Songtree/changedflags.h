#ifndef CHANGEDFLAGS_H
#define CHANGEDFLAGS_H

#include "../CorePlugin_global.h"

namespace Core
{
    class Genre;
    class Album;
    class Artist;

    class COREPLUGINSHARED_EXPORT ChangedFlags
    {
        public:

            ChangedFlags();

            bool artistChanged;
            Artist *artist;
            bool genreChanged;
            Genre *genre;
            bool albumChanged;
            Album *album;
    };
}

#endif // CHANGEDFLAGS_H
