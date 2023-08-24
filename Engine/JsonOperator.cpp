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
    // ������
    void Initialize()
    {

    }

    //JSON�t�@�C����ǂݍ��ފ֐�
    bool LoadJSONFromFile(string filename, Document& document)
    {
        FILE* fp;
        if (fopen_s(&fp, filename.c_str(), "r") != 0)
        {
            MessageBox(NULL, "Load Error", "BaseProjDx9�G���[", MB_OK);
        }

        // �t�@�C������ǂݍ���
        char readBuffer[65536];
        FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        document.ParseStream(is);

        // �t�@�C�������
        fclose(fp);

        // �ǂݍ��݂������������ǂ�����Ԃ�
        if (!document.HasParseError() && document.IsObject())
        {
            //�z��Ɋi�[
            //dataList.insert(std::make_pair(filename, document));
            return true;
        }
        return false;
    }

    //�t�@�C���̓��e�𕶎���Ƃ��ēǂݍ���
    bool LoadJSONString(std::string filename, std::string& str)
    {
        // JSON�t�@�C�����J��
        std::ifstream ifs(filename);
        if (!ifs) {
            return false;
        }

        // �t�@�C���̓��e�𕶎���Ƃ��ēǂݍ���
        std::string jsonStr((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        str = jsonStr;
        ifs.close();
    }

    //JSON�t�@�C�����쐬����֐�
    bool CreateJSONFile(std::string filename)
    {
        // JSON�I�u�W�F�N�g���쐬
        Document document;
        document.SetObject();

        // JSON�t�@�C���ɏ����o��
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

    //�Z�b�V������ǉ�����֐�
    bool AddSection(const std::string& filename, const std::string& section)
    {
        //�t�@�C���̓��e�𕶎���Ƃ��ēǂݍ���
        std::string str = "";
        //���s������false��Ԃ�
        if (!LoadJSONString(filename, str))
        {
            return false;
        }

        // JSON�f�[�^���p�[�X����
        // �p�[�X�@�f�[�^����͂��K�v�ȃf�[�^�����o������
        Document document;
        //���s������false��Ԃ�
        if (document.Parse(str.c_str()).HasParseError()) {
            return false;
        }

        // �V�����l��ǉ��܂��͏㏑������
        if (!document.IsObject()) {
            return false;
        }

        // �Z�N�V������ǉ�����
        Document::AllocatorType& allocator = document.GetAllocator();
        Value newValueObj(kObjectType);
        rapidjson::GenericStringRef<char> ref{ section.c_str() };
        document.AddMember(ref, newValueObj, allocator);

        // �X�V���ꂽJSON�f�[�^�𕶎���ɕϊ�����
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        document.Accept(writer);
        std::string updatedJsonStr = buffer.GetString();

        // JSON�t�@�C�����㏑������
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }

        ofs << updatedJsonStr;
        ofs.close();

        return true;
    }

    //JSON�t�@�C���̕������ǂݎ��
    bool GetJSONString(std::string filename, std::string key, std::string& out)
    {
        Document data;
        //�t�@�C�����J���Ȃ�������false��Ԃ�
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //data�ɓǂݎ�����f�[�^������
        const char* name = "";
        if (data.HasMember(key.c_str()) && data[key.c_str()].IsString()) {
            name = data[key.c_str()].GetString();
            out = name;
            return true;
        }
        //���s������false��Ԃ�
        return false;
    }

    //JSON�t�@�C���̐����l��ǂݎ��
    bool GetJSONInt(std::string filename, std::string key, int& out)
    {
        Document data;
        //�t�@�C�����J���Ȃ�������false��Ԃ�
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //data�ɓǂݎ�����f�[�^������
        int name = 0;
        if (data.HasMember(key.c_str()) && data[key.c_str()].IsInt()) {
            name = data[key.c_str()].GetInt();
            out = name;
            return true;
        }
        //���s������false��Ԃ�
        return false;
    }

    //JSON�t�@�C���̐����l��ǂݎ��
    bool GetJSONFloat(std::string filename, std::string key, float& out)
    {
        Document data;
        //�t�@�C�����J���Ȃ�������false��Ԃ�
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //data�ɓǂݎ�����f�[�^������
        float name = 0.0f;
        if (data.HasMember(key.c_str()) && data[key.c_str()].IsFloat()) {
            name = data[key.c_str()].GetFloat();
            out = name;
            return true;
        }
        //���s������false��Ԃ�
        return false;
    }

    //JSON�t�@�C���̕������ǂݎ��
    bool GetJSONString(std::string filename, std::string section, std::string key, std::string& out)
    {
        Document data;
        //�t�@�C�����J���Ȃ�������false��Ԃ�
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //data�ɓǂݎ�����f�[�^������
        const char* name = "";

        //�����̃Z�b�V���������邩�ǂ����m�F
        if (data.IsObject())
        {
            const Value& sectionData = data[section.c_str()];

            //�����̃L�[�����邩�ǂ����m�F
            if (sectionData.HasMember(key.c_str()) && sectionData[key.c_str()].IsString()) {

                //�ǂݎ�����f�[�^������
                name = sectionData[key.c_str()].GetString();
                out = name;
                return true;
            }
        }

        //���s������false��Ԃ�
        return false;
    }

    //JSON�t�@�C���̐����l��ǂݎ��
    bool GetJSONInt(std::string filename, std::string section, std::string key, int& out)
    {
        Document data;
        //�t�@�C�����J���Ȃ�������false��Ԃ�
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //data�ɓǂݎ�����f�[�^������
        int name = 0.0f;

        //�����̃Z�b�V���������邩�ǂ����m�F
        if (data.IsObject())
        {
            const Value& sectionData = data[section.c_str()];

            //�����̃L�[�����邩�ǂ����m�F
            if (sectionData.HasMember(key.c_str()) && sectionData[key.c_str()].IsInt()) {

                //�ǂݎ�����f�[�^������
                name = sectionData[key.c_str()].GetInt();
                out = name;
                return true;
            }
        }
        //���s������false��Ԃ�
        return false;
    }

    //JSON�t�@�C���̐����l��ǂݎ��
    bool GetJSONFloat(std::string filename, std::string section, std::string key, float& out)
    {
        Document data;
        //�t�@�C�����J���Ȃ�������false��Ԃ�
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //data�ɓǂݎ�����f�[�^������
        float name = 0.0f;

        //�����̃Z�b�V���������邩�ǂ����m�F
        if (data.IsObject())
        {
            const Value& sectionData = data[section.c_str()];

            //�����̃L�[�����邩�ǂ����m�F
            if (sectionData.HasMember(key.c_str()) && sectionData[key.c_str()].IsFloat()) {

                //�ǂݎ�����f�[�^������
                name = sectionData[key.c_str()].GetFloat();
                out = name;
                return true;
            }
        }

        //���s������false��Ԃ�
        return false;
    }

    //JSON�t�@�C���ɏ�������
    bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const std::string& value)
    {
        // JSON�I�u�W�F�N�g���쐬
        Document sectionDocument;
        sectionDocument.SetObject();

        // JSON�Ƀf�[�^��ǉ�
        Document::AllocatorType& allocator = sectionDocument.GetAllocator();

        Value keyDocument(kObjectType);
        rapidjson::GenericStringRef<char> ref{ key.c_str() };
        rapidjson::GenericStringRef<char> val{ value.c_str() };
        keyDocument.AddMember(ref, val, allocator);
        rapidjson::GenericStringRef<char> sec{ section.c_str() };
        sectionDocument.AddMember(sec, keyDocument, allocator);

        // JSON�𕶎��񉻂���
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        sectionDocument.Accept(writer);

        // JSON���t�@�C���ɏ�������
        std::ofstream ofs(filename, std::ios::app);
        if (!ofs) {
            return false;
        }
        ofs << buffer.GetString();
        ofs.close();

        return true;
    }

    //JSON�t�@�C���ɏ�������(�㏑��)
    bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const int& value)
    {
        // JSON�I�u�W�F�N�g���쐬
        Document sectionDocument;
        sectionDocument.SetObject();

        // JSON�Ƀf�[�^��ǉ�
        Document::AllocatorType& allocator = sectionDocument.GetAllocator();

        Value keyDocument(kObjectType);
        rapidjson::GenericStringRef<char> ref{ key.c_str() };
        keyDocument.AddMember(ref, value, allocator);
        rapidjson::GenericStringRef<char> sec{ section.c_str() };
        sectionDocument.AddMember(sec, keyDocument, allocator);

        // JSON�𕶎��񉻂���
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        sectionDocument.Accept(writer);

        // JSON���t�@�C���ɏ�������
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }
        ofs << buffer.GetString();
        ofs.close();

        return true;
    }

    //JSON�t�@�C���ɏ�������(�㏑��)
    bool WriteJSONToFile(const std::string& filename, const std::string& section, const std::string& key, const float& value)
    {
        // JSON�I�u�W�F�N�g���쐬
        Document sectionDocument;
        sectionDocument.SetObject();

        // JSON�Ƀf�[�^��ǉ�
        Document::AllocatorType& allocator = sectionDocument.GetAllocator();

        Value keyDocument(kObjectType);
        rapidjson::GenericStringRef<char> ref{ key.c_str() };
        keyDocument.AddMember(ref, value, allocator);
        rapidjson::GenericStringRef<char> sec{ section.c_str() };
        sectionDocument.AddMember(sec, keyDocument, allocator);

        // JSON�𕶎��񉻂���
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        sectionDocument.Accept(writer);

        // JSON���t�@�C���ɏ�������
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }
        ofs << buffer.GetString();
        ofs.close();

        return true;
    }

    //JSON�t�@�C���ɏ�������(�ǋL�A���������j
    bool AppendToJSONFileString(const std::string& filename, const std::string& section, const std::string& key, std::string value)
    {
        //�t�@�C���̓��e�𕶎���Ƃ��ēǂݍ���
        std::string str = "";

        //fileName�̃t�@�C�����̃t�@�C�����Ȃ�������
        std::ifstream file(filename);
        if (!file.good())
        {
            //�t�@�C�������
            if (!CreateJSONFile(filename))
            {
                return false;          
            }  
        }

        //�t�@�C���ǂݍ���
        if (!LoadJSONString(filename, str))
        {
            return false;
        }

        // JSON�f�[�^���p�[�X����
        // �p�[�X�@�f�[�^����͂��K�v�ȃf�[�^�����o������
        Document document;
        //���s������false��Ԃ�
        if (document.Parse(str.c_str()).HasParseError()) {
            return false;
        }

        // �V�����l��ǉ��܂��͏㏑������
        if (!document.IsObject()) {
            return false;
        }

        //�Z�N�V�������Ȃ�������
        if (!document.HasMember(section.c_str()))
        {
            //�Z�N�V������ǉ�
            if (!AddSection(filename, section))
            {
                return false;
            }
            else
            {
                //�ēx���[�h����
                //���s������false��Ԃ�
                if (!LoadJSONString(filename, str))
                {
                    return false;
                }

                // JSON�f�[�^���p�[�X����
                // �p�[�X�@�f�[�^����͂��K�v�ȃf�[�^�����o������
                //���s������false��Ԃ�
                if (document.Parse(str.c_str()).HasParseError())
                {
                    return false;
                }
            }
        }

        // �I�u�W�F�N�g���Ɋ��ɓ����L�[�����݂���ꍇ�͏㏑���A�����łȂ��ꍇ�͒ǉ�����
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

        // �X�V���ꂽJSON�f�[�^�𕶎���ɕϊ�����
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        document.Accept(writer);
        std::string updatedJsonStr = buffer.GetString();

        // JSON�t�@�C�����㏑������
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }

        ofs << updatedJsonStr;
        ofs.close();

        return true;
    }

    // JSON�t�@�C���ɏ�������(�ǋL�A���������j
    bool AppendToJSONFileFloat(const std::string& filename, const std::string& section, const std::string& key, float value)
    {
        //�t�@�C���̓��e�𕶎���Ƃ��ēǂݍ���
        std::string str = "";

        //fileName�̃t�@�C�����̃t�@�C�����Ȃ�������
        std::ifstream file(filename);
        if (!file.good())
        {
            //�t�@�C�������
            if (!CreateJSONFile(filename))
            {
                return false;
            }
        }

        //�t�@�C���ǂݍ���
        if (!LoadJSONString(filename, str))
        {
            return false;
        }

        // JSON�f�[�^���p�[�X����
        // �p�[�X�@�f�[�^����͂��K�v�ȃf�[�^�����o������
        Document document;
        //���s������false��Ԃ�
        if (document.Parse(str.c_str()).HasParseError()) {
            return false;
        }

        // �V�����l��ǉ��܂��͏㏑������
        if (!document.IsObject()) {
            return false;
        }

        //�Z�N�V�������Ȃ�������
        if (!document.HasMember(section.c_str()))
        {
            //�Z�N�V������ǉ�
            if (!AddSection(filename, section))
            {
                return false;
            }
            else
            {
                //�ēx���[�h����
                //���s������false��Ԃ�
                if (!LoadJSONString(filename, str))
                {
                    return false;
                }

                // JSON�f�[�^���p�[�X����
                // �p�[�X�@�f�[�^����͂��K�v�ȃf�[�^�����o������
                //���s������false��Ԃ�
                if (document.Parse(str.c_str()).HasParseError()) 
                {
                    return false;
                }
            }
        }

        // �I�u�W�F�N�g���Ɋ��ɓ����L�[�����݂���ꍇ�͏㏑���A�����łȂ��ꍇ�͒ǉ�����
        Document::AllocatorType& allocator = document.GetAllocator();
        if (document[section.c_str()].HasMember(key.c_str())) {
            document[section.c_str()][key.c_str()] = value;
        }
        else {
            Value newValueObj(value);
            document[section.c_str()].AddMember(Value(key.c_str(), allocator).Move(), newValueObj, allocator);
        }

        // �X�V���ꂽJSON�f�[�^�𕶎���ɕϊ�����
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        document.Accept(writer);
        std::string updatedJsonStr = buffer.GetString();

        // JSON�t�@�C�����㏑������
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }

        ofs << updatedJsonStr;
        ofs.close();

        return true;
    }

    //�Z�N�V�����̃L�[�ƃZ�N�V���������ׂč폜
    bool DeleteJSONSection(const std::string& filename, const std::string& section)
    {
        Document data;
        //�t�@�C�����J���Ȃ�������false��Ԃ�
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        //�Z�N�V�����̃����o�[��S�č폜����
        if(data.HasMember(section.c_str()))
        {
            data.RemoveMember(section.c_str());
            data.EraseMember(section.c_str());
        }

        // �X�V���ꂽJSON�f�[�^�𕶎���ɕϊ�����
        StringBuffer buffer;
        Writer<StringBuffer> writer(buffer);
        data.Accept(writer);
        std::string updatedJsonStr = buffer.GetString();

        // JSON�t�@�C�����㏑������
        std::ofstream ofs(filename);
        if (!ofs) {
            return false;
        }

        ofs << updatedJsonStr;
        ofs.close();

        return true;
    }

    // �I�u�W�F�N�g�𐶐����邽�߂̏���JSON���珑������(������������)
    bool WhiteCreateInfo(const std::string& filename, const std::string& section, InstanceManager::CreateInfoJSON& info)
    {
        //������̏��
        std::string infoStr[InstanceManager::INFO_STR] =
        {
            info.loadFile,
            info.objectName
        };

        //���l�̏��
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

       //������̏�������
       for (auto i = 0; i < InstanceManager::INFO_STR; i++)
        {
           if (!AppendToJSONFileString(filename, section, InstantiateKeyString[i], infoStr[i]))
           {
               return false;
           }
        }

       //���l�̏�������
       for (auto i = 0; i < InstanceManager::INFO_FLOAT; i++)
       {
           if (!AppendToJSONFileFloat(filename, section, InstantiateKeyFloat[i], infoFloat[i]))
           {
               return false;
           }
       }

        return true;
    }

    //�摜�𐶐����邽�߂̏���JSON���珑������(������������)
    bool WhiteCreateImageInfo(const std::string& filename, const std::string& section, InstanceManager::CreateImageInfoJSON& info)
    {
        //������̏��
        std::string infoStr[InstanceManager::IMAGE_INFO_STR] =
        {
            info.loadFile,
        };

        //���l�̏��
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

        //������̏�������
        for (auto i = 0; i < InstanceManager::IMAGE_INFO_STR; i++)
        {
            if (!AppendToJSONFileString(filename, section, InstantiateKeyString[i], infoStr[i]))
            {
                return false;
            }
        }

        //���l�̏�������
        for (auto i = 0; i < InstanceManager::IMAGE_INFO_FLOAT; i++)
        {
            if (!AppendToJSONFileFloat(filename, section, InstantiateKeyFloat[i], infoFloat[i]))
            {
                return false;
            }
        }

        return true;
    }

    //�I�u�W�F�N�g�𐶐����邽�߂̏���JSON����ǂݍ���
    bool GetInstanceInfo(const std::string& filename, const std::string& section, InstanceManager::CreateInfoJSON& info)
    {
        //������̏��
        std::string infoStr[InstanceManager::INFO_STR] =
        {
            info.loadFile,
            info.objectName
        };

        //���l�̏��
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


        //������̓ǂݍ���
        for (auto i = 0; i < InstanceManager::INFO_STR; i++)
        {
            if (!GetJSONString(filename, section, InstantiateKeyString[i], infoStr[i]))
            {
                return false;
            }
        }

        //���l�̓ǂݍ���
        for (auto i = 0; i < InstanceManager::INFO_FLOAT; i++)
        {
            if (!GetJSONFloat(filename, section, InstantiateKeyFloat[i], infoFloat[i]))
            {
                return false;
            }
        }

        //�Ԃ��\���̂��쐬
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

    //�摜�𐶐����邽�߂̏���JSON����ǂݍ���
    bool GetCreateImageInfo(const std::string& filename, const std::string& section, InstanceManager::CreateImageInfoJSON& info)
    {
        //������̏��
        std::string infoStr[InstanceManager::IMAGE_INFO_STR] =
        {
            info.loadFile,
        };

        //���l�̏��
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

        //������̓ǂݍ���
        for (auto i = 0; i < InstanceManager::IMAGE_INFO_STR; i++)
        {
            if (!GetJSONString(filename, section, InstantiateKeyString[i], infoStr[i]))
            {
                return false;
            }
        }

        //���l�̓ǂݍ���
        for (auto i = 0; i < InstanceManager::IMAGE_INFO_FLOAT; i++)
        {
            if (!GetJSONFloat(filename, section, InstantiateKeyFloat[i], infoFloat[i]))
            {
                return false;
            }
        }

        //�Ԃ��\���̂��쐬
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

    //�d������������̌��ɐ���������v���O����
    bool CreateUniqueNameJSON(std::string filename, std::string& str)
    {
        // �����̃L�[�̃J�E���g��ێ�����}�b�v
        std::map<std::string, int> keyCountMap;

        //fileName�̃t�@�C�����̃t�@�C�����Ȃ�������
        std::ifstream file(filename);
        if (!file.good())
        {
            //�t�@�C�������
            if (!CreateJSONFile(filename))
            {
                return false;
            }
        }

        Document data;
        //�t�@�C�����J���Ȃ�������false��Ԃ�
        if (!LoadJSONFromFile(filename.c_str(), data))
        {
            return false;
        }

        // JSON�I�u�W�F�N�g���̊����̃L�[���J�E���g
        for (auto it = data.MemberBegin(); it != data.MemberEnd(); ++it) {
            const std::string existingKey = it->name.GetString();
            keyCountMap[existingKey]++;
        }

        // �d�������L�[������ꍇ�A������t�����ă��j�[�N�ȃL�[���쐬
        std::string uniqueStr = str;
        int suffix = 1;
        while (keyCountMap.find(uniqueStr) != keyCountMap.end()) {
            uniqueStr = str + std::to_string(suffix);
            suffix++;
        }
        str = uniqueStr;
        return true;
    }

    // �V�[���𕶎��ɕϊ�
    std::string SceneToString(CanParentObj parent)
    {
        if (parentStrList.size() >= parent)
        {
            return parentStrList[parent];
        }
        return "";
    }

    //�{�^���𕶎��ɕϊ�
    std::string ButtonToString(ButtonManager::ButtonKinds button)
    {
        if (buttonStrList.size() >= button)
        {
            return buttonStrList[button];
        }
        return "";
    }

    //�������V�[���ɕϊ�
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

    /// �������{�^���ɕϊ�
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
//// JSON�z��̓ǂݍ��݂Ə���
   //if (document.HasMember("numbers") && document["numbers"].IsArray()) {
   //    const Value& numbersArray = document["numbers"];
   //    for (SizeType i = 0; i < numbersArray.Size(); i++) {
   //        if (numbersArray[i].IsNumber()) {
   //            double number = numbersArray[i].GetDouble();
   //            std::cout << "Number at index " << i << ": " << number << std::endl;
   //        }
   //    }
   //}


      // // �t�@�C�����J��
      // FILE* fp;
      // if (fopen_s(&fp, filename.c_str(), "r") != 0)
      // {
      //     MessageBox(NULL, "error", "BaseProjDx9�G���[", MB_OK);
      // }
      // // �t�@�C������ǂݍ���
      // string str;
      //// char readBuffer[65536];
      // FileReadStream is(fp, &str.front(), SHRT_MAX);
      // Document doc;
      // doc.ParseStream(is);
      // document.ParseStream(is);
      // dataList.insert(std::make_pair( list.at(filename), doc ));
      // // �t�@�C�������
      // if(fp != nullptr)
      //// fclose(fp);
      // // �ǂݍ��݂������������ǂ�����Ԃ�
      // return !document.HasParseError() && document.IsObject();
       // �t�@�C�����J��

//// JSON�t�@�C���ɏ�������(�ǋL�A���������j
//bool AppendToJSONFileFloat(const std::string& filename, const std::string& section, const std::string& key, float value)
//{
//    //�t�@�C���̓��e�𕶎���Ƃ��ēǂݍ���
//    std::string str = "";
//    //���s������false��Ԃ�
//    if (!LoadJSONString(filename, str))
//    {
//        return false;
//    }
//
//    // JSON�f�[�^���p�[�X����
//    // �p�[�X�@�f�[�^����͂��K�v�ȃf�[�^�����o������
//    Document document;
//    //���s������false��Ԃ�
//    if (document.Parse(str.c_str()).HasParseError()) {
//        return false;
//    }
//
//    // �V�����l��ǉ��܂��͏㏑������
//    if (!document.IsObject()) {
//        return false;
//    }
//
//    // �I�u�W�F�N�g���Ɋ��ɓ����L�[�����݂���ꍇ�͏㏑���A�����łȂ��ꍇ�͒ǉ�����
//    Document::AllocatorType& allocator = document.GetAllocator();
//    if (document.HasMember(key.c_str())) {
//        document[key.c_str()] = value;
//    }
//    else {
//        Value newValueObj(value);
//        document.AddMember(Value(key.c_str(), allocator).Move(), newValueObj, allocator);
//    }
//
//    // �X�V���ꂽJSON�f�[�^�𕶎���ɕϊ�����
//    StringBuffer buffer;
//    Writer<StringBuffer> writer(buffer);
//    document.Accept(writer);
//    std::string updatedJsonStr = buffer.GetString();
//
//    // JSON�t�@�C�����㏑������
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