#ifndef STREAMZ_PRIVATESTREAM_H
#define STREAMZ_PRIVATESTREAM_H
#include "Stream.h"
#include <vector>

/**
 * Represents a comment made by a Viewer
 */
struct Comment{
    Date date; /**< Comment date */
    std::string nickname; /**< Viewer nickname */
    std::string comment; /**< Comment message */
};

class PrivateStream : public Stream {
public:
    /**
     * Class constructor
     * @param title Title of the stream
     * @param streamer Streamer making the stream
     * @param language Language of the stream
     * @param id Identification of the stream
     * @param minimum_age Minimum age to watch the stream
     * @param max_capacity Maximum capacity of the stream
     * @param allowed_viewers Viewers allowed to watch the stream
     */
    PrivateStream(const std::string &title, const std::string &streamer, const std::string &language, unsigned int id, unsigned minimum_age, unsigned max_capacity, const std::vector<std::string> &allowed_viewers);

    /**
     * Class constructor
     * @param title Title of the stream
     * @param streamer Streamer making the stream
     * @param language Language of the stream
     * @param id Identification of the stream
     * @param minimum_age Minimum age to watch the stream
     * @param max_capacity Maximum capacity of the stream
     * @param allowed_viewers Viewers allowed to watch the stream
     * @param likes Number of likes
     * @param dislikes Number of dislikes
     * @param start_date std::string that represents start date of stream
     * @param comments Vector of stream comments
     */
    PrivateStream(const std::string &title, const std::string &streamer, const std::string &language, unsigned int id, unsigned minimum_age, unsigned max_capacity, const std::vector<std::string> &allowed_viewers, unsigned int likes, unsigned int dislikes, const std::string &start_date, const std::vector<Comment> &comments);
    /**
     * Check if viewer can join the stream
     * @param viewer Viewer who wants to join the stream
     * @return Boolean indicating if he can join the stream
     */
    bool canJoin(Viewer &viewer);
    /**
     * Gets the comments of the stream
     * @return Comments of the stream
     */
    std::vector<Comment> & getComments();
    /**
     * Writes in the indicated ostream the information about the stream
     * @param os Output stream where the information will be writen
     * @return Stream where the information will be writen
     */
    std::ostream& print(std::ostream & os) const;
    /**
     * Adds a comment to the stream
     * @param viewer Viewer leaving the comment
     * @param comment Comment the viewer is leaving
     */
    void addComment(Viewer &viewer, const std::string &comment);
private:
    /**
     * Maximum capacity of the stream
     */
    unsigned max_capacity;
    /**
     * Vector with the viewers allowed to watch the stream
     */
    std::vector<std::string> allowed_viewers;
    /**
     * Vector with all the comments
     */
    std::vector<Comment> comments;
};

#endif //STREAMZ_PRIVATESTREAM_H
