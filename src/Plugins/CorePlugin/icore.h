#ifndef ICORE_H
#define ICORE_H

namespace Core
{
    class IPlaybackController;

    class ICore
    {
        private:

            explicit ICore();

        public:

            static ICore* instance();
            static IPlaybackController* playbackController();
            static void registerPlaybackController(IPlaybackController* pbc);

        private:

            static ICore* m_instance;
            IPlaybackController* m_playbackController;
    };
}

#endif // ICORE_H
