#include "Player.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "ImageBase.h"
#include "GameManager.h"
#include "Engine/BoxCollider.h"
#include "VFX.h"


Player::Player(GameObject* parent, std::string pathName)
	:PlayerBase(parent, "Player", pathName)
{
}

//初期化
void Player::Initialize()
{
	//コライダーをつける(PLAYER_SIZEは半径のため2倍に)
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), Math::Float3Mul( PLAYER_SIZE, TWICE));
	AddCollider(collision);
}

//更新
void Player::Update()
{
	//ネタを一つ以下に保つ処理
	NetaSingleton();

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

		if (Input::IsKeyDown(DIK_G))
		{
			EmitterData ed;
			ed.textureFileName = "PaticleAssets/star.png";
			ed.delay = 0;
			ed.number = 6;
			ed.lifeTime = 20;
			ed.direction = XMFLOAT3(0, 1, 0);
			ed.directionRnd = XMFLOAT3(90, 90, 0);
			ed.speed = 00.1f;
			ed.speedRnd = 0.8;
			ed.sizeRnd = XMFLOAT2(0.4, 0.4);
			ed.scale = XMFLOAT2(1.05, 1.05);
			ed.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);

			ed.color = XMFLOAT4(1, 1, 0.1, 1);
			ed.size = XMFLOAT2(0.65, 0.65);
			ed.position = XMFLOAT3(0, 0, 0);
			ed.rotateRnd = XMFLOAT3(0, 0, 0);
			

			VFX::Start(ed);
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

//ネタを一つ以下に保つ処理
void Player::NetaSingleton()
{
	GameObject* pTmp = nullptr;
	//もしNetaクラスを継承した子オブジェクトが2つ以上になったら
	for (auto it = this->GetChildList()->begin(); it != this->GetChildList()->end(); ++it)
	{
		//タグがネタなら
		if ((*it)->GetTag() == "neta")
		{
			if (pTmp == nullptr)
			{
				pTmp = (*it);
			}
			else
			{
				pTmp->KillMe();
			}
		}
	}
}
