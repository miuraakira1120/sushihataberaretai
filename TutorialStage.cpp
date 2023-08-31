#include "TutorialStage.h"
#include "NetaMaterial.h"

//コンストラクタ
TutorialStage::TutorialStage(GameObject* parent, std::string path)
	: StageBase(parent, "TutorialStage", path)
{
}

//更新前に一度だけ呼ばれる
void TutorialStage::SetUp()
{
	//NetaMaterial* pNetaMaterial = Instantiate<NetaMaterial>(this);
	NetaMaterial* pNetaMaterial = NetaMaterialInstantiate<NetaMaterial>(this, "maguro.fbx");
	pNetaMaterial->SetPosition(4, 0, 4);
}
