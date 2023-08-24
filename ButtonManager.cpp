#include "ButtonManager.h"
#include "ChangeSceneButton.h"
#include "PlayerControlButton.h"
#include "Slider.h"
#include "MoveByMouthButton.h"

namespace ButtonManager
{
    //ボタンオブジェクトの生成と初期設定
    void InstantiateButton(GameObject* pParent, GameObject* pChild, XMFLOAT3& position, const XMFLOAT3& interval)
    {
        if (pParent != nullptr)
        {
            pParent->PushBackChild(pChild);
        }

        //初期化処理
        pChild->Initialize();
        //生成位置調整
        pChild->SetPosition(position);

        //間隔を空ける
        Math::Float3Sub(position, interval);
    }


    //画面遷移ボタンの作成
    GameObject* CreateSceneChangeButton(GameObject* pParent, XMFLOAT3 position, SCENE_ID name, std::string imageName)
    {
        auto* pNewObject = new ChangeSceneButton(pParent, name, imageName);
        InstantiateButton(pParent, pNewObject, position, XMFLOAT3(0.0f, 0.0f, 0.0f));
        return pNewObject;
    }

    //プレイヤーのボタン設定画面の作成
    GameObject* CreatePlayerControlButton(GameObject* pParent, XMFLOAT3 position, std::string imageName)
    {
        auto* pNewObject = new PlayerControlButton(pParent, imageName);
        InstantiateButton(pParent, pNewObject, position, XMFLOAT3(0.0f, 0.0f, 0.0f));
        return pNewObject;
    }

    //スライダーの作成
    GameObject* CreateSliderButton(GameObject* pParent, XMFLOAT3 position, std::string imageName, std::string childImageName)
    {
        auto* pNewObject = new Slider(pParent, imageName, childImageName);
        InstantiateButton(pParent, pNewObject, position, XMFLOAT3(0.0f, 0.0f, 0.0f));
        return pNewObject;
    }

    // マウスによって動くボタンの作成
    GameObject* CreateMoveByMouthButton(GameObject* pParent, XMFLOAT3 position, std::string imageName)
    {
        auto* pNewObject = new MoveByMouthButton(pParent, imageName);
        InstantiateButton(pParent, pNewObject, position, XMFLOAT3(0.0f, 0.0f, 0.0f));
        return pNewObject;
    }
}