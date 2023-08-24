#include "RedBox.h"
#include "Engine/Model.h"

//コンストラクタ
RedBox::RedBox(GameObject* parent)
    :GameObject(parent, "RedBox"), hModel_(-1)
{
}

//デストラクタ
RedBox::~RedBox()
{
}

//初期化
void RedBox::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("RedBox.fbx");
    assert(hModel_ >= 0);

    transform_.scale_ = { 0.25f, 0.25f, 0.25f };
}

//更新
void RedBox::Update()
{
}

//描画
void RedBox::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void RedBox::Release()
{
}

void RedBox::SetPosition(XMFLOAT3 pos_)
{
    transform_.position_ = pos_;
}
