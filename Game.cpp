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
    deck.clear(); // �� �ʱ�ȭ
    int numPairs = (rows * cols) / 2;  // ī�� �� ���� ����

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
        std::cout << "���� ���̵��� �����ϼ���:\n";
        std::cout << "1. ���� (4x4)\n";
        std::cout << "2. ���� (6x6)\n";
        std::cout << "3. ����� (10x10)\n";
        std::cout << "����: ";

        if (!(std::cin >> difficulty)) {
            // �Է��� ���ڰ� �ƴ� ��� ó��
            std::cin.clear();              // �Է� ���� �ʱ�ȭ
            std::cin.ignore(1000, '\n');   // ���ۿ��� ���� �Է°� ����
            std::cout << "�߸��� �Է��Դϴ�. 1, 2, 3 �߿� �������ּ���.\n";
            system("cls");
        }
        else if (difficulty < 1 || difficulty > 3) {
            // ��ȿ�� ������ �ƴ� ���
            std::cout << "�߸��� �Է��Դϴ�. 1, 2, 3 �߿� �������ּ���.\n";
        }
        else {
            // ��ȿ�� �Է��� ���
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
        std::cout << "  ī�� ��Ī ���ӿ� ���� ���� ȯ���մϴ�!\n";
        std::cout << "----------------------------\n";
        std::cout << "1. ���� ����\n";
        std::cout << "2. ���� ����\n";
        std::cout << "----------------------------\n";
        std::cout << "����: ";

        if (!(std::cin >> menuOption)) {
            std::cin.clear();              // �Է� ���� �ʱ�ȭ
            std::cin.ignore(1000, '\n');   // ���ۿ��� ���� �Է°� ����
            std::cout << "�߸��� �Է��Դϴ�. 1 �Ǵ� 2�� �Է����ּ���.\n";
            system("cls");
        }
        else if (menuOption == 1 || menuOption == 2) {
            break;
        }
        else {
            std::cout << "�߸��� �Է��Դϴ�. 1 �Ǵ� 2�� �Է����ּ���.\n";
        }
    }

    if (menuOption == 2) {
        std::cout << "������ �����մϴ�.\n";
        exit(0);  // ���� ����
    }
}

void Game::start() {
    // ���� ���� ���� �޴� ǥ�� �� ���̵� ����
    displayMenu();
    system("cls");
    setDifficulty();  // ���̵� ����

    // �� �ʱ�ȭ �� ����
    initializeDeck();
    shuffleDeck();

    int index1, index2;

    // ��ü ī�� 3�� ���� �����ֱ�
    std::cout << "��ü ī�尡 ��� �����˴ϴ�!\n";
    showDeck(true); // ��� ī�� ����
    std::this_thread::sleep_for(std::chrono::seconds(3));  // 3�� ���
    system("cls"); // ȭ���� �ʱ�ȭ�� �α� ����

    while (true) {
        showDeck(false); // ���� ���¸� ������

        // �÷��̾� ���� ǥ��
        std::cout << "\n�÷��̾� 1 ����: " << player1Score
            << " | �÷��̾� 2 ����: " << player2Score << "\n";

        std::cout << "�÷��̾� " << currentPlayer << " �����Դϴ�!\n";
        std::cout << "ī�带 �����ϼ��� (��: 1 2): ";

        // �Է¹ޱ�
        if (!(std::cin >> index1 >> index2)) {
            // �Է°��� ���ڰ� �ƴ� ���
            std::cin.clear();              // �Է� ���� �ʱ�ȭ
            std::cin.ignore(1000, '\n');   // ���ۿ��� ���� �Է°� ����
            std::cout << "��ȿ���� ���� �Է��Դϴ�. ���ڸ� �Է����ּ���.\n";
            system("cls");
            continue;
        }

        // ����� �Է°��� 0���� �����ϴ� �ε����� ��ȯ
        index1 -= 1;
        index2 -= 1;

        // ��ȿ�� �˻�
        if (index1 < 0 || index2 < 0 || index1 >= deck.size() || index2 >= deck.size() || index1 == index2) {
            std::cout << "��ȿ���� ���� �����Դϴ�. �ٽ� �õ��ϼ���.\n";
            system("cls");
            continue;
        }

        deck[index1].flip();
        deck[index2].flip();
        showDeck(false);

        // ��� �����ֱ�
        std::this_thread::sleep_for(std::chrono::seconds(2));

        if (checkMatch(index1, index2)) {
            std::cout << "��Ī ����!\n";
        }
        else {
            std::cout << "��Ī ����.\n";
            deck[index1].flip();
            deck[index2].flip();
        }

        // ���� �Ϸ� ���� Ȯ��
        if (std::all_of(deck.begin(), deck.end(), [](Card& card) { return card.getIsMatched(); })) {
            std::cout << "���� �Ϸ�!\n";
            std::cout << "�÷��̾� 1 ����: " << player1Score << "\n";
            std::cout << "�÷��̾� 2 ����: " << player2Score << "\n";
            std::cout << "����: " << (player1Score > player2Score ? "�÷��̾� 1" : "�÷��̾� 2") << "\n";
            break;
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1; // �� ����
        system("cls"); // �α� ����
    }
}
