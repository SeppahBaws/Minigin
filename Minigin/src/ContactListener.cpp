#include "MiniginPCH.h"
#include "ContactListener.h"
#include "GameObject.h"

namespace dae
{
	void ContactListener::BeginContact(b2Contact* contact)
	{
		if (m_IsCleanup)
			return;

		GameObject* pObjA = static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
		GameObject* pObjB = static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData());

		pObjA->OnCollisionBegin(pObjB);
	}

	void ContactListener::EndContact(b2Contact* contact)
	{
		if (m_IsCleanup)
			return;

		GameObject* pObjA = static_cast<GameObject*>(contact->GetFixtureA()->GetBody()->GetUserData());
		GameObject* pObjB = static_cast<GameObject*>(contact->GetFixtureB()->GetBody()->GetUserData());

		pObjA->OnCollisionEnd(pObjB);
	}
}
