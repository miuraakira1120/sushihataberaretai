#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class Cannon : public GameObject
{
    int hModel_;    //モデル番号
    const float CANNON_SIZE_Y = 1.0f;
    unsigned int timer;
public:
    //コンストラクタ
    Cannon(GameObject* parent);

    //デストラクタ
    ~Cannon();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};