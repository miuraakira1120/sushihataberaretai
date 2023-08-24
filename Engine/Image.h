#pragma once

#pragma once

#include <vector>
#include <string>
#include "Sprite.h"
#include "Transform.h"
#include "Direct3D.h"

//UI�̎��
enum UI_Type
{
	NONE = 0,
	PAUSE,
	TYPE_MAX
};

//-----------------------------------------------------------
//2D�摜���Ǘ�����
//-----------------------------------------------------------
namespace Image
{
	//�{�^���t�@�C���̃f�B���N�g����
	const std::string DIRECTORY_BUTTON = ".\\Button/"; 

	//�|�[�Y�t�@�C���̃f�B���N�g����
	const std::string DIRECTORY_UI = ".\\Image/";

	//�摜���
	struct ImageData
	{
		//�t�@�C����
		std::string fileName;

		//���[�h�����摜�f�[�^�̃A�h���X
		Sprite*		pSprite;

		//�؂蔲���͈�
		RECT		rect;

		//�A���t�@
		float		alpha;

		//�s��
		Transform transform;

		//�R���X�g���N�^
		ImageData() : pSprite(nullptr)
		{
			fileName = "";
			alpha = 1.0f;
			pSprite = nullptr;
		}
	};


	//������
	void Initialize();

	//�摜�����[�h
	//���łɓ������O�̃t�@�C�������[�h�ς݂̏ꍇ�́A�����̃f�[�^�̔ԍ���Ԃ�
	//�����FfileName�@�t�@�C����
	//�ߒl�F���̉摜�f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�
	int Load(std::string fileName);

	//�`��
	//�����Fhandle	�`�悵�����摜�̔ԍ�
	//�����Fmatrix	���[���h�s��
	//�����Fmatrix	���[���h�s��
	void Draw(int handle, Direct3D::SHADER_TYPE type = Direct3D::SHADER_2D);

	//�C�ӂ̉摜���J��
	//�����Fhandle	�J�����������f���̔ԍ�
	void Release(int handle);

	//�S�Ẳ摜�����
	//�i�V�[�����؂�ւ��Ƃ��͕K�����s�j
	void AllRelease();

	//�؂蔲���͈͂̐ݒ�
	//�����Fhandle	�ݒ肵�����摜�̔ԍ�
	//�����Fx		�؂蔲�������͈͂̍��[�w���W
	//�����Fy		�؂蔲�������͈͂̏�[�x���W
	//�����Fwidth	�؂蔲�������͈͂̕�
	//�����Fheight	�؂蔲�������͈͂̍���
	void SetRect(int handle, int x, int y, int width, int height);

	//�؂蔲���͈͂����Z�b�g�i�摜�S�̂�\������j
	//�����Fhandle	�ݒ肵�����摜�̔ԍ�
	void ResetRect(int handle);

	//�A���t�@�l���w��
	//�����Fhandle	�ݒ肵�����摜�̔ԍ�
	//�����Falpha �A���t�@�l�i�s�����x�j�@0�`255�Ŏw��
	void SetAlpha(int handle, int alpha);

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�����摜�̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetTransform(int handle, Transform& transform);

	//���[���h�s��̎擾
	//�����Fhandle	�m�肽���摜�̔ԍ�
	//�ߒl�F���[���h�s��
	XMMATRIX GetMatrix(int handle);

	/// <summary>
	/// �E�B���h�E�S�̂Ƀs�b�^���~���l�߂�s���ݒ�
	/// </summary>
	/// <param name="handle">�ݒ肵�����摜�̔ԍ�</param>
	void SetTransformFullSize(int handle);

	/// <summary>
	/// �摜�T�C�Y�̎擾
	/// </summary>
	/// <param name="handle">�ݒ肵�����摜�̔ԍ�</param>
	/// <returns>�摜�T�C�Y</returns>
	XMFLOAT3 GetTextureSize(int handle);

	/// <summary>
	/// �}�E�X���摜�ɓ������Ă��邩�ǂ����̔���
	/// </summary>
	/// <param name="imagePos"></param>
	/// <param name="imageSize"></param>
	/// <param name="mousePos"></param>
	/// <returns></returns>
	bool OnMouseOver(int handle);
}