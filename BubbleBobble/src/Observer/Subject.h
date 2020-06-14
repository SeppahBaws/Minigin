#pragma once


enum class Event;
class Observer;

namespace dae
{
	class GameObject;
}

class Subject
{
public:
	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

protected:
	void Notify(const dae::GameObject& object, Event event);

private:
	std::vector<Observer*> m_pObservers;
};
