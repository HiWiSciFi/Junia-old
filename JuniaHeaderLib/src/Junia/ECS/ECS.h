#ifndef _ECS_H
#define _ECS_H

class Entity;
#include <list>
#include <typeinfo>


class Component {
public:
	/// @brief the entity this component is attached to
	Entity* entity = nullptr;
	/// @brief if this component is enabled (if functions are called on this component)
	bool enabled = true;

	/// @brief override to catch the initialization event
	virtual void onInit() {  }
	/// @brief override to catch the update event
	virtual void onUpdate() {  }
	/// @brief override to catch the draw event
	virtual void onDraw() {  }

	/// @brief called by the engine on initialization
	void init() { this->onInit(); }
	/// @brief called by the engine on update
	void update() { this->onUpdate(); }
	/// @brief called by the engine on draw
	void draw() { this->onDraw(); }

};


class Entity {
public:
	~Entity() {  }

	/// @brief create a component and attach it to this entity
	/// @tparam T the type of the component to add
	/// @tparam ...TArgs the type of the arguments to pass to the component constructor
	/// @param ...args the arguments to pass to the component constructor
	/// @return if there is no attached component of this type it will create one and otherwise a pointer to the component that already exists
	template <typename T, typename... TArgs>
	T* addComponent(TArgs... args) {

		auto tid = typeid(T).raw_name();
		for (Component*& c : components) {
			if (tid == typeid(*(c)).raw_name()) {
				return dynamic_cast<T*>(c);
			}
		}

		T* c = new T(std::forward<TArgs>(args)...);
		c->entity = this;
		components.push_back(c);
		c->init();
		return c;
	}

	/// @brief get an attached component of a certain type
	/// @tparam T the type of the component to find
	/// @tparam ...TArgs the type of the arguments to pass to the constructor of the component in case there is no component of the type already attached
	/// @param ...defaultArgs the arguments to pass to the constructor of the component in case there is no component of the type already attached
	/// @return the attached component of the given type
	template <typename T, typename... TArgs>
	T* getComponent(TArgs... defaultArgs) {
		return addComponent<T>(std::forward<TArgs>(defaultArgs)...);
	}

	/// @brief require a component to exist on this entity
	/// @tparam T the type of the component that has to exist
	/// @tparam ...TArgs the type of the arguments to pass to the constructor of the component in case there is no component of the type already attached
	/// @param ...defaultArgs the arguments to pass to the constructor of the component in case there is no component of the type already attached
	/// @return the attached component of the given type
	template <typename T, typename... TArgs>
	T* requireComponent(TArgs... defaultArgs) {
		return getComponent<T>(std::forward<TArgs>(defaultArgs)...);
	}

	/// @brief check if the entity has a component of a given type attached
	/// @tparam T the type of the component to find
	/// @return true, if a component of the type is attached, false if not
	template <typename T>
	bool hasComponent() {
		auto tid = typeid(T).raw_name();
		for (Component*& c : components) {
			if (tid == typeid(*(c)).raw_name()) {
				return true;
			}
		}
		return false;
	}

	/// @brief called by the engine on update
	void update() { for (Component*& c : components) c->update(); }
	/// @brief called by the engine on draw
	void draw() { for (Component*& c : components) c->draw(); }

private:
	/// @brief a list of the attached components
	std::list<Component*> components;
};

#endif // _ECS_H