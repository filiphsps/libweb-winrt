#pragma once

namespace AK {

template<typename T>
class WeakPtr;

template<typename T>
class NonnullOwnPtr {
public:
    using ElementType = T;

    enum AdoptTag { Adopt };

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
    inline T* ptr();

    NonnullOwnPtr(NonnullOwnPtr const&) = delete;
    template<typename U>
    NonnullOwnPtr(NonnullOwnPtr<U> const&) = delete;
    NonnullOwnPtr& operator=(NonnullOwnPtr const&) = delete;
    template<typename U>
    NonnullOwnPtr& operator=(NonnullOwnPtr<U> const&) = delete;

    /*template<typename U>
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
    NonnullOwnPtr& operator=(WeakPtr<U> const&) = delete;*/

    inline T* operator->();
    inline const T* operator->() const;

    inline T& operator*();
    inline const T& operator*() const;

    inline operator const T* () const;
    inline operator T* ();

    operator bool() const = delete;
    bool operator!() const = delete;

private:
    T* m_ptr = nullptr;
};

template<typename T>
inline NonnullOwnPtr<T> adopt_own(T& object)
{
    return NonnullOwnPtr<T>(NonnullOwnPtr<T>::Adopt, object);
}

template<class T, class... Args>
    requires(IsConstructible<T, Args...>) inline NonnullOwnPtr<T> make(Args&&... args)
{
    return NonnullOwnPtr<T>(NonnullOwnPtr<T>::Adopt, *new T(forward<Args>(args)...));
}

// FIXME: Remove once P0960R3 is available in Clang.
template<class T, class... Args>
inline NonnullOwnPtr<T> make(Args&&... args)
{
    return NonnullOwnPtr<T>(NonnullOwnPtr<T>::Adopt, *new T{ forward<Args>(args)... });
}

/*template<typename T>
struct Traits<NonnullOwnPtr<T>> : public GenericTraits<NonnullOwnPtr<T>> {
    using PeekType = T*;
    using ConstPeekType = const T*;
    static unsigned hash(NonnullOwnPtr<T> const& p) { return ptr_hash((FlatPtr)p.ptr()); }
    static bool equals(NonnullOwnPtr<T> const& a, NonnullOwnPtr<T> const& b) { return a.ptr() == b.ptr(); }
};

template<typename T, typename U>
inline void swap(NonnullOwnPtr<T>& a, NonnullOwnPtr<U>& b)
{
    a.swap(b);
}

template<typename T>
struct Formatter<NonnullOwnPtr<T>> : Formatter<const T*> {
    ErrorOr<void> format(FormatBuilder& builder, NonnullOwnPtr<T> const& value)
    {
        return Formatter<const T*>::format(builder, value.ptr());
    }
};*/

}

using AK::adopt_own;
using AK::make;
using AK::NonnullOwnPtr;
