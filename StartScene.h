#pragma once
#include "Engine/GameObject.h"
#include <vector>



//スタートシーンを管理するクラス
class StartScene : public GameObject
{
	int hSound_;    //サウンド番号
	int hPict_;    //画像番号
	int iniListButton;//タイトルシーンのボタンの番号

	GameObject* pStartButton;

	std::vector<GameObject*> instanceList;
	
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	StartScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
};
