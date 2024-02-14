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

static_assert(std::is_same<const int, Parameter<int>>::value, "Pass an int as const int");
static_assert(std::is_same<int *const, Parameter<int *>>::value, "Pass a pointer to int as int *const (constant pointer to int)");
static_assert(std::is_same<const Person &, Parameter<Person>>::value, "Pass a Person as const Person &");
static_assert(std::is_same<int &, Parameter<int &>>::value, "Pass a reference to an int as int &");

static_assert(std::is_same<int &, boost::call_traits<int &>::reference>::value, "Don't take a reference of a reference");
static_assert(std::is_same<int &, boost::call_traits<int>::reference>::value, "Take a reference on a simple type");
static_assert(std::is_same<const Person &, boost::call_traits<Person>::const_reference>::value, "Take a const reference on a struct");

int main()
{
    print<int>(std::cout, 5);
    Person p{42, "Slartibartfast"};
    print<Person>(std::cout, p);

    return 0;
}
