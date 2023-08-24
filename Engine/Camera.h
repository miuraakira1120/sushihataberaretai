#pragma once
#include "GameObject.h"

//-----------------------------------------------------------
//カメラ
//-----------------------------------------------------------
namespace Camera
{

	//初期化（プロジェクション行列作成）
	void Initialize();

	//更新（ビュー行列作成）
	void Update();

	//視点（カメラの位置）を設定
	void SetPosition(XMFLOAT3 position);

	//焦点（見る位置）を設定
	void SetTarget(XMFLOAT3 target);

	//位置を取得
	XMFLOAT3 GetPosition();

	//焦点を取得
	XMFLOAT3 GetTarget();

	//ビュー行列を取得
	XMMATRIX GetViewMatrix();

	//プロジェクション行列を取得
	XMMATRIX GetProjectionMatrix();

	void SetViewFlag(int flag);

	/// <summary>
	/// 視野角の設定(度数法)
	/// </summary>
	/// <param name="fov"></param>
	void SetFOV(float fov);

	//ビルボード用回転行列を取得
	XMMATRIX GetBillboardMatrix();

	/// <summary>
	/// ワールド座標をスクリーン座標に変換
	/// </summary>
	/// <returns>変換後の座標</returns>
	/// 
	
	/// <summary>
	/// ワールド座標をスクリーン座標に変換
	/// </summary>
	/// <param name="position">ワールド座標</param>
	/// <returns>変換後の座標</returns>
	XMFLOAT3 ToWorldCalcScreen(XMFLOAT3 position);
};