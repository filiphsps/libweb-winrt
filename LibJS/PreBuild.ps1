$curDir = Get-Location

Set-Location .\..\serenity
git reset --hard
Set-Location $curDir

# Hacks n' workarounds
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\AbstractOperations.cpp).replace('new_target ?: js_undefined()', 'new_target ? new_target : js_undefined()') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\AbstractOperations.cpp
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\ObjectPrototype.cpp).replace('*desc->get ?: js_undefined()', '*desc->get ? *desc->get : js_undefined()') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\ObjectPrototype.cpp
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\ObjectPrototype.cpp).replace('*desc->set ?: js_undefined()', '*desc->set ? *desc->set : js_undefined()') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\ObjectPrototype.cpp

(Get-Content .\..\serenity\Userland\Libraries\LibJS\Token.h).replace('(Empty) -> StringView { VERIFY_NOT_REACHED(); }', '(Empty) { VERIFY_NOT_REACHED(); return StringView {}; }') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Token.h
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Token.h).replace('(Empty) -> FlyString { VERIFY_NOT_REACHED(); }', '(Empty) { VERIFY_NOT_REACHED(); return FlyString {}; }') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Token.h

(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h).replace('#define __TRY_OR_REJECT', '#define __TRY_OR_REJECT_BAK') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h).replace('#define TRY_OR_REJECT_WITH_VALUE', '#define TRY_OR_REJECT_WITH_VALUE_BAK') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h

(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\NumberConstructor.cpp).replace('#ifdef __clang__', '#if defined(__clang__) || defined(AK_OS_WINRT)') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\NumberConstructor.cpp
