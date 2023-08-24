#pragma once
#include <DirectXMath.h>

using namespace DirectX;

enum TransMode
{
	TRANS_NORMAL_MODE,			//��{�I�ȍ��W
	TRANS_AXIS_MODE,			//�����ړ����ĉ�]���邩
	TRANS_CHANGEPARENT_MODE,	//�e��ς��Ĉړ�
	TRANS_NONROTATE,			//rotate_���g�킸�ɉ�]
	TRANS_MAX,
};

//-----------------------------------------------------------
//�ʒu�A�����A�g�嗦�Ȃǂ��Ǘ�����N���X
//-----------------------------------------------------------
class Transform
{
private:
	TransMode transMode;		//����TransMode
	
public:
	XMMATRIX matTranslate_;		//�ړ��s��
	XMMATRIX matRotate_;		//��]�s��
	XMMATRIX changeMatRotate_;	//TRANS_NONROTATE�̎��̉�]�s��	
	XMMATRIX matScale_;			//�g��s��
	XMFLOAT3 position_;			//�ʒu
	XMFLOAT3 rotate_;			//����
	XMFLOAT3 scale_;			//�g�嗦
	Transform * pParent_;		//�e�I�u�W�F�N�g�̏��
	XMFLOAT3 axisMatrix_;		//���̃}�g���N�X�����ɉ�]����
	Transform* transParentTmp;	//�e�������̂ڂ邽�߂Ɏg���|�C���^�ϐ�
	unsigned int parentNum;		//�e���ǂꂭ�炢�����̂ڂ邩
	unsigned int NumberOfLoops;	//���񃋁[�v������
	unsigned int pravTransMode;	//1�t���[���O��TransMode
	

	//�R���X�g���N�^
	Transform();

	//�f�X�g���N�^
	~Transform();

	//�e�s��̌v�Z
	//�����F�Ȃ�
	//�ߒl�F�Ȃ�
	void Calclation();

	//���[���h�s����擾
	//�����F�Ȃ�
	//�ߒl�F���̎��_�ł̃��[���h�s��
	XMMATRIX GetWorldMatrix();

	void NomalAxisRotate();	//�����ړ����Ȃ��ŉ�]����
	void MoveAxisRotate();  //�����ړ����ĉ�]����

	/// <summary>
	/// ��]�̐e��ς���
	/// </summary>
	/// <param name="����1 parentNum : ���Ԗڂ̐e�ŉ�]���邩(0�����̐e)"></param>
	void ChangeParentRotate(int parentNum_);

	void SetAxisTrans(XMFLOAT3 mat);//���̎��ŉ��

	/// <summary>
	/// ���������߂�֐�
	/// </summary>
	/// <param name="����1 : �ʒu1"></param>
	/// <param name="����2 : �ʒu2"></param>
	/// <returns></returns>
	static float FloatDistance(XMFLOAT3 a, XMFLOAT3 b)
	{
		float abX = a.x - b.x;
		float abY = a.y - b.y;
		float abZ = a.z - b.z;
		return (float)sqrt((abX * abX) + (abY + abY) + (abZ + abZ));
	}

	/// <summary>���_��ʂ�C�ӎ���]</summary>
	/// <param name="pos">�ړ������������̂̈ʒu</param>
	/// <param name="rot">��]�p�x(�x���@)</param>
	/// <param name="axis">���_�ȊO�̎��ƂȂ�ʒu�x�N�g��</param>
	/// <param name="end">���̂�����[�̈ʒu�x�N�g��(���w��Ō��_�ɂȂ�)</param>
	void ArbRotationAxis(XMFLOAT3* pos, float rot, XMVECTOR axis, XMVECTOR end = { 0,0,0,0 });

	/// <summary>���_��ʂ�C�ӎ���]</summary>
	/// <param name="pos">�ړ������������̂̈ʒu</param>
	/// <param name="rad">��]�p�x(���W�A��)</param>
	/// <param name="axis">���_�ȊO�̎��ƂȂ�ʒu�x�N�g��</param>
	/// <param name="end">���̂�����[�̈ʒu�x�N�g��(���w��Ō��_�ɂȂ�)</param>
	void ArbRotationAxisR(XMFLOAT3* pos, float rad, XMVECTOR axis, XMVECTOR end = { 0,0,0,0 });

	//��]�̃��[�h��ς���
	void SetRotateMode(TransMode mode);
};

