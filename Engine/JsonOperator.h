#pragma once

#include <string>
#include<vector>
#include <map>
#include <iostream>
#include <fstream>
#include "SceneManager.h"
#include "../Json/rapidjson-master/include/rapidjson/document.h"
#include "../Json/rapidjson-master/include/rapidjson/filereadstream.h"
#include "../Json/rapidjson-master/include/rapidjson/filewritestream.h"
#include "../Json/rapidjson-master/include/rapidjson/writer.h"
#include "../InstanceManager.h"


using namespace rapidjson;
class GameObject;


//JSON�̋L�q��
//https://products.sint.co.jp/topsic/blog/json#toc-2

namespace JsonOperator
{

	//////////////////////////////////////////////////////////////////////////////////////////////
	// �V�[���Ɋ֌W����萔
	// �g�p����JSON�t�@�C���̖��O
	//�e�X�g
	const std::string TEST_JSON = "../Assets\\GameData\\Test.json";
	
	//�^�C�g��
	const std::string TITLE_JSON = "../Assets\\GameData\\TitleScene.json";	
	const std::string TITLE_BUTTON_JSON = "../Assets\\GameData\\TitleButton.json";
	const std::string TITLE_IMAGE_JSON = "../Assets\\GameData\\TitleImage.json";

	//////////////////////////////////////////////////////////////////////////////////////////////
	// �|�[�Y�Ɋ֌W����萔
	// �g�p����JSON�t�@�C���̖��O
	const std::string PAUSE_IMAGE_JSON = "../Assets\\GameData\\PauseImage.json";
	const std::string PAUSE_BUTTON_JSON = "../Assets\\GameData\\PauseButton.json";
	//////////////////////////////////////////////////////////////////////////////////////////////
	//�e�ɂȂ�\���̂���I�u�W�F�N�g�𕶎���ɂ������̒萔
	const std::vector<std::string> parentStrList =
	{
		"playScene",
		"startScene",    
		"goalScene",
		"gameOverScene"
		"pause"
	};

	enum CanParentObj
	{
		SCENE_PLAY = 0,
		SCENE_START,
		SCENE_GOAL,
		SCENE_GAMEOVER,
		PAUSE,
		MAX
	};

	//���������\���̂���{�^���𕶎���ɂ������̒萔
	const std::vector<std::string> buttonStrList =
	{
		"sceneChangeButton",
		"playerControlButton",
		"slider"
	};

	//���������\���̂���I�u�W�F�N�g�𕶎���ɂ������̒萔

	/////////////////////////////////////////////////////////////////////////////////////////////////


	////�e�V�[���Ǝg�p����JSON�t�@�C���̖��O��R�t����
	//std::map<SCENE_ID, std::string> sceneFilename
	//{
	//	{SCENE_ID::SCENE_ID_START, TEST_JSON},
	//};

	///////////Instance�̂��߂̒萔/////////////////////////////////////////////////
	
	// �����������key(InstantiateInfoJSON�̗v�f�ɑΉ�������) 
	const std::vector<std::string> InstantiateKeyString =
	{
     	"loadFile",		//�ǂݍ��މ摜
		"objectName"	//�ǂ�ȃI�u�W�F�N�g�𐶐����邩
	};	

	// �����������key(InstantiateInfoJSON�̗v�f�ɑΉ�������) 
	const std::vector<std::string> InstantiateKeyFloat =
	{
		"positionX",	//�ʒu
		"positionY",	//�ʒu
		"positionZ",	//�ʒu
		"rotateX",		//����
		"rotateY",		//����
		"rotateZ",		//����
		"scaleX",		//�g�嗦
		"scaleY",		//�g�嗦
		"scaleZ",		//�g�嗦
		"alpha"			//�A���t�@�l
	};
	

	/////////////////////////////////////////////////////////////////////////


	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// JSON�t�@�C����ǂݍ��ފ֐�
	/// </summary>
	/// <param name="filename">�ǂݍ��ރt�@�C���̖��O</param>
	/// <param name="document">�ǂݍ��ރh�L�������g</param>
	/// <returns>�����������ǂ���</returns>
	bool LoadJSONFromFile(std::string filename, Document& document);

	/// <summary>
	/// �t�@�C���̓��e�𕶎���Ƃ��ēǂݍ���
	/// </summary>
	/// <param name="filename">�ǂݍ��ރt�@�C���̖��O</param>
	/// <param name="str">�ǂݍ��񂾕�����</param>
	/// <returns>�����������ǂ���</returns>
	bool LoadJSONString(std::string filename, std::string& str);

	/// <summary>
	/// JSON�t�@�C�����쐬����֐�
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// /// <returns>�����������ǂ���</returns>
	bool CreateJSONFile(std::string filename);

	/// <summary>
	/// �Z�b�V������ǉ�����֐�
	/// </summary>
	/// <param name="filename">�ǂݍ��ރt�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <returns>�����������ǂ���</returns>
	bool AddSection(const std::string& filename, const std::string& section);
	
	/// <summary>
	/// JSON�t�@�C���̕������ǂݎ��
	/// </summary>
	/// <param name="fileName">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾕�����</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONString(std::string filename, std::string key, std::string &out);

	/// <summary>
	/// JSON�t�@�C���̐����l��ǂݎ��
	/// </summary>
	/// <param name="fileName">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾐����l</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONInt(std::string filename, std::string key, int &out);

	/// <summary>
	/// JSON�t�@�C���̏����l��ǂݎ��
	/// </summary>
	/// <param name="fileName">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾏����l</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONFloat(std::string filename, std::string key, float& out);

	//////////////////////////////////////�Z�N�V��������i�I�[�o�[���[�h�j////////////////////////////////////////////

	/// <summary>
	/// JSON�t�@�C���̕������ǂݎ��
	/// </summary>
	/// <param name="fileName">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾕�����</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONString(std::string filename, std::string section, std::string key, std::string& out);

	/// <summary>
	/// JSON�t�@�C���̐����l��ǂݎ��
	/// </summary>
	/// <param name="fileName">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾐����l</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONInt(std::string filename, std::string section, std::string key, int& out);

	/// <summary>
	/// JSON�t�@�C���̏����l��ǂݎ��
	/// </summary>
	/// <param name="filename">�ǂݎ��t�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="out">�ǂݍ��񂾏����l</param>
	/// <returns>�����������ǂ���</returns>
	bool GetJSONFloat(std::string filename, std::string section, std::string key, float& out);

	////////////////////////////��������(�㏑���j///////////////////////////////////////////////////

	/// <summary>
	/// JSON�t�@�C���ɏ�������
	/// </summary>
	/// <param name="filename">>�������ރt�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="value">�����l</param>
	/// <returns>�����������ǂ���</returns>
	bool WriteJSONToFile(const std::string& filename, const std::string &section, const std::string &key, const std::string &value);

	/// <summary>
	/// JSON�t�@�C���ɏ�������
	/// </summary>
	/// <param name="filename">>�������ރt�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="value">�����l</param>
	/// <returns>�����������ǂ���</returns>
	bool WriteJSONToFile(const std::string& filename, const std::string &section, const std::string &key, const int &value);

	/// <summary>
	/// JSON�t�@�C���ɏ�������(�㏑���j
	/// </summary>
	/// <param name="filename">>�������ރt�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="value">�����l</param>
	/// <returns>�����������ǂ���</returns>
	bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const float& value);

	/// ///////////////////////��������(�ǋL)///////////////////////////////////////////////////////////////


	//bool PostscriptJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const float& value)

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////��������(�ǋL�A���������j///////////////////////////////////////////////////

	/// <summary>
	/// JSON�t�@�C���ɏ�������(�ǋL�A���������j
	/// </summary>
	/// <param name="filename">�������ރt�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="value">�������ޒl</param>
	/// <returns>�����������ǂ���</returns>
	bool AppendToJSONFileString(const std::string& filename, const std::string& section, const std::string& key, std::string value);

	/// <summary>
	/// JSON�t�@�C���ɏ�������(�ǋL�A���������j
	/// </summary>
	/// <param name="filename">�������ރt�@�C���̖��O</param>
	/// <param name="section">�Z�N�V������</param>
	/// <param name="key">�L�[�̖��O</param>
	/// <param name="value">�������ޒl</param>
	/// <returns>�����������ǂ���</returns>
	bool AppendToJSONFileFloat(const std::string& filename, const std::string& section, const std::string& key, float value);

	/// <summary>
	/// �Z�N�V�����̃L�[�ƃZ�N�V���������ׂč폜
	/// </summary>
	/// <param name="filename">�폜����t�@�C����</param>
	/// <param name="section">�Z�N�V������</param>
	/// <returns>�����������ǂ���</returns>
	bool DeleteJSONSection(const std::string& filename, const std::string& section);
	/////////////////////////////////////////////////////////////////////////////////////////

	///////////////////////////////Instance�̂��߂̊֐�//////////////////////////////////////////////////////////


	/// <summary>
	/// �I�u�W�F�N�g�𐶐����邽�߂̏���JSON���珑������(������������)
	/// </summary>
	/// <param name="filename">�Z�N�V����</param>
	/// <param name="key">�L�[</param>
	/// <param name="info">�l������\����</param>
	/// <returns>�����������ǂ���</returns>
	bool WhiteCreateInfo(const std::string& filename, const std::string& section, InstanceManager::CreateInfoJSON& info);

	/// <summary>
	/// �摜�𐶐����邽�߂̏���JSON���珑������(������������)
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="section">�Z�N�V����</param>
	/// <param name="info">�l������\����</param>
	/// <returns>�����������ǂ���</returns>
	bool WhiteCreateImageInfo(const std::string& filename, const std::string& section, InstanceManager::CreateImageInfoJSON& info);

	/// <summary>
	/// �I�u�W�F�N�g�𐶐����邽�߂̏���JSON����ǂݍ���
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="section">�Z�N�V����</param>
	/// <param name="key">�L�[</param>
	/// <param name="info">�l������\����</param>
	/// <returns>�����������ǂ���</returns>
	bool GetInstanceInfo(const std::string& filename, const std::string& section, InstanceManager::CreateInfoJSON& info);

	/// <summary>
	/// �摜�𐶐����邽�߂̏���JSON����ǂݍ���
	/// </summary>
	/// <param name="filename">�t�@�C����</param>
	/// <param name="section">�Z�N�V����</param>
	/// <param name="key">�L�[</param>
	/// <param name="info">�l������\����</param>
	/// <returns>�����������ǂ���</returns>
	bool GetCreateImageInfo(const std::string& filename, const std::string& section, InstanceManager::CreateImageInfoJSON& info);
	
	/// <summary>
	/// �d������������̌��ɐ���������v���O����
	/// </summary>
	/// <param name="filename">�������ރt�@�C���̖��O</param>
	/// <param name="str">���j�[�N�ɂ�����������</param>
	/// <returns>�����������ǂ���</returns>
	bool CreateUniqueNameJSON(std::string filename, std::string& str);

	/// <summary>
	/// �e�ɂȂ�\���̂���I�u�W�F�N�g�𕶎��ɕϊ�
	/// </summary>
	/// <param name="scene">������ɂ���e�I�u�W�F�N�g</param>
	/// <returns>�ϊ�����������</returns>
	std::string SceneToString(CanParentObj parent);

	/// <summary>
	/// �{�^���𕶎��ɕϊ�
	/// </summary>
	/// <param name="scene">������ɂ���{�^��</param>
	/// <returns>�ϊ�����������</returns>
	std::string ButtonToString(ButtonManager::ButtonKinds button);
	
	/// <summary>
	/// �������V�[���ɕϊ�
	/// </summary>
	/// <param name="scene">�V�[���ɂ��镶����</param>
	/// <returns>�ϊ������e�I�u�W�F�N�g</returns>
	CanParentObj StringToParent(std::string parent);
	
	/// <summary>
	/// �������{�^���ɕϊ�
	/// </summary>
	/// <param name="button">�{�^���ɂ��镶����</param>
	/// <returns></returns>
	ButtonManager::ButtonKinds StringToButton(std::string  button);

};

