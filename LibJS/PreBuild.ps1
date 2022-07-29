$curDir = Get-Location

Set-Location .\..\serenity
git reset --hard
Set-Location $curDir

(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h).replace('#define __TRY_OR_REJECT', '#define __TRY_OR_REJECT_BAK') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h).replace('#define TRY_OR_REJECT_WITH_VALUE', '#define TRY_OR_REJECT_WITH_VALUE_BAK') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h

#(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h).replace('    ({', '    ([&]{') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h
#(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h).replace('    })', '    }())') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h
