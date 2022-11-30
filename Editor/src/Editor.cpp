#include "Editor.hpp"
#include <Junia.hpp>

#include <iostream>

int main(int argc, char** argv)
{
	std::cout << "Hello World!" << std::endl;
	std::cout << "1 + 2 = " << add(1, 2) << std::endl;
	std::cout << "3 - 2 = " << subtract(3, 2) << std::endl;
	MakeWindow();
	std::cout << "Ok..." << std::endl;
	return 0;
}
