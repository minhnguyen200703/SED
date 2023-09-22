#ifndef REVIEW_H
#define REVIEW_H

#include <string>

class Review {
private:
    int score; // Rating score (1 to 10)
    std::string comment; // Review comments

public:
    Review(int score, std::string comment);
    Review();

    int getScore() const;
    std::string getComment() const;
    void Review::setScore(int score);
    void Review::setComment(std::string comment);
};
 
#endif
