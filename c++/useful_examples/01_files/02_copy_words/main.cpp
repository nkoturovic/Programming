#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <numeric>

int main() {
    std::ifstream in_file;
    in_file.open("input_file.txt");

    std::ofstream out_file;
    out_file.open("output_file.txt");

    std::vector<std::string> lines;

    std::copy(std::istream_iterator<std::string>(in_file), 
              std::istream_iterator<std::string>(),
              std::back_inserter(lines));

    std::transform(
            std::make_move_iterator(lines.begin()),
            std::make_move_iterator(lines.end()),
            std::ostream_iterator<std::string>(out_file, "\n"),
            [](std::string &&s) {
                return std::accumulate(
                       s.begin(),
                       s.end(), 
                       std::string{}, 
                       [](std::string s, char c) {
                           return s.append(1, std::toupper(c));
                       });
            });
}
