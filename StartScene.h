#pragma once
#include "Engine/GameObject.h"
#include <vector>



//�X�^�[�g�V�[�����Ǘ�����N���X
class StartScene : public GameObject
{
	int hSound_;    //�T�E���h�ԍ�
	int hPict_;    //�摜�ԍ�
	int iniListButton;//�^�C�g���V�[���̃{�^���̔ԍ�

	GameObject* pStartButton;

	std::vector<GameObject*> instanceList;
	
public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	StartScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};
