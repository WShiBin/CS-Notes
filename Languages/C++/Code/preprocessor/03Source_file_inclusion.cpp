#if __has_include(<optional>)
#include <optional>
#define have_optional 1
#elif __has_include(<experimental/optional>)
#include <experimental/optional>
#define have_optional 1
#define experimental_optional 1
#else
#define have_optional 0
#endif

#include <iostream>

int main()
{
    if (have_optional)
        std::cout << "<optional> is present.\n";

    int x = 42;
#if have_optional == 1
    std::optional<int> i = x;
#else
    int *i = &x;
#endif
    std::cout << "i = " << *i << '\n';
}