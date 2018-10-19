#include "GraphEditLogic.h"
#include "Test.h"
#include "NavTriangle.h"
#include "NavGraph.h"
#include "MeshRenderer.h"
#include "NavSystem.h"

#ifdef _CHECK_LEAK
#define new  new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

GraphEditLogic::GraphEditLogic(Test* test)
{
	mTest = test;
	mGraph = NULL;
	mID = 0;
}

GraphEditLogic::~GraphEditLogic()
{

}

void GraphEditLogic::OnPick(const Nav::NavTriangle* tri, const Nav::Vector3& point, const Nav::NavGraph* graph)
{
	if (mGraph == graph || graph == NULL)
		return;
	mGraph = (Nav::NavGraph*)graph;
	mID = mGraph->mID;
	mTest->mRenderer->SetEditGraph(mGraph);
}

static bool isOpenTip = false;
void GraphEditLogic::OnGUI()
{
	if (mGraph == NULL)
		return;
	int sceneID = (int)mID / 100;
	int layerID = (int)mID % 100;
	ImGui::Text(STU("����ID").c_str());
	ImGui::SameLine();
	ImGui::InputInt("#graphSceneID", &sceneID);

	ImGui::Text(STU("�㼶ID").c_str());
	ImGui::SameLine();
	ImGui::InputInt("#graphLayerID", &layerID);

	mID = sceneID * 100 + layerID;

	if (ImGui::BeginPopupModal(STU("����").c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text(STU("�㼶�Ѵ�����������д�㼶").c_str());
		ImGui::Separator();
		if (ImGui::Button(STU("��").c_str(), ImVec2(60, 24)))
		{
			isOpenTip = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}

	if (isOpenTip)
	{
		ImGui::OpenPopup(STU("����").c_str());
	}

	if (ImGui::Button(STU("ȷ��").c_str(), ImVec2(mTest->mLeftUIWidth - 20.0f, 30.0f)))
	{
		if (NULL != mTest->mNavSystem->GetGraphByID(mID))
		{
			isOpenTip = true;
			return;
		}

		mTest->mNavSystem->ResetGraphID(mGraph->mID, mID);

		mGraph = (Nav::NavGraph*)NULL;
		mTest->mRenderer->SetEditGraph(mGraph);
		return;
	}

	if (ImGui::Button(STU("ȡ��").c_str(), ImVec2(mTest->mLeftUIWidth - 20.0f, 30.0f)))
	{
		mGraph = (Nav::NavGraph*)NULL;
		mTest->mRenderer->SetEditGraph(mGraph);
		return;
	}
}