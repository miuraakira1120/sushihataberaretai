#pragma once
#include "Neta.h"
#include "Engine/GameObject.h"

class Tuna : public Neta
{
	//�X�L�������߂鎞�Ԃ̍ő�l
	const float ACCUMULATE_MAX = 4.0f;

	//�X�L���̔�������
	const int SKILL_TIME_ACCEL = 30;
	const int SKILL_TIME_KEEP  = 45;
	const int SKILL_TIME_DECEL = 35;
	const int SKILL_TIME = SKILL_TIME_ACCEL + SKILL_TIME_KEEP + SKILL_TIME_DECEL;

	//���ȉ��̑��x�ɂȂ����痎����
	const float CONSTANT_SPEED = 2.0f;

	//������
	const float ACCELERATION_RATE = 0.02f;

	//������
	const float DECELERATION_RATE = 0.05f;

	//���݂��߂Ă���X�L���̎���
	float accumulateTime;

	//�X�L���������Ɏg������
	int skillTime;

	//�X�L���𔭓����Ă��邩�ǂ���
	bool isSkill;

	//�X�L���g�p���̉����x
	float accel;

	//�X�L���g�p���Ɏg���t���O
	bool accelFlag;

public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	/// <param name="pathName">���f���̃t�@�C����</param>
	Tuna(GameObject* parent, std::string pathName);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �ŗL�̃X�L��
	/// �}�O��:�ːi
	/// </summary>
	virtual void Skill() override;
};

