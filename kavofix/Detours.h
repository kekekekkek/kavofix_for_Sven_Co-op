#pragma once

extern bool Detour32(char* src, char* dst, const intptr_t len);
extern char* TrampHook32(char* src, char* dst, const intptr_t len);