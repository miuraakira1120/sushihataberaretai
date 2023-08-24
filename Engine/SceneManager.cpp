#include "sceneManager.h"

#include "Model.h"
#include "Image.h"
#include "Audio.h"

#include "../PlayScene.h"
#include "../StartScene.h"

#include "../GoalScene.h"
#include "../GameOverScene.h"

#include "../Imgui_Obj.h"
#include "../EditScene.h"
#include "../TutorialScene.h"


//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//������
void SceneManager::Initialize()
{
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TUTORIAL;
	nextSceneID_ = currentSceneID_;
	pNowScene[currentSceneID_] = Instantiate<TutorialScene>(this);
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		Audio::Release();
		Model::AllRelease();
		Image::AllRelease();

		//imgui�̃��X�g���N���A����
		Imgui_Obj::ClearList();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_PLAY: pNowScene[SCENE_ID_PLAY] = Instantiate<PlayScene>(this); break;
		case SCENE_ID_START: pNowScene[SCENE_ID_START] = Instantiate<StartScene>(this); break;
		case SCENE_ID_GOAL: pNowScene[SCENE_ID_GOAL] = Instantiate<GoalScene>(this); break;
		case SCENE_ID_GAMEOVER: pNowScene[SCENE_ID_GAMEOVER] = Instantiate<GameOverScene>(this); break;
		case SCENE_ID_EDIT: pNowScene[SCENE_ID_EDIT] = Instantiate<EditScene>(this); break;
		case SCENE_ID_TUTORIAL: pNowScene[SCENE_ID_TUTORIAL] = Instantiate<TutorialScene>(this); break;
		}
		Audio::Initialize();
		currentSceneID_ = nextSceneID_;		
	}
}

//�`��
void SceneManager::Draw()
{
}

//�J��
void SceneManager::Release()
{
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;
}

SCENE_ID SceneManager::GetNowSceneID()
{
	return currentSceneID_;
}

GameObject* SceneManager::GetNowScenePointer()
{
	return pNowScene[currentSceneID_];
}


