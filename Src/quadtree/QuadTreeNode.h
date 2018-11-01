#ifndef __QUAD_TREE_NODE_H__
#define __QUAD_TREE_NODE_H__

/*
//�Ĳ����ڵ��࣬��ͷ�ڵ�����Ĳ���;
//����ϵ���Ͻ�Ϊԭ�㣬������Ϊx�������������y�����;
//���Ĳ����Ĳ����ǣ�1������ʱ��̬����ڵ��ɾ���ڵ㣬����������
//					2��������������ȫ����ĳ���ڵ�ʱ�Ż�ȡ���޳���
//					3�����������ȫ������������ڵ��ڣ��Ǹ��ڵ�Ҳ�洢����;
*/
#pragma once
#include <list>

// �Ĳ�������ö��;
enum QuadType
{
	ROOT,			// ��;
	UP_RIGHT,		//���ޢ�;
	UP_LEFT,		//���ޢ�;
	BOTTOM_LEFT,	//���ޢ�;
	BOTTOM_RIGHT,	//���ޢ�;
};

// ����T�����г�Ա��{ x, y, width, height }
template <typename T>
class QuadTreeNode
{
public:
	QuadTreeNode(float _x, float _y, float _width, float _height, int _level, int _maxLevel, QuadType _quadType, QuadTreeNode* _parent);
	~QuadTreeNode();
public:
	void InsertObject(T* object); // �������;
	std::list<T*> GetObjectsAt(float px, float py, float w, float h); // ��ѯ���󣬻��һƬ������Ķ���������ȫ��Χ;
	std::list<T*> GetObjectsAt(float px, float py);
	void RemoveObjectsAt(float px, float py, float w, float h); // ɾ������ɾ��һƬ������Ķ���ͽڵ㣬��ȫ��Χ;

	void GetRect(float* x, float* y, float* width, float* height);
	void GetMaxLevel(int* maxLevel);
private:
	bool IsContain(float px, float py, float w, float h, T* object) const; // �ж�ĳ�������Ƿ����ĳ����;
	bool IsContain(float px, float py, float w, float h, QuadTreeNode<T>* quadTreeNode) const; // �ж�ĳ�������Ƿ����ĳ����;
	bool IsContainPoint(QuadTreeNode<T>* quadTreeNode, float px, float py) const;
private:
	std::list<T*> objects;

	// �����ӽڵ㣬��������;
	QuadTreeNode* parent;
	QuadTreeNode* upRightNode;
	QuadTreeNode* upLeftNode;
	QuadTreeNode* bottomLeftNode;
	QuadTreeNode* bottomRightNode;
	// �ڵ�����;
	QuadType quadType;
	// ����ͳ������ԣ����Ͻ�Ϊê��;
	float x;
	float y;
	float width;
	float height;

	int level;		// ��ǰ���;
	int maxLevel;	// ������;
};

template <typename T>
QuadTreeNode<T>::QuadTreeNode(float _x, float _y, float _width, float _height,
	int _level, int _maxLevel, QuadType _quadType, QuadTreeNode *_parent) :
	quadType(_quadType),
	x(_x),
	y(_y),
	width(_width),
	height(_height),
	level(_level),
	maxLevel(_maxLevel)
{
	parent = _parent;
	upRightNode = NULL;
	upLeftNode = NULL;
	bottomLeftNode = NULL;
	bottomRightNode = NULL;
}


template <typename T>
QuadTreeNode<T>::~QuadTreeNode()
{
	// �������Ҷ�ӽڵ㣬�������ӽڵ�;
	if (upRightNode)
	{
		delete upRightNode;
		upRightNode = NULL;
	}
	if (upLeftNode)
	{
		delete upLeftNode;
		upLeftNode = NULL;
	}
	if (bottomLeftNode)
	{
		delete bottomLeftNode;
		bottomLeftNode = NULL;
	}
	if (bottomRightNode)
	{
		delete bottomRightNode;
		bottomRightNode = NULL;
	}

	parent = NULL;
}

template <typename T>
bool QuadTreeNode<T>::IsContain(float px, float py, float w, float h, T *object) const
{
	if (object->x >= px
		&&object->x + object->width <= px + w
		&&object->y >= py
		&&object->y + object->height <= py + h)
		return true;
	return false;
}


template <typename T>
bool QuadTreeNode<T>::IsContain(float px, float py, float w, float h, QuadTreeNode<T> *quadTreeNode) const
{
	if (quadTreeNode->x >= px
		&&quadTreeNode->x + quadTreeNode->width <= px + w
		&&quadTreeNode->y >= py
		&&quadTreeNode->y + quadTreeNode->height <= py + h)
		return true;
	return false;
}

template <typename T>
bool QuadTreeNode<T>::IsContainPoint(QuadTreeNode<T>* quadTreeNode, float px, float py) const
{
	if (quadTreeNode->x <= px
		&& quadTreeNode->y <= py
		&& quadTreeNode->x + quadTreeNode->width >= px
		&& quadTreeNode->y + quadTreeNode->height >= py)
	{
		return true;
	}
	return false;
}

template <typename T>
void QuadTreeNode<T>::InsertObject(T* object)
{
	// �����Ҷ�ӽڵ㣬�����Ҷ�ӽڵ�;
	if (level == maxLevel)
	{
		objects.push_back(object);
		return;
	}

	// ��Ҷ�ӽڵ㣬����²�ڵ���԰����ö�����ݹ鹹���ӽڵ㲢�������,�߹����߲���;
	if (IsContain(x + width / 2, y, width / 2, height / 2, object))
	{
		if (!upRightNode) // �����ظ��������ǵ�ԭ���Ľڵ�;
			upRightNode = new QuadTreeNode(x + width / 2, y, width / 2, height / 2, level + 1, maxLevel, UP_RIGHT, this);//���û���ӽڵ�ʹ����ӽڵ㣬parent�ڵ��ǵ�ǰ�ڵ�;
		upRightNode->InsertObject(object);
		return;
	}
	else if (IsContain(x, y, width / 2, height / 2, object))
	{
		if (!upLeftNode)
			upLeftNode = new QuadTreeNode(x, y, width / 2, height / 2, level + 1, maxLevel, UP_LEFT, this);
		upLeftNode->InsertObject(object);
		return;
	}
	else if (IsContain(x, y + height / 2, width / 2, height / 2, object))
	{
		if (!bottomLeftNode)
			bottomLeftNode = new QuadTreeNode(x, y + height / 2, width / 2, height / 2, level + 1, maxLevel, BOTTOM_LEFT, this);
		bottomLeftNode->InsertObject(object);
		return;
	}
	else if (IsContain(x + width / 2, y + height / 2, width / 2, height / 2, object))
	{
		if (!bottomRightNode)
			bottomRightNode = new QuadTreeNode(x + width / 2, y + height / 2, width / 2, height / 2, level + 1, maxLevel, BOTTOM_RIGHT, this);
		bottomRightNode->InsertObject(object);
		return;
	}
	// �²�ڵ㲻����ȫ�����ö�������뵽��ǰ��Ҷ�ӽڵ�;
	// ����ж�Ҳ����ʡȥ;
	if (IsContain(x, y, width, height, object))
		objects.push_back(object);
}

template <typename T>
std::list<T*> QuadTreeNode<T>::GetObjectsAt(float px, float py, float w, float h)
{
	std::list<T*> resObjects;
	// �����ǰ�ڵ���ȫ���������ѵ�ǰ�ڵ��Ķ���ŵ��б�ĩβ,������Ҳ��;
	if (IsContain(px, py, w, h, this))
	{
		resObjects.insert(resObjects.end(), objects.begin(), objects.end());
		// ���һ��;
		if (level == maxLevel)
			return resObjects;
	}

	// ������²�ڵ�Ͱ��²�ڵ�����Ķ���ӽ���;
	if (upRightNode)
	{
		std::list<T*> upRightChild;
		upRightChild = upRightNode->GetObjectsAt(px, py, w, h);
		resObjects.insert(resObjects.end(), upRightChild.begin(), upRightChild.end());
	}
	if (upLeftNode)
	{
		std::list<T*> upLeftChild;
		upLeftChild = upLeftNode->GetObjectsAt(px, py, w, h);
		resObjects.insert(resObjects.end(), upLeftChild.begin(), upLeftChild.end());
	}
	if (bottomLeftNode)
	{
		std::list<T*> bottomLeftChild;
		bottomLeftChild = bottomLeftNode->GetObjectsAt(px, py, w, h);
		resObjects.insert(resObjects.end(), bottomLeftChild.begin(), bottomLeftChild.end());
	}
	if (bottomRightNode)
	{
		std::list<T*> bottomRightChild;
		bottomRightChild = bottomRightNode->GetObjectsAt(px, py, w, h);
		resObjects.insert(resObjects.end(), bottomRightChild.begin(), bottomRightChild.end());
	}
	return resObjects;
}

template <typename T>
std::list<T*> QuadTreeNode<T>::GetObjectsAt(float px, float py)
{
	std::list<T*> resObjects;
	if (!IsContainPoint(this, px, py))
	{
		return resObjects;
	}
	resObjects.insert(resObjects.end(), objects.begin(), objects.end());
	// ���һ��;
	if (level == maxLevel)
		return resObjects;

	// ������²�ڵ�Ͱ��²�ڵ�����Ķ���ӽ���;
	if (upRightNode)
	{
		std::list<T*> upRightChild;
		upRightChild = upRightNode->GetObjectsAt(px, py);
		resObjects.insert(resObjects.end(), upRightChild.begin(), upRightChild.end());
	}
	if (upLeftNode)
	{
		std::list<T*> upLeftChild;
		upLeftChild = upLeftNode->GetObjectsAt(px, py);
		resObjects.insert(resObjects.end(), upLeftChild.begin(), upLeftChild.end());
	}
	if (bottomLeftNode)
	{
		std::list<T*> bottomLeftChild;
		bottomLeftChild = bottomLeftNode->GetObjectsAt(px, py);
		resObjects.insert(resObjects.end(), bottomLeftChild.begin(), bottomLeftChild.end());
	}
	if (bottomRightNode)
	{
		std::list<T*> bottomRightChild;
		bottomRightChild = bottomRightNode->GetObjectsAt(px, py);
		resObjects.insert(resObjects.end(), bottomRightChild.begin(), bottomRightChild.end());
	}
	return resObjects;
}

//////////////////////////////////////////////////////////////////////////

template <typename T>
void QuadTreeNode<T>::RemoveObjectsAt(float px, float py, float w, float h)
{
	// �������ڵ㱻������ɾ������ڵ�Ķ���;
	// ����ж���Ҫ�ǶԸ��ڵ������ã������ӽڵ�ʵ�����ϲ㶼�����ж�;
	if (IsContain(px, py, w, h, this))
	{
		// ������ڵ��Ķ���;
		objects.clear();
		// ���һ��;
		if (level == maxLevel)
			return;

	}
	// ������ӽڵ��ұ������������ӽڵ㣬ע������Ұָ��;
	// ��ʵֻҪ�ϲ㱻�����ˣ��²�϶������������뻹��Ľ�;
	if (upRightNode&&IsContain(px, py, w, h, upRightNode))
	{
		upRightNode->RemoveObjectsAt(px, py, w, h);
		delete upRightNode;
		upRightNode = NULL;

	}
	if (upLeftNode&&IsContain(px, py, w, h, upLeftNode))
	{
		upLeftNode->RemoveObjectsAt(px, py, w, h);
		delete upLeftNode;
		upLeftNode = NULL;

	}
	if (bottomLeftNode&&IsContain(px, py, w, h, bottomLeftNode))
	{
		bottomLeftNode->RemoveObjectsAt(px, py, w, h);
		delete bottomLeftNode;
		bottomLeftNode = NULL;

	}
	if (bottomRightNode&&IsContain(px, py, w, h, bottomRightNode))
	{
		bottomRightNode->RemoveObjectsAt(px, py, w, h);
		delete bottomRightNode;
		bottomRightNode = NULL;
	}
}

template <typename T>
void QuadTreeNode<T>::GetRect(float* _x, float* _y, float* _width, float* _height)
{
	(*_x) = x;
	(*_y) = y;
	(*_width) = width;
	(*_height) = height;
}

template <typename T>
void QuadTreeNode<T>::GetMaxLevel(int* _maxLevel)
{
	(*_maxLevel) = maxLevel;
}

#endif
