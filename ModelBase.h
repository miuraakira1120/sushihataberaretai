#pragma once
#include "Engine/GameObject.h"

//モデルのベースを管理するクラス
class ModelBase : public GameObject
{
    int hModel_;    //モデル番号
    float scroll;
public:
    //コンストラクタ
    ModelBase(GameObject* parent, std::string filename);

    //デストラクタ
    ~ModelBase();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};