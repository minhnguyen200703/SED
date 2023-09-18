// Review.cpp
#include "Review.h"

Review::Review(int score, std::string comments) : score(score), comments(comments) {
    // Initialize other Review attributes or perform necessary setup
}

int Review::getScore() const {
    return score;
}

std::string Review::getComments() const {
    return comments;
}

// You can add more methods or functionality to the Review class as needed.
