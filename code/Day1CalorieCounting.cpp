#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ranges>
#include <numeric>
#include <algorithm>

int TopThreeAcc(const std::vector<std::string> &data) {
    auto view = data
                | std::views::lazy_split(std::string{})
                | std::views::transform([](const auto &elf) {
        auto toInt = [](const auto &str) { return std::stoi(str); };
        auto rng = elf
                   | std::views::transform(toInt)
                   | std::views::common;
        return std::reduce(rng.begin(), rng.end());
    });

    std::vector<int> topThree(3);

    std::ranges::partial_sort_copy(view, topThree, std::greater{});

    return std::reduce(topThree.begin(), topThree.end());

}


int MaxCalories(const std::vector<std::string> &data) {
    auto view = data
                | std::views::lazy_split(std::string{})
                | std::views::transform([](const auto &elf) {
        auto toInt = [](const auto &str) { return std::stoi(str); };
        auto rng = elf
                   | std::views::transform(toInt)
                   | std::views::common;
        return std::reduce(rng.begin(), rng.end());
    });
    return std::ranges::max(view);
}


int Parse(std::string_view filePath) {
    std::vector<std::string> data;
    std::ifstream file(filePath.data());
    if (!file.is_open()) {
        std::cout << "open file failed" << std::endl;
        return -1;
    }
    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);
    }

    std::cout << "MaxCalories: " << MaxCalories(data) << std::endl;
    std::cout << "TopThreeAcc: " << TopThreeAcc(data) << std::endl;
    return 0;
}

int main() {
    Parse("01.txt");
    return 0;
}
