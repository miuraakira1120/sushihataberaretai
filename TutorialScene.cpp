#include "TutorialScene.h"
#include "GameManager.h"
#include "TutorialStage.h"
#include "Engine/Camera.h"
#include "Controller.h"
#include "Player.h"

//コンストラクタ
TutorialScene::TutorialScene(GameObject* parent)
	: GameObject(parent, "TutorialScene")
{
}

//初期化
void TutorialScene::Initialize()
{
	//プレイヤーを生成
	CharacterInstantiate<Player>(this, "syari.fbx")->SetPosition(0,30,0);

	//ステージを生成
	GameManager::SetNowStage((StageBase*)StageInstantiate<TutorialStage>(this, "Stage1.fbx"));

	//カメラのコントローラーを生成
	Instantiate<Controller>(this);
}

//更新
void TutorialScene::Update()
{

}

//描画
void TutorialScene::Draw()
{
}

//開放
void TutorialScene::Release()
{
}