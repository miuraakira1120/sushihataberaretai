#pragma once
#include "Engine/GameObject.h"
#include "Engine/Image.h"

class ModelBase;

//UI�Ȃǂ����Ƃ��Ɏg�p����V�[�����Ǘ�����N���X
class EditScene : public GameObject
{
	UI_Type modeUI;				//�ǂ�UI���������Ă��邩
	UI_Type prevModeUI;			//1f�O�܂łǂ�UI���������Ă�����

	float rotateY;
	ModelBase* pSoy;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	EditScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
