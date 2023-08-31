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

// OBB�ƕ��ʂ̏Փ˔���
bool OBB::OBBvsPlane(OBB& obb, XMFLOAT3 pos, XMVECTOR nomal, float* Len)
{
    // ���ʂ̖@���ɑ΂���OBB�̎ˉe���̒������Z�o
    float r = 0.0f;               // �ߐڋ���
    XMVECTOR PlaneNormal = nomal; // ���ʂ̖@���x�N�g��
    for (int i = 0; i < 3; i++) {
        XMVECTOR Direct = obb.GetDirect(i); // OBB��1�̎��x�N�g��
        r += fabs(XMVectorGetX(XMVector3Dot((Direct * obb.GetLen_W(i)), PlaneNormal)));
    }

    // ���ʂ�OBB�̋������Z�o
    XMVECTOR ObbPos = obb.GetPos_W();
    XMVECTOR PlanePos = XMLoadFloat3(&pos);
    float s = XMVectorGetX((XMVector3Dot((ObbPos - PlanePos), PlaneNormal)));

    // �߂��������Z�o
    if (Len != NULL) {
        if (s > 0)
            *Len = r - fabs(s);
        else
            *Len = r + fabs(s);
    }

    // �Փ˔���
    if (fabs(s) - r < 0.0f)
        return true; // �Փ˂��Ă���

    return false; // �Փ˂��Ă��Ȃ�
}

//OBB��OBB�̏Փ˔���
bool OBB::ColOBBs(OBB& obb1, OBB& obb2)
{
    // �e�����x�N�g���̊m��
    // �iN***:�W���������x�N�g���j
    XMVECTOR NAe1 = obb1.GetDirect(0), Ae1 = NAe1 * obb1.GetLen_W(0);
    XMVECTOR NAe2 = obb1.GetDirect(1), Ae2 = NAe2 * obb1.GetLen_W(1);
    XMVECTOR NAe3 = obb1.GetDirect(2), Ae3 = NAe3 * obb1.GetLen_W(2);
    XMVECTOR NBe1 = obb2.GetDirect(0), Be1 = NBe1 * obb2.GetLen_W(0);
    XMVECTOR NBe2 = obb2.GetDirect(1), Be2 = NBe2 * obb2.GetLen_W(1);
    XMVECTOR NBe3 = obb2.GetDirect(2), Be3 = NBe3 * obb2.GetLen_W(2);
    XMVECTOR Interval = obb1.GetPos_W() - obb2.GetPos_W();

    // ������ : Ae1
    float rA = XMVectorGetX(XMVector3Length(Ae1));
    float rB = LenSegOnSeparateAxis(NAe1, Be1, Be2, Be3);
    float L = fabs(XMVectorGetX(XMVector3Dot(Interval, NAe1)));
    if (L > rA + rB)
        return false; // �Փ˂��Ă��Ȃ�

    // ������ : Ae2
    rA = XMVectorGetX(XMVector3Length(Ae2));
    rB = LenSegOnSeparateAxis(NAe2, Be1, Be2, Be3);
    L = fabs(XMVectorGetX(XMVector3Dot(Interval, NAe2)));
    if (L > rA + rB)
        return false;

    // ������ : Ae3
    rA = XMVectorGetX(XMVector3Length(Ae3));
    rB = LenSegOnSeparateAxis(NAe3, Be1, Be2, Be3);
    L = fabs(XMVectorGetX(XMVector3Dot(Interval, NAe3)));
    if (L > rA + rB)
        return false;

    // ������ : Be1
    rA = LenSegOnSeparateAxis(NBe1, Ae1, Ae2, Ae3);
    rB = XMVectorGetX(XMVector3Length(Be1));
    L = fabs(XMVectorGetX(XMVector3Dot(Interval, NBe1)));
    if (L > rA + rB)
        return false;

    // ������ : Be2
    rA = LenSegOnSeparateAxis(NBe2, Ae1, Ae2, Ae3);
    rB = XMVectorGetX(XMVector3Length(Be2));
    L = fabs(XMVectorGetX(XMVector3Dot(Interval, NBe2)));
    if (L > rA + rB)
        return false;

    // ������ : Be3
    rA = LenSegOnSeparateAxis(NBe3, Ae1, Ae2, Ae3);
    rB = XMVectorGetX(XMVector3Length(Be3));
    L = fabs(XMVectorGetX(XMVector3Dot(Interval, NBe3)));
    if (L > rA + rB)
        return false;

    // ������ : C11
    XMVECTOR Cross;
    Cross = XMVector3Cross(NAe1, NBe1);
    rA = LenSegOnSeparateAxis(Cross, Ae2, Ae3);
    rB = LenSegOnSeparateAxis(Cross, Be2, Be3);
    L = fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));
    if (L > rA + rB)
        return false;

    // ������ : C12
    Cross = XMVector3Cross (NAe1, NBe2);
    rA = LenSegOnSeparateAxis(Cross, Ae2, Ae3);
    rB = LenSegOnSeparateAxis(Cross, Be1, Be3);
    L = fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));
    if (L > rA + rB)
        return false;

    // ������ : C13
    Cross = XMVector3Cross(NAe1, NBe3);
    rA = LenSegOnSeparateAxis(Cross, Ae2, Ae3);
    rB = LenSegOnSeparateAxis(Cross, Be1, Be2);
    L = fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));
    if (L > rA + rB)
        return false;

    // ������ : C21
    Cross = XMVector3Cross(NAe2, NBe1);
    rA = LenSegOnSeparateAxis(Cross, Ae1, Ae3);
    rB = LenSegOnSeparateAxis(Cross, Be2, Be3);
    L = fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));
    if (L > rA + rB)
        return false;

    // ������ : C22
    Cross = XMVector3Cross(NAe2, NBe2);
    rA = LenSegOnSeparateAxis(Cross, Ae1, Ae3);
    rB = LenSegOnSeparateAxis(Cross, Be1, Be3);
    L = fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));
    if (L > rA + rB)
        return false;

    // ������ : C23
    Cross = XMVector3Cross(NAe2, NBe3);
    rA = LenSegOnSeparateAxis(Cross, Ae1, Ae3);
    rB = LenSegOnSeparateAxis(Cross, Be1, Be2);
    L = fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));
    if (L > rA + rB)
        return false;

    // ������ : C31
    Cross = XMVector3Cross(NAe3, NBe1);
    rA = LenSegOnSeparateAxis(Cross, Ae1, Ae2);
    rB = LenSegOnSeparateAxis(Cross, Be2, Be3);
    L = fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));
    if (L > rA + rB)
        return false;

    // ������ : C32
    Cross = XMVector3Cross(NAe3, NBe2);
    rA = LenSegOnSeparateAxis(Cross, Ae1, Ae2);
    rB = LenSegOnSeparateAxis(Cross, Be1, Be3);
    L = fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));
    if (L > rA + rB)
        return false;

    // ������ : C33
    Cross = XMVector3Cross(NAe3, NBe3);
    rA = LenSegOnSeparateAxis(Cross, Ae1, Ae2);
    rB = LenSegOnSeparateAxis(Cross, Be1, Be2);
    L = fabs(XMVectorGetX(XMVector3Dot(Interval, Cross)));
    if (L > rA + rB)
        return false;

    // �������ʂ����݂��Ȃ��̂Łu�Փ˂��Ă���v
    return true;
}

//�������ɓ��e���ꂽ���������瓊�e���������Z�o
float OBB::LenSegOnSeparateAxis(XMVECTOR Sep, XMVECTOR e1, XMVECTOR e2, XMVECTOR e3)
{
    // 3�̓��ς̐�Βl�̘a�œ��e���������v�Z
    // ������Sep�͕W��������Ă��邱��
    float r1 = fabs(XMVectorGetX(XMVector3Dot(Sep, e1)));
    float r2 = fabs(XMVectorGetX(XMVector3Dot(Sep, e2)));
    float r3;
    if (XMVectorGetX(e3) == 0  &&
        XMVectorGetY(e3) == 0  &&
        XMVectorGetZ(e3) == 0 )
    {
        r3 = (fabs(XMVectorGetX(XMVector3Dot(Sep, e3))));
    }
    else
    {
        r3 = 0;
    }
    return r1 + r2 + r3;
}

//OBB�Ƌ��̂̏Փ˔���
float OBB::LenOBBToPoint(OBB& obb, XMFLOAT3 pos)
{
    XMVECTOR Vec = { 0, 0, 0 };   // �ŏI�I�ɒ��������߂�x�N�g��

    // �e���ɂ��Ă͂ݏo�������̃x�N�g�����Z�o
    for (int i = 0; i < 3; i++)
    {
        float L = obb.GetLen_W(i);
        if (L <= 0) continue;  // L=0�͌v�Z�ł��Ȃ�
        XMVECTOR vPos = XMLoadFloat3(&pos);
        float s = XMVectorGetX(XMVector3Dot(vPos - obb.GetPos_W(), obb.GetDirect(i)) / L);

        // s�̒l����A�͂ݏo��������������΂��̃x�N�g�������Z
        s = fabs(s);
        if (s > 1)
            Vec += (1 - s) * L * obb.GetDirect(i);   // �͂ݏo���������̃x�N�g���Z�o
    }

    return XMVectorGetX(XMVector3Length(Vec));   // �������o��
}

