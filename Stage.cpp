#include "Stage.h"
#include "Engine/Model.h"
#include "Goal.h"
#include "SalmonRoe.h"
#include "Engine/Direct3D.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent, std::string path)
    : StageBase(parent, "Stage", path)
{
}

//�X�V�O�ɌĂԊ֐�
void Stage::SetUp()
{
    //Instantiate<SalmonRoe>(this);
    //Instantiate<Goal>(this);
}
