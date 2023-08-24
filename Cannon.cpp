#include "Cannon.h"
#include "Engine/Model.h"
#include "Syari.h"
#include "Stage.h"
#include "Ball.h"
#include "Engine/Camera.h"

//コンストラクタ
Cannon::Cannon(GameObject* parent)
    :GameObject(parent, "Cannon"), hModel_(-1),timer(0)
{
}

//デストラクタ
Cannon::~Cannon()
{
}

//初期化
void Cannon::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("cucumberTest.fbx");
    assert(hModel_ >= 0);

    //Model::SetAnimFrame(hModel_, 1, 3000, 3.0f);

    
}

//更新
void Cannon::Update()
{
    if (timer++ >=60)
    {
        XMFLOAT3 CannonShotPos = Model::GetBonePosition(hModel_, "Cannon_ShotPos");
        XMFLOAT3 CannonRoot = Model::GetBonePosition(hModel_, "Cannon_Root");
        Ball* pBall = Instantiate<Ball>(this->GetParent()->GetParent());
        pBall->SetPosition(CannonShotPos);
        //pBall->SetPosition(Transform::Float3Add(this->GetParent()->GetPosition(), CannonRoot));
        XMVECTOR vCannonFront = XMLoadFloat3(&CannonShotPos);
        XMVECTOR vCannonBack = XMLoadFloat3(&CannonRoot);

        XMFLOAT3 fBallMove;
        XMVECTOR vBallMove = vCannonFront - vCannonBack;
        vBallMove = XMVector3Normalize(vBallMove);
        vBallMove *= 0.5;
        XMStoreFloat3(&fBallMove, vBallMove);

        
        pBall->SetMove(fBallMove);

        timer = 0;
    }
    //Syari* pSyari = (Syari*)FindObject("Syari");
    //transform_.position_ = pSyari->GetPosition();
}

//描画
void Cannon::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Cannon::Release()
{
}