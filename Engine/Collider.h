#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

//クラスの前方宣言
class GameObject;
class BoxCollider;
class SphereCollider;


//あたり判定のタイプ
enum ColliderType
{
	COLLIDER_BOX,		//箱型
	COLLIDER_CIRCLE		//球体
};

//-----------------------------------------------------------
//あたり判定を管理するクラス
//-----------------------------------------------------------
class Collider
{
	//それぞれのクラスのprivateメンバにアクセスできるようにする
	friend class BoxCollider;
	friend class SphereCollider;

	//軸の基準
	const XMVECTOR AXIS_BASE_X = { 1.0f,0,0 };
	const XMVECTOR AXIS_BASE_Y = { 0,1.0f,0 };
	const XMVECTOR AXIS_BASE_Z = { 0,0,1.0f };

protected:
	GameObject*		pGameObject_;	//この判定をつけたゲームオブジェクト
	ColliderType	type_;			//種類
	XMFLOAT3		center_;		//中心位置（ゲームオブジェクトの原点から見た位置）
	XMFLOAT3		size_;			//判定サイズ（幅、高さ、奥行き）
	int				hDebugModel_;	//デバッグ表示用のモデルのID

public:

	//関数ポインタ
	using FunctionPtr = void (GameObject::*)(GameObject*);

	FunctionPtr OnCollision;  //当たった時に呼ばれる関数のポインタ
	FunctionPtr OutCollision; //当たらなくなった時に呼ばれる関数のポインタ

	//関数ポインタセットするとき
	void SetHitFunc(FunctionPtr func) { OnCollision = func; }
	void SetHitOutFunc(FunctionPtr func) { OutCollision = func; }

	//コンストラクタ
	Collider();

	//デストラクタ
	virtual ~Collider();

	//接触判定（継承先のSphereColliderかBoxColliderでオーバーライド）
	//引数：target	相手の当たり判定
	//戻値：接触してればtrue
	virtual bool IsHit(Collider* target) = 0;

	//箱型同士の衝突判定
	//引数：boxA	１つ目の箱型判定
	//引数：boxB	２つ目の箱型判定
	//戻値：接触していればtrue
	bool IsHitBoxVsBox(BoxCollider* boxA, BoxCollider* boxB);

	//箱型と球体の衝突判定
	//引数：box	箱型判定
	//引数：sphere	２つ目の箱型判定
	//戻値：接触していればtrue
	bool IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere);

	//球体同士の衝突判定
	//引数：circleA	１つ目の球体判定
	//引数：circleB	２つ目の球体判定
	//戻値：接触していればtrue
	bool IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB);

	//当たった時に呼ばれる関数ポインタをセット
	template<class T>
	void SetHitFunc(void (T::* func)(GameObject*)) { SetHitFunc(static_cast<FunctionPtr>(func)); }

	//当たらなくなった時に呼ばれる関数のポインタをセット
	template<class T>
	void SetHitOutFunc(void (T::* func)(GameObject*)) { SetHitOutFunc(static_cast<FunctionPtr>(func)); }

	//テスト表示用の枠を描画
	//引数：position	オブジェクトの位置
	void Draw(XMFLOAT3 position);

	//セッター
	void SetGameObject(GameObject* gameObject) { pGameObject_ = gameObject; }

private:

	

};

