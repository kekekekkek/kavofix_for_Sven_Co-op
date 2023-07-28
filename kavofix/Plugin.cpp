#include "Include.h"

CKavoFixPlugin g_KavoFixPlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CKavoFixPlugin, IClientPlugin, CLIENT_PLUGIN_INTERFACE_VERSION, g_KavoFixPlugin);

api_version_s CKavoFixPlugin::GetAPIVersion()
{
	return SVENMOD_API_VER;
}

bool CKavoFixPlugin::Load(CreateInterfaceFn pfnSvenModFactory, ISvenModAPI* pSvenModAPI, IPluginHelpers* pPluginHelpers)
{
	BindApiToGlobals(pSvenModAPI);
	return true;
}

void CKavoFixPlugin::PostLoad(bool bGlobalLoad)
{
	g_pDetoursAPI->DetourFunction(((void*)((uintptr_t)GetModuleHandleA("hw.dll") + 0x6D580)), (void*)UnknownFuncHook, GET_FUNC_PTR(OrigUnknownFunc));
}

void CKavoFixPlugin::Unload(void)
{

}

bool CKavoFixPlugin::Pause(void)
{
	return true;
}

void CKavoFixPlugin::Unpause(void)
{

}

void CKavoFixPlugin::OnFirstClientdataReceived(client_data_t* pcldata, float flTime)
{

}

void CKavoFixPlugin::OnBeginLoading(void)
{

}

void CKavoFixPlugin::OnEndLoading(void)
{

}

void CKavoFixPlugin::OnDisconnect(void)
{

}

void CKavoFixPlugin::GameFrame(client_state_t state, double frametime, bool bPostRunCmd)
{
	if (bPostRunCmd)
	{

	}
	else
	{

	}
}

void CKavoFixPlugin::Draw(void)
{

}

void CKavoFixPlugin::DrawHUD(float time, int intermission)
{

}

const char* CKavoFixPlugin::GetName(void)
{
	return "KavoFix";
}

const char* CKavoFixPlugin::GetAuthor(void)
{
	return "kek";
}

const char* CKavoFixPlugin::GetVersion(void)
{
	return "0.1";
}

const char* CKavoFixPlugin::GetDescription(void)
{
	return "Allows you to write cyrillic messages without any problems.";
}

const char* CKavoFixPlugin::GetURL(void)
{
	return "https://github.com/kekekekkek";
}

const char* CKavoFixPlugin::GetDate(void)
{
	return SVENMOD_BUILD_TIMESTAMP;
}

const char* CKavoFixPlugin::GetLogTag(void)
{
	return "KAVOFIX";
}