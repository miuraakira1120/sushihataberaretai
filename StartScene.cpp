#include "StartScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "ButtonManager.h"
#include "Engine/IniOperator.h"
#include "Imgui_Obj.h"
#include "Pause.h"
#include "Engine/JsonOperator.h"
#include "Engine/Audio.h"


//�R���X�g���N�^
StartScene::StartScene(GameObject* parent)
	: GameObject(parent, "StartScene"), hPict_(-1), hSound_(-1)
{
}

//������
void StartScene::Initialize()
{

	InstanceManager::AllCreateImage(JsonOperator::TITLE_IMAGE_JSON, instanceList, this);
	InstanceManager::AllCreateButton(JsonOperator::TITLE_BUTTON_JSON, instanceList, this);

	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };	

	JsonOperator::GetJSONFloat(JsonOperator::TITLE_JSON, "ChangeSceneButton", "posX", pos.x);
	JsonOperator::GetJSONFloat(JsonOperator::TITLE_JSON, "ChangeSceneButton", "posY", pos.y);
	pStartButton = ButtonManager::CreateSceneChangeButton(this, pos, SCENE_ID_PLAY, "GameStartButton.png");
	//pStartButton->SetPosition(0,)

	JsonOperator::AppendToJSONFileString(JsonOperator::TITLE_JSON, "sec", "key", "hello");
	JsonOperator::AppendToJSONFileFloat(JsonOperator::TITLE_JSON, "OptionButton", "posX", 100);

	


	
	//�T�E���h�f�[�^�̃��[�h
	hSound_ = Audio::Load("TestHello.wav", false, 1.0f);
	assert(hSound_ >= 0);
}

//�X�V
void StartScene::Update()
{	
	if (Input::IsKeyDown(DIK_2))
	{
		Audio::Play(hSound_);
	}
}

//�`��
void StartScene::Draw()
{
}

//�J��
void StartScene::Release()
{
}