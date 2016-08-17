function_traits
===============

Example:

```C++

#include <type_traits>
#include <iostream>
#include <iomanip>

#include <function_traits.hpp>

using namespace std;

int myFunction( int, float ) {

}

int main() {
    typedef function_traits<decltype( myFunction )> traits;

    cout << boolalpha << is_same<int, typename traits::template arg<0>::type>::value << endl; //true

    auto cb = []() -> double {
        return 10.0;
    };

    cout << boolalpha << is_same<double, typename function_traits<decltype( cb )>::result_type>::value << endl; //true

    return 0;
}

```
