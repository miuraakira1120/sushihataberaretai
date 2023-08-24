#pragma once
#include "PlayerBase.h"
class Player : public PlayerBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="parent">親オブジェクト</param>
    /// <param name="name">オブジェクトの名前</param>
    /// <param name="pathName"></param>
    Player(GameObject* parent, std::string pathName);

    /// <summary>
    /// 更新
    /// </summary>
    virtual void Update() override;
};

