#include <boost/call_traits.hpp>

#include <iostream>
#include <type_traits>

struct Person
{
    int         age;
    std::string name;
};

std::ostream &operator<<(std::ostream &str, const Person &val)
{
    return str << "Person{ " << val.age << ", " << val.name << " }";
}

template <typename T>
void print(std::ostream &str, typename boost::call_traits<T>::param_type arg)
{
    str << arg << '\n';
}

template <typename T>
using Parameter = typename boost::call_traits<T>::param_type;

static_assert(std::is_same<const int, Parameter<int>>::value);
static_assert(std::is_same<int *const, Parameter<int *>>::value);
static_assert(std::is_same<const Person &, Parameter<Person>>::value);

int main()
{
    print<int>(std::cout, 5);
    Person p{42, "Slartibartfast"};
    print<Person>(std::cout, p);

    return 0;
}
