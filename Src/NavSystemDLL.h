#ifndef __NAV_SYSTEM_DLL_H__
#define __NAV_SYSTEM_DLL_H__

#if defined (EXPORTBUILD)
#define _DLLExprot __declspec (dllexport)
#else
#define _DLLExprot __declspec (dllimport)
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
	_DLLExprot bool Create(const char* path);

	//************************************
	// Method:    ������ǰ�����ĵ���;
	// Returns:   �Ƿ񴴽��ɹ�;
	// Parameter: [path]nav�ļ�����·����Unicode���룬wchar_t*ǿתΪunsinged char*;
	// Parameter: [len]unsinged char*�ֽ���;
	//************************************
	_DLLExprot bool CreateW(const unsigned char* path, unsigned int len);

	//************************************
	// Method:    �ͷŵ�ǰ�����ĵ���;
	// Returns:   void
	//************************************
	_DLLExprot void Release();

	//************************************
	// Method:    ��ǰ���������Ĳ���;
	// Returns:   �Ƿ�ɹ���ȡ����;
	// Parameter: [layerCount]���ػ�ȡ�Ĳ���;
	//************************************
	_DLLExprot bool GetLayerCount(unsigned int* layerCount);

	//************************************
	// Method:    ���ָ��λ�����ڵĲ�������posָ��λ�ã���ֱ���·���һ�����ߣ�������ײ���ĵ�һ�������Ĳ�������;
	// Returns:   �Ƿ�ɹ���ȡ����������;
	// Parameter: [pos]ָ��λ��;
	// Parameter: [layer]���صĲ�������;
	//************************************
	_DLLExprot bool GetLayer(const NAV_VEC3* pos, unsigned int* layer);

	//************************************
	// Method:    ���ָ��λ�õĸ߶ȡ���posָ��λ�ã���ֱ���·���һ�����ߣ�������ײ���ĵ�һ��������Yֵ;
	// Returns:   �Ƿ�ɹ���ȡ�߶�;
	// Parameter: [pos]ָ��λ��;
	// Parameter: [height]���صĸ߶�ֵ;
	// Parameter: [layer]���صĲ�������;
	//************************************
	_DLLExprot bool GetNavHeight(const NAV_VEC3* pos, float* height, unsigned int* layer);

	//************************************
	// Method:    ���ָ����ĸ߶�;
	// Returns:   �Ƿ�ɹ���ȡ�߶ȣ��������������Ƿ��ڵ�����;
	// Parameter: [pos]ָ��λ��;
	// Parameter: [layer]ָ��������;
	// Parameter: [height]���صĸ߶�;
	//************************************
	_DLLExprot bool GetLayerHeight(const NAV_VEC3* pos, unsigned int layer, float* height);

	//************************************
	// Method:    �߶�Ͷ�䵼����Ե;
	// Returns:   �߶��Ƿ���ײ��������Ե����ײ������true;
	// Parameter: [start]�߶����;
	// Parameter: [end]�߶��յ�;
	// Parameter: [layer]��⵼���Ĳ�����;
	// Parameter: [hitPos]����߶���ײ���˵�����Ե���򷵻���ײ�㣬���򷵻�[end];
	//************************************
	_DLLExprot bool LineCast(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer, NAV_VEC3* hitPos);

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
	_DLLExprot bool LineCastEdge(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer, NAV_VEC3* hitPos, NAV_VEC3* edgePoint0, NAV_VEC3* edgePoint1);

	//************************************
	// Method:    �ж��߶��Ƿ��뵼����Ե�ཻ����ȻLineCastҲ���жϣ�����LineTestЧ����΢��һ��;
	// Returns:   �ཻ�򷵻�true�����ཻ�򷵻�false;
	// Parameter: [start]�߶����;
	// Parameter: [end]�߶��յ�;
	// Parameter: [layer]��⵼���Ĳ�����;
	//************************************
	_DLLExprot bool LineTest(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer);

	//************************************
	// Method:    �߶���ָ����ĵ���ģ�͵���ײ��ע�ⲻ�Ǽ���Ե;
	// Returns:   �߶��Ƿ��뵼���ཻ���ཻ����true;
	// Parameter: [start]�߶����;
	// Parameter: [end]�߶��յ�;
	// Parameter: [layer]��⵼���Ĳ�����;
	// Parameter: [hitPos]�����뵼���Ľ���;
	//************************************
	_DLLExprot bool RayCastLayer(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer, NAV_VEC3* hitPos);

	//************************************
	// Method:    �߶��뵼��ģ�͵���ײ��ע�ⲻ�Ǽ���Ե;
	// Returns:   �߶��Ƿ��뵼���ཻ���ཻ����true;
	// Parameter: [start]�߶����;
	// Parameter: [end]�߶��յ�;
	// Parameter: [hitPos]�����뵼���Ľ���;
	//************************************
	_DLLExprot bool RayCastNav(const NAV_VEC3* start, const NAV_VEC3* end, NAV_VEC3* hitPos);

	//************************************
	// Method:    AStar�㷨�����һ������Ѱ··��;
	// Returns:   �Ƿ�ɹ������Ѱ··����������򷵻�true;
	// Parameter: [start]Ѱ·���;
	// Parameter: [end]Ѱ·�յ�;
	// Parameter: [layer]ָ�������Ĳ�����;
	// Parameter: [pathBuffer]���Ⱥ�˳�򷵻�·���㼯��;
	// Parameter: [pathNodeCount]·��������;
	//************************************
	_DLLExprot bool CalcLayerPath(const NAV_VEC3* start, const NAV_VEC3* end, unsigned int layer, NAV_VEC3** pathBuffer, unsigned int* pathNodeCount);

	//************************************
	// Method:    �ͷ�CalcLayerPath���������·������;
	// Returns:   �Ƿ��ͷųɹ�;
	// Parameter: [pathBuffer]CalcLayerPath���������·������;
	//************************************
	_DLLExprot bool ReleaseLayerPath(NAV_VEC3** pathBuffer);

	//************************************
	// Method:    ��ȡָ���㵼�������ж��㣨��Ҫ�༭���ã�;
	// Returns:   �Ƿ��ȡ�ɹ�;
	// Parameter: [verticesBuffer]�������еĶ���;
	// Parameter: [verticesCount]���ж�������;
	// Parameter: [layer]ָ��������;
	//************************************
	_DLLExprot bool GetLayerTriangles(NAV_VEC3** verticesBuffer, unsigned int* verticesCount, unsigned int layer);

	//************************************
	// Method:    �ͷ�GetLayerTriangles��ȡ�����Ķ������ݣ���Ҫ�༭���ã�;
	// Returns:   �Ƿ��ͷųɹ�;
	// Parameter: [verticesBuffer]GetLayerTriangles��ȡ�����Ķ�������;
	//************************************
	_DLLExprot bool ReleaseLayerTriangles(NAV_VEC3** verticesBuffer);

	//************************************
	// Method:    ��ȡָ���㵼���ϣ��ŵ�����;
	// Returns:   �Ƿ��ȡ�ɹ�;
	// Parameter: [layer]ָ��������;
	// Parameter: [gateCount]�����ŵ�����;
	//************************************
	_DLLExprot bool GetLayerGateCount(unsigned int layer, unsigned int* gateCount);

	//************************************
	// Method:    ����Ƿ�ָ���㵼���ϵ�ĳһ���ſ���ͨ��;
	// Returns:   �Ƿ���ɹ�;
	// Parameter: [layer]ָ��������;
	// Parameter: [gateIndex]������;
	// Parameter: [passable]����ָ�����Ƿ����ͨ�У�Ҳ����������Ƿ���;
	//************************************
	_DLLExprot bool IsLayerGatePassable(unsigned int layer, unsigned int gateIndex, bool* passable);

	//************************************
	// Method:    ����ָ���㵼���ϵ�ĳһ����;
	// Returns:   �Ƿ�����ɹ�;
	// Parameter: [layer]ָ��������;
	// Parameter: [gateIndex]������;
	// Parameter: [passable]trueΪ���ţ�falseΪ����;
	//************************************
	_DLLExprot bool SetLayerGatePassable(unsigned int layer, unsigned int gateIndex, bool passable);

	//************************************
	// Method:    ��ùر��ŵ��ŵĶ��㼯�ϣ���Ҫ�༭���ã�;
	// Returns:   �Ƿ��ȡ�ɹ�;
	// Parameter: [layer]ָ��������;
	// Parameter: [verticesBuffer]�����ŵĶ��㼯��;
	// Parameter: [verticesCount]�����ŵĶ��������;
	//************************************
	_DLLExprot bool GetLayerCloseGates(unsigned int layer, NAV_VEC3** verticesBuffer, unsigned int* verticesCount);

	//************************************
	// Method:    �ͷ�GetLayerCloseGates��ȡ�����Ķ������ݣ���Ҫ�༭���ã�;
	// Returns:   �Ƿ��ͷųɹ�;
	// Parameter: [verticesBuffer]GetLayerCloseGates��ȡ�����Ķ�������;
	//************************************
	_DLLExprot bool ReleaseLayerCloseGates(NAV_VEC3** verticesBuffer);
}

#endif