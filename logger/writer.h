#ifndef __WRITER_H__
#define __WRITER_H__

#include <string>

class Writer {
public:
	inline Writer() {}
	inline virtual ~Writer() {}

	virtual void Write(const std::string& _content, int color) = 0;
};

#endif // __WRITER_H__