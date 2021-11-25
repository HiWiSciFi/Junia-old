#ifndef _TRANSFORMCOMPONENT_H
#define _TRANSFORMCOMPONENT_H

#include "Junia/ECS.h"

class TransformComponent : public Component {
public:
	/// @brief the x position
	int x;
	/// @brief the y position
	int y;

	/// @brief initialize with x and y position of 0
	TransformComponent() {
		x = 0;
		y = 0;
	}

	/// @brief initialize with given x and y position
	/// @param _x the x position
	/// @param _y the y position
	TransformComponent(int _x, int _y) {
		x = _x;
		y = _y;
	}

	void onInit() override {
		
	}

	void onUpdate() override {
		x++;
		y++;
	}
};

#endif // _TRANSFORMCOMPONENT_H