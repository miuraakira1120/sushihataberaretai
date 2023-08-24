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


//コンストラクタ
PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"),pos(0), hPict_(-1)
{
}

//初期化
void PlayScene::Initialize()
{
	//ステージを生成
	GameManager::SetNowStage((StageBase*)StageInstantiate<Stage>(this, "stage1-1TrueTest.fbx"));

	//カメラのコントローラーを生成
	Instantiate<Controller>(this);

	//ゴール生成
	Instantiate<Goal>(this);

	//プレイヤーを生成
	//CharacterInstantiate<Player>(this, "syari.fbx");
	Instantiate<Syari>(this);
}

//更新
void PlayScene::Update()
{
	pos += UVSCROLL_SPEED;
}

//描画
void PlayScene::Draw()
{
}

//開放
void PlayScene::Release()
{
}
