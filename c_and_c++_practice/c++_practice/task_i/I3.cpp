#include <iterator>
#include <exception>
template <typename T>
typename T::value_type
last3(const T &a){
    typename T::const_reverse_iterator i = a.rbegin();
    typename T::const_reverse_iterator j = a.rend();
    if ((i == j) || (++i == j) || (++i == j)){
        throw std::exception();
    }
    typename T::const_reverse_iterator k = a.rbegin();
    return *(k++) + *(k++) + *(k++);
}
