#ifndef REVIEW_H
#define REVIEW_H

#include <string>

class Review {
private:
    int score; // Rating score (1 to 10)
    std::string comments; // Review comments

public:
    Review(int score, std::string comments);

    int getScore() const;
    std::string getComments() const;
};

#endif
