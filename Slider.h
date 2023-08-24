#pragma once
#include "Engine/GameObject.h"
#include "Button.h"

//◆◆◆を管理するクラス
class Slider : public Button
{
	const std::string DEF_CHILD_PATH = "testButton.png";
	std::string childPathName;//スライダーのボタンの画像ファイル名

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	/// <param name="fileName">スライダーの画像</param>
	Slider(GameObject* parent, std::string fileName);

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	/// <param name="fileName">スライダーの画像</param>
	/// <param name="childFileName">スライダーのボタンの画像</param>
	Slider(GameObject* parent, std::string fileName, std::string childFileName);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// ボタンが押された時の処理
	/// </summary>
	void Event() override;

};

