#pragma once
#include <string>
#include <DirectXMath.h>
#include <vector>
#include "ButtonManager.h"
#include "Button.h"

using namespace DirectX;

class GameObject;
using std::string;

//JSON��p���ăI�u�W�F�N�g���쐬����
namespace InstanceManager
{
	//���������ŕK�v�ȏ��̗v�f�������邩
	const int INFO_STR = 2;
	const int INFO_FLOAT = 9;

	//���������ŕK�v�ȏ��̗v�f�������邩(�摜)
	const int IMAGE_INFO_STR = 1;
	const int IMAGE_INFO_FLOAT = 10;

	const std::string SUCCESS = "success";//�����������ǂ����𔻒肷�鎞�Ɏg���萔


	//JSON�̏��ŃI�u�W�F�N�g���쐬���邽�߂̍\����
	struct CreateInfoJSON
	{
		std::string loadFile;			//�ǂݍ��މ摜
		std::string objectName;			//�ǂ�ȃI�u�W�F�N�g�𐶐����邩
		///////////////////////////////////////////////////////////////////
		XMFLOAT3 position;				//�ʒu
		XMFLOAT3 rotate;				//����
		XMFLOAT3 scale;					//�g�嗦
	};

	//JSON�̏��ŉ摜�쐬���邽�߂̍\����
	struct CreateImageInfoJSON
	{
		std::string loadFile;			//�ǂݍ��މ摜
		XMFLOAT3 position;				//�ʒu
		XMFLOAT3 rotate;				//����
		XMFLOAT3 scale;					//�g�嗦
		int alpha;
	};

	//////////////////////////////////�{�^��////////////////////////////////////////////////////////////////////
	/// <summary>
	/// JSON��p���ă{�^����ۑ�����i�Z�N�V���������j�[�N�ɂ���j
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="section">�Z�N�V������(�Q�Ɠn��)</param>
	/// <param name="pathName">�ǂݍ��ރt�@�C���̖��O</param>
	/// <param name="objectName">���{�^���̎��</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="rot">����</param>
	/// <param name="sca">�g�嗦</param>
	/// <returns>�����������ǂ���</returns>
	bool SaveButton(std::string filename, std::string& section, std::string pathName, std::string objectName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca);

	/// <summary>
	/// JSON��p���ăI�u�W�F�N�g���㏑���ۑ�����i�Z�N�V���������j�[�N�ɂ��Ȃ��j
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="pathName">�ǂݍ��ރt�@�C���̖��O</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="rot">����</param>
	/// <param name="sca">�g�嗦</param>
	/// <returns></returns>
	bool OverWriteSaveButton(std::string filename, std::string section, std::string pathName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca);

	/// <summary>
	/// CreateInfoJSON�̏�����Ƀ{�^�����쐬����֐�
	/// </summary>
	/// <param name="info">�l��ǂݎ��\����</param>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="section">�Z�N�V������</param>
	/// <returns>�쐬�����I�u�W�F�N�g�̃|�C���^</returns>
	Button* CreateButtonOnInfo(InstanceManager::CreateInfoJSON info, GameObject* parent, std::string filename, std::string section);

	/// <summary>
	/// JSON��p���ă{�^����������i�����o�[���ׂāj
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="pButtonList">���������{�^���̃|�C���^�̃��X�g</param>
	/// <returns>�����������ǂ���</returns>
	bool AllCreateButton(std::string filename, std::vector<GameObject*>& pButtonList, GameObject* parent);

	/// <summary>
	/// JSON��p���ă{�^����������i�����o�[���ׂāj
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="parent">���������{�^���̃|�C���^�̃��X�g</param>
	/// <returns>�����������ǂ���</returns>
	bool AllCreateButton(std::string filename, GameObject* parent);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////�摜////////////////////////////////////////////////////////////////////

	/// <summary>
	/// JSON��p���ĉ摜��ۑ�����i�Z�N�V���������j�[�N�ɂ���j
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="pathName">�t�@�C����</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="rot">����</param>
	/// <param name="sca">�g�嗦</param>
	/// <returns>�����������ǂ���</returns>
	bool SaveImage(std::string filename, std::string& section, std::string pathName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, int alpha);

	/// <summary>
	/// JSON��p���ĉ摜���㏑���ۑ�����i�Z�N�V���������j�[�N�ɂ��Ȃ��j
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="pathName">�ǂݍ��ރt�@�C���̖��O</param>
	/// <param name="pos">�ʒu</param>
	/// <param name="rot">����</param>
	/// <param name="sca">�g�嗦</param>
	/// <param name="sca">�A���t�@�l</param>
	/// <returns></returns>
	bool OverWriteSaveImage(std::string filename, std::string section, std::string pathName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, int alpha);
	
	/// <summary>
	/// CreateInfoJSON�̏�����Ƀ{�^�����쐬����֐�
	/// </summary>
	/// <param name="info">�l������\����</param>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="section">�Z�N�V������</param>
	/// <returns>�쐬�����I�u�W�F�N�g�̃|�C���^</returns>
	GameObject* CreateImageOnInfo(InstanceManager::CreateImageInfoJSON info, GameObject* parent, std::string filename, std::string section);

	/// <summary>
	/// JSON��p���ĉ摜�𐶐�����i�����o�[���ׂāj
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="pImageList">�摜�̃��X�g</param>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	/// <returns>�����������ǂ���</returns>
	bool AllCreateImage(std::string filename, std::vector<GameObject*>& pImageList, GameObject* parent);

	/// <summary>
	/// JSON��p���ĉ摜�𐶐�����i�����o�[���ׂāj
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="parent">�e�I�u�W�F�N�g</param>
	/// <returns>�����������ǂ���</returns>
	bool AllCreateImage(std::string filename, GameObject* parent);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

