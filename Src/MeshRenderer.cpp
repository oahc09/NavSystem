#include "MeshRenderer.h"
#include "NavTriangle.h"
#include "NavHeightmap.h"

struct MeshVertex
{
	D3DXVECTOR3 pos;
	DWORD color;

	static const int fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;
};

MeshRenderer::MeshRenderer(IDirect3DDevice9* device, FBXHelper::FBXMeshDatas* mDatas)
{
	mDevice = device;
	mShowNavMesh = true;
	mShowWireMesh = true;
	mShowHeightmap = false;

	if (mDatas == NULL)
		return;
	for (size_t i = 0; i < mDatas->datas.size(); ++i)
	{
		FBXHelper::FBXMeshData* data = mDatas->datas[i];
		
		DWORD faceNum = (DWORD)(data->indices.size() / 3);
		DWORD vertexNum = (DWORD)data->pos.size();
		{
			ID3DXMesh* mesh = NULL;
			HRESULT hr = D3DXCreateMeshFVF(faceNum, vertexNum, D3DXMESH_32BIT, MeshVertex::fvf, mDevice, &mesh);
			if (FAILED(hr))
				continue;
			mMeshes.push_back(mesh);
			mHeightMeshes.push_back(NULL);

			MeshVertex* vb = NULL;
			mesh->LockVertexBuffer(NULL, (void**)&vb);
			for (size_t j = 0; j < data->pos.size(); ++j)
			{
				vb[j].pos = data->pos[j];
				vb[j].color = 0xffffffff;
			}
			//memcpy(vb, &data->pos[0], vertexNum * sizeof(D3DXVECTOR3));
			mesh->UnlockVertexBuffer();

			void* ib = NULL;
			mesh->LockIndexBuffer(NULL, &ib);
			memcpy(ib, &data->indices[0], faceNum * 3 * sizeof(unsigned int));
			mesh->UnlockIndexBuffer();
		}
		{
			ID3DXMesh* mesh = NULL;
			HRESULT hr = D3DXCreateMeshFVF(faceNum, vertexNum, D3DXMESH_32BIT, MeshVertex::fvf, mDevice, &mesh);
			if (FAILED(hr))
				continue;
			mWireMeshes.push_back(mesh);

			MeshVertex* vb = NULL;
			mesh->LockVertexBuffer(NULL, (void**)&vb);
			for (size_t j = 0; j < data->pos.size(); ++j)
			{
				vb[j].pos = data->pos[j];
				vb[j].color = 0xff000000;
			}
			//memcpy(vb, &data->pos[0], vertexNum * sizeof(D3DXVECTOR3));
			mesh->UnlockVertexBuffer();

			void* ib = NULL;
			mesh->LockIndexBuffer(NULL, &ib);
			memcpy(ib, &data->indices[0], faceNum * 3 * sizeof(unsigned int));
			mesh->UnlockIndexBuffer();
		}
	}

	mStartMesh = NULL;
	mEndMesh = NULL;
	mSelectedMesh = NULL;
}

MeshRenderer::~MeshRenderer()
{
	mDevice = NULL;
	for (size_t i = 0; i < mMeshes.size(); ++i)
	{
		ID3DXMesh* mesh = mMeshes[i];
		SAFE_RELEASE(mesh);
	}
	mMeshes.clear();

	for (size_t i = 0; i < mWireMeshes.size(); ++i)
	{
		ID3DXMesh* mesh = mWireMeshes[i];
		SAFE_RELEASE(mesh);
	}
	mWireMeshes.clear();

	for (size_t i = 0; i < mHeightMeshes.size(); ++i)
	{
		ID3DXMesh* mesh = mHeightMeshes[i];
		SAFE_RELEASE(mesh);
	}
	mHeightMeshes.clear();

	SAFE_RELEASE(mStartMesh);
	SAFE_RELEASE(mEndMesh);
	SAFE_RELEASE(mSelectedMesh);
	mSelectedPath.clear();
}

void MeshRenderer::Render()
{
	if (mShowNavMesh)
	{
		for (size_t i = 0; i < mMeshes.size(); ++i)
		{
			ID3DXMesh* mesh = mMeshes[i];
			if (!mesh)
			{
				continue;
			}
			mesh->DrawSubset(0);
		}
	}
	
	if (mShowHeightmap)
	{
		for (size_t i = 0; i < mHeightMeshes.size(); ++i)
		{
			ID3DXMesh* mesh = mHeightMeshes[i];
			if (!mesh)
			{
				continue;
			}
			mesh->DrawSubset(0);
		}
	}

	if (mShowWireMesh)
	{
		mDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		mDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		mDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		for (size_t i = 0; i < mWireMeshes.size(); ++i)
		{
			ID3DXMesh* mesh = mWireMeshes[i];
			if (!mesh)
			{
				continue;
			}
			mesh->DrawSubset(0);
		}
		mDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		mDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		mDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	if (mSelectedMesh)
		mSelectedMesh->DrawSubset(0);

	if (mStartMesh)
		mStartMesh->DrawSubset(0);
	if (mEndMesh)
		mEndMesh->DrawSubset(0);

	if (mSelectedPath.size() > 0)
	{
		mDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		mDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
		mDevice->SetFVF(MeshVertex::fvf);
		mDevice->DrawPrimitiveUP(D3DPT_LINELIST, mSelectedPath.size() / 2, (void*)&mSelectedPath[0], sizeof(MeshVertex));
		mDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		mDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}
}

void MeshRenderer::SetPointMesh(const Vector3& pt0, const Vector3& pt1, const Vector3& pt2, const Vector3& point, bool isStart)
{
	ID3DXMesh** ppMesh = NULL;
	DWORD color = 0;
	if (isStart)
	{
		ppMesh = &mStartMesh;
		color = 0xffff00ff;
	}
	else
	{
		ppMesh = &mEndMesh;
		color = 0xff0000ff;
	}

	HRESULT hr = D3DXCreateMeshFVF(1, 3, D3DXMESH_32BIT, MeshVertex::fvf, mDevice, ppMesh);
	if (FAILED(hr))
		return;
	MeshVertex* vb = NULL;
	(*ppMesh)->LockVertexBuffer(NULL, (void**)&vb);
	{
		MeshVertex& v0 = vb[0];
		v0.color = color;
		v0.pos = *(D3DXVECTOR3*)(&pt0);
		MeshVertex& v1 = vb[1];
		v1.color = color;
		v1.pos = *(D3DXVECTOR3*)(&pt1);
		MeshVertex& v2 = vb[2];
		v2.color = color;
		v2.pos = *(D3DXVECTOR3*)(&pt2);
	}
	(*ppMesh)->UnlockVertexBuffer();

	unsigned int* ib = NULL;
	(*ppMesh)->LockIndexBuffer(NULL, (void**)&ib);
	{
		ib[0] = 0;
		ib[1] = 1;
		ib[2] = 2;
	}
	(*ppMesh)->UnlockIndexBuffer();
}

void MeshRenderer::SetSelectedPath(const std::vector<NavTriangle*>& tris)
{
	SAFE_RELEASE(mSelectedMesh);

	size_t count = tris.size() * 3;
	HRESULT hr = D3DXCreateMeshFVF(tris.size(), count, D3DXMESH_32BIT, MeshVertex::fvf, mDevice, &mSelectedMesh);
	if (FAILED(hr))
		return;

	MeshVertex* vb = NULL;
	mSelectedMesh->LockVertexBuffer(NULL, (void**)&vb);
	for (size_t i = 0; i < tris.size(); ++i)
	{
		NavTriangle* t = tris[i];
		MeshVertex& v0 = vb[i * 3];
		v0.color = 0xffff0000;
		v0.pos = *(D3DXVECTOR3*)(&t->mPoint[0]);
		MeshVertex& v1 = vb[i * 3 + 1];
		v1.color = 0xffff0000;
		v1.pos = *(D3DXVECTOR3*)(&t->mPoint[1]);
		MeshVertex& v2 = vb[i * 3 + 2];
		v2.color = 0xffff0000;
		v2.pos = *(D3DXVECTOR3*)(&t->mPoint[2]);
	}
	mSelectedMesh->UnlockVertexBuffer();

	unsigned int* ib = NULL;
	mSelectedMesh->LockIndexBuffer(NULL, (void**)&ib);
	for (size_t i = 0; i < tris.size(); ++i)
	{
		ib[i * 3] = i * 3;
		ib[i * 3 + 1] = i * 3 + 1;
		ib[i * 3 + 2] = i * 3 + 2;
	}
	mSelectedMesh->UnlockIndexBuffer();
}

void MeshRenderer::SetSelectedPath(const std::vector<Vector3>& path)
{
	mSelectedPath.clear();

	for (size_t i = 0; i < path.size() - 1; ++i)
	{
		Vector3 v0 = path[i];
		Vector3 v1 = path[i + 1];

		MeshVertex mv0;
		mv0.pos = *(D3DXVECTOR3*)(&v0);
		mv0.color = 0xff000000;
		MeshVertex mv1;
		mv1.pos = *(D3DXVECTOR3*)(&v1);
		mv1.color = 0xff000000;

		mSelectedPath.push_back(mv0);
		mSelectedPath.push_back(mv1);
	}
}

void MeshRenderer::SetHeightmap(const NavHeightmap* heightmap, size_t index)
{
	int verticesCount = (heightmap->mSizeX + 1) * (heightmap->mSizeZ + 1);
	int faceCount = heightmap->mSizeX * heightmap->mSizeZ * 2;
	ID3DXMesh* mesh = NULL;
	HRESULT hr = D3DXCreateMeshFVF(faceCount, verticesCount, D3DXMESH_32BIT, MeshVertex::fvf, mDevice, &mesh);
	if (FAILED(hr))
		return;
	MeshVertex* vb = NULL;
	mesh->LockVertexBuffer(NULL, (void**)&vb);
	for (int i = 0; i < verticesCount; ++i)
	{
		MeshVertex& v = vb[i];
		int ix = i % (heightmap->mSizeX + 1);
		int iz = i / (heightmap->mSizeX + 1);
		v.pos.x = heightmap->mMin.x + heightmap->mCellSize.x * (float)ix;
		v.pos.z = heightmap->mMin.y + heightmap->mCellSize.y * (float)iz;
		v.pos.y = heightmap->mHeights[i];

		v.color = 0xff00ffff;
	}
	mesh->UnlockVertexBuffer();

	unsigned int* ib = NULL;
	mesh->LockIndexBuffer(NULL, (void**)&ib);
	memset(ib, 0, faceCount * 3 * sizeof(unsigned int));
	int cellCount = faceCount / 2;
	int indexIB = -1;
	for (int i = 0; i < cellCount; ++i)
	{
		if (heightmap->mCellPassability[i] == 0)
			continue;
		int col = i % heightmap->mSizeX;
		int row = i / heightmap->mSizeX;

		unsigned int index0 = row * (heightmap->mSizeX + 1) + col;
		unsigned int index1 = row * (heightmap->mSizeX + 1) + col + 1;
		unsigned int index2 = (row + 1) * (heightmap->mSizeX + 1) + col;
		unsigned int index3 = (row + 1) * (heightmap->mSizeX + 1) + col + 1;

		ib[++indexIB] = index0; ib[++indexIB] = index1; ib[++indexIB] = index2;
		ib[++indexIB] = index3; ib[++indexIB] = index2; ib[++indexIB] = index1;
	}
	mesh->UnlockIndexBuffer();
	mHeightMeshes.push_back(mesh);
}

void MeshRenderer::ClearPath()
{
	SAFE_RELEASE(mStartMesh);
	SAFE_RELEASE(mEndMesh);
	SAFE_RELEASE(mSelectedMesh);
	mSelectedPath.clear();
}