#pragma once
#include <string>

//-----------------------------------------------------------
//�T�E���h���Ǘ�����iXAudio�g�p�j
//-----------------------------------------------------------
namespace Audio
{
	//�T�E���h�̎��
	enum class Sound_Type
	{
		BGM,
		SE,
		VOICE,
		MASTER,
		SOUND_MAX
	};

	//������
	void Initialize();

	/// <summary>
	/// �T�E���h�t�@�C��(.wav�j�����[�h
	/// </summary>
	/// <param name="fileName">�t�@�C����</param>
	/// <param name="loopFlg">�Đ��`��(true�Ŗ������[�v�Afalse�łP�x�̂ݍĐ�)</param>
	/// <param name="svNum">�����ɖ炷�ő吔�i�ȗ��j</param>
	/// <param name="volume">����</param>
	/// <returns>���łɓ������O�̃t�@�C�������[�h�ς݂̏ꍇ�́A�����̃f�[�^�̔ԍ���Ԃ�</returns>
	int Load(std::string fileName, bool loopFlg, float volume, int svNum = 1);

	//�Đ�
	//�����Fhandle	�炵�����T�E���h�̔ԍ�
	void Play(int ID);

	/// <summary>
	/// ����Ă鉹�y�̒�~���s���֐�
	/// </summary>
	/// <param name="ID">�~�߂����T�E���h�̔ԍ�</param>
	void Stop(int ID);

	/// <summary>
	/// �Đ��I���������ǂ����𒲂ׂ�֐�
	/// </summary>
	/// <param name="ID">�m�F�������T�E���h�̔ԍ�</param>
	/// <returns>�I�����Ă�����true</returns>
	bool IsEndPlayBack(int ID);

	/// <summary>
	/// �}�X�^�[�{�����[����ύX����
	/// </summary>
	/// <param name="vol">�ύX��̃}�X�^�[�{�����[��(0����100)</param>
	/// 

	/// <summary>
	/// �}�X�^�[�{�����[����ύX����
	/// </summary>
	/// <param name="vol">�ύX��̃{�����[��(0����100)</param>
	/// <param name="type">�ύX���郔�H�����[���^�C�v�^�C�v</param>
	void SetVolume(float vol, Sound_Type type);

	//���ׂĊJ��
	void Release();
	void AllRelease();
};
