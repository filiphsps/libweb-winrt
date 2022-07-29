(Get-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h).replace('    ({', '    (try{') | Set-Content .\..\serenity\Userland\Libraries\LibJS\Runtime\PromiseReaction.h
