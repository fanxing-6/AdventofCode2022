#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ranges>
#include <numeric>
#include <algorithm>
#include <array>

int SumPriority(const std::vector<std::string> &data) {
    auto view = [](std::string str) -> int {

        auto iter = str.begin() + str.length() / 2;
        std::sort(str.begin(), iter);
        std::sort(iter, str.end());

        std::vector<char> result;
        std::set_intersection(str.begin(), iter, iter, str.end(), std::back_inserter(result));

        if (std::isupper(result[0])) {
            return 27 + result[0] - 'A';
        }

        return 1 + result[0] - 'a';
    };

    auto view2 = data
                 | std::views::transform(view)
                 | std::views::common;

    return std::reduce(view2.begin(), view2.end());
}

int Attachment(std::vector<std::string> data) {
    // pre-sort the input
    std::ranges::for_each(data, [](auto &str) {
        std::ranges::sort(str);
    });

    int result = 0;
    for (auto &&chunk: data | std::views::chunk(3)) {
        std::vector<char> tmp, out;
        std::ranges::set_intersection(chunk[0].begin(), chunk[0].end(),
                                      chunk[1].begin(), chunk[1].end(),
                                      std::back_inserter(tmp));
        std::ranges::set_intersection(tmp.begin(), tmp.end(),
                                      chunk[2].begin(), chunk[2].end(),
                                      std::back_inserter(out));

        if (std::isupper(out[0])) {
            result += 27 + out[0] - 'A';
        } else {
            result += 1 + out[0] - 'a';
        }
    }
    return result;
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
    std::cout << "SumPriority: " << SumPriority(data) << std::endl;
    std::cout << "Attachment: " << Attachment(data) << std::endl;
    return 0;
}

int main() {
    Parse(R"(D:\AllCodeProjects\CLionProject\AdventofCode2022\code\03.txt)");
}