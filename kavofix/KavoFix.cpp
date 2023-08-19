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

void FixServerSide(bool bShouldntRestore)
{
	HMODULE hServer = GetModuleHandleA("server.dll");

	if (hServer)
	{
		char chValue[500];
		memcpy(chValue, ((void*)((uintptr_t)hServer + 0x3AE660)), sizeof(chValue));

		if (strstr(chValue, (bShouldntRestore ? "%c* %s" : "%c%s:")))
		{
			ZeroMemory(chValue, strlen(chValue));
			strcat(chValue, (bShouldntRestore ? "%c%s:" : "%c* %s"));

			DWORD dwOldProtect = NULL;
			VirtualProtect(((void*)((uintptr_t)hServer + 0x3AE660)), 7, PAGE_EXECUTE_READWRITE, &dwOldProtect);

			ZeroMemory(((void*)((uintptr_t)hServer + 0x3AE660)), 7);

			memcpy(((void*)((uintptr_t)hServer + 0x3AE660)), chValue, strlen(chValue));
			VirtualProtect(((void*)((uintptr_t)hServer + 0x3AE660)), 7, dwOldProtect, &dwOldProtect);
		}
	}
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
	{
		FixServerSide(kf_fixserverside.GetBool());

		if (kf_fixtype.GetInt() <= 0
			|| kf_fixserverside.GetBool())
		{
			(
				(strStr[(strStr[3] != 95 ? 4 : 9)] != 34 && strStr[strStr.length() - 1] != 34)
				? strStr.insert((strStr[3] != 95 ? 4 : 9), "\"/me ").append("\"")
				: strStr.insert((strStr[3] != 95 ? 5 : 10), "/me ")
			);
		}
		else
			strStr.insert((strStr.find_last_of(34)), (strlen(kf_addchar.GetString()) > 0 ? kf_addchar.GetString() : "`"));

		for (int i = (strStr.find(34) + (kf_fixtype.GetInt() <= 0 || kf_fixserverside.GetBool() ? 5 : 1)); i < strStr.find_last_of(34); i++)
		{
			if (strStr[i] != 32)
			{
				strStr.erase((strStr.find(34) + (kf_fixtype.GetInt() <= 0 || kf_fixserverside.GetBool() ? 5 : 1)), (i - (strStr.find(34) + (kf_fixtype.GetInt() <= 0 || kf_fixserverside.GetBool() ? 5 : 1))));
				break;
			}
		}

		if (IsWhiteSpace(strStr, (strStr[3] != 95 ? 9 : 14), strStr.length() - 1) == 1)
			goto Skip;

		if (!kf_putalways.GetBool())
		{
			for (int i = (strlen(kf_addchar.GetString()) > 0 && kf_fixtype.GetInt() >= 1 && !kf_fixserverside.GetBool()
				? (strStr[3] != 95 ? 5 : 12) 
				: (strlen(kf_addchar.GetString()) <= 0 && kf_fixtype.GetInt() >= 1 && !kf_fixserverside.GetBool()
					? (strStr[3] != 95 ? 5 : 12) 
					: (strStr[3] != 95 ? 9 : 14))); i < (strlen(kf_addchar.GetString()) > 0 && kf_fixtype.GetInt() >= 1 && !kf_fixserverside.GetBool()
				? strStr.length() - strlen(kf_addchar.GetString()) - 1 
				: (strlen(kf_addchar.GetString()) <= 0 && kf_fixtype.GetInt() >= 1 && !kf_fixserverside.GetBool()
					? strStr.length() - 2 
					: strStr.length() - 1)); i++)
			{
				if (strStr[i] == 32)
					continue;

				if (strStr[i] > 0 && strStr[i] < 256)
					goto Skip;
			}
		}

		memcpy(((void*)((uintptr_t)pStr + 0x178)), strStr.c_str(), strStr.length());
		memset(((void*)((uintptr_t)pStr + 0x178 + strStr.length())), 0, 1);
	}

Skip:
	return OrigUnknownFunc();
}