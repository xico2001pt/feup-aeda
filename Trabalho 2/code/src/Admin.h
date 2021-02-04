#ifndef STREAMZ_ADMIN_H
#define STREAMZ_ADMIN_H
#include "Platform.h"
#include "Date.h"
#include <string>

class Platform;

class Admin {
    const Platform & platform; /**< Reference to the associated platform */
public:
    /**
     * Class constructor
     * @param platform Pointer to the platform that will be monitored
     */
    Admin(const Platform & platform);
    /**
     * Calculates the average views per stream
     * @return average views per stream
     */
    float averageViews() const;
    /**
     * Counts the number of streams (active + archived) that meet the requirements given as parameters
     * @param isPublic boolean indicating if the function is searching for public streams
     * @param lower lower time interval limit
     * @param upper upper time interval limit
     * @return number of streams that meet the requirements given as parameters
     */
    unsigned int streamsCounter(const bool isPublic, const Date &lower, const Date &upper) const;
    /**
     * Searches the most created language
     * @return string indicating the most created language
     */
    std::string topLanguage() const;
    /**
     * Searches the most created type of stream (public or private)
     * @return string indicating the most created type of stream ("public", "private" or "draw")
     */
    std::string topTypeStream() const;
    /**
     * Searches the streamer with the most total views
     * @return nickname of the streamer with the most total views
     */
    std::string topStreamer() const;
    /**
     * Gets donations whose evaluation is in the interval [a1, a2] greater than a minimum value
     * @param a1 Lower limit of the interval
     * @param a2 Upper limit of the interval
     * @param min_value Minimum value of the donation
     * @return Vector with donations that match the criteria
     */
    vector<Donation> getDonationsEval(unsigned a1, unsigned a2, unsigned min_value = 0);
    /**
     * Gets donations from a streamer
     * @param st Streamer
     * @return Vector with donations that match the criteria
     */
    vector<Donation> getDonationsStreamer(string st);
    /**
     * Gets donations higher than a value
     * @param v Value
     * @return Vector with donations that match the criteria
     */
    vector<Donation> getDonationsValue(unsigned v);
};


#endif //STREAMZ_ADMIN_H
