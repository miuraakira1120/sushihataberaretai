#include "BlueBox.h"
#include "Engine/Model.h"

//コンストラクタ
BlueBox::BlueBox(GameObject* parent)
    :GameObject(parent, "BlueBox"), hModel_(-1)
{
}

//デストラクタ
BlueBox::~BlueBox()
{
}

//初期化
void BlueBox::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("BlueBox.fbx");
    assert(hModel_ >= 0);

    transform_.scale_ = { 0.25f, 0.25f, 0.25f };
}

//更新
void BlueBox::Update()
{
}

//描画
void BlueBox::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void BlueBox::Release()
{
}

void BlueBox::SetPosition(XMFLOAT3 pos_)
{
    transform_.position_ = pos_;
}
