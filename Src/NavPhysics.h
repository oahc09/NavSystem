#ifndef __NAV_PHYSICS_H__
#define __NAV_PHYSICS_H__

#include "NavInc.h"

class NavTriangle;

namespace NavPhysics
{
	struct NavHit
	{
		float distance;
		Vector3 hitPoint;
	};

	/************************************************************************
	 * ����:				�ж��������Ƿ�������ཻ;
	 * ����:				�������;
	 * ����:				���߷��򣬱����һ��;
	 * ����:				������;
	 * ����:				������ײ��Ϣ;
	 * ����ֵ��				trueΪ�ཻ��falseΪû�ཻ;
	*************************************************************************/
	bool RayIntersectTriangle(const Vector3& orig, const Vector3& dir,
		const Vector3& v0, const Vector3& v1, const Vector3& v2,
		NavHit* hit);

	/************************************************************************
	 * ����:				�ж��߶��Ƿ�������ཻ;
	 * ����:				�������;
	 * ����:				���߷��򣬱����һ��;
	 * ����:				�߶�;
	 * ����:				������ײ��Ϣ;
	 * ����ֵ��				trueΪ�ཻ��falseΪû�ཻ;
	*************************************************************************/
	bool RayIntersectSegment(const Vector2& orig, const Vector2& dir,
		const Vector2& lineBegin, const Vector2& lineEnd,
		NavHit* hit);

	/************************************************************************
	 * ����:				�ж϶�ά���Ƿ���������ཻ����������λ�ü��ʱ������ȵ�������������������ߺ��������ཻ����;
	 * ����:				������������;
	 * ����:				��ά��;
	 * ����ֵ��				trueΪ�ཻ��falseΪû�ཻ;
	*************************************************************************/
	bool TriangleIntersect2DPoint(const Vector2& v0, const Vector2& v1, const Vector2& v2,
		const Vector2& point2D);
}

#endif