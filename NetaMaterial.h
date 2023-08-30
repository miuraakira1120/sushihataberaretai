#pragma once
#include "Engine/GameObject.h"

class ModelBase;

//◆◆◆を管理するクラス
class NetaMaterial : public GameObject
{
protected:
    const float MODEL_ALPHA = 0.2f;//モデルのアルファ値
    const float INTERNAL_MODEL_SCALE = 0.5f;//内部に入れるモデルの大きさ
    const XMFLOAT3 INTERNAL_MODEL_ROTATE = { 0.0f, 0.1f, 0.0f };//内部に入れるモデルの回転速度

    int hModel_;                //モデル番号
    ModelBase* pInternalModel; //内部に入れるモデルのポインタ
    std::string internalModelPath;//内部に入れるモデルのパス

public:
    //コンストラクタ
    NetaMaterial(GameObject* parent);

    //デストラクタ
    ~NetaMaterial();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;
};