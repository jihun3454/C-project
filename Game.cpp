#include "Game.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

Game::Game() : score(0), rows(4), cols(4), player1Score(0), player2Score(0), currentPlayer(1) {
    initializeDeck();
    shuffleDeck();
}

void Game::initializeDeck() {
    deck.clear(); // 덱 초기화
    int numPairs = (rows * cols) / 2;  // 카드 한 쌍의 개수

    for (int i = 1; i <= numPairs; i++) {
        deck.push_back(Card(i));
        deck.push_back(Card(i));
    }
}

void Game::shuffleDeck() {
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(time(0)));
}

bool Game::checkMatch(int index1, int index2) {
    if (deck[index1].getValue() == deck[index2].getValue()) {
        deck[index1].setMatched();
        deck[index2].setMatched();
        if (currentPlayer == 1) {
            player1Score += 10;
        }
        else {
            player2Score += 10;
        }
        return true;
    }
    else {
        return false;
    }
}

void Game::showDeck(bool showAll) {
    for (size_t i = 0; i < deck.size(); ++i) {
        if (deck[i].getIsMatched()) {
            std::cout << "[*] ";
        }
        else if (deck[i].getIsFlipped() || showAll) {
            std::cout << "[" << deck[i].getValue() << "] ";
        }
        else {
            std::cout << "[?] ";
        }

        if ((i + 1) % cols == 0) std::cout << std::endl;
    }
}

void Game::setDifficulty() {
    int difficulty;
    while (true) {
        std::cout << "게임 난이도를 선택하세요:\n";
        std::cout << "1. 쉬움 (4x4)\n";
        std::cout << "2. 보통 (6x6)\n";
        std::cout << "3. 어려움 (10x10)\n";
        std::cout << "선택: ";

        if (!(std::cin >> difficulty)) {
            // 입력이 숫자가 아닐 경우 처리
            std::cin.clear();              // 입력 상태 초기화
            std::cin.ignore(1000, '\n');   // 버퍼에서 남은 입력값 제거
            std::cout << "잘못된 입력입니다. 1, 2, 3 중에 선택해주세요.\n";
            system("cls");
        }
        else if (difficulty < 1 || difficulty > 3) {
            // 유효한 선택이 아닌 경우
            std::cout << "잘못된 입력입니다. 1, 2, 3 중에 선택해주세요.\n";
        }
        else {
            // 유효한 입력인 경우
            if (difficulty == 1) {
                rows = 4;
                cols = 4;
            }
            else if (difficulty == 2) {
                rows = 6;
                cols = 6;
            }
            else if (difficulty == 3) {
                rows = 10;
                cols = 10;
            }
            break;
        }
    }
}


void Game::displayMenu() {
    int menuOption;
    while (true) {
        std::cout << "----------------------------\n";
        std::cout << "  카드 매칭 게임에 오신 것을 환영합니다!\n";
        std::cout << "----------------------------\n";
        std::cout << "1. 게임 시작\n";
        std::cout << "2. 게임 종료\n";
        std::cout << "----------------------------\n";
        std::cout << "선택: ";

        if (!(std::cin >> menuOption)) {
            std::cin.clear();              // 입력 상태 초기화
            std::cin.ignore(1000, '\n');   // 버퍼에서 남은 입력값 제거
            std::cout << "잘못된 입력입니다. 1 또는 2를 입력해주세요.\n";
            system("cls");
        }
        else if (menuOption == 1 || menuOption == 2) {
            break;
        }
        else {
            std::cout << "잘못된 입력입니다. 1 또는 2를 입력해주세요.\n";
        }
    }

    if (menuOption == 2) {
        std::cout << "게임을 종료합니다.\n";
        exit(0);  // 게임 종료
    }
}

void Game::start() {
    // 게임 시작 전에 메뉴 표시 및 난이도 설정
    displayMenu();
    system("cls");
    setDifficulty();  // 난이도 설정

    // 덱 초기화 및 셔플
    initializeDeck();
    shuffleDeck();

    int index1, index2;

    // 전체 카드 3초 동안 보여주기
    std::cout << "전체 카드가 잠깐 공개됩니다!\n";
    showDeck(true); // 모든 카드 공개
    std::this_thread::sleep_for(std::chrono::seconds(3));  // 3초 대기
    system("cls"); // 화면을 초기화해 로그 제거

    while (true) {
        showDeck(false); // 현재 상태를 보여줌

        // 플레이어 점수 표시
        std::cout << "\n플레이어 1 점수: " << player1Score
            << " | 플레이어 2 점수: " << player2Score << "\n";

        std::cout << "플레이어 " << currentPlayer << " 차례입니다!\n";
        std::cout << "카드를 선택하세요 (예: 1 2): ";

        // 입력받기
        if (!(std::cin >> index1 >> index2)) {
            // 입력값이 숫자가 아닌 경우
            std::cin.clear();              // 입력 상태 초기화
            std::cin.ignore(1000, '\n');   // 버퍼에서 남은 입력값 제거
            std::cout << "유효하지 않은 입력입니다. 숫자를 입력해주세요.\n";
            system("cls");
            continue;
        }

        // 사용자 입력값을 0부터 시작하는 인덱스로 변환
        index1 -= 1;
        index2 -= 1;

        // 유효성 검사
        if (index1 < 0 || index2 < 0 || index1 >= deck.size() || index2 >= deck.size() || index1 == index2) {
            std::cout << "유효하지 않은 선택입니다. 다시 시도하세요.\n";
            system("cls");
            continue;
        }

        deck[index1].flip();
        deck[index2].flip();
        showDeck(false);

        // 잠깐 보여주기
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (checkMatch(index1, index2)) {
            std::cout << "매칭 성공!\n";
        }
        else {
            std::cout << "매칭 실패.\n";
            deck[index1].flip();
            deck[index2].flip();
        }

        // 게임 완료 조건 확인
        if (std::all_of(deck.begin(), deck.end(), [](Card& card) { return card.getIsMatched(); })) {
            std::cout << "게임 완료!\n";
            std::cout << "플레이어 1 점수: " << player1Score << "\n";
            std::cout << "플레이어 2 점수: " << player2Score << "\n";
            std::cout << "승자: " << (player1Score > player2Score ? "플레이어 1" : "플레이어 2") << "\n";
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1; // 턴 변경
        system("cls"); // 로그 제거
    }
}
