#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

//�N���X�̑O���錾
class GameObject;
class BoxCollider;
class SphereCollider;


//�����蔻��̃^�C�v
enum ColliderType
{
	COLLIDER_BOX,		//���^
	COLLIDER_CIRCLE		//����
};

//-----------------------------------------------------------
//�����蔻����Ǘ�����N���X
//-----------------------------------------------------------
class Collider
{
	//���ꂼ��̃N���X��private�����o�ɃA�N�Z�X�ł���悤�ɂ���
	friend class BoxCollider;
	friend class SphereCollider;

	//���̊
	const XMVECTOR AXIS_BASE_X = { 1.0f,0,0 };
	const XMVECTOR AXIS_BASE_Y = { 0,1.0f,0 };
	const XMVECTOR AXIS_BASE_Z = { 0,0,1.0f };

protected:
	GameObject*		pGameObject_;	//���̔���������Q�[���I�u�W�F�N�g
	ColliderType	type_;			//���
	XMFLOAT3		center_;		//���S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
	XMFLOAT3		size_;			//����T�C�Y�i���A�����A���s���j
	int				hDebugModel_;	//�f�o�b�O�\���p�̃��f����ID

public:

	//�֐��|�C���^
	using FunctionPtr = void (GameObject::*)(GameObject*);

	FunctionPtr OnCollision;  //�����������ɌĂ΂��֐��̃|�C���^
	FunctionPtr OutCollision; //������Ȃ��Ȃ������ɌĂ΂��֐��̃|�C���^

	//�֐��|�C���^�Z�b�g����Ƃ�
	void SetHitFunc(FunctionPtr func) { OnCollision = func; }
	void SetHitOutFunc(FunctionPtr func) { OutCollision = func; }

	//�R���X�g���N�^
	Collider();

	//�f�X�g���N�^
	virtual ~Collider();

	//�ڐG����i�p�����SphereCollider��BoxCollider�ŃI�[�o�[���C�h�j
	//�����Ftarget	����̓����蔻��
	//�ߒl�F�ڐG���Ă��true
	virtual bool IsHit(Collider* target) = 0;

	//���^���m�̏Փ˔���
	//�����FboxA	�P�ڂ̔��^����
	//�����FboxB	�Q�ڂ̔��^����
	//�ߒl�F�ڐG���Ă����true
	bool IsHitBoxVsBox(BoxCollider* boxA, BoxCollider* boxB);

	//���^�Ƌ��̂̏Փ˔���
	//�����Fbox	���^����
	//�����Fsphere	�Q�ڂ̔��^����
	//�ߒl�F�ڐG���Ă����true
	bool IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere);

	//���̓��m�̏Փ˔���
	//�����FcircleA	�P�ڂ̋��̔���
	//�����FcircleB	�Q�ڂ̋��̔���
	//�ߒl�F�ڐG���Ă����true
	bool IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB);

	//�����������ɌĂ΂��֐��|�C���^���Z�b�g
	template<class T>
	void SetHitFunc(void (T::* func)(GameObject*)) { SetHitFunc(static_cast<FunctionPtr>(func)); }

	//������Ȃ��Ȃ������ɌĂ΂��֐��̃|�C���^���Z�b�g
	template<class T>
	void SetHitOutFunc(void (T::* func)(GameObject*)) { SetHitOutFunc(static_cast<FunctionPtr>(func)); }

	//�e�X�g�\���p�̘g��`��
	//�����Fposition	�I�u�W�F�N�g�̈ʒu
	void Draw(XMFLOAT3 position);

	//�Z�b�^�[
	void SetGameObject(GameObject* gameObject) { pGameObject_ = gameObject; }

private:

	

};

