#include "NetaMaterial.h"
#include "Engine/Model.h"
#include "ModelBase.h"

//コンストラクタ
NetaMaterial::NetaMaterial(GameObject* parent)
    :GameObject(parent, "NetaMaterial"), pInternalModel(nullptr)
{
}

//デストラクタ
NetaMaterial::~NetaMaterial()
{
}

//初期化
void NetaMaterial::Initialize()
{
    pathName_ = "TransparentSphere.fbx";
    //モデルデータのロード
    hModel_ = Model::Load(pathName_, MODEL_ALPHA);
    assert(hModel_ >= 0);

    //中のモデルの作成
    pInternalModel = CharacterInstantiate<ModelBase>(this, "maguro.fbx");
    pInternalModel->SetScale(INTERNAL_MODEL_SCALE, INTERNAL_MODEL_SCALE, INTERNAL_MODEL_SCALE);
}

//更新
void NetaMaterial::Update()
{
    //内部モデルの回転
    pInternalModel->SetRotate(Math::Float3Add(pInternalModel->GetRotate(), INTERNAL_MODEL_ROTATE));
}

//描画
void NetaMaterial::Draw()
{
    Transform trans = pInternalModel->GetTransform();
    Model::SetTransform(pInternalModel->GetModelHandle(), trans);
    Model::Draw(pInternalModel->GetModelHandle());

    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void NetaMaterial::Release()
{
}