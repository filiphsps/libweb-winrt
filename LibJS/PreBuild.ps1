$curDir = Get-Location

Set-Location .\..\serenity
git reset --hard
Set-Location $curDir

(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h).replace('    ({', '    ([&]{') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h
(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h).replace('    })', '    }())') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h
# (Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h).replace('        _temporary', '        return _temporary') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h
