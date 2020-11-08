#ifndef CAMERA_CONTROL_PLATFORM_ARRAY_HPP
#define CAMERA_CONTROL_PLATFORM_ARRAY_HPP

#include <stddef.h>
#include <stdint.h>

namespace platform
{
  template<typename ValueType, size_t Size>
  struct array
  {
    using value_type = ValueType;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using reference = value_type &;
    using const_reference = value_type const &;
    using pointer = value_type *;
    using const_pointer = value_type const *;
    using iterator = pointer;
    using const_iterator = const_pointer;

    auto constexpr data() noexcept -> pointer
    {
      return static_cast<pointer>(m_data);
    }

    auto constexpr data() const noexcept -> const_pointer
    {
      return static_cast<const_pointer>(m_data);
    }

    auto constexpr size() const noexcept -> size_type
    {
      return Size;
    }

    auto constexpr empty() const noexcept -> bool
    {
      return size();
    }

    auto constexpr operator[](size_t index) noexcept -> reference
    {
      return *(begin() + index);
    }

    auto constexpr operator[](size_t index) const noexcept -> const_reference
    {
      return *(begin() + index);
    }

    auto constexpr front() noexcept -> reference
    {
      return *begin();
    }

    auto constexpr front() const noexcept -> const_reference
    {
      return *begin();
    }

    auto constexpr back() noexcept -> reference
    {
      return *(end() - 1);
    }

    auto constexpr back() const noexcept -> const_reference
    {
      return *(end() - 1);
    }

    auto constexpr begin() noexcept -> iterator
    {
      return data();
    }

    auto constexpr begin() const noexcept -> const_iterator
    {
      return data();
    }

    auto constexpr cbegin() const noexcept -> const_iterator
    {
      return begin();
    }

    auto constexpr end() noexcept -> iterator
    {
      return data() + static_cast<difference_type>(size());
    }

    auto constexpr end() const noexcept -> const_iterator
    {
      return data() + static_cast<difference_type>(size());
    }

    auto constexpr cend() const noexcept -> const_iterator
    {
      return end();
    }

    ValueType m_data[Size]{};
  };

  template<typename ElementTypes, typename... RemainingElements>
  array(ElementTypes, RemainingElements...) -> array<ElementTypes, 1 + sizeof...(RemainingElements)>;
}  // namespace platform

#endif