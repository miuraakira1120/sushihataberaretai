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
			/*EmitterData starEfect = VFX::SetEmitterDataStar();
			starEfect.position = GetPosition();
			VFX::Start(starEfect);*/

			EmitterData data;
			

			data.position = GetPosition();
			VFX::Start(data);
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
