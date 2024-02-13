// Source: https://gist.github.com/amezin/c4bfc0dd11dd200c13b3

#include "FdStreambuf.h"

#include <cassert>
#include <streambuf>
#include <new>

#include <io.h>

const size_t FdStreambuf::bufferSize = 4096;

FdStreambuf::FdStreambuf(int d) : fd_(d), readBuf(0), writeBuf(0)
{
}

FdStreambuf::~FdStreambuf()
{
	close();
}

void FdStreambuf::fd(int v)
{
	if (fd_ == v) {
		return;
	}

	if (fd_ >= 0) {
		sync();
		::close(fd_);
	}

	setg(0, 0, 0);
	setp(0, 0);
	
	delete [] readBuf;
	readBuf = 0;

	delete [] writeBuf;
	writeBuf = 0;

	fd_ = v;
}

FdStreambuf::int_type FdStreambuf::underflow()
{
	assert(gptr() == egptr());

	if (fd_ < 0) {
		return traits_type::eof();
	}

	if (readBuf) {
		*readBuf = *(gptr() - 1);
	} else {
		readBuf = new (std::nothrow) char[bufferSize];
		if (!readBuf) {
			return traits_type::eof();
		}
	}

	int nRead = read(fd_, readBuf + 1, bufferSize - 1);
	if (nRead <= 0) {
		return traits_type::eof();
	}
	setg(readBuf, readBuf + 1, readBuf + 1 + nRead);
	return traits_type::to_int_type(*gptr());
}

FdStreambuf::int_type FdStreambuf::overflow(int_type c)
{
	assert(pptr() == epptr());

	if (fd_ < 0) {
		return traits_type::eof();
	}

	if (!writeBuf) {
		writeBuf = new (std::nothrow) char[bufferSize];
		if (!writeBuf) {
			return traits_type::eof();
		}
	}

	if (c == traits_type::eof() || sync() == -1) {
		return traits_type::eof();
	}

	*pptr() = traits_type::to_char_type(c);
	pbump(1);
	return c;
}

int FdStreambuf::sync()
{
	if (fd_ < 0 || !writeBuf) {
		return 0;
	}

	char *p = pbase();
	while (p < pptr()) {
		int nWritten = write(fd_, p, pptr() - p);
		if (nWritten <= 0) {
			return -1;
		}
		p += nWritten;
	}

	setp(writeBuf, writeBuf + bufferSize);
	return 0;
}
