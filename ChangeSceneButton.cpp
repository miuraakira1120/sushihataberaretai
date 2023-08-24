#include "ChangeSceneButton.h"

ChangeSceneButton::ChangeSceneButton(GameObject* parent, SCENE_ID name, std::string fileName)
	:Button(parent, "ChangeSceneButton"), changeSceneName(name)
{
	pathName_ = fileName;
}

void ChangeSceneButton::Initialize()
{
	//‰æ‘œ‚ÌÝ’è‚ð‚·‚é
	SetImage(pathName_);
}

void ChangeSceneButton::Event()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(changeSceneName);
}

void ChangeSceneButton::SetChangeSceneName(SCENE_ID name)
{
	changeSceneName = name;
}

void ChangeSceneButton::PreUpdate()
{
	//‘I‚Î‚ê‚Ä‚¢‚½‚ç‰æ‘œ‚ðŠg‘å‚·‚é
	if (GetValue())
	{
		transform_.scale_ = IMAGE_SIZE_MAG;
	}
	else
	{
		transform_.scale_ = IMAGE_SIZE_DEF;
	}
}
