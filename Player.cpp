#include "Player.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "ImageBase.h"
#include "GameManager.h"


Player::Player(GameObject* parent, std::string pathName)
	:PlayerBase(parent, "Player", pathName)
{

}

//更新
void Player::Update()
{
	//ボタンの処理
	//もしプレイヤーが入力を受け付けていたら
	if(GetCanMove())
	{
		//移動
		//左クリックで移動
		if (Input::IsMouseButton(0))
		{
			Move();
		}

		//移動
		//右クリックでバック移動
		if (Input::IsMouseButton(1))
		{
			Move(true);
		}

		//ジャンプ
		//スペースでジャンプ
		if (Input::IsKeyDown(DIK_SPACE))
		{
			Jump(); 
		}
	}

	//重力の処理
	Gravity();

	//ステージ関連の処理
	{
		//ステージのモデルを取得
		StageBase* pStage = GameManager::GetNowStage();    //ステージオブジェクトを探す
		int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得

		//姿勢を地面の法線に添わせる
		PostureGroundFollow(hGroundModel);

		//地面にめり込んだ時の処理
		RevertProcess(hGroundModel);
	}
	
	//このオブジェクトにカメラをセットする
	SetCameraController();
}
