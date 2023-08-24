#pragma once
#include "global.h"
#include "GameObject.h"

//�Q�[���ɓo�ꂷ��V�[��
enum SCENE_ID
{
	SCENE_ID_PLAY = 0,
	SCENE_ID_START,
	SCENE_ID_GOAL,
	SCENE_ID_GAMEOVER,
	SCENE_ID_EDIT,
	SCENE_ID_TUTORIAL,
	SCENE_ID_MAX
};

//-----------------------------------------------------------
//�V�[���؂�ւ���S������I�u�W�F�N�g
//-----------------------------------------------------------
class SceneManager : public GameObject
{
public:

	//�R���X�g���N�^
	//�����Fparent	�e�I�u�W�F�N�g�i��{�I�ɃQ�[���}�l�[�W���[�j
	SceneManager(GameObject* parent);

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
	//�����Fnext	���̃V�[����ID
	void ChangeScene(SCENE_ID next);

	//���̃V�[����ID��Ԃ��Q�b�^�[
	SCENE_ID GetNowSceneID();

	//���̃V�[���̃|�C���^��Ԃ��Q�b�^�[
	GameObject* GetNowScenePointer();

private:
	SCENE_ID currentSceneID_;	//���݂̃V�[��
	SCENE_ID nextSceneID_;		//���̃V�[��

	//�V�[���̃|�C���^�̔z��
	GameObject* pNowScene[SCENE_ID_MAX];

};