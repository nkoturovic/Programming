#include <iostream>
#include <QTime>

int main()
{
    qsrand(static_cast<unsigned>(QTime(0,0).secsTo(QTime::currentTime())));

    for (auto i=0u; i < 10u; i++)
        std::cout << i+1 << ": " << qrand() << '\n';

    return 0;
}
