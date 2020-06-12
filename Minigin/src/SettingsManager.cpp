#include "MiniginPCH.h"
#include "SettingsManager.h"

#pragma warning(push)
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#include "INIReader.h"
#pragma warning(pop)

namespace dae
{
	void SettingsManager::LoadSettings(const std::string& settingsFile)
	{
		const INIReader reader(settingsFile);

		if (reader.ParseError() != 0)
		{
			std::cerr << "ERROR: Failed to load settings file!" << std::endl;
			return;
		}

		m_EngineSettings = {};
		m_EngineSettings.debug = reader.GetBoolean("Minigin", "debug", false);
		m_EngineSettings.resourcesLocation = reader.Get("Minigin", "resourcesLocation", "");

		m_WindowSettings = {};
		m_WindowSettings.width = reader.GetInteger("Window", "width", 640);
		m_WindowSettings.height = reader.GetInteger("Window", "height", 480);
		m_WindowSettings.title = reader.Get("Window", "title", "Minigin Game");
		m_WindowSettings.resizable = reader.GetBoolean("Window", "resizable", false);
	}

	WindowSettings SettingsManager::GetWindowSettings() const
	{
		return m_WindowSettings;
	}

	EngineSettings SettingsManager::GetEngineSettings() const
	{
		return m_EngineSettings;
	}
}
