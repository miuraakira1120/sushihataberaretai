#include <vector>
#include <DirectXMath.h>
#include <directxmath.h>


using namespace DirectX;


class OBB
{
	XMVECTOR pos;				   // �ʒu
	std::vector<XMVECTOR> normalDirect;	   // �����x�N�g��
	std::vector<float> fLength;              // �e�������̒���

public:
	void SetPos(XMVECTOR position);
	void SetNormalDirect(std::vector<XMVECTOR> direct);
	void SetLength(std::vector<float> length);
	
	void SetOBBAll(XMVECTOR position, std::vector<XMVECTOR> direct, std::vector<float> length);

	XMVECTOR GetDirect(int elem);   // �w�莲�ԍ��̕����x�N�g�����擾
	float GetLen_W(int elem);       // �w�莲�����̒������擾
	XMVECTOR GetPos_W();            // �ʒu���擾

	/// <summary>
	/// OBB�ƕ��ʂ̏Փ˔���
	/// </summary>
	bool OBBvsPlane(OBB& obb, XMFLOAT3 pos, XMVECTOR nomal, float* Len = 0);
};