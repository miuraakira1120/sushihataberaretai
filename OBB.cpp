#include "OBB.h"

void OBB::SetPos(XMVECTOR position)
{
	pos = position;
}

void OBB::SetNormalDirect(std::vector<XMVECTOR> direct)
{
	normalDirect = direct;
}

void OBB::SetLength(std::vector<float> length)
{
	fLength = length;
}

void OBB::SetOBBAll(XMVECTOR position, std::vector<XMVECTOR> direct, std::vector<float> length)
{
	pos = position;
	normalDirect = direct;
	fLength = length;
}

XMVECTOR OBB::GetDirect(int elem)
{
	if (normalDirect.size() > elem && 0 <= elem)
	{
		return normalDirect[elem];
	}
	return XMVectorZero();
}

float OBB::GetLen_W(int elem)
{
	if (fLength.size() > elem && 0 <= elem)
	{
		return fLength[elem];
	}
	return -1;
}

XMVECTOR OBB::GetPos_W()
{
	return pos;
}

// OBBと平面の衝突判定
bool OBB::OBBvsPlane(OBB& obb, XMFLOAT3 pos, XMVECTOR nomal, float* Len)
{
    // 平面の法線に対するOBBの射影線の長さを算出
    float r = 0.0f;               // 近接距離
    XMVECTOR PlaneNormal = nomal; // 平面の法線ベクトル
    for (int i = 0; i < 3; i++) {
        XMVECTOR Direct = obb.GetDirect(i); // OBBの1つの軸ベクトル
        r += fabs(XMVectorGetX(XMVector3Dot((Direct * obb.GetLen_W(i)), PlaneNormal)));
    }

    // 平面とOBBの距離を算出
    XMVECTOR ObbPos = obb.GetPos_W();
    XMVECTOR PlanePos = XMLoadFloat3(&pos);
    float s = XMVectorGetX((XMVector3Dot((ObbPos - PlanePos), PlaneNormal)));

    // 戻し距離を算出
    if (Len != NULL) {
        if (s > 0)
            *Len = r - fabs(s);
        else
            *Len = r + fabs(s);
    }

    // 衝突判定
    if (fabs(s) - r < 0.0f)
        return true; // 衝突している

    return false; // 衝突していない
}

