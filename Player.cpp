#include "Player.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "ImageBase.h"
#include "GameManager.h"
#include "Engine/BoxCollider.h"
#include "VFX.h"


Player::Player(GameObject* parent, std::string pathName)
	:PlayerBase(parent, "Player", pathName)
{
}

//������
void Player::Initialize()
{
	//�R���C�_�[������(PLAYER_SIZE�͔��a�̂���2�{��)
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), Math::Float3Mul( PLAYER_SIZE, TWICE));
	AddCollider(collision);
}

//�X�V
void Player::Update()
{
	//�l�^����ȉ��ɕۂ���
	NetaSingleton();

	//�{�^���̏���
	//�����v���C���[�����͂��󂯕t���Ă�����
	if(GetCanMove())
	{
		//�ړ�
		//���N���b�N�ňړ�
		if (Input::IsMouseButton(0))
		{
			Move();
		}

		//�ړ�
		//�E�N���b�N�Ńo�b�N�ړ�
		if (Input::IsMouseButton(1))
		{
			Move(true);
		}

		//�W�����v
		//�X�y�[�X�ŃW�����v
		if (Input::IsKeyDown(DIK_SPACE))
		{
			Jump(); 
		}

		if (Input::IsKeyDown(DIK_G))
		{
			EmitterData ed;
			ed.textureFileName = "PaticleAssets/star.png";
			ed.delay = 0;
			ed.number = 6;
			ed.lifeTime = 20;
			ed.direction = XMFLOAT3(0, 1, 0);
			ed.directionRnd = XMFLOAT3(90, 90, 0);
			ed.speed = 00.1f;
			ed.speedRnd = 0.8;
			ed.sizeRnd = XMFLOAT2(0.4, 0.4);
			ed.scale = XMFLOAT2(1.05, 1.05);
			ed.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);

			ed.color = XMFLOAT4(1, 1, 0.1, 1);
			ed.size = XMFLOAT2(0.65, 0.65);
			ed.position = XMFLOAT3(0, 0, 0);
			ed.rotateRnd = XMFLOAT3(0, 0, 0);
			

			VFX::Start(ed);
		}
	}

	//�d�͂̏���
	Gravity();

	//�X�e�[�W�֘A�̏���
	{
		//�X�e�[�W�̃��f�����擾
		StageBase* pStage = GameManager::GetNowStage();    //�X�e�[�W�I�u�W�F�N�g��T��
		int hGroundModel = pStage->GetModelHandle();    //���f���ԍ����擾

		//�p����n�ʂ̖@���ɓY�킹��
		PostureGroundFollow(hGroundModel);

		//�n�ʂɂ߂荞�񂾎��̏���
		RevertProcess(hGroundModel);
	}
	
	//���̃I�u�W�F�N�g�ɃJ�������Z�b�g����
	SetCameraController();
}

//�l�^����ȉ��ɕۂ���
void Player::NetaSingleton()
{
	GameObject* pTmp = nullptr;
	//����Neta�N���X���p�������q�I�u�W�F�N�g��2�ȏ�ɂȂ�����
	for (auto it = this->GetChildList()->begin(); it != this->GetChildList()->end(); ++it)
	{
		//�^�O���l�^�Ȃ�
		if ((*it)->GetTag() == "neta")
		{
			if (pTmp == nullptr)
			{
				pTmp = (*it);
			}
			else
			{
				pTmp->KillMe();
			}
		}
	}
}
