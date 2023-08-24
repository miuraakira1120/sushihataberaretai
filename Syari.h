#pragma once

#include <vector>
#include "Engine/GameObject.h"
#include "Engine/Model.h"
#include "Gauge.h"
#include "PoryLine.h"

#define VERTEX_VLU 8

class OBB;
class RedBox;
class BlueBox;

static const float SYARI_SIZE_X = 0.5f; //�V������X�̃T�C�Y�i1�{�j
static const float SYARI_SIZE_Y = 0.5f; //�V������Y�̃T�C�Y�i1�{�j
static const float SYARI_SIZE_Z = 1.0f; //�V������Z�̃T�C�Y�i1�{�j
const int BONE_DIRECTION_ARRAY_SIZE = 6;

using std::vector;

static enum  Ver
{
    UP_RIGHT_FRONT = 0,
    UP_RIGHT_BACK,
    UP_LEFT_FRONT,
    UP_LEFT_BACK,
    DOWN_RIGHT_FRONT,
    DOWN_RIGHT_BACK,
    DOWN_LEFT_FRONT,
    DOWN_LEFT_BACK,
    VERTEX_MAX,
};

class Syari : public GameObject
{
    enum ShortDistance
    {
        LEFTEST,
        RIGHTEST,
        FOREMOST,
        INNERMOST,
        SHORT_DISTANCE_MAX
    };

    enum Direction
    {
        TOP = 0,
        BOTOM,
        LEFT,
        RIGHT,
        FRONT,
        BACK,
        DOWN_RIGHT_FRONT,
        DOWN_RIGHT_BACK,
        DOWN_LEFT_FRONT,
        DOWN_LEFT_BACK,
        DIRECTION_MAX
    };

     XMFLOAT3 direction[6] = {
        {  0,  1,  0  }, //��
        {  0, -1,  0  }, //��
        { -1,  0,  0  }, //��
        {  1,  0,  0  }, //�E
        {  0 , 0, -1  }, //��O
        {  0,  0,  1  }  //��
    };

    const float directionDistance[6] = {
        SYARI_SIZE_Y,
        -SYARI_SIZE_Y,
        -SYARI_SIZE_X,
        SYARI_SIZE_X,
        -SYARI_SIZE_Z,
        SYARI_SIZE_Z
    };

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

    const float SYARI_SPEED = 0.25f;//�V�����̃X�s�[�h
    const float ROTATE_SPEED = 0.2f; //�V�����̉�]�̃X�s�[�h
    const float FALL_SPEED = 0.02f; //������X�s�[�h
    const float SPEED_LIMIT = 0.5f;  //�����̑��x���E 2->0.5
    const float JUMP_SPEED = 1.0f; //�W�����v�̃X�s�[�h
    const float SPEED_OF_JUMP = 0.4f; //�������x

    const XMVECTOR upRightFrontPos = { 0.5f, 0.5f, 1.0f };//�V�����̏�E�O�̈ʒu
    const XMVECTOR upRightBackPos = { 0.5f, 0.5f, -1.0f };//�V�����̏�E��̈ʒu
    const XMVECTOR upLeftFrontPos = { -0.5f, 0.5f, 1.0f };//�V�����̏㍶�O�̈ʒu
    const XMVECTOR upLeftBackPos = { -0.5f, 0.5f, -1.0f };//�V�����̏㍶��̈ʒu
    const XMVECTOR downRightFrontPos = { 0.5f, -0.5f, 1.0f };//�V�����̉����O�̈ʒu
    const XMVECTOR downRightBackPos = { 0.5f, -0.5f, -1.0f };//�V�����̉��E��̈ʒu
    const XMVECTOR downLeftFrontPos = { -0.5f, -0.5f, 1.0f };//�V�����̉����O�̈ʒu
    const XMVECTOR downLeftBackPos = { -0.5f, -0.5f, -1.0f };//�V�����̉�����̈ʒu

    vector<XMVECTOR> vVertexPos;
    int hModel_;    //���f���ԍ�
    int mode;     //���[�h
    bool breakFlag = false;
    XMFLOAT3 axisPos;
    XMFLOAT3 prevPos;
    XMFLOAT3 prevBonePos[VERTEX_MAX]; //1f�O�̊p�̈ʒu
    bool isGround;   //�n�ʂɐݒu���Ă��邩
    XMFLOAT3 upDistanceDifference;

    //�Q�[�W�I�u�W�F�N�g
    Gauge* pGauge_;
    float jumpSpeed;
    PoryLine* pLine;
    int countTime;
    XMVECTOR vMove;
    XMFLOAT3 fMove;

    XMVECTOR flipped;
    XMFLOAT3 prevPosMove;//1f�O�̎����̈ʒu
public:
    float accel;//���ǂꂾ���������邩
    XMFLOAT3 fupRightFrontPos;
    XMFLOAT3 vertexBonePos[VERTEX_MAX];
    //�R���X�g���N�^
    Syari(GameObject* parent);

    //�f�X�g���N�^
    ~Syari();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //���f���̃Q�b�^�[
    int GetModelHandle() { return hModel_; }

    /// <summary>
    /// �L�[������܂Ƃ߂�֐�
    /// </summary>
    void KeyOperation();

    //�W�����v����
    void Jump();

    //�ړ�����֐�
    void Move();

    /// <summary>
    /// ���󒆂ɂ��邩�ǂ������ׂ�֐�
    /// </summary>
    /// <returns>
    /// �^�@�󒆂ɂ���
    /// �U�@�󒆂ɂ��Ȃ�
    /// </returns>
    bool isFly();

    //�}�E�X�ɂ���]
    void MoveMouse();

    /// <summary>
    /// OBB�ƕ��ʂ̏Փ˔���
    /// </summary>
    bool OBBvsPlane(OBB& obb, XMFLOAT3 pos, XMVECTOR nomal, float* Len = 0);
     
    //�����ɓ�������
    //�����FpTarget ������������
    void OnCollision(GameObject* pTarget) override;

    /////�Z�b�^�[
    void SetFlipped(XMVECTOR fl);

    //�Q�b�^�[
    XMFLOAT3 GetUpDistanceDifference();

};