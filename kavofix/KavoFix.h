#pragma once

//no need to clean stack
typedef void (*UnknownFuncFn)();
extern UnknownFuncFn OrigUnknownFunc;

typedef void (*OutputDebugStringFn)(const char* cchMsg);
extern OutputDebugStringFn OrigOutputDbgStr;

extern void UnknownFuncHook();
extern void OutputDebugStringHook(const char* cchMsg);

extern DetourHandle_t dhUnkFunc;
extern DetourHandle_t dhOutputDbgStr;

extern bool bKavoFix_ServerPlugin;