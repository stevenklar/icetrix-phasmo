#pragma once
#include "Icetrix/Application.h"
#include "Icetrix/Events.h"
#include <pch.h>
#include <Windows.h>
#include <codecvt>
#include <appdata/helpers.h>
#include <appdata/pch-il2cpp.h>
#include "Utility.h"
#include "Game.h"

using namespace app;

class GameVersion
{
private:
	app::String* gameVersion = nullptr;
public:
	GameVersion()
	{
		g_sApp.dispatcher.sink<Icetrix::Layer::MenuDrawEvent>().connect<&GameVersion::Render>(*this);
		g_sApp.dispatcher.sink<Icetrix::LayerEvent::Attach>().connect<&GameVersion::AttachHook>(*this);
		g_sApp.dispatcher.sink<Icetrix::LayerEvent::Detach>().connect<&GameVersion::DetachHook>(*this);
		g_sApp.dispatcher.sink<Phasmo::Event::ServerSettingsUpdate>().connect<&GameVersion::ServerSettingsUpdate>(*this);
	}

	void AttachHook()
	{
		if (!checkStatus("Initialize", MH_Initialize()))
			return;

		FuncHook(PhotonNetwork_get_PhotonServerSettings);
	}

	void DetachHook()
	{
		DeFuncHook(PhotonNetwork_get_PhotonServerSettings);
	}

	//"signature": "ServerSettings * PhotonNetwork_get_PhotonServerSettings(MethodInfo * method)",
	HOOK_DEF(app::ServerSettings*, PhotonNetwork_get_PhotonServerSettings, (MethodInfo* method))
	{
		app::ServerSettings* serverSettings = oPhotonNetwork_get_PhotonServerSettings(method);
		g_sApp.dispatcher.trigger<Phasmo::Event::ServerSettingsUpdate>(serverSettings);
		return serverSettings;
	}

	void ServerSettingsUpdate(Phasmo::Event::ServerSettingsUpdate e)
	{
		auto appSettings = e.serverSettings->fields.AppSettings;
		if (!appSettings)
			return;
		gameVersion = appSettings->fields.AppVersion;
	}

	void Render()
	{
		const std::string buildVersion = "0.176.39 - Main";

		if (!g_sFeatures->Get("Watermark")->enabled)
			return;

		if (!gameVersion)
			return;

		std::string sGameVersion = GetUTF8StringFromNETString(gameVersion);
		ImColor color = (sGameVersion == buildVersion) ? ImColor(0, 255, 0) : ImColor(255, 0, 0);

		g_sRenderer->BeginScene();
		g_sRenderer->RenderSimpleText("GameVersion: " + sGameVersion, { 10.f, 30.f }, 15.f, color);
		g_sRenderer->EndScene();
	}

private:
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10FFFF, std::codecvt_mode::little_endian>, char16_t> UTF16_TO_UTF8;
	std::string GetUTF8StringFromNETString(app::String* netString)
	{
		if (netString == NULL)
			return NULL;

		uint16_t* buffer = new uint16_t[netString->fields.m_stringLength + 1];
		memcpy(buffer, &netString->fields.m_firstChar, netString->fields.m_stringLength * sizeof(uint16_t));
		buffer[netString->fields.m_stringLength] = L'\0';
		std::string newString = UTF16_TO_UTF8.to_bytes((const char16_t*)buffer);

		delete[] buffer;

		return newString;
	}
};
