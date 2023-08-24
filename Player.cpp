#include "Player.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "ImageBase.h"
#include "GameManager.h"


Player::Player(GameObject* parent, std::string pathName)
	:PlayerBase(parent, "Player", pathName)
{

}

//�X�V
void Player::Update()
{
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
