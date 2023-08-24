#pragma once
#include "Engine/SceneManager.h"
#include "ButtonManager.h"
#include "InstanceManager.h"

//imguiを管理するクラス
namespace Imgui_Obj
{
    //再設定の時に必要な情報
    struct SettingInfo
    {
        SettingInfo(GameObject* obj, std::string loadFileName, std::string sectionName, std::string writeFileName, XMFLOAT3 position, XMFLOAT3 rotate, XMFLOAT3 scale, int alpha = 255) :
            pObject_{ obj }, loadFileName_{ loadFileName }, sectionName_{ sectionName }, writeFile_{ writeFileName }, iniPosition_
            { position }, iniRotate_{ rotate }, iniScale_{ scale }, alpha_{ alpha } {}

        GameObject* pObject_;
        std::string loadFileName_;      //読み込むファイル名
        std::string sectionName_;       //セクションの名前 
        std::string writeFile_;         //保存をする際に書き込んだJSONのファイル名
        XMFLOAT3    iniPosition_;       //位置
        XMFLOAT3    iniRotate_;         //向き
        XMFLOAT3    iniScale_;          //拡大率
        int         alpha_;             //アルファ値 

    };

    //初期化
    void Initialize(SceneManager* pSceneManager_);

    //更新
    void Update();

    //開放
    void Release();

    /// <summary>
    /// Imguiの生成
    /// </summary>
    void InstantiateImgui();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw();

    /// <summary>
    /// オブジェクトを生成するImguiを出す関数
    /// </summary>
    void ImguiIniObj();
    
    /// <summary>
    /// シーンチェンジするImguiを生成する関数
    /// </summary>
    /// <param name="isPause">ポーズ画面かどうか</param>
    void SceneChangeImgui();

    /// <summary>
    /// imguiでボタンを生成した後にやること
    /// </summary>
    void RearButtonInstantiate();

    /// <summary>
    /// imguiで画像を生成した後にやること
    /// </summary>
    void RearImageInstantiate();
    
    //作ったボタンの再移動等を出来るようにする
    void ReSettingButton();

    /// <summary>
    /// ボタン作成モードの時に出すimgui
    /// </summary>
    void CreateButtonImgui();

    /// <summary>
    /// 画像作成モードの時に出すImgui(Beginの中で使う)
    /// </summary>
    void CreateImageImgui();

    /// <summary>
    /// 3Dオブジェクト作成モードの時に出すImgui(Beginの中で使う)
    /// </summary>
    void CreateObjectImgui();

    /// <summary>
    /// オブジェクトを生成する時に基本的なImguiを出す(Beginの中で使う)
    /// </summary>
    void SettingBasicImgui();

    /// <summary>
    /// デバッグログを表示するImguiを出す
    /// </summary>
    void CreateDebugLog();
    
    /// <summary>
    /// デバッグログを表示するリストに追加する
    /// </summary>
    /// <param name="obj">追加するオブジェクト</param>
    void AddDebugLogList(GameObject* obj);


    /// <summary>
    /// 拡張子を追加する関数(変数extensionを参照)
    /// </summary>
    /// <returns>返す拡張子</returns>
    std::string AddExtension();

    /// <summary>
    /// 作ったボタンのリストに入れる
    /// </summary>
    /// <param name="filename">ファイル名</param>
    /// <param name="section">セクション名</param>
    /// <param name="info">生成する時に必要な情報</param>
    /// <param name="button">入れるポインタ</param>
    void AddButtonList(std::string filename, std::string section, InstanceManager::CreateInfoJSON info, Button* button);

    /// <summary>
    /// 作った画像のリストに入れる
    /// </summary>
    /// <param name="filename">ファイル名</param>
    /// <param name="section">セクション名</param>
    /// <param name="info">生成する時に必要な情報</param>
    /// <param name="button">入れるポインタ</param>
    void AddImageList(std::string filename, std::string section, InstanceManager::CreateImageInfoJSON info, GameObject* image);

    /// <summary>
    /// 今あるリストをクリアする
    /// </summary>
    void ClearList();

    /// <summary>
    /// UIモードを選択するImguiを作成する
    /// </summary>
    void UISelectModeImgui();

    //modeUIのゲッター

    /// <summary>
    /// modeUIのゲッター
    /// </summary>
    /// <returns>modeUI</returns>
    int GetUIType();
    
    /// <summary>
    /// ファイルがあるか確認
    /// </summary>
    /// <param name="filename">調べるファイル名</param>
    /// <returns><returns>存在するかどうか</returns></returns>
    bool existFile(std::string filename);

    
};

//追加するボタンを増やす手順
//1 CreateButtonImguiの中のどんな種類のボタンを生成するかに追加
//2 生成ボタンに追加
//3 JsonOperator::ButtonToStringに追加(buttonStrList)
