#include "StageBase.h"
#include "Engine/Model.h"

//コンストラクタ
StageBase::StageBase(GameObject* parent, const std::string& name, const std::string& pathName)
	:GameObject(parent, name), hModel_(-1)
{
	SetPathName(pathName);
}

//初期化
void StageBase::Initialize()
{
	hModel_ = Model::Load(DIRECTORY + pathName_);
	assert(hModel_ >= 0);
}

//更新
void StageBase::Update()
{
}

//描画
void StageBase::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void StageBase::Release()
{
}
