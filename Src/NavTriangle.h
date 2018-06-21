#ifndef __NAV_TRIANGLE_H__
#define __NAV_TRIANGLE_H__

#include "NavInc.h"

namespace Nav
{
	class NavTriangle
	{
	public:
		NavTriangle();

		NavTriangle(const Vector3& v0, const Vector3& v1, const Vector3& v2);

		unsigned int GetSize();

		unsigned int WriteTo(char* dest, unsigned int ptr);

		unsigned int ReadFrom(char* src, unsigned int ptr);
	public:
		// ��������������;
		Vector3 mPoint[3];

		// ����������;
		Vector3 mCenter;

		// Adjacent;

		// �ڽ�������;
		std::vector<NavTriangle*> mNeighbors;
		// ��������˵�� 0:[0,1]; 1:[1,2]; 2:[2,0];
		std::vector<int> mShareEdgeIndices;
		// ���ڽ������εľ���;
		std::vector<float> mDistance;
		// �ڽӱߵ��е�;
		std::vector<Vector3> mEdgeCenter;

		// �Ƿ���;
		bool mPassable;
	};
}

#endif