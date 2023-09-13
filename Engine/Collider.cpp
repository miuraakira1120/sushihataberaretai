#include "BoxCollider.h"
#include "SphereCollider.h"
#include "GameObject.h"
#include "Model.h"
#include "Transform.h"

#include "../OBB.h"

//コンストラクタ
Collider::Collider():
	pGameObject_(nullptr)
{
}

//デストラクタ
Collider::~Collider()
{
}

//箱型同士の衝突判定
//引数：boxA	１つ目の箱型判定
//引数：boxB	２つ目の箱型判定
//戻値：接触していればtrue
bool Collider::IsHitBoxVsBox(BoxCollider* boxA, BoxCollider* boxB)
{

	XMFLOAT3 boxPosA = Math::Float3Add(boxA->pGameObject_->GetWorldPosition(), boxA->center_);
	XMFLOAT3 boxPosB = Math::Float3Add(boxB->pGameObject_->GetWorldPosition(), boxB->center_);

	//OBBで当たり判定
	OBB boxAOBB, boxBOBB;

	//OBBに必要な軸のリストを作る
	//各軸に対するベクトルを求める
	XMMATRIX rotateX, rotateY, rotateZ, m;
	rotateX = XMMatrixRotationX(XMConvertToRadians(boxA->pGameObject_->GetTransform().rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(boxA->pGameObject_->GetTransform().rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(boxA->pGameObject_->GetTransform().rotate_.z));
	//回転行列を求める
	m = rotateZ * rotateX * rotateY;
	//リストにセットする
	std::vector<XMVECTOR> fAxisA = { 
		XMVector3TransformCoord(AXIS_BASE_X, m), 
		XMVector3TransformCoord(AXIS_BASE_Y, m), 
		XMVector3TransformCoord(AXIS_BASE_Z, m)
	};

	//各軸に対するベクトルを求める
	rotateX = XMMatrixRotationX(XMConvertToRadians(boxB->pGameObject_->GetTransform().rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(boxB->pGameObject_->GetTransform().rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(boxB->pGameObject_->GetTransform().rotate_.z));
	
	//リストにセットする
	std::vector<XMVECTOR> fAxisB = {
		XMVector3TransformCoord(AXIS_BASE_X, m),
		XMVector3TransformCoord(AXIS_BASE_Y, m),
		XMVector3TransformCoord(AXIS_BASE_Z, m)
	};

	//OBBに必要な長さのリストを作る
	std::vector<float> fLengthA = { boxA->size_.x / 2, boxA->size_.y / 2, boxA->size_.z / 2};
	std::vector<float> fLengthB = { boxB->size_.x, boxB->size_.y, boxB->size_.z};

	//OBBに必要な情報をセットする
	boxAOBB.SetOBBAll(XMLoadFloat3(&boxPosA), fAxisA, fLengthA);
	boxBOBB.SetOBBAll(XMLoadFloat3(&boxPosB), fAxisB, fLengthB);

	//OBBとOBBの衝突判定
	if (boxAOBB.ColOBBs(boxAOBB, boxBOBB))
	{
		return true;
	}
	return false;
}

//箱型と球体の衝突判定
//引数：box	箱型判定
//引数：sphere	２つ目の箱型判定
//戻値：接触していればtrue
bool Collider::IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere)
{
	XMFLOAT3 boxPos = Math::Float3Add(box->pGameObject_->GetWorldPosition(), box->center_);
	//OBBで当たり判定
	OBB boxOBB;

	//OBBに必要な軸のリストを作る
	//各軸に対するベクトルを求める
	XMMATRIX rotateX, rotateY, rotateZ, m;
	rotateX = XMMatrixRotationX(XMConvertToRadians(box->pGameObject_->GetTransform().rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(box->pGameObject_->GetTransform().rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(box->pGameObject_->GetTransform().rotate_.z));
	//回転行列を求める
	m = rotateZ * rotateY * rotateX;
	//リストにセットする
	std::vector<XMVECTOR> fAxis = {
		XMVector3TransformCoord(AXIS_BASE_X, m),
		XMVector3TransformCoord(AXIS_BASE_Y, m),
		XMVector3TransformCoord(AXIS_BASE_Z, m)
	};
	//OBBに必要な長さのリストを作る
	std::vector<float> fLength = { box->size_.x / 2 , box->size_.y / 2, box->size_.z / 2};
	//OBBに必要な情報をセットする
	boxOBB.SetOBBAll(XMLoadFloat3(&boxPos), fAxis, fLength);

	if (boxOBB.LenOBBToPoint(boxOBB, Math::Float3Add(sphere->pGameObject_->GetWorldPosition(), sphere->center_)) <= sphere->size_.x)
	{
		return true;
	}
	return false;

}

//球体同士の衝突判定
//引数：circleA	１つ目の球体判定
//引数：circleB	２つ目の球体判定
//戻値：接触していればtrue
bool Collider::IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB)
{
	XMFLOAT3 centerA = circleA->center_;
	XMFLOAT3 positionA = circleA->pGameObject_->GetWorldPosition();
	XMFLOAT3 centerB = circleB->center_;
	XMFLOAT3 positionB = circleB->pGameObject_->GetWorldPosition();

	XMVECTOR v = (XMLoadFloat3(&centerA) + XMLoadFloat3(&positionA))
		- (XMLoadFloat3(&centerB) + XMLoadFloat3(&positionB));

	if (XMVector3Length(v).m128_f32[0] <= circleA->size_.x + circleB->size_.x)
	{
		return true;
	}

	return false;
}

//テスト表示用の枠を描画
//引数：position	オブジェクトの位置
void Collider::Draw(XMFLOAT3 position)
{
	Transform transform;
	transform.position_ = XMFLOAT3(position.x + center_.x, position.y + center_.y, position.z + center_.z);
	transform.scale_ = size_;
	transform.rotate_ = pGameObject_->GetTransform().rotate_;
	transform.Calclation();
	Model::SetTransform(hDebugModel_, transform);
	Model::Draw(hDebugModel_);
}
