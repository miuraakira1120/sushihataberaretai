#include "ImageBase.h"
#include "Engine/Image.h"
#include "Engine/Camera.h"
#include "Player.h"
#include "Imgui_Obj.h"

//�R���X�g���N�^
ImageBase::ImageBase(GameObject* parent, std::string pathName, int alpha)
    :GameObject(parent, "ImageBase"),hPict_(-1), isParentMove(false),shiftPosition()
{
    SetPathName(pathName);
    SetAlpha(alpha);
}

//�f�X�g���N�^
ImageBase::~ImageBase()
{
}

//������
void ImageBase::Initialize()
{
    std::string fullPath = Image::DIRECTORY_UI + pathName_;
    //�摜�f�[�^�̃��[�h
    hPict_ = Image::Load(fullPath);
    assert(hPict_ >= 0);

    PrevPathName_ = pathName_;

    Imgui_Obj::AddDebugLogList(this);
}

//�X�V
void ImageBase::Update()
{
    //�O�t���[����pathName_���Ⴄ�Ȃ�
    if (PrevPathName_ != pathName_)
    {
        std::string fullPath = Image::DIRECTORY_UI + pathName_;
        //�����[�h
        //�摜�f�[�^�̃��[�h
        hPict_ = Image::Load(fullPath);
        assert(hPict_ >= 0);
    }
    PrevPathName_ = pathName_;
}

//�`��
void ImageBase::Draw()
{
    //�A���t�@�l���Z�b�g����
    Image::SetAlpha(hPict_, alpha_);

    //�ʏ�̏��
    if (!isParentMove)
    {
        Image::SetTransform(hPict_, transform_);
    }
    //�e�I�u�W�F�N�g�̈ʒu�ɂ��ĉ摜�̈ʒu��ς�����
    else
    {       
        Transform scrTransform = transform_;
        scrTransform.position_ = parentObjectPositionByImagePosition();
        Image::SetTransform(hPict_, scrTransform);
    }

    //�`��
    Image::Draw(hPict_);
}

//�J��
void ImageBase::Release()
{
}

//�e�I�u�W�F�N�g�̈ʒu�ɂ��ĉ摜�̈ʒu��ς���
XMFLOAT3 ImageBase::parentObjectPositionByImagePosition()
{
    //�e�I�u�W�F�N�g���X�N���[�����W�ɕϊ�
    XMFLOAT3 scrParentPos = Camera::ToWorldCalcScreen(Math::Float3Add(GetParent()->GetPosition(), transform_.position_));
    //scrParentPos = Math::Float3Add( scrParentPos, transform_.position_);
    return scrParentPos;
}



//�e�I�u�W�F�N�g�̈ʒu�ɂ��ĉ摜�̈ʒu��ς����Ԃɂ���
void ImageBase::SetParentMove(bool flag)
{
    isParentMove = flag;
}

void ImageBase::SetShiftPos(XMFLOAT3 shift)
{
    shiftPosition = shift;
}


