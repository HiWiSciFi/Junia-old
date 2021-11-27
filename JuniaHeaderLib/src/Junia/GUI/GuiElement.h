#ifndef _GUIELEMENT_H
#define _GUIELEMENT_H

class GuiElement {
public:
	GuiElement* parent = nullptr;

	virtual ~GuiElement() {  }

	/// @brief override to catch initialization event
	virtual void onInit() {  }
	/// @brief override to catch update event
	virtual void onUpdate() {  }
	/// @brief override to catch draw event
	virtual void onDraw(SDL_Renderer* renderer) {  }

	/// @brief set the parent of this GuiElement
	/// @param _parent a pointer to the parent GuiElement
	void setParent(GuiElement* _parent) { parent = _parent; }

	/// @brief called by the engine on initialization
	void init() { onInit(); }
	/// @brief called by the engine on update
	void update() { onUpdate(); }
	/// @brief called by the engine on draw
	void draw(SDL_Renderer* renderer) { onDraw(renderer); }
};

#endif // _GUIELEMENT_H