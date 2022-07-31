$curDir = Get-Location

Write-Host "Resetting serenity codebase..." -NoNewline
Set-Location .\..\serenity
git reset --hard --quiet
Set-Location $curDir
Write-Host " Done!"

# Hacks n' workarounds
Write-Host "Starting serenity code patching..." -NoNewline
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\AbstractOperations.cpp).replace('new_target ?: js_undefined()', 'new_target ? new_target : js_undefined()') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\AbstractOperations.cpp
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\ObjectPrototype.cpp).replace('*desc->get ?: js_undefined()', '*desc->get ? *desc->get : js_undefined()') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\ObjectPrototype.cpp
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\ObjectPrototype.cpp).replace('*desc->get ?: js_undefined()', '*desc->get ? *desc->get : js_undefined()') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\ObjectPrototype.cpp
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\ObjectPrototype.cpp).replace('*desc->set ?: js_undefined()', '*desc->set ? *desc->set : js_undefined()') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\ObjectPrototype.cpp

(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\FunctionObject.h).replace('{ VERIFY_NOT_REACHED(); }', '{ VERIFY_NOT_REACHED(); return {}; }') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\FunctionObject.h

(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\ModuleEnvironment.cpp).replace('    VERIFY_NOT_REACHED();', '    VERIFY_NOT_REACHED(); return false;') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\ModuleEnvironment.cpp
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\NativeFunction.cpp).replace('    VERIFY_NOT_REACHED();', '    VERIFY_NOT_REACHED(); return {};') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\NativeFunction.cpp
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\ObjectEnvironment.cpp).replace('    VERIFY_NOT_REACHED();', '    VERIFY_NOT_REACHED(); return {};') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\ObjectEnvironment.cpp
(Get-Content .\..\serenity\Userland\Libraries\LibJS\CyclicModule.cpp).replace('    VERIFY_NOT_REACHED();', '    VERIFY_NOT_REACHED(); return {};') | Set-Content .\..\serenity\Userland\Libraries\LibJS\CyclicModule.cpp

(Get-Content .\..\serenity\Userland\Libraries\LibJS\Token.h).replace('(Empty) -> StringView { VERIFY_NOT_REACHED(); }', '(Empty) { VERIFY_NOT_REACHED(); return StringView {}; }') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Token.h
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Token.h).replace('(Empty) -> FlyString { VERIFY_NOT_REACHED(); }', '(Empty) { VERIFY_NOT_REACHED(); return FlyString {}; }') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Token.h
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\WeakRef.cpp).replace('(Empty) -> bool { VERIFY_NOT_REACHED(); }', '(Empty) { VERIFY_NOT_REACHED(); return false; }') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\WeakRef.cpp
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\VM.cpp).replace('(Empty) -> ThrowCompletionOr<PropertyKey> { VERIFY_NOT_REACHED(); }', '(Empty) -> ThrowCompletionOr<PropertyKey> { VERIFY_NOT_REACHED(); return NULL; }') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\VM.cpp

(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h).replace('#define __TRY_OR_REJECT', '#define __TRY_OR_REJECT_BAK') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h).replace('#define TRY_OR_REJECT_WITH_VALUE', '#define TRY_OR_REJECT_WITH_VALUE_BAK') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h

(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\NumberConstructor.cpp).replace('#ifdef __clang__', '#if defined(__clang__) || defined(AK_OS_WINRT)') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\NumberConstructor.cpp

(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\Intl\DurationFormat.h).replace('static constexpr AK::Array<', 'static AK::Array<') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\Intl\DurationFormat.h

(Get-Content .\..\serenity\Userland\Libraries\LibJS\Bytecode\Register.h).replace('constexpr static u32 a', 'Register() {} constexpr static u32 a') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Bytecode\Register.h
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\Reference.h).replace('Reference() = default;', 'Reference() {}') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\Reference.h

(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\Completion.h).replace('requires(IsSame<ValueType, Empty>)', '') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\Completion.h
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\Completion.h).replace('    : m_value(Empty {})', '') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\Completion.h

# AST.cpp
$ast_cpp = Get-Content -Path .\..\serenity\Userland\Libraries\LibJS\AST.cpp
$ast_cpp[490] = '    VERIFY_NOT_REACHED(); return {};'
$ast_cpp[1480] = '    VERIFY_NOT_REACHED(); return {};'
$ast_cpp[1486] = '    VERIFY_NOT_REACHED(); return {};'
$ast_cpp[1486] = '    VERIFY_NOT_REACHED(); return {};'
$ast_cpp[2499] = '    VERIFY_NOT_REACHED(); return {};'
$ast_cpp[2884] = '    VERIFY_NOT_REACHED(); return {};'
$ast_cpp[2968] = '    VERIFY_NOT_REACHED(); return {};'
Set-Content -Path .\..\serenity\Userland\Libraries\LibJS\AST.cpp -Value $ast_cpp

# AST.h
$ast_h = Get-Content -Path .\..\serenity\Userland\Libraries\LibJS\AST.h
$ast_h[570] = '        VERIFY_NOT_REACHED(); return {};'
Set-Content -Path .\..\serenity\Userland\Libraries\LibJS\AST.h -Value $ast_h

# FIXME: These disable functionality
(Get-Content .\..\serenity\Userland\Libraries\LibJS\AST.cpp).replace('initializer = make_handle', '//initializer = make_handle') | Set-Content .\..\serenity\Userland\Libraries\LibJS\AST.cpp
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Parser.h).replace('AK_MAKE_NONCOPYABLE(RulePosition);', '') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Parser.h
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Parser.h).replace('AK_MAKE_NONMOVABLE(RulePosition);', '') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Parser.h

Write-Host " Done!"
