#include <sstream>
#include <iostream>
#include <iomanip>

int main()
{
	std::stringstream ss;
	ss << "Hello there";
	std::cout << ss.str() << std::endl;

	std::cout << std::ends;
	std::cout << "Hello " << std::endl;
	std::cout << std::setbase(16);
	std::cout << 13 << std::endl;
	std::cout << std::boolalpha;
	std::cout << std::uppercase << true;
	ss << std::boolalpha;
	ss << true;
	std::cout << std::uppercase <<  ss.str() << std::endl;

	return 0;
}

