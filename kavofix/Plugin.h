#pragma once

//-----------------------------------------------------------------------------
// KavoFix Plugin
//-----------------------------------------------------------------------------

class CKavoFixPlugin : public IClientPlugin
{
public:
	virtual api_version_t GetAPIVersion(void);
	virtual bool Load(CreateInterfaceFn pfnSvenModFactory, ISvenModAPI* pSvenModAPI, IPluginHelpers* pPluginHelpers);
	virtual void PostLoad(bool bGlobalLoad);
	virtual void Unload(void);
	virtual bool Pause(void);
	virtual void Unpause(void);
	virtual void OnFirstClientdataReceived(client_data_t* pcldata, float flTime);
	virtual void OnBeginLoading(void);
	virtual void OnEndLoading(void);
	virtual void OnDisconnect(void);
	virtual void GameFrame(client_state_t state, double frametime, bool bPostRunCmd);
	virtual void Draw(void);
	virtual void DrawHUD(float time, int intermission);
	virtual const char* GetName(void);
	virtual const char* GetAuthor(void);
	virtual const char* GetVersion(void);
	virtual const char* GetDescription(void);
	virtual const char* GetURL(void);
	virtual const char* GetDate(void);
	virtual const char* GetLogTag(void);
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

extern CKavoFixPlugin g_KavoFixPlugin;