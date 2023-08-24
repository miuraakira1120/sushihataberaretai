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

