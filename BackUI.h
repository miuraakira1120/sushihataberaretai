#pragma once
#pragma once
#include "Engine/GameObject.h"

//UIの背景
class BackUI : public GameObject
{
    int hPict_;

public:
    //コンストラクタ
    BackUI(GameObject* parent);

    //デストラクタ
    ~BackUI();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};