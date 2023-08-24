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


//コンストラクタ
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//初期化
void SceneManager::Initialize()
{
	//最初のシーンを準備
	currentSceneID_ = SCENE_ID_TUTORIAL;
	nextSceneID_ = currentSceneID_;
	pNowScene[currentSceneID_] = Instantiate<TutorialScene>(this);
}

//更新
void SceneManager::Update()
{
	//次のシーンが現在のシーンと違う　＝　シーンを切り替えなければならない
	if (currentSceneID_ != nextSceneID_)
	{
		//そのシーンのオブジェクトを全削除
		KillAllChildren();

		//ロードしたデータを全削除
		Audio::Release();
		Model::AllRelease();
		Image::AllRelease();

		//imguiのリストをクリアする
		Imgui_Obj::ClearList();

		//次のシーンを作成
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

//描画
void SceneManager::Draw()
{
}

//開放
void SceneManager::Release()
{
}

//シーン切り替え（実際に切り替わるのはこの次のフレーム）
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


