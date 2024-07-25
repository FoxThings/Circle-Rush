#pragma once

#include <list>
#include "ObjectsHolder.hpp"

class Simulation : public ObjectsHolder {
public:
	void Update();
	GameObject* GetObjectByCollider(BoxCollider* collider);
};
