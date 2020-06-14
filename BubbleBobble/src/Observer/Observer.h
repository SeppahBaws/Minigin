#pragma once

enum class Event;

namespace dae
{
	class GameObject;
}

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void OnNotify(const dae::GameObject& object, Event event) = 0;
};
