#ifndef __NAV_INC_H__
#define __NAV_INC_H__

#define _CRT_SECURE_NO_WARNINGS 

#include <vector>
#include <map>
#include <string>
#include "math/Vector3.h"
#include "micropather/micropather.h"
#include "quadtree/QuadTreeNode.h"

#define SAFE_DELETE(x) if (x) { delete x; x = NULL; }
#define SAFE_DELETE_ARRAY(x) if (x) { delete [] x; x = NULL; }
#define SAFE_RELEASE(x) if (x) { x->Release(); x = NULL; }
#define CURRENT_VERSION 102

namespace Nav
{
	float MinFloat(float f1, float f2);

	float MaxFloat(float f1, float f2);
}

#endif