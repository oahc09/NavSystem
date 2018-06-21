#include "PathFindLogic.h"
#include "Test.h"
#include "NavTriangle.h"
#include "NavGraph.h"
#include "MeshRenderer.h"

#ifdef _CHECK_LEAK
#define new  new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

PathFindLogic::PathFindLogic(Test* test)
{
	mTest = test;
	mShowTriPath = true;
	mSmoothPath = true;
	mCost = 0.0f;
}

PathFindLogic::~PathFindLogic()
{
	if (mTest->mRenderer)
		mTest->mRenderer->ClearPath();
}

void PathFindLogic::OnPick(const Nav::NavTriangle* tri, const Vector3& point, const Nav::NavGraph* graph)
{
	if (mTest->mRenderer == NULL)
		return;
	if (tri == NULL)
	{
		mClickMode = eClickState::eClickState_None;
		ClearPath();
		mCost = 0.0f;
		return;
	}
	mCost = 0.0f;
	if (mStartTri == NULL && mEndTri == NULL)
	{
		mClickMode = eClickState::eClickState_Start;
	}
	if (mStartTri != NULL && mEndTri == NULL)
	{
		mClickMode = eClickState::eClickState_End;
	}
	if (mStartTri != NULL && mEndTri != NULL)
	{
		mClickMode = eClickState::eClickState_Start;
		ClearPath();
	}

	if (mClickMode == eClickState_Start)
	{
		SetPointMesh(tri, point, true);
		return;
	}
	else if (mClickMode == eClickState_End)
	{
		SetPointMesh(tri, point, false);

		const Nav::NavGraph* finder = graph;
		if (mStartTri != NULL && mEndTri != NULL)
		{
			std::vector<Nav::NavTriangle*> findPath;
			float cost;
			if (mShowTriPath)
			{
				if (finder->Solve(mStartTri, mEndTri, &findPath, &cost))
				{
					mTest->mRenderer->SetSelectedPath(findPath);
				}
			}
			std::vector<Vector3> findVectorPath;
			if (finder->Solve(mStartPoint, mEndPoint, &findVectorPath, &cost, mSmoothPath))
			{
				mTest->mRenderer->SetSelectedPath(findVectorPath);
			}
			mCost = cost;
		}

		return;
	}
}

void PathFindLogic::OnGUI()
{
	ImGui::Spacing();
	ImGui::Text(STU("��һ�ε��ģ�ͣ�ȷ��Ѱ·���\n�ڶ��ε��������ȷ��Ѱ·�յ�\n�Զ�����·��").c_str());
	ImGui::Spacing();
	ImGui::Text(STU("Ѱ·���ģ�%f").c_str(), mCost);
	ImGui::Spacing();

	std::string text = mSmoothPath ? "�ر�·��ƽ��" : "����·��ƽ��";
	if (ImGui::Button(STU(text).c_str(), ImVec2(mTest->mLeftUIWidth - 20.0f, 30.0f)))
	{
		mSmoothPath = !mSmoothPath;
	}
}

void PathFindLogic::SetPointMesh(const Nav::NavTriangle* tri, const Vector3& point, bool isStart)
{
	if (mTest->mRenderer == NULL)
		return;
	ID3DXMesh** ppMesh = NULL;
	DWORD color = 0;
	if (isStart)
	{
		mStartTri = (Nav::NavTriangle*)tri;
		mStartPoint = point;
	}
	else
	{
		mEndTri = (Nav::NavTriangle*)tri;
		mEndPoint = point;
	}
	mTest->mRenderer->SetPointMesh(tri->mPoint[0], tri->mPoint[1], tri->mPoint[2], point, isStart);
}

void PathFindLogic::ClearPath()
{
	mStartTri = NULL;
	mEndTri = NULL;
	mClickMode = eClickState_None;

	if (mTest->mRenderer)
		mTest->mRenderer->ClearPath();
}