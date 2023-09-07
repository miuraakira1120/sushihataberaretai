#include "NetaMaterial.h"
#include "Engine/Model.h"
#include "ModelBase.h"
#include "Engine/SphereCollider.h"
#include "Engine/BoxCollider.h"
#include "Tuna.h"
#include "VFX.h"

//コンストラクタ
NetaMaterial::NetaMaterial(GameObject* parent)
    :GameObject(parent, "NetaMaterial"), pInternalModel(nullptr)
{
}

NetaMaterial::NetaMaterial(GameObject* parent, std::string fileName)
{
    internalModelPath = fileName;
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

    //コライダーをつける
    SphereCollider* collision = new SphereCollider(XMFLOAT3(0, 0, 0), SPHERE_SIZE);
    AddCollider(collision);

    //箱型のコライダーをつける（テスト）
    //BoxCollider* boxCollision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(2, 2, 2));
    //AddCollider(boxCollision);

    //中のモデルの作成
    pInternalModel = CharacterInstantiate<ModelBase>(this, internalModelPath);
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

//何かに当たったら呼び出される関数
void NetaMaterial::OnCollision(GameObject* pTarget)
{
    //プレイヤーにぶつかったら
    if (pTarget->GetName() == "Player")
    {
        //中にあるモデルがマグロなら
        if (internalModelPath == "maguro.fbx")
        {
            //プレイヤーの子オブジェクトを追加
            CharacterInstantiate<Tuna>(pTarget, "maguro.fbx");

            //エフェクト
            EmitterData starEfect = VFX::SetEmitterDataStar();
            starEfect.position = pTarget->GetPosition();
            VFX::Start(starEfect);

            //中のモデルを消す
            pInternalModel->KillMe();

            //中のモデルの名前を消す
            internalModelPath = "";
        }
    }
}
