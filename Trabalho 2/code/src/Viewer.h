#ifndef STREAMZ_VIEWER_H
#define STREAMZ_VIEWER_H
#include "User.h"
#include "Stream.h"
#include <memory>
#include <vector>

class Order;

class Viewer : public User {
    /**
     * Add current stream to history if needed and link current_stream_feedback to correct char in history
     */
    void syncHistory();
    /**
     * Pointer to feedback char of current stream
     * If it's not nullptr, then it will point to a char (pair.second) of a entry in streams history
     */
    char *current_stream_feedback = nullptr;

    std::vector<Order> pending_orders;
    std::vector<Order> completed_orders;
public:
    /**
     * Class constructor
     * @param nickname Nickname of the user
     * @param name Name of the user
     * @param birth_date Birth date of the user
     * @param platform Reference to associated platform
     * @throws InvalidAge
     */
    Viewer(const std::string &nickname, const std::string &name, const Date &birth_date, Platform &platform);

    /**
     * Class constructor
     * @param nickname Nickname of the user
     * @param name Name of the user
     * @param birth_date Birth date of the user
     * @param history Watched streams history
     * @param platform Reference to associated platform
     * @param history Viewer's stream history
     * @throws InvalidAge
     */
    Viewer(const std::string &nickname, const std::string &name, const Date &birth_date, Platform &platform, const std::vector<std::pair<unsigned int, char>> &history);
    /**
     * Gets the weak pointer to the stream the viewer is currently watching
     * @return Weak pointer to the stream the viewer is currently watching
     */
    std::weak_ptr<Stream> getCurrentStream() const;
    /**
     * Joins the stream given as an argument
     * @param id - id of stream
     */
    void joinStream(unsigned int id);
    /**
     * Join stream hosted by specified streamer
     * @param streamer - nickname of the streamer
     */
     void joinStream(const std::string &streamer);
    /**
     * Leaves the stream that is currently being watched
     */
    void leaveStream();
    /**
     * Like the stream (if already liked, then the previous like is removed)
     */
    void like();
    /**
     * Dislike the stream (if already disliked, then the previous dislike is removed)
     */
    void dislike();
    /**
     * Return char that represents current feedback ('L' like, 'D' dislike, '-' None)
     * @return char
     */
    char getCurrentFeedback() const;
    /**
     * Leave a comment in the current stream (if viewer is not in private stream nothing will happen)
     * @param str - Comment content
     */
    void comment(const std::string &str);
    /**
     * Displays on the screen the info about the user
     */
    void show() const;
    /**
     * Writes in the indicated ostream the information about the user
     * @param os Stream where the information will be writen
     * @return Stream where the information will be writen
     */
    std::ostream& print(std::ostream & os) const;

    /**
     * Checks if the users have the same nickname
     * @param other Viewer to be compared with
     * @return Boolean indicating if the viewers are the same
     */
    bool operator==(const Viewer &other) const;

    /*
     * Move Order 'o' from pending_orders to complete_orders
     * @param o Order to be moved
     */
    void completeOrder(const Order &o);

    /*
     * Add order to pending_orders
     * @param o Order to be added
     */
    void addPendingOrder(const Order &o);

    /*
     * Add order straight to completed_orders
     * @param o Order to be added
     */
    void addCompletedOrder(const Order &o);

    /*
     * Remove pending order at position 'pos' of the vector
     * @param pos Index of orders
     */
    void removeOrderAtPos(int pos);

    /*
     * Show all viewer's orders
     */
    void showOrders();

    /*
     * Get pending_orders vector
     * @return vector with orders
     */
    std::vector<Order> & getPendingOrders();

    /*
     * Get complete_orders vector
     * @return vector with orders
     */
    std::vector<Order> & getCompletedOrders();
};

#endif //STREAMZ_VIEWER_H
