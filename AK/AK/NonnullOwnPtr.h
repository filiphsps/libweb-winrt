#pragma once

namespace AK {

template<typename T>
class WeakPtr;

template<typename T>
class NonnullOwnPtr {
public:
    using ElementType = T;

    enum AdoptTag { Adopt };

    inline T* operator->();

    inline T& operator*();

    inline operator T* ();

private:
    T* m_ptr = nullptr;
};

}

using AK::NonnullOwnPtr;
