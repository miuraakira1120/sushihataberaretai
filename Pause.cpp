#include "Pause.h"
#include "Engine/Image.h"
#include "GameManager.h"
#include "BackUI.h"
#include "Engine/SceneManager.h"
#include "Engine/JsonOperator.h"
#include "InstanceManager.h"


//�R���X�g���N�^
Pause::Pause()
{
}

//�f�X�g���N�^
Pause::~Pause()
{
}

//������
void Pause::Initialize()
{
}

//�X�V
void Pause::Update()
{
	//�����|�[�Y���Ă��Ȃ�������
	if (GameManager::GetIsPause())
	{
		return;
	}

	//UI���X�g�̒��g�̍X�V��S���Ă�
	AllPauseUIUpdate();
}

//�`��
void Pause::Draw()
{
	//�����|�[�Y���Ă��Ȃ�������
	if (GameManager::GetIsPause())
	{
		return;
	}

	//�쐬����UI�̕`����Ă�
	AllPauseUIDraw();
}

//�J��
void Pause::Release()
{
}

//UI�̍쐬
void Pause::CreateUI()
{
	std::vector<GameObject*> tmp;
	InstanceManager::AllCreateImage(JsonOperator::PAUSE_IMAGE_JSON, tmp, GameManager::GetpSceneManagerPointor()->GetNowScenePointer());

	for (auto i = 0; i < tmp.size(); i++)
	{
		//UIList�ɓ����
		AddUIList(tmp[i]);
	}
}

//UI�̍폜
void Pause::DeleteUI()
{
	//UIList�̒��g�����ׂď���
	for (auto i = UIList.begin(); i != UIList.end();)
	{
		(*i)->KillMe();
		i = UIList.erase(i);

	}

	//UIList�����ׂč폜
	UIList.clear();
}

//UI���X�g�̒��g�̍X�V��S���Ă�
void Pause::AllPauseUIUpdate()
{
	for (auto i = UIList.begin(); i != UIList.end(); i++)
	{
		if ((*i) != nullptr)
			(*i)->Update();
	}
}

//UI���X�g�̒��g�̕`���S���Ă�
void Pause::AllPauseUIDraw()
{
	//UIList�̌��̕����O�ɕ`��
	for (auto i = UIList.begin(); i != UIList.end(); i++)
	{
		if ((*i) != nullptr)
			(*i)->Draw();
	}
}

//UIList�ɓ����
void Pause::AddUIList(GameObject* ui)
{
	UIList.push_back(ui);
}

