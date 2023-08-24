#include "PlayScene.h"
#include "Syari.h"
#include "Maguro.h"
#include "Stage.h"
#include "Controller.h"
#include "RedBox.h"
#include "BlueBox.h"
#include "Goal.h"
#include "Engine/Camera.h"
#include "Cannon.h"
#include "SalmonRoe.h"
#include "Engine/Image.h"
#include "Player.h"
#include "ImageBase.h"
#include "GameManager.h"


//�R���X�g���N�^
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),pos(0), hPict_(-1)
{
}

//������
void PlayScene::Initialize()
{
	//�X�e�[�W�𐶐�
	GameManager::SetNowStage((StageBase*)StageInstantiate<Stage>(this, "stage1-1TrueTest.fbx"));

	//�J�����̃R���g���[���[�𐶐�
	Instantiate<Controller>(this);

	//�S�[������
	Instantiate<Goal>(this);

	//�v���C���[�𐶐�
	//CharacterInstantiate<Player>(this, "syari.fbx");
	Instantiate<Syari>(this);
}

//�X�V
void PlayScene::Update()
{
	pos += UVSCROLL_SPEED;
}

//�`��
void PlayScene::Draw()
{
}

//�J��
void PlayScene::Release()
{
}
