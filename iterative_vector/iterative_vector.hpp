#include <algorithm>
#include <mutex>
#include <set>
#include <vector>

template <typename T, typename Compare = std::less<T>,
          typename Allocator = std::allocator<T>>
class iterative_vector {
public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  // To be defined
  // iterator
  // const_iterator

  iterative_vector() = default;
  iterative_vector(std::initializer_list<T> l) : m_readonly_buffer(l) {}
  // iterative_vector(const iterator begin, const iterator end);

  iterative_vector(const iterative_vector &copy)
      : m_readonly_buffer(copy.m_readonly_buffer),
        m_write_only_buffer(copy.m_write_only_buffer) {}

  size_type size() const { return m_readonly_buffer.size(); }

  size_type pending_size() const { return m_write_only_buffer.size(); }

  void insert(const T &value) { m_readonly_buffer.push_back(value); }

  const std::set<T, Compare, Allocator> &data() const {
    return m_readonly_buffer;
  }
  const std::vector<T, Allocator> &pending_data() const {
    return m_readonly_buffer;
  }

  void refresh() {
    std::lock_guard<std::mutex> guard(m_data_lock);
    std::sort(m_write_only_buffer.begin(), m_write_only_buffer.end(),
              Compare{});
    std::vector<T> destination{};
    std::merge(m_readonly_buffer.begin(), m_readonly_buffer.end(),
               m_write_only_buffer.begin(), m_write_only_buffer.end(),
               std::back_inserter(destination), Compare{});
    m_readonly_buffer = std::set<T>(destination.begin(), destination.end());
    m_write_only_buffer.clear();
  }

  iterative_vector &operator=(iterative_vector other) {
    std::swap(*this, other);
    return *this;
  }

  friend void swap(iterative_vector &first, iterative_vector &second) {
    std::swap(first.m_readonly_buffer, second.m_readonly_buffer);
    std::swap(first.m_write_only_buffer, second.m_write_only_buffer);
  }

private:
  std::set<T, Compare, Allocator> m_readonly_buffer;
  std::vector<T, Allocator> m_write_only_buffer;
  std::mutex m_data_lock;
};