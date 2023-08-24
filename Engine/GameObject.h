#pragma once
#include <DirectXMath.h>
#include <list>
#include <string>
#include <assert.h>
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Transform.h"
#include "Math.h"

using namespace DirectX;


//-----------------------------------------------------------
//全てのゲームオブジェクト（シーンも含めて）が継承するインターフェース
// ゲームオブジェクトは、親子構造になっていて、
// マトリクスの影響を受けることになる
//-----------------------------------------------------------
class GameObject
{
protected:
	
	//位置や向きなどを管理するオブジェクト
	Transform				 transform_;

	//オブジェクトの名前
	const std::string		 objectName_;

	//衝突判定リスト
	std::list<Collider*>	 colliderList_;	

	//オブジェクトのタグ
	std::string	   			 tag_;

	//前フレームからの移動ベクトル
	XMVECTOR				 vMoved;

	//モデルや画像ファイルの名前
	std::string				 pathName_;

	//オブジェクトごとのユニークな名前
	std::string				 uniqueName_;

	//アルファ値
	int						 alpha_;


public:
	//コンストラクタ
	GameObject();
	GameObject(GameObject* parent);
	GameObject(GameObject* parent, const std::string& name);
	GameObject(GameObject* parent, const std::string& name, const std::string& pathFilename);

	//デストラクタ
	virtual ~GameObject();

	//各オブジェクトで必ず作る関数
	virtual void Initialize(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw() = 0;
	virtual void Release(void) = 0;

	//継承元で使用使用するための関数
	//更新が呼ばれる前に設定しておきたいものがある時に使う
	virtual void SetUp() {};

	//自分の該当関数を読んだ後、子供の関数も呼ぶ
	void UpdateSub();
	void DrawSub();
	void ReleaseSub();


	////ローカル行列の取得（このオブジェクトの行列）
	////戻値：ローカル行列
	//XMMATRIX GetLocalMatrix();

	//ワールド行列の取得（親の影響を受けた最終的な行列）
	//戻値：ワールド行列
	XMMATRIX GetWorldMatrix();



	//各フラグの制御
	bool IsDead();			// 削除するかどうか
	void KillMe();			// 自分を削除する
	void Enter();			// Updateを許可
	void Leave();			// Updateを拒否
	void Visible();			// Drawを許可
	void Invisible();		// Drawを拒否
	bool IsInitialized();	// 初期化済みかどうか
	void SetInitialized();	// 初期化済みにする
	bool IsEntered();		// Update実行していいか
	bool IsVisibled();		// Draw実行していいか
	void DoSetUp();			//セットアップが完了した状態にする
	bool IsSetUp();			//セットアップが完了しているか
	void PutShadow();		//影をつける
	void DeleteShadow();	//影を消す
	bool IsSyadow();		


	//子オブジェクトリストを取得
	//戻値：子オブジェクトリスト
	std::list<GameObject*>* GetChildList();

	//親オブジェクトを取得
	//戻値：親オブジェクトのアドレス
	GameObject* GetParent();

	//名前でオブジェクトを検索（対象は自分の子供以下）
	//引数：name	検索する名前
	//戻値：見つけたオブジェクトのアドレス（見つからなければnullptr）
	GameObject* FindChildObject(const std::string& name);

	//名前でオブジェクトを検索（対象は全体）
	//引数：検索する名前
	//戻値：見つけたオブジェクトのアドレス
	GameObject* FindObject(const std::string& name) { return GetRootJob()->FindChildObject(name); }

	//オブジェクトの名前を取得
	//戻値：名前
	const std::string& GetObjectName(void) const;

	//子オブジェクトを追加（リストの最後へ）
	//引数：追加するオブジェクト
	void PushBackChild(GameObject* obj);

	//子オブジェクトを追加（リストの先頭へ）
	//引数：obj 追加するオブジェクト
	void PushFrontChild(GameObject* obj);

	//子オブジェクトを全て削除
	void KillAllChildren();

	//コライダー（衝突判定）を追加する
	void AddCollider(Collider * collider);

	//何かと衝突した場合に呼ばれる（オーバーライド用）
	//引数：pTarget	衝突した相手
	virtual void OnCollision(GameObject* pTarget) {};

	//衝突判定
	//引数：pTarget	衝突してるか調べる相手
	void Collision(GameObject* pTarget);

	//テスト用の衝突判定枠を表示
	void CollisionDraw();

	//RootJobを取得
	GameObject* GetRootJob();

	//各アクセス関数
	XMFLOAT3 GetPosition() { return transform_.position_; }
	XMFLOAT3 GetRotate() { return transform_.rotate_; }
	XMFLOAT3 GetScale() { return transform_.scale_; }
	XMFLOAT3 GetWorldPosition() { return Math::Float3Add(GetParent()->transform_.position_ , transform_.position_); }
	XMFLOAT3 GetWorldRotate() { return Math::Float3Add(GetParent()->transform_.rotate_, transform_.rotate_); }
	XMFLOAT3 GetWorldScale() { return Math::Float3Add(GetParent()->transform_.scale_, transform_.scale_); }
	std::string GetTag() { return tag_; }
	XMVECTOR GetMoved() {return vMoved ;}
	Transform GetTransform() { return transform_; }
	std::string GetName() { return objectName_; }
	std::string GetUniqueName() { return uniqueName_; }
	std::string GetPathName() { return pathName_; }


	void SetPosition(XMFLOAT3 position) { transform_.position_ = position; }
	void SetPosition(float x, float y, float z) { SetPosition(XMFLOAT3( x, y, z )); }
	void SetRotate(XMFLOAT3 rotate) { transform_.rotate_ = rotate; }
	void SetRotate(float x, float y, float z) { SetRotate(XMFLOAT3( x, y, z )); }
	void SetRotateX(float x) { SetRotate(x, transform_.rotate_.y, transform_.rotate_.z); }
	void SetRotateY(float y) { SetRotate(transform_.rotate_.x, y, transform_.rotate_.z); }
	void SetRotateZ(float z) { SetRotate(transform_.rotate_.x, transform_.rotate_.y, z); }
	void SetScale(XMFLOAT3 scale) { transform_.scale_ = scale; }
	void SetScale(float x, float y, float z) { SetScale(XMFLOAT3(x, y, z)); }
	void SetTag(std::string tag) { tag_ = tag; }
	void SetMoved(XMVECTOR moved) { vMoved = moved; }
	void SetPathName(std::string pathName) { pathName_ = pathName; }
	void SetUniqueName(std::string uniqueName) { uniqueName_ = uniqueName; }
	void SetAlpha(int alpha) { alpha_ = alpha; }


private:

	//オブジェクト削除（再帰）
	//引数：obj　削除するオブジェクト
	void KillObjectSub(GameObject* obj);

private:
	//フラグ
	struct OBJECT_STATE
	{
		unsigned initialized : 1;	//初期化済みか
		unsigned entered : 1;		//更新するか
		unsigned visible : 1;		//描画するか
		unsigned dead : 1;			//削除するか
		unsigned setUp : 1;			//セットアップしているか
		unsigned hasShadow : 1;		//影をつけるかどうか
	};
	OBJECT_STATE state_;

	//親オブジェクト
	GameObject* pParent_;

	//子オブジェクトリスト
	std::list<GameObject*> childList_;
};


//オブジェクトを作成するテンプレート
template <class T>
T* Instantiate(GameObject* pParent)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

//モデル(や画像)の名前と位置を引数にオブジェクトを作成するテンプレート
template <class T>
T* Instantiate(GameObject* pParent, std::string fileName, XMFLOAT3 pos)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetPathName(fileName);
	pNewObject->Initialize();
	pNewObject->SetPosition(pos);
	return pNewObject;
}

//モデル(や画像)の名前と位置、向き、拡大率を引数にオブジェクトを作成するテンプレート
template <class T>
T* Instantiate(GameObject* pParent, std::string fileName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca)
{
	T* pNewObject = new T(pParent);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->SetPathName(fileName);
	pNewObject->Initialize();
	pNewObject->SetPosition(pos);
	pNewObject->SetRotate(rot);
	pNewObject->SetScale(sca);
	return pNewObject;
}

//モデル(や画像)の名前と位置、向き、拡大率を引数にボタンを作成するテンプレート
template <class T>
T* InstantiateButton(GameObject* pParent, std::string fileName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca)
{
	T* pNewObject = new T(pParent, fileName);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	pNewObject->SetPosition(pos);
	pNewObject->SetRotate(rot);
	pNewObject->SetScale(sca);
	return pNewObject;
}

//モデル(や画像)の名前と位置、向き、拡大率を引数にボタンを作成するテンプレート
template <class T>
T* InstantiateButton(GameObject* pParent, std::string fileName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, std::string uniqueName)
{
	T* pNewObject = new T(pParent, fileName);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	pNewObject->SetPosition(pos);
	pNewObject->SetRotate(rot);
	pNewObject->SetScale(sca);
	pNewObject->SetUniqueName(uniqueName);
	return pNewObject;
}

//モデル(や画像)の名前と位置、向き、拡大率を引数にオブジェクトを作成するテンプレート
template <class T>
T* InstantiateImage(GameObject* pParent, std::string fileName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, int alpha = 255)
{
	T* pNewObject = new T(pParent, fileName, alpha);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	pNewObject->SetPosition(pos);
	pNewObject->SetRotate(rot);
	pNewObject->SetScale(sca);
	return pNewObject;
}

//キャラクターを作成するテンプレート
template <class T>
T* CharacterInstantiate(GameObject* pParent, std::string fileName)
{
	T* pNewObject = new T(pParent, fileName);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

//ステージを作成するテンプレート
template <class T>
T* StageInstantiate(GameObject* pParent, std::string fileName)
{
	T* pNewObject = new T(pParent, fileName);
	if (pParent != nullptr)
	{
		pParent->PushBackChild(pNewObject);
	}
	pNewObject->Initialize();
	return pNewObject;
}

