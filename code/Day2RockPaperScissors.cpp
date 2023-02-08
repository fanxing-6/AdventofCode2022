#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ranges>
#include <numeric>
#include <algorithm>
#include <array>


int TotalScore(const std::vector<std::pair<char, char>> &data) {
    // The first column is what your opponent is going to play: A for Rock, B for Paper, and C for Scissors.
    //1 for Rock, 2 for Paper, and 3 for Scissors
    //X for Rock, Y for Paper, and Z for Scissors
    //X == 1 Y == 2 Z == 3
    //0 if you lost, 3 if the round was a draw, and 6 if you won

    auto score = [](auto &pair) -> int {

        char opponent = pair.first;
        char you = pair.second;

        constexpr int scores[] = {1, 2, 3};
        int score = scores[you - 'X'];

        constexpr int opponentMatrix[3][3] = {
                {3, 6, 0},
                {0, 3, 6},
                {6, 0, 3},
        };

        score += opponentMatrix[opponent - 'A'][you - 'X'];
        return score;
    };

    auto view = data
                | std::views::transform(score)
                | std::views::common;

    return std::reduce(view.begin(), view.end());
}

int TotalScore2(const std::vector<std::pair<char, char>> &data) {
    auto score = [](auto &pair) -> int {

        char opponent = pair.first - 'A';
        char you = pair.second - 'X';

        int score = you * 3;
        if (you == 1) {
            return score + opponent + 1;
        } else if (you == 2) {
            return score + (opponent + 1) % 3 + 1;
        }
        return score + (opponent + 2) % 3 + 1;
    };
    auto view = data
                | std::views::transform(score)
                | std::views::common;

    return std::reduce(view.begin(), view.end());
}


int Parse(std::string_view filePath) {
    std::vector<std::pair<char, char>> data;
    std::ifstream file(filePath.data());
    if (!file.is_open()) {
        std::cout << "open file failed" << std::endl;
        return -1;
    }
    std::pair<char, char> line;
    while (file >> line.first >> line.second) {
        data.push_back(line);
    }
    std::cout << "TotalScore: " << TotalScore(data) << std::endl;
    std::cout << "TotalScore2: " << TotalScore2(data) << std::endl;
    return 0;
}


int main() {
    Parse(R"(D:\AllCodeProjects\CLionProject\AdventofCode2022\code\02.txt)");
}