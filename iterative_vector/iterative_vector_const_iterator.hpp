#include <iterator>

template<typename ITV>
class const_itv_iterator{
    using value_type = typename ITV::value_type;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = value_type*;
    using reference = value_type*;
    using difference_type = std::ptrdiff_t;

};

