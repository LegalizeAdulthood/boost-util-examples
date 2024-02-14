#include <boost/compressed_pair.hpp>

#include <iostream>
#include <utility>

struct Empty
{
};

struct Derived : Empty
{
    explicit Derived(int i) :
        i(i)
    {
    }
    int i;
};

// std::pair
static_assert(sizeof(std::pair<int, int>) == sizeof(int) * 2, "Pair is as big as the two things inside it.");
static_assert(sizeof(Empty) > 0, "Empty struct has some storage");
static_assert(sizeof(Derived) == sizeof(int), "Empty base class optimization");
static_assert(sizeof(std::pair<Empty, Empty>) == 2 * sizeof(Empty), "Holds two Empty structs");
static_assert(sizeof(std::pair<Derived, Derived>) == 2 * sizeof(int), "Empty base class optimization");

// boost::compressed_pair
template <typename T, typename U>
using cpair = boost::compressed_pair<T, U>;

static_assert(sizeof(cpair<int, int>) == 2 * sizeof(int), "Compressed pair holds two things");
static_assert(sizeof(cpair<int, Empty>) == sizeof(int), "Empty classes don't impose additional storage");
static_assert(sizeof(cpair<Empty, int>) == sizeof(int), "Empty classes don't impose additional storage");
static_assert(sizeof(cpair<Empty, Empty>) == sizeof(Empty), "Both empty still holds one Empty amount of storage");

// See also: https://github.com/Morwenn/tight_pair and other compressed pair implementations

std::ostream &operator<<(std::ostream &str, const Empty &)
{
    return str << "Empty{}";
}

std::ostream &operator<<(std::ostream &str, const Derived &val)
{
    return str << "Derived{ " << val.i << " }";
}

int main()
{
    cpair<Derived, Empty> p{Derived{42}, Empty{}};
    std::cout << "first() == " << p.first() << ", second() == " << p.second() << '\n';
    return 0;
}
