#include "Include.h"

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

void UnknownFuncHook()
{
	char chStr[500];
	void* pStr = NULL;
	string strStr = "";

	if (!kavofix.GetBool())
		goto Skip;

	_asm
	{
		lea edx, [esp]
		mov pStr, edx
	}

	for (int a = 0; a < 4096; a += 4)
	{
		memcpy(chStr, ((void*)((uintptr_t)pStr + a)), sizeof(chStr));

		if (strstr(chStr, "say"))
		{
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