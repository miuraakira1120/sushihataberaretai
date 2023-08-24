#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Engine/GameObject.h"

class PlayScene : public GameObject
{

	//const XMFLOAT3 UVSCROLL_SPEED = { 0.1f, 0.1f, 0.0f };
	const float UVSCROLL_SPEED = 0.1f;

	struct ConstantBuffer
	{
		XMMATRIX	dummy_;		// 空
		float		pos;		// uvの移動する位置
	};

	float pos;
	Microsoft::WRL::ComPtr<ID3D11Buffer>pConstantBuffer_;	//コンスタントバッファ

	int hPict_;					//画像番号

public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	PlayScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};