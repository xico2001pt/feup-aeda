#ifndef STREAMZ_STREAMDATA_H
#define STREAMZ_STREAMDATA_H
#include <iostream>
#include "Date.h"
#include <string>

void showStreamsHeader();

class StreamData {
protected:
    unsigned id; /**< Id of the stream*/
    std::string title; /**< Title of the stream*/
    std::string streamer; /**< Streamer nickname*/
    Date start_date; /**< Start date of the stream*/
    Date end_date; /**< End date of the stream*/
    std::string language; /**< Language of the stream*/
    unsigned min_age; /**< Minimum viewer age*/
    unsigned viewers = 0; /**< Number of viewers*/
    bool isPublic = true; /**< Accessibility of the stream*/
    unsigned likes = 0; /**< Number of likes*/
    unsigned dislikes = 0; /**< Number of dislikes*/
    bool over = false; /**< Keep track if stream is over or not*/
public:
    /**
     * Class constructor
     * @param id Id of the stream
     * @param title Title of the stream
     * @param streamer Nickname of the streamer hosting the stream
     * @param start_date Start date of the stream
     * @param end_date End date of the stream
     * @param viewers Number of viewers
     * @param isPublic True if public, false if private
     * @param language Language of the stream
     * @param min_age Minimum age to watch the stream
     * @param likes Number of likes
     * @param dislikes Number of dislikes
     * @param over True if stream is already over
     */
    StreamData(unsigned id, const std::string &title, const std::string &streamer,const Date &start_date, const Date &end_date,  const std::string &language,
               unsigned viewers, bool isPublic, unsigned min_age, unsigned likes=0, unsigned dislikes=0, bool over=false);
    /**
     * Gets the id of the stream
     * @return id of the stream
     */
    unsigned getId() const;
    /**
     * Gets the title of the stream
     * @return title of the stream
     */
    std::string getTitle() const;
    /**
     * Gets the streamer
     * @return streamer
     */
    std::string getStreamer() const;
    /**
     * Gets the start date of the stream
     * @return start date of the stream
     */
    Date getStartDate() const;
    /**
     * Gets the end date of the stream
     * @return end date of the stream
     */
    Date getEndDate() const;
    /**
     * Gets the language of the stream
     * @return language of the stream
     */
    std::string getLanguage() const;
    /**
     * Gets the number of viewers at the stream
     * @return number of viewers at the stream
     */
    unsigned getViewers() const;
    /**
     * Checks if stream is public or private
     * @return boolean indicating if the stream is public
     */
    bool getIsPublic() const;
    /**
     * Gets number of likes of the stream
     * @return Number of likes of the stream
     */
    unsigned getLikes() const;
    /**
     * Gets number of dislikes of the stream
     * @return Number of dislikes of the stream
     */
    unsigned getDislikes() const;
    /**
     * Gets minimum viewer age
     * @return age
     */
     unsigned getMinAge() const;
    /**
     * Checks if stream has already ended
     * @return true if stream has already ended
     */
    bool isOver() const;
    /**
     * Prints data about the stream
     * @param os Output stream where the information will be writen
     * @param d StreamData
     * @return Stream where the information will be writen
     */
    friend std::ostream& operator<<(std::ostream& os, const StreamData &d);
    /**
     * Print data about stream into ostream
     * @param os Stream where the information will be writen
     * @return Stream where the information will be writen
     */
    virtual std::ostream& print(std::ostream & os) const;
    /**
     * Displays on the screen info about the stream
     */
    void show() const;
};


#endif //STREAMZ_STREAMDATA_H
