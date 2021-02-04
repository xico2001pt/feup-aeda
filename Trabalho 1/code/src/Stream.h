#ifndef STREAMZ_STREAM_H
#define STREAMZ_STREAM_H
#include "StreamData.h"
#include "Viewer.h"

class Viewer;

class Stream : public StreamData{
public:
    /**
     * Class constructor
     * @param title Title of the stream
     * @param streamer Streamer making the stream
     * @param language Language of the stream
     * @param id Id of the stream
     * @param minimum_age Minimum age to watch the stream
     */
    Stream(const std::string &title, const std::string &streamer, const std::string &language, unsigned int id, const unsigned minimum_age);
    /**
     * Class constructor
     * @param title Title of the stream
     * @param streamer Streamer making the stream
     * @param language Language of the stream
     * @param id Id of the stream
     * @param minimum_age Minimum age to watch the stream
     * @param likes Number of likes
     * @param dislikes Number of dislikes
     * @param start_date String to start_date
     */
    Stream(const std::string &title, const std::string &streamer, const std::string &language, unsigned int id,
           const unsigned int minimum_age, unsigned int likes, unsigned int dislikes,
           const std::string &start_date);

    /**
     * Check if viewer can join the stream
     * @param viewer Viewer who wants to join the stream
     * @return boolean Boolean indicating if he can join the stream
     */
    bool virtual canJoin(const Viewer &viewer);
    /**
     * Adds viewer to the stream
     */
    void joinStream();
    /**
     * Removes viewer from the stream
     */
    void leaveStream();
    /**
     * Gives a like to the stream
     */
    void giveLike();
    /**
     * Remove a like from stream
     */
    void removeLike();
    /**
     * Gives a dislike to the stream
     */
    void giveDislike();
    /**
     * Remove a dislike from stream
     */
    void removeDislike();
    /**
     * Ends the stream
     */
    void endStream();
};


#endif //STREAMZ_STREAM_H
