#include "Gauge.h"
#include "Engine/Image.h"

//�R���X�g���N�^
Gauge::Gauge(GameObject* parent)
    :GameObject(parent, "Gauge"), 
    hPict_{-1,-1,-1},
    stopRatio_((float)nowHp_ / (float)maxHp_), moveRatio_(stopRatio_),


    nowHp_(250 * 60),      //����HP �i�K�X�ύX�j
    maxHp_(250 * 60),      //MaxHP�i�K�X�ύX�j
    SPEED(0.005f)     //�o�[�̈ړ����x�i���D�݂Łj
{
}

//�f�X�g���N�^
Gauge::~Gauge()
{
}

//������
void Gauge::Initialize()
{
    //�Q�[�W�̃T�C�Y�i�摜�T�C�Y����j
    transform_.scale_ = XMFLOAT3(1.5f, 1.5f, 1.0f);

    //�Q�[�W�̈ʒu�i��ʒ��S����j
    transform_.position_ = XMFLOAT3(-0.95f, 0.88f, 0);



    //�摜�t�@�C�����[�h
    {
        //�g�p����摜�t�@�C����
        const char* fileName[] = { "Gauge_Frame.png", "Gauge_Green.png", "Gauge_LightGreen.png", "Gauge_Red.png" };

        //���[�h
        for (int i = 0; i < PICT_MAX; i++)
        {
            hPict_[i] = Image::Load(fileName[i]);
            assert(hPict_[i] >= 0);
        }
    }
}

//�X�V
void Gauge::Update()
{
    //�ő�HP�ɑ΂���A����HP�̊���
    stopRatio_ = (float)nowHp_ / (float)maxHp_;

    //�o�[�𓮂���
    if (moveRatio_ < stopRatio_) moveRatio_ += SPEED;
    if (moveRatio_ > stopRatio_) moveRatio_ -= SPEED;

}

//�`��
void Gauge::Draw()
{

    Transform gaugeTrans;

    //HP�ω��Ȃ�
    if (abs(moveRatio_ - stopRatio_) < SPEED)
    {
        //�΃Q�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_GREEN]);
    }


    //�񕜒�
    else if (moveRatio_ < stopRatio_)
    {
        //���΃Q�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[PICT_LGREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_LGREEN]);

        //�΃Q�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio_;
        Image::SetTransform(hPict_[PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_GREEN]);
    }

    //�_���[�W��
    else
    {
        //�ԃQ�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= moveRatio_;
        Image::SetTransform(hPict_[PICT_RED], gaugeTrans);
        Image::Draw(hPict_[PICT_RED]);

        //�΃Q�[�W
        gaugeTrans = transform_;
        gaugeTrans.scale_.x *= stopRatio_;
        Image::SetTransform(hPict_[PICT_GREEN], gaugeTrans);
        Image::Draw(hPict_[PICT_GREEN]);
    }



    //�g
    gaugeTrans = transform_;
    Image::SetTransform(hPict_[PICT_FRAME], gaugeTrans);
    Image::Draw(hPict_[PICT_FRAME]);
}


//�J��
void Gauge::Release()
{
}

///////////////////////////////

//�_���[�W
void Gauge::Damage(int value)
{
    nowHp_ -= value;
    if (nowHp_ < 0)    nowHp_ = 0;
}

//��
void Gauge::Recovery(int value)
{
    nowHp_ += value;
    if (nowHp_ > maxHp_) nowHp_ = maxHp_;
}

void Gauge::SetMaxHP(int maxHP)
{
    maxHp_ = maxHP;
}

void Gauge::SetNowHP(int nowHP)
{
    nowHp_ = nowHP;
}

int Gauge::GetMaxHP()
{
    return maxHp_;
}

int Gauge::GetNowHP()
{
    return nowHp_;
}
