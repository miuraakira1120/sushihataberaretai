#include "Ball.h"
#include "Engine/Model.h"
#include "Stage.h"
#include "Engine/Camera.h"
#include "Engine/SphereCollider.h"

//コンストラクタ
Ball::Ball(GameObject* parent)
    :GameObject(parent, "Ball"), hModel_(-1),fMove(), isPrevRayHit(true),count(0)
{
}

//デストラクタ
Ball::~Ball()
{
}

//初期化
void Ball::Initialize()
{
    hModel_ = Model::Load("Ball.fbx");
    assert(hModel_ >= 0); 

    //当たり判定を追加
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), 1.0f);
    AddCollider(collision);

    vMoved = {0,0,0,0};
    prevPos = transform_.position_;
}

//更新
void Ball::Update()
{
    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得

    RayCastData posLowData;                    
    posLowData.start = transform_.position_;   //レイの方向
    posLowData.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &posLowData); //レイを発射

    //RayCastData posRightData;
    //posRightData.start = transform_.position_;   //レイの方向
    //posRightData.dir = XMFLOAT3(1, 0, 0);       //レイの方向
    //Model::RayCast(hGroundModel, &posRightData); //レイを発射

    //RayCastData posLeftData;
    //posLeftData.start = transform_.position_;   //レイの方向
    //posLeftData.dir = XMFLOAT3(-1, 0, 0);       //レイの方向
    //Model::RayCast(hGroundModel, &posLeftData); //レイを発射

    //RayCastData posFrontData;
    //posFrontData.start = transform_.position_;   //レイの方向
    //posFrontData.dir = XMFLOAT3(0, 0, -1);       //レイの方向
    //Model::RayCast(hGroundModel, &posFrontData); //レイを発射

    //RayCastData posBackData;
    //posBackData.start = transform_.position_;   //レイの方向
    //posBackData.dir = XMFLOAT3(0, 0, 1);       //レイの方向
    //Model::RayCast(hGroundModel, &posBackData); //レイを発射

    transform_.position_ = Math::Float3Add(transform_.position_, fMove);
    //もし下に地面があったら
    if (posLowData.hit && posLowData.dist - BALL_SIZE > accel)
    {
        //接地フラグを偽にする
        isGround = false;

        //重力
        if (SPEED_LIMIT >= accel)
        {
            accel += FALL_SPEED;
            transform_.position_.y -= accel;
        }
        else
        {
            transform_.position_.y -= SPEED_LIMIT;
        }
    }
    else if(isPrevRayHit) //もし下に地面がなかったら
    {
        if (++count >= 5)
        {
            KillMe();
        }
        accel = 0.0f;
        transform_.position_.y -= posLowData.dist - BALL_SIZE;
        //接地フラグを真にする
        isGround = true;
    }

   isPrevRayHit = posLowData.hit;

   //if (posRightData.hit && posRightData.dist < BALL_SIZE)
   //{
   //    fMove.x *= -1;
   //}
   //if (posLeftData.hit && posLeftData.dist < BALL_SIZE)
   //{
   //    fMove.x *= -1;
   //}
   //if (posFrontData.hit && posFrontData.dist < BALL_SIZE)
   //{
   //    fMove.z *= -1;
   //}
   //if (posBackData.hit && posBackData.dist < BALL_SIZE)
   //{
   //    fMove.z *= -1;
   //}

   XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
   XMVECTOR vPrevPos = XMLoadFloat3(&prevPos);
   vMoved = vPos - vPrevPos;
   SetMoved(vMoved);

   prevPos = transform_.position_;

}

//描画
void Ball::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Ball::Release()
{
}

void Ball::SetMove(XMFLOAT3 move)
{
    fMove = move;
}

void Ball::SetPosition(XMFLOAT3 pos)
{
    transform_.position_ = pos;
}
