#include "ModelBase.h"
#include "Engine/Model.h"

//コンストラクタ
ModelBase::ModelBase(GameObject* parent, std::string filename)
    :GameObject(parent, "ModelBase"), hModel_(-1), scroll(0)
{
    SetPathName(filename); 
}

//デストラクタ
ModelBase::~ModelBase()
{
}

//初期化
void ModelBase::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load(pathName_);
    assert(hModel_ >= 0);
}

//更新
void ModelBase::Update()
{
    scroll += 0.1f;
}

//描画
void ModelBase::Draw()
{
    Model::SetScrollVal(hModel_, scroll);
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void ModelBase::Release()
{
}