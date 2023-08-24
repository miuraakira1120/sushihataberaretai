#pragma once
#include "Engine/GameObject.h"
#include "StageBase.h"

//チュートリアルシーンを管理するクラス
class TutorialStage : public StageBase
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="parent">親オブジェクト</param>
	/// <param name="path">表示するモデル</param>
	TutorialStage(GameObject* parent, std::string path);
};
