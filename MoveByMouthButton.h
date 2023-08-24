#pragma once
#include <string>
#include "Button.h"

class MoveByMouthButton : public Button
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	MoveByMouthButton(GameObject* parent, std::string fileName);

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// ボタンが押された時の処理
	/// </summary>
	void Event() override;

	/// <summary>
	/// Update関数の前に呼ばれる関数
	/// </summary>
	void PreUpdate() override;
};

