#include <iostream>

int main(int argc, char** argv) {
	int nReturn{ 0 };

	std::cout << "ARGUMENT COUNT : " << argc << std::endl;
	std::cout << "PROGRAM        : " << argv[0] << std::endl;

	std::cin.get();

	return nReturn;
}
