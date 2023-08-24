#pragma once
#include "Engine/GameObject.h"
#include "StageBase.h"

//チュートリアルシーンを管理するクラス
class Stage : public StageBase
{
public:

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="parent">親オブジェクト</param>
    /// <param name="path">表示するモデル</param>
    Stage(GameObject* parent, std::string path);

    //更新前に呼ぶ関数
    void SetUp() override;
};

