#ifndef STREAMZ_DONATION_H
#define STREAMZ_DONATION_H

#include <string>
#include <iostream>

using namespace std;

class Donation {
    string streamer; /**< Streamer receiving the donation */
    unsigned value; /**< Value of the donation */
    unsigned evaluation; /**< Evaluation of the streamer */
    unsigned counter; /**< Counter of same donations */
public:
    /**
     * Class constructor
     * @param s streamer
     * @param v value
     * @param e evaluation
     */
    Donation(string s, unsigned v, unsigned e);
    /**
     * Gets the nickname of the streamer who received the donation
     * @return Nickname of the streamer who received the donation
     */
    string getStreamer() const;
    /**
     * Gets the value of the donation
     * @return Value of the donation
     */
    unsigned getValue() const;
    /**
     * Gets the evaluation of the streamer
     * @return Evaluation of the streamer
     */
    unsigned getEvaluation() const;
    /**
     * Gets counter of same donations
     * @return Counter of same donations
     */
    unsigned getCounter() const;
    /**
     * Sets counter to specified value
     * @param c Value of counter
     */
    void setCounter(unsigned c);
    /**
     * Operator to order the BST
     * @param d Donation
     * @return boolean
     */
    bool operator<(const Donation &d) const;
    /**
     * Check if donations are equal
     * @param d Donation
     * @return boolean indicating if donations are equal
     */
    bool operator==(const Donation &d) const;
    friend std::ostream& operator <<(std::ostream& os, const Donation &d);
};

#endif //STREAMZ_DONATION_H
