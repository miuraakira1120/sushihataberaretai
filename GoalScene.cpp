#include "GoalScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
GoalScene::GoalScene(GameObject* parent)
	: GameObject(parent, "GoalScene"), hPict_(-1)
{
}

//������
void GoalScene::Initialize()
{
	//�摜�f�[�^�̃��[�h
	hPict_ = Image::Load("Stage1Crear.png");
	assert(hPict_ >= 0);
}

//�X�V
void GoalScene::Update()
{
	if (Input::IsKeyDown(DIK_RETURN) || Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_START);
	}
}

//�`��
void GoalScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void GoalScene::Release()
{
}