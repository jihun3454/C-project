#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
private:
    int value;       // 카드의 값
    bool isMatched;  // 카드가 매칭되었는지 여부
    bool isFlipped;  // 카드가 현재 뒤집혀 있는지 여부

public:
    Card(int val);
    int getValue() const;
    bool getIsMatched() const;
    bool getIsFlipped() const;
    void flip();
    void setMatched();
};

#endif
