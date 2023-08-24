#include "Button.h"
#include "Engine/Image.h"
#include "Engine/Direct3D.h"
#include "Engine/Input.h"
#include "Engine/Direct3D.h"

//�I�΂�Ă��Ȃ�
void Button::UnSelect()
{
	select_ = false;
}

//�I�΂�Ă���
void Button::Select()
{
	select_ = true;
}

//�����ꂽ���̏���
void Button::Event()
{
}

void Button::PreUpdate()
{
}

//�R���X�g���N�^
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

    // �萔�o�b�t�@�̍쐬
    Direct3D::pDevice_->CreateBuffer(&cb, NULL, &pConstantBuffer_);
}

//�X�V
void Button::Update()
{
    //Update�̑O�ɌĂԏ���
    PreUpdate();

    //�}�E�X����
    if (operationRight_)
    {
        //��ʂ̃T�C�Y
        const XMVECTOR windowSize = XMVectorSet(static_cast<float>(Direct3D::screenWidth_), static_cast<float>(Direct3D::screenHeight_), 0.0f, 0.0f);

        value_ = FALSE;

        //�{�^����ɂ��邩
        if (Image::OnMouseOver(hPict_))
        {
            value_ = TRUE;
            Select();
        }
    }

    if (select_)
    {
        //�����ꂽ��
        if (Input::IsMouseButtonDown(0))
        {
            Event();
        }
    }

    UnSelect();

    //�O�t���[����pathName_���Ⴄ�Ȃ�
    if (PrevPathName_ != pathName_)
    {
        //�����[�h
        //�摜�f�[�^�̃��[�h
        hPict_ = Image::Load(pathName_);
        assert(hPict_ >= 0);
    }
    PrevPathName_ = pathName_;
}

//�`��
void Button::Draw()
{
    Direct3D::pContext_->VSSetConstantBuffers(1, 1, pConstantBuffer_.GetAddressOf());
    Direct3D::pContext_->PSSetConstantBuffers(1, 1, pConstantBuffer_.GetAddressOf());

    // �p�����[�^�̎󂯓n��
    D3D11_MAPPED_SUBRESOURCE pdata;

    //��̍s��
    //�{�^���𔒂�����l
    ConstantBuffer cb = { XMMatrixIdentity(),value_ };

    Direct3D::pContext_->Map(pConstantBuffer_.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃��\�[�X�A�N�Z�X���ꎞ�~�߂�
    memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));		                    // ���\�[�X�֒l�𑗂�
    Direct3D::pContext_->Unmap(pConstantBuffer_.Get(), 0);									    // GPU����̃��\�[�X�A�N�Z�X���ĊJ

    //�`��
    Image::SetTransform(hPict_, transform_);
    Image::Draw(hPict_, shaderType_);
}

//���
void Button::Release()
{
}

//�摜�̐ݒ�
void Button::SetImage(const std::string& name)
{
    std::string fullPath = Image::DIRECTORY_BUTTON + name;
    //�摜�f�[�^�̃��[�h
    hPict_ = Image::Load(fullPath);
    //���[�h���ꂽ���m�F
    assert(hPict_ >= 0);
}

void Button::SetImage(const std::string& name, Direct3D::SHADER_TYPE type)
{
    shaderType_ = type;
    //�摜�f�[�^�̃��[�h
    hPict_ = Image::Load(name);
    //���[�h���ꂽ���m�F
    assert(hPict_ >= 0);
}

//�}�E�X�ɂ��{�^������̌������D
void Button::NoRight()
{
    operationRight_ = false;
    UnSelect();
}

//�}�E�X�ɂ��{�^������̌����t�^
void Button::Right()
{
    operationRight_ = true;
    Select();
}

bool Button::GetValue()
{
    return value_;
}
