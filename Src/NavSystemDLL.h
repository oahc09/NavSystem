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
	// Method:    ������ǰ�����ĵ���;
	// Returns:   �Ƿ񴴽��ɹ�;
	// Parameter: [path]nav�ļ�����·����UTF8����;
	// Parameter: [len]�ֽ���;
	//************************************
	_DLLExprot bool Nav_Create(const char* path, const char* scnName);

	//************************************
	// Method:    ���ڴ洴����ǰ�����ĵ���;
	// Returns:   �Ƿ񴴽��ɹ�;
	// Parameter: [data]nav�ļ��Ķ���������;
	//************************************
	_DLLExprot bool Nav_CreateFromMemory(char* data, const char* scnName);

	//************************************
	// Method:    �Ƿ�����˼�ͼ;
	// Returns:   �Ƿ�����˼�ͼ;
	//************************************
	_DLLExprot bool Nav_HasSketchScene();

	//************************************
	// Method:    ���ļ�������ͼ;
	// Returns:   �Ƿ񴴽��ɹ�;
	// Parameter: [path]��ͼ�ļ�·��;
	//************************************
	_DLLExprot bool Nav_LoadSketchSceneFromFile(const char* path);

	//************************************
	// Method:    ���ڴ洴����ͼ;
	// Returns:   �Ƿ񴴽��ɹ�;
	// Parameter: [data]��ͼ�Ķ�����·��;
	//************************************
	_DLLExprot bool Nav_LoadSketchSceneFromMemory(char* data);

	//************************************
	// Method:    �ͷ�һ�㵼��������;
	// Returns:   void
	// Parameter: [layer]�����Ĳ�ID;
	//************************************
	_DLLExprot void Nav_ReleaseLayer(unsigned int layer);

	//************************************
	// Method:    ͨ���������ͷ�һ�㵼��������;
	// Returns:   void
	// Parameter: [index]�����Ĳ�����;
	//************************************
	_DLLExprot void Nav_ReleaseLayerByIndex(unsigned int index);

	//************************************
	// Method:    ͨ���������ͷ�һ�㵼��������;
	// Returns:   void
	// Parameter: [scnName]�����ĳ�����;
	//************************************
	_DLLExprot void Nav_ReleaseLayerByScnName(const char* scnName);

	//************************************
	// Method:    �ͷŵ�����������;
	// Returns:   void
	//************************************
	_DLLExprot void Nav_Release();

	//************************************
	// Method:    ��ǰ���������Ĳ���;
	// Returns:   �Ƿ�ɹ���ȡ����;
	// Parameter: [layerCount]���ػ�ȡ�Ĳ���;
	//************************************
	_DLLExprot bool Nav_GetLayerCount(unsigned int* layerCount);

	//************************************
	// Method:    ����������ȡ��ID;
	// Returns:   �Ƿ�ɹ���ȡ��ID;
	// Parameter: [layer]���ػ�ȡ�Ĳ�ID;
	//************************************
	_DLLExprot bool Nav_GetLayerByIndex(unsigned int index, unsigned int* layer);

	//************************************
	// Method:    ����������ȡ������;
	// Returns:   �Ƿ�ɹ���ȡ������;
	// Parameter: [index]������;
	// Parameter: [scnName]���ػ�õĳ�����;
	//************************************
	_DLLExprot bool Nav_GetScnNameByIndex(unsigned int index, const char** scnName);

	//************************************
	// Method:    ���ݲ�ID��ȡ������;
	// Returns:   �Ƿ�ɹ���ȡ������;
	// Parameter: [layer]��ID;
	// Parameter: [scnName]���ػ�õĳ�����;
	//************************************
	_DLLExprot bool Nav_GetScnNameByLayer(unsigned int layer, const char** scnName);

	//************************************
	// Method:    ���ָ��λ�����ڵĲ�������posָ��λ�ã���ֱ���·���һ�����ߣ�������ײ���ĵ�һ�������Ĳ�������;
	// Returns:   �Ƿ�ɹ���ȡ����������;
	// Parameter: [pos]ָ��λ��;
	// Parameter: [layer]���صĲ�������;
	//************************************
	_DLLExprot bool Nav_GetLayer(const NAV_VEC3* pos, unsigned int* layer);

	//************************************
	// Method:    ���ָ��λ�õĸ߶ȡ���posָ��λ�ã���ֱ���·���һ�����ߣ�������ײ���ĵ�һ��������Yֵ;
	// Returns:   �Ƿ�ɹ���ȡ�߶�;
	// Parameter: [pos]ָ��λ��;
	// Parameter: [height]���صĸ߶�ֵ;
	// Parameter: [layer]���صĲ�������;
	//************************************
	_DLLExprot bool Nav_GetNavHeight(const NAV_VEC3* pos, float* height, unsigned int* layer);

	//************************************
	// Method:    ���ָ����ĸ߶�;
	// Returns:   �Ƿ�ɹ���ȡ�߶ȣ��������������Ƿ��ڵ�����;
	// Parameter: [pos]ָ��λ��;
	// Parameter: [layer]ָ��������;
	// Parameter: [height]���صĸ߶�;
	//************************************
	_DLLExprot bool Nav_GetLayerHeight(const NAV_VEC3* pos, unsigned int layer, float* height);

	//************************************
	// Method:    �߶�Ͷ�䵼����Ե;
	// Returns:   �߶��Ƿ���ײ��������Ե����ײ������true;
	// Parameter: [start]�߶����;
	// Parameter: [end]�߶��յ�;
	// Parameter: [layer]��⵼���Ĳ�����;
	// Parameter: [hitPos]����߶���ײ���˵�����Ե���򷵻���ײ�㣬���򷵻�[end];
	//************************************
	_DLLExprot bool Nav_LineCast(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer, NAV_VEC3* hitPos);

	//************************************
	// Method:    �߶�Ͷ�䵼����Ե;
	// Returns:   �߶��Ƿ���ײ��������Ե����ײ������true;
	// Parameter: [start]�߶����;
	// Parameter: [end]�߶��յ�;
	// Parameter: [layer]��⵼���Ĳ�����;
	// Parameter: [hitPos]����߶���ײ���˵�����Ե���򷵻���ײ�㣬���򷵻�[end];
	// Parameter: [edgePoint0]����߶���ײ���˵�����Ե���򷵻���ײ���ĵ����ߵ�һ������;
	// Parameter: [edgePoint1]����߶���ײ���˵�����Ե���򷵻���ײ���ĵ����ߵ���һ������;
	//************************************
	_DLLExprot bool Nav_LineCastEdge(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer, NAV_VEC3* hitPos, NAV_VEC3* edgePoint0, NAV_VEC3* edgePoint1);

	//************************************
	// Method:    �ж��߶��Ƿ��뵼����Ե�ཻ����ȻLineCastҲ���жϣ�����LineTestЧ����΢��һ��;
	// Returns:   �ཻ�򷵻�true�����ཻ�򷵻�false;
	// Parameter: [start]�߶����;
	// Parameter: [end]�߶��յ�;
	// Parameter: [layer]��⵼���Ĳ�����;
	//************************************
	_DLLExprot bool Nav_LineTest(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer);

	//************************************
	// Method:    �߶���ָ����ĵ���ģ�͵���ײ��ע�ⲻ�Ǽ���Ե;
	// Returns:   �߶��Ƿ��뵼���ཻ���ཻ����true;
	// Parameter: [start]�߶����;
	// Parameter: [end]�߶��յ�;
	// Parameter: [layer]��⵼���Ĳ�����;
	// Parameter: [hitPos]�����뵼���Ľ���;
	//************************************
	_DLLExprot bool Nav_RayCastLayer(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer, NAV_VEC3* hitPos);

	//************************************
	// Method:    �߶��뵼��ģ�͵���ײ��ע�ⲻ�Ǽ���Ե;
	// Returns:   �߶��Ƿ��뵼���ཻ���ཻ����true;
	// Parameter: [start]�߶����;
	// Parameter: [end]�߶��յ�;
	// Parameter: [hitPos]�����뵼���Ľ���;
	//************************************
	_DLLExprot bool Nav_RayCastNav(const NAV_VEC3* start, const NAV_VEC3* end, NAV_VEC3* hitPos);

	//************************************
	// Method:    AStar�㷨�����һ������Ѱ··��;
	// Returns:   �Ƿ�ɹ������Ѱ··����������򷵻�true;
	// Parameter: [start]Ѱ·���;
	// Parameter: [end]Ѱ·�յ�;
	// Parameter: [layer]ָ�������Ĳ�����;
	// Parameter: [pathBuffer]���Ⱥ�˳�򷵻�·���㼯��;
	// Parameter: [pathNodeCount]·��������;
	//************************************
	_DLLExprot bool Nav_CalcLayerPath(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer, NAV_VEC3** pathBuffer, unsigned int* pathNodeCount);

	//************************************
	// Method:    AStar�㷨�����һ������Ѱ··��;
	// Returns:   �Ƿ�ɹ������Ѱ··����������򷵻�true;
	// Parameter: [start]Ѱ·���;
	// Parameter: [end]Ѱ·�յ�;
	// Parameter: [pathBuffer]���Ⱥ�˳�򷵻�·���㼯��;
	// Parameter: [pathNodeCount]·��������;
	//************************************
	_DLLExprot bool Nav_CalcPath(const NAV_VEC3* start, const NAV_VEC3* end, NAV_VEC3** pathBuffer, unsigned int* pathNodeCount);

	//************************************
	// Method:    �ͷ�CalcLayerPath��CalcPath���������·������;
	// Returns:   �Ƿ��ͷųɹ�;
	// Parameter: [pathBuffer]CalcLayerPath���������·������;
	//************************************
	_DLLExprot bool Nav_ReleasePath(NAV_VEC3** pathBuffer);	

	//************************************
	// Method:    ��ȡָ���㵼�������ж��㣨��Ҫ�༭���ã�;
	// Returns:   �Ƿ��ȡ�ɹ�;
	// Parameter: [verticesBuffer]�������еĶ���;
	// Parameter: [verticesCount]���ж�������;
	// Parameter: [layer]ָ��������;
	//************************************
	_DLLExprot bool Nav_GetTrianglesByIndex(NAV_VEC3** verticesBuffer, unsigned int* verticesCount, unsigned int index);

	//************************************
	// Method:    �ͷ�Nav_GetTrianglesByIndex��ȡ�����Ķ������ݣ���Ҫ�༭���ã�;
	// Returns:   �Ƿ��ͷųɹ�;
	// Parameter: [verticesBuffer]Nav_GetTrianglesByIndex��ȡ�����Ķ�������;
	//************************************
	_DLLExprot bool Nav_ReleaseTriangles(NAV_VEC3** verticesBuffer);

	//************************************
	// Method:    ��ȡָ���㵼���ϣ��ŵ�����;
	// Returns:   �Ƿ��ȡ�ɹ�;
	// Parameter: [layer]ָ��������;
	// Parameter: [gateCount]�����ŵ�����;
	//************************************
	_DLLExprot bool Nav_GetLayerGateCount(unsigned int layer, unsigned int* gateCount);

	//************************************
	// Method:    ����Ƿ�ָ���㵼���ϵ�ĳһ���ſ���ͨ��;
	// Returns:   �Ƿ���ɹ�;
	// Parameter: [layer]ָ��������;
	// Parameter: [gateIndex]������;
	// Parameter: [passable]����ָ�����Ƿ����ͨ�У�Ҳ����������Ƿ���;
	//************************************
	_DLLExprot bool Nav_IsLayerGatePassable(unsigned int layer, unsigned int gateIndex, bool* passable);

	//************************************
	// Method:    ����ָ���㵼���ϵ�ĳһ����;
	// Returns:   �Ƿ�����ɹ�;
	// Parameter: [layer]ָ��������;
	// Parameter: [gateIndex]������;
	// Parameter: [passable]trueΪ���ţ�falseΪ����;
	//************************************
	_DLLExprot bool Nav_SetLayerGatePassable(unsigned int layer, unsigned int gateIndex, bool passable);

	//************************************
	// Method:    ��ùر��ŵ��ŵĶ��㼯�ϣ���Ҫ�༭���ã�;
	// Returns:   �Ƿ��ȡ�ɹ�;
	// Parameter: [layer]ָ��������;
	// Parameter: [verticesBuffer]�����ŵĶ��㼯��;
	// Parameter: [verticesCount]�����ŵĶ��������;
	//************************************
	_DLLExprot bool Nav_GetLayerCloseGates(unsigned int layer, NAV_VEC3** verticesBuffer, unsigned int* verticesCount);

	//************************************
	// Method:    �ͷ�GetLayerCloseGates��ȡ�����Ķ������ݣ���Ҫ�༭���ã�;
	// Returns:   �Ƿ��ͷųɹ�;
	// Parameter: [verticesBuffer]GetLayerCloseGates��ȡ�����Ķ�������;
	//************************************
	_DLLExprot bool Nav_ReleaseLayerCloseGates(NAV_VEC3** verticesBuffer);

	//************************************
	// Method:    ��ȡָ�����AABB��;
	// Returns:   �Ƿ��ȡ�ɹ�;
	// Parameter: [layer]ָ��������;
	// Parameter: [min]����AABB�е���С��;
	// Parameter: [max]����AABB�е�����;
	//************************************
	_DLLExprot bool Nav_GetLayerBound(unsigned int layer, NAV_VEC3* min, NAV_VEC3* max);

	//************************************
	// Method:    ��ȡ���в��AABB��;
	// Returns:   �Ƿ��ȡ�ɹ�;
	// Parameter: [layer]ָ��������;
	// Parameter: [min]����AABB�е���С��;
	// Parameter: [max]����AABB�е�����;
	//************************************
	_DLLExprot bool Nav_GetNavBound(NAV_VEC3* min, NAV_VEC3* max);

	_DLLExprot bool Nav_SetBoundsVolume(unsigned int layer, char* data, unsigned int len);

	_DLLExprot bool Nav_GetLayerEdges(unsigned int layer, NAV_VEC3** verticesBuffer, unsigned int* edgeCount);

	_DLLExprot bool Nav_ReleaseLayerEdges(NAV_VEC3** verticesBuffer);
}

#endif