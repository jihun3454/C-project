#include "Card.h"

Card::Card(int val) : value(val), isMatched(false), isFlipped(false) {}

int Card::getValue() const {
    return value;
}

bool Card::getIsMatched() const {
    return isMatched;
}

bool Card::getIsFlipped() const {
    return isFlipped;
}

void Card::flip() {
    isFlipped = !isFlipped;
}

void Card::setMatched() {
    isMatched = true;
}
