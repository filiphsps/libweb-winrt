#pragma once

#include <variant>
#include "Forward.h"

namespace AK {
using Empty = std::monostate;

template<typename... Ts>
struct Variant : public std::variant<Ts...> {
    Variant();

    using std::variant<Ts...>::variant;
    using std::variant<Ts...>::operator=;

    template<typename T>
    void set(T&& t)
    {
        *this = std::forward<T>(t);
    }

    template<typename T>
    T* get_pointer()
    {
        return std::get_if<T>(this);
    }

    template<typename T>
    T& get()
    {
        return std::get<T>(*this);
    }

    template<typename T>
    T* get_pointer() const
    {
        return const_cast<T*>(std::get_if<T>(this));
    }

    template<typename T>
    T& get() const
    {
        return const_cast<T&>(std::get<T>(*this));
    }

    template<typename T>
    bool has() const
    {
        return std::holds_alternative<T>(*this);
    }

    template<typename... Us>
    struct overloaded : Us... { using Us::operator()...; };

    template<typename... Fs>
    decltype(auto) visit(Fs&&... functions) const
    {
        return std::visit(overloaded{ std::forward<Fs>(functions)... }, *this);
    }

    template<typename... Fs>
    decltype(auto) visit(Fs&&... functions)
    {
        return std::visit(overloaded{ std::forward<Fs>(functions)... }, *this);
    }

    template<typename... NewTs>
    Variant<NewTs...> downcast()&&;
    /* {
        return std::visit([](auto& entry) -> Variant<NewTs...> {
            return Variant<NewTs...>(std::move(entry));
            }, *this);
    }*/

    template<typename... NewTs>
    Variant<NewTs...> downcast() const&;
    /* {
        return std::visit([](auto const& entry) -> Variant<NewTs...> {
            return entry;
            }, *this);
    }*/
};
}

using AK::Empty;
using AK::Variant;
