#pragma once
#include "Engine/GameObject.h"

//◆◆◆を管理するクラス
class SalmonRoe : public GameObject
{
    const float SALMONROE_SIZE_Y = 0.6;
    int hModel_;    //モデル番号
public:
    //コンストラクタ
    SalmonRoe(GameObject* parent);

    //デストラクタ
    ~SalmonRoe();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};