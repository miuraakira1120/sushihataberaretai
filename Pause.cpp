#include "Pause.h"
#include "Engine/Image.h"
#include "GameManager.h"
#include "BackUI.h"
#include "Engine/SceneManager.h"
#include "Engine/JsonOperator.h"
#include "InstanceManager.h"


//コンストラクタ
Pause::Pause()
{
}

//デストラクタ
Pause::~Pause()
{
}

//初期化
void Pause::Initialize()
{
}

//更新
void Pause::Update()
{
	//もしポーズしていなかったら
	if (GameManager::GetIsPause())
	{
		return;
	}

	//UIリストの中身の更新を全部呼ぶ
	AllPauseUIUpdate();
}

//描画
void Pause::Draw()
{
	//もしポーズしていなかったら
	if (GameManager::GetIsPause())
	{
		return;
	}

	//作成したUIの描画を呼ぶ
	AllPauseUIDraw();
}

//開放
void Pause::Release()
{
}

//UIの作成
void Pause::CreateUI()
{
	std::vector<GameObject*> tmp;
	InstanceManager::AllCreateImage(JsonOperator::PAUSE_IMAGE_JSON, tmp, GameManager::GetpSceneManagerPointor()->GetNowScenePointer());

	for (auto i = 0; i < tmp.size(); i++)
	{
		//UIListに入れる
		AddUIList(tmp[i]);
	}
}

//UIの削除
void Pause::DeleteUI()
{
	//UIListの中身をすべて消す
	for (auto i = UIList.begin(); i != UIList.end();)
	{
		(*i)->KillMe();
		i = UIList.erase(i);

	}

	//UIListをすべて削除
	UIList.clear();
}

//UIリストの中身の更新を全部呼ぶ
void Pause::AllPauseUIUpdate()
{
	for (auto i = UIList.begin(); i != UIList.end(); i++)
	{
		if ((*i) != nullptr)
			(*i)->Update();
	}
}

//UIリストの中身の描画を全部呼ぶ
void Pause::AllPauseUIDraw()
{
	//UIListの後ろの方が前に描画
	for (auto i = UIList.begin(); i != UIList.end(); i++)
	{
		if ((*i) != nullptr)
			(*i)->Draw();
	}
}

//UIListに入れる
void Pause::AddUIList(GameObject* ui)
{
	UIList.push_back(ui);
}

