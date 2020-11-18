#ifndef STREAMZ_STREAMDATA_H
#define STREAMZ_STREAMDATA_H
#include <iostream>
#include "Date.h"
#include <string>

void showStreamsHeader();

class StreamData {
protected:
    unsigned id; /**> Id of the stream*/
    string title; /**> Title of the stream*/
    string streamer; /**> Streamer nickname*/
    Date start_date; /**> Start date of the stream*/
    Date end_date; /**> End date of the stream*/
    string language; /**> Language of the stream*/
    unsigned min_age; /**>Minimum viewer age*/
    unsigned viewers = 0; /**>Number of viewers*/
    bool isPublic = true; /**>Accessibility of the stream*/
    unsigned likes = 0; /**> Number of likes*/
    unsigned dislikes = 0; /**> Number of dislikes*/
    bool over = false; /**>Keep track if stream is over or not*/
public:
    /**
     * Class constructor
     */
    StreamData(unsigned id, const string &title, const string &streamer,const Date &start_date, const Date &end_date,  const string &language,
               unsigned viewers, bool isPublic, unsigned min_age, unsigned likes=0, unsigned dislikes=0);
    /**
     * Gets the id of the stream
     * @return id of the stream
     */
    unsigned getId() const;
    /**
     * Gets the title of the stream
     * @return title of the stream
     */
    string getTitle() const;
    /**
     * Gets the streamer
     * @return streamer
     */
    string getStreamer() const;
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
    string getLanguage() const;
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
     * Return true if stream has already ended
     * @return
     */
    bool isOver() const;
    /**
     * Prints data about the stream
     * @param os Output stream where the information will be writen
     * @param d StreamData
     * @return Stream where the information will be writen
     */
    friend ostream& operator<<(ostream& os, const StreamData &d);
    /**
     * Print data about stream into ostream
     * @param os
     * @return
     */
    virtual std::ostream& print(std::ostream & os) const;
    /**
     * Displays on the screen info about the stream
     */
    void show() const;
};


#endif //STREAMZ_STREAMDATA_H
