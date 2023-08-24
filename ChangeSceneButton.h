#pragma once
#include <string>
#include "Button.h"
#include "Engine/SceneManager.h"

class ChangeSceneButton : public Button
{
private:
	const XMFLOAT3 IMAGE_SIZE_DEF = { 1.0f, 1.0f, 1.0f };
	const XMFLOAT3 IMAGE_SIZE_MAG = { 1.1f, 1.1f, 1.0f };

	SCENE_ID changeSceneName;

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	ChangeSceneButton(GameObject* parent, SCENE_ID name, std::string fileName);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// ボタンが押された時の処理
	/// </summary>
	void Event() override;

	/// <summary>
	/// 遷移先のシーンの名前のセッター
	/// </summary>
	/// <param name="name"></param>
	void SetChangeSceneName(SCENE_ID name);

	/// <summary>
	/// Update関数の前に呼ばれる関数
	/// </summary>
	void PreUpdate() override;
};

