#include "Button.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"
#include "Engine/Direct3D.h"

//選ばれていない
void Button::UnSelect()
{
	select_ = false;
}

//選ばれている
void Button::Select()
{
	select_ = true;
}

//押された時の処理
void Button::Event()
{
}

void Button::PreUpdate()
{
}

//コンストラクタ
Button::Button(GameObject* parent, const std::string& name)
    :GameObject(parent, name), hPict_(-1), value_(0.0f), select_(false), operationRight_(true), shaderType_(Direct3D::SHADER_TYPE::SHADER_2D), PrevPathName_(pathName_)
{
    D3D11_BUFFER_DESC cb;
    cb.ByteWidth = sizeof(ConstantBuffer);
    cb.Usage = D3D11_USAGE_DYNAMIC;
    cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cb.MiscFlags = 0;
    cb.StructureByteStride = 0;

    // 定数バッファの作成
    Direct3D::pDevice_->CreateBuffer(&cb, NULL, &pConstantBuffer_);
}

//更新
void Button::Update()
{
    //Updateの前に呼ぶ処理
    PreUpdate();

    //マウス操作
    if (operationRight_)
    {
        //画面のサイズ
        const XMVECTOR windowSize = XMVectorSet(static_cast<float>(Direct3D::screenWidth_), static_cast<float>(Direct3D::screenHeight_), 0.0f, 0.0f);

        value_ = FALSE;

        //ボタン上にあるか
        if (Image::OnMouseOver(hPict_))
        {
            value_ = TRUE;
            Select();
        }
    }

    if (select_)
    {
        //押されたか
        if (Input::IsMouseButtonDown(0))
        {
            Event();
        }
    }

    UnSelect();

    //前フレームとpathName_が違うなら
    if (PrevPathName_ != pathName_)
    {
        //リロード
        //画像データのロード
        hPict_ = Image::Load(pathName_);
        assert(hPict_ >= 0);
    }
    PrevPathName_ = pathName_;
}

//描画
void Button::Draw()
{
    Direct3D::pContext_->VSSetConstantBuffers(1, 1, pConstantBuffer_.GetAddressOf());
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, pConstantBuffer_.GetAddressOf());

    // パラメータの受け渡し
    D3D11_MAPPED_SUBRESOURCE pdata;

    //空の行列
    //ボタンを白くする値
    ConstantBuffer cb = { XMMatrixIdentity(),value_ };

    Direct3D::pContext_->Map(pConstantBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのリソースアクセスを一時止める
    memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));		                    // リソースへ値を送る
    Direct3D::pContext_->Unmap(pConstantBuffer_.Get(), 0);									    // GPUからのリソースアクセスを再開

    //描画
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_, shaderType_);
}

//解放
void Button::Release()
{
}

//画像の設定
void Button::SetImage(const std::string& name)
{
    std::string fullPath = Image::DIRECTORY_BUTTON + name;
    //画像データのロード
    hPict_ = Image::Load(fullPath);
    //ロードされたか確認
    assert(hPict_ >= 0);
}

void Button::SetImage(const std::string& name, Direct3D::SHADER_TYPE type)
{
    shaderType_ = type;
    //画像データのロード
    hPict_ = Image::Load(name);
    //ロードされたか確認
    assert(hPict_ >= 0);
}

//マウスによるボタン操作の権限剥奪
void Button::NoRight()
{
    operationRight_ = false;
    UnSelect();
}

//マウスによるボタン操作の権限付与
void Button::Right()
{
    operationRight_ = true;
    Select();
}

bool Button::GetValue()
{
    return value_;
}
