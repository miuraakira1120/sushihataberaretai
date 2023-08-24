#include "SalmonRoe.h"
#include "Cannon.h"
#include "Engine/Model.h"
#include "Stage.h"
#include "ImageBase.h"

//コンストラクタ
SalmonRoe::SalmonRoe(GameObject* parent)
    :GameObject(parent, "SalmonRoe"), hModel_(-1)
{
}

//デストラクタ
SalmonRoe::~SalmonRoe()
{
}

//初期化
void SalmonRoe::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("salmonRoe.fbx");
    assert(hModel_ >= 0);
    Instantiate<Cannon>(this);

    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得
    RayCastData data;
    data.start = transform_.position_;   //レイの発射位置
    data.dir = XMFLOAT3(0, -1, 0);       //レイの方向
    Model::RayCast(hGroundModel, &data); //レイを発射

     //レイが当たったら
    if (data.hit)
    {
        //その分位置を下げる
        transform_.position_.y -= data.dist - SALMONROE_SIZE_Y;
    }

    transform_.position_.x = 4;


    ImageBase* pImage = InstantiateImage<ImageBase>(this, "tuna.jpg", XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
    pImage->SetParentMove(true);
    pImage->SetPosition(0, 5, 0);
    pImage->SetScale(0.2, 0.2, 0.2);
}

//更新
void SalmonRoe::Update()
{
}

//描画
void SalmonRoe::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void SalmonRoe::Release()
{
}