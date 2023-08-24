#include "StageBase.h"
#include "Engine/Model.h"

//�R���X�g���N�^
StageBase::StageBase(GameObject* parent, const std::string& name, const std::string& pathName)
	:GameObject(parent, name), hModel_(-1)
{
	SetPathName(pathName);
}

//������
void StageBase::Initialize()
{
	hModel_ = Model::Load(DIRECTORY + pathName_);
	assert(hModel_ >= 0);
}

//�X�V
void StageBase::Update()
{
}

//�`��
void StageBase::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void StageBase::Release()
{
}
