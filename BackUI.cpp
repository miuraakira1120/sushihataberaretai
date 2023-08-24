#include "BackUI.h"
#include "Engine/Image.h"

//コンストラクタ
BackUI::BackUI(GameObject* parent)
    :GameObject(parent, "BackUI"), hPict_(-1)
{
}

//デストラクタ
BackUI::~BackUI()
{
}

//初期化
void BackUI::Initialize()
{
    //画像データのロード
    hPict_ = Image::Load(pathName_);
    assert(hPict_ >= 0);
}

//更新
void BackUI::Update()
{
}

//描画
void BackUI::Draw()
{
    Image::SetTransform(hPict_, transform_);
    Image::SetAlpha(hPict_, 100);
    Image::Draw(hPict_);
}

//開放
void BackUI::Release()
{
}