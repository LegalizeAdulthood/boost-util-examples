#include <boost/utility/in_place_factory.hpp>
#include <boost/utility/typed_in_place_factory.hpp>

#include <iostream>

struct Point
{
    Point(int x, int y) :
        x(x),
        y(y)
    {
    }
    int x;
    int y;
};

struct Container
{
    Container() = default;
    ~Container()
    {
        delete[] static_cast<char *>(static_cast<void *>(m_storage));
    }

    template <typename Expr>
    Container(const Expr &expr)
    {
        construct(expr, &expr);
    }

    template <typename InPlaceFactory>
    void construct(const InPlaceFactory &factory, const boost::in_place_factory_base *)
    {
        factory.template apply<Point>(m_storage);
    }

    template <typename TypedInPlaceFactory>
    void construct(const TypedInPlaceFactory &factory, const boost::typed_in_place_factory_base *)
    {
        factory.apply(m_storage);
    }

    template <typename Expr>
    void build(const Expr &expr)
    {
        construct(expr, &expr);
    }

    const Point &value() const
    {
        return *m_storage;
    }

private:
    static Point *uninitializedStorage()
    {
        return static_cast<Point *>(static_cast<void *>(new char[sizeof(Point)]));
    }
    Point *m_storage{uninitializedStorage()};
};

int main()
{
    Container p1(boost::in_place(1, 2));
    std::cout << "p1(" << p1.value().x << ", " << p1.value().y << ")\n";

    Container p2(boost::in_place<Point>(3, 4));
    std::cout << "p2(" << p2.value().x << ", " << p2.value().y << ")\n";

    return 0;
}
