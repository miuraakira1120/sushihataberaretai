#include "GoalScene.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

//コンストラクタ
GoalScene::GoalScene(GameObject* parent)
	: GameObject(parent, "GoalScene"), hPict_(-1)
{
}

//初期化
void GoalScene::Initialize()
{
	//画像データのロード
	hPict_ = Image::Load("Stage1Crear.png");
	assert(hPict_ >= 0);
}

//更新
void GoalScene::Update()
{
	if (Input::IsKeyDown(DIK_RETURN) || Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_START);
	}
}

//描画
void GoalScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//開放
void GoalScene::Release()
{
}