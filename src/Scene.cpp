#include "Scene.h"

#include <algorithm>

#include "DisplayObject.h"

Scene::Scene()
= default;

Scene::~Scene()
{
	removeAllChildren();
}


void Scene::addChild(DisplayObject * child, DrawLayers layer_index, std::optional<uint32_t> order_index)
{
	uint32_t index = 0;
	// If we passed in an order index, override the auto-increment value
	if (order_index.has_value())
	{
		index = order_index.value();
	}
	// If we did not pass in an order index, generate one for them
	else
	{
		index = m_nextLayerIndex++;
	}
	child->setLayerIndex(layer_index, index);
	child->m_pParentScene = this;
	m_displayList.push_back(child);
}

void Scene::addChildAfterUpdate(DisplayObject* child, DrawLayers layer_index, std::optional<uint32_t> order_index)
{
	uint32_t index = 0;
	// If we passed in an order index, override the auto-increment value
	if (order_index.has_value())
	{
		index = order_index.value();
	}
	// If we did not pass in an order index, generate one for them
	else
	{
		index = m_nextLayerIndex++;
	}
	child->setLayerIndex(layer_index, index);
	child->m_pParentScene = this;
	m_addQueueObjects.push_back(child);
}

void Scene::removeChild(DisplayObject * child)
{
	delete child;
	m_displayList.erase(std::remove(m_displayList.begin(), m_displayList.end(), child), m_displayList.end());
}

void Scene::removeChildAfterUpdate(DisplayObject* child)
{
	child->setEnabled(false);
	m_removeQueueObjects.push_back(child);
}

void Scene::removeAllChildren()
{
	for (auto& count : m_displayList)
	{
		delete count;
		count = nullptr;
	}

	m_displayList.clear();
}


int Scene::numberOfChildren() const
{
	return m_displayList.size();
}

bool Scene::sortObjects(DisplayObject * left, DisplayObject * right)
{
	/*
	 * First check if they have the same enabled status, if they have the same enabled status,
	 * we first check to see if they're on the same layer, if they are then we sort by layer order index,
	 * otherwise we simply sort by layer index
	 * If they do not have the same enabled status, one is true and one is false, so if left is true, it gets
	 * sorted first, otherwise right is true and it goes first
	 * This will effectively sort by layer indices, and move disabled elements to the end of the list
	 */
	return
		(left->isEnabled() == right->isEnabled()) ?
		(left->m_layerIndex == right->m_layerIndex ?
			left->m_layerOrderIndex < right->m_layerOrderIndex :
			left->m_layerIndex < right->m_layerIndex) :
		left->isEnabled();
}

void Scene::updateDisplayList()
{
	std::sort(m_displayList.begin(), m_displayList.end(), sortObjects);
	for (auto& display_object : m_displayList)
	{
		if (display_object != nullptr)
		{
			if (!display_object->isEnabled())
				break;
			display_object->update();
		}
	}
	m_removeChildrenInQueue();
	m_addChildInQueue();
}

void Scene::drawDisplayList()
{
	std::sort(m_displayList.begin(), m_displayList.end(), sortObjects);
	for (auto& display_object : m_displayList)
	{
		if (display_object != nullptr)
		{
			if (display_object->isEnabled() && display_object->isVisible())
			{
				display_object->draw();
			}

		}
	}

}

std::vector<DisplayObject*> Scene::getDisplayList() const
{
	return m_displayList;
}


inline void Scene::m_addChildInQueue()
{
	for (auto obj : m_addQueueObjects)
	{
		m_displayList.push_back(obj);
	}
	m_addQueueObjects.clear();
}



void Scene::m_removeChildrenInQueue()
{
	for (auto obj : m_removeQueueObjects)
	{
		delete obj;
		m_displayList.erase(std::remove(m_displayList.begin(), m_displayList.end(), obj), m_displayList.end());
	}
	m_removeQueueObjects.clear();
}