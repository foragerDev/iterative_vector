#include <iterator>

template<typename ITV>
class const_it_vector_iterator{
    using value_type = typename ITV::value_type;
    using iterator_category = std::random_access_iterator_tag;
    using pointer = value_type*;
    using reference = value_type*;
    using difference_type = std::ptrdiff_t;

};

