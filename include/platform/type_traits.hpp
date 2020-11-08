#ifndef CAMERA_CONTROL_PLATFORM_SFINAE_HPP
#define CAMERA_CONTROL_PLATFORM_SFINAE_HPP

namespace platform
{

  template<typename ValueType, ValueType Value>
  struct integral_constant
  {
    using value_type = ValueType;
    using type = integral_constant;

    auto constexpr static value = Value;

    constexpr operator value_type() const noexcept
    {
      return value;
    }

    auto constexpr operator()() const noexcept -> value_type
    {
      return value;
    }
  };

  template<bool Value>
  using bool_constant = integral_constant<bool, Value>;

  using true_type = bool_constant<true>;
  using false_type = bool_constant<false>;

  template<typename LType, typename RType>
  struct is_same : false_type
  {
  };

  template<typename Type>
  struct is_same<Type, Type> : true_type
  {
  };

  template<typename LType, typename RType>
  auto constexpr is_same_v = is_same<LType, RType>::value;

  template<typename... Types>
  struct are_same : false_type
  {
  };

  template<typename SingleType>
  struct are_same<SingleType> : true_type
  {
  };

  template<typename FirstType, typename SecondType, typename... OtherTypes>
  struct are_same<FirstType, SecondType, OtherTypes...>
      : bool_constant<is_same_v<FirstType, SecondType> && are_same<SecondType, OtherTypes...>::value>
  {
  };

  template<typename... Types>
  auto constexpr are_same_v = are_same<Types...>::value;

  template<bool Enable, typename EnabledType = void>
  struct enable_if
  {
  };

  template<typename Candidate>
  struct is_enum : bool_constant<__is_enum(Candidate)>
  {
  };

  template<typename Candidate>
  auto constexpr is_enum_v = is_enum<Candidate>::value;

  template<typename Candidate, bool = is_enum_v<Candidate>>
  struct underlying_type
  {
  };

  template<typename Candidate>
  struct underlying_type<Candidate, true>
  {
    using type = __underlying_type(Candidate);
  };

  template<typename Candidate>
  using underlying_type_t = typename underlying_type<Candidate>::type;

  template<typename InputType>
  struct remove_cv
  {
    using type = InputType;
  };

  template<typename InputType>
  struct remove_cv<InputType const>
  {
    using type = InputType;
  };

  template<typename InputType>
  struct remove_cv<InputType volatile>
  {
    using type = InputType;
  };

  template<typename InputType>
  struct remove_cv<InputType const volatile>
  {
    using type = InputType;
  };

  template<typename InputType>
  using remove_cv_t = typename remove_cv<InputType>::type;

  namespace detail
  {

    template<typename Candidate>
    struct is_integral : false_type
    {
    };

    template<>
    struct is_integral<bool> : true_type
    {
    };

    template<>
    struct is_integral<char> : true_type
    {
    };

    template<>
    struct is_integral<unsigned char> : true_type
    {
    };

    template<>
    struct is_integral<signed char> : true_type
    {
    };

    template<>
    struct is_integral<char8_t> : true_type
    {
    };

    template<>
    struct is_integral<char16_t> : true_type
    {
    };

    template<>
    struct is_integral<char32_t> : true_type
    {
    };

    template<>
    struct is_integral<wchar_t> : true_type
    {
    };

    template<>
    struct is_integral<short> : true_type
    {
    };

    template<>
    struct is_integral<int> : true_type
    {
    };

    template<>
    struct is_integral<long> : true_type
    {
    };

    template<>
    struct is_integral<long long> : true_type
    {
    };

    template<>
    struct is_integral<unsigned short> : true_type
    {
    };

    template<>
    struct is_integral<unsigned int> : true_type
    {
    };

    template<>
    struct is_integral<unsigned long> : true_type
    {
    };

    template<>
    struct is_integral<unsigned long long> : true_type
    {
    };

  }  // namespace detail

  template<typename Candidate>
  struct is_integral : detail::is_integral<remove_cv_t<Candidate>>
  {
  };

  template<typename Candidate>
  auto constexpr is_integral_v = is_integral<Candidate>::value;

  template<typename EnabledType>
  struct enable_if<true, EnabledType>
  {
    using type = EnabledType;
  };

  template<bool Enable, typename EnabledType = void>
  using enable_if_t = typename enable_if<Enable, EnabledType>::type;

}  // namespace platform

#endif
