#pragma once
#ifndef __SCENE__
#define __SCENE__

#include <vector>
#include <optional>
#include "GameObject.h"


class Scene : public GameObject
{
public:
	friend class DisplayObject;
	Scene();
	virtual ~Scene();

	// Inherited via GameObject
	virtual void draw() override = 0;
	virtual void update() override = 0;
	virtual void clean() override = 0;
	virtual void handleEvents() = 0;
	virtual void start() = 0;

	void addChild(DisplayObject* child, uint32_t layer_index = 0, std::optional<uint32_t> order_index = std::nullopt);
	void addChildAfterUpdate(DisplayObject* child, uint32_t layer_index = 0, std::optional<uint32_t> order_index = std::nullopt);
	void removeChild(DisplayObject* child);
	void removeChildAfterUpdate(DisplayObject* child);

	void removeAllChildren();
	int numberOfChildren() const;

	void updateDisplayList();
	void drawDisplayList();

	std::vector<DisplayObject*> getDisplayList() const;

private:
	uint32_t m_nextLayerIndex = 0;
	std::vector<DisplayObject*> m_displayList;
	std::vector<DisplayObject*> m_addQueueObjects;
	std::vector<DisplayObject*> m_removeQueueObjects;

	static bool sortObjects(DisplayObject* left, DisplayObject* right);
	void m_addChildInQueue();
	void m_removeChildrenInQueue();
};

#endif /* defined (__SCENE__) */
