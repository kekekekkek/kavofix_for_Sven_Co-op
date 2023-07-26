#include "Include.h"

typedef void (*UnknownFuncFn)();
UnknownFuncFn OrigUnknownFunc;

void UnknownFuncHook()
{
	char chText[500];
	char* chInsert = NULL;

	uintptr_t uCommand = ((uintptr_t)GetModuleHandleA("hw.dll") + 0xFEDA88);
	memcpy(chText, (void*)uCommand, sizeof(chText));

	char chIntermediate[500];
	ZeroMemory(chIntermediate, sizeof(chIntermediate));

	if (strstr(chText, "say") && chText[0] == 's')
	{
		if (strlen(chText) == (chText[3] != '_' ? 6 : 11))
			goto Skip;

		for (int i = (chText[3] != '_' ? 5 : 10); i < strlen(chText); i++)
		{
			if (chText[i] == '"')
			{
				chText[(chText[3] != '_' ? 4 : 9)] = 0;
				break;
			}

			chIntermediate[i - (chText[3] != '_' ? 5 : 10)] = chText[i];
		}

		chInsert = strcat(strcat(chText, "/me "), chIntermediate);

		for (int i = 0; i < strlen(chIntermediate); i++)
		{
			if (chIntermediate[i] == 32)
				continue;

			if (chIntermediate[i] > 0 && chIntermediate[i] < 256)
				goto Skip;
		}

		for (int i = 0; i < strlen(chInsert); i++)
			memset((void*)(uCommand + i), (int)chInsert[i], 1);

		memset((void*)(uCommand + strlen(chInsert)), 0, 1);
	}

Skip:
	return OrigUnknownFunc();
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH)
	{
		uintptr_t uInstruct = ((uintptr_t)GetModuleHandleA("hw.dll") + 0x3C12F);
		OrigUnknownFunc = (UnknownFuncFn)TrampHook32((char*)uInstruct, (char*)UnknownFuncHook, 5);
	}

	return TRUE;
}