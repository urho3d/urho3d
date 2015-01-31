//
// Copyright (c) 2008-2015 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#pragma once

#include "../Container/Vector.h"
#include "../Container/List.h"
#include "../Container/HashSet.h"
#include "../Container/HashMap.h"

#include <algorithm>

namespace std
{

template <class T> typename Urho3D::Vector<T>::ConstIterator begin(const Urho3D::Vector<T>& v) { return v.Begin(); }
template <class T> typename Urho3D::Vector<T>::ConstIterator end(const Urho3D::Vector<T>& v) { return v.End(); }
template <class T> typename Urho3D::Vector<T>::Iterator begin(Urho3D::Vector<T>& v) { return v.Begin(); }
template <class T> typename Urho3D::Vector<T>::Iterator end(Urho3D::Vector<T>& v) { return v.End(); }

template <class T> typename Urho3D::PODVector<T>::ConstIterator begin(const Urho3D::PODVector<T>& v) { return v.Begin(); }
template <class T> typename Urho3D::PODVector<T>::ConstIterator end(const Urho3D::PODVector<T>& v) { return v.End(); }
template <class T> typename Urho3D::PODVector<T>::Iterator begin(Urho3D::PODVector<T>& v) { return v.Begin(); }
template <class T> typename Urho3D::PODVector<T>::Iterator end(Urho3D::PODVector<T>& v) { return v.End(); }

template <class T> typename Urho3D::List<T>::ConstIterator begin(const Urho3D::List<T>& v) { return v.Begin(); }
template <class T> typename Urho3D::List<T>::ConstIterator end(const Urho3D::List<T>& v) { return v.End(); }
template <class T> typename Urho3D::List<T>::Iterator begin(Urho3D::List<T>& v) { return v.Begin(); }
template <class T> typename Urho3D::List<T>::Iterator end(Urho3D::List<T>& v) { return v.End(); }

template <class T, class U> typename Urho3D::HashMap<T, U>::ConstIterator begin(const Urho3D::HashMap<T, U>& v) { return v.Begin(); }
template <class T, class U> typename Urho3D::HashMap<T, U>::ConstIterator end(const Urho3D::HashMap<T, U>& v) { return v.End(); }
template <class T, class U> typename Urho3D::HashMap<T, U>::Iterator begin(Urho3D::HashMap<T, U>& v) { return v.Begin(); }
template <class T, class U> typename Urho3D::HashMap<T, U>::Iterator end(Urho3D::HashMap<T, U>& v) { return v.End(); }

template <class T> typename Urho3D::HashSet<T>::ConstIterator begin(const Urho3D::HashSet<T>& v) { return v.Begin(); }
template <class T> typename Urho3D::HashSet<T>::ConstIterator end(const Urho3D::HashSet<T>& v) { return v.End(); }
template <class T> typename Urho3D::HashSet<T>::Iterator begin(Urho3D::HashSet<T>& v) { return v.Begin(); }
template <class T> typename Urho3D::HashSet<T>::Iterator end(Urho3D::HashSet<T>& v) { return v.End(); }

}

// VS2010+ and other compilers: use std::begin(), std::end() & range based for
// C++11 features need to be enabled
#if !defined(_MSC_VER) || _MSC_VER > 1600
#define foreach(VAL, VALS) for (VAL : VALS)
// Fallback solution for VS2010. Will have problem with break statement.
// See https://github.com/urho3d/Urho3D/issues/561
#else

namespace Urho3D
{

template<typename T>
struct false_wrapper {
    false_wrapper(const T& value) : value(value) { }
    operator bool() const { return false; }
    T value;
};

template<typename T>
false_wrapper<T> make_false_wrapper(const T& value) {
    return false_wrapper<T>(value);
}

// vector support functions

template <class T>
Urho3D::RandomAccessIterator<T> Begin(Urho3D::Vector<T> &v) {
    return v.Begin();
}
template <class T>
Urho3D::RandomAccessIterator<T> Begin(Urho3D::Vector<T> *v) {
    return v->Begin();
}

template <class T>
Urho3D::RandomAccessConstIterator<T> Begin(const Urho3D::Vector<T> &v) {
    return v.Begin();
}
template <class T>
Urho3D::RandomAccessConstIterator<T> Begin(const Urho3D::Vector<T> *v) {
    return v->Begin();
}

template <class T>
Urho3D::RandomAccessIterator<T> End(Urho3D::Vector<T> &v) {
    return v.End();
}
template <class T>
Urho3D::RandomAccessIterator<T> End(Urho3D::Vector<T> *v) {
    return v->End();
}

template <class T>
Urho3D::RandomAccessConstIterator<T> End(const Urho3D::Vector<T> &v) {
    return v.End();
}
template <class T>
Urho3D::RandomAccessConstIterator<T> End(const Urho3D::Vector<T> *v) {
    return v->End();
}

// podvector support functions

template <class T>
Urho3D::RandomAccessIterator<T> Begin(Urho3D::PODVector<T> &v) {
    return v.Begin();
}
template <class T>
Urho3D::RandomAccessIterator<T> Begin(Urho3D::PODVector<T> *v) {
    return v->Begin();
}

template <class T>
Urho3D::RandomAccessConstIterator<T> Begin(const Urho3D::PODVector<T> &v) {
    return v.Begin();
}
template <class T>
Urho3D::RandomAccessConstIterator<T> Begin(const Urho3D::PODVector<T> *v) {
    return v->Begin();
}

template <class T>
Urho3D::RandomAccessIterator<T> End(Urho3D::PODVector<T> &v) {
    return v.End();
}
template <class T>
Urho3D::RandomAccessIterator<T> End(Urho3D::PODVector<T> *v) {
    return v->End();
}

template <class T>
Urho3D::RandomAccessConstIterator<T> End(const Urho3D::PODVector<T> &v) {
    return v.End();
}
template <class T>
Urho3D::RandomAccessConstIterator<T> End(const Urho3D::PODVector<T> *v) {
    return v->End();
}

}

#define foreach(VAL, VALS) \
    if (const auto& _foreach_begin = Urho3D::make_false_wrapper(Urho3D::Begin(VALS))) { } else \
    if (const auto& _foreach_end = Urho3D::make_false_wrapper(Urho3D::End(VALS))) { } else \
    for (auto it = _foreach_begin.value; it != _foreach_end.value; ++it) \
    if (bool _foreach_flag = false) { } else \
    for (VAL = *it; !_foreach_flag; _foreach_flag = true)

#endif
