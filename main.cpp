#include <functional>
#include <iostream>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

namespace Lambda {

template <typename T> struct Performer {
  // The ability to contain members
  // The ability to preserve state between calls to operator()
  void operator()(const T &);
};

} // namespace Lambda

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// WTF.h
namespace WTF {

template <typename T> void MyFunction(const std::function<void(const T &)> &cb);

template <typename T> void Woah(const std::function<void(const T &)> &cb);

} // namespace WTF

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

namespace Data {

struct Transfer {
  // Store some transferable data
};

} // namespace Data

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

/**
 * I have read before about implicit conversion but I couldn't digest it.
 * Comming at a problem from a perspective of a person who already has a problem
 * and is looking for a way to solve it is always more efficient than just
 * reading mindlessly. The most difficult way to learn something is by just
 * accepting it because at that time it is unfamilair and the mind has to create
 * new connections to be able to digest it and consume that knowledge. The very
 * first time I was reading about implicit conversion when using constructors
 * that take single argument was confusing for me. However this time after I was
 * thinking about implicit conversion, I thought about it in the following way:
 * "I have a struct and I want to create it without using constructor, how can i
 * achieve implicit conversion by assigning a value without specifying which
 * constructor I called?"
 *
 * Once I knew in theory what I want to achieve and had a use case, I could
 * write down sample code that did that so I could experiment using it, get used
 * to syntax, get familiar, create meaning, etc.
 **/
namespace ImplicitConversion {

struct Construct {
  int m_value;
  Construct(int value);
};

} // namespace ImplicitConversion

namespace DisableImplicitConversion {

struct Construct {
  int m_value;
  explicit Construct(int value);
};

} // namespace DisableImplicitConversion

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main() {
  WTF::MyFunction<Data::Transfer>([](const Data::Transfer &data) { /* ... */ });

  WTF::Woah<Data::Transfer>([](const Data::Transfer &data) { /* ... */ });

  WTF::MyFunction<Data::Transfer>(Lambda::Performer<Data::Transfer>{});

  ImplicitConversion::Construct foo = 1; // Should implicitly convert
  // Check the constructed value
  std::cout << foo.m_value;

  // DisableImplicitConversion::Construct bar = 1; // Should throw an error
  // Check the constructed value
  // std::cout << bar.m_value;

  return 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <typename T> void Lambda::Performer<T>::operator()(const T &_t) {
  // Perform stuff on T...
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <typename T>
void WTF::MyFunction(const std::function<void(const T &)> &cb) {
  // Perform task...
}

template <typename T> void WTF::Woah(const std::function<void(const T &)> &cb) {
  // Perform task...
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

ImplicitConversion::Construct::Construct(int value) : m_value{value} {}

DisableImplicitConversion::Construct::Construct(int value) : m_value{value} {}
