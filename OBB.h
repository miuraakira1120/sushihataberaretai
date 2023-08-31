#include <vector>
#include <DirectXMath.h>
#include <directxmath.h>


using namespace DirectX;


class OBB
{
	XMVECTOR pos;				   // 位置
	std::vector<XMVECTOR> normalDirect;	   // 方向ベクトル
	std::vector<float> fLength;              // 各軸方向の長さ

public:
	void SetPos(XMVECTOR position);
	void SetNormalDirect(std::vector<XMVECTOR> direct);
	void SetLength(std::vector<float> length);
	
	void SetOBBAll(XMVECTOR position, std::vector<XMVECTOR> direct, std::vector<float> length);

	XMVECTOR GetDirect(int elem);   // 指定軸番号の方向ベクトルを取得
	float GetLen_W(int elem);       // 指定軸方向の長さを取得
	XMVECTOR GetPos_W();            // 位置を取得

	/// <summary>
	/// OBBと平面の衝突判定
	/// </summary>
	bool OBBvsPlane(OBB& obb, XMFLOAT3 pos, XMVECTOR nomal, float* Len = 0);

	/// <summary>
	///  OBBとOBBの衝突判定
	/// http://marupeke296.com/COL_3D_No13_OBBvsOBB.html
	/// </summary>
	bool ColOBBs(OBB& obb1, OBB& obb2);

	/// <summary>
	/// 分離軸に投影された軸成分から投影線分長を算出
	/// </summary>
	/// <param name="Sep"></param>
	/// <param name="e1"></param>
	/// <param name="e2"></param>
	/// <param name="e3"></param>
	/// <returns></returns>
	float LenSegOnSeparateAxis(XMVECTOR Sep, XMVECTOR e1, XMVECTOR e2, XMVECTOR e3 = { 0,0,0 });

	//OBBと球体の衝突判定
	float LenOBBToPoint(OBB& obb, XMFLOAT3 pos);
};