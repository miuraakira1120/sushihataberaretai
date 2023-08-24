#pragma once
#include "Engine/GameObject.h"
#include "Engine/SceneManager.h"

namespace ButtonManager
{
    //ボタンの種類
    enum ButtonKinds
    {
        SCENE_CHANGE_BUTTON,
        PLAYER_CONTROL_BUTTON,
        SLIDER,
        MOVE_BY_MOUTH_BUTTON,
        BUTTON_KINDS_MAX
    };

    /// <summary>
    /// ボタンオブジェクトの生成と初期設定
    /// </summary>
    /// <param name="pParent">親オブジェクト</param>
    /// <param name="pChild">子オブジェクト</param>
    /// <param name="position">生成位置</param>
    /// <param name="interval">生成間隔</param>
    void InstantiateButton(GameObject* pParent, GameObject* pChild, XMFLOAT3& position, const XMFLOAT3& interval);

    /// <summary>
    /// 画面遷移ボタンの作成
    /// </summary>
    /// <param name="pParent">親オブジェクト</param>
    /// <param name="position">ボタンの位置</param>
    /// <param name="name">遷移先の名前</param>
    /// <param name="fileName">表示させる画像の名前</param>
    /// <returns>ボタンのポインタ</returns>
    GameObject* CreateSceneChangeButton(GameObject* pParent, XMFLOAT3 position, SCENE_ID name, std::string imageName);


    /// <summary>
    /// プレイヤーのボタン配置を変えるボタンの作成
    /// </summary>
    /// <param name="pParent">親オブジェクト</param>
    /// <param name="position">ボタンの位置</param>
    /// <param name="fileName">表示させる画像の名前</param>
    /// <returns>ボタンのポインタ</returns>
    GameObject* CreatePlayerControlButton(GameObject* pParent, XMFLOAT3 position, std::string imageName);

    /// <summary>
    /// スライダーの作成
    /// </summary>
    /// <param name="pParent">親オブジェクト</param>
    /// <param name="position">ボタンの位置</param>
    /// <param name="imageName">表示させる画像の名前</param>
    /// <param name="childImageName">スラーダーのボタンに表示させる画像の名前</param>
    /// <returns>スライダーのポインタ</returns>
    GameObject* CreateSliderButton(GameObject* pParent, XMFLOAT3 position, std::string imageName, std::string childImageName);

    /// <summary>
    /// マウスによって動くボタンの作成
    /// </summary>
    /// <param name="pParent">親オブジェクト</param>
    /// <param name="position">ボタンの位置</param>
    /// <param name="imageName">表示させる画像の名前</param>
    /// <returns>このボタンのポインタ</returns>
    GameObject* CreateMoveByMouthButton(GameObject* pParent, XMFLOAT3 position, std::string imageName);

};

//ボタン作成手順
//１　ボタンクラスを作る
//２　Create関数を作成
//３　ButtonKindsに追加
//後はCreate関数を呼べばいい

//Imguiに追加も

