# kavofix_for_Sven_Co-op
### English
After one year, i decided to come back again to try and fix this shit. Thanks to my friend who accidentally stumbled upon one thing that became a great hint for me :D

This fix is similar to this guide i wrote exactly a year ago: https://steamcommunity.com/sharedfiles/filedetails/?id=2844186040. It also has some of its older features.
You can translate this if you want. But now i have redone some things, and this is what i expected to see originally.

You can switch the branch and use this module as a plugin for SvenMod, or inject the module separately.<br><br>
You can read instruction about SvenMod plugins here: https://github.com/sw1ft747/svenmod<br>
Maybe this fix can be made much easier, but at the moment it works as it should xd

P.S: Also, you can create a `.cfg` file in which you can store settings for console variables of this plugin.

### Russian
Спустя год, я снова решил вернуться, чтобы попытаться исправить эту поебень. Спасибо моему другу, который случайно обнаружил одну вещь, которая стала для меня большой подсказкой :D

Этот фикс похож на тот, который я делал ранее, о котором Вы сможете прочитать здесь: https://steamcommunity.com/sharedfiles/filedetails/?id=2844186040. 

А также, он обладает некоторыми его старыми особенностями. Но, теперь он более менее похож на то, чего я пытался добиться изначально, а именно корректное отображение кириллических сообщений в чате игры без указания дополнительных латинских символов.

Также, Вы можете переключить ветку и использовать этот модуль в качестве плагина для SvenMod, или же инжектить оригинал отдельно, на Ваше усмотрение.<br><br>
Подробную инструкцию с работой SvenMod и его плагинов Вы сможете прочитать тут: https://github.com/sw1ft747/svenmod<br><br>
P.S: И да, пж извините за мой английский, ибо я слишком тупой и ленивый чтобы выучить его нормально. Также, Вы можете создать файл с расширением `.cfg`, где Вы сможете хранить настройки консольных переменных данного плагина.

### Usage
| Console Variable | Default Value | Type | Description |
| ---------------- | ------------- | ---- | ----------- |
| kavofix | 1 | bool | Allows you to enable or disable this plugin. |
| kf_fixtype | 0 | int | Allows you to select fix type. |
| kf_putalways | 0 | bool | Always put the word `/me`/specified character at the begin/end of the message? |
| kf_addchar | "`" | string | Adds the specified character to the end of the message depending on \"kf_fixtype\". |
| kf_fixserverside | 1 | bool | Allows you to write in cyrillic on a local server without any problems. |

`kf_fixserverside` only works when you write `/me` before the message.

### Compile
Release/x86

### Screenshots
* FixType=0<br><br>
![FixType0](https://github.com/kekekekkek/kavofix_for_Sven_Co-op/blob/svenmod/img/Screenshot_1.png)

* FixType=1<br><br>
![FixType1](https://github.com/kekekekkek/kavofix_for_Sven_Co-op/blob/svenmod/img/Screenshot_2.png)

* ServerSideFix=1<br><br>
![ServerSideFix](https://github.com/kekekekkek/kavofix_for_Sven_Co-op/blob/svenmod/img/Screenshot_3.png)
