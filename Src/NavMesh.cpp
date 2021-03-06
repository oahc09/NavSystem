#include "NavMesh.h"
#include "NavTriangle.h"
#include "NavEdge.h"
#include "NavPhysics.h"
#include "NavLinkInfo.h"
#include "NavSystem.h"
#include "NavBoundsVolume.h"

#ifdef _CHECK_LEAK
#define new  new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

namespace Nav
{
	struct AdjacentEdgePair
	{
		int firstTriIndex1;
		int firstTriIndex2;
		int secondTriIndex1;
		int secondTriIndex2;

		AdjacentEdgePair()
		{
			firstTriIndex1 = firstTriIndex2 = secondTriIndex1 = secondTriIndex2 = -1;
		}

		int EncodeFirstEdgeIndex()
		{
			if (firstTriIndex1 == 0)
			{
				if (firstTriIndex2 == 1)
				{
					return 0;
				}
				if (firstTriIndex2 == 2)
				{
					return 2;
				}
			}
			if (firstTriIndex1 == 1)
			{
				if (firstTriIndex2 == 0)
				{
					return 0;
				}
				if (firstTriIndex2 == 2)
				{
					return 1;
				}
			}
			if (firstTriIndex1 == 2)
			{
				if (firstTriIndex2 == 0)
				{
					return 2;
				}
				if (firstTriIndex2 == 1)
				{
					return 1;
				}
			}
			return -1;
		}

		int EncodeSecondEdgeIndex()
		{
			if (secondTriIndex1 == 0)
			{
				if (secondTriIndex2 == 1)
				{
					return 0;
				}
				if (secondTriIndex2 == 2)
				{
					return 2;
				}
			}
			if (secondTriIndex1 == 1)
			{
				if (secondTriIndex2 == 0)
				{
					return 0;
				}
				if (secondTriIndex2 == 2)
				{
					return 1;
				}
			}
			if (secondTriIndex1 == 2)
			{
				if (secondTriIndex2 == 0)
				{
					return 2;
				}
				if (secondTriIndex2 == 1)
				{
					return 1;
				}
			}
			return -1;
		}
	};

	void DecodeEdgeIndex(int edgeIndex, int* pointIndex1, int* pointIndex2)
	{
		if (edgeIndex == 0)
		{
			(*pointIndex1) = 0;
			(*pointIndex2) = 1;
		}
		else if (edgeIndex == 1)
		{
			(*pointIndex1) = 1;
			(*pointIndex2) = 2;
		}
		else if (edgeIndex == 2)
		{
			(*pointIndex1) = 2;
			(*pointIndex2) = 0;
		}
	}

	NavMesh::NavMesh()
	{
		mMin.Set(FLT_MAX, FLT_MAX, FLT_MAX);
		mMax.Set(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	}

	NavMesh::NavMesh(Vector3* vertices, int vertexNum, unsigned int* indices, int indicesNum)
	{
		mMin.Set(FLT_MAX, FLT_MAX, FLT_MAX);
		mMax.Set(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		for (int i = 0; i < indicesNum; i += 3)
		{
			unsigned int index0 = indices[i];
			unsigned int index1 = indices[i + 1];
			unsigned int index2 = indices[i + 2];

			NavTriangle* tri = new NavTriangle(vertices[index0], vertices[index1], vertices[index2]);
			mTriangles.push_back(tri);

			Vector3 triMax, triMin;
			tri->GetBound(&triMin, &triMax);
			mMin.Set(
				MinFloat(triMin.x, mMin.x),
				MinFloat(triMin.y, mMin.y),
				MinFloat(triMin.z, mMin.z)
				);
			mMax.Set(
				MaxFloat(triMax.x, mMax.x),
				MaxFloat(triMax.y, mMax.y),
				MaxFloat(triMax.z, mMax.z)
				);
		}
		UpdateAdjacent();
	}

	void NavMesh::GetBound(Vector3* min, Vector3* max)
	{
		(*min) = mMin;
		(*max) = mMax;
	}

	void NavMesh::AddBoundsVolume(NavBoundsVolume* bv)
	{
		std::map<std::string, NavBoundsVolume*>::iterator it;
		it = mBoundsVolumesMap.find(bv->mName);
		if (it != mBoundsVolumesMap.end())
		{
			return;
		}
		mBoundsVolumesMap[bv->mName] = bv;
		mBoundsVolumes.push_back(bv);
	}

	void NavMesh::DelBoundsVolume(const std::string& name)
	{
		std::map<std::string, NavBoundsVolume*>::iterator it;
		it = mBoundsVolumesMap.find(name);
		if (it == mBoundsVolumesMap.end())
		{
			return;
		}
		NavBoundsVolume* bv = it->second;
		mBoundsVolumesMap.erase(it);

		std::vector<NavBoundsVolume*>::iterator itv;
		for (itv = mBoundsVolumes.begin(); itv != mBoundsVolumes.end(); ++itv)
		{
			if ((*itv) == bv)
			{
				mBoundsVolumes.erase(itv);
				break;
			}
		}

		SAFE_DELETE(bv);
	}

	bool NavMesh::GetHeight(const Vector3& pos, float* height)
	{
		NavPhysics::NavHit hit;
		Vector3 vPos = pos;
		vPos.y += 1.0f;

		for (size_t i = 0; i < mTriangles.size(); ++i)
		{
			NavTriangle* tri = mTriangles[i];
			if (!tri->mPassable)
				continue;
			if (NavPhysics::RayIntersectTriangle(vPos, Vector3::DOWN,
				tri->mPoint[0], tri->mPoint[1], tri->mPoint[2], &hit))
			{
				(*height) = hit.hitPoint.y;
				return true;
			}
		}
		return false;
	}

	void NavMesh::UpdateAdjacent(bool calcBounds)
	{
		for (unsigned int i = 0; i < mTriangles.size(); ++i)
		{
			NavTriangle* tri = mTriangles[i];
			tri->mNeighbors.clear();
			tri->mDistance.clear();
		}
		for (unsigned int i = 0; i < mTriangles.size(); ++i)
		{
			NavTriangle* tri1 = mTriangles[i];
			for (unsigned int j = i + 1; j < mTriangles.size(); ++j)
			{
				NavTriangle* tri2 = mTriangles[j];

				AdjacentEdgePair aep;
				if (IsTriangleAdjacent(tri1, tri2, &aep))
				{
					Vector3 edge = tri1->mCenter - tri2->mCenter;
					float distance = edge.Length();
					int ptIndex1 = -1;
					int ptIndex2 = -1;

					tri1->mNeighbors.push_back(tri2);
					tri1->mDistance.push_back(distance);
					tri1->mShareEdgeIndices.push_back(aep.EncodeFirstEdgeIndex());
					ptIndex1 = aep.firstTriIndex1;
					ptIndex2 = aep.firstTriIndex2;
					Vector3 edgeCenter1 = (tri1->mPoint[ptIndex1] + tri1->mPoint[ptIndex2]) * 0.5f;
					tri1->mEdgeCenter.push_back(edgeCenter1);

					tri2->mNeighbors.push_back(tri1);
					tri2->mDistance.push_back(distance);
					tri2->mShareEdgeIndices.push_back(aep.EncodeSecondEdgeIndex());
					ptIndex1 = aep.secondTriIndex1;
					ptIndex2 = aep.secondTriIndex2;
					Vector3 edgeCenter2 = (tri2->mPoint[ptIndex1] + tri2->mPoint[ptIndex2]) * 0.5f;
					tri2->mEdgeCenter.push_back(edgeCenter2);
				}
			}
		}
		if (!calcBounds)
			return;
		for (unsigned int i = 0; i < mTriangles.size(); ++i)
		{
			NavTriangle* tri = mTriangles[i];

			bool hasEdge[3] { false, false, false };
			for (unsigned int j = 0; j < tri->mShareEdgeIndices.size(); ++j)
			{
				int edgeIndex = tri->mShareEdgeIndices[j];
				hasEdge[edgeIndex] = true;
			}
			for (int j = 0; j < 3; ++j)
			{
				if (hasEdge[j])
					continue;
				int edgeIndex = j;

				int ptIndex1 = -1;
				int ptIndex2 = -1;
				DecodeEdgeIndex(edgeIndex, &ptIndex1, &ptIndex2);

				NavEdge* edge = new NavEdge();
				edge->mPoint[0] = tri->mPoint[ptIndex1];
				edge->mPoint[1] = tri->mPoint[ptIndex2];
				mBounds.push_back(edge);
			}
		}
	}

	bool NavMesh::IsTriangleAdjacent(NavTriangle* tri1, NavTriangle* tri2, AdjacentEdgePair* aep)
	{
		for (int i = 0; i < 3; ++i)
		{
			Vector3& p1 = tri1->mPoint[i];
			for (int j = 0; j < 3; ++j)
			{
				if (aep->secondTriIndex1 == j)
					continue;
				Vector3& p2 = tri2->mPoint[j];

				if (p2 == p1)
				{
					if (aep->secondTriIndex1 >= 0)
					{
						aep->firstTriIndex2 = i;
						aep->secondTriIndex2 = j;
						return true;
					}
					else
					{
						aep->firstTriIndex1 = i;
						aep->secondTriIndex1 = j;
					}
					break;
				}
			}
		}
		return false;
	}

	NavMesh::~NavMesh()
	{
		for (unsigned int i = 0; i < mTriangles.size(); ++i)
		{
			NavTriangle* tri = mTriangles[i];
			SAFE_DELETE(tri);
		}
		mTriangles.clear();

		for (unsigned int i = 0; i < mNavLinkInfos.size(); ++i)
		{
			NavLinkInfo* link = mNavLinkInfos[i];
			SAFE_DELETE(link);
		}
		mNavLinkInfos.clear();

		for (unsigned int i = 0; i < mBounds.size(); ++i)
		{
			NavEdge* edge = mBounds[i];
			SAFE_DELETE(edge);
		}
		mBounds.clear();

		for (unsigned int i = 0; i < mBoundsVolumes.size(); ++i)
		{
			NavBoundsVolume* bv = mBoundsVolumes[i];
			SAFE_DELETE(bv);
		}
		mBoundsVolumes.clear();
	}

	unsigned int NavMesh::GetSize()
	{
		unsigned int size = sizeof(unsigned int);
		for (unsigned int i = 0; i < mTriangles.size(); ++i)
		{
			NavTriangle* tri = mTriangles[i];
			size += tri->GetSize();
		}
		size += sizeof(unsigned int);
		for (unsigned int i = 0; i < mNavLinkInfos.size(); ++i)
		{
			NavLinkInfo* linkInfo = mNavLinkInfos[i];
			size += linkInfo->GetSize();
		}

		bool saveBounds = gNavSystem->GetVersion() >= 102;

		if (saveBounds)
		{
			size += sizeof(unsigned int);
			for (unsigned int i = 0; i < mBounds.size(); ++i)
			{
				size += (sizeof(Vector3) * 2);
			}
		}
		return size;
	}

	unsigned int NavMesh::WriteTo(char* dest, unsigned int ptr)
	{
		unsigned int triCount = (unsigned int)mTriangles.size();
		memcpy(dest + ptr, &triCount, sizeof(unsigned int));
		ptr += sizeof(unsigned int);

		for (unsigned int i = 0; i < triCount; ++i)
		{
			NavTriangle* tri = mTriangles[i];
			ptr = tri->WriteTo(dest, ptr);
		}

		unsigned int linkCount = (unsigned int)mNavLinkInfos.size();
		memcpy(dest + ptr, &linkCount, sizeof(unsigned int));
		ptr += sizeof(unsigned int);

		for (unsigned int i = 0; i < linkCount; ++i)
		{
			NavLinkInfo* link = mNavLinkInfos[i];
			ptr = link->WriteTo(dest, ptr);
		}

		bool saveBounds = gNavSystem->GetVersion() >= 102;

		if (saveBounds)
		{
			unsigned int boundsCount = (unsigned int)mBounds.size();
			memcpy(dest + ptr, &boundsCount, sizeof(unsigned int));
			ptr += sizeof(unsigned int);

			unsigned int edgeSize = sizeof(Vector3) * 2;
			for (unsigned int i = 0; i < mBounds.size(); ++i)
			{
				NavEdge* edge = mBounds[i];
				memcpy(dest + ptr, &edge->mPoint[0], edgeSize);
				ptr += edgeSize;
			}
		}
		return ptr;
	}

	unsigned int NavMesh::ReadFrom(char* src, unsigned int ptr)
	{
		unsigned int triCount = 0;
		memcpy(&triCount, &src[ptr], sizeof(unsigned int));
		ptr += sizeof(unsigned int);

		mMin.Set(FLT_MAX, FLT_MAX, FLT_MAX);
		mMax.Set(-FLT_MAX, -FLT_MAX, -FLT_MAX);
		for (unsigned int i = 0; i < triCount; ++i)
		{
			NavTriangle* tri = new NavTriangle();
			ptr = tri->ReadFrom(src, ptr);
			mTriangles.push_back(tri);

			Vector3 triMax, triMin;
			tri->GetBound(&triMin, &triMax);
			mMin.Set(
				MinFloat(triMin.x, mMin.x),
				MinFloat(triMin.y, mMin.y),
				MinFloat(triMin.z, mMin.z)
				);
			mMax.Set(
				MaxFloat(triMax.x, mMax.x),
				MaxFloat(triMax.y, mMax.y),
				MaxFloat(triMax.z, mMax.z)
				);
		}

		if (gNavSystem->GetVersion() > 100)
		{
			unsigned int linkCount = 0;
			memcpy(&linkCount, &src[ptr], sizeof(unsigned int));
			ptr += sizeof(unsigned int);

			for (unsigned int i = 0; i < linkCount; ++i)
			{
				NavLinkInfo* linkInfo = new NavLinkInfo();
				ptr = linkInfo->ReadFrom(src, ptr);
				mNavLinkInfos.push_back(linkInfo);
			}
		}

		bool calcBounds = gNavSystem->GetVersion() < 102;
		UpdateAdjacent(calcBounds);

		if (!calcBounds)
		{
			unsigned int boundsCount = 0;
			memcpy(&boundsCount, &src[ptr], sizeof(unsigned int));
			ptr += sizeof(unsigned int);
			for (unsigned int i = 0; i < boundsCount; ++i)
			{
				NavEdge* edge = new NavEdge();
				Vector3 v0, v1;
				memcpy(v0.mem, &src[ptr], sizeof(Vector3));
				ptr += sizeof(Vector3);
				memcpy(v1.mem, &src[ptr], sizeof(Vector3));
				ptr += sizeof(Vector3);
				edge->mPoint[0] = v0;
				edge->mPoint[1] = v1;
				mBounds.push_back(edge);
			}
		}

		return ptr;
	}
}