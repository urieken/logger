#ifndef __WINDOWS_CONSOLE_WRITER_H__
#define __WINDOWS_CONSOLE_WRITER_H__

#include "writer.h"

class WindowsConsoleWriter : public Writer {
public:
	inline WindowsConsoleWriter() : Writer{} {}
	inline virtual ~WindowsConsoleWriter(){}

	virtual void Write(const std::string& _content, int color);
};

#endif // __WINDOWS_CONSOLE_WRITER_H__