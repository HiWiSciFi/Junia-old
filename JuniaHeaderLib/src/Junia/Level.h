#ifndef _LEVEL_H
#define _LEVEL_H

#include "ECS/ECS.h"
#include <list>

class Level {
public:
	~Level() { while (!entities.empty()) delete entities.front(), entities.pop_front(); }

	/// @brief load a certain level
	/// @param level the level to be loaded
	static void loadLevel(Level* level) {  }

	/// @brief create an entity in the level
	/// @return a pointer to the created entity
	Entity* createEntity() {
		Entity* e = new Entity();
		entities.push_back(e);
		return e;
	}

	/// @brief called by the engine to load the level
	void load() { this->onLoad(); }
	/// @brief called by the engine to unload the level
	void unload() { this->onUnload(); }

	/// @brief override to catch the load event
	virtual void onLoad() {  }
	/// @brief override to catch the unload event
	virtual void onUnload() {  }

	void update() { for (Entity*& e : entities) e->update(); }
	void draw() { for (Entity*& e : entities) e->draw(); }

private:
	/// @brief the entities in the level
	std::list<Entity*> entities;
};

#endif // _LEVEL_H