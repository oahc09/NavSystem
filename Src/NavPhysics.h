#ifndef __NAV_PHYSICS_H__
#define __NAV_PHYSICS_H__

#include "NavInc.h"

class NavTriangle;

namespace NavPhysics
{
	struct NavHit
	{
		float distance;
		Nav::Vector3 hitPoint;
	};

	/************************************************************************
	 * ����:				�ж��������Ƿ�������ཻ;
	 * ����:				�������;
	 * ����:				���߷��򣬱����һ��;
	 * ����:				������;
	 * ����:				������ײ��Ϣ;
	 * ����ֵ��				trueΪ�ཻ��falseΪû�ཻ;
	*************************************************************************/
	bool RayIntersectTriangle(const Nav::Vector3& orig, const Nav::Vector3& dir,
		const Nav::Vector3& v0, const Nav::Vector3& v1, const Nav::Vector3& v2,
		NavHit* hit);

	/************************************************************************
	 * ����:				�ж��߶��Ƿ�������ཻ;
	 * ����:				�������;
	 * ����:				���߷��򣬱����һ��;
	 * ����:				�߶�;
	 * ����:				������ײ��Ϣ;
	 * ����ֵ��				trueΪ�ཻ��falseΪû�ཻ;
	*************************************************************************/
	bool RayIntersectSegment2D(const Nav::Vector2& orig, const Nav::Vector2& dir,
		const Nav::Vector2& lineBegin, const Nav::Vector2& lineEnd,
		NavHit* hit);

	/************************************************************************
	 * ����:				�ж϶�ά���Ƿ���������ཻ����������λ�ü��ʱ������ȵ�������������������ߺ��������ཻ����;
	 * ����:				������������;
	 * ����:				��ά��;
	 * ����ֵ��				trueΪ�ཻ��falseΪû�ཻ;
	*************************************************************************/
	bool TriangleAABBPoint2D(const Nav::Vector2& v0, const Nav::Vector2& v1, const Nav::Vector2& v2,
		const Nav::Vector2& point2D);

	/************************************************************************
	* ����:					TriangleIntersect2DPoint��3D�����汾;
	* ����:					������������;
	* ����:					��ά��;
	* ����ֵ��				trueΪ�ཻ��falseΪû�ཻ;
	*************************************************************************/
	bool TriangleAABBPoint2D(const Nav::Vector3& v0, const Nav::Vector3& v1, const Nav::Vector3& v2,
		const Nav::Vector3& point2D);

	/************************************************************************
	* ����:					�����߶ε�AABB���ཻ���;
	* ����:					�߶�1;
	* ����:					�߶�2;
	* ����ֵ��				trueΪ�ཻ��falseΪû�ཻ;
	*************************************************************************/
	bool SegmentAABBSegment2D(const Nav::Vector3& line1Begin, const Nav::Vector3& line1End,
		const Nav::Vector3& line2Begin, const Nav::Vector3& line2End);

	bool IsPointInTriangle(const Nav::Vector2& v0, const Nav::Vector2& v1, const Nav::Vector2& v2, const Nav::Vector2& point);

	bool IsPointInTriangle2D(const Nav::Vector3& v0, const Nav::Vector3& v1, const Nav::Vector3& v2, const Nav::Vector3& point);

	bool IsSegmentsInterct(const Nav::Vector2& line1Begin, const Nav::Vector2& line1End,
		const Nav::Vector2& line2Begin, const Nav::Vector2& line2End);

	bool SegmentIntersectSegment(const Nav::Vector2& line1Begin, const Nav::Vector2& line1End,
		const Nav::Vector2& line2Begin, const Nav::Vector2& line2End,
		Nav::Vector2* hitPoint);

	float CalcTriangleArea2D(const Nav::Vector3& v0, const Nav::Vector3& v1, const Nav::Vector3& v2);
}

#endif