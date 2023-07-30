#include "Include.h"

typedef void (*UnknownFuncFn)();
UnknownFuncFn OrigUnknownFunc;

int IsWhiteSpace(string strText, int iStart, int iEnd)
{
	if (iStart >= iEnd && strText[iEnd] != 34)
		return -1;

	for (int i = iStart; i < iEnd; i++)
	{
		if (strText[i] == 34)
			continue;

		if (strText[i] != 32)
			return 0;
	}

	return 1;
}

char* ToLowerCase(char* chArray)
{
	for (int i = 0; i < strlen(chArray); i++)
		chArray[i] = ((char)tolower(chArray[i]));

	return chArray;
}

void UnknownFuncHook()
{
	char chStr[500];
	void* pStr = NULL;
	string strStr = "";

	_asm
	{
		lea edx, [esp]
		mov pStr, edx
	}

	for (int a = 0; a < 4096; a += 4)
	{
		memcpy(chStr, ((void*)((uintptr_t)pStr + a)), sizeof(chStr));

		if (strstr(ToLowerCase(chStr), "say"))
		{
			if (chStr[(chStr[3] != 95 ? 4 : 9)] != 34 && chStr[strlen(chStr) - 1] != 34)
			{
				strStr = string(chStr).insert((chStr[3] != 95 ? 4 : 9), "\"/me ").append("\"");

				for (int i = (strStr[3] != 95 ? 9 : 14); i < strStr.length(); i++)
				{
					if (strStr[i] != 32)
					{
						strStr.erase((strStr[3] != 95 ? 9 : 14), abs(((strStr[3] != 95 ? 9 : 14) - i)));
						break;
					}
				}
			}
			else
				strStr = string(chStr).insert((chStr[3] != 95 ? 5 : 10), "/me ");

			if (IsWhiteSpace(strStr, (chStr[3] != 95 ? 10 : 17), strStr.length() - 1) == 1)
				goto Skip;

			for (int b = (chStr[3] != 95 ? 10 : 17); b < strStr.length() - 1; b++)
			{
				if (strStr[b] == 32)
					continue;

				if (strStr[b] > 0 && strStr[b] < 256)
					goto Skip;
			}

			for (int b = 0; b < strStr.length(); b++)
				memset(((void*)((uintptr_t)pStr + a + b)), (int)strStr[b], 1);

			memset(((void*)((uintptr_t)pStr + a + strStr.length())), 0, 1);
		}
	}

Skip:
	return OrigUnknownFunc();
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReasonForCall, LPVOID lpReserved)
{
	if (dwReasonForCall == DLL_PROCESS_ATTACH)
	{
		uintptr_t uFunc = ((uintptr_t)GetModuleHandleA("hw.dll") + 0x6D580);
		OrigUnknownFunc = (UnknownFuncFn)TrampHook32((char*)uFunc, (char*)UnknownFuncHook, 6);
	}

	return TRUE;
}