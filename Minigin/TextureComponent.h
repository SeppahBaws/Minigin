#pragma once
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class TextureComponent final : public BaseComponent
	{
	public:
		TextureComponent();
		virtual ~TextureComponent();
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) noexcept = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) noexcept = delete;

		void SetTexture(const std::string& filename);

		void OnRender() override;

	private:
		Texture2D* m_pTexture = nullptr;
	};
}
