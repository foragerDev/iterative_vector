#include <vector>

template<typename T, typename Allocator = std::allocator<T>>
class iterative_vector {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;
        //To be defined
        //iterator
        //const_iterator

        iterative_vector() = default;
        iterative_vector(std::initializer_list<T> l) : m_readonly_buffer(l){
        }
        //iterative_vector(const iterator begin, const iterator end);
private:
    std::vector<T, Allocator> m_readonly_buffer;
    std::vector<T, Allocator> m_write_only_buffer; 
};