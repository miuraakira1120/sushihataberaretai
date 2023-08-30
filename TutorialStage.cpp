#include "TutorialStage.h"
#include "NetaMaterial.h"

//コンストラクタ
TutorialStage::TutorialStage(GameObject* parent, std::string path)
	: StageBase(parent, "TutorialStage", path)
{
}

//更新前に一度だけ呼ばれる
void TutorialStage::SetUp()
{
	Instantiate<NetaMaterial>(this);
}
