// Review.cpp
#include "Review.h"

Review::Review(int score, std::string comments) : score(score), comment(comments) {
    // Initialize other Review attributes or perform necessary setup
}
Review::Review() : score(0), comment("") {
    // Initialize other Review attributes or perform necessary setup
}

int Review::getScore() const {
    return score;
}

std::string Review::getComment() const {
    return comment;
}

void Review::setScore(int score) {
    this->score = score;
}

void Review::setComment(std::string comment) {
    this->comment = comment;
}

// You can add more methods or functionality to the Review class as needed.
