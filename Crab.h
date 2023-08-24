#pragma once
#include "Engine/GameObject.h"

class Stage;
class Syari;
class RayCastData;

class Crab : public GameObject
{
    const float MAGURO_SIZE_X = 0.25f; //�}�O����X�̃T�C�Y�i1�{�j
    const float MAGURO_SIZE_Y = 0.25f; //�}�O����Y�̃T�C�Y�i1�{�j
    const float MAGURO_SIZE_Z = 1.5f;  //�}�O����Z�̃T�C�Y�i1�{�j

    const float FALL_ANGLE = 5.0f;    //������p�x
    const short ROTATE_MAX = 360;      //��]�̍ő�
    const float FALL_SPEED = 0.2f * 0.01f;     //������X�s�[�h

    const std::string vertexName[8] = {
       "Vertex_Hight_Right_Front",
       "Vertex_Hight_Right_Back",
       "Vertex_Hight_Left_Front",
       "Vertex_Hight_Left_Back",
       "Vertex_Low_Right_Front",
       "Vertex_Low_Right_Back",
       "Vertex_Low_Left_Front",
       "Vertex_Low_Left_Back"
    };

    int hModel_;     //���f���ԍ�
    bool fallFlag;   //�}�O���������邩�ǂ����t���O
    Syari* pSyari;   //�V�����̃|�C���^
    int hSyariModel; //�V�����̃��f���ԍ�
    Stage* pStage;   //�X�e�[�W�̃|�C���^
    int hGroundModel;//�X�e�[�W�̃��f���ԍ�
    XMFLOAT3 vertexBonePos[8];

    XMFLOAT3 prevPos;//1f�O�̎����̈ʒu
public:
    //�R���X�g���N�^
    Crab(GameObject* parent);

    //�f�X�g���N�^
    ~Crab();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //�e�̐e���猩���ʒu�����
    XMFLOAT3 GetParentPos()
    {
        return Math::Float3Add(GetParent()->GetPosition(), transform_.position_);
    }

    //�����ɓ�������
     //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

    /// <summary>
    /// �I�u�W�F�N�g���|�C���^�ɓ����
    /// </summary>
    void FindAllObject();

    /// <summary>
    /// ���C���΂��֐�
    /// </summary>
    RayCastData DoRay(XMFLOAT3 start, XMFLOAT3 dir, int hModel);

    /// <summary>
    /// �}�O���̕������Z
    /// </summary>
    void PhysicalOperation();
};
