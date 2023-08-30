#pragma once
#include "Engine/GameObject.h"
#include "VFX.h"

class Stage;
class Syari;
class RayCastData;
class PlayerBase;

class Maguro : public GameObject
{
    const float MAGURO_SIZE_X = 0.25f; //�}�O����X�̃T�C�Y�i1�{�j
    const float MAGURO_SIZE_Y = 0.25f; //�}�O����Y�̃T�C�Y�i1�{�j
    const float MAGURO_SIZE_Z = 1.5f;  //�}�O����Z�̃T�C�Y�i1�{�j

    const float FALL_ANGLE = 0.1f;    //������p�x
    const short ROTATE_MAX = 360;      //��]�̍ő�
    const XMFLOAT3 ROTATE_STAGING_ANGE = { 0.3f, 0.5f, 0.7f };
    //const float FALL_SPEED = 0.2f * 0.03f;     //������X�s�[�h

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

    int hModel_;            //���f���ԍ�
    bool isLandingMotion;   //�������[�V�����ɓ����Ă��邩
    bool isFullFall;        //���������������ǂ���
    //Syari* pSyari;        //�V�����̃|�C���^
    int hSyariModel;        //�V�����̃��f���ԍ�
    Stage* pStage;          //�X�e�[�W�̃|�C���^
    int hGroundModel;       //�X�e�[�W�̃��f���ԍ�
    XMFLOAT3 vertexBonePos[8];
    XMFLOAT3 prevPos;       //1f�O�̎����̈ʒu
    float gravity;          //���󂯂Ă���d�̗͂�(�}�C�i�X�Ȃ�d�͂�U��؂��ď�ɍs��)
    Syari* pSyari;          //�e�̃|�C���^
    EmitterData explosion;  //�����G�t�F�N�g�̏��

    
public:
    //�R���X�g���N�^
    Maguro(GameObject* parent);

    //�f�X�g���N�^
    ~Maguro();

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

    /// <summary>
    /// �������o
    /// </summary>
    void LandingStaging();

    /// <summary>
    /// �������̉�]���o
    /// </summary>
    void RotationStaging();

    /// <summary>
    /// �d�͂̏���
    /// </summary>
    void Gravity();


};