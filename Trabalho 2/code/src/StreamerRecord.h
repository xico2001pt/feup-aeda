#ifndef STREAMZ_STREAMERRECORD_H
#define STREAMZ_STREAMERRECORD_H
#include <string>

class Streamer;

class StreamerRecord {
    Streamer * streamer; /**< Pointer to the streamer, if active */
    std::string nickname; /**< Nickname of the streamer */
    bool active; /**< Indicates if the streamer is active */
public:
    /**
     * Class constructor
     * @param st Pointer to the streamer
     */
    explicit StreamerRecord(Streamer * st);
    /**
     * Class constructor
     * @param nick Nickname of the streamer
     */
    explicit StreamerRecord(const std::string &nick);
    /**
     * Copy constructor
     * @param sr StreamerRecord that will be copied
     */
    StreamerRecord(const StreamerRecord &sr);
    /**
     * Class destructor
     */
    ~StreamerRecord();
    /**
     * Gets the streamer pointer, if active
     * @return streamer pointer
     */
    const Streamer * getStreamer() const;
    /**
     * Gets the nickname of the streamer
     * @return String containing the nickname of the streamer
     */
    std::string getNickname() const;
    /**
     * Indicates if the streamer is active
     * @return boolean indicating if the streamer is active
     */
    bool isActive() const;
};

#endif //STREAMZ_STREAMERRECORD_H
