#pragma once
#include <string>
#include <DirectXMath.h>
#include <vector>
#include "ButtonManager.h"
#include "Button.h"

using namespace DirectX;

class GameObject;
using std::string;

//JSONを用いてオブジェクトを作成する
namespace InstanceManager
{
	//生成する上で必要な情報の要素が何個あるか
	const int INFO_STR = 2;
	const int INFO_FLOAT = 9;

	//生成する上で必要な情報の要素が何個あるか(画像)
	const int IMAGE_INFO_STR = 1;
	const int IMAGE_INFO_FLOAT = 10;

	const std::string SUCCESS = "success";//成功したかどうかを判定する時に使う定数


	//JSONの情報でオブジェクトを作成するための構造体
	struct CreateInfoJSON
	{
		std::string loadFile;			//読み込む画像
		std::string objectName;			//どんなオブジェクトを生成するか
		///////////////////////////////////////////////////////////////////
		XMFLOAT3 position;				//位置
		XMFLOAT3 rotate;				//向き
		XMFLOAT3 scale;					//拡大率
	};

	//JSONの情報で画像作成するための構造体
	struct CreateImageInfoJSON
	{
		std::string loadFile;			//読み込む画像
		XMFLOAT3 position;				//位置
		XMFLOAT3 rotate;				//向き
		XMFLOAT3 scale;					//拡大率
		int alpha;
	};

	//////////////////////////////////ボタン////////////////////////////////////////////////////////////////////
	/// <summary>
	/// JSONを用いてボタンを保存する（セクションをユニークにする）
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="section">セクション名(参照渡し)</param>
	/// <param name="pathName">読み込むファイルの名前</param>
	/// <param name="objectName">作るボタンの種類</param>
	/// <param name="pos">位置</param>
	/// <param name="rot">向き</param>
	/// <param name="sca">拡大率</param>
	/// <returns>成功したかどうか</returns>
	bool SaveButton(std::string filename, std::string& section, std::string pathName, std::string objectName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca);

	/// <summary>
	/// JSONを用いてオブジェクトを上書き保存する（セクションをユニークにしない）
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="section">セクション名</param>
	/// <param name="pathName">読み込むファイルの名前</param>
	/// <param name="pos">位置</param>
	/// <param name="rot">向き</param>
	/// <param name="sca">拡大率</param>
	/// <returns></returns>
	bool OverWriteSaveButton(std::string filename, std::string section, std::string pathName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca);

	/// <summary>
	/// CreateInfoJSONの情報を基にボタンを作成する関数
	/// </summary>
	/// <param name="info">値を読み取る構造体</param>
	/// <param name="parent">親オブジェクト</param>
	/// <param name="filename">ファイル名</param>
	/// <param name="section">セクション名</param>
	/// <returns>作成したオブジェクトのポインタ</returns>
	Button* CreateButtonOnInfo(InstanceManager::CreateInfoJSON info, GameObject* parent, std::string filename, std::string section);

	/// <summary>
	/// JSONを用いてボタン生成する（メンバーすべて）
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="pButtonList">生成したボタンのポインタのリスト</param>
	/// <returns>成功したかどうか</returns>
	bool AllCreateButton(std::string filename, std::vector<GameObject*>& pButtonList, GameObject* parent);

	/// <summary>
	/// JSONを用いてボタン生成する（メンバーすべて）
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="parent">生成したボタンのポインタのリスト</param>
	/// <returns>成功したかどうか</returns>
	bool AllCreateButton(std::string filename, GameObject* parent);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////画像////////////////////////////////////////////////////////////////////

	/// <summary>
	/// JSONを用いて画像を保存する（セクションをユニークにする）
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="section">セクション名</param>
	/// <param name="pathName">ファイル名</param>
	/// <param name="pos">位置</param>
	/// <param name="rot">向き</param>
	/// <param name="sca">拡大率</param>
	/// <returns>成功したかどうか</returns>
	bool SaveImage(std::string filename, std::string& section, std::string pathName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, int alpha);

	/// <summary>
	/// JSONを用いて画像を上書き保存する（セクションをユニークにしない）
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="section">セクション名</param>
	/// <param name="pathName">読み込むファイルの名前</param>
	/// <param name="pos">位置</param>
	/// <param name="rot">向き</param>
	/// <param name="sca">拡大率</param>
	/// <param name="sca">アルファ値</param>
	/// <returns></returns>
	bool OverWriteSaveImage(std::string filename, std::string section, std::string pathName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, int alpha);
	
	/// <summary>
	/// CreateInfoJSONの情報を基にボタンを作成する関数
	/// </summary>
	/// <param name="info">値を入れる構造体</param>
	/// <param name="parent">親オブジェクト</param>
	/// <param name="filename">ファイル名</param>
	/// <param name="section">セクション名</param>
	/// <returns>作成したオブジェクトのポインタ</returns>
	GameObject* CreateImageOnInfo(InstanceManager::CreateImageInfoJSON info, GameObject* parent, std::string filename, std::string section);

	/// <summary>
	/// JSONを用いて画像を生成する（メンバーすべて）
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="pImageList">画像のリスト</param>
	/// <param name="parent">親オブジェクト</param>
	/// <returns>成功したかどうか</returns>
	bool AllCreateImage(std::string filename, std::vector<GameObject*>& pImageList, GameObject* parent);

	/// <summary>
	/// JSONを用いて画像を生成する（メンバーすべて）
	/// </summary>
	/// <param name="filename">ファイル名</param>
	/// <param name="parent">親オブジェクト</param>
	/// <returns>成功したかどうか</returns>
	bool AllCreateImage(std::string filename, GameObject* parent);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
};

