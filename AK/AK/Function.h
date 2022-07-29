/*
 * Copyright (C) 2016 Apple Inc. All rights reserved.
 * Copyright (c) 2021, Gunnar Beutner <gbeutner@serenityos.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include "./AK/Assertions.h"
#include "./AK/Atomic.h"
#include "./AK/BitCast.h"
#include "./AK/Noncopyable.h"
#include "./AK/ScopeGuard.h"
#include "./AK/StdLibExtras.h"
#include "./AK/Types.h"

namespace AK {

template<typename>
class Function;

template<typename F>
inline constexpr bool IsFunctionPointer = (IsPointer<F> && IsFunction<RemovePointer<F>>);

// Not a function pointer, and not an lvalue reference.
template<typename F>
inline constexpr bool IsFunctionObject = (!IsFunctionPointer<F> && IsRvalueReference<F&&>);

template<typename Out, typename... In>
class Function<Out(In...)> {
    AK_MAKE_NONCOPYABLE(Function);

public:
    Function() = default;
    Function(std::nullptr_t)
    {
    }

    ~Function() = default;

    template<typename CallableType>
    Function(CallableType&& callable) requires((IsFunctionObject<CallableType>&& IsCallableWithArguments<CallableType, In...> && !IsSame<RemoveCVReference<CallableType>, Function>));

    template<typename FunctionType>
    Function(FunctionType f) requires((IsFunctionPointer<FunctionType>&& IsCallableWithArguments<RemovePointer<FunctionType>, In...> && !IsSame<RemoveCVReference<FunctionType>, Function>));

    Function(Function&& other);

    Out operator()(In... in) const;

    explicit operator bool() const;

    template<typename CallableType>
    Function& operator=(CallableType&& callable) requires((IsFunctionObject<CallableType>&& IsCallableWithArguments<CallableType, In...>));

    template<typename FunctionType>
    Function& operator=(FunctionType f) requires((IsFunctionPointer<FunctionType>&& IsCallableWithArguments<RemovePointer<FunctionType>, In...>));

    Function& operator=(std::nullptr_t);

    Function& operator=(Function&& other);

private:
    class CallableWrapperBase {
    public:
        virtual ~CallableWrapperBase() = default;
        // Note: This is not const to allow storing mutable lambdas.
        virtual Out call(In...) = 0;
        virtual void destroy() = 0;
        virtual void init_and_swap(u8*, size_t) = 0;
    };

    template<typename CallableType>
    class CallableWrapper final : public CallableWrapperBase {
        AK_MAKE_NONMOVABLE(CallableWrapper);
        AK_MAKE_NONCOPYABLE(CallableWrapper);

    public:
        explicit CallableWrapper(CallableType&& callable)
            : m_callable(move(callable))
        {
        }

        Out call(In... in) final override;

        void destroy();

        void init_and_swap(u8* destination, size_t size) final override;

    private:
        CallableType m_callable;
    };

    enum class FunctionKind {
        NullPointer,
        Inline,
        Outline,
    };

    CallableWrapperBase* callable_wrapper() const;

    void clear(bool may_defer = true);

    template<typename Callable>
    void init_with_callable(Callable&& callable);

    void move_from(Function&& other);

    FunctionKind m_kind{ FunctionKind::NullPointer };
    bool m_deferred_clear{ false };
    //mutable Atomic<u16> m_call_nesting_level{ 0 };
    static constexpr size_t inline_capacity = 4 * sizeof(void*);
    //alignas(max(alignof(CallableWrapperBase), alignof(CallableWrapperBase*))) u8 m_storage[inline_capacity];
};

}

using AK::Function;
