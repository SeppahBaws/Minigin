#pragma once
#include "BaseComponent.h"
#include "RigidBodyComponent.h"
#include "Texture2D.h"

class StretchedTextureRenderer : public dae::BaseComponent
{
public:
	StretchedTextureRenderer(const std::string& texture);
	virtual ~StretchedTextureRenderer();

	void OnPrepare() override;
	void OnRender() override;

private:
	dae::RigidBodyComponent* m_pRB = nullptr;

	dae::Texture2D* m_pTexture;
};
