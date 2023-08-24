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

//初期化（プロジェクション行列作成）
void Camera::Initialize()
{
	_position = XMFLOAT3(0, 3, -10);	//カメラの位置
	_target = XMFLOAT3( 0, 0, 0);	//カメラの焦点

	viewFlag = 0;

	fov_ = XM_PIDIV4;	//視野角(2分の1π{90度})

	//プロジェクション行列
	//_proj = XMMatrixPerspectiveFovLH(fov_, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 0.1f, 1000.0f);
	_proj2 = XMMatrixPerspectiveFovLH(fov_, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_ / 2.0f, 0.1f, 1000.0f);

	_proj = XMMatrixPerspectiveFovLH(fov_, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 1.0f, 1000.0f);
}

//更新（ビュー行列作成）
void Camera::Update()
{
	//ビュー行列
	_view = XMMatrixLookAtLH(XMVectorSet(_position.x, _position.y, _position.z, 0),
		XMVectorSet(_target.x, _target.y, _target.z, 0), XMVectorSet(0, 1, 0, 0));

	//ビルボード行列
	//（常にカメラの方を向くように回転させる行列。パーティクルでしか使わない）
	//http://marupeke296.com/DXG_No11_ComeOnBillboard.html
	_billBoard = XMMatrixLookAtLH(XMVectorSet(0, 0, 0, 0), XMLoadFloat3(&_target) - XMLoadFloat3(&_position), XMVectorSet(0, 1, 0, 0));
	_billBoard = XMMatrixInverse(nullptr, _billBoard);
}

//焦点を設定
void Camera::SetTarget(XMFLOAT3 target) { _target = target; }

//位置を設定
void Camera::SetPosition(XMFLOAT3 position) { _position = position; }

//焦点を取得
XMFLOAT3 Camera::GetTarget() { return _target; }

//位置を取得
XMFLOAT3 Camera::GetPosition() { return _position; }

//ビュー行列を取得
XMMATRIX Camera::GetViewMatrix() { return _view; }

//プロジェクション行列を取得
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

//視野角の設定(度数法)
void Camera::SetFOV(float fov)
{
	fov_ = fov;
	//プロジェクション行列
	_proj = XMMatrixPerspectiveFovLH(fov_, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_, 1.0f, 1000.0f);
	_proj2 = XMMatrixPerspectiveFovLH(fov_, (FLOAT)Direct3D::screenWidth_ / (FLOAT)Direct3D::screenHeight_ / 2.0f, 0.1f, 1000.0f);
}

//ビルボード用回転行列を取得
XMMATRIX Camera::GetBillboardMatrix() { return _billBoard; }

//ワールド座標をスクリーン座標に変換
XMFLOAT3 Camera::ToWorldCalcScreen(XMFLOAT3 position)
{
	//positionをXMVECTORに変換
	XMVECTOR worldPositionVec = XMLoadFloat3(&position);

	// ワールド座標をスクリーン座標に変換
	XMVECTOR screenPositionVec = XMVector3Project(worldPositionVec, 0, 0,
		Direct3D::vp_left.Width, Direct3D::vp_left.Height, Direct3D::vp_left.MinDepth, Direct3D::vp_left.MaxDepth,
		_proj, _view, XMMatrixIdentity());

	// スクリーン座標の取得
	XMFLOAT3 screenPosition;
	XMStoreFloat3(&screenPosition, screenPositionVec);
	
	//ピクセルから-1から1の範囲に変換
	screenPosition = Math::PixelToTransform(screenPosition);

	return screenPosition;
}
	////必要な変数を作成
	//XMMATRIX invView, invPrj, viewPor, invViewport;

	////positionのXMVECTORに変換
	//XMVECTOR vPos = XMLoadFloat3(&position);

	////各行列の逆行列を算出
	//invView = XMMatrixInverse(nullptr, _view);
	//invPrj	= XMMatrixInverse(nullptr, _proj);

	////ビューポートをXMMATRIXに変換
	//viewPor = XMMatrixIdentity();
	//viewPor.r[0] = XMVectorSet(Direct3D::vp_left.Width / 2.0f, 0.0f, 0.0f, 0.0f);
	//viewPor.r[1] = XMVectorSet(0.0f, -Direct3D::vp_left.Height / 2.0f, 0.0f, 0.0f);
	//viewPor.r[3] = XMVectorSet(Direct3D::vp_left.TopLeftX + Direct3D::vp_left.Width / 2.0f, Direct3D::vp_left.TopLeftY + Direct3D::vp_left.Height / 2.0f, 0.0f, 1.0f);

	//invViewport = XMMatrixInverse(nullptr, viewPor);

	//// 逆変換
	//XMMATRIX tmp = invView * invPrj * invViewport;
	//XMVECTOR pout = XMVector3TransformCoord(vPos, tmp);

	//XMFLOAT3 fPort;
	//XMStoreFloat3(&fPort, pout);
	//return fPort;









