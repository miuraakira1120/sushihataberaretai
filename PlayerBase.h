#pragma once
#include <DirectXMath.h>
#include <vector>
#include "Engine/GameObject.h"
#include "Engine/Direct3D.h"

class Controller;

using namespace DirectX;

//プレイヤーのサイズ
const XMFLOAT3 PLAYER_SIZE{
    0.5f,        //シャリのXのサイズ（1倍）
    0.5f,        //シャリのYのサイズ（1倍）
    1.0f,        //シャリのZのサイズ（1倍）
};

class PlayerBase : public GameObject
{
private:

    //フラグ
    struct STATE
    {
        bool  isGround;              //地面に設置しているか
        bool  canMove;               //動くことができるか
        bool  isCamControll;         //カメラをこのオブジェクトで制御するか

        STATE() 
        { 
            isGround        = false; 
            canMove         = true;
            isCamControll   = true;
        }
    }state_;

    int   hModel_;               //モデル番号
    float gravity;               //今受けている重力の力(マイナスなら重力を振り切って上に行く)
    XMFLOAT3 size;               //プレイヤーのサイズ
    Direct3D::SHADER_TYPE type;  //描画に使用するシェーダー
    Controller* pController;
    XMFLOAT3 prevPos;            //前のフレームの位置

public:

    //コンストラクタ
    PlayerBase(GameObject* parent, std::string name, std::string pathName);

    //初期化
    virtual void Initialize() {};

    //更新
    virtual void Update() {};

    //描画
    virtual void Draw();

    //開放
    virtual void Release() {};

    //セットアップする関数
    virtual void SetUp();

    //何かに当たった
    //引数：pTarget 当たった相手
    virtual void OnCollision(GameObject* pTarget) {};

    //ジャンプする
    void Jump();

    /// <summary>
    /// 移動する関数
    /// </summary>
    /// <param name="isInverse">バックするかどうか</param>
    void Move(bool isInverse = false);

    /// <summary>
    /// 移動する関数
    /// </summary>
    /// <param name="accel">どれくらい進むか</param>
    /// /// <param name="isInverse">バックするかどうか</param>
    void Move(float accel, bool isInverse = false);

    //モデルのゲッター
    int GetModelHandle() { return hModel_; }

    //重力の処理
    void Gravity();

    /// <summary>
    /// 衝突しているか調べる
    /// </summary>
    /// <param name="hStageModel">ステージのモデル</param>
    /// <param name="vec">レイを飛ばす方向</param>
    /// <param name="rayPos">レイをどこから飛ばすか</param>
    /// <param name="length">戻す距離</param>
    /// <returns>衝突したかどうか</returns>
    bool CheckIfCollided(int hStageModel, XMFLOAT3 vec,XMFLOAT3 rayPos, float &length);
    
    /// <summary>
    /// 姿勢を地面の法線に添わせる
    /// </summary>
    /// <param name="hStageModel">ステージのモデル</param>
    void PostureGroundFollow(int hStageModel);

    /// <summary>
    /// このオブジェクトにカメラをセットする
    /// </summary>
    void SetCameraController(XMFLOAT3 ShiftPos = XMFLOAT3(0.0f,0.0f,0.0f));


    /// <summary>
    /// 地面にめり込んだ時の処理
    /// </summary>
    /// <param name="hStageModel">ステージのモデル</param>
    void RevertProcess(int hStageModel);

    //state_の各ゲッター、セッター
    void SetIsGround(bool a) { state_.isGround = a; }
    void SetIsCamControll(bool a) { state_.isCamControll = a; }
    void SetCanMove(bool a) { state_.canMove = a; }

    bool GetIsGround() { return state_.isGround; }
    bool GetIsCamControll() { return state_.isCamControll; }
    bool GetCanMove() { return state_.canMove; }
};

