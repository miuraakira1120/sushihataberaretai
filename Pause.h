#pragma once
#include "Engine/GameObject.h"
#include <directxmath.h>
#include <vector>

//Pauseシーンを管理するクラス
class Pause
{
private:
    std::vector<GameObject*> UIList;

public:
    //コンストラクタ
    Pause();

    //デストラクタ
    ~Pause();

    //初期化
    void Initialize();

    //更新
    void Update();

    //描画
    void Draw();

    //開放
    void Release();

    //UIの作成
    void CreateUI();

    //UIの削除
    void DeleteUI();

    //UIリストの中身の更新を全部呼ぶ
    void AllPauseUIUpdate();

    //UIリストの中身の描画を全部呼ぶ
    void AllPauseUIDraw();

    //UIListに入れる
    void AddUIList(GameObject* ui);
};