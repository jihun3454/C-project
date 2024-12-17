#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
private:
    int value;       // ī���� ��
    bool isMatched;  // ī�尡 ��Ī�Ǿ����� ����
    bool isFlipped;  // ī�尡 ���� ������ �ִ��� ����

public:
    Card(int val);
    int getValue() const;
    bool getIsMatched() const;
    bool getIsFlipped() const;
    void flip();
    void setMatched();
};

#endif
