#include "ChangeSceneButton.h"

ChangeSceneButton::ChangeSceneButton(GameObject* parent, SCENE_ID name, std::string fileName)
	:Button(parent, "ChangeSceneButton"), changeSceneName(name)
{
	pathName_ = fileName;
}

void ChangeSceneButton::Initialize()
{
	//画像の設定をする
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
	//選ばれていたら画像を拡大する
	if (GetValue())
	{
		transform_.scale_ = IMAGE_SIZE_MAG;
	}
	else
	{
		transform_.scale_ = IMAGE_SIZE_DEF;
	}
}
