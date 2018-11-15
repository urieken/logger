#include "windows_console_writer.h"

#include <Windows.h>

#include <iostream>

void WindowsConsoleWriter::Write(const std::string& _content, int color) {
	HANDLE hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);

	::SetConsoleTextAttribute(hConsole, color);
	std::cout << _content << std::endl;
	::SetConsoleTextAttribute(hConsole, 7);
}