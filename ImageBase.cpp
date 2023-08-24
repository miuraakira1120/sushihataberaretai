#include "ImageBase.h"
#include "Engine/Image.h"
#include "Engine/Camera.h"
#include "Player.h"
#include "Imgui_Obj.h"

//コンストラクタ
ImageBase::ImageBase(GameObject* parent, std::string pathName, int alpha)
    :GameObject(parent, "ImageBase"),hPict_(-1), isParentMove(false),shiftPosition()
{
    SetPathName(pathName);
    SetAlpha(alpha);
}

//デストラクタ
ImageBase::~ImageBase()
{
}

//初期化
void ImageBase::Initialize()
{
    std::string fullPath = Image::DIRECTORY_UI + pathName_;
    //画像データのロード
    hPict_ = Image::Load(fullPath);
    assert(hPict_ >= 0);

    PrevPathName_ = pathName_;

    Imgui_Obj::AddDebugLogList(this);
}

//更新
void ImageBase::Update()
{
    //前フレームとpathName_が違うなら
    if (PrevPathName_ != pathName_)
    {
        std::string fullPath = Image::DIRECTORY_UI + pathName_;
        //リロード
        //画像データのロード
        hPict_ = Image::Load(fullPath);
        assert(hPict_ >= 0);
    }
    PrevPathName_ = pathName_;
}

//描画
void ImageBase::Draw()
{
    //アルファ値をセットする
    Image::SetAlpha(hPict_, alpha_);

    //通常の状態
    if (!isParentMove)
    {
        Image::SetTransform(hPict_, transform_);
    }
    //親オブジェクトの位置にって画像の位置を変える状態
    else
    {       
        Transform scrTransform = transform_;
        scrTransform.position_ = parentObjectPositionByImagePosition();
        Image::SetTransform(hPict_, scrTransform);
    }

    //描画
    Image::Draw(hPict_);
}

//開放
void ImageBase::Release()
{
}

//親オブジェクトの位置にって画像の位置を変える
XMFLOAT3 ImageBase::parentObjectPositionByImagePosition()
{
    //親オブジェクトをスクリーン座標に変換
    XMFLOAT3 scrParentPos = Camera::ToWorldCalcScreen(Math::Float3Add(GetParent()->GetPosition(), transform_.position_));
    //scrParentPos = Math::Float3Add( scrParentPos, transform_.position_);
    return scrParentPos;
}



//親オブジェクトの位置にって画像の位置を変える状態にする
void ImageBase::SetParentMove(bool flag)
{
    isParentMove = flag;
}

void ImageBase::SetShiftPos(XMFLOAT3 shift)
{
    shiftPosition = shift;
}


