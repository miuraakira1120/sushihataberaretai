#pragma once
#include "Engine/GameObject.h"

//�摜���o�������̃N���X
class ImageBase : public GameObject
{
    int hPict_;                //�摜�ԍ�
    std::string PrevPathName_; //1�t���[���O�̉摜�ԍ�  

    bool isParentMove;//�e�I�u�W�F�N�g�̈ʒu�ɂ��ĉ摜�̈ʒu��ς���
    XMFLOAT3 shiftPosition;//�e�I�u�W�F�N�g�̈ʒu�ɂ��ĉ摜�̈ʒu��ς��鎞�Ɏg���A���炷�l

public:
    //�R���X�g���N�^
    ImageBase(GameObject* parent, std::string pathName, int alpha = 255);

    //�f�X�g���N�^
    ~ImageBase();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    
    /// <summary>
    /// �e�I�u�W�F�N�g�̈ʒu�ɂ��ĉ摜�̈ʒu��ς���
    /// </summary>
    /// <returns>�ύX��̃X�N���[�����W</returns>
    XMFLOAT3 parentObjectPositionByImagePosition();

    /// <summary>
    /// �e�I�u�W�F�N�g�̈ʒu�ɂ��ĉ摜�̈ʒu��ς����Ԃɂ���
    /// </summary>
    /// <returns>�ύX��̃X�N���[�����W</returns>
    void SetParentMove(bool flag);

    /// <summary>
    /// shiftPosition�̃Z�b�^�[
    /// </summary>
    void SetShiftPos(XMFLOAT3 shift);

};