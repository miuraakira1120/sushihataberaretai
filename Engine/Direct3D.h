#pragma once

//�C���N���[�h
#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;


//-----------------------------------------------------------
//��ʂ̕`��Ɋւ��鏈��
//-----------------------------------------------------------
namespace Direct3D
{
	////////////////////////�O��������A�N�Z�X����ϐ��Q///////////////////////////////
	//�y�f�o�C�X�z
	//�`����s�����߂̊��⃊�\�[�X�̍쐬�Ɏg��
	extern ID3D11Device*           pDevice_;

	//�y�R���e�L�X�g�z
	//GPU�ɖ��߂��o�����߂̂��
	extern ID3D11DeviceContext*    pContext_;

	//�r���[�|�[�g
	extern D3D11_VIEWPORT vp_left;

	//�y�R���e�L�X�g�z
	//GPU�ɖ��߂��o�����߂̂��
	extern XMMATRIX lightView_;
	extern XMMATRIX clipToUV_;
	extern ID3D11ShaderResourceView* pDepthSRV_;

	


	//���V�F�[�_�[�֘A�ŕK�v�ȃZ�b�g
	enum SHADER_TYPE
	{
		SHADER_UNLIT = 0,
		SHADER_3D, 
		SHADER_2D, 
		SHADER_FLASH_2D,
		SHADER_BILLBOARD,
		SHADER_UVSCROLL,
		SHADER_SHADOW,
		SHADER_MAX
	};	//4�^�C�v�i3D�p�A2D�p�A�����蔻��g�\���p, �r���{�[�h�p�j

	enum ViewPos
	{
		MAIN_CAM,
		SUB_CAM,
	};
	struct SHADER_BUNDLE
	{
		//�y���_���̓��C�A�E�g���z
		//1�̒��_�f�[�^���ǂ�ȏ����ǂ�ȏ��ԂŊi�[���Ă邩�i�ʒu�ƐF�Ɩ@���Ɓc�Ƃ��j
		ID3D11InputLayout *pVertexLayout;

		//�y���_�V�F�[�_�z
		//�V�F�[�_�[�i�Z�Z.hlsl�j�̒��̒��_�V�F�[�_�[�iVS�j�������R���p�C���������̂�����
		//�V�F�[�_�[�̓n�[�h�ɂ���ē��삪�قȂ�̂ŁA���s���ɃR���p�C������B
		ID3D11VertexShader *pVertexShader;

		//�y�s�N�Z���V�F�[�_�z
		//�V�F�[�_�[�i�Z�Z.hlsl�j�̒��̃s�N�Z���V�F�[�_�[�iPS�j�������R���p�C���������̂�����
		ID3D11PixelShader *pPixelShader;

		//�y���X�^���C�U�z
		//���_�̕\���ʒu�m���A��ʂ̂ǂ̃s�N�Z�������点��΂��������߂����
		ID3D11RasterizerState*	pRasterizerState;
	};
	
	extern SHADER_BUNDLE shaderBundle[SHADER_MAX];

	//���u�����h���[�h
	enum BLEND_MODE
	{
		BLEND_DEFAULT, BLEND_ADD, BLEND_MAX
	};

	//���̑�
	extern int		screenWidth_;		//�X�N���[���̕�
	extern int		screenHeight_;		//�X�N���[���̍���
	extern bool		isDrawCollision_;	//�R���W������\�����邩�t���O

	extern int		lrMode;
	extern SHADER_TYPE nowShaderType;




	////////////////////////��������͊֐�///////////////////////////////

	//����������
	//�����FhWnd			�E�B���h�E�n���h��
	//�����FscreenWidth		�X�N���[���̕�
	//�����FscreenHeight	�X�N���[���̍���
	HRESULT Initialize(HWND hWnd, int screenWidth, int screenHeight);

	//�V�F�[�_�[�֘A�ŕK�v�ȃZ�b�g����
	void InitShaderBundle();

	//DEBUG�̓����蔻��Shader�̏�����
	void InitShaderUnlit();

	//Shader2D�̏�����
	void InitShader2D();

	//Shader3D�̏�����
	void InitShader3D();

	//���_�V�F�[�_�[�̍쐬
	ID3DBlob* CreateVertexSheder(int num);

	//�s�N�Z���V�F�[�_�[�̍쐬
	void CreatePixelSheder(int num);

	//���X�^���C�U�쐬
	void CreateRasterizer(int num);

	//������`�悷��ShaderBundle��ݒ�
	//�����Ftype	�V�F�[�_�[�͉����g����
	void SetShader(SHADER_TYPE type);

	//�e�N�X�`���֐[�x����`��
	void BeginDrawToTexture();

	//�u�����h���[�h�̕ύX
	//�����FblendMode	BLEND_DEFAULT	�ʏ�
	//					BLEND_ADD		���Z�����i�p�[�e�B�N���p�j
	void SetBlendMode(BLEND_MODE blendMode);

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//�J������
	void Release();


	//�O�p�`�Ɛ����i���C�j�̏Փ˔���i�Փ˔���Ɏg�p�j
	//�����Fstart�@		���C�̃X�^�[�g�ʒu
	//�����Fdirection	���C�̕���
	//�����Fv0,v1,v2	�O�p�`�̊e���_�ʒu
	//�����Fdistance	�Փ˓_�܂ł̋�����Ԃ�
	//�ߒl�F�Փ˂������ǂ���
	bool Intersect(XMFLOAT3& start, XMFLOAT3& direction, XMFLOAT3 &v0, XMFLOAT3& v1, XMFLOAT3& v2, float* distance, XMFLOAT3* pos);

	//Z�o�b�t�@�ւ̏�������ON/OFF
	//�����FisWrite	  true=��������ON�^false=��������OFF
	void SetDepthBafferWriteEnable(bool isWrite);

	void SetViewPort(int lr);
};
