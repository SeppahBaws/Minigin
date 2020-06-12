#pragma once
#include "Singleton.h"

namespace dae
{
	struct WindowSettings
	{
		int width = 640;
		int height = 480;
		std::string title = "";
		bool resizable = false;
	};

	struct EngineSettings
	{
		bool debug = false;
		std::string resourcesLocation = "";
	};

	class SettingsManager final : public Singleton<SettingsManager>
	{
	public:
		void LoadSettings(const std::string& settingsFile);

		WindowSettings GetWindowSettings() const;
		EngineSettings GetEngineSettings() const;

	private:
		WindowSettings m_WindowSettings;
		EngineSettings m_EngineSettings;
	};
}
