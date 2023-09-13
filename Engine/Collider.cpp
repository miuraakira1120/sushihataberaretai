#include "BoxCollider.h"
#include "SphereCollider.h"
#include "GameObject.h"
#include "Model.h"
#include "Transform.h"

#include "../OBB.h"

//�R���X�g���N�^
Collider::Collider():
	pGameObject_(nullptr)
{
}

//�f�X�g���N�^
Collider::~Collider()
{
}

//���^���m�̏Փ˔���
//�����FboxA	�P�ڂ̔��^����
//�����FboxB	�Q�ڂ̔��^����
//�ߒl�F�ڐG���Ă����true
bool Collider::IsHitBoxVsBox(BoxCollider* boxA, BoxCollider* boxB)
{

	XMFLOAT3 boxPosA = Math::Float3Add(boxA->pGameObject_->GetWorldPosition(), boxA->center_);
	XMFLOAT3 boxPosB = Math::Float3Add(boxB->pGameObject_->GetWorldPosition(), boxB->center_);

	//OBB�œ����蔻��
	OBB boxAOBB, boxBOBB;

	//OBB�ɕK�v�Ȏ��̃��X�g�����
	//�e���ɑ΂���x�N�g�������߂�
	XMMATRIX rotateX, rotateY, rotateZ, m;
	rotateX = XMMatrixRotationX(XMConvertToRadians(boxA->pGameObject_->GetTransform().rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(boxA->pGameObject_->GetTransform().rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(boxA->pGameObject_->GetTransform().rotate_.z));
	//��]�s������߂�
	m = rotateZ * rotateX * rotateY;
	//���X�g�ɃZ�b�g����
	std::vector<XMVECTOR> fAxisA = { 
		XMVector3TransformCoord(AXIS_BASE_X, m), 
		XMVector3TransformCoord(AXIS_BASE_Y, m), 
		XMVector3TransformCoord(AXIS_BASE_Z, m)
	};

	//�e���ɑ΂���x�N�g�������߂�
	rotateX = XMMatrixRotationX(XMConvertToRadians(boxB->pGameObject_->GetTransform().rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(boxB->pGameObject_->GetTransform().rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(boxB->pGameObject_->GetTransform().rotate_.z));
	
	//���X�g�ɃZ�b�g����
	std::vector<XMVECTOR> fAxisB = {
		XMVector3TransformCoord(AXIS_BASE_X, m),
		XMVector3TransformCoord(AXIS_BASE_Y, m),
		XMVector3TransformCoord(AXIS_BASE_Z, m)
	};

	//OBB�ɕK�v�Ȓ����̃��X�g�����
	std::vector<float> fLengthA = { boxA->size_.x / 2, boxA->size_.y / 2, boxA->size_.z / 2};
	std::vector<float> fLengthB = { boxB->size_.x, boxB->size_.y, boxB->size_.z};

	//OBB�ɕK�v�ȏ����Z�b�g����
	boxAOBB.SetOBBAll(XMLoadFloat3(&boxPosA), fAxisA, fLengthA);
	boxBOBB.SetOBBAll(XMLoadFloat3(&boxPosB), fAxisB, fLengthB);

	//OBB��OBB�̏Փ˔���
	if (boxAOBB.ColOBBs(boxAOBB, boxBOBB))
	{
		return true;
	}
	return false;
}

//���^�Ƌ��̂̏Փ˔���
//�����Fbox	���^����
//�����Fsphere	�Q�ڂ̔��^����
//�ߒl�F�ڐG���Ă����true
bool Collider::IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere)
{
	XMFLOAT3 boxPos = Math::Float3Add(box->pGameObject_->GetWorldPosition(), box->center_);
	//OBB�œ����蔻��
	OBB boxOBB;

	//OBB�ɕK�v�Ȏ��̃��X�g�����
	//�e���ɑ΂���x�N�g�������߂�
	XMMATRIX rotateX, rotateY, rotateZ, m;
	rotateX = XMMatrixRotationX(XMConvertToRadians(box->pGameObject_->GetTransform().rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(box->pGameObject_->GetTransform().rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(box->pGameObject_->GetTransform().rotate_.z));
	//��]�s������߂�
	m = rotateZ * rotateY * rotateX;
	//���X�g�ɃZ�b�g����
	std::vector<XMVECTOR> fAxis = {
		XMVector3TransformCoord(AXIS_BASE_X, m),
		XMVector3TransformCoord(AXIS_BASE_Y, m),
		XMVector3TransformCoord(AXIS_BASE_Z, m)
	};
	//OBB�ɕK�v�Ȓ����̃��X�g�����
	std::vector<float> fLength = { box->size_.x / 2 , box->size_.y / 2, box->size_.z / 2};
	//OBB�ɕK�v�ȏ����Z�b�g����
	boxOBB.SetOBBAll(XMLoadFloat3(&boxPos), fAxis, fLength);

	if (boxOBB.LenOBBToPoint(boxOBB, Math::Float3Add(sphere->pGameObject_->GetWorldPosition(), sphere->center_)) <= sphere->size_.x)
	{
		return true;
	}
	return false;

}

//���̓��m�̏Փ˔���
//�����FcircleA	�P�ڂ̋��̔���
//�����FcircleB	�Q�ڂ̋��̔���
//�ߒl�F�ڐG���Ă����true
bool Collider::IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB)
{
	XMFLOAT3 centerA = circleA->center_;
	XMFLOAT3 positionA = circleA->pGameObject_->GetWorldPosition();
	XMFLOAT3 centerB = circleB->center_;
	XMFLOAT3 positionB = circleB->pGameObject_->GetWorldPosition();

	XMVECTOR v = (XMLoadFloat3(&centerA) + XMLoadFloat3(&positionA))
		- (XMLoadFloat3(&centerB) + XMLoadFloat3(&positionB));

	if (XMVector3Length(v).m128_f32[0] <= circleA->size_.x + circleB->size_.x)
	{
		return true;
	}

	return false;
}

//�e�X�g�\���p�̘g��`��
//�����Fposition	�I�u�W�F�N�g�̈ʒu
void Collider::Draw(XMFLOAT3 position)
{
	Transform transform;
	transform.position_ = XMFLOAT3(position.x + center_.x, position.y + center_.y, position.z + center_.z);
	transform.scale_ = size_;
	transform.rotate_ = pGameObject_->GetTransform().rotate_;
	transform.Calclation();
	Model::SetTransform(hDebugModel_, transform);
	Model::Draw(hDebugModel_);
}
