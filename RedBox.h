#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class RedBox : public GameObject
{
    int hModel_;    //モデル番号
public:
    //コンストラクタ
    RedBox(GameObject* parent);

    //デストラクタ
    ~RedBox();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    void SetPosition(XMFLOAT3 pos_);
};