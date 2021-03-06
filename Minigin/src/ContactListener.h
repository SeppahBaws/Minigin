﻿#pragma once

#include <box2d/box2d.h>

namespace dae
{
	class ContactListener final : public b2ContactListener
	{
	public:
		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;

		void SetCleanup(bool isCleanup)
		{
			m_IsCleanup = isCleanup;
		}

	private:
		bool m_IsCleanup = false;
	};
}
