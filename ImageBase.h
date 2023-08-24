#pragma once
#include "Engine/GameObject.h"

//画像を出すだけのクラス
class ImageBase : public GameObject
{
    int hPict_;                //画像番号
    std::string PrevPathName_; //1フレーム前の画像番号  

    bool isParentMove;//親オブジェクトの位置にって画像の位置を変える
    XMFLOAT3 shiftPosition;//親オブジェクトの位置にって画像の位置を変える時に使う、ずらす値

public:
    //コンストラクタ
    ImageBase(GameObject* parent, std::string pathName, int alpha = 255);

    //デストラクタ
    ~ImageBase();

    //初期化
    void Initialize() override;

    //更新
    void Update() override;

    //描画
    void Draw() override;

    //開放
    void Release() override;

    
    /// <summary>
    /// 親オブジェクトの位置にって画像の位置を変える
    /// </summary>
    /// <returns>変更後のスクリーン座標</returns>
    XMFLOAT3 parentObjectPositionByImagePosition();

    /// <summary>
    /// 親オブジェクトの位置にって画像の位置を変える状態にする
    /// </summary>
    /// <returns>変更後のスクリーン座標</returns>
    void SetParentMove(bool flag);

    /// <summary>
    /// shiftPositionのセッター
    /// </summary>
    void SetShiftPos(XMFLOAT3 shift);

};