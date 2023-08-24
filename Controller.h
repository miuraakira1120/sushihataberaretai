#pragma once
#include "Engine/GameObject.h"

class Controller : public GameObject
{
    XMFLOAT3 cameraAngle;//カメラの初期位置の角度
    float    cameraDistance;
public:
    //コンストラクタ
    Controller(GameObject* parent);

    //デストラクタ
    ~Controller();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //現在位置のゲッター
    XMFLOAT3 GetPosition();

    //向きのゲッター
    XMFLOAT3 GetRotate();

    /// <summary>
    /// コントローラーでカメラを回転させる関数
    /// </summary>
    /// <param name="position">コントローラーの位置を変える</param>
    void SetCameraPos(XMFLOAT3 position);

    /// <summary>
    /// リープを使用してコントローラーでカメラを回転させる関数
    /// </summary>
    /// <param name="position">到達するべき位置</param>
    /// <param name="attenRate">減衰比率(1{等倍 }より0.1の方が減速する)</param>
    void SetCameraLerpPos(XMFLOAT3 position, float attenRate);

    /// <summary>
    /// リープをとFoV使用してコントローラーでカメラを回転させる関数
    /// 動いていたかどうかによってFoVを変更
    /// </summary>
    /// <param name="isMoved">動いていたか</param>
    void ChangeFovMove(bool isMoved);

    /// <summary>
    /// カメラの位置が壁と衝突しているかを返す
    /// </summary>
    /// <returns>衝突しているか</returns>
    bool IsCameraCollision();

    /// <summary>
    /// カメラの距離のセッター
    /// </summary>
    /// <param name="distance">距離</param>
    void SetCameraDistance(float distance);

    /// <summary>
    /// カメラの距離のゲッター
    /// </summary>
    /// <returns>距離</returns>
    float GetCameraDistance();
};

