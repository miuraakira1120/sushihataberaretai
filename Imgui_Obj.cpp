#include "Imgui_Obj.h"
#include "imgui/imgui.h"
#include "Time.h"
#include "Engine/JsonOperator.h"

#include "Engine/GameObject.h"
#include "Maguro.h"
#include "Syari.h"
#include "Engine/Text.h"
#include "ChangeSceneButton.h"
#include "PlayerControlButton.h"
#include "Engine/SceneManager.h"
#include "Engine/Math.h"
#include "Engine/Input.h"

#include "Pause.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

#include "GameManager.h"
#include "ImageBase.h"

#include "EditScene.h"

#include <filesystem>
#include<Windows.h>

#include "Slider.h"

//何のクラスを作成するか
enum class IniType
{
    NONE,
    BUTTON,
    ENEMY,
    IMAGE,
    PLAYER,
    TYPE_MAX

};

namespace
{
    Text* pText;
    int gameTimerID;
    ChangeSceneButton* pChangeSceneButton;
    SceneManager* pSceneManager;

    int modeUI = static_cast<int>(UI_Type::NONE);//UI作成の時に使うどんなUIを作成するか決める
    int prevModeUI = static_cast<int>(UI_Type::NONE);//前フレームまでのmodeUI

    float changeSceneButtonX;
    float changeSceneButtonY;

    int iniListButton;//タイトルシーンのボタンの番号

    //使用するiniファイルの名前
    const std::string iniFileName = "UI.ini";
    const float DRAG_SPEED = 0.05f;//トランスフォームを調整するボタンの速度調整

    //char型の配列のサイズ(2の8乗)
    const int CHAR_SIZE = 256;

    //拡張子
    const int EXTENSION_PNG = 0;//png
    const int EXTENSION_JPG = 1;//jpg
    const int EXTENSION_FBX = 2;
    int extension = 0;
    

    //親を何にするか
    int parentNum;

    int buttonKinds = static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON);//ボタンの種類

    IniType iniType = IniType::NONE;

    int nextScene;                      //次に行くシーン
    bool isEditScene;                   //今、エディットシーンにいるかどうか

    int SceneChangeNextScene;           //SceneChangeの時に使う次に行くシーン

    std::string selectUniqueName;       //選択中のオブジェクトのユニークな名前
    
    GameObject* pSelectObj;             //選択中のオブジェクト
    std::string selectButtonKinds;      //選択中のオブジェクトの種類
    string selectLoadFileNameStr;       //選択中のオブジェクトが読み込む画像やモデルのファイル名
    char loadFileName[CHAR_SIZE] = "";  //選択中の読み込むファイル名
    char sectionName[CHAR_SIZE];        //選択中のセクションの名前 
    XMFLOAT3 iniPosition = { 0,0,0 };   //選択中の位置
    XMFLOAT3 iniScale = { 1,1,1 };      //選択中の拡大率
    XMFLOAT3 iniRotate = { 0,0,0 };     //選択中の向き
    std::string selectWriteFile;        //選択中のオブジェクトが保存をする際に書き込んだJSONのファイル名
    int selectAlpha = 255;              //選択中のアルファ
    bool canCreate = false;             //選択中のオブジェクトが生成できるか

    std::vector<Imgui_Obj::SettingInfo> settingInfoButtonList;//作ったボタンのリスト
    std::vector<Imgui_Obj::SettingInfo> settingInfoImageList; //作った画像のリスト

    std::vector<Imgui_Obj::SettingInfo> settingInfoButtonFromPauseList;//作ったボタンのリスト(ポーズ画面)
    std::vector<Imgui_Obj::SettingInfo> settingInfoImageFromPauseList; //作った画像のリスト(ポーズ画面)

    std::vector<GameObject*> debugLogList; //デバッグログを表示するオブジェクトのリスト
    
}

namespace Imgui_Obj
{
    //初期化
    void Initialize(SceneManager* pSceneManager_)
    {
        pText = new Text;
        pText->Initialize();
        pSceneManager = pSceneManager_;
    }

    //更新
    void Update()
    {
        pChangeSceneButton = (ChangeSceneButton*)pSceneManager->FindObject("ChangeSceneButton");

        //Imguiを生成する
        InstantiateImgui();
        
    }

    //開放
    void Release()
    {
        pText->Release();
    }

    //Imguiを生成する
    void InstantiateImgui()
    {
        //作成用のImguiを出す
        ImguiIniObj();

        //作ったオブジェクトの再設定を出来るようにする
        ReSettingButton();

        //楽にシーンチェンジ出来るようにする
        SceneChangeImgui();

        //デバッグログを表示するImguiを出す
        CreateDebugLog();

        //今エディットシーンにいたら
        if (pSceneManager->GetNowSceneID() == SCENE_ID::SCENE_ID_EDIT)
        {
            //UIモードを選択するImguiを作成する
            UISelectModeImgui();
        }

        ////タイトルシーンだったら
        //if (pSceneManager->GetNowSceneID() == SCENE_ID::SCENE_ID_START)
        //{
        //    ///////////////////////ボタンの位置////////////////////////////////////////

        //    ImGui::Begin("Botton Pos");
        //    //////////////////////スタートボタン/////////////////////////////////////////////////////

        //    static float testFloat;
        //    ImGui::InputFloat("x", &testFloat, -1, 1);

        //    if (ImGui::Button("MouseModeON"))
        //    {
        //        pChangeSceneButton->MouseModeON();
        //    }
        //    if (ImGui::Button("MouseModeOFF"))
        //    {
        //        pChangeSceneButton->MouseModeOFF();
        //    }

        //    ImGui::SliderFloat("ChangeSceneButtonX", &changeSceneButtonX, -1.0f, 1.0f);
        //    ImGui::SliderFloat("ChangeSceneButtonY", &changeSceneButtonY, -1.0f, 1.0f);

        //    //マウスモードならシリンダーで位置が変わらない変わらない
        //    if (!pChangeSceneButton->GetMouseMode())
        //    {
        //        //シリンダーいじるまでは変わらない
        //        if (!changeSceneButtonX == 0 || !changeSceneButtonY == 0)
        //        {
        //            //ボタンの位置を変える
        //            pChangeSceneButton->SetPosition(changeSceneButtonX, changeSceneButtonY, 0);
        //        }
        //    }
        //    else
        //    {
        //        //マウスモードかつボタンが選ばれてなおかつ左クリックが押されていたら
        //        if (pChangeSceneButton->GetValue() && Input::IsMouseButton(1))
        //        {
        //            pChangeSceneButton->SetPosition(Math::PixelToTransform(Input::GetMousePosition()));
        //        }
        //    }

        //    //ボタンの位置のセーブ
        //    if (ImGui::Button("PositionSave"))
        //    {
        //        JsonOperator::AppendToJSONFileFloat(JsonOperator::TITLE_JSON, "ChangeSceneButton", "posX", pChangeSceneButton->GetPosition().x);
        //        JsonOperator::AppendToJSONFileFloat(JsonOperator::TITLE_JSON, "ChangeSceneButton", "posY", pChangeSceneButton->GetPosition().y);
        //    }

        //    ImGui::End();
        //}
    }

    //描画
    void Draw()
    {
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }

    //オブジェクトを生成するImguiを出す関数
    void ImguiIniObj()
    {
        //Pause SettingのImguiを作成
        ImGui::Begin("Pause Setting");
        if (ImGui::TreeNode("Create"))
        {

            if (ImGui::Button("Button"))
            {
                iniType = IniType::BUTTON;
            }
            if (ImGui::Button("Image"))
            {
                iniType = IniType::IMAGE;
            }
            if (ImGui::Button("Enemy"))
            {
                iniType = IniType::ENEMY;
            }
            if (ImGui::Button("Player"))
            {
                iniType = IniType::PLAYER;
            }
            ImGui::TreePop();

            //ボタン作成モードなら
            if (iniType == IniType::BUTTON)
            {
                //ボタン作成モードの時に出すimgui
                CreateButtonImgui();
            }

            //画像作成モードなら
            if (iniType == IniType::IMAGE)
            {
                //画像作成モードの時に出すimgui
                CreateImageImgui();
            }

            //3Dオブジェクト作成モードの時に出すimgui
            if (iniType == IniType::PLAYER)
            {
                //3Dオブジェクト作成モードの時に出すImgui(Beginの中で使う)
                CreateObjectImgui();
            }
        }
        ImGui::End();
    }

    //シーンチェンジするImguiを生成する関数
    void SceneChangeImgui()
    {
        ImGui::Begin("Scene Change");
        ImGui::RadioButton("Title", &nextScene, static_cast<int>(SCENE_ID::SCENE_ID_START)); ImGui::SameLine();
        ImGui::RadioButton("Play", &nextScene, static_cast<int>(SCENE_ID::SCENE_ID_PLAY));
        ImGui::RadioButton("Goal", &nextScene, static_cast<int>(SCENE_ID::SCENE_ID_GOAL)); ImGui::SameLine();
        ImGui::RadioButton("GameOver", &nextScene, static_cast<int>(SCENE_ID::SCENE_ID_GAMEOVER));
        ImGui::RadioButton("Edit", &nextScene, static_cast<int>(SCENE_ID::SCENE_ID_EDIT));
        ImGui::RadioButton("Tutorial", &nextScene, static_cast<int>(SCENE_ID::SCENE_ID_TUTORIAL));

        if (ImGui::Button("Scene Change"))
        {
            //もしもエディットシーンに行く予定なら
            if (nextScene == SCENE_ID::SCENE_ID_EDIT)
            {
                isEditScene = true;
            }
            else
            {
                isEditScene = false;
            }
            
            pSceneManager->ChangeScene(static_cast<SCENE_ID>(nextScene));
        }
        ImGui::End();
    }

    //imguiでボタンを保存した後にやること
    void RearButtonInstantiate()
    {
        SettingInfo setting{ pSelectObj, selectLoadFileNameStr, selectUniqueName , selectWriteFile,iniPosition, iniRotate, iniScale };
        settingInfoButtonList.push_back(setting);
        pSelectObj = nullptr;
    }

    // imguiで画像を生成した後にやること
    void RearImageInstantiate()
    {
        SettingInfo setting{ pSelectObj, selectLoadFileNameStr, selectUniqueName , selectWriteFile,iniPosition, iniRotate, iniScale, selectAlpha };
        settingInfoImageList.push_back(setting);
        pSelectObj = nullptr;
    }

    //作ったボタンの再移動等を出来るようにする
    void ReSettingButton()
    {
        ImGui::Begin("CreateList");

        //ボタン
        if (ImGui::TreeNode("Button"))
        {
            //pCreateListの分だけ回す
            for (int i = 0; i < settingInfoButtonList.size(); i++)
            {
                if (ImGui::TreeNode(settingInfoButtonList[i].sectionName_.c_str()))
                {
                    //読み込むファイル名を入力
                    ImGui::Text("LoadFileName");
                    //string型をChar型に変換
                    char sec[CHAR_SIZE];
                    settingInfoButtonList[i].loadFileName_.copy(sec, CHAR_SIZE - 1);
                    sec[settingInfoButtonList[i].loadFileName_.length()] = '\0';

                    //読み込むInputTextを表示
                    ImGui::InputText("LoadFile", sec, CHAR_SIZE);
                    settingInfoButtonList[i].loadFileName_ = sec;

                    std::filesystem::directory_entry dir;
                    dir.assign(settingInfoButtonList[i].loadFileName_);

                    //指定したファイルが存在するか
                    canCreate = dir.exists();
                    if (!canCreate)
                    {
                        ImGui::Text("file doesn't exist");
                    }
                    else
                    {
                        //決定ボタンを表示
                        if (ImGui::Button("Decision"))
                        {
                            settingInfoButtonList[i].pObject_->SetPathName(settingInfoButtonList[i].loadFileName_);
                        }
                    }

                    //Transfomの情報を入力
                    ImGui::Text("Transform");
                    //位置
                    float* iniPositionArrayTmp[3] = { &settingInfoButtonList[i].iniPosition_.x, &settingInfoButtonList[i].iniPosition_.y, &settingInfoButtonList[i].iniPosition_.z };
                    ImGui::DragFloat3("Position", iniPositionArrayTmp[0], DRAG_SPEED, -1.0f, 1.0f);
                    settingInfoButtonList[i].pObject_->SetPosition(settingInfoButtonList[i].iniPosition_);

                    //向き
                    float* iniRotateArrayTmp[3] = { &settingInfoButtonList[i].iniRotate_.x,&settingInfoButtonList[i].iniRotate_.y, &settingInfoButtonList[i].iniRotate_.z };
                    ImGui::DragFloat3("Rotate", iniRotateArrayTmp[0], DRAG_SPEED, -1.0f, 1.0f);
                    settingInfoButtonList[i].pObject_->SetRotate(settingInfoButtonList[i].iniRotate_);

                    //拡大率
                    float* iniScaleArrayTmp[3] = { &settingInfoButtonList[i].iniScale_.x,&settingInfoButtonList[i].iniScale_.y, &settingInfoButtonList[i].iniScale_.z };
                    ImGui::DragFloat3("Scale", iniScaleArrayTmp[0], DRAG_SPEED, 0.0f, 100.0f);
                    settingInfoButtonList[i].pObject_->SetScale(settingInfoButtonList[i].iniScale_);

                    //保存
                    if (ImGui::Button("Save"))
                    {
                        InstanceManager::OverWriteSaveButton(
                            settingInfoButtonList[i].writeFile_,
                            settingInfoButtonList[i].sectionName_,
                            settingInfoButtonList[i].loadFileName_,
                            settingInfoButtonList[i].iniPosition_,
                            settingInfoButtonList[i].iniRotate_,
                            settingInfoButtonList[i].iniScale_);
                    }

                    //削除
                    if (ImGui::Button("Delete"))
                    {
                        //オブジェクトを削除
                        settingInfoButtonList[i].pObject_->KillMe();

                        //そのセクションの中身消す
                        JsonOperator::DeleteJSONSection(settingInfoButtonList[i].writeFile_, settingInfoButtonList[i].sectionName_);
                         
                        //リストのポインタも消す
                        settingInfoButtonList.erase(settingInfoButtonList.begin() + i);
                    }
                    ImGui::TreePop();
                }               
            }
            ImGui::TreePop();
        }

        //画像
        if (ImGui::TreeNode("Image"))
        {
            //pCreateListの分だけ回す
            for (int i = 0; i < settingInfoImageList.size(); i++)
            {
                if (ImGui::TreeNode(settingInfoImageList[i].sectionName_.c_str()))
                {
                    //読み込むファイル名を入力
                    ImGui::Text("LoadFileName");
                    //string型をChar型に変換
                    char sec[CHAR_SIZE];
                    settingInfoImageList[i].loadFileName_.copy(sec, CHAR_SIZE - 1);
                    sec[settingInfoImageList[i].loadFileName_.length()] = '\0';

                    //読み込むInputTextを表示
                    ImGui::InputText("LoadFile", sec, CHAR_SIZE);
                    settingInfoImageList[i].loadFileName_ = sec;

                    std::filesystem::directory_entry dir;
                    dir.assign(settingInfoImageList[i].loadFileName_);

                    //指定したファイルが存在するか
                    canCreate = dir.exists();
                    if (!canCreate)
                    {
                        ImGui::Text("file doesn't exist");
                    }
                    else
                    {
                        //決定ボタンを表示
                        if (ImGui::Button("Decision"))
                        {
                            settingInfoImageList[i].pObject_->SetPathName(settingInfoImageList[i].loadFileName_);
                        }
                    }

                    //Transfomの情報を入力
                    ImGui::Text("Transform");
                    //位置
                    float* iniPositionArrayTmp[3] = { &settingInfoImageList[i].iniPosition_.x, &settingInfoImageList[i].iniPosition_.y, &settingInfoImageList[i].iniPosition_.z };
                    ImGui::DragFloat3("Position", iniPositionArrayTmp[0], DRAG_SPEED, -1.0f, 1.0f);
                    settingInfoImageList[i].pObject_->SetPosition(settingInfoImageList[i].iniPosition_);

                    //向き
                    float* iniRotateArrayTmp[3] = { &settingInfoImageList[i].iniRotate_.x,&settingInfoImageList[i].iniRotate_.y, &settingInfoImageList[i].iniRotate_.z };
                    ImGui::DragFloat3("Rotate", iniRotateArrayTmp[0], DRAG_SPEED, -1.0f, 1.0f);
                    settingInfoImageList[i].pObject_->SetRotate(settingInfoImageList[i].iniRotate_);

                    //拡大率
                    float* iniScaleArrayTmp[3] = { &settingInfoImageList[i].iniScale_.x,&settingInfoImageList[i].iniScale_.y, &settingInfoImageList[i].iniScale_.z };
                    ImGui::DragFloat3("Scale", iniScaleArrayTmp[0], DRAG_SPEED, 0.0f, 100.0f);
                    settingInfoImageList[i].pObject_->SetScale(settingInfoImageList[i].iniScale_);

                    //アルファ値を変える
                    ImGui::DragInt("alpha", &settingInfoImageList[i].alpha_, 1, 0, 255);
                    settingInfoImageList[i].pObject_->SetAlpha(settingInfoImageList[i].alpha_);

                    //保存
                    if (ImGui::Button("Save"))
                    {
                        InstanceManager::OverWriteSaveImage(
                            settingInfoImageList[i].writeFile_,
                            settingInfoImageList[i].sectionName_,
                            settingInfoImageList[i].loadFileName_,
                            settingInfoImageList[i].iniPosition_,
                            settingInfoImageList[i].iniRotate_,
                            settingInfoImageList[i].iniScale_,
                            settingInfoImageList[i].alpha_);
                    }

                    //削除
                    if (ImGui::Button("Delete"))
                    {
                        //オブジェクトを削除
                        settingInfoImageList[i].pObject_->KillMe();

                        //そのセクションの中身消す
                        JsonOperator::DeleteJSONSection(settingInfoImageList[i].writeFile_, settingInfoImageList[i].sectionName_);

                        //リストのポインタも消す
                        settingInfoImageList.erase(settingInfoImageList.begin() + i);
                    }
                    ImGui::TreePop();
                }

                
            }
            ImGui::TreePop();
        }

        ImGui::End();
    }

    //ボタン作成モードの時に出すimgui
    void CreateButtonImgui()
    {
        ImGui::Begin("Create Button");

        // オブジェクトを生成する時に基本的なImguiを出す(Beginの中で使う)
        SettingBasicImgui();

        //どんな種類のボタンを生成するか
        ImGui::Text("ButtonType");
        //ImGui::RadioButton("SceneChange", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON)); ImGui::SameLine();
        ImGui::RadioButton("PlayerControl", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON));
        ImGui::RadioButton("Slinder", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::SLIDER));

        //シーンチェンジボタンを作成する予定なら
        if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON))
        {
            ImGui::Text("NextScene");
            ImGui::RadioButton("Title", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_START)); ImGui::SameLine();
            ImGui::RadioButton("Play", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_PLAY));
            ImGui::RadioButton("GameOver", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_GAMEOVER)); ImGui::SameLine();
            ImGui::RadioButton("Clear", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_GOAL));
        }

        //生成ボタン
        if (canCreate && ImGui::Button("Create"))
        {       
            //拡張子を追加
            selectLoadFileNameStr = std::string(loadFileName) + AddExtension();

            //保存していないオブジェクトは消す
            if (pSelectObj != nullptr)
            {
                pSelectObj->KillMe();
            }

            //プレイヤーのボタン配置を変えるボタンを作成するなら
            if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON))
            {       
                //ボタンの種類
                selectButtonKinds = JsonOperator::ButtonToString(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON);

                //オブジェクトを作成しポインタを保存しておく
                pSelectObj = InstantiateButton<PlayerControlButton>(pSceneManager->GetNowScenePointer(), selectLoadFileNameStr, iniPosition, iniRotate, iniScale);
            }

            //スライダーを作成するなら
            if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::SLIDER))
            {
                //ボタンの種類
                selectButtonKinds = JsonOperator::ButtonToString(ButtonManager::ButtonKinds::SLIDER);

                //オブジェクトを作成しポインタを保存しておく
                pSelectObj = InstantiateButton<Slider>(pSceneManager->GetNowScenePointer(), selectLoadFileNameStr, iniPosition, iniRotate, iniScale);
            }
        }

        if (pSelectObj != nullptr)
        {
            ImGui::SameLine();
            //セーブボタン
            if (ImGui::Button("Save"))
            {
                //親が今のシーンなら
                if (parentNum == static_cast<int>(GameManager::ParentNum::NOW_SCENE))
                {
                    //タイトルシーンだったら
                    switch (pSceneManager->GetNowSceneID())
                    {
                        //タイトルシーンだったら
                    case SCENE_ID::SCENE_ID_START:
                        InstanceManager::SaveButton(JsonOperator::TITLE_BUTTON_JSON, selectUniqueName, selectLoadFileNameStr, selectButtonKinds, iniPosition, iniRotate, iniScale);
                        break;
                    default:
                        break;
                    }
                }
                //ポーズだったら
                else if (parentNum == static_cast<int>(GameManager::ParentNum::PAUSE))
                {
                    //保存する
                    InstanceManager::SaveButton(JsonOperator::PAUSE_BUTTON_JSON, selectUniqueName, selectLoadFileNameStr, selectButtonKinds, iniPosition, iniRotate, iniScale);
                }

                //imguiでボタンを保存した後にやること
                RearButtonInstantiate();
            }ImGui::SameLine();

            //削除ボタン
            if (ImGui::Button("Delete"))
            {
                pSelectObj->KillMe();
                pSelectObj = nullptr;
            }
        }

        //キャンセルボタン
        if (ImGui::Button("Cancel"))
        {

            iniType = IniType::NONE;
        }
        ImGui::End();
    }

    //画像作成モードの時に出すImgui
    void CreateImageImgui()
    {
        //imguiを生成
        ImGui::Begin("Create Image");

        // オブジェクトを生成する時に基本的なImguiを出す(Beginの中で使う)
        SettingBasicImgui();

        //生成ボタン
        if (canCreate && ImGui::Button("Create"))
        {
            //拡張子を追加
            selectLoadFileNameStr = std::string(loadFileName) + AddExtension();

            //保存していないオブジェクトは消す
            if (pSelectObj != nullptr)
            {
                pSelectObj->KillMe();
            }

            //オブジェクトを作成しポインタを保存しておく
            pSelectObj = InstantiateImage<ImageBase>(pSceneManager->GetNowScenePointer(), selectLoadFileNameStr, iniPosition, iniRotate, iniScale, selectAlpha);
        }

        //オブジェクトを作っていたら
        if (pSelectObj != nullptr)
        {
            ImGui::SameLine();
            //セーブボタン
            if (ImGui::Button("Save"))
            {
                //親が今のシーンなら
                if (parentNum == static_cast<int>(GameManager::ParentNum::NOW_SCENE))
                {
                    switch (pSceneManager->GetNowSceneID())
                    {
                        //タイトルシーンだったら
                    case SCENE_ID::SCENE_ID_START:
                        //保存する
                        InstanceManager::SaveImage(JsonOperator::TITLE_IMAGE_JSON, selectUniqueName, selectLoadFileNameStr, iniPosition, iniRotate, iniScale, selectAlpha);
                        break;

                    default:
                        break;
                    }
                }
                //ポーズだったら
                else if (parentNum == static_cast<int>(GameManager::ParentNum::PAUSE))
                {
                    //保存する
                    InstanceManager::SaveImage(JsonOperator::PAUSE_IMAGE_JSON, selectUniqueName, selectLoadFileNameStr, iniPosition, iniRotate, iniScale, selectAlpha);
                }

                //imguiで画像を保存した後にやること
                RearImageInstantiate();
            }ImGui::SameLine();

            //削除ボタン
            if (ImGui::Button("Delete"))
            {
                pSelectObj->KillMe();
                pSelectObj = nullptr;
            }
        }

        //キャンセルボタン
        if (ImGui::Button("Cancel"))
        {

            iniType = IniType::NONE;
        }
        ImGui::End();
    }

    //3Dオブジェクト作成モードの時に出すImgui(Beginの中で使う)
    void CreateObjectImgui()
    {
        ImGui::Begin("Create Button");

        // オブジェクトを生成する時に基本的なImguiを出す(Beginの中で使う)
        SettingBasicImgui();

        //どんな種類のボタンを生成するか
        ImGui::Text("ButtonType");
        //ImGui::RadioButton("SceneChange", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON)); ImGui::SameLine();
        ImGui::RadioButton("PlayerControl", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON));
        ImGui::RadioButton("Slinder", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::SLIDER));

        //シーンチェンジボタンを作成する予定なら
        if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON))
        {
            ImGui::Text("NextScene");
            ImGui::RadioButton("Title", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_START)); ImGui::SameLine();
            ImGui::RadioButton("Play", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_PLAY));
            ImGui::RadioButton("GameOver", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_GAMEOVER)); ImGui::SameLine();
            ImGui::RadioButton("Clear", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_GOAL));
        }

        //生成ボタン
        if (canCreate && ImGui::Button("Create"))
        {
            selectButtonKinds = JsonOperator::ButtonToString(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON);

            //拡張子を追加
            selectLoadFileNameStr = std::string(loadFileName) + AddExtension();

            //保存していないオブジェクトは消す
            if (pSelectObj != nullptr)
            {
                pSelectObj->KillMe();
            }

            //プレイヤーのボタン配置を変えるボタンを作成するなら
            if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON))
            {
                //オブジェクトを作成しポインタを保存しておく
                pSelectObj = InstantiateButton<PlayerControlButton>(pSceneManager->GetNowScenePointer(), selectLoadFileNameStr, iniPosition, iniRotate, iniScale);
            }
            //スライダーを作成するなら
            if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON))
            {
                //オブジェクトを作成しポインタを保存しておく
                pSelectObj = InstantiateButton<PlayerControlButton>(pSceneManager->GetNowScenePointer(), selectLoadFileNameStr, iniPosition, iniRotate, iniScale);
            }
        }

        if (pSelectObj != nullptr)
        {
            ImGui::SameLine();
            //セーブボタン
            if (ImGui::Button("Save"))
            {
                //親が今のシーンなら
                if (parentNum == static_cast<int>(GameManager::ParentNum::NOW_SCENE))
                {
                    //タイトルシーンだったら
                    switch (pSceneManager->GetNowSceneID())
                    {
                        //タイトルシーンだったら
                    case SCENE_ID::SCENE_ID_START:
                        InstanceManager::SaveButton(JsonOperator::TITLE_BUTTON_JSON, selectUniqueName, selectLoadFileNameStr, selectButtonKinds, iniPosition, iniRotate, iniScale);
                        break;
                    default:
                        break;
                    }
                }
                //ポーズだったら
                else if (parentNum == static_cast<int>(GameManager::ParentNum::PAUSE))
                {
                    //保存する
                    InstanceManager::SaveButton(JsonOperator::PAUSE_BUTTON_JSON, selectUniqueName, selectLoadFileNameStr, selectButtonKinds, iniPosition, iniRotate, iniScale);
                }

                //imguiでボタンを保存した後にやること
                RearButtonInstantiate();
            }ImGui::SameLine();

            //削除ボタン
            if (ImGui::Button("Delete"))
            {
                pSelectObj->KillMe();
                pSelectObj = nullptr;
            }
        }

        //キャンセルボタン
        if (ImGui::Button("Cancel"))
        {

            iniType = IniType::NONE;
        }
        ImGui::End();
    }
    

    //Transformをいじるimguiを出す
    void TransformImgui()
    {
        //Transfomの情報を入力
        ImGui::Text("Transform");

        //位置
        //参照で生成
        float* iniPositionArray[3] = { &iniPosition.x, &iniPosition.y, &iniPosition.z };
        ImGui::DragFloat3("Position", iniPositionArray[0], DRAG_SPEED, -1.0f, 1.0f);
        
        //向き
        float* iniRotateArray[3] = { &iniRotate.x,&iniRotate.y, &iniRotate.z };
        ImGui::DragFloat3("Rotate", iniRotateArray[0], DRAG_SPEED, -1.0f, 1.0f);
           
        //拡大率
        float* iniScaleArray[3] = { &iniScale.x,&iniScale.y, &iniScale.z };
        ImGui::DragFloat3("Scale", iniScaleArray[0], DRAG_SPEED, -1.0f, 1.0f);           

        //アルファ値を変える
        ImGui::DragInt("alpha", &selectAlpha, 1, 0, 255);         

        if (pSelectObj != nullptr)
        {
            pSelectObj->SetPosition(iniPosition);
            pSelectObj->SetRotate(iniRotate);
            pSelectObj->SetScale(iniScale);
            pSelectObj->SetAlpha(selectAlpha);
        }
    }

    //オブジェクトを生成する時に基本的なImguiを出す
    void SettingBasicImgui()
    {      
        //セクション名
        ImGui::Text("ObjectName");
        ImGui::InputText("name", sectionName, CHAR_SIZE);
        selectUniqueName = sectionName;

        ImGui::NewLine();

        //読み込むファイル名を入力
        ImGui::Text("LoadFileName");

        std::string filename = AddExtension();
        ImGui::InputText(filename.c_str(), loadFileName, CHAR_SIZE);
        ImGui::RadioButton("png", &extension, EXTENSION_PNG); ImGui::SameLine();
        ImGui::RadioButton("jpg", &extension, EXTENSION_JPG); ImGui::SameLine();
        ImGui::RadioButton("fbx", &extension, EXTENSION_FBX); 

        //ファイル名+拡張子にする
        std::string f = loadFileName + filename;

        //ファイルがあるか確認
        canCreate = existFile(f);
        if (!canCreate)
        {
            ImGui::Text("file doesn't exist");
        }
        else
        {
            ImGui::Text("file exist");
        }

        ImGui::NewLine();

        //Transformをいじるimguiを出す
        TransformImgui();

        ImGui::NewLine();

        //親オブジェクトは何か(どこで生成するか)
        ImGui::Text("Parent");

        //エディットシーンじゃなかったら
        if (!isEditScene)
        {
            ImGui::RadioButton("NowScene", &parentNum, static_cast<int>(GameManager::ParentNum::NOW_SCENE)); ImGui::SameLine();
        }        
        else
        {
            ImGui::RadioButton("Pause", &parentNum, static_cast<int>(GameManager::ParentNum::PAUSE));
        }
        ImGui::NewLine();

    }

    //デバッグログを表示するImguiを出す
    void CreateDebugLog()
    {
        ImGui::Begin("Debug Log");

        for (int i = 0; i < debugLogList.size(); i++)
        {
            ImGui::Text("Position");
            ImGui::Text("%f", debugLogList[i]->GetPosition().x);
            ImGui::Text("%f", debugLogList[i]->GetPosition().y);
            ImGui::Text("%f", debugLogList[i]->GetPosition().z);
        }


        ImGui::End();
    }

    //デバッグログを表示するリストに追加する
    void AddDebugLogList(GameObject* obj)
    {
        debugLogList.push_back(obj);
    }

    // 拡張子を追加する関数(変数extensionを参照)
    std::string AddExtension()
    {
        switch (extension)
        {
        case EXTENSION_PNG :
            return ".png";
        case EXTENSION_JPG:
            return ".jpg";
        case EXTENSION_FBX:
            return ".fbx";
        default:
            return "";
            break;
        }
    }

    //作ったボタンのリストに入れる
    void AddButtonList(std::string filename, std::string section, InstanceManager::CreateInfoJSON info, Button* button)
    {
        SettingInfo SetInfo((GameObject*)button, info.loadFile, section, filename, info.position, info.rotate, info.scale);
        settingInfoButtonList.push_back(SetInfo);
    }

    //作った画像のリストに入れる
    void AddImageList(std::string filename, std::string section, InstanceManager::CreateImageInfoJSON info, GameObject* image)
    {
        SettingInfo SetInfo(image, info.loadFile, section, filename, info.position, info.rotate, info.scale, info.alpha);
        settingInfoImageList.push_back(SetInfo);
    }

    //今あるリストをクリアする
    void ClearList()
    {
        //リストを消す
        settingInfoButtonFromPauseList.clear();
        settingInfoImageFromPauseList.clear();
        settingInfoButtonList.clear();
        settingInfoImageList.clear();
        debugLogList.clear();
    }

    //UIモードを選択するImguiを作成する
    void UISelectModeImgui()
    {
        ImGui::Begin("UI_TYPE");

        //ラジオボタン作成
        ImGui::RadioButton("NONE", &modeUI, static_cast<int>(UI_Type::NONE)); ImGui::SameLine();
        ImGui::RadioButton("PAUSE", &modeUI, static_cast<int>(UI_Type::PAUSE)); 

        //前フレームと作成するUIが違ったら
        if (modeUI != prevModeUI)
        {
            //リストを消す
            ClearList();
        }

        prevModeUI = modeUI;
        ImGui::End();
    }

    // modeUIのゲッター
    int GetUIType()
    {
        return modeUI;
    }

    // ファイルがあるか確認
    bool existFile(std::string filename)
    {
        std::string fullFilename = "";
        //作成タイプによって探すディレクトリを変える
        switch (iniType)
        {
        case IniType::NONE:
            break;
        case IniType::BUTTON:
            fullFilename += Image::DIRECTORY_BUTTON;
            break;
        case IniType::ENEMY:
            break;
        case IniType::IMAGE:
            fullFilename += Image::DIRECTORY_UI;
            break;
        case IniType::TYPE_MAX:
            break;
        default:
            break;
        }
        fullFilename += filename;
        std::filesystem::directory_entry dir;
        dir.assign(fullFilename);

        //指定したファイルが存在するか
        return dir.exists();
    }
}



//TREENODE
//TreePop

//
//ImGui::Begin("Test Window");
//
//ImGui::Text("Hello, world %d", 123);
//
////if (ImGui::Button("オブジェクトを追加")) 
////{
////    printf("Button\n");
////}
//
//static char buf[256] = "";
//if (ImGui::InputText("string", buf, 256)) {
//    printf("InputText\n");
//}
//
//static float f = 0.0f;
//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
