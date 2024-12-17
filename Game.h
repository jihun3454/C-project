#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Card.h"
#include <thread> // sleep_for ����� ���� ���
#include <chrono> // �ð� ���� ���
#include <cstdlib> // system() �Լ� ����� ���� ���

class Game {
private:
    std::vector<Card> deck;
    int score;
    int rows, cols;
    int player1Score, player2Score;  // �÷��̾� ����
    int currentPlayer; // ���� �÷��̾� (1 �Ǵ� 2)

    void initializeDeck();
    void shuffleDeck();
    bool checkMatch(int index1, int index2);
    void displayMenu();
    void showDeck(bool showAll = false);
    void setDifficulty();

public:
    Game();
    void start();   
};

#endif
