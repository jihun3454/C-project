#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Card.h"
#include <thread> // sleep_for 사용을 위한 헤더
#include <chrono> // 시간 관련 헤더
#include <cstdlib> // system() 함수 사용을 위한 헤더

class Game {
private:
    std::vector<Card> deck;
    int score;
    int rows, cols;
    int player1Score, player2Score;  // 플레이어 점수
    int currentPlayer; // 현재 플레이어 (1 또는 2)

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
