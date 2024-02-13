#include <boost/utility/base_from_member.hpp>

#include "FdStreambuf.h"

#include <cstdio>
#include <iomanip>
#include <ostream>

class fdostream : boost::base_from_member<FdStreambuf>, public std::ostream
{
public:
    explicit fdostream(int fd) :
        base_from_member(fd),
        std::ostream(&member)
    {
    }
};

int main()
{
    fdostream stdOut(1);

    stdOut << "This is going to standard out, file descriptor 1\n";

    return 0;
}
