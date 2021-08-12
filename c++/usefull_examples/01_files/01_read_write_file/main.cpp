#include <fstream>
#include <iostream>

int main() {
    std::ifstream in_file;
    in_file.open("input_file.txt");

    std::ofstream out_file;
    out_file.open("output_file.txt");

    while (in_file) {
        std::string line_buf;
        std::getline(in_file, line_buf);
        if (!line_buf.empty()) {
            line_buf.append("\n");
            out_file.write(line_buf.c_str(), line_buf.size());
        }
    }
}
