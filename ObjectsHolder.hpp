#pragma once

#include "GameObject.hpp"
#include <vector>

class ObjectsHolder {
public:
	ObjectsHolder();
	~ObjectsHolder();
	void AddObject(GameObject* object);
	void RemoveObject(GameObject* object);

protected:
	std::vector<GameObject*>* objects;
};
