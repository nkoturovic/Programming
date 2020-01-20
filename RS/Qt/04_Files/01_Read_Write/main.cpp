#include <iostream>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{

    QFile input_file("input_file.txt");

    if (!input_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Error opening file for reading!" << std::endl;
        exit(EXIT_FAILURE);
    }

    QTextStream input_text(&input_file);

    std::vector<QString> lines;
    /* Reading line by line */
    while (!input_text.atEnd()) {
       QString line = input_text.readLine();
       lines.emplace_back(std::move(line));
    }

    input_file.close();

    /* Let's make every second line all uppercase characters */
    for (auto it = lines.begin(); it != lines.end(); it++) {
        /* For every even line from 0 to lines.size() */
        if (std::distance(lines.begin(),it) % 2 == 0) {
            auto &line = *it;

            for (auto &c : line)
              c = c.toUpper();
        }
    }

    /* We could of read whole file at one
     * instead: input_text.readAll(); */

    QFile output_file("output_file.txt");
    QTextStream output_text(&output_file);

    if (!output_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        std::cerr << "Error opening file for writing!" << std::endl;
        exit(EXIT_FAILURE);
    }

    for (auto && line : lines) {
        output_text << line << '\n';
    }

    output_file.close();

    return 0;
}
