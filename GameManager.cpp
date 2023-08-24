#include "GameManager.h"
#include "Pause.h"
#include "Engine/Input.h"

namespace
{
	//pause�̃|�C���^
	Pause* pPause;

	//���Ԃ���~���Ă��邩
	bool isTimeMoving;

	//�|�[�Y���Ă��邩
	bool isPause;

	//SceneManager�̃|�C���^
	SceneManager* pSceneManager;

	//���C�g�̌���
	XMFLOAT4 lightVec;

	//���̃X�e�[�W
	StageBase* pNowStage;
}

namespace GameManager
{
	//������
	void Initialize()
	{
		//�e�ϐ��̏�����
		isTimeMoving = true;

		//�|�[�Y����
		pPause = new Pause;
		pPause->Initialize();

		isPause = false;

		//���C�g�̌������w��
		lightVec = LIGHT_VEC;

		//���̃X�e�[�W�̏�����
		pNowStage = nullptr;
	}

	//�X�V
	void Update()
	{
		//�|�[�Y�L�[����������
		if (Input::IsKeyDown(DIK_1))
		{
			//�|�[�Y��Ԃ��t�ɂ���֐�
			PauseReverse();

			//�|�[�Y���Ă���
			if (isPause)
			{
				//UI�̍쐬
				pPause->CreateUI();			
			}
			else
			{
				//UI�̍폜
				pPause->DeleteUI();
			}
		}
		//�|�[�Y�̍X�V
		pPause->Update();
	}

	//�`��
	void Draw()
	{
		//�|�[�Y���Ă�����
		if (isPause)
		{
			//�|�[�Y��ʂ�`��
			pPause->Draw();
		}	
	}

	//���
	void Release()
	{
		//�������
		if ((pPause) != nullptr)
		{
			delete (pPause);
			(pPause) = nullptr;
		}
	}

	//���Ԃ������Ă��邩
	bool GetIsTimeMoving()
	{
		return isTimeMoving;
	}

	//���Ԃ𓮂������ǂ���
	void SetTimeMoving(bool flag)
	{
		isTimeMoving = flag;
	}

	//���Ԃ������Ă������~���A�~�܂��Ă����瓮����
	void TimeMovingReverse()
	{
		isTimeMoving = !isTimeMoving;
	}

	//isPause�̃Q�b�^�[
	bool GetIsPause()
	{
		return isPause;
	}
	void SetScenemanagerPointor(SceneManager* pScene)
	{
		pSceneManager = pScene;
	}
	SceneManager* GetpSceneManagerPointor()
	{
		return pSceneManager;
	}

	//�|�[�Y��Ԃ��t�ɂ���֐�
	void PauseReverse()
	{
		//isPause���t�ɂ���
		isPause = !isPause;

		//�Q�[�������Ԃ������Ă������~���A�~�܂��Ă����瓮����
		TimeMovingReverse();
	}

	// �|�[�Y��Ԃ�ݒ肷��֐�
	void SetPause(bool pause)
	{
		isPause = pause;
	}

	//���C�g�̌������Z�b�g����֐�
	void SetLightVec(XMFLOAT3 light)
	{
		lightVec =  XMFLOAT4(light.x, light.y, light.z, 0);
	}

	//���C�g�̌������擾����֐�
	XMFLOAT3 GetLightVec()
	{
		return XMFLOAT3(lightVec.x, lightVec.y, lightVec.z);
	}

	//pNowStage�̃Q�b�^�[
	StageBase* GetNowStage()
	{
		return pNowStage;
	}

	//pNowStage�̃Z�b�^�[
	void SetNowStage(StageBase* pStage)
	{
		pNowStage = pStage;
	}
}