#pragma once

#include "./AK/Assertions.h"
#include "./AK/Format.h"
#include "./AK/RefCounted.h"
#include "./AK/StdLibExtras.h"
#include "./AK/Traits.h"
#include "./AK/Types.h"

namespace AK {

template<typename T>
class WeakPtr;

template<typename T>
class NonnullOwnPtr {
public:
    using ElementType = T;

    enum AdoptTag { Adopt };

    // FIXME: this shouldn't exist
    NonnullOwnPtr()
    {
    }

    NonnullOwnPtr(AdoptTag, T& ptr)
        : m_ptr(&ptr)
    {
    }
    NonnullOwnPtr(NonnullOwnPtr&& other)
        : m_ptr(other.leak_ptr())
    {
    }
    template<typename U>
    NonnullOwnPtr(NonnullOwnPtr<U>&& other)
        : m_ptr(other.leak_ptr())
    {
    }

    T* leak_ptr();
    ALWAYS_INLINE T* ptr();

    NonnullOwnPtr(NonnullOwnPtr const&) = delete;
    template<typename U>
    NonnullOwnPtr(NonnullOwnPtr<U> const&) = delete;
    NonnullOwnPtr& operator=(NonnullOwnPtr const&) = delete;
    template<typename U>
    NonnullOwnPtr& operator=(NonnullOwnPtr<U> const&) = delete;

    template<typename U>
    NonnullOwnPtr(RefPtr<U> const&) = delete;
    template<typename U>
    NonnullOwnPtr(NonnullRefPtr<U> const&) = delete;
    template<typename U>
    NonnullOwnPtr(WeakPtr<U> const&) = delete;
    template<typename U>
    NonnullOwnPtr& operator=(RefPtr<U> const&) = delete;
    template<typename U>
    NonnullOwnPtr& operator=(NonnullRefPtr<U> const&) = delete;
    template<typename U>
    NonnullOwnPtr& operator=(WeakPtr<U> const&) = delete;

    ALWAYS_INLINE T* operator->();
    ALWAYS_INLINE const T* operator->() const;

    ALWAYS_INLINE T& operator*();
    ALWAYS_INLINE const T& operator*() const;

    ALWAYS_INLINE operator const T* () const;
    ALWAYS_INLINE operator T* ();

    operator bool() const = delete;
    bool operator!() const = delete;

private:
    T* m_ptr = nullptr;
};

template<typename T>
ALWAYS_INLINE NonnullOwnPtr<T> adopt_own(T& object)
{
    return NonnullOwnPtr<T>(NonnullOwnPtr<T>::Adopt, object);
}

template<class T, class... Args>
    requires(IsConstructible<T, Args...>) ALWAYS_INLINE NonnullOwnPtr<T> make(Args&&... args)
{
    return NonnullOwnPtr<T>(NonnullOwnPtr<T>::Adopt, *new T(forward<Args>(args)...));
}

template<class T, class... Args>
ALWAYS_INLINE NonnullOwnPtr<T> make(Args&&... args)
{
    return NonnullOwnPtr<T>(NonnullOwnPtr<T>::Adopt, *new T{ forward<Args>(args)... });
}

template<typename T>
struct Traits<NonnullOwnPtr<T>> : public GenericTraits<NonnullOwnPtr<T>> {
    using PeekType = T*;
    using ConstPeekType = const T*;
    static unsigned hash(NonnullOwnPtr<T> const& p) { return ptr_hash((FlatPtr)p.ptr()); }
    static bool equals(NonnullOwnPtr<T> const& a, NonnullOwnPtr<T> const& b) { return a.ptr() == b.ptr(); }
};

template<typename T, typename U>
ALWAYS_INLINE void swap(NonnullOwnPtr<T>& a, NonnullOwnPtr<U>& b)
{
    a.swap(b);
}

template<typename T>
struct Formatter<NonnullOwnPtr<T>> : Formatter<const T*> {
    ErrorOr<void> format(FormatBuilder& builder, NonnullOwnPtr<T> const& value)
    {
        return Formatter<const T*>::format(builder, value.ptr());
    }
};

}

using AK::adopt_own;
using AK::make;
using AK::NonnullOwnPtr;
