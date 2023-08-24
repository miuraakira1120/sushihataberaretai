#pragma once
#include <DirectXMath.h>

using namespace DirectX;

enum TransMode
{
	TRANS_NORMAL_MODE,			//基本的な座標
	TRANS_AXIS_MODE,			//軸を移動して回転するか
	TRANS_CHANGEPARENT_MODE,	//親を変えて移動
	TRANS_NONROTATE,			//rotate_を使わずに回転
	TRANS_MAX,
};

//-----------------------------------------------------------
//位置、向き、拡大率などを管理するクラス
//-----------------------------------------------------------
class Transform
{
private:
	TransMode transMode;		//今のTransMode
	
public:
	XMMATRIX matTranslate_;		//移動行列
	XMMATRIX matRotate_;		//回転行列
	XMMATRIX changeMatRotate_;	//TRANS_NONROTATEの時の回転行列	
	XMMATRIX matScale_;			//拡大行列
	XMFLOAT3 position_;			//位置
	XMFLOAT3 rotate_;			//向き
	XMFLOAT3 scale_;			//拡大率
	Transform * pParent_;		//親オブジェクトの情報
	XMFLOAT3 axisMatrix_;		//このマトリクスを軸に回転する
	Transform* transParentTmp;	//親をさかのぼるために使うポインタ変数
	unsigned int parentNum;		//親をどれくらいさかのぼるか
	unsigned int NumberOfLoops;	//何回ループしたか
	unsigned int pravTransMode;	//1フレーム前のTransMode
	

	//コンストラクタ
	Transform();

	//デストラクタ
	~Transform();

	//各行列の計算
	//引数：なし
	//戻値：なし
	void Calclation();

	//ワールド行列を取得
	//引数：なし
	//戻値：その時点でのワールド行列
	XMMATRIX GetWorldMatrix();

	void NomalAxisRotate();	//軸を移動しないで回転する
	void MoveAxisRotate();  //軸を移動して回転する

	/// <summary>
	/// 回転の親を変える
	/// </summary>
	/// <param name="引数1 parentNum : 何番目の親で回転するか(0が元の親)"></param>
	void ChangeParentRotate(int parentNum_);

	void SetAxisTrans(XMFLOAT3 mat);//この軸で回る

	/// <summary>
	/// 距離を求める関数
	/// </summary>
	/// <param name="引数1 : 位置1"></param>
	/// <param name="引数2 : 位置2"></param>
	/// <returns></returns>
	static float FloatDistance(XMFLOAT3 a, XMFLOAT3 b)
	{
		float abX = a.x - b.x;
		float abY = a.y - b.y;
		float abZ = a.z - b.z;
		return (float)sqrt((abX * abX) + (abY + abY) + (abZ + abZ));
	}

	/// <summary>原点を通る任意軸回転</summary>
	/// <param name="pos">移動させたいものの位置</param>
	/// <param name="rot">回転角度(度数法)</param>
	/// <param name="axis">原点以外の軸となる位置ベクトル</param>
	/// <param name="end">軸のもう一端の位置ベクトル(無指定で原点になる)</param>
	void ArbRotationAxis(XMFLOAT3* pos, float rot, XMVECTOR axis, XMVECTOR end = { 0,0,0,0 });

	/// <summary>原点を通る任意軸回転</summary>
	/// <param name="pos">移動させたいものの位置</param>
	/// <param name="rad">回転角度(ラジアン)</param>
	/// <param name="axis">原点以外の軸となる位置ベクトル</param>
	/// <param name="end">軸のもう一端の位置ベクトル(無指定で原点になる)</param>
	void ArbRotationAxisR(XMFLOAT3* pos, float rad, XMVECTOR axis, XMVECTOR end = { 0,0,0,0 });

	//回転のモードを変える
	void SetRotateMode(TransMode mode);
};

