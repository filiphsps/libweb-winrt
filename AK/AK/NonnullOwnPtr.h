#pragma once

namespace AK {

template<typename T>
class WeakPtr;

template<typename T>
class NonnullOwnPtr {

    inline T* operator->();

    inline T& operator*();

    inline operator T* ();

};

}

using AK::NonnullOwnPtr;
