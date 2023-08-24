#include "TestButton.h"
#include "Engine/SceneManager.h"

//�R���X�g���N�^
TestButton::TestButton(GameObject* parent)
	:Button(parent, "TestButton")
{

}

//������
void TestButton::Initialize()
{
	SetImage("testButton.png");
}

void TestButton::Event()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_PLAY);
}
