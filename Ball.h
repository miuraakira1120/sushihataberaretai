#pragma once
#include "Engine/GameObject.h"


//◆◆◆を管理するクラス
class Ball : public GameObject
{
    //定数
    const float SPEED_LIMIT = 2.0f;  //落下の速度限界
    const float FALL_SPEED = 0.02f; //落ちるスピード
    const float BALL_SIZE = 0.5f;

    int hModel_;    //モデル番号
    XMFLOAT3 fMove;
    bool isGround;   //地面に設置しているか
    float accel;//今どれだけ加速するか
    bool isPrevRayHit;
    int count;

    XMVECTOR vMoved;

    XMFLOAT3 prevPos;//
public:
    //コンストラクタ
    Ball(GameObject* parent);

    //デストラクタ
    ~Ball();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //セッター
    void SetMove(XMFLOAT3 move);
    void SetPosition(XMFLOAT3 pos);

};