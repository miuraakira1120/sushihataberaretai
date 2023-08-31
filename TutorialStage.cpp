#include "TutorialStage.h"
#include "NetaMaterial.h"

//�R���X�g���N�^
TutorialStage::TutorialStage(GameObject* parent, std::string path)
	: StageBase(parent, "TutorialStage", path)
{
}

//�X�V�O�Ɉ�x�����Ă΂��
void TutorialStage::SetUp()
{
	//NetaMaterial* pNetaMaterial = Instantiate<NetaMaterial>(this);
	NetaMaterial* pNetaMaterial = NetaMaterialInstantiate<NetaMaterial>(this, "maguro.fbx");
	pNetaMaterial->SetPosition(4, 0, 4);
}
