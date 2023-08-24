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
	//�X�e�[�W�𐶐�
	GameManager::SetNowStage((StageBase*)StageInstantiate<TutorialStage>(this, "Tutorial.fbx"));

	//�J�����̃R���g���[���[�𐶐�
	Instantiate<Controller>(this);

	//�v���C���[�𐶐�
	CharacterInstantiate<Player>(this, "syari.fbx");
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