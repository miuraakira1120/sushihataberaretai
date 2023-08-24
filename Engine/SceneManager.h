#pragma once
#include "global.h"
#include "GameObject.h"

//ゲームに登場するシーン
enum SCENE_ID
{
	SCENE_ID_PLAY = 0,
	SCENE_ID_START,
	SCENE_ID_GOAL,
	SCENE_ID_GAMEOVER,
	SCENE_ID_EDIT,
	SCENE_ID_TUTORIAL,
	SCENE_ID_MAX
};

//-----------------------------------------------------------
//シーン切り替えを担当するオブジェクト
//-----------------------------------------------------------
class SceneManager : public GameObject
{
public:

	//コンストラクタ
	//引数：parent	親オブジェクト（基本的にゲームマネージャー）
	SceneManager(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//シーン切り替え（実際に切り替わるのはこの次のフレーム）
	//引数：next	次のシーンのID
	void ChangeScene(SCENE_ID next);

	//今のシーンのIDを返すゲッター
	SCENE_ID GetNowSceneID();

	//今のシーンのポインタを返すゲッター
	GameObject* GetNowScenePointer();

private:
	SCENE_ID currentSceneID_;	//現在のシーン
	SCENE_ID nextSceneID_;		//次のシーン

	//シーンのポインタの配列
	GameObject* pNowScene[SCENE_ID_MAX];

};