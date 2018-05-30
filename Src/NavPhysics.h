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

	/* \����:				�ж��������Ƿ�������ཻ;
	 * \����:				�������;
	 * \����:				���߷��򣬱����һ��;
	 * \����:				������;
	 * \����:				������ײ��Ϣ;
	 * \����ֵ��			trueΪ�ཻ��falseΪû�ཻ;
	*/
	bool RayIntersectTriangle(const Vector3& orig, const Vector3& dir,
		const Vector3& v0, const Vector3& v1, const Vector3& v2,
		NavHit* hit);
}

#endif