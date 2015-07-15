#ifndef QSPOTIFYRINGBUFFER_H
#define QSPOTIFYRINGBUFFER_H

#define BUF_SIZE (1 << 18) // 256KB

class QByteArray;

class QSpotifyRingbuffer
{
public:
    QSpotifyRingbuffer();
    ~QSpotifyRingbuffer();
    void close();
    /**
     * \a reset is the same as calling \a close() and \a open() in a sequence.
     */
    void reset();
    void open();

    int read(char *data, int numBytes);
    int write(const char *data, int numBytes);

    int freeBytes();
    int filledBytes() { return m_size; }

    bool isOpen() { return m_isOpen; }

private:
    char *m_data;
    int m_readPos;
    int m_writePos;

    int m_size;

    bool m_isOpen;
};

#endif // QSPOTIFYRINGBUFFER_H
