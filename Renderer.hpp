#pragma once

#include <cstdint>
#include <vector>
#include <list>
#include "ObjectsHolder.hpp"

class Renderer : public ObjectsHolder {
public:
	Renderer(uint32_t* buffer, uint32_t width, uint32_t height);
	void Update();

private:
	uint32_t* buffer;
	uint32_t width;
	uint32_t height;
};
