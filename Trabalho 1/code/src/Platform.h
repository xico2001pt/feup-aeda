#ifndef STREAMZ_PLATFORM_H
#define STREAMZ_PLATFORM_H
#include "Exceptions.h"
#include "Archive.h"
#include <vector>
#include <string>
#include <memory>
#include <list>

#define MINIMUM_VIEWER_AGE 12
#define MINIMUM_STREAMER_AGE 15

class User;
class Viewer;
class Streamer;
class StreamData;
class Stream;

/*
 * Sorting parameter
 */
enum sortingMode{
    views,
    id,
    minimum_age,
    likes
};
/*
 * Sorting order
 */
enum sortingOrder{
    ascending,
    descending
};

class Platform {
private:
    friend class Admin;
    bool test = false;/**< If test = true the Platform is in test mode that doesn't read nor write information to files */

    std::vector<User *> users; /*< Users*/
    std::vector<std::shared_ptr<Stream>> active_streams; /*< Active streams */

    unsigned int stream_id_count = 1; /*< Track stream ids to be assigned to new streams*/

    struct IOFiles{
        const std::string user_file = "user.txt";
        const std::string active_stream_file = "active_streams.txt";
        const std::string archived_stream_file = "archive.txt";
    };
    IOFiles files; /*< Holds file information to save data across sessions */

    Archive archive; /*< Archive containing all terminated streams */

    /**
     * Get the 10 highest streams in active_streams using F predicate as a comparator
     * Non-const because it relies on partial sorting of active_streams but
     * the vector active_streams will be restored to it's original state before returning
     * @param F pred - Predicate that will be used by std::max_element
     * @return vector<weak_ptr<Stream>> containing all the top streams in descending order
     */
    template <typename F>
    std::vector<std::weak_ptr<Stream>> getTopActiveStreams(F pred);

    /**
     * Sort all active streams according to pred
     * @param pred - predicate that will be passed to std::sort()
     */
    template <typename F>
    void sortActiveStreams(F pred);

    /**
     * Check if a user with a given nickname already exists
     * @param nickname - user nickname
     * @return true if user exists
     */
    bool userExists(const std::string &nickname) const;

    /**
     * Read all users from a file and place them in users vector
     */
    void readUsersFromFile();

    /**
     * Read a single user from a file and place him in the users vector
     * @param file - fstream to file
     * @return true if successful
     */
    bool readUserFromFile(std::ifstream &file);

    /**
     * Read all streams from a file and place them in active_streams vector
     */
    void readStreamsFromFile();

    /**
     * Read a single stream from a file and place it in active_streams vector
     * @param file - fstream to file
     * @return true if successful
     */
    bool readStreamFromFile(std::ifstream &file);

public:
    /**
     * Constructor
     */
    Platform();

    /**
     * Destructor
     */
    ~Platform();

    /**
     * Store all current information in files specified in IOFiles files
     */
    void save();

    /**
     * Sort active_streams according to the specified mode and order
     * @param mode - sortingMode (views,id,minimum_age,likes)
     * @param order - sortingOrder (ascending,descending)
     */
    void sort(sortingMode mode, sortingOrder order);

    /**
     * Register a new Viewer to the Platform
     * @param nickname - viewer's nickname
     * @param name - viewer's name
     * @param birth_date - viewer's birthday
     * @return true if registered with success
     */
    bool registerViewer(const std::string &nickname, const std::string &name, const Date &birth_date);

    /**
     * Register a new Streamer to the Platform
     * @param nickname - streamers' nickname
     * @param name - streamer's name
     * @param birth_date - streamer's birthday
     * @return true if registered with success
     */
    bool registerStreamer(const std::string &nickname, const std::string &name, const Date &birth_date);

    /**
     * Get number of users registered in the platform
     * @return unsigned int
     */
    unsigned int getUserCount() const;

    /**
     * Get number of active streams in the platform
     * @return unsigned int
     */
    unsigned int getActiveStreamCount() const;

    /**
     * Get number of archived streams
     * @return unsigned int
     */
    unsigned int getArchivedStreamCount() const;

    /**
     * Get total number of streams (active + archived) in the platform
     * @return unsigned int
     */
    unsigned int getTotalStreamCount() const;

    /**
     * Get user by nickname
     * @param nickname
     * @throws UserDoesNotExist
     * @return corresponding User *
     */
    User * getUser(const std::string &nickname);

    /**
     * Delete a user from the Platform
     * @param nickname - user's nickname
     * @return true if user was deleted with success
     */
    bool deleteUser(const std::string &nickname);

    /**
     * Delete a stream from the Platform
     * @param id - stream id
     * @return true if deleted with success
     */
    bool deleteStream(unsigned int id);

    /**
     * Return weak_ptr to stream hosted by streamer
     * @param streamer - nickname of the streamer
     * @param viewer - viewer reference
     * @throws StreamerNotStreaming
     * @return weak_ptr to stream
     */
    std::weak_ptr<Stream> joinStream(const std::string &streamer, const Viewer &viewer);

    /**
     * Return weak_ptr to stream with id
     * @param id - unique stream id
     * @param viewer - viewer reference
     * @throws StreamDoesNotExist, StreamNoLongerActive
     * @return weak_ptr to stream
     */
    std::weak_ptr<Stream> joinStream(unsigned int id, const Viewer &viewer);

    /**
     * Start a Public Stream and return a weak_ptr to it
     * @param title - Stream title
     * @param streamer - Streamer nickname
     * @param language - Stream language
     * @param minimum_age - Minimum viewer age
     * @return weak_ptr to stream
     */
    std::weak_ptr<Stream> startPublicStream(const std::string &title, const std::string &streamer, const std::string &language,
                                            unsigned minimum_age);

    /**
     * Start a Private Stream and return a weak_ptr to it
     * @param title - Stream Title
     * @param streamer - Streamer nickname
     * @param language - Stream language
     * @param minimum_age - Minimum viewer age
     * @param max_capacity - Maximum number of viewers
     * @param allowed_viewers - Vector with allowed viewers nicknames
     * @return weak_ptr to stream
     */
    std::weak_ptr<Stream> startPrivateStream(const std::string &title, const std::string &streamer, const std::string &language,
                                             unsigned minimum_age, unsigned max_capacity,
                                             const std::vector<std::string> &allowed_viewers);

    /**
     * End stream with a given id
     * @param id - stream id
     */
    void endStream(unsigned int id);

    /**
     * Get top 10 active streams by views and by likes
     */
    void topActiveStreams();

    /**
     * Get top 10 archived streams by views and by likes
     */
    void topArchivedStreams() const;

    /**
     * Show all streams active in the platform that match the filters
     * @param language_filter - Language of streams to be shown
     * @param minimum_age - Only streams with minimum_age < specified minimum_age will be shown
     */
    void showStreams(const std::string &language_filter = "", unsigned minimum_age = 99999) const;

    /**
     * Show all streams in archive
     */
    void showArchive();

    /**
     * Show all streams in a user history
     * @param ids - User history
     * @param filter - feedback char 'L','D','-', only streams with feedback == filter will be shown,
     *         e.g if filter='L' only liked streams will be shown
     */
    void showStreamHistory(const std::vector<std::pair<unsigned int, char>> &history, char filter=0) const;

    /**
     * Show all users in the platform
     */
    void showUsers() const;

    /**
     * Clear all vectors in memory
     * Does not remove anything from files
     */
    void testMode();

    /**
     * Get a vector with all active_streams (Used for testing purposes)
     * @return active_streams
     */
    std::vector<std::shared_ptr<Stream>> testGetStreams();
};


#endif //STREAMZ_PLATFORM_H
