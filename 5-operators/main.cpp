#include <boost/operators.hpp>

#include <cmath>
#include <iostream>
#include <stdexcept>

struct FancyInt : boost::operators<FancyInt>
{
    explicit FancyInt(int val) :
        m_fancy(val)
    {
    }

    // clang-format off
    bool operator<(const FancyInt &rhs) const   { return m_fancy < rhs.m_fancy; }
    bool operator==(const FancyInt &rhs) const  { return m_fancy == rhs.m_fancy; }
    FancyInt &operator+=(const FancyInt &rhs)   { m_fancy += rhs.m_fancy; return *this; }
    FancyInt &operator-=(const FancyInt &rhs)   { m_fancy -= rhs.m_fancy; return *this; }
    FancyInt &operator*=(const FancyInt &rhs)   { m_fancy *= rhs.m_fancy; return *this; }
    FancyInt &operator/=(const FancyInt &rhs)   { m_fancy /= rhs.m_fancy; return *this; }
    FancyInt &operator%=(const FancyInt &rhs)   { m_fancy %= rhs.m_fancy; return *this; }
    FancyInt &operator|=(const FancyInt &rhs)   { m_fancy |= rhs.m_fancy; return *this; }
    FancyInt &operator&=(const FancyInt &rhs)   { m_fancy &= rhs.m_fancy; return *this; }
    FancyInt &operator^=(const FancyInt &rhs)   { m_fancy ^= rhs.m_fancy; return *this; }
    FancyInt &operator<<=(const FancyInt &rhs)  { m_fancy <<= rhs.m_fancy; return *this; }
    FancyInt &operator>>=(const FancyInt &rhs)  { m_fancy >>= rhs.m_fancy; return *this; }
    FancyInt &operator++()                      { ++m_fancy; return *this; }
    FancyInt &operator--()                      { --m_fancy; return *this; }
    // clang-format on

    operator int() const
    {
        return m_fancy;
    }

private:
    int m_fancy{};
};

struct Complex : boost::less_than_comparable<Complex>,
                 boost::equality_comparable<Complex>,
                 boost::addable<Complex>,
                 boost::subtractable<Complex>,
                 boost::multipliable<Complex>,
                 boost::dividable<Complex>,
                 boost::modable<Complex>,
                 boost::incrementable<Complex>,
                 boost::decrementable<Complex>
{
    Complex(float r, float i) :
        real(r),
        imag(i)
    {
    }
    Complex(const Complex &rhs) :
        real(rhs.real),
        imag(rhs.imag)
    {
    }

    float real;
    float imag;

    // clang-format off
    bool operator<(const Complex &rhs) const    { return real < rhs.real || (real == rhs.real && imag < rhs.imag); }
    bool operator==(const Complex &rhs) const   { return real == rhs.real && imag == rhs.imag; }
    Complex &operator+=(const Complex &rhs)     { real += rhs.real; imag += rhs.imag; return *this; }
    Complex &operator-=(const Complex &rhs)     { real -= rhs.real; imag -= rhs.imag; return *this; }
    Complex &operator*=(const Complex &rhs)     { real *= rhs.real; imag *= rhs.imag; return *this; } // only for purposes of exposition :)
    Complex &operator/=(const Complex &rhs)     { real /= rhs.real; imag /= rhs.imag; return *this; } // only for purposes of exposition :)
    Complex &operator%=(const Complex &rhs)     { real = std::fmod(real, rhs.real); imag = std::fmod(imag, rhs.imag); return *this; }
    Complex &operator++()                       { real++; return *this; }
    Complex &operator--()                       { real--; return *this; }
    // clang-format on
};

template <typename T, typename U>
void require_equal(T t, U u)
{
    if (t != u)
    {
        throw std::runtime_error("not equal");
    }
}

int main()
{
    try
    {
        {
            FancyInt i(10);
            FancyInt j(2);
            require_equal(10, i);
            require_equal(12, i + j);
            require_equal(8, i - j);
            require_equal(20, i * j);
            require_equal(5, i / j);
            require_equal(10, i | j);
            require_equal(2, i & j);
        }

        {
            Complex z1(1, 1);
            Complex z2(-1, -1);
            require_equal(0.0f, (z1 + z2).real);
            require_equal(2.0f, (z1 - z2).real);
            require_equal(-1.0f, (z1 * z2).real);
        }
    }
    catch (const std::exception &bang)
    {
        std::cerr << "oops: " << bang.what() << '\n';
        return 1;
    }
    catch (...)
    {
        return 2;
    }
    return 0;
}
