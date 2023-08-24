#pragma once
#include "Engine/GameObject.h"

class Controller : public GameObject
{
    XMFLOAT3 cameraAngle;//�J�����̏����ʒu�̊p�x
    float    cameraDistance;
public:
    //�R���X�g���N�^
    Controller(GameObject* parent);

    //�f�X�g���N�^
    ~Controller();

    //������
    void Initialize() override;

    //�X�V
    void Update() override;

    //�`��
    void Draw() override;

    //�J��
    void Release() override;

    //���݈ʒu�̃Q�b�^�[
    XMFLOAT3 GetPosition();

    //�����̃Q�b�^�[
    XMFLOAT3 GetRotate();

    /// <summary>
    /// �R���g���[���[�ŃJ��������]������֐�
    /// </summary>
    /// <param name="position">�R���g���[���[�̈ʒu��ς���</param>
    void SetCameraPos(XMFLOAT3 position);

    /// <summary>
    /// ���[�v���g�p���ăR���g���[���[�ŃJ��������]������֐�
    /// </summary>
    /// <param name="position">���B����ׂ��ʒu</param>
    /// <param name="attenRate">�����䗦(1{���{ }���0.1�̕�����������)</param>
    void SetCameraLerpPos(XMFLOAT3 position, float attenRate);

    /// <summary>
    /// ���[�v����FoV�g�p���ăR���g���[���[�ŃJ��������]������֐�
    /// �����Ă������ǂ����ɂ����FoV��ύX
    /// </summary>
    /// <param name="isMoved">�����Ă�����</param>
    void ChangeFovMove(bool isMoved);

    /// <summary>
    /// �J�����̈ʒu���ǂƏՓ˂��Ă��邩��Ԃ�
    /// </summary>
    /// <returns>�Փ˂��Ă��邩</returns>
    bool IsCameraCollision();

    /// <summary>
    /// �J�����̋����̃Z�b�^�[
    /// </summary>
    /// <param name="distance">����</param>
    void SetCameraDistance(float distance);

    /// <summary>
    /// �J�����̋����̃Q�b�^�[
    /// </summary>
    /// <returns>����</returns>
    float GetCameraDistance();
};

