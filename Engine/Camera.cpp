#include "camera.h"
#include "Direct3D.h"

XMFLOAT3 _position;
XMFLOAT3 _target;
XMMATRIX _view;
XMMATRIX _proj;
XMMATRIX _proj2;
int viewFlag;
XMMATRIX _billBoard;
float fov_;

//�������i�v���W�F�N�V�����s��쐬�j
void Camera::Initialize()
{
	_position = XMFLOAT3(0, 3, -10);	//�J�����̈ʒu
	_target = XMFLOAT3( 0, 0, 0);	//�J�����̏œ_

	viewFlag = 0;

	fov_ = XM_PIDIV4;	//����p(2����1��{90�x})

	//�v���W�F�N�V�����s��
	//_proj = XMMatrixPerspectiveFovLH(fov_, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
	_proj2 = XMMatrixPerspectiveFovLH(fov_, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_ / 2.0f, 0.1f, 1000.0f);

	_proj = XMMatrixPerspectiveFovLH(fov_, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 1.0f, 1000.0f);
}

//�X�V�i�r���[�s��쐬�j
void Camera::Update()
{
	//�r���[�s��
	_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
		XMVectorSet(_target.x, _target.y, _target.z, 0), XMVectorSet(0, 1, 0, 0));

	//�r���{�[�h�s��
	//�i��ɃJ�����̕��������悤�ɉ�]������s��B�p�[�e�B�N���ł����g��Ȃ��j
	//http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	_billBoard = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&_target) - XMLoadFloat3(&_position), XMVectorSet(0, 1, 0, 0));
	_billBoard = XMMatrixInverse(nullptr, _billBoard);
}

//�œ_��ݒ�
void Camera::SetTarget(XMFLOAT3 target) { _target = target; }

//�ʒu��ݒ�
void Camera::SetPosition(XMFLOAT3 position) { _position = position; }

//�œ_���擾
XMFLOAT3 Camera::GetTarget() { return _target; }

//�ʒu���擾
XMFLOAT3 Camera::GetPosition() { return _position; }

//�r���[�s����擾
XMMATRIX Camera::GetViewMatrix() { return _view; }

//�v���W�F�N�V�����s����擾
XMMATRIX Camera::GetProjectionMatrix()
{
	switch (viewFlag)
	{
	case 0:
		return _proj;
	case 1:
		return _proj2;		
	default:
		return _proj;
	}
}

void Camera::SetViewFlag(int flag)
{
	viewFlag = flag;
}

//����p�̐ݒ�(�x���@)
void Camera::SetFOV(float fov)
{
	fov_ = fov;
	//�v���W�F�N�V�����s��
	_proj = XMMatrixPerspectiveFovLH(fov_, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 1.0f, 1000.0f);
	_proj2 = XMMatrixPerspectiveFovLH(fov_, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_ / 2.0f, 0.1f, 1000.0f);
}

//�r���{�[�h�p��]�s����擾
XMMATRIX Camera::GetBillboardMatrix() { return _billBoard; }

//���[���h���W���X�N���[�����W�ɕϊ�
XMFLOAT3 Camera::ToWorldCalcScreen(XMFLOAT3 position)
{
	//position��XMVECTOR�ɕϊ�
	XMVECTOR worldPositionVec = XMLoadFloat3(&position);

	// ���[���h���W���X�N���[�����W�ɕϊ�
	XMVECTOR screenPositionVec = XMVector3Project(worldPositionVec, 0, 0,
		Direct3D::vp_left.Width, Direct3D::vp_left.Height, Direct3D::vp_left.MinDepth, Direct3D::vp_left.MaxDepth,
		_proj, _view, XMMatrixIdentity());

	// �X�N���[�����W�̎擾
	XMFLOAT3 screenPosition;
	XMStoreFloat3(&screenPosition, screenPositionVec);
	
	//�s�N�Z������-1����1�͈̔͂ɕϊ�
	screenPosition = Math::PixelToTransform(screenPosition);

	return screenPosition;
}
	////�K�v�ȕϐ����쐬
	//XMMATRIX invView, invPrj, viewPor, invViewport;

	////position��XMVECTOR�ɕϊ�
	//XMVECTOR vPos = XMLoadFloat3(&position);

	////�e�s��̋t�s����Z�o
	//invView = XMMatrixInverse(nullptr, _view);
	//invPrj	= XMMatrixInverse(nullptr, _proj);

	////�r���[�|�[�g��XMMATRIX�ɕϊ�
	//viewPor = XMMatrixIdentity();
	//viewPor.r[0] = XMVectorSet(Direct3D::vp_left.Width / 2.0f, 0.0f, 0.0f, 0.0f);
	//viewPor.r[1] = XMVectorSet(0.0f, -Direct3D::vp_left.Height / 2.0f, 0.0f, 0.0f);
	//viewPor.r[3] = XMVectorSet(Direct3D::vp_left.TopLeftX + Direct3D::vp_left.Width / 2.0f, Direct3D::vp_left.TopLeftY + Direct3D::vp_left.Height / 2.0f, 0.0f, 1.0f);

	//invViewport = XMMatrixInverse(nullptr, viewPor);

	//// �t�ϊ�
	//XMMATRIX tmp = invView * invPrj * invViewport;
	//XMVECTOR pout = XMVector3TransformCoord(vPos, tmp);

	//XMFLOAT3 fPort;
	//XMStoreFloat3(&fPort, pout);
	//return fPort;









