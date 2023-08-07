#include "Include.h"

UnknownFuncFn OrigUnknownFunc;
DetourHandle_t dhHandle = NULL;

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

string ToLowerCase(string strText)
{
	for (int i = 0; i < strText.length(); i++)
		strText[i] = ((char)tolower(strText[i]));

	return strText;
}

void UnknownFuncHook()
{
	char chStr[500];
	void* pStr = NULL;
	string strStr = "";

	memcpy(&pStr, ((void*)((uintptr_t)GetModuleHandleA("hw.dll") + 0x00FE9E14)), sizeof(void*));
	memcpy(chStr, ((void*)((uintptr_t)pStr + 0x178)), sizeof(chStr));

	strStr = string(chStr);

	if (!kavofix.GetBool())
		goto Skip;

	if (strstr(ToLowerCase(strStr).c_str(), "say"))
	(
		(strStr[(strStr[3] != 95 ? 4 : 9)] != 34 && strStr[strStr.length() - 1] != 34)
		? strStr.insert((strStr[3] != 95 ? 4 : 9), "\"/me ").append("\"")
		: strStr.insert((strStr[3] != 95 ? 5 : 10), "/me ")
	);

	for (int i = (strStr.find(34) + 5); i < strStr.find_last_of(34); i++)
	{
		if (strStr[i] != 32)
		{
			strStr.erase((strStr.find(34) + 5), (i - (strStr.find(34) + 5)));
			break;
		}
	}

	if (IsWhiteSpace(strStr, (strStr[3] != 95 ? 10 : 17), strStr.length() - 1) == 1)
		goto Skip;

	if (!kf_putalways.GetBool())
	{
		for (int i = (strStr[3] != 95 ? 10 : 17); i < strStr.length() - 1; i++)
		{
			if (strStr[i] == 32)
				continue;

			if (strStr[i] > 0 && strStr[i] < 256)
				goto Skip;
		}
	}

	memcpy(((void*)((uintptr_t)pStr + 0x178)), strStr.c_str(), strStr.length());
	memset(((void*)((uintptr_t)pStr + 0x178 + strStr.length())), 0, 1);

Skip:
	return OrigUnknownFunc();
}