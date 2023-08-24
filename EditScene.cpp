#include "EditScene.h"
#include "Engine/JsonOperator.h"
#include "Imgui_Obj.h"
#include "ModelBase.h"
#include "Engine/Camera.h"


//コンストラクタ
EditScene::EditScene(GameObject* parent)
	: GameObject(parent, "EditScene"), modeUI(UI_Type::NONE), prevModeUI(UI_Type::NONE)
{
}

//初期化
void EditScene::Initialize()
{	
	//pSoy = CharacterInstantiate<ModelBase>(this, "SoySauce.fbx");
	//pSoy->SetRotateX(180);
	//pSoy->SetScale(5, 5, 5);
	//Camera::SetTarget(transform_.position_);
}

//更新
void EditScene::Update()
{
	modeUI = static_cast<UI_Type>(Imgui_Obj::GetUIType());

	//前の作成していたUIのタイプと違ったら
	if (modeUI != prevModeUI)
	{
		//子供をすべて消す
		KillAllChildren();

		//対応したUIを作成
		switch (modeUI)
		{
		case UI_Type::NONE:
			break;
		case UI_Type::PAUSE:
			InstanceManager::AllCreateImage(JsonOperator::PAUSE_IMAGE_JSON, this);
			InstanceManager::AllCreateButton(JsonOperator::PAUSE_BUTTON_JSON, this);
			break;
		case UI_Type::TYPE_MAX:
			break;
		default:
			break;
		}
	}
	prevModeUI = modeUI;


	

}

//描画
void EditScene::Draw()
{
}

//開放
void EditScene::Release()
{
}