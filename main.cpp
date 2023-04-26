#include <functional>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

namespace Lambda {

template <typename T>
struct Performer {
  // The ability to contain members
  // The ability to preserve state between calls to operator()
  void operator()(const T&);
};

} // namespace Lambda

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// WTF.h
namespace WTF {

template <typename T>
void MyFunction(const std::function<void(const T&)>& cb);

template <typename T>
void Woah(const std::function<void(const T&)>& cb);

} // namespace WTF

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

namespace Data {

struct Transfer {
  // Store some transferable data
};

} // namespace Transfer

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
  WTF::MyFunction<Data::Transfer>([](const Data::Transfer& data) { /* ... */ });

  WTF::Woah<Data::Transfer>([](const Data::Transfer& data) { /* ... */ });

  WTF::MyFunction<Data::Transfer>(Lambda::Performer<Data::Transfer> {});

  return 0;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <typename T>
void Lambda::Performer<T>::operator()(const T& _t)
{
  // Perform stuff on T...
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <typename T>
void WTF::MyFunction(const std::function<void(const T&)>& cb)
{
  // Perform task...
}

template <typename T>
void WTF::Woah(const std::function<void(const T&)>& cb)
{
  // Perform task...
}
