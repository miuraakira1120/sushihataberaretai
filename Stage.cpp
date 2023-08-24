#include "Stage.h"
#include "Engine/Model.h"
#include "Goal.h"
#include "SalmonRoe.h"
#include "Engine/Direct3D.h"

//コンストラクタ
Stage::Stage(GameObject* parent, std::string path)
    : StageBase(parent, "Stage", path)
{
}

//更新前に呼ぶ関数
void Stage::SetUp()
{
    //Instantiate<SalmonRoe>(this);
    //Instantiate<Goal>(this);
}
