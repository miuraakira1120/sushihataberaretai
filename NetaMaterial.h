#pragma once
#include "Engine/GameObject.h"

class ModelBase;

//ネタの素クラス
class NetaMaterial : public GameObject
{
protected:
    const float     MODEL_ALPHA = 0.2f;                             //モデルのアルファ値
    const float     INTERNAL_MODEL_SCALE = 0.5f;                    //内部に入れるモデルの大きさ
    const float     SPHERE_SIZE = 1.0f;                             //このモデルのサイズ
    const XMFLOAT3  INTERNAL_MODEL_ROTATE = { 0.0f, 0.3f, 0.0f };   //内部に入れるモデルの回転速度 

    int hModel_;                    //モデル番号
    ModelBase* pInternalModel;      //内部に入れるモデルのポインタ
    std::string internalModelPath;  //内部に入れるモデルのパス
    std::string internalModelType;  //取ると何のネタを乗せるのか
    

public:
    //コンストラクタ
    NetaMaterial(GameObject* parent);
    NetaMaterial(GameObject* parent, std::string fileName);

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

    //何かに当たった
   //引数：pTarget 当たった相手
    virtual void OnCollision(GameObject* pTarget);
};