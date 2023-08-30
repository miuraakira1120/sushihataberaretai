#pragma once
#include "Engine/GameObject.h"
#include "PlayerBase.h"

class Neta : public GameObject
{
private:
    const XMFLOAT3 NETA_SIZE =
    {
        0.25f, //ネタのXのサイズ（1倍）
        0.25f, //ネタのYのサイズ（1倍）
        1.5f,  //ネタのZのサイズ（1倍）
    };

    int   hModel_;               //モデル番号
    float gravity;               //今受けている重力の力(マイナスなら重力を振り切って上に行く)

protected:
    PlayerBase* pPlayer;          //PlayerのPlayerBase型のポインタ


public:
    //コンストラクタ
	Neta(GameObject* parent, const std::string& name, const std::string& pathFilename);

    //初期化
    virtual void Initialize() {};

    //更新
    virtual void Update() {};

    //描画
    virtual void Draw();

    //開放
    virtual void Release() {};

    //セットアップする関数
    virtual void SetUp();

    //固有のスキル
    virtual void Skill() {};

    //親の親から見た位置を入手
    XMFLOAT3 GetParentPos();

    //物理演算
    void PhysicalOperation();

    /// <summary>
    /// 落下演出
    /// </summary>
    void LandingStaging();

    /// <summary>
    /// 重力の処理
    /// </summary>
    void Gravity();

    /// <summary>
    /// 基底クラスで設定する更新(Updateの前に呼ぶ)
    /// </summary>
    void PriUpdate();
};

