#pragma once
#include <DirectXMath.h>
#include <list>
#include <string>
#include <assert.h>
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "Math.h"

using namespace DirectX;


//-----------------------------------------------------------
//�S�ẴQ�[���I�u�W�F�N�g�i�V�[�����܂߂āj���p������C���^�[�t�F�[�X
// �Q�[���I�u�W�F�N�g�́A�e�q�\���ɂȂ��Ă��āA
// �}�g���N�X�̉e�����󂯂邱�ƂɂȂ�
//-----------------------------------------------------------
class GameObject
{
protected:
	
	//�ʒu������Ȃǂ��Ǘ�����I�u�W�F�N�g
	Transform				 transform_;

	//�I�u�W�F�N�g�̖��O
	const std::string		 objectName_;

	//�Փ˔��胊�X�g
	std::list<Collider*>	 colliderList_;	

	//�I�u�W�F�N�g�̃^�O
	std::string	   			 tag_;

	//�O�t���[������̈ړ��x�N�g��
	XMVECTOR				 vMoved;

	//���f����摜�t�@�C���̖��O
	std::string				 pathName_;

	//�I�u�W�F�N�g���Ƃ̃��j�[�N�Ȗ��O
	std::string				 uniqueName_;

	//�A���t�@�l
	int						 alpha_;


public:
	//�R���X�g���N�^
	GameObject();
	GameObject(GameObject* parent);
	GameObject(GameObject* parent, const std::string& name);
	GameObject(GameObject* parent, const std::string& name, const std::string& pathFilename);

	//�f�X�g���N�^
	virtual ~GameObject();

	//�e�I�u�W�F�N�g�ŕK�����֐�
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw() = 0;
	virtual void Release(void) = 0;

	//�p�����Ŏg�p�g�p���邽�߂̊֐�
	//�X�V���Ă΂��O�ɐݒ肵�Ă����������̂����鎞�Ɏg��
	virtual void SetUp() {};

	//�����̊Y���֐���ǂ񂾌�A�q���̊֐����Ă�
	void UpdateSub();
	void DrawSub();
	void ReleaseSub();


	////���[�J���s��̎擾�i���̃I�u�W�F�N�g�̍s��j
	////�ߒl�F���[�J���s��
	//XMMATRIX GetLocalMatrix();

	//���[���h�s��̎擾�i�e�̉e�����󂯂��ŏI�I�ȍs��j
	//�ߒl�F���[���h�s��
	XMMATRIX GetWorldMatrix();



	//�e�t���O�̐���
	bool IsDead();			// �폜���邩�ǂ���
	void KillMe();			// �������폜����
	void Enter();			// Update������
	void Leave();			// Update������
	void Visible();			// Draw������
	void Invisible();		// Draw������
	bool IsInitialized();	// �������ς݂��ǂ���
	void SetInitialized();	// �������ς݂ɂ���
	bool IsEntered();		// Update���s���Ă�����
	bool IsVisibled();		// Draw���s���Ă�����
	void DoSetUp();			//�Z�b�g�A�b�v������������Ԃɂ���
	bool IsSetUp();			//�Z�b�g�A�b�v���������Ă��邩
	void PutShadow();		//�e������
	void DeleteShadow();	//�e������
	bool IsSyadow();		


	//�q�I�u�W�F�N�g���X�g���擾
	//�ߒl�F�q�I�u�W�F�N�g���X�g
	std::list<GameObject*>* GetChildList();

	//�e�I�u�W�F�N�g���擾
	//�ߒl�F�e�I�u�W�F�N�g�̃A�h���X
	GameObject* GetParent();

	//���O�ŃI�u�W�F�N�g�������i�Ώۂ͎����̎q���ȉ��j
	//�����Fname	�������閼�O
	//�ߒl�F�������I�u�W�F�N�g�̃A�h���X�i������Ȃ����nullptr�j
	GameObject* FindChildObject(const std::string& name);

	//���O�ŃI�u�W�F�N�g�������i�Ώۂ͑S�́j
	//�����F�������閼�O
	//�ߒl�F�������I�u�W�F�N�g�̃A�h���X
	GameObject* FindObject(const std::string& name) { return GetRootJob()->FindChildObject(name); }

	//�I�u�W�F�N�g�̖��O���擾
	//�ߒl�F���O
	const std::string& GetObjectName(void) const;

	//�q�I�u�W�F�N�g��ǉ��i���X�g�̍Ō�ցj
	//�����F�ǉ�����I�u�W�F�N�g
	void PushBackChild(GameObject* obj);

	//�q�I�u�W�F�N�g��ǉ��i���X�g�̐擪�ցj
	//�����Fobj �ǉ�����I�u�W�F�N�g
	void PushFrontChild(GameObject* obj);

	//�q�I�u�W�F�N�g��S�č폜
	void KillAllChildren();

	//�R���C�_�[�i�Փ˔���j��ǉ�����
	void AddCollider(Collider * collider);

	//�����ƏՓ˂����ꍇ�ɌĂ΂��i�I�[�o�[���C�h�p�j
	//�����FpTarget	�Փ˂�������
	virtual void OnCollision(GameObject* pTarget) {};

	//�Փ˔���
	//�����FpTarget	�Փ˂��Ă邩���ׂ鑊��
	void Collision(GameObject* pTarget);

	//�e�X�g�p�̏Փ˔���g��\��
	void CollisionDraw();

	//RootJob���擾
	GameObject* GetRootJob();

	//�e�A�N�Z�X�֐�
	XMFLOAT3 GetPosition() { return transform_.position_; }
	XMFLOAT3 GetRotate() { return transform_.rotate_; }
	XMFLOAT3 GetScale() { return transform_.scale_; }
	XMFLOAT3 GetWorldPosition() { return Math::Float3Add(GetParent()->transform_.position_ , transform_.position_); }
	XMFLOAT3 GetWorldRotate() { return Math::Float3Add(GetParent()->transform_.rotate_, transform_.rotate_); }
	XMFLOAT3 GetWorldScale() { return Math::Float3Add(GetParent()->transform_.scale_, transform_.scale_); }
	std::string GetTag() { return tag_; }
	XMVECTOR GetMoved() {return vMoved ;}
	Transform GetTransform() { return transform_; }
	std::string GetName() { return objectName_; }
	std::string GetUniqueName() { return uniqueName_; }
	std::string GetPathName() { return pathName_; }


	void SetPosition(XMFLOAT3 position) { transform_.position_ = position; }
	void SetPosition(float x, float y, float z) { SetPosition(XMFLOAT3( x, y, z )); }
	void SetRotate(XMFLOAT3 rotate) { transform_.rotate_ = rotate; }
	void SetRotate(float x, float y, float z) { SetRotate(XMFLOAT3( x, y, z )); }
	void SetRotateX(float x) { SetRotate(x, transform_.rotate_.y, transform_.rotate_.z); }
	void SetRotateY(float y) { SetRotate(transform_.rotate_.x, y, transform_.rotate_.z); }
	void SetRotateZ(float z) { SetRotate(transform_.rotate_.x, transform_.rotate_.y, z); }
	void SetScale(XMFLOAT3 scale) { transform_.scale_ = scale; }
	void SetScale(float x, float y, float z) { SetScale(XMFLOAT3(x, y, z)); }
	void SetTag(std::string tag) { tag_ = tag; }
	void SetMoved(XMVECTOR moved) { vMoved = moved; }
	void SetPathName(std::string pathName) { pathName_ = pathName; }
	void SetUniqueName(std::string uniqueName) { uniqueName_ = uniqueName; }
	void SetAlpha(int alpha) { alpha_ = alpha; }


private:

	//�I�u�W�F�N�g�폜�i�ċA�j
	//�����Fobj�@�폜����I�u�W�F�N�g
	void KillObjectSub(GameObject* obj);

private:
	//�t���O
	struct OBJECT_STATE
	{
		unsigned initialized : 1;	//�������ς݂�
		unsigned entered : 1;		//�X�V���邩
		unsigned visible : 1;		//�`�悷�邩
		unsigned dead : 1;			//�폜���邩
		unsigned setUp : 1;			//�Z�b�g�A�b�v���Ă��邩
		unsigned hasShadow : 1;		//�e�����邩�ǂ���
	};
	OBJECT_STATE state_;

	//�e�I�u�W�F�N�g
	GameObject* pParent_;

	//�q�I�u�W�F�N�g���X�g
	std::list<GameObject*> childList_;
};


//�I�u�W�F�N�g���쐬����e���v���[�g
template <class T>
T* Instantiate(GameObject* pParent)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

//���f��(��摜)�̖��O�ƈʒu�������ɃI�u�W�F�N�g���쐬����e���v���[�g
template <class T>
T* Instantiate(GameObject* pParent, std::string fileName, XMFLOAT3 pos)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetPathName(fileName);
	pNewObject->Initialize();
	pNewObject->SetPosition(pos);
	return pNewObject;
}

//���f��(��摜)�̖��O�ƈʒu�A�����A�g�嗦�������ɃI�u�W�F�N�g���쐬����e���v���[�g
template <class T>
T* Instantiate(GameObject* pParent, std::string fileName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetPathName(fileName);
	pNewObject->Initialize();
	pNewObject->SetPosition(pos);
	pNewObject->SetRotate(rot);
	pNewObject->SetScale(sca);
	return pNewObject;
}

//���f��(��摜)�̖��O�ƈʒu�A�����A�g�嗦�������Ƀ{�^�����쐬����e���v���[�g
template <class T>
T* InstantiateButton(GameObject* pParent, std::string fileName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca)
{
	T* pNewObject = new T(pParent, fileName);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	pNewObject->SetPosition(pos);
	pNewObject->SetRotate(rot);
	pNewObject->SetScale(sca);
	return pNewObject;
}

//���f��(��摜)�̖��O�ƈʒu�A�����A�g�嗦�������Ƀ{�^�����쐬����e���v���[�g
template <class T>
T* InstantiateButton(GameObject* pParent, std::string fileName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::string uniqueName)
{
	T* pNewObject = new T(pParent, fileName);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	pNewObject->SetPosition(pos);
	pNewObject->SetRotate(rot);
	pNewObject->SetScale(sca);
	pNewObject->SetUniqueName(uniqueName);
	return pNewObject;
}

//���f��(��摜)�̖��O�ƈʒu�A�����A�g�嗦�������ɃI�u�W�F�N�g���쐬����e���v���[�g
template <class T>
T* InstantiateImage(GameObject* pParent, std::string fileName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, int alpha = 255)
{
	T* pNewObject = new T(pParent, fileName, alpha);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	pNewObject->SetPosition(pos);
	pNewObject->SetRotate(rot);
	pNewObject->SetScale(sca);
	return pNewObject;
}

//�L�����N�^�[���쐬����e���v���[�g
template <class T>
T* CharacterInstantiate(GameObject* pParent, std::string fileName)
{
	T* pNewObject = new T(pParent, fileName);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

//�X�e�[�W���쐬����e���v���[�g
template <class T>
T* StageInstantiate(GameObject* pParent, std::string fileName)
{
	T* pNewObject = new T(pParent, fileName);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

