#include "InstanceManager.h"
#include "Engine/JsonOperator.h"
#include "ChangeSceneButton.h"
#include "PlayerControlButton.h"
#include "ImageBase.h"
#include "Engine/JsonOperator.h"
#include "Imgui_Obj.h"

namespace InstanceManager
{
	//JSONを用いてオブジェクトを保存する（セクションをユニークにする）
	bool SaveButton(std::string filename, std::string& section, std::string pathName, std::string objectName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca)
	{
		
		CreateInfoJSON info =
		{
			pathName,
			objectName,
			pos,
			rot,
			sca
		};

		//ユニークなセクション名を作る
		std::string uniqueStr = section;
		if (!JsonOperator::CreateUniqueNameJSON(filename, uniqueStr))
		{
			return false;
		}

		//引数に作成したユニークな名前を入れる
		section = uniqueStr;

		//JSONにInstantiateに必要な情報を書き込む
		JsonOperator::WhiteCreateInfo(filename, uniqueStr, info);

		return true;
	}

	//JSONを用いてオブジェクトを上書き保存する（セクションをユニークにしない）
	bool OverWriteSaveButton(std::string filename, std::string section, std::string pathName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca)
	{
		std::string str;
		JsonOperator::GetJSONString(filename, section,JsonOperator::InstantiateKeyString[1], str);

		CreateInfoJSON info =
		{
			pathName,
			str,
			pos,
			rot,
			sca
		};

		//JSONにInstantiateに必要な情報を書き込む
		JsonOperator::WhiteCreateInfo(filename, section, info);

		return true;
	}

	//CreateInfoJSONの情報を基にボタンを作成する関数
	Button* CreateButtonOnInfo(InstanceManager::CreateInfoJSON info, GameObject* parent, std::string filename, std::string section)
	{
		Button* pResult = nullptr;
		
		//シーンチェンジボタンなら
		if (info.objectName == "sceneChangeButton")
		{
			//return InstantiateButton<ChangeSceneButton>(parent, info.loadFile, info.position, info.rotate, info.scale);
		}

		//プレイヤーコントロールボタンなら
		if (info.objectName == "playerControlButton")
		{			
			pResult = InstantiateButton<PlayerControlButton>(parent, info.loadFile, info.position, info.rotate, info.scale);
		}		

		//ボタンのリストにポインタを追加
		Imgui_Obj::AddButtonList(filename, section, info, pResult);

		return pResult;
	}

	//JSONを用いてボタン生成する（メンバーすべて）
	bool AllCreateButton(std::string filename, std::vector<GameObject*>& pButtonList, GameObject* parent)
	{
		std::vector<GameObject*>resultList;
		//ファイル読み込み
		Document data;
		if (!JsonOperator::LoadJSONFromFile(filename, data))
		{
			return false;
		}
		
		if (!data.IsObject())
		{
			return false;
		}

		//読み取る
		int i = 0;
		std::vector <InstanceManager::CreateInfoJSON> infoList;
		for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it)
		{
			std::string section = it->name.GetString();
			InstanceManager::CreateInfoJSON insInfo;
			JsonOperator::GetInstanceInfo(filename, section, insInfo);
			infoList.push_back(insInfo);

			//ボタンを作成してリストに入れる
			resultList.push_back(CreateButtonOnInfo(infoList[i], parent, filename, section));
			i++;
		}

		pButtonList = resultList;

		return true;
	}

	//JSONを用いてボタン生成する（メンバーすべて）
	bool AllCreateButton(std::string filename, GameObject* parent)
	{
		std::vector<GameObject*>resultList;
		//ファイル読み込み
		Document data;
		if (!JsonOperator::LoadJSONFromFile(filename, data))
		{
			return false;
		}

		if (!data.IsObject())
		{
			return false;
		}

		//読み取る
		int i = 0;
		std::vector <InstanceManager::CreateInfoJSON> infoList;
		for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it)
		{
			std::string section = it->name.GetString();
			InstanceManager::CreateInfoJSON insInfo;
			JsonOperator::GetInstanceInfo(filename, section, insInfo);
			infoList.push_back(insInfo);

			//ボタンを作成してリストに入れる
			resultList.push_back(CreateButtonOnInfo(infoList[i], parent, filename, section));
			i++;
		}

		return true;
	}

	// JSONを用いて画像を保存する（セクションをユニークにする）
	bool SaveImage(std::string filename, std::string& section, std::string pathName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, int alpha)
	{
		CreateImageInfoJSON info =
		{
			pathName,
			pos,
			rot,
			sca,
			alpha
		};

		//ユニークなセクション名を作る
		std::string uniqueStr = section;
		if (!JsonOperator::CreateUniqueNameJSON(filename, uniqueStr))
		{
			return false;
		}

		//引数に作成したユニークな名前を入れる
		section = uniqueStr;

		//JSONに画像をInstantiateに必要な情報を書き込む
		JsonOperator::WhiteCreateImageInfo(filename, section, info);

		return true;
	}

	// JSONを用いて画像を上書き保存する（セクションをユニークにしない）
	bool OverWriteSaveImage(std::string filename, std::string section, std::string pathName, XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 sca, int alpha)
	{
		CreateImageInfoJSON info =
		{
			pathName,
			pos,
			rot,
			sca,
			alpha
		};

		//JSONにInstantiateに必要な情報を書き込む
		JsonOperator::WhiteCreateImageInfo(filename, section, info);

		return true;
	}

	// CreateInfoJSONの情報を基に画像を作成する関数
	GameObject* CreateImageOnInfo(InstanceManager::CreateImageInfoJSON info, GameObject* parent, std::string filename, std::string section)
	{
		GameObject* pResult = InstantiateImage<ImageBase>(parent, info.loadFile, info.position, info.rotate, info.scale, info.alpha);
		Imgui_Obj::AddImageList(filename, section, info, pResult);
		return pResult;
	}

	//JSONを用いて画像を生成する（メンバーすべて）
	bool AllCreateImage(std::string filename, std::vector<GameObject*>& pImageList, GameObject* parent)
	{
		std::vector<GameObject*>resultList;
		//ファイル読み込み
		Document data;
		if (!JsonOperator::LoadJSONFromFile(filename, data))
		{
			return false;
		}

		if (!data.IsObject())
		{
			return false;
		}

		//読み取る
		int j = 0;
		std::vector <InstanceManager::CreateImageInfoJSON> infoList;
		for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it)
		{
			std::string section = it->name.GetString();
			InstanceManager::CreateImageInfoJSON insInfo;
			JsonOperator::GetCreateImageInfo(filename, section, insInfo);
			infoList.push_back(insInfo);

			//画像を作成してリストに入れる
			resultList.push_back(CreateImageOnInfo(infoList[j], parent, filename, section));
			j++;
		}

		pImageList = resultList;

		return true;
	}

	//JSONを用いて画像を生成する（メンバーすべて）
	bool AllCreateImage(std::string filename, GameObject* parent)
	{
		std::vector<GameObject*>resultList;
		//ファイル読み込み
		Document data;
		if (!JsonOperator::LoadJSONFromFile(filename, data))
		{
			return false;
		}

		if (!data.IsObject())
		{
			return false;
		}

		//読み取る
		int j = 0;
		std::vector <InstanceManager::CreateImageInfoJSON> infoList;
		for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it)
		{
			std::string section = it->name.GetString();
			InstanceManager::CreateImageInfoJSON insInfo;
			JsonOperator::GetCreateImageInfo(filename, section, insInfo);
			infoList.push_back(insInfo);

			//画像を作成してリストに入れる
			resultList.push_back(CreateImageOnInfo(infoList[j], parent, filename, section));
			j++;
		}

		return true;
	}
}