#include "JsonOperator.h"
#include <Windows.h>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream>
#include "../Json/rapidjson-master/include/rapidjson/stringbuffer.h"

using namespace rapidjson;

using std::string;
using std::vector;

namespace
{
    std::map<string, Document> dataList;
    // ("../Assets\\GameData\\TitleData.json");

}

namespace JsonOperator
{
    // 初期化
    void Initialize()
    {

    }

    //JSONファイルを読み込む関数
    bool LoadJSONFromFile(string filename, Document& document)
    {
        FILE* fp;
        if (fopen_s(&fp, filename.c_str(), "r") != 0)
        {
            MessageBox(NULL, "Load Error", "BaseProjDx9エラー", MB_OK);
        }

        // ファイルから読み込む
        char readBuffer[65536];
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        document.ParseStream(is);

        // ファイルを閉じる
        fclose(fp);

        // 読み込みが成功したかどうかを返す
        if (!document.HasParseError() && document.IsObject())
        {
            //配列に格納
            //dataList.insert(std::make_pair(filename, document));
            return true;
        }
        return false;
    }

    //ファイルの内容を文字列として読み込む
    bool LoadJSONString(std::string filename, std::string& str)
    {
        // JSONファイルを開く
        std::ifstream ifs(filename);
        if (!ifs) {
            return false;
        }

        // ファイルの内容を文字列として読み込む
        std::string jsonStr((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        str = jsonStr;
        ifs.close();
    }

    //JSONファイルを作成する関数
    bool CreateJSONFile(std::string filename)
    {
        // JSONオブジェクトを作成
        Document document;
        document.SetObject();

        // JSONファイルに書き出す
        std::ofstream ofs(filename);
        if (ofs) 
        {
            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            document.Accept(writer);
            ofs << buffer.GetString();
        }
        else 
        {
            return false;
        }
        return true;
    }

    //セッションを追加する関数
    bool AddSection(const std::string& filename, const std::string& section)
    {
        //ファイルの内容を文字列として読み込む
        std::string str = "";
        //失敗したらfalseを返す
        if (!LoadJSONString(filename, str))
        {
            return false;
        }

        // JSONデータをパースする
        // パース　データを解析し必要なデータを取り出すこと
        Document document;
        //失敗したらfalseを返す
        if (document.Parse(str.c_str()).HasParseError()) {
            return false;
        }

        // 新しい値を追加または上書きする
        if (!document.IsObject()) {
            return false;
        }

        // セクションを追加する
        Document::AllocatorType& allocator = document.GetAllocator();
        Value newValueObj(kObjectType);
        rapidjson::GenericStringRef<char> ref{ section.c_str() };
        document.AddMember(ref, newValueObj, allocator);

        // 更新されたJSONデータを文字列に変換する
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        document.Accept(writer);
        std::string updatedJsonStr = buffer.GetString();

        // JSONファイルを上書きする
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }

        ofs << updatedJsonStr;
        ofs.close();

        return true;
    }

    //JSONファイルの文字列を読み取る
    bool GetJSONString(std::string filename, std::string key, std::string& out)
    {
        Document data;
        //ファイルを開けなかったらfalseを返す
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //dataに読み取ったデータを入れる
        const char* name = "";
        if (data.HasMember(key.c_str()) && data[key.c_str()].IsString()) {
            name = data[key.c_str()].GetString();
            out = name;
            return true;
        }
        //失敗したらfalseを返す
        return false;
    }

    //JSONファイルの整数値を読み取る
    bool GetJSONInt(std::string filename, std::string key, int& out)
    {
        Document data;
        //ファイルを開けなかったらfalseを返す
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //dataに読み取ったデータを入れる
        int name = 0;
        if (data.HasMember(key.c_str()) && data[key.c_str()].IsInt()) {
            name = data[key.c_str()].GetInt();
            out = name;
            return true;
        }
        //失敗したらfalseを返す
        return false;
    }

    //JSONファイルの整数値を読み取る
    bool GetJSONFloat(std::string filename, std::string key, float& out)
    {
        Document data;
        //ファイルを開けなかったらfalseを返す
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //dataに読み取ったデータを入れる
        float name = 0.0f;
        if (data.HasMember(key.c_str()) && data[key.c_str()].IsFloat()) {
            name = data[key.c_str()].GetFloat();
            out = name;
            return true;
        }
        //失敗したらfalseを返す
        return false;
    }

    //JSONファイルの文字列を読み取る
    bool GetJSONString(std::string filename, std::string section, std::string key, std::string& out)
    {
        Document data;
        //ファイルを開けなかったらfalseを返す
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //dataに読み取ったデータを入れる
        const char* name = "";

        //引数のセッションがあるかどうか確認
        if (data.IsObject())
        {
            const Value& sectionData = data[section.c_str()];

            //引数のキーがあるかどうか確認
            if (sectionData.HasMember(key.c_str()) && sectionData[key.c_str()].IsString()) {

                //読み取ったデータを入れる
                name = sectionData[key.c_str()].GetString();
                out = name;
                return true;
            }
        }

        //失敗したらfalseを返す
        return false;
    }

    //JSONファイルの整数値を読み取る
    bool GetJSONInt(std::string filename, std::string section, std::string key, int& out)
    {
        Document data;
        //ファイルを開けなかったらfalseを返す
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //dataに読み取ったデータを入れる
        int name = 0.0f;

        //引数のセッションがあるかどうか確認
        if (data.IsObject())
        {
            const Value& sectionData = data[section.c_str()];

            //引数のキーがあるかどうか確認
            if (sectionData.HasMember(key.c_str()) && sectionData[key.c_str()].IsInt()) {

                //読み取ったデータを入れる
                name = sectionData[key.c_str()].GetInt();
                out = name;
                return true;
            }
        }
        //失敗したらfalseを返す
        return false;
    }

    //JSONファイルの整数値を読み取る
    bool GetJSONFloat(std::string filename, std::string section, std::string key, float& out)
    {
        Document data;
        //ファイルを開けなかったらfalseを返す
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //dataに読み取ったデータを入れる
        float name = 0.0f;

        //引数のセッションがあるかどうか確認
        if (data.IsObject())
        {
            const Value& sectionData = data[section.c_str()];

            //引数のキーがあるかどうか確認
            if (sectionData.HasMember(key.c_str()) && sectionData[key.c_str()].IsFloat()) {

                //読み取ったデータを入れる
                name = sectionData[key.c_str()].GetFloat();
                out = name;
                return true;
            }
        }

        //失敗したらfalseを返す
        return false;
    }

    //JSONファイルに書き込む
    bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const std::string& value)
    {
        // JSONオブジェクトを作成
        Document sectionDocument;
        sectionDocument.SetObject();

        // JSONにデータを追加
        Document::AllocatorType& allocator = sectionDocument.GetAllocator();

        Value keyDocument(kObjectType);
        rapidjson::GenericStringRef<char> ref{ key.c_str() };
        rapidjson::GenericStringRef<char> val{ value.c_str() };
        keyDocument.AddMember(ref, val, allocator);
        rapidjson::GenericStringRef<char> sec{ section.c_str() };
        sectionDocument.AddMember(sec, keyDocument, allocator);

        // JSONを文字列化する
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        sectionDocument.Accept(writer);

        // JSONをファイルに書き込む
        std::ofstream ofs(filename, std::ios::app);
        if (!ofs) {
            return false;
        }
        ofs << buffer.GetString();
        ofs.close();

        return true;
    }

    //JSONファイルに書き込む(上書き)
    bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const int& value)
    {
        // JSONオブジェクトを作成
        Document sectionDocument;
        sectionDocument.SetObject();

        // JSONにデータを追加
        Document::AllocatorType& allocator = sectionDocument.GetAllocator();

        Value keyDocument(kObjectType);
        rapidjson::GenericStringRef<char> ref{ key.c_str() };
        keyDocument.AddMember(ref, value, allocator);
        rapidjson::GenericStringRef<char> sec{ section.c_str() };
        sectionDocument.AddMember(sec, keyDocument, allocator);

        // JSONを文字列化する
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        sectionDocument.Accept(writer);

        // JSONをファイルに書き込む
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }
        ofs << buffer.GetString();
        ofs.close();

        return true;
    }

    //JSONファイルに書き込む(上書き)
    bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const float& value)
    {
        // JSONオブジェクトを作成
        Document sectionDocument;
        sectionDocument.SetObject();

        // JSONにデータを追加
        Document::AllocatorType& allocator = sectionDocument.GetAllocator();

        Value keyDocument(kObjectType);
        rapidjson::GenericStringRef<char> ref{ key.c_str() };
        keyDocument.AddMember(ref, value, allocator);
        rapidjson::GenericStringRef<char> sec{ section.c_str() };
        sectionDocument.AddMember(sec, keyDocument, allocator);

        // JSONを文字列化する
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        sectionDocument.Accept(writer);

        // JSONをファイルに書き込む
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }
        ofs << buffer.GetString();
        ofs.close();

        return true;
    }

    //JSONファイルに書き込む(追記、書き換え）
    bool AppendToJSONFileString(const std::string& filename, const std::string& section, const std::string& key, std::string value)
    {
        //ファイルの内容を文字列として読み込む
        std::string str = "";

        //fileNameのファイル名のファイルがなかったら
        std::ifstream file(filename);
        if (!file.good())
        {
            //ファイルを作る
            if (!CreateJSONFile(filename))
            {
                return false;          
            }  
        }

        //ファイル読み込み
        if (!LoadJSONString(filename, str))
        {
            return false;
        }

        // JSONデータをパースする
        // パース　データを解析し必要なデータを取り出すこと
        Document document;
        //失敗したらfalseを返す
        if (document.Parse(str.c_str()).HasParseError()) {
            return false;
        }

        // 新しい値を追加または上書きする
        if (!document.IsObject()) {
            return false;
        }

        //セクションがなかったら
        if (!document.HasMember(section.c_str()))
        {
            //セクションを追加
            if (!AddSection(filename, section))
            {
                return false;
            }
            else
            {
                //再度ロードする
                //失敗したらfalseを返す
                if (!LoadJSONString(filename, str))
                {
                    return false;
                }

                // JSONデータをパースする
                // パース　データを解析し必要なデータを取り出すこと
                //失敗したらfalseを返す
                if (document.Parse(str.c_str()).HasParseError())
                {
                    return false;
                }
            }
        }

        // オブジェクト内に既に同じキーが存在する場合は上書き、そうでない場合は追加する
        Document::AllocatorType& allocator = document.GetAllocator();
        if (document[section.c_str()].HasMember(key.c_str())) {
            rapidjson::GenericStringRef<char> val{ value.c_str() };
            document[section.c_str()][key.c_str()] = val;
        }
        else {
            rapidjson::GenericStringRef<char> sec{ key.c_str() };
            rapidjson::GenericStringRef<char> ref{ value.c_str() };
            Value newValueObj(ref);
            document[section.c_str()].AddMember(Value(sec, allocator).Move(), newValueObj, allocator);
        }

        // 更新されたJSONデータを文字列に変換する
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        document.Accept(writer);
        std::string updatedJsonStr = buffer.GetString();

        // JSONファイルを上書きする
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }

        ofs << updatedJsonStr;
        ofs.close();

        return true;
    }

    // JSONファイルに書き込む(追記、書き換え）
    bool AppendToJSONFileFloat(const std::string& filename, const std::string& section, const std::string& key, float value)
    {
        //ファイルの内容を文字列として読み込む
        std::string str = "";

        //fileNameのファイル名のファイルがなかったら
        std::ifstream file(filename);
        if (!file.good())
        {
            //ファイルを作る
            if (!CreateJSONFile(filename))
            {
                return false;
            }
        }

        //ファイル読み込み
        if (!LoadJSONString(filename, str))
        {
            return false;
        }

        // JSONデータをパースする
        // パース　データを解析し必要なデータを取り出すこと
        Document document;
        //失敗したらfalseを返す
        if (document.Parse(str.c_str()).HasParseError()) {
            return false;
        }

        // 新しい値を追加または上書きする
        if (!document.IsObject()) {
            return false;
        }

        //セクションがなかったら
        if (!document.HasMember(section.c_str()))
        {
            //セクションを追加
            if (!AddSection(filename, section))
            {
                return false;
            }
            else
            {
                //再度ロードする
                //失敗したらfalseを返す
                if (!LoadJSONString(filename, str))
                {
                    return false;
                }

                // JSONデータをパースする
                // パース　データを解析し必要なデータを取り出すこと
                //失敗したらfalseを返す
                if (document.Parse(str.c_str()).HasParseError()) 
                {
                    return false;
                }
            }
        }

        // オブジェクト内に既に同じキーが存在する場合は上書き、そうでない場合は追加する
        Document::AllocatorType& allocator = document.GetAllocator();
        if (document[section.c_str()].HasMember(key.c_str())) {
            document[section.c_str()][key.c_str()] = value;
        }
        else {
            Value newValueObj(value);
            document[section.c_str()].AddMember(Value(key.c_str(), allocator).Move(), newValueObj, allocator);
        }

        // 更新されたJSONデータを文字列に変換する
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        document.Accept(writer);
        std::string updatedJsonStr = buffer.GetString();

        // JSONファイルを上書きする
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }

        ofs << updatedJsonStr;
        ofs.close();

        return true;
    }

    //セクションのキーとセクションをすべて削除
    bool DeleteJSONSection(const std::string& filename, const std::string& section)
    {
        Document data;
        //ファイルを開けなかったらfalseを返す
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //セクションのメンバーを全て削除する
        if(data.HasMember(section.c_str()))
        {
            data.RemoveMember(section.c_str());
            data.EraseMember(section.c_str());
        }

        // 更新されたJSONデータを文字列に変換する
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        data.Accept(writer);
        std::string updatedJsonStr = buffer.GetString();

        // JSONファイルを上書きする
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }

        ofs << updatedJsonStr;
        ofs.close();

        return true;
    }

    // オブジェクトを生成するための情報をJSONから書き込む(書き換えあり)
    bool WhiteCreateInfo(const std::string& filename, const std::string& section, InstanceManager::CreateInfoJSON& info)
    {
        //文字列の情報
        std::string infoStr[InstanceManager::INFO_STR] =
        {
            info.loadFile,
            info.objectName
        };

        //数値の情報
        float infoFloat[InstanceManager::INFO_FLOAT] =
        {
            info.position.x,
            info.position.y,
            info.position.z,

            info.rotate.x,
            info.rotate.y,
            info.rotate.z,

            info.scale.x,
            info.scale.y,
            info.scale.z,
        };

       //文字列の書き込み
       for (auto i = 0; i < InstanceManager::INFO_STR; i++)
        {
           if (!AppendToJSONFileString(filename, section, InstantiateKeyString[i], infoStr[i]))
           {
               return false;
           }
        }

       //数値の書き込み
       for (auto i = 0; i < InstanceManager::INFO_FLOAT; i++)
       {
           if (!AppendToJSONFileFloat(filename, section, InstantiateKeyFloat[i], infoFloat[i]))
           {
               return false;
           }
       }

        return true;
    }

    //画像を生成するための情報をJSONから書き込む(書き換えあり)
    bool WhiteCreateImageInfo(const std::string& filename, const std::string& section, InstanceManager::CreateImageInfoJSON& info)
    {
        //文字列の情報
        std::string infoStr[InstanceManager::IMAGE_INFO_STR] =
        {
            info.loadFile,
        };

        //数値の情報
        float infoFloat[InstanceManager::IMAGE_INFO_FLOAT] =
        {
            info.position.x,
            info.position.y,
            info.position.z,

            info.rotate.x,
            info.rotate.y,
            info.rotate.z,

            info.scale.x,
            info.scale.y,
            info.scale.z,

            info.alpha
        };

        //文字列の書き込み
        for (auto i = 0; i < InstanceManager::IMAGE_INFO_STR; i++)
        {
            if (!AppendToJSONFileString(filename, section, InstantiateKeyString[i], infoStr[i]))
            {
                return false;
            }
        }

        //数値の書き込み
        for (auto i = 0; i < InstanceManager::IMAGE_INFO_FLOAT; i++)
        {
            if (!AppendToJSONFileFloat(filename, section, InstantiateKeyFloat[i], infoFloat[i]))
            {
                return false;
            }
        }

        return true;
    }

    //オブジェクトを生成するための情報をJSONから読み込む
    bool GetInstanceInfo(const std::string& filename, const std::string& section, InstanceManager::CreateInfoJSON& info)
    {
        //文字列の情報
        std::string infoStr[InstanceManager::INFO_STR] =
        {
            info.loadFile,
            info.objectName
        };

        //数値の情報
        float infoFloat[InstanceManager::INFO_FLOAT] =
        {
            info.position.x,
            info.position.y,
            info.position.z,

            info.rotate.x,
            info.rotate.y,
            info.rotate.z,

            info.scale.x,
            info.scale.y,
            info.scale.z,
        };


        //文字列の読み込み
        for (auto i = 0; i < InstanceManager::INFO_STR; i++)
        {
            if (!GetJSONString(filename, section, InstantiateKeyString[i], infoStr[i]))
            {
                return false;
            }
        }

        //数値の読み込み
        for (auto i = 0; i < InstanceManager::INFO_FLOAT; i++)
        {
            if (!GetJSONFloat(filename, section, InstantiateKeyFloat[i], infoFloat[i]))
            {
                return false;
            }
        }

        //返す構造体を作成
        InstanceManager::CreateInfoJSON result =
        {
            infoStr[0],
            infoStr[1],
            {infoFloat[0], infoFloat[1], infoFloat[2]},
            {infoFloat[3], infoFloat[4], infoFloat[5]},
            {infoFloat[6], infoFloat[7], infoFloat[8]}
        };

        info = result;
        return true;
    }

    //画像を生成するための情報をJSONから読み込む
    bool GetCreateImageInfo(const std::string& filename, const std::string& section, InstanceManager::CreateImageInfoJSON& info)
    {
        //文字列の情報
        std::string infoStr[InstanceManager::IMAGE_INFO_STR] =
        {
            info.loadFile,
        };

        //数値の情報
        float infoFloat[InstanceManager::IMAGE_INFO_FLOAT] =
        {
            info.position.x,
            info.position.y,
            info.position.z,

            info.rotate.x,
            info.rotate.y,
            info.rotate.z,

            info.scale.x,
            info.scale.y,
            info.scale.z,

            info.alpha
        };

        //文字列の読み込み
        for (auto i = 0; i < InstanceManager::IMAGE_INFO_STR; i++)
        {
            if (!GetJSONString(filename, section, InstantiateKeyString[i], infoStr[i]))
            {
                return false;
            }
        }

        //数値の読み込み
        for (auto i = 0; i < InstanceManager::IMAGE_INFO_FLOAT; i++)
        {
            if (!GetJSONFloat(filename, section, InstantiateKeyFloat[i], infoFloat[i]))
            {
                return false;
            }
        }

        //返す構造体を作成
        InstanceManager::CreateImageInfoJSON result =
        {
            infoStr[0],
            {infoFloat[0], infoFloat[1], infoFloat[2]},
            {infoFloat[3], infoFloat[4], infoFloat[5]},
            {infoFloat[6], infoFloat[7], infoFloat[8]},
            infoFloat[9]
        };

        info = result;

        return true;

    }

    //重複した文字列の後ろに数字をつけるプログラム
    bool CreateUniqueNameJSON(std::string filename, std::string& str)
    {
        // 既存のキーのカウントを保持するマップ
        std::map<std::string, int> keyCountMap;

        //fileNameのファイル名のファイルがなかったら
        std::ifstream file(filename);
        if (!file.good())
        {
            //ファイルを作る
            if (!CreateJSONFile(filename))
            {
                return false;
            }
        }

        Document data;
        //ファイルを開けなかったらfalseを返す
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        // JSONオブジェクト内の既存のキーをカウント
        for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it) {
            const std::string existingKey = it->name.GetString();
            keyCountMap[existingKey]++;
        }

        // 重複したキーがある場合、数字を付加してユニークなキーを作成
        std::string uniqueStr = str;
        int suffix = 1;
        while (keyCountMap.find(uniqueStr) != keyCountMap.end()) {
            uniqueStr = str + std::to_string(suffix);
            suffix++;
        }
        str = uniqueStr;
        return true;
    }

    // シーンを文字に変換
    std::string SceneToString(CanParentObj parent)
    {
        if (parentStrList.size() >= parent)
        {
            return parentStrList[parent];
        }
        return "";
    }

    //ボタンを文字に変換
    std::string ButtonToString(ButtonManager::ButtonKinds button)
    {
        if (buttonStrList.size() >= button)
        {
            return buttonStrList[button];
        }
        return "";
    }

    //文字をシーンに変換
    CanParentObj StringToParent(std::string parent)
    {
        for (int i = 0; i < parentStrList.size(); i++)
        {
            if (parentStrList[i] == parent)
            {
                return static_cast<CanParentObj>(i);
            }
        }

        return CanParentObj::MAX;
    }

    /// 文字をボタンに変換
    ButtonManager::ButtonKinds StringToButton(std::string button)
    {
        for (int i = 0; i < buttonStrList.size(); i++)
        {
            if (buttonStrList[i] == button)
            {
                return static_cast<ButtonManager::ButtonKinds>(i);
            }
        }
        return ButtonManager::ButtonKinds::BUTTON_KINDS_MAX;
    }
}
//// JSON配列の読み込みと処理
   //if (document.HasMember("numbers") && document["numbers"].IsArray()) {
   //    const Value& numbersArray = document["numbers"];
   //    for (SizeType i = 0; i < numbersArray.Size(); i++) {
   //        if (numbersArray[i].IsNumber()) {
   //            double number = numbersArray[i].GetDouble();
   //            std::cout << "Number at index " << i << ": " << number << std::endl;
   //        }
   //    }
   //}


      // // ファイルを開く
      // FILE* fp;
      // if (fopen_s(&fp, filename.c_str(), "r") != 0)
      // {
      //     MessageBox(NULL, "error", "BaseProjDx9エラー", MB_OK);
      // }
      // // ファイルから読み込む
      // string str;
      //// char readBuffer[65536];
      // FileReadStream is(fp, &str.front(), SHRT_MAX);
      // Document doc;
      // doc.ParseStream(is);
      // document.ParseStream(is);
      // dataList.insert(std::make_pair( list.at(filename), doc ));
      // // ファイルを閉じる
      // if(fp != nullptr)
      //// fclose(fp);
      // // 読み込みが成功したかどうかを返す
      // return !document.HasParseError() && document.IsObject();
       // ファイルを開く

//// JSONファイルに書き込む(追記、書き換え）
//bool AppendToJSONFileFloat(const std::string& filename, const std::string& section, const std::string& key, float value)
//{
//    //ファイルの内容を文字列として読み込む
//    std::string str = "";
//    //失敗したらfalseを返す
//    if (!LoadJSONString(filename, str))
//    {
//        return false;
//    }
//
//    // JSONデータをパースする
//    // パース　データを解析し必要なデータを取り出すこと
//    Document document;
//    //失敗したらfalseを返す
//    if (document.Parse(str.c_str()).HasParseError()) {
//        return false;
//    }
//
//    // 新しい値を追加または上書きする
//    if (!document.IsObject()) {
//        return false;
//    }
//
//    // オブジェクト内に既に同じキーが存在する場合は上書き、そうでない場合は追加する
//    Document::AllocatorType& allocator = document.GetAllocator();
//    if (document.HasMember(key.c_str())) {
//        document[key.c_str()] = value;
//    }
//    else {
//        Value newValueObj(value);
//        document.AddMember(Value(key.c_str(), allocator).Move(), newValueObj, allocator);
//    }
//
//    // 更新されたJSONデータを文字列に変換する
//    StringBuffer buffer;
//    Writer<StringBuffer> writer(buffer);
//    document.Accept(writer);
//    std::string updatedJsonStr = buffer.GetString();
//
//    // JSONファイルを上書きする
//    std::ofstream ofs(filename);
//    if (!ofs) {
//        return false;
//    }
//
//    ofs << updatedJsonStr;
//    ofs.close();
//
//    return true;
//}