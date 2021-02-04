#ifndef STREAMZ_ARCHIVE_H
#define STREAMZ_ARCHIVE_H
#include "StreamData.h"
#include <vector>
#include <list>


class Archive {
private:
    friend class Admin;
    bool test = false; /**< If test = true, then the Archive is in test mode, that doesn't read nor write information to files */
    std::string filename; /**< Name of the file used for storing StreamData */
    std::vector<StreamData> streams; /**< Stores StreamData of every stream */
    std::list<StreamData> top_views; /**< List with StreamData of the streams (up to 10) with most views, sorted in ascending order*/
    std::list<StreamData> top_likes; /**< List with StreamData of the streams (up to 10) with most likes, sorted in ascending order*/

    /**
     * Search vector streams for StreamData with the given id
     * @param id - Id of stream
     * @returns position of stream in the vector or -1 is the stream does not exist
     */
    int binarySearch(unsigned int id) const;

    /**
     * Read a single StreamData from a file
     * Returns true if read successfully
     */
    bool readStreamFromFile(std::ifstream &file);

    /**
     * Compare data to the streams in top 10, and update the top lists if needed
     * @param data
     */
    void updateTop(const StreamData &data);
public:
    explicit Archive(const std::string &filename = "archive.txt");
    ~Archive();

    /**
     * Store a stream
     * @param data
     */
    void archiveStream(const StreamData &data);

    /**
     * Get number of streams stored
     * @return stream count
     */
    unsigned int getStreamCount() const;

    /**
     * Show the information of every stream stored
     */
    void show() const;

    /**
     * Show the top 10 streams by number of views and number of likes
     */
    void showTop() const;

    /**
     * Show a specific stream
     * @param id - id of the stream
     */
    void showStream(unsigned int id) const;

    /**
     * Return a vector of pointers to all streams specified in ids
     * @param history - streamHistory from a User
     * @param filter - char that will be matched with feedback from each stream ('L': like, 'D': dislike, '-': None)
     * @return std::vector<const StreamData *> with pointers to all streams
     */
    std::vector<const StreamData *> getStreamsById(const std::vector<std::pair<unsigned int, char>> &history, char filter = 0) const;

    /**
     * Enable test mode in which file read/write operations are disabled, and all current information cleared     *
     */
    void testMode();
};


#endif //STREAMZ_ARCHIVE_H
