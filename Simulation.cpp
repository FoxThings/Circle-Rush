#include "Simulation.hpp"
#include <functional>

void Simulation::Update()
{
	std::vector<std::function<void()>> procedures = std::vector<std::function<void()>>();

	// So stupid physic simulation :)
	for (size_t i = 0; i < objects->size(); ++i) {
		for (size_t j = i + 1; j < objects->size() - 1; ++j) {
			GameObject* first = objects->at(i);
			GameObject* second = objects->at(j);

			Vector2D firstSize = first->collider.size;
			Vector2D secondSize = second->collider.size;

			// Center pivot coordinate system to UpLeftCorner
			Vector2D firstPostion = first->position - firstSize * 0.5;
			Vector2D secondsPostion = second->position - secondSize * 0.5;

			if (
				firstPostion.x < secondsPostion.x + secondSize.x &&
				firstPostion.x + firstSize.x > secondsPostion.x &&
				firstPostion.y < secondsPostion.y + secondSize.y &&
				firstPostion.y + firstSize.y > secondsPostion.y
				) {
				procedures.push_back(
					[first, second]() {
					if (first->collider.callback != nullptr) {
						first->collider.callback(&first->collider, &second->collider);
					}
					if (second->collider.callback != nullptr) {
						second->collider.callback(&second->collider, &first->collider);
					}
				});
			}
		}
	}

	for (size_t i = 0; i < procedures.size(); ++i) {
		procedures[i]();
	}
}

GameObject* Simulation::GetObjectByCollider(BoxCollider* collider)
{
	for (size_t i = 0; i < objects->size(); ++i) {
		if (&(objects->at(i)->collider) == collider) {
			return objects->at(i);
		}
	}

	return nullptr;
}
