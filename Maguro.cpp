#include <vector>
#include <math.h>
#include "Maguro.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "Engine/BoxCollider.h"
#include "Time.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Engine/Input.h"
#include "Engine/Camera.h"
#include "GameManager.h"

namespace
{
    const float FALL_SPEED_LIMIT = 0.7f;    //落下の速度限界 
    const float JUMP_POWER       = 0.8f;    //跳躍速度
    const float FALL_SPEED       = 0.02f;   //落ちるスピード
}

//コンストラクタ
Maguro::Maguro(GameObject* parent)
    :GameObject(parent, "Maguro"), hModel_(-1), isLandingMotion(false),
    prevPos(0.0f,0.0f,0.0f), pSyari(nullptr),pStage(nullptr), hSyariModel(0), 
    hGroundModel(-1), gravity(0), isFullFall(false)
{
}

//デストラクタ
Maguro::~Maguro()
{
}

//初期化
void Maguro::Initialize()
{
    //初期位置の設定
    transform_.position_.y = SYARI_SIZE_Y + MAGURO_SIZE_Y;

    //モデルデータのロード
    hModel_ = Model::Load("maguro.fbx");
    assert(hModel_ >= 0);

    explosion.textureFileName = "Cloud.png";
    explosion.delay = 0;
    explosion.number = 80;
    explosion.lifeTime = 20;
    explosion.direction = XMFLOAT3(0, 1, 0);
    explosion.directionRnd = XMFLOAT3(90, 90, 90);
    explosion.speed = 0.1f;
    explosion.speedRnd = 0.8;
    explosion.size = XMFLOAT2(1, 1);
    explosion.sizeRnd = XMFLOAT2(0.4, 0.4);
    explosion.scale = XMFLOAT2(1.05, 1.05);
    explosion.color = XMFLOAT4(1, 1, 0.1, 1);
    explosion.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);

    
    //ステージのモデルを取得
    StageBase* pStage = GameManager::GetNowStage();    //ステージオブジェクトを探す
    hGroundModel = pStage->GetModelHandle();    //モデル番号を取得
}

//更新
void Maguro::Update()
{
    //オブジェクトを探して、ポインタに入れる
    FindAllObject();

    //各頂点の位置を調べる
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        vertexBonePos[i] = Model::GetBonePosition(hModel_, vertexName[i]);
    }

    //一番低いところと高いところを探す
    int lowest = 0;
    int highest = 0;
    for (int i = 1; i < sizeof(vertexBonePos) / sizeof(XMFLOAT3); i++)
    {
        if (vertexBonePos[lowest].y > vertexBonePos[i].y)
        {
            lowest = i;
        }
        if (vertexBonePos[highest].y < vertexBonePos[i].y)
        {
            highest = i;
        }
    }

    RayCastData nowLowPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    nowLowPosData.start = { vertexBonePos[lowest].x,vertexBonePos[lowest].y + 3,vertexBonePos[lowest].z };  /*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    nowLowPosData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &nowLowPosData); //レイを発射

    RayCastData nowHightPosData;                    //一番低い角からレイを飛ばして、床とぶつかるかを調べる
    nowHightPosData.start = vertexBonePos[highest]/*XMFLOAT3(prevPos.x, 0.0f, prevPos.z)*/;                //レイの方向
    nowHightPosData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &nowHightPosData); //レイを発射

    if (nowLowPosData.pos.y >= vertexBonePos[lowest].y)
    {
       //SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
       //pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);

        //ターゲットをこのオブジェクトに変更
        Camera::SetTarget(Math::Float3Sub(transform_.position_, GetParent()->GetPosition()));

        //爆発エフェクトのエミッターを設置
        explosion.position = transform_.position_;
        VFX::Start(explosion);	

        //プレイヤーにカメラを追従させるようにする
        //pSyari->SetIsCamControll(true);

        //このオブジェクトを削除する
        KillMe();
    }

#if _DEBUG
    if (Input::IsKey(DIK_T))
    {
        transform_.position_.z += 0.1f;
    }
#endif

    //シャリの物理演算
    if (!isLandingMotion)
    {
        PhysicalOperation();
    }
    else
    {
        //落下演出
        LandingStaging();
    }

    prevPos = transform_.position_;//自分の今の場所を1f前の場所変数に入れる
}

//描画
void Maguro::Draw()
{
    if (!isLandingMotion)
    {
        Model::SetTransform(hModel_, transform_);
        Model::Draw(hModel_);
    }
    else
    {
        Transform trans = transform_;
        trans.position_ = Math::Float3Sub(transform_.position_, GetParent()->GetPosition());
        Model::SetTransform(hModel_, trans);
        Model::Draw(hModel_);
    }
}

//開放
void Maguro::Release()
{
}

//何かに当たった
void Maguro::OnCollision(GameObject* pTarget)
{ 
}

//オブジェクトを探して、ポインタに入れる
void Maguro::FindAllObject()
{
    //ステージのモデルを取得
    StageBase* pStage = GameManager::GetNowStage();    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得
}

//レイを飛ばす
RayCastData Maguro::DoRay(XMFLOAT3 start, XMFLOAT3 dir, int hModel)
{
    RayCastData rayData;
    rayData.start = start;
    rayData.dir = dir;
    Model::RayCast(hModel, &rayData);
    return rayData;
}

void Maguro::PhysicalOperation()
{
    //親のポインタを取得
    pSyari = (Syari*)GetParent();

    //モデル番号を取得
    hSyariModel = pSyari->GetModelHandle();

   /* RayCastData syariData = DoRay(GetParentPos(), XMFLOAT3(0, -1, 0), hSyariModel);*/
    XMFLOAT3 syariUpDistanceDifference = pSyari->GetUpDistanceDifference();
    //マグロがシャリの上に乗っていたら
    //if (!syariData.hit)
    {
        //右と手前のほう高ければ＋
        //左の奥ほう高ければ－
        if (syariUpDistanceDifference.z > FALL_ANGLE || syariUpDistanceDifference.z < FALL_ANGLE)
        {
            if (syariUpDistanceDifference.z > FALL_ANGLE > 0)
            {
                transform_.position_.x += FALL_SPEED * abs(syariUpDistanceDifference.z);
            }
            else
            {
                transform_.position_.x -= FALL_SPEED * abs(syariUpDistanceDifference.z);
            }
        }
        if (syariUpDistanceDifference.x > FALL_ANGLE || syariUpDistanceDifference.x < FALL_ANGLE)
        {
            if (syariUpDistanceDifference.x > FALL_ANGLE > 0)
            {
                transform_.position_.z -= FALL_SPEED * abs(syariUpDistanceDifference.x);
            }
            else
            {
                transform_.position_.z += FALL_SPEED * abs(syariUpDistanceDifference.x);
            }
        }
    }

    if (abs(transform_.position_.x) > SYARI_SIZE_X || abs(transform_.position_.z) > SYARI_SIZE_Z)
    {
        //プレイヤーにカメラを追従させなくする
        //pSyari->SetIsCamControll(false);

        //プレイヤーの入力を受け付けなくする
        //pSyari->SetCanMove(false);

        //落下演出
        isLandingMotion = true;

        //親の親を親にして移動する
        transform_.ChangeParentRotate(0);
        transform_.SetRotateMode(TRANS_CHANGEPARENT_MODE);

        //親オブジェクトの位置に移動
        transform_.position_ = Math::Float3Add(GetParent()->GetPosition(), transform_.position_);
        transform_.position_.y += SYARI_SIZE_Y;

        //飛び上がる
        gravity -= JUMP_POWER;
    }
}

//落下演出
void Maguro::LandingStaging()
{
    //ターゲットをこのオブジェクトに変更
    Camera::SetTarget(transform_.position_);

    //重力の処理
    Gravity();

    //落下時の回転演出
    RotationStaging();
}

//落下時の回転演出
void Maguro::RotationStaging()
{
    transform_.rotate_ = Math::Float3Add(ROTATE_STAGING_ANGE, transform_.rotate_);
}

//重力の処理
void Maguro::Gravity()
{
    //スピードの上限に達していなければ
    if (FALL_SPEED_LIMIT >= gravity)
    {
        gravity += FALL_SPEED;
        transform_.position_.y -= gravity;
    }
    else
    {
        transform_.position_.y -= FALL_SPEED_LIMIT;
    }
}




