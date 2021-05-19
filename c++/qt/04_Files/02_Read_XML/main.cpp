#include <iostream>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <sstream>

int main(int argc, char *argv[])
{
    QFile input_file("example.xml");

    if (!input_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cerr << "Error opening file for reading!" << std::endl;
        exit(EXIT_FAILURE);
    }

    QXmlStreamReader xml(&input_file);

    using tok_type = QXmlStreamReader::TokenType;
    QString str;

    while (!xml.atEnd()) {
        auto token = xml.readNext();
        switch (token) {
            case tok_type::StartDocument : str += "BEGIN\n"; break;
            case tok_type::StartElement : str += xml.name() + " {"; break;
            case tok_type::EndElement : str += "}"; break;
            case tok_type::EndDocument : str += "\nEND"; break;
            case tok_type::Characters : str += xml.text(); break;
            case tok_type::Comment : str += "/* " + xml.text() + "*/\n"; break;
        }
    }

    std::cout << str.toStdString() << '\n';
}
