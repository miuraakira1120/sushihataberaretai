#include "Transform.h"
#include "GameObject.h"


Transform::Transform() : pParent_(nullptr)
{
	position_ = XMFLOAT3(0, 0, 0);
	rotate_ = XMFLOAT3(0, 0, 0);
	scale_ = XMFLOAT3(1, 1, 1);
	matTranslate_ = XMMatrixIdentity();
	matRotate_ = XMMatrixIdentity();
	matScale_ = XMMatrixIdentity();
	axisMatrix_ = { 0.0f , 0.0f, 0.0f };
	transMode = TRANS_NORMAL_MODE;
	parentNum = 0;
	transParentTmp = this;
	pravTransMode = -1;
}



Transform::~Transform()
{
}

void Transform::Calclation()
{
	//移動行列
	matTranslate_ = XMMatrixTranslation(position_.x, position_.y, position_.z);

	//回転行列
	XMMATRIX rotateX, rotateY, rotateZ;
	rotateX = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
	rotateY = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
	rotateZ = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
	matRotate_ = rotateZ * rotateX * rotateY;

	//拡大縮小
	matScale_ = XMMatrixScaling(scale_.x, scale_.y, scale_.z);
}

XMMATRIX Transform::GetWorldMatrix() 
{
	Calclation();
	switch (transMode)
	{
	case TRANS_NORMAL_MODE :
		pravTransMode = TRANS_NORMAL_MODE;
		if (pParent_)
		{
			return  matScale_ * matRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
		}
		return  matScale_ * matRotate_ * matTranslate_;

	case TRANS_AXIS_MODE :
		pravTransMode = TRANS_AXIS_MODE;
		if (pParent_)
		{
			return  matScale_ * XMMatrixTranslation(axisMatrix_.x, axisMatrix_.y, axisMatrix_.z) * matRotate_
				* XMMatrixTranslation(-(axisMatrix_.x), -(axisMatrix_.y), -(axisMatrix_.z)) * matTranslate_ * pParent_->GetWorldMatrix();
		}
		return  matScale_ * matRotate_ * matTranslate_;

	case TRANS_CHANGEPARENT_MODE :
		for (int i = 0; i < parentNum + 1; i++)
		{
			if (transParentTmp->pParent_ != nullptr)
			{
				transParentTmp = transParentTmp->pParent_;
			}
		}
		XMMATRIX returnMatrix = matScale_ * matRotate_ * matTranslate_ * transParentTmp->GetWorldMatrix();
		//NumberOfLoopsのリセット
		transParentTmp = this;
		NumberOfLoops = 0;
		if (pravTransMode != TRANS_CHANGEPARENT_MODE)
		{
			rotate_ = pParent_->rotate_;
		}
		pravTransMode = TRANS_CHANGEPARENT_MODE;
		return  returnMatrix;

	case TRANS_NONROTATE :
		pravTransMode = TRANS_NONROTATE;
		if (pParent_)
		{
			return  matScale_ * changeMatRotate_ * matTranslate_ * pParent_->GetWorldMatrix();
		}
		return  matScale_ * matRotate_ * matTranslate_;
		break;
	default:
		break;
	}
}

void Transform::MoveAxisRotate()
{
	transMode = TRANS_AXIS_MODE;
}

void Transform::ChangeParentRotate(int parentNum_)
{
	transMode = TRANS_CHANGEPARENT_MODE;
	parentNum = parentNum_;
}

void Transform::NomalAxisRotate()
{
	transMode = TRANS_NORMAL_MODE;
}

void Transform::SetAxisTrans(XMFLOAT3 mat)
{
	axisMatrix_ = mat;
}

void Transform::ArbRotationAxis(XMFLOAT3* pos, float rot, XMVECTOR axis, XMVECTOR end)
{
	//度数法→弧度法に変換
	float rad = XMConvertToRadians(rot);

	ArbRotationAxisR(pos, rad, axis, end);
}
void Transform::ArbRotationAxisR(XMFLOAT3* pos, float rad, XMVECTOR axis, XMVECTOR end)
{
	//endを原点に移動
	XMVECTOR vPos = XMLoadFloat3(pos);
	vPos -= end;
	axis -= end;

	//クォータニオン、共役クォータニオンを作成
	XMVECTOR Qua = XMQuaternionRotationAxis(axis, rad);
	XMVECTOR Conj = XMQuaternionConjugate(Qua);

	//ansに移動後の位置情報が入る
	XMVECTOR ans = vPos;

	//それぞれのベクトルをかける
	ans = XMQuaternionMultiply(Conj, vPos);
	ans = XMQuaternionMultiply(ans, Qua);

	ans += end;

	//posの値を更新
	XMStoreFloat3(pos, ans);
}

void Transform::SetRotateMode(TransMode mode)
{
	transMode = mode;
}

