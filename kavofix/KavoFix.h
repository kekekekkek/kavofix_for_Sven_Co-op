#pragma once

//no need to clean stack
typedef void (*UnknownFuncFn)();
extern UnknownFuncFn OrigUnknownFunc;

extern void UnknownFuncHook();
extern DetourHandle_t dhHandle;