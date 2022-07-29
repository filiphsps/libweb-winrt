#pragma once

#include "./AK/AllOf.h"
#include "./AK/Forward.h"
#include "./AK/Span.h"
#include "./AK/StdLibExtras.h"
#include "./AK/Try.h"

namespace AK {

template<typename T, typename ChunkType = Vector<T>>
class DisjointChunks {
public:
    DisjointChunks() = default;
    ~DisjointChunks() = default;
    DisjointChunks(DisjointChunks const&) = default;
    DisjointChunks(DisjointChunks&&) = default;

    DisjointChunks& operator=(DisjointChunks&&) = default;
    DisjointChunks& operator=(DisjointChunks const&) = default;

    void append(ChunkType&& chunk);
    void extend(DisjointChunks&& chunks);
    void extend(DisjointChunks const& chunks);

    ChunkType& first_chunk();
    ChunkType& last_chunk();
    ChunkType const& first_chunk() const;
    ChunkType const& last_chunk() const;

    void ensure_capacity(size_t needed_capacity);

    void insert(size_t index, T value);

    void clear();

    T& operator[](size_t index);
    T const& at(size_t index) const;
    T& at(size_t index);

    T* find(size_t index);

    T const* find(size_t index) const;

    size_t size() const;

    bool is_empty() const;
};

}

using AK::DisjointChunks;