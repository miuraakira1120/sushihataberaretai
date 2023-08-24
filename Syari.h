#pragma once

#include <vector>
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Gauge.h"
#include "PoryLine.h"

#define VERTEX_VLU 8

class OBB;
class RedBox;
class BlueBox;

static const float SYARI_SIZE_X = 0.5f; //シャリのXのサイズ（1倍）
static const float SYARI_SIZE_Y = 0.5f; //シャリのYのサイズ（1倍）
static const float SYARI_SIZE_Z = 1.0f; //シャリのZのサイズ（1倍）
const int BONE_DIRECTION_ARRAY_SIZE = 6;

using std::vector;

static enum  Ver
{
    UP_RIGHT_FRONT = 0,
    UP_RIGHT_BACK,
    UP_LEFT_FRONT,
    UP_LEFT_BACK,
    DOWN_RIGHT_FRONT,
    DOWN_RIGHT_BACK,
    DOWN_LEFT_FRONT,
    DOWN_LEFT_BACK,
    VERTEX_MAX,
};

class Syari : public GameObject
{
    enum ShortDistance
    {
        LEFTEST,
        RIGHTEST,
        FOREMOST,
        INNERMOST,
        SHORT_DISTANCE_MAX
    };

    enum Direction
    {
        TOP = 0,
        BOTOM,
        LEFT,
        RIGHT,
        FRONT,
        BACK,
        DOWN_RIGHT_FRONT,
        DOWN_RIGHT_BACK,
        DOWN_LEFT_FRONT,
        DOWN_LEFT_BACK,
        DIRECTION_MAX
    };

     XMFLOAT3 direction[6] = {
        {  0,  1,  0  }, //上
        {  0, -1,  0  }, //下
        { -1,  0,  0  }, //左
        {  1,  0,  0  }, //右
        {  0 , 0, -1  }, //手前
        {  0,  0,  1  }  //奥
    };

    const float directionDistance[6] = {
        SYARI_SIZE_Y,
        -SYARI_SIZE_Y,
        -SYARI_SIZE_X,
        SYARI_SIZE_X,
        -SYARI_SIZE_Z,
        SYARI_SIZE_Z
    };

    const std::string vertexName[8] = {
        "Vertex_Hight_Right_Front",
        "Vertex_Hight_Right_Back",
        "Vertex_Hight_Left_Front",
        "Vertex_Hight_Left_Back",
        "Vertex_Low_Right_Front",
        "Vertex_Low_Right_Back",
        "Vertex_Low_Left_Front",
        "Vertex_Low_Left_Back"
    };

    const float SYARI_SPEED = 0.25f;//シャリのスピード
    const float ROTATE_SPEED = 0.2f; //シャリの回転のスピード
    const float FALL_SPEED = 0.02f; //落ちるスピード
    const float SPEED_LIMIT = 0.5f;  //落下の速度限界 2->0.5
    const float JUMP_SPEED = 1.0f; //ジャンプのスピード
    const float SPEED_OF_JUMP = 0.4f; //跳躍速度

    const XMVECTOR upRightFrontPos = { 0.5f, 0.5f, 1.0f };//シャリの上右前の位置
    const XMVECTOR upRightBackPos = { 0.5f, 0.5f, -1.0f };//シャリの上右後の位置
    const XMVECTOR upLeftFrontPos = { -0.5f, 0.5f, 1.0f };//シャリの上左前の位置
    const XMVECTOR upLeftBackPos = { -0.5f, 0.5f, -1.0f };//シャリの上左後の位置
    const XMVECTOR downRightFrontPos = { 0.5f, -0.5f, 1.0f };//シャリの下左前の位置
    const XMVECTOR downRightBackPos = { 0.5f, -0.5f, -1.0f };//シャリの下右後の位置
    const XMVECTOR downLeftFrontPos = { -0.5f, -0.5f, 1.0f };//シャリの下左前の位置
    const XMVECTOR downLeftBackPos = { -0.5f, -0.5f, -1.0f };//シャリの下左後の位置

    vector<XMVECTOR> vVertexPos;
    int hModel_;    //モデル番号
    int mode;     //モード
    bool breakFlag = false;
    XMFLOAT3 axisPos;
    XMFLOAT3 prevPos;
    XMFLOAT3 prevBonePos[VERTEX_MAX]; //1f前の角の位置
    bool isGround;   //地面に設置しているか
    XMFLOAT3 upDistanceDifference;

    //ゲージオブジェクト
    Gauge* pGauge_;
    float jumpSpeed;
    PoryLine* pLine;
    int countTime;
    XMVECTOR vMove;
    XMFLOAT3 fMove;

    XMVECTOR flipped;
    XMFLOAT3 prevPosMove;//1f前の自分の位置
public:
    float accel;//今どれだけ加速するか
    XMFLOAT3 fupRightFrontPos;
    XMFLOAT3 vertexBonePos[VERTEX_MAX];
    //コンストラクタ
    Syari(GameObject* parent);

    //デストラクタ
    ~Syari();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //モデルのゲッター
    int GetModelHandle() { return hModel_; }

    /// <summary>
    /// キー操作をまとめる関数
    /// </summary>
    void KeyOperation();

    //ジャンプする
    void Jump();

    //移動する関数
    void Move();

    /// <summary>
    /// 今空中にいるかどうか調べる関数
    /// </summary>
    /// <returns>
    /// 真　空中にいる
    /// 偽　空中にいない
    /// </returns>
    bool isFly();

    //マウスによる回転
    void MoveMouse();

    /// <summary>
    /// OBBと平面の衝突判定
    /// </summary>
    bool OBBvsPlane(OBB& obb, XMFLOAT3 pos, XMVECTOR nomal, float* Len = 0);
     
    //何かに当たった
    //引数：pTarget 当たった相手
    void OnCollision(GameObject* pTarget) override;

    /////セッター
    void SetFlipped(XMVECTOR fl);

    //ゲッター
    XMFLOAT3 GetUpDistanceDifference();

};