#pragma once

namespace AK {

template<typename Container, typename ValueType>
class SimpleIterator {
public:
    friend Container;
};

}