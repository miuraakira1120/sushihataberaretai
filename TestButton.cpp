#include "TestButton.h"
#include "Engine/SceneManager.h"

//コンストラクタ
TestButton::TestButton(GameObject* parent)
	:Button(parent, "TestButton")
{

}

//初期化
void TestButton::Initialize()
{
	SetImage("testButton.png");
}

void TestButton::Event()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_PLAY);
}
