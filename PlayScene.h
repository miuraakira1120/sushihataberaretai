#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "Engine/GameObject.h"

class PlayScene : public GameObject
{

	//const XMFLOAT3 UVSCROLL_SPEED = { 0.1f, 0.1f, 0.0f };
	const float UVSCROLL_SPEED = 0.1f;

	struct ConstantBuffer
	{
		XMMATRIX	dummy_;		// ��
		float		pos;		// uv�̈ړ�����ʒu
	};

	float pos;
	Microsoft::WRL::ComPtr<ID3D11Buffer>pConstantBuffer_;	//�R���X�^���g�o�b�t�@

	int hPict_;					//�摜�ԍ�

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	PlayScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;
};