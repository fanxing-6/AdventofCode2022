#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ranges>
#include <numeric>
#include <algorithm>
#include <array>

using uint = uint64_t;

class Interval {
public:
    uint min;
    uint max;

    //A是B的子集，返回true
    bool IsSubsetOf(const Interval &interval) const {
        return min >= interval.min && max <= interval.max;
    }

    bool IsOverlapWith(const Interval &interval) const {
        return (min >= interval.min && min <= interval.max) ||
               (max >= interval.min && max <= interval.max) ||
               IsSubsetOf(interval);
    }

    friend std::istream &operator>>(std::istream &is, Interval &interval) {
        is >> interval.min;
        is.ignore(1);
        is >> interval.max;
        return is;
    }

};

uint Overlap(const std::vector<std::pair<Interval, Interval>> &data) {
    return std::ranges::count_if(data, [](auto &pair) -> uint {
        return pair.first.IsOverlapWith(pair.second)
               || pair.second.IsOverlapWith(pair.first);
    });
}

uint Contain(const std::vector<std::pair<Interval, Interval>> &data) {
    return std::ranges::count_if(data, [](auto &pair) -> uint {
        return pair.first.IsSubsetOf(pair.second)
               || pair.second.IsSubsetOf(pair.first);
    });
}


int Parse(std::string_view filePath) {

    std::vector<std::pair<Interval, Interval>> data;
    std::ifstream file(filePath.data());
    if (!file.is_open()) {
        std::cout << "open file failed" << std::endl;
        return -1;
    }
    Interval left{}, right{};
    char temp;
    while (file >> left >> temp >> right) {
        data.emplace_back(left, right);
    }
    std::cout << "Contain: " << Contain(data) << std::endl;
    std::cout << "Overlap: " << Overlap(data) << std::endl;
    return 0;
}


int main() {
    Parse(R"(D:\AllCodeProjects\CLionProject\AdventofCode2022\code\04.txt)");
    return 0;
}