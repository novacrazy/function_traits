function_traits
===============

### Example:

```C++

#include <type_traits>
#include <iostream>
#include <iomanip>

#include <function_traits.hpp>

using namespace std;
using namespace fn_traits;

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

### API

#### [Click here for Doxygen generated documentation](https://novacrazy.github.io/function_traits/html/index.html)

All of these are within the namespace `fn_traits`.

#### `function_traits<Functor>::arity`

Integer value representing the number of parameters in the given Functor
 
#### `function_traits<Functor>::result_type`
##### alias: `function_traits<Functor>::return_type`
The return/result type of the Functor
 
#### `function_traits<Functor>::function_type`

A simplified version of Functor

#### `function_traits<Functor>::template arg<N>::type`

Access the type of argument `N`

#### `function_traits<Functor>::tuple_type`

Shortcut for `std::tuple<Args...>` where `Args...` are the arguments of the Functor given.
