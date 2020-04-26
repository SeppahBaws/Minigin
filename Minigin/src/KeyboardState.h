#pragma once

namespace dae
{
	class KeyboardState
	{
	public:
		KeyboardState() = default;

		void SetState(uint64_t key, bool pressed);
		bool Evaluate(uint64_t key) const;

		uint64_t GetLowByte() const { return m_LowByte; }
		uint64_t GetHighByte() const { return m_HighByte; }

	private:
		uint64_t m_LowByte = 0;
		uint64_t m_HighByte = 0;
	};
}
