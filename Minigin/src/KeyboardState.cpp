#include "MiniginPCH.h"
#include "KeyboardState.h"

#include "KeyboardInput.h"

namespace dae
{
	void KeyboardState::SetState(uint64_t key, bool pressed)
	{
		if (pressed)
		{
			if (key < KEYS_REGION_2_BEGIN)
			{
				m_LowByte |= uint64_t(1) << (key - KEYS_REGION_1_BEGIN);
			}
			else if (key <= KEYS_REGION_2_END)
			{
				m_HighByte |= uint64_t(1) << (key - KEYS_REGION_2_BEGIN);
			}
			else
			{
				m_HighByte |= uint64_t(1) << (key - KEYS_REGION_3_BEGIN + (KEYS_REGION_2_END - KEYS_REGION_2_BEGIN) + 1);
			}
		}
		else
		{
			if (key < KEYS_REGION_2_BEGIN)
			{
				m_LowByte &= ~(uint64_t(1) << (key - KEYS_REGION_1_BEGIN));
			}
			else if (key <= KEYS_REGION_2_END)
			{
				m_HighByte &= ~(uint64_t(1) << (key - KEYS_REGION_2_BEGIN));
			}
			else
			{
				m_HighByte &= ~(uint64_t(1) << (key - KEYS_REGION_3_BEGIN + (KEYS_REGION_2_END - KEYS_REGION_2_BEGIN) + 1));
			}
		}
	}

	bool KeyboardState::Evaluate(uint64_t key) const
	{
		if (key < KEYS_REGION_2_BEGIN)
		{
			return m_LowByte & (uint64_t(1) << (key - KEYS_REGION_1_BEGIN));
		}
		else if (key <= KEYS_REGION_2_END)
		{
			return m_HighByte & (uint64_t(1) << (key - KEYS_REGION_2_BEGIN));
		}

		return m_HighByte & (uint64_t(1) << (key - KEYS_REGION_3_BEGIN + (KEYS_REGION_2_END - KEYS_REGION_2_BEGIN) + 1));
	}
}
