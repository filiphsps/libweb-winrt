#pragma once

#include "./AK/Assertions.h"
#include "./AK/Error.h"
#include "./AK/Span.h"
#include "./AK/Types.h"
#include "./AK/kmalloc.h"

namespace AK {
namespace Detail {

template<size_t inline_capacity>
class ByteBuffer {
public:
    ByteBuffer() = default;

    ~ByteBuffer()
    {
        clear();
    }

    ByteBuffer(ByteBuffer const& other);

    ByteBuffer(ByteBuffer&& other);

    ByteBuffer& operator=(ByteBuffer&& other);

    ByteBuffer& operator=(ByteBuffer const& other);

    static ErrorOr<ByteBuffer> create_uninitialized(size_t size);

    static ErrorOr<ByteBuffer> create_zeroed(size_t size);

    static ErrorOr<ByteBuffer> copy(void const* data, size_t size);

    static ErrorOr<ByteBuffer> copy(ReadonlyBytes bytes);

    template<size_t other_inline_capacity>
    bool operator==(ByteBuffer<other_inline_capacity> const& other) const;

    bool operator!=(ByteBuffer const& other) const { return !(*this == other); }

    u8& operator[](size_t i);

    u8 const& operator[](size_t i) const;

    bool is_empty() const { return m_size == 0; }
    size_t size() const { return m_size; }

    u8* data() { return m_inline ? m_inline_buffer : m_outline_buffer; }
    u8 const* data() const { return m_inline ? m_inline_buffer : m_outline_buffer; }

    Bytes bytes() { return { data(), size() }; }
    ReadonlyBytes bytes() const { return { data(), size() }; }

    AK::Span<u8> span() { return { data(), size() }; }
    AK::Span<const u8> span() const { return { data(), size() }; }

    u8* offset_pointer(int offset) { return data() + offset; }
    u8 const* offset_pointer(int offset) const { return data() + offset; }

    void* end_pointer() { return data() + m_size; }
    void const* end_pointer() const { return data() + m_size; }

    ErrorOr<ByteBuffer> slice(size_t offset, size_t size) const;

    void clear();

    inline void resize(size_t new_size);

    inline void ensure_capacity(size_t new_capacity);

    ErrorOr<void> try_resize(size_t new_size);

    ErrorOr<void> try_ensure_capacity(size_t new_capacity);

    /// Return a span of bytes past the end of this ByteBuffer for writing.
    /// Ensures that the required space is available.
    ErrorOr<Bytes> get_bytes_for_writing(size_t length);

    /// Like get_bytes_for_writing, but crashes if allocation fails.
    Bytes must_get_bytes_for_writing(size_t length);

    void append(u8 byte);

    void append(ReadonlyBytes bytes);

    void append(void const* data, size_t data_size) { append({ data, data_size }); }

    ErrorOr<void> try_append(u8 byte);

    ErrorOr<void> try_append(ReadonlyBytes bytes);

    ErrorOr<void> try_append(void const* data, size_t data_size);

    void operator+=(ByteBuffer const& other);

    void overwrite(size_t offset, void const* data, size_t data_size);

    void zero_fill();

    operator Bytes() { return bytes(); }
    operator ReadonlyBytes() const { return bytes(); }

    inline size_t capacity() const { return m_inline ? inline_capacity : m_outline_capacity; }

private:
    void move_from(ByteBuffer&& other);

    void trim(size_t size, bool may_discard_existing_data);

    NEVER_INLINE void shrink_into_inline_buffer(size_t size, bool may_discard_existing_data);

    NEVER_INLINE ErrorOr<void> try_ensure_capacity_slowpath(size_t new_capacity);

    union {
        u8 m_inline_buffer[inline_capacity];
        struct {
            u8* m_outline_buffer;
            size_t m_outline_capacity;
        };
    };
    size_t m_size{ 0 };
    bool m_inline{ true };
};

}

/*template<>
struct Traits<ByteBuffer> : public GenericTraits<ByteBuffer> {
static unsigned hash(ByteBuffer const& byte_buffer)
{
    return Traits<ReadonlyBytes>::hash(byte_buffer.span());
}
};*/

}
