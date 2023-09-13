#include "TutorialScene.h"
#include "GameManager.h"
#include "TutorialStage.h"
#include "Engine/Camera.h"
#include "Controller.h"
#include "Player.h"

//�R���X�g���N�^
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene")
{
}

//������
void TutorialScene::Initialize()
{
	//�v���C���[�𐶐�
	CharacterInstantiate<Player>(this, "syari.fbx")->SetPosition(0,30,0);

	//�X�e�[�W�𐶐�
	GameManager::SetNowStage((StageBase*)StageInstantiate<TutorialStage>(this, "Stage1.fbx"));

	//�J�����̃R���g���[���[�𐶐�
	Instantiate<Controller>(this);
}

//�X�V
void TutorialScene::Update()
{

}

//�`��
void TutorialScene::Draw()
{
}

//�J��
void TutorialScene::Release()
{
}