#pragma once

#include <cstdint>
#include <vector>
#include <list>
#include "GameObject.hpp"

class Renderer {
public:
	Renderer(uint32_t* buffer, uint32_t width, uint32_t height);
	~Renderer();
	void AddObject(GameObject* object);
	void RemoveObject(GameObject* object);
	void Update();

private:
	uint32_t* buffer;
	uint32_t width;
	uint32_t height;
	std::list<GameObject*>* objects;
};
