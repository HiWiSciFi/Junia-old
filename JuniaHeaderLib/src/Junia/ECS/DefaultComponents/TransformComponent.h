#ifndef _TRANSFORMCOMPONENT_H
#define _TRANSFORMCOMPONENT_H

#include "../ECS.h"

class TransformComponent : public Component {
public:
	/// @brief the x position
	int x;
	/// @brief the y position
	int y;

	int xscale;
	int yscale;

	/// @brief initialize with x and y position of 0
	TransformComponent() {
		x = 0;
		y = 0;
		xscale = 1;
		yscale = 1;
	}

	/// @brief initialize with given x and y position
	/// @param _x the x position
	/// @param _y the y position
	TransformComponent(int _x, int _y) {
		x = _x;
		y = _y;
		xscale = 1;
		yscale = 1;
	}
};

#endif // _TRANSFORMCOMPONENT_H