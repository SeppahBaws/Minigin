#pragma once
#include "BaseComponent.h"
#include "Color.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent final : public BaseComponent
	{
	public:
		TextComponent(const std::string& text = "", const std::string& font = "Lingua.otf",
			unsigned int fontSize = 24, Color color = { 1.0f, 1.0f, 1.0f });
		~TextComponent();
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		void OnUpdate() override;
		void OnRender() override;

		void SetText(const std::string& text);
		void SetFont(const std::string& font);
		void SetSize(unsigned int size);
		void SetColor(const Color& color);

	private:
		void ReloadFont();

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::string m_FontFile;
		unsigned int m_FontSize;
		Color m_Color;
		Font* m_pFont;
		Texture2D* m_pTexture;
	};
}
