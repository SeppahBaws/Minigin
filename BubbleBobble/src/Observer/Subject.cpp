#include "pch.h"
#include "Subject.h"

#include "Observer.h"

void Subject::AddObserver(Observer* observer)
{
	m_pObservers.push_back(observer);
}

void Subject::RemoveObserver(Observer* observer)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), observer), m_pObservers.end());
}

void Subject::Notify(const dae::GameObject& object, Event event)
{
	for (Observer* observer : m_pObservers)
	{
		observer->OnNotify(object, event);
	}
}
