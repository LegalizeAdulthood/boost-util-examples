// Source: https://gist.github.com/amezin/c4bfc0dd11dd200c13b3

#pragma once

#include <streambuf>

class FdStreambuf : public std::streambuf
{
public:
	FdStreambuf(int d = -1);
	~FdStreambuf();

	int fd() const
	{
		return fd_;
	}

	void fd(int v);

	void close() { fd(-1); }

protected:
	int_type underflow();
	int_type overflow(int_type c);
	int sync();

private:
	int fd_;
	char *readBuf, *writeBuf;

	static const size_t bufferSize;
};
