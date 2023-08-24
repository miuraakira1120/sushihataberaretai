#include "Controller.h"
#include "Engine/Camera.h"
#include "Engine/Input.h"
#include "Syari.h"
#include "Maguro.h"
#include "Engine/Direct3D.h"
#include "Engine/Image.h"
#include "GameManager.h"

namespace
{
    const float CAMERA_SPEED = 3.0f;
    const float DOWN_ANGLE_LIMIT = 20.0f;
    const float UP_ANGLE_LIMIT = -10.0f;
    const float PAD_SPEED = 3.0f;
    const float CAMERA_SIZE = 0.1f;//カメラの当たり判定の大きさ

    const float MOVED_FOV = XM_PIDIV4 * 1.1f; // プレイヤーが移動している時のFoV
    const float FOV = XM_PIDIV4; // プレイヤーが立ち止まっている時のFoV
}

//コンストラクタ
Controller::Controller(GameObject* parent)
    :GameObject(parent, "Controller"), cameraAngle(0.0f, 4.0f, 20.0f),cameraDistance(15.0f)
{
}

//デストラクタ
Controller::~Controller()
{
}

//初期化
void Controller::Initialize()
{
}

//更新
void Controller::Update()
{
    //カメラの焦点をControllerオブジェクトに
    //矢印キーで回転
    if (Input::IsKey(DIK_A))
    {
        transform_.rotate_.y -= CAMERA_SPEED;
    }
    if (Input::IsKey(DIK_D))
    {
        transform_.rotate_.y += CAMERA_SPEED;
    }
    if (Input::IsKey(DIK_S) && transform_.rotate_.x > UP_ANGLE_LIMIT)
    {
        transform_.rotate_.x -= CAMERA_SPEED; 
    }
    if (Input::IsKey(DIK_W) && transform_.rotate_.x < DOWN_ANGLE_LIMIT)
    {
        transform_.rotate_.x += CAMERA_SPEED; 
    }

    XMFLOAT3 stickR = { Input::GetPadStickR().y, Input::GetPadStickR().x, 0 };
    transform_.rotate_ = Math::Float3Add(Math::Float3Mul( stickR, PAD_SPEED, PAD_SPEED, PAD_SPEED), transform_.rotate_);
}

//描画
void Controller::Draw()
{
}

//開放
void Controller::Release()
{
}

XMFLOAT3 Controller::GetPosition()
{
    return transform_.position_;
}

XMFLOAT3 Controller::GetRotate()
{
    return transform_.rotate_;
}

//コントローラーでカメラを回転関数
void Controller::SetCameraPos(XMFLOAT3 position)
{
    //最終的なカメラの位置
    XMFLOAT3 camPos;

    //カメラの位置の設定
    //距離を設定
    XMVECTOR vCam = XMVectorSet(cameraAngle.x, cameraAngle.y, cameraAngle.z, 0.0f);

    //コントローラーの角度によってカメラの位置を変える
    XMMATRIX mRotate = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    mRotate *= XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    vCam = XMVector3TransformCoord(vCam, mRotate);

    //正規化してカメラの位置を調整
    vCam = XMVector3Normalize(vCam);

    //カメラのベクトル
    XMFLOAT3 camVec;
    XMStoreFloat3(&camVec, vCam);

    //現在地をXMVECTORに変換
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //ステージのモデル番号を取得
    StageBase* pStage = GameManager::GetNowStage();    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();       //モデル番号を取得

    //レイを飛ばしてコントローラーとカメラの間にステージのモデルがあるか確認
    RayCastData data;
    data.start = transform_.position_;   //レイの発射位置
    data.dir = camVec;                   //レイの方向
    Model::RayCast(hGroundModel, &data); //レイを発射

    //レイが障害物に当たったら
    if (data.hit)
    {
        //カメラから衝突点までの距離
        XMFLOAT3 fDist = Math::Float3Sub(data.pos, transform_.position_);
        XMVECTOR vLength = XMLoadFloat3(&fDist);
        vLength = XMVector3Length(vLength);
        float length = XMVectorGetX(vLength) - CAMERA_SIZE;

        //距離的にぶつかっていたら
        if (length <= cameraDistance)
        {
            //カメラの距離を計算
            vCam *= length;

            //最終的なカメラの位置
            XMStoreFloat3(&camPos, vCam + vPos);
        }
        else
        {
            //カメラの距離を計算
            vCam *= cameraDistance;

            //最終的なカメラの位置
            XMStoreFloat3(&camPos, vCam + vPos);
        }
    }
    else
    {
        //カメラの距離を計算
        vCam *= cameraDistance;
        //最終的なカメラの位置
        XMStoreFloat3(&camPos, vCam + vPos);

        //カメラの位置を変える
        Camera::SetPosition(camPos);
    }

    Camera::SetPosition(camPos);
    transform_.position_ = position;

    //カメラの焦点を変える
    Camera::SetTarget(transform_.position_);

    
}

//リープを使用してコントローラーでカメラを回転させる関数
void Controller::SetCameraLerpPos(XMFLOAT3 position, float attenRate)
{
    //XMVECTORに変換
    //到達するべき位置
    XMVECTOR vReachPosition = XMLoadFloat3(&position);

    //現在地
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);

    //Lerp減衰
    XMVECTOR vCamPos = XMVectorLerp(vPos, vReachPosition, attenRate);

    //XMFLOAT3に変換
    XMFLOAT3 camPos;
    XMStoreFloat3(&camPos, vCamPos);

    //コントローラーでカメラを回転
    SetCameraPos(camPos);
}

//リープとFoV使用してコントローラーでカメラを回転させる関数
void Controller::ChangeFovMove(bool isMoved)
{
    //FoVの設定
    float fov = isMoved ? MOVED_FOV : FOV;
    Camera::SetFOV(fov);
}

//カメラの位置が壁と衝突しているかを返す
bool Controller::IsCameraCollision()
{
    return false;
}

//カメラの距離のセッター
void Controller::SetCameraDistance(float distance)
{
    cameraDistance = distance;
}

//カメラの距離のゲッター
float Controller::GetCameraDistance()
{
    return cameraDistance;
}
