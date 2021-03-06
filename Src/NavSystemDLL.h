#ifndef __NAV_SYSTEM_DLL_H__
#define __NAV_SYSTEM_DLL_H__

#if defined _WINDOWS
	#if defined (EXPORTBUILD)
		#define _DLLExprot __declspec (dllexport)
	#else
		#define _DLLExprot __declspec (dllimport)
	#endif
#else
	#define _DLLExprot 
#endif

struct NAV_VEC3 { float x, y, z; };

struct NAV_VEC2 { float x, z; };

extern "C"
{
	//************************************
	// Method:    创建当前场景的导航;
	// Returns:   是否创建成功;
	// Parameter: [path]nav文件所在路径，UTF8编码;
	// Parameter: [len]字节数;
	//************************************
	_DLLExprot bool Nav_Create(const char* path, const char* scnName);

	//************************************
	// Method:    从内存创建当前场景的导航;
	// Returns:   是否创建成功;
	// Parameter: [data]nav文件的二进制数据;
	//************************************
	_DLLExprot bool Nav_CreateFromMemory(char* data, const char* scnName);

	//************************************
	// Method:    是否加载了简图;
	// Returns:   是否加载了简图;
	//************************************
	_DLLExprot bool Nav_HasSketchScene();

	//************************************
	// Method:    从文件创建简图;
	// Returns:   是否创建成功;
	// Parameter: [path]简图文件路径;
	//************************************
	_DLLExprot bool Nav_LoadSketchSceneFromFile(const char* path);

	//************************************
	// Method:    从内存创建简图;
	// Returns:   是否创建成功;
	// Parameter: [data]简图的二进制路径;
	//************************************
	_DLLExprot bool Nav_LoadSketchSceneFromMemory(char* data);

	//************************************
	// Method:    释放一层导航的数据;
	// Returns:   void
	// Parameter: [layer]导航的层ID;
	//************************************
	_DLLExprot void Nav_ReleaseLayer(unsigned int layer);

	//************************************
	// Method:    通过层索引释放一层导航的数据;
	// Returns:   void
	// Parameter: [index]导航的层索引;
	//************************************
	_DLLExprot void Nav_ReleaseLayerByIndex(unsigned int index);

	//************************************
	// Method:    通过场景名释放一层导航的数据;
	// Returns:   void
	// Parameter: [scnName]导航的场景名;
	//************************************
	_DLLExprot void Nav_ReleaseLayerByScnName(const char* scnName);

	//************************************
	// Method:    释放导航所有数据;
	// Returns:   void
	//************************************
	_DLLExprot void Nav_Release();

	//************************************
	// Method:    当前场景导航的层数;
	// Returns:   是否成功获取层数;
	// Parameter: [layerCount]返回获取的层数;
	//************************************
	_DLLExprot bool Nav_GetLayerCount(unsigned int* layerCount);

	//************************************
	// Method:    根据索引获取层ID;
	// Returns:   是否成功获取层ID;
	// Parameter: [layer]返回获取的层ID;
	//************************************
	_DLLExprot bool Nav_GetLayerByIndex(unsigned int index, unsigned int* layer);

	//************************************
	// Method:    根据索引获取场景名;
	// Returns:   是否成功获取场景名;
	// Parameter: [index]层索引;
	// Parameter: [scnName]返回获得的场景名;
	//************************************
	_DLLExprot bool Nav_GetScnNameByIndex(unsigned int index, const char** scnName);

	//************************************
	// Method:    根据层ID获取场景名;
	// Returns:   是否成功获取场景名;
	// Parameter: [layer]层ID;
	// Parameter: [scnName]返回获得的场景名;
	//************************************
	_DLLExprot bool Nav_GetScnNameByLayer(unsigned int layer, const char** scnName);

	//************************************
	// Method:    获得指定位置所在的层数。在pos指定位置，垂直向下发射一条射线，返回碰撞到的第一个导航的层数索引;
	// Returns:   是否成功获取导航层索引;
	// Parameter: [pos]指定位置;
	// Parameter: [layer]返回的层数索引;
	//************************************
	_DLLExprot bool Nav_GetLayer(const NAV_VEC3* pos, unsigned int* layer);

	//************************************
	// Method:    获得指定位置的高度。在pos指定位置，垂直向下发射一条射线，返回碰撞到的第一个导航的Y值;
	// Returns:   是否成功获取高度;
	// Parameter: [pos]指定位置;
	// Parameter: [height]返回的高度值;
	// Parameter: [layer]返回的层数索引;
	//************************************
	_DLLExprot bool Nav_GetNavHeight(const NAV_VEC3* pos, float* height, unsigned int* layer);

	//************************************
	// Method:    获得指定层的高度;
	// Returns:   是否成功获取高度，可以用来检测点是否在导航上;
	// Parameter: [pos]指定位置;
	// Parameter: [layer]指定层索引;
	// Parameter: [height]返回的高度;
	//************************************
	_DLLExprot bool Nav_GetLayerHeight(const NAV_VEC3* pos, unsigned int layer, float* height);

	//************************************
	// Method:    线段投射导航边缘;
	// Returns:   线段是否碰撞到导航边缘，碰撞到返回true;
	// Parameter: [start]线段起点;
	// Parameter: [end]线段终点;
	// Parameter: [layer]检测导航的层索引;
	// Parameter: [hitPos]如果线段碰撞到了导航边缘，则返回碰撞点，否则返回[end];
	//************************************
	_DLLExprot bool Nav_LineCast(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer, NAV_VEC3* hitPos);

	//************************************
	// Method:    线段投射导航边缘;
	// Returns:   线段是否碰撞到导航边缘，碰撞到返回true;
	// Parameter: [start]线段起点;
	// Parameter: [end]线段终点;
	// Parameter: [layer]检测导航的层索引;
	// Parameter: [hitPos]如果线段碰撞到了导航边缘，则返回碰撞点，否则返回[end];
	// Parameter: [edgePoint0]如果线段碰撞到了导航边缘，则返回碰撞到的导航边的一个顶点;
	// Parameter: [edgePoint1]如果线段碰撞到了导航边缘，则返回碰撞到的导航边的另一个顶点;
	//************************************
	_DLLExprot bool Nav_LineCastEdge(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer, NAV_VEC3* hitPos, NAV_VEC3* edgePoint0, NAV_VEC3* edgePoint1);

	//************************************
	// Method:    判断线段是否与导航边缘相交，虽然LineCast也能判断，但是LineTest效率稍微高一点;
	// Returns:   相交则返回true，不相交则返回false;
	// Parameter: [start]线段起点;
	// Parameter: [end]线段终点;
	// Parameter: [layer]检测导航的层索引;
	//************************************
	_DLLExprot bool Nav_LineTest(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer);

	//************************************
	// Method:    线段与指定层的导航模型的碰撞，注意不是检测边缘;
	// Returns:   线段是否与导航相交，相交返回true;
	// Parameter: [start]线段起点;
	// Parameter: [end]线段终点;
	// Parameter: [layer]检测导航的层索引;
	// Parameter: [hitPos]射线与导航的交点;
	//************************************
	_DLLExprot bool Nav_RayCastLayer(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer, NAV_VEC3* hitPos);

	//************************************
	// Method:    线段与导航模型的碰撞，注意不是检测边缘;
	// Returns:   线段是否与导航相交，相交返回true;
	// Parameter: [start]线段起点;
	// Parameter: [end]线段终点;
	// Parameter: [hitPos]射线与导航的交点;
	//************************************
	_DLLExprot bool Nav_RayCastNav(const NAV_VEC3* start, const NAV_VEC3* end, NAV_VEC3* hitPos);

	//************************************
	// Method:    AStar算法计算出一条最优寻路路径;
	// Returns:   是否成功计算出寻路路径，计算出则返回true;
	// Parameter: [start]寻路起点;
	// Parameter: [end]寻路终点;
	// Parameter: [layer]指定导航的层索引;
	// Parameter: [pathBuffer]按先后顺序返回路径点集合;
	// Parameter: [pathNodeCount]路径点数量;
	//************************************
	_DLLExprot bool Nav_CalcLayerPath(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer, NAV_VEC3** pathBuffer, unsigned int* pathNodeCount);

	//************************************
	// Method:    AStar算法计算出一条最优寻路路径;
	// Returns:   是否成功计算出寻路路径，计算出则返回true;
	// Parameter: [start]寻路起点;
	// Parameter: [end]寻路终点;
	// Parameter: [pathBuffer]按先后顺序返回路径点集合;
	// Parameter: [pathNodeCount]路径点数量;
	//************************************
	_DLLExprot bool Nav_CalcPath(const NAV_VEC3* start, const NAV_VEC3* end, NAV_VEC3** pathBuffer, unsigned int* pathNodeCount);

	//************************************
	// Method:    释放CalcLayerPath和CalcPath计算出来的路径数据;
	// Returns:   是否释放成功;
	// Parameter: [pathBuffer]CalcLayerPath计算出来的路径数据;
	//************************************
	_DLLExprot bool Nav_ReleasePath(NAV_VEC3** pathBuffer);	

	//************************************
	// Method:    获取指定层导航的所有顶点（主要编辑器用）;
	// Returns:   是否获取成功;
	// Parameter: [verticesBuffer]返回所有的顶点;
	// Parameter: [verticesCount]所有顶点数量;
	// Parameter: [layer]指定层索引;
	//************************************
	_DLLExprot bool Nav_GetTrianglesByIndex(NAV_VEC3** verticesBuffer, unsigned int* verticesCount, unsigned int index);

	//************************************
	// Method:    释放Nav_GetTrianglesByIndex获取出来的顶点数据（主要编辑器用）;
	// Returns:   是否释放成功;
	// Parameter: [verticesBuffer]Nav_GetTrianglesByIndex获取出来的顶点数据;
	//************************************
	_DLLExprot bool Nav_ReleaseTriangles(NAV_VEC3** verticesBuffer);

	//************************************
	// Method:    获取指定层导航上，门的数量;
	// Returns:   是否获取成功;
	// Parameter: [layer]指定层索引;
	// Parameter: [gateCount]返回门的数量;
	//************************************
	_DLLExprot bool Nav_GetLayerGateCount(unsigned int layer, unsigned int* gateCount);

	//************************************
	// Method:    检查是否指定层导航上的某一道门可以通行;
	// Returns:   是否检查成功;
	// Parameter: [layer]指定层索引;
	// Parameter: [gateIndex]门索引;
	// Parameter: [passable]返回指定门是否可以通行，也就是这道门是否开着;
	//************************************
	_DLLExprot bool Nav_IsLayerGatePassable(unsigned int layer, unsigned int gateIndex, bool* passable);

	//************************************
	// Method:    开关指定层导航上的某一道门;
	// Returns:   是否操作成功;
	// Parameter: [layer]指定层索引;
	// Parameter: [gateIndex]门索引;
	// Parameter: [passable]true为开门，false为关门;
	//************************************
	_DLLExprot bool Nav_SetLayerGatePassable(unsigned int layer, unsigned int gateIndex, bool passable);

	//************************************
	// Method:    获得关闭着的门的顶点集合（主要编辑器用）;
	// Returns:   是否获取成功;
	// Parameter: [layer]指定层索引;
	// Parameter: [verticesBuffer]返回门的顶点集合;
	// Parameter: [verticesCount]返回门的顶点的数量;
	//************************************
	_DLLExprot bool Nav_GetLayerCloseGates(unsigned int layer, NAV_VEC3** verticesBuffer, unsigned int* verticesCount);

	//************************************
	// Method:    释放GetLayerCloseGates获取出来的顶点数据（主要编辑器用）;
	// Returns:   是否释放成功;
	// Parameter: [verticesBuffer]GetLayerCloseGates获取出来的顶点数据;
	//************************************
	_DLLExprot bool Nav_ReleaseLayerCloseGates(NAV_VEC3** verticesBuffer);

	//************************************
	// Method:    获取指定层的AABB盒;
	// Returns:   是否获取成功;
	// Parameter: [layer]指定层索引;
	// Parameter: [min]返回AABB盒的最小点;
	// Parameter: [max]返回AABB盒的最大点;
	//************************************
	_DLLExprot bool Nav_GetLayerBound(unsigned int layer, NAV_VEC3* min, NAV_VEC3* max);

	//************************************
	// Method:    获取所有层的AABB盒;
	// Returns:   是否获取成功;
	// Parameter: [layer]指定层索引;
	// Parameter: [min]返回AABB盒的最小点;
	// Parameter: [max]返回AABB盒的最大点;
	//************************************
	_DLLExprot bool Nav_GetNavBound(NAV_VEC3* min, NAV_VEC3* max);

	//************************************
	// Method:    添加边界体;
	// Returns:   是否添加成功;
	// Parameter: [layer]指定层索引;
	// Parameter: [data]边界体数据;
	// Parameter: [len]边界体数据长度;
	//************************************
	_DLLExprot bool Nav_AddBoundsVolume(unsigned int layer, char* data, unsigned int len);

	_DLLExprot bool Nav_GetLayerEdges(unsigned int layer, NAV_VEC3** verticesBuffer, unsigned int* edgeCount);

	_DLLExprot bool Nav_ReleaseLayerEdges(NAV_VEC3** verticesBuffer);
}

#endif