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

//���̃N���X���쐬���邩
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

    int modeUI = static_cast<int>(UI_Type::NONE);//UI�쐬�̎��Ɏg���ǂ��UI���쐬���邩���߂�
    int prevModeUI = static_cast<int>(UI_Type::NONE);//�O�t���[���܂ł�modeUI

    float changeSceneButtonX;
    float changeSceneButtonY;

    int iniListButton;//�^�C�g���V�[���̃{�^���̔ԍ�

    //�g�p����ini�t�@�C���̖��O
    const std::string iniFileName = "UI.ini";
    const float DRAG_SPEED = 0.05f;//�g�����X�t�H�[���𒲐�����{�^���̑��x����

    //char�^�̔z��̃T�C�Y(2��8��)
    const int CHAR_SIZE = 256;

    //�g���q
    const int EXTENSION_PNG = 0;//png
    const int EXTENSION_JPG = 1;//jpg
    const int EXTENSION_FBX = 2;
    int extension = 0;
    

    //�e�����ɂ��邩
    int parentNum;

    int buttonKinds = static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON);//�{�^���̎��

    IniType iniType = IniType::NONE;

    int nextScene;                      //���ɍs���V�[��
    bool isEditScene;                   //���A�G�f�B�b�g�V�[���ɂ��邩�ǂ���

    int SceneChangeNextScene;           //SceneChange�̎��Ɏg�����ɍs���V�[��

    std::string selectUniqueName;       //�I�𒆂̃I�u�W�F�N�g�̃��j�[�N�Ȗ��O
    
    GameObject* pSelectObj;             //�I�𒆂̃I�u�W�F�N�g
    std::string selectButtonKinds;      //�I�𒆂̃I�u�W�F�N�g�̎��
    string selectLoadFileNameStr;       //�I�𒆂̃I�u�W�F�N�g���ǂݍ��މ摜�⃂�f���̃t�@�C����
    char loadFileName[CHAR_SIZE] = "";  //�I�𒆂̓ǂݍ��ރt�@�C����
    char sectionName[CHAR_SIZE];        //�I�𒆂̃Z�N�V�����̖��O 
    XMFLOAT3 iniPosition = { 0,0,0 };   //�I�𒆂̈ʒu
    XMFLOAT3 iniScale = { 1,1,1 };      //�I�𒆂̊g�嗦
    XMFLOAT3 iniRotate = { 0,0,0 };     //�I�𒆂̌���
    std::string selectWriteFile;        //�I�𒆂̃I�u�W�F�N�g���ۑ�������ۂɏ�������JSON�̃t�@�C����
    int selectAlpha = 255;              //�I�𒆂̃A���t�@
    bool canCreate = false;             //�I�𒆂̃I�u�W�F�N�g�������ł��邩

    std::vector<Imgui_Obj::SettingInfo> settingInfoButtonList;//������{�^���̃��X�g
    std::vector<Imgui_Obj::SettingInfo> settingInfoImageList; //������摜�̃��X�g

    std::vector<Imgui_Obj::SettingInfo> settingInfoButtonFromPauseList;//������{�^���̃��X�g(�|�[�Y���)
    std::vector<Imgui_Obj::SettingInfo> settingInfoImageFromPauseList; //������摜�̃��X�g(�|�[�Y���)

    std::vector<GameObject*> debugLogList; //�f�o�b�O���O��\������I�u�W�F�N�g�̃��X�g
    
}

namespace Imgui_Obj
{
    //������
    void Initialize(SceneManager* pSceneManager_)
    {
        pText = new Text;
        pText->Initialize();
        pSceneManager = pSceneManager_;
    }

    //�X�V
    void Update()
    {
        pChangeSceneButton = (ChangeSceneButton*)pSceneManager->FindObject("ChangeSceneButton");

        //Imgui�𐶐�����
        InstantiateImgui();
        
    }

    //�J��
    void Release()
    {
        pText->Release();
    }

    //Imgui�𐶐�����
    void InstantiateImgui()
    {
        //�쐬�p��Imgui���o��
        ImguiIniObj();

        //������I�u�W�F�N�g�̍Đݒ���o����悤�ɂ���
        ReSettingButton();

        //�y�ɃV�[���`�F���W�o����悤�ɂ���
        SceneChangeImgui();

        //�f�o�b�O���O��\������Imgui���o��
        CreateDebugLog();

        //���G�f�B�b�g�V�[���ɂ�����
        if (pSceneManager->GetNowSceneID() == SCENE_ID::SCENE_ID_EDIT)
        {
            //UI���[�h��I������Imgui���쐬����
            UISelectModeImgui();
        }

        ////�^�C�g���V�[����������
        //if (pSceneManager->GetNowSceneID() == SCENE_ID::SCENE_ID_START)
        //{
        //    ///////////////////////�{�^���̈ʒu////////////////////////////////////////

        //    ImGui::Begin("Botton Pos");
        //    //////////////////////�X�^�[�g�{�^��/////////////////////////////////////////////////////

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

        //    //�}�E�X���[�h�Ȃ�V�����_�[�ňʒu���ς��Ȃ��ς��Ȃ�
        //    if (!pChangeSceneButton->GetMouseMode())
        //    {
        //        //�V�����_�[������܂ł͕ς��Ȃ�
        //        if (!changeSceneButtonX == 0 || !changeSceneButtonY == 0)
        //        {
        //            //�{�^���̈ʒu��ς���
        //            pChangeSceneButton->SetPosition(changeSceneButtonX, changeSceneButtonY, 0);
        //        }
        //    }
        //    else
        //    {
        //        //�}�E�X���[�h���{�^�����I�΂�ĂȂ������N���b�N��������Ă�����
        //        if (pChangeSceneButton->GetValue() && Input::IsMouseButton(1))
        //        {
        //            pChangeSceneButton->SetPosition(Math::PixelToTransform(Input::GetMousePosition()));
        //        }
        //    }

        //    //�{�^���̈ʒu�̃Z�[�u
        //    if (ImGui::Button("PositionSave"))
        //    {
        //        JsonOperator::AppendToJSONFileFloat(JsonOperator::TITLE_JSON, "ChangeSceneButton", "posX", pChangeSceneButton->GetPosition().x);
        //        JsonOperator::AppendToJSONFileFloat(JsonOperator::TITLE_JSON, "ChangeSceneButton", "posY", pChangeSceneButton->GetPosition().y);
        //    }

        //    ImGui::End();
        //}
    }

    //�`��
    void Draw()
    {
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    }

    //�I�u�W�F�N�g�𐶐�����Imgui���o���֐�
    void ImguiIniObj()
    {
        //Pause Setting��Imgui���쐬
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

            //�{�^���쐬���[�h�Ȃ�
            if (iniType == IniType::BUTTON)
            {
                //�{�^���쐬���[�h�̎��ɏo��imgui
                CreateButtonImgui();
            }

            //�摜�쐬���[�h�Ȃ�
            if (iniType == IniType::IMAGE)
            {
                //�摜�쐬���[�h�̎��ɏo��imgui
                CreateImageImgui();
            }

            //3D�I�u�W�F�N�g�쐬���[�h�̎��ɏo��imgui
            if (iniType == IniType::PLAYER)
            {
                //3D�I�u�W�F�N�g�쐬���[�h�̎��ɏo��Imgui(Begin�̒��Ŏg��)
                CreateObjectImgui();
            }
        }
        ImGui::End();
    }

    //�V�[���`�F���W����Imgui�𐶐�����֐�
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
            //�������G�f�B�b�g�V�[���ɍs���\��Ȃ�
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

    //imgui�Ń{�^����ۑ�������ɂ�邱��
    void RearButtonInstantiate()
    {
        SettingInfo setting{ pSelectObj, selectLoadFileNameStr, selectUniqueName , selectWriteFile,iniPosition, iniRotate, iniScale };
        settingInfoButtonList.push_back(setting);
        pSelectObj = nullptr;
    }

    // imgui�ŉ摜�𐶐�������ɂ�邱��
    void RearImageInstantiate()
    {
        SettingInfo setting{ pSelectObj, selectLoadFileNameStr, selectUniqueName , selectWriteFile,iniPosition, iniRotate, iniScale, selectAlpha };
        settingInfoImageList.push_back(setting);
        pSelectObj = nullptr;
    }

    //������{�^���̍Ĉړ������o����悤�ɂ���
    void ReSettingButton()
    {
        ImGui::Begin("CreateList");

        //�{�^��
        if (ImGui::TreeNode("Button"))
        {
            //pCreateList�̕�������
            for (int i = 0; i < settingInfoButtonList.size(); i++)
            {
                if (ImGui::TreeNode(settingInfoButtonList[i].sectionName_.c_str()))
                {
                    //�ǂݍ��ރt�@�C���������
                    ImGui::Text("LoadFileName");
                    //string�^��Char�^�ɕϊ�
                    char sec[CHAR_SIZE];
                    settingInfoButtonList[i].loadFileName_.copy(sec, CHAR_SIZE - 1);
                    sec[settingInfoButtonList[i].loadFileName_.length()] = '\0';

                    //�ǂݍ���InputText��\��
                    ImGui::InputText("LoadFile", sec, CHAR_SIZE);
                    settingInfoButtonList[i].loadFileName_ = sec;

                    std::filesystem::directory_entry dir;
                    dir.assign(settingInfoButtonList[i].loadFileName_);

                    //�w�肵���t�@�C�������݂��邩
                    canCreate = dir.exists();
                    if (!canCreate)
                    {
                        ImGui::Text("file doesn't exist");
                    }
                    else
                    {
                        //����{�^����\��
                        if (ImGui::Button("Decision"))
                        {
                            settingInfoButtonList[i].pObject_->SetPathName(settingInfoButtonList[i].loadFileName_);
                        }
                    }

                    //Transfom�̏������
                    ImGui::Text("Transform");
                    //�ʒu
                    float* iniPositionArrayTmp[3] = { &settingInfoButtonList[i].iniPosition_.x, &settingInfoButtonList[i].iniPosition_.y, &settingInfoButtonList[i].iniPosition_.z };
                    ImGui::DragFloat3("Position", iniPositionArrayTmp[0], DRAG_SPEED, -1.0f, 1.0f);
                    settingInfoButtonList[i].pObject_->SetPosition(settingInfoButtonList[i].iniPosition_);

                    //����
                    float* iniRotateArrayTmp[3] = { &settingInfoButtonList[i].iniRotate_.x,&settingInfoButtonList[i].iniRotate_.y, &settingInfoButtonList[i].iniRotate_.z };
                    ImGui::DragFloat3("Rotate", iniRotateArrayTmp[0], DRAG_SPEED, -1.0f, 1.0f);
                    settingInfoButtonList[i].pObject_->SetRotate(settingInfoButtonList[i].iniRotate_);

                    //�g�嗦
                    float* iniScaleArrayTmp[3] = { &settingInfoButtonList[i].iniScale_.x,&settingInfoButtonList[i].iniScale_.y, &settingInfoButtonList[i].iniScale_.z };
                    ImGui::DragFloat3("Scale", iniScaleArrayTmp[0], DRAG_SPEED, 0.0f, 100.0f);
                    settingInfoButtonList[i].pObject_->SetScale(settingInfoButtonList[i].iniScale_);

                    //�ۑ�
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

                    //�폜
                    if (ImGui::Button("Delete"))
                    {
                        //�I�u�W�F�N�g���폜
                        settingInfoButtonList[i].pObject_->KillMe();

                        //���̃Z�N�V�����̒��g����
                        JsonOperator::DeleteJSONSection(settingInfoButtonList[i].writeFile_, settingInfoButtonList[i].sectionName_);
                         
                        //���X�g�̃|�C���^������
                        settingInfoButtonList.erase(settingInfoButtonList.begin() + i);
                    }
                    ImGui::TreePop();
                }               
            }
            ImGui::TreePop();
        }

        //�摜
        if (ImGui::TreeNode("Image"))
        {
            //pCreateList�̕�������
            for (int i = 0; i < settingInfoImageList.size(); i++)
            {
                if (ImGui::TreeNode(settingInfoImageList[i].sectionName_.c_str()))
                {
                    //�ǂݍ��ރt�@�C���������
                    ImGui::Text("LoadFileName");
                    //string�^��Char�^�ɕϊ�
                    char sec[CHAR_SIZE];
                    settingInfoImageList[i].loadFileName_.copy(sec, CHAR_SIZE - 1);
                    sec[settingInfoImageList[i].loadFileName_.length()] = '\0';

                    //�ǂݍ���InputText��\��
                    ImGui::InputText("LoadFile", sec, CHAR_SIZE);
                    settingInfoImageList[i].loadFileName_ = sec;

                    std::filesystem::directory_entry dir;
                    dir.assign(settingInfoImageList[i].loadFileName_);

                    //�w�肵���t�@�C�������݂��邩
                    canCreate = dir.exists();
                    if (!canCreate)
                    {
                        ImGui::Text("file doesn't exist");
                    }
                    else
                    {
                        //����{�^����\��
                        if (ImGui::Button("Decision"))
                        {
                            settingInfoImageList[i].pObject_->SetPathName(settingInfoImageList[i].loadFileName_);
                        }
                    }

                    //Transfom�̏������
                    ImGui::Text("Transform");
                    //�ʒu
                    float* iniPositionArrayTmp[3] = { &settingInfoImageList[i].iniPosition_.x, &settingInfoImageList[i].iniPosition_.y, &settingInfoImageList[i].iniPosition_.z };
                    ImGui::DragFloat3("Position", iniPositionArrayTmp[0], DRAG_SPEED, -1.0f, 1.0f);
                    settingInfoImageList[i].pObject_->SetPosition(settingInfoImageList[i].iniPosition_);

                    //����
                    float* iniRotateArrayTmp[3] = { &settingInfoImageList[i].iniRotate_.x,&settingInfoImageList[i].iniRotate_.y, &settingInfoImageList[i].iniRotate_.z };
                    ImGui::DragFloat3("Rotate", iniRotateArrayTmp[0], DRAG_SPEED, -1.0f, 1.0f);
                    settingInfoImageList[i].pObject_->SetRotate(settingInfoImageList[i].iniRotate_);

                    //�g�嗦
                    float* iniScaleArrayTmp[3] = { &settingInfoImageList[i].iniScale_.x,&settingInfoImageList[i].iniScale_.y, &settingInfoImageList[i].iniScale_.z };
                    ImGui::DragFloat3("Scale", iniScaleArrayTmp[0], DRAG_SPEED, 0.0f, 100.0f);
                    settingInfoImageList[i].pObject_->SetScale(settingInfoImageList[i].iniScale_);

                    //�A���t�@�l��ς���
                    ImGui::DragInt("alpha", &settingInfoImageList[i].alpha_, 1, 0, 255);
                    settingInfoImageList[i].pObject_->SetAlpha(settingInfoImageList[i].alpha_);

                    //�ۑ�
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

                    //�폜
                    if (ImGui::Button("Delete"))
                    {
                        //�I�u�W�F�N�g���폜
                        settingInfoImageList[i].pObject_->KillMe();

                        //���̃Z�N�V�����̒��g����
                        JsonOperator::DeleteJSONSection(settingInfoImageList[i].writeFile_, settingInfoImageList[i].sectionName_);

                        //���X�g�̃|�C���^������
                        settingInfoImageList.erase(settingInfoImageList.begin() + i);
                    }
                    ImGui::TreePop();
                }

                
            }
            ImGui::TreePop();
        }

        ImGui::End();
    }

    //�{�^���쐬���[�h�̎��ɏo��imgui
    void CreateButtonImgui()
    {
        ImGui::Begin("Create Button");

        // �I�u�W�F�N�g�𐶐����鎞�Ɋ�{�I��Imgui���o��(Begin�̒��Ŏg��)
        SettingBasicImgui();

        //�ǂ�Ȏ�ނ̃{�^���𐶐����邩
        ImGui::Text("ButtonType");
        //ImGui::RadioButton("SceneChange", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON)); ImGui::SameLine();
        ImGui::RadioButton("PlayerControl", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON));
        ImGui::RadioButton("Slinder", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::SLIDER));

        //�V�[���`�F���W�{�^�����쐬����\��Ȃ�
        if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON))
        {
            ImGui::Text("NextScene");
            ImGui::RadioButton("Title", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_START)); ImGui::SameLine();
            ImGui::RadioButton("Play", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_PLAY));
            ImGui::RadioButton("GameOver", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_GAMEOVER)); ImGui::SameLine();
            ImGui::RadioButton("Clear", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_GOAL));
        }

        //�����{�^��
        if (canCreate && ImGui::Button("Create"))
        {       
            //�g���q��ǉ�
            selectLoadFileNameStr = std::string(loadFileName) + AddExtension();

            //�ۑ����Ă��Ȃ��I�u�W�F�N�g�͏���
            if (pSelectObj != nullptr)
            {
                pSelectObj->KillMe();
            }

            //�v���C���[�̃{�^���z�u��ς���{�^�����쐬����Ȃ�
            if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON))
            {       
                //�{�^���̎��
                selectButtonKinds = JsonOperator::ButtonToString(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON);

                //�I�u�W�F�N�g���쐬���|�C���^��ۑ����Ă���
                pSelectObj = InstantiateButton<PlayerControlButton>(pSceneManager->GetNowScenePointer(), selectLoadFileNameStr, iniPosition, iniRotate, iniScale);
            }

            //�X���C�_�[���쐬����Ȃ�
            if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::SLIDER))
            {
                //�{�^���̎��
                selectButtonKinds = JsonOperator::ButtonToString(ButtonManager::ButtonKinds::SLIDER);

                //�I�u�W�F�N�g���쐬���|�C���^��ۑ����Ă���
                pSelectObj = InstantiateButton<Slider>(pSceneManager->GetNowScenePointer(), selectLoadFileNameStr, iniPosition, iniRotate, iniScale);
            }
        }

        if (pSelectObj != nullptr)
        {
            ImGui::SameLine();
            //�Z�[�u�{�^��
            if (ImGui::Button("Save"))
            {
                //�e�����̃V�[���Ȃ�
                if (parentNum == static_cast<int>(GameManager::ParentNum::NOW_SCENE))
                {
                    //�^�C�g���V�[����������
                    switch (pSceneManager->GetNowSceneID())
                    {
                        //�^�C�g���V�[����������
                    case SCENE_ID::SCENE_ID_START:
                        InstanceManager::SaveButton(JsonOperator::TITLE_BUTTON_JSON, selectUniqueName, selectLoadFileNameStr, selectButtonKinds, iniPosition, iniRotate, iniScale);
                        break;
                    default:
                        break;
                    }
                }
                //�|�[�Y��������
                else if (parentNum == static_cast<int>(GameManager::ParentNum::PAUSE))
                {
                    //�ۑ�����
                    InstanceManager::SaveButton(JsonOperator::PAUSE_BUTTON_JSON, selectUniqueName, selectLoadFileNameStr, selectButtonKinds, iniPosition, iniRotate, iniScale);
                }

                //imgui�Ń{�^����ۑ�������ɂ�邱��
                RearButtonInstantiate();
            }ImGui::SameLine();

            //�폜�{�^��
            if (ImGui::Button("Delete"))
            {
                pSelectObj->KillMe();
                pSelectObj = nullptr;
            }
        }

        //�L�����Z���{�^��
        if (ImGui::Button("Cancel"))
        {

            iniType = IniType::NONE;
        }
        ImGui::End();
    }

    //�摜�쐬���[�h�̎��ɏo��Imgui
    void CreateImageImgui()
    {
        //imgui�𐶐�
        ImGui::Begin("Create Image");

        // �I�u�W�F�N�g�𐶐����鎞�Ɋ�{�I��Imgui���o��(Begin�̒��Ŏg��)
        SettingBasicImgui();

        //�����{�^��
        if (canCreate && ImGui::Button("Create"))
        {
            //�g���q��ǉ�
            selectLoadFileNameStr = std::string(loadFileName) + AddExtension();

            //�ۑ����Ă��Ȃ��I�u�W�F�N�g�͏���
            if (pSelectObj != nullptr)
            {
                pSelectObj->KillMe();
            }

            //�I�u�W�F�N�g���쐬���|�C���^��ۑ����Ă���
            pSelectObj = InstantiateImage<ImageBase>(pSceneManager->GetNowScenePointer(), selectLoadFileNameStr, iniPosition, iniRotate, iniScale, selectAlpha);
        }

        //�I�u�W�F�N�g������Ă�����
        if (pSelectObj != nullptr)
        {
            ImGui::SameLine();
            //�Z�[�u�{�^��
            if (ImGui::Button("Save"))
            {
                //�e�����̃V�[���Ȃ�
                if (parentNum == static_cast<int>(GameManager::ParentNum::NOW_SCENE))
                {
                    switch (pSceneManager->GetNowSceneID())
                    {
                        //�^�C�g���V�[����������
                    case SCENE_ID::SCENE_ID_START:
                        //�ۑ�����
                        InstanceManager::SaveImage(JsonOperator::TITLE_IMAGE_JSON, selectUniqueName, selectLoadFileNameStr, iniPosition, iniRotate, iniScale, selectAlpha);
                        break;

                    default:
                        break;
                    }
                }
                //�|�[�Y��������
                else if (parentNum == static_cast<int>(GameManager::ParentNum::PAUSE))
                {
                    //�ۑ�����
                    InstanceManager::SaveImage(JsonOperator::PAUSE_IMAGE_JSON, selectUniqueName, selectLoadFileNameStr, iniPosition, iniRotate, iniScale, selectAlpha);
                }

                //imgui�ŉ摜��ۑ�������ɂ�邱��
                RearImageInstantiate();
            }ImGui::SameLine();

            //�폜�{�^��
            if (ImGui::Button("Delete"))
            {
                pSelectObj->KillMe();
                pSelectObj = nullptr;
            }
        }

        //�L�����Z���{�^��
        if (ImGui::Button("Cancel"))
        {

            iniType = IniType::NONE;
        }
        ImGui::End();
    }

    //3D�I�u�W�F�N�g�쐬���[�h�̎��ɏo��Imgui(Begin�̒��Ŏg��)
    void CreateObjectImgui()
    {
        ImGui::Begin("Create Button");

        // �I�u�W�F�N�g�𐶐����鎞�Ɋ�{�I��Imgui���o��(Begin�̒��Ŏg��)
        SettingBasicImgui();

        //�ǂ�Ȏ�ނ̃{�^���𐶐����邩
        ImGui::Text("ButtonType");
        //ImGui::RadioButton("SceneChange", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON)); ImGui::SameLine();
        ImGui::RadioButton("PlayerControl", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON));
        ImGui::RadioButton("Slinder", &buttonKinds, static_cast<int>(ButtonManager::ButtonKinds::SLIDER));

        //�V�[���`�F���W�{�^�����쐬����\��Ȃ�
        if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::SCENE_CHANGE_BUTTON))
        {
            ImGui::Text("NextScene");
            ImGui::RadioButton("Title", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_START)); ImGui::SameLine();
            ImGui::RadioButton("Play", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_PLAY));
            ImGui::RadioButton("GameOver", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_GAMEOVER)); ImGui::SameLine();
            ImGui::RadioButton("Clear", &SceneChangeNextScene, static_cast<int>(SCENE_ID::SCENE_ID_GOAL));
        }

        //�����{�^��
        if (canCreate && ImGui::Button("Create"))
        {
            selectButtonKinds = JsonOperator::ButtonToString(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON);

            //�g���q��ǉ�
            selectLoadFileNameStr = std::string(loadFileName) + AddExtension();

            //�ۑ����Ă��Ȃ��I�u�W�F�N�g�͏���
            if (pSelectObj != nullptr)
            {
                pSelectObj->KillMe();
            }

            //�v���C���[�̃{�^���z�u��ς���{�^�����쐬����Ȃ�
            if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON))
            {
                //�I�u�W�F�N�g���쐬���|�C���^��ۑ����Ă���
                pSelectObj = InstantiateButton<PlayerControlButton>(pSceneManager->GetNowScenePointer(), selectLoadFileNameStr, iniPosition, iniRotate, iniScale);
            }
            //�X���C�_�[���쐬����Ȃ�
            if (buttonKinds == static_cast<int>(ButtonManager::ButtonKinds::PLAYER_CONTROL_BUTTON))
            {
                //�I�u�W�F�N�g���쐬���|�C���^��ۑ����Ă���
                pSelectObj = InstantiateButton<PlayerControlButton>(pSceneManager->GetNowScenePointer(), selectLoadFileNameStr, iniPosition, iniRotate, iniScale);
            }
        }

        if (pSelectObj != nullptr)
        {
            ImGui::SameLine();
            //�Z�[�u�{�^��
            if (ImGui::Button("Save"))
            {
                //�e�����̃V�[���Ȃ�
                if (parentNum == static_cast<int>(GameManager::ParentNum::NOW_SCENE))
                {
                    //�^�C�g���V�[����������
                    switch (pSceneManager->GetNowSceneID())
                    {
                        //�^�C�g���V�[����������
                    case SCENE_ID::SCENE_ID_START:
                        InstanceManager::SaveButton(JsonOperator::TITLE_BUTTON_JSON, selectUniqueName, selectLoadFileNameStr, selectButtonKinds, iniPosition, iniRotate, iniScale);
                        break;
                    default:
                        break;
                    }
                }
                //�|�[�Y��������
                else if (parentNum == static_cast<int>(GameManager::ParentNum::PAUSE))
                {
                    //�ۑ�����
                    InstanceManager::SaveButton(JsonOperator::PAUSE_BUTTON_JSON, selectUniqueName, selectLoadFileNameStr, selectButtonKinds, iniPosition, iniRotate, iniScale);
                }

                //imgui�Ń{�^����ۑ�������ɂ�邱��
                RearButtonInstantiate();
            }ImGui::SameLine();

            //�폜�{�^��
            if (ImGui::Button("Delete"))
            {
                pSelectObj->KillMe();
                pSelectObj = nullptr;
            }
        }

        //�L�����Z���{�^��
        if (ImGui::Button("Cancel"))
        {

            iniType = IniType::NONE;
        }
        ImGui::End();
    }
    

    //Transform��������imgui���o��
    void TransformImgui()
    {
        //Transfom�̏������
        ImGui::Text("Transform");

        //�ʒu
        //�Q�ƂŐ���
        float* iniPositionArray[3] = { &iniPosition.x, &iniPosition.y, &iniPosition.z };
        ImGui::DragFloat3("Position", iniPositionArray[0], DRAG_SPEED, -1.0f, 1.0f);
        
        //����
        float* iniRotateArray[3] = { &iniRotate.x,&iniRotate.y, &iniRotate.z };
        ImGui::DragFloat3("Rotate", iniRotateArray[0], DRAG_SPEED, -1.0f, 1.0f);
           
        //�g�嗦
        float* iniScaleArray[3] = { &iniScale.x,&iniScale.y, &iniScale.z };
        ImGui::DragFloat3("Scale", iniScaleArray[0], DRAG_SPEED, -1.0f, 1.0f);           

        //�A���t�@�l��ς���
        ImGui::DragInt("alpha", &selectAlpha, 1, 0, 255);         

        if (pSelectObj != nullptr)
        {
            pSelectObj->SetPosition(iniPosition);
            pSelectObj->SetRotate(iniRotate);
            pSelectObj->SetScale(iniScale);
            pSelectObj->SetAlpha(selectAlpha);
        }
    }

    //�I�u�W�F�N�g�𐶐����鎞�Ɋ�{�I��Imgui���o��
    void SettingBasicImgui()
    {      
        //�Z�N�V������
        ImGui::Text("ObjectName");
        ImGui::InputText("name", sectionName, CHAR_SIZE);
        selectUniqueName = sectionName;

        ImGui::NewLine();

        //�ǂݍ��ރt�@�C���������
        ImGui::Text("LoadFileName");

        std::string filename = AddExtension();
        ImGui::InputText(filename.c_str(), loadFileName, CHAR_SIZE);
        ImGui::RadioButton("png", &extension, EXTENSION_PNG); ImGui::SameLine();
        ImGui::RadioButton("jpg", &extension, EXTENSION_JPG); ImGui::SameLine();
        ImGui::RadioButton("fbx", &extension, EXTENSION_FBX); 

        //�t�@�C����+�g���q�ɂ���
        std::string f = loadFileName + filename;

        //�t�@�C�������邩�m�F
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

        //Transform��������imgui���o��
        TransformImgui();

        ImGui::NewLine();

        //�e�I�u�W�F�N�g�͉���(�ǂ��Ő������邩)
        ImGui::Text("Parent");

        //�G�f�B�b�g�V�[������Ȃ�������
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

    //�f�o�b�O���O��\������Imgui���o��
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

    //�f�o�b�O���O��\�����郊�X�g�ɒǉ�����
    void AddDebugLogList(GameObject* obj)
    {
        debugLogList.push_back(obj);
    }

    // �g���q��ǉ�����֐�(�ϐ�extension���Q��)
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

    //������{�^���̃��X�g�ɓ����
    void AddButtonList(std::string filename, std::string section, InstanceManager::CreateInfoJSON info, Button* button)
    {
        SettingInfo SetInfo((GameObject*)button, info.loadFile, section, filename, info.position, info.rotate, info.scale);
        settingInfoButtonList.push_back(SetInfo);
    }

    //������摜�̃��X�g�ɓ����
    void AddImageList(std::string filename, std::string section, InstanceManager::CreateImageInfoJSON info, GameObject* image)
    {
        SettingInfo SetInfo(image, info.loadFile, section, filename, info.position, info.rotate, info.scale, info.alpha);
        settingInfoImageList.push_back(SetInfo);
    }

    //�����郊�X�g���N���A����
    void ClearList()
    {
        //���X�g������
        settingInfoButtonFromPauseList.clear();
        settingInfoImageFromPauseList.clear();
        settingInfoButtonList.clear();
        settingInfoImageList.clear();
        debugLogList.clear();
    }

    //UI���[�h��I������Imgui���쐬����
    void UISelectModeImgui()
    {
        ImGui::Begin("UI_TYPE");

        //���W�I�{�^���쐬
        ImGui::RadioButton("NONE", &modeUI, static_cast<int>(UI_Type::NONE)); ImGui::SameLine();
        ImGui::RadioButton("PAUSE", &modeUI, static_cast<int>(UI_Type::PAUSE)); 

        //�O�t���[���ƍ쐬����UI���������
        if (modeUI != prevModeUI)
        {
            //���X�g������
            ClearList();
        }

        prevModeUI = modeUI;
        ImGui::End();
    }

    // modeUI�̃Q�b�^�[
    int GetUIType()
    {
        return modeUI;
    }

    // �t�@�C�������邩�m�F
    bool existFile(std::string filename)
    {
        std::string fullFilename = "";
        //�쐬�^�C�v�ɂ���ĒT���f�B���N�g����ς���
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

        //�w�肵���t�@�C�������݂��邩
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
////if (ImGui::Button("�I�u�W�F�N�g��ǉ�")) 
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
