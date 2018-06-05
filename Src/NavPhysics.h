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
	bool RayIntersectSegment2D(const Vector2& orig, const Vector2& dir,
		const Vector2& lineBegin, const Vector2& lineEnd,
		NavHit* hit);

	/************************************************************************
	 * ����:				�ж϶�ά���Ƿ���������ཻ����������λ�ü��ʱ������ȵ�������������������ߺ��������ཻ����;
	 * ����:				������������;
	 * ����:				��ά��;
	 * ����ֵ��				trueΪ�ཻ��falseΪû�ཻ;
	*************************************************************************/
	bool TriangleAABBPoint2D(const Vector2& v0, const Vector2& v1, const Vector2& v2,
		const Vector2& point2D);

	/************************************************************************
	* ����:					TriangleIntersect2DPoint��3D�����汾;
	* ����:					������������;
	* ����:					��ά��;
	* ����ֵ��				trueΪ�ཻ��falseΪû�ཻ;
	*************************************************************************/
	bool TriangleAABBPoint2D(const Vector3& v0, const Vector3& v1, const Vector3& v2,
		const Vector3& point2D);

	/************************************************************************
	* ����:					�����߶ε�AABB���ཻ���;
	* ����:					�߶�1;
	* ����:					�߶�2;
	* ����ֵ��				trueΪ�ཻ��falseΪû�ཻ;
	*************************************************************************/
	bool SegmentAABBSegment2D(const Vector3& line1Begin, const Vector3& line1End,
		const Vector3& line2Begin, const Vector3& line2End);

	bool IsPointInTriangle(const Vector2& v0, const Vector2& v1, const Vector2& v2, const Vector2& point);

	bool IsSegmentsInterct(const Vector2& line1Begin, const Vector2& line1End,
		const Vector2& line2Begin, const Vector2& line2End);

	bool SegmentIntersectSegment(const Vector2& line1Begin, const Vector2& line1End,
		const Vector2& line2Begin, const Vector2& line2End,
		Vector2* hitPoint);
}

#endif