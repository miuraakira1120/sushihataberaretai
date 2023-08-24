#pragma once
#include "Engine/GameObject.h"

class StageBase : public GameObject
{
	int hModel_;    //モデル番号
    const std::string DIRECTORY = ".\\Stage/"; //ステージのディレクトリ名

public:
    
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="parent">親オブジェクト</param>
    /// <param name="name">ステージの名前</param>
    /// <param name="pathName">モデルのパス</param>
    StageBase(GameObject* parent, const std::string& name, const std::string& pathName);

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    //ハンドルを取得する関数
    int GetModelHandle() { return hModel_; }
};

