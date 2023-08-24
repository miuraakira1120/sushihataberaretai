#include <DirectXMath.h>
#include <vector>
#include "Syari.h"
#include "Engine/Model.h"
#include "Stage.h"
#include "Engine/Input.h"
#include "RedBox.h"
#include "BlueBox.h"
#include "Engine/Camera.h"
#include "Maguro.h"
#include <directxmath.h>
#include "Engine/BoxCollider.h"
#include "Goal.h"
#include "Controller.h"
#include "Time.h"
#include "Engine/SceneManager.h"
#include "OBB.h"
#include "Ball.h"
#include "Engine/Global.h"
#include "VFX.h"


using std::vector;

//コンストラクタ
Syari::Syari(GameObject* parent)
    :GameObject(parent, "Syari"), hModel_(-1), mode(1), axisPos(0,0,0),
    prevPos(0.0f, 0.0f, 0.0f), accel(0.0f), jumpSpeed(0), pGauge_(nullptr), isGround(false), 
    prevBonePos(), countTime(0), flipped(XMVECTOR{ 0,0,0,0 }), upDistanceDifference(0,0,0), prevPosMove(0,0,0)
{
}

//デストラクタ
Syari::~Syari()
{
}

//初期化
void Syari::Initialize()
{
    //モデルデータのロード
    hModel_ = Model::Load("syari.fbx");
    //hModel_ = Model::Load("GodSyari.fbx");
    assert(hModel_ >= 0);

    //子オブジェクトの生成
    Instantiate<Maguro>(this);

    //当たり判定の生成
    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
    AddCollider(collision);

    /*transform_.position_.x = 10;
    transform_.position_.y = -10;
    transform_.position_.z = 31;*/

    pGauge_ = Instantiate<Gauge>(this);

    //ポリライン初期化
    pLine = new PoryLine;
    pLine->Load("tex.png");

    
    pGauge_->SetMaxHP(300 * 60);

    transform_.position_.y = -37;
}

//更新
void Syari::Update()
{
    prevPosMove = transform_.position_;
    countTime++;
    //pGauge_->SetNowHP(Time::GetTimei());
    pGauge_->Damage(1);

    if (countTime > 250 * 60)
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_GAMEOVER);
    }

    vMove = { 0,0,0,0 };

    //MoveMouse();
    //キー入力をする
    KeyOperation();


    //各頂点の位置を調べる
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        vertexBonePos[i] = Model::GetBonePosition(hModel_, vertexName[i]);
    }

    Stage* pStage = (Stage*)FindObject("Stage");    //ステージオブジェクトを探す
    int hGroundModel = pStage->GetModelHandle();    //モデル番号を取得

    Goal* pGoal = (Goal*)FindObject("Goal");        //ゴールオブジェクトを探す
    int hGoalModel = pGoal->GetModelHandle();       //モデル番号を取得

    //一番低いところと高いところを探す
    int lowest = 0;
    int highest = 0;
    for (int i = 1; i < sizeof(vertexBonePos) / sizeof(XMFLOAT3); i++)
    {
        if (vertexBonePos[lowest].y > vertexBonePos[i].y)
        {
            lowest = i;
        }
        if (vertexBonePos[highest].y < vertexBonePos[i].y)
        {
            highest = i;
        }
    }

    //一番右と左を探す
    int rightest = 0;
    int leftest = 0;
    for (int i = 1; i < sizeof(vertexBonePos) / sizeof(XMFLOAT3); i++)
    {
        if (vertexBonePos[leftest].x > vertexBonePos[i].x)
        {
            leftest = i;
        }
        if (vertexBonePos[rightest].x < vertexBonePos[i].x)
        {
            rightest = i;
        }
    }

    //一番奥と手前を探す
    int foremost = 0;//奥
    int innermost = 0;//手前
    for (int i = 1; i < sizeof(vertexBonePos) / sizeof(XMFLOAT3); i++)
    {
        if (vertexBonePos[innermost].z > vertexBonePos[i].z)
        {
            innermost = i;
        }
        if (vertexBonePos[foremost].z < vertexBonePos[i].z)
        {
            foremost = i;
        }
    }
    ////////////////////レイを飛ばす/////////////////////

    RayCastData GoalData;                       //シャリの位置からレイを飛ばして、ゴールとぶつかるかを調べる
    GoalData.start = transform_.position_;      //レイの発射位置
    GoalData.dir = XMFLOAT3(0, -1, 0);          //レイの方向
    Model::RayCast(hGoalModel, &GoalData);      //レイを発射

    /////////////////////////////////////////////////////

     //重力
    if (SPEED_LIMIT >= accel)
    {
        accel += FALL_SPEED;
        transform_.position_.y -= accel;
    }
    else
    {
        transform_.position_.y -= SPEED_LIMIT;
    }

    XMFLOAT3 fFlipped;
    XMStoreFloat3(&fFlipped, flipped);
    transform_.position_ = Math::Float3Add( transform_.position_, fFlipped);
    flipped = XMVectorSet(0, 0, 0, 0);
    
    ///////////////レイを飛ばし放題//////////////
    

    //各頂点の位置を調べる
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        vertexBonePos[i] = Model::GetBonePosition(hModel_, vertexName[i]);
    }
    XMFLOAT3 fMoveBonePos[VERTEX_MAX];
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        //過去のボーンの位置からどこに動いたか
        fMoveBonePos[i] = Math::Float3Sub(vertexBonePos[i], prevBonePos[i]);
    }

    RayCastData rayMove[VERTEX_MAX];

    for (int i = 0; i < VERTEX_MAX; i++)
    {
        rayMove[i].start = prevBonePos[i];   //レイの発射位置
        rayMove[i].dir = fMoveBonePos[i];       //レイの方向
        Model::RayCast(hGroundModel, &rayMove[i]); //レイを発射
    }

    for (int i = 0; i < VERTEX_MAX; i++)
    {
        XMVECTOR vMoveBonePos = XMLoadFloat3(&fMoveBonePos[i]);
        float moveLength = XMVectorGetX(XMVector3Length(vMoveBonePos));
        if (rayMove->hit && rayMove->dist < moveLength)
        {
            XMVECTOR vRay;
            vRay = XMVector3Normalize(XMLoadFloat3(&rayMove[i].start));
            vRay *= rayMove->dist;
            XMFLOAT3 fRay;
            XMStoreFloat3(&fRay, vRay);
            transform_.position_.x += fRay.x;
            transform_.position_.z += fRay.z;
        }
    }

    /////////////////////////////////////////////
   
    transform_.SetRotateMode(TRANS_NONROTATE);
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
    //各軸に対するベクトルを求める
    XMMATRIX rotateX, rotateY, rotateZ;
    rotateX = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
    rotateY = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
    rotateZ = XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));
    XMMATRIX m = rotateZ * rotateX * rotateY;

    XMFLOAT3 fUpVec = { 0, SYARI_SIZE_Y, 0 }; 
    XMVECTOR vUpVec = XMLoadFloat3(&fUpVec);
    vUpVec = XMVector3TransformCoord(vUpVec, m);	//ベクトルvBoneDirを行列ｍで変形
    vUpVec += vPos;
    XMStoreFloat3(&fUpVec, vUpVec);
    vUpVec -= vPos;

    XMFLOAT3 fBoneDirVec;
    XMStoreFloat3(&fBoneDirVec, - vUpVec);
    RayCastData GroundData;                       //シャリの位置からレイを飛ばして、ゴールとぶつかるかを調べる
    GroundData.start = transform_.position_;      //レイの発射位置
    GroundData.dir = fBoneDirVec;          //レイの方向
    Model::RayCast(hGroundModel, &GroundData);      //レイを発射

    XMVECTOR nor = XMVector3Normalize(GroundData.normal); //法線
    XMVECTOR up = XMVector3Normalize(vUpVec);  //上ベクトル

    if (XMVectorGetX(nor) != XMVectorGetX(up) || XMVectorGetY(nor) != XMVectorGetY(up) || XMVectorGetZ(nor) != XMVectorGetZ(up))
    {
        //ベクトル間のラジアン角度求める
        float dot = XMVectorGetX(XMVector3Dot(XMVector3Normalize(nor), XMVector3Normalize(up)));

        //外積求める
        XMVECTOR cross = XMVector3Cross(nor, up);

        if (dot >= -1 && dot != 0 && dot <= 1)
        {
            XMMATRIX y;
            y = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
            //回転行列求める
            transform_.changeMatRotate_ = y * XMMatrixRotationAxis(cross, -acos(dot));
        }
    }
    else
    {
        XMMATRIX x, y, z;
        x = XMMatrixRotationX(XMConvertToRadians(transform_.rotate_.x));
        y = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
        z = XMMatrixRotationZ(XMConvertToRadians(transform_.rotate_.z));
        XMMATRIX mat = z * x * y;
        transform_.changeMatRotate_ = mat;
    }

    vector<XMVECTOR> boneDirVec;
    XMFLOAT3 fBoneDir[BONE_DIRECTION_ARRAY_SIZE] =
    {
        {SYARI_SIZE_X, 0, 0},
        {0, SYARI_SIZE_Y, 0},
        {0, 0, SYARI_SIZE_Z},
    };

    for (int i = 0; i < BONE_DIRECTION_ARRAY_SIZE; i++)
    {
        XMVECTOR vBoneDir = XMLoadFloat3(&fBoneDir[i]);
        vBoneDir = XMVector3TransformCoord(vBoneDir, transform_.changeMatRotate_);	//ベクトルvBoneDirを行列ｍで変形
        vBoneDir += vPos;
        XMStoreFloat3(&fBoneDir[i], vBoneDir);

        boneDirVec.push_back(vBoneDir - vPos);
    }
 
    vector<float> fLength;
    for (int i = 0; i < fLength.size() - 1; i++)
    {
        fLength.push_back(XMVectorGetX(XMVector3Length(boneDirVec[i])));
    }

    //各頂点の位置を調べる
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        vertexBonePos[i] = Model::GetBonePosition(hModel_, vertexName[i]);
    }

    XMFLOAT3 fDirection[DIRECTION_MAX] =
    {
        {  0,  1,  0  }, //上
        {  0, -1,  0  }, //下
        { -1,  0,  0  }, //左
        {  1,  0,  0  }, //右
        {  0 , 0, -1  }, //手前
        {  0,  0,  1  }, //奥
        { Math::Float3Sub(vertexBonePos[DOWN_RIGHT_FRONT], transform_.position_)},
        { Math::Float3Sub(vertexBonePos[DOWN_RIGHT_BACK], transform_.position_)},
        { Math::Float3Sub(vertexBonePos[DOWN_LEFT_FRONT], transform_.position_)},
        { Math::Float3Sub(vertexBonePos[DOWN_LEFT_BACK], transform_.position_)}
    };

    //シャリのOBBを設定
    OBB syariOBB;
    syariOBB.SetOBBAll(vPos, boneDirVec, fLength);
    for (int i = 0; i < DIRECTION_MAX; i++)
    {
        //床のOBB衝突判定
        RayCastData syariOBBData;
        syariOBBData.start = transform_.position_;   //レイの発射位置
        syariOBBData.dir   = direction[i];       //レイの方向
        Model::RayCast(hGroundModel, &syariOBBData); //レイを発射
        float length;
        if (syariOBBData.hit && OBBvsPlane(syariOBB, syariOBBData.pos, syariOBBData.normal, &length))
        {
            switch (i)
            {
            case TOP :
                //めり込みを直す
                 transform_.position_.y -= length;
                break;
            case BOTOM:
                //接地フラグを真にする
                isGround = true;
                accel = 0;
                //めり込みを直す
                transform_.position_.y += length;
                break;

            case LEFT :
                //めり込みを直す
                transform_.position_.x += length;
                break;

            case RIGHT :
                //めり込みを直す
                transform_.position_.x -= length;
                break;

            case FRONT :
                //めり込みを直す
                transform_.position_.z += length;
                break;

            case BACK:
                //めり込みを直す
                transform_.position_.z -= length;
                break; 
            default:
                break;
            }
        }
        else
        {
            if (i == BOTOM)
            {
                //接地フラグを偽にする
                isGround = false;
            }
        }
    }
   
    //各頂点の位置を調べる
    for (int i = 0; i < VERTEX_MAX; i++)
    {
        vertexBonePos[i] = Model::GetBonePosition(hModel_, vertexName[i]);
    }

    upDistanceDifference =
    { 
        vertexBonePos[UP_RIGHT_FRONT].y - vertexBonePos[UP_RIGHT_BACK].y,
        0.0f,
        vertexBonePos[UP_RIGHT_FRONT].y - vertexBonePos[UP_LEFT_FRONT].y 
    };

    //ゴールしたら
    if (GoalData.hit && GoalData.dist <= SYARI_SIZE_Y)
    {
        SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
        pSceneManager->ChangeScene(SCENE_ID_GOAL);
    }

    //ポリラインに現在の位置を伝える
    pLine->AddPosition(transform_.position_);

    //動かす前の位置を保存しておく
    prevPos = transform_.position_;
    for (int i = 0; i < VERTEX_MAX; i++)
    { 
        prevBonePos[i] = vertexBonePos[i];
    }

    //カメラのコントローラーを探す
    Controller* pController = (Controller*)FindObject("Controller");
    Camera::SetTarget(transform_.position_);
    //pController->SetCameraPos(transform_.position_);
    pController->SetCameraLerpPos(transform_.position_, 0.05f);
    //pController->ChangeFovMove(Math::Float3Comparison(prevPosMove, transform_.position_));
    
}

//描画
void Syari::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);

    //ポリラインを描画
   // pLine->Draw();
}

//開放
void Syari::Release()
{
    pLine->Release();
}

//キー操作
void Syari::KeyOperation()
{
#if _DEBUG
    if (Input::IsKeyDown(DIK_RETURN))
    {
        EmitterData  data;
        data.textureFileName = "PCloud.png";
        data.position = transform_.position_;
        data.delay = 0;
        data.number = 80;
        data.lifeTime = 20;
        data.direction = XMFLOAT3(0, 1, 0);
        data.directionRnd = XMFLOAT3(90, 90, 90);
        data.speed = 0.1f;
        data.speedRnd = 0.8;
        data.size = XMFLOAT2(1, 1);
        data.sizeRnd = XMFLOAT2(0.4, 0.4);
        data.scale = XMFLOAT2(1.05, 1.05);
        data.color = XMFLOAT4(1, 1, 0.1, 1);
        data.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
        VFX::Start(data);	//エミッターを設置
    }
#endif
    ////////移動/////////////

    //左マウスキーを押したとき
    if (Input::IsMouseButton(0) || Input::IsPadButton(XINPUT_GAMEPAD_RIGHT_SHOULDER))
    {
        Controller* pController = (Controller*)FindObject("Controller");
        transform_.rotate_.y = pController->GetRotate().y;
        XMFLOAT3 move = { 0,0,SYARI_SPEED };//プレイヤーの移動ベクトル
        vMove = XMLoadFloat3(&move);//移動ベクトルの型をXMVECTORに変換
        XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
        vMove = XMVector3TransformCoord(vMove, mRotate);
        vMove *= -1;
        Move();
    }

    //右マウスキーを押したとき
    if (Input::IsMouseButton(1) || Input::IsPadButton(XINPUT_GAMEPAD_LEFT_SHOULDER))
    {
        Controller* pController = (Controller*)FindObject("Controller");
        transform_.rotate_.y = pController->GetRotate().y;
        XMFLOAT3 move = { 0,0,SYARI_SPEED };//プレイヤーの移動ベクトル
        vMove = XMLoadFloat3(&move);//移動ベクトルの型をXMVECTORに変換
        XMMATRIX mRotate = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));
        vMove = XMVector3TransformCoord(vMove, mRotate);
        vMove *= 1;
        Move();
    }
    //ジャンプする
    if (Input::IsKeyDown(DIK_SPACE) || Input::IsPadButtonDown(XINPUT_GAMEPAD_B))
    {
        Jump();
    }
}

bool Syari::isFly()
{
    return false;
}

void Syari::MoveMouse()
{
    XMFLOAT3 moveMouse = Input::GetMouseMove();
    transform_.rotate_.x += moveMouse.y * ROTATE_SPEED;
    transform_.rotate_.z += moveMouse.x * ROTATE_SPEED;
}

void Syari::Jump()
{
    if (isGround)
    {
        accel -= SPEED_OF_JUMP;
    }
}

void Syari::Move()
{
    XMStoreFloat3(&fMove, vMove);
    XMVECTOR vPos;
    vPos = XMLoadFloat3(&transform_.position_);//シャリの現在地をXMVECTORに変換
    vPos += vMove;
    XMStoreFloat3(&transform_.position_, vPos);//現在地をtransform_.position_に送る
}

// OBB vs Plane
bool Syari::OBBvsPlane(OBB& obb, XMFLOAT3 planePos, XMVECTOR planeNomal, float* Len)
{
    // 平面の法線に対するOBBの射影線の長さを算出
    FLOAT r = 0.0f;          // 近接距離
    XMVECTOR PlaneNormal = planeNomal; // 平面の法線ベクトル
    for (int i = 0; i < 3; i++) {
        XMVECTOR Direct = obb.GetDirect(i); // OBBの1つの軸ベクトル
        r += fabs(XMVectorGetX(XMVector3Dot((Direct * obb.GetLen_W(i)), PlaneNormal)));
    }

    // 平面とOBBの距離を算出
    XMVECTOR ObbPos = obb.GetPos_W();
    XMVECTOR PlanePos = XMLoadFloat3(&planePos);
    FLOAT s = XMVectorGetX((XMVector3Dot((ObbPos - PlanePos), PlaneNormal)));

    // 戻し距離を算出
    if (Len != NULL) {
        if (s > 0)
            *Len = r - fabs(s);
        else
            *Len = r + fabs(s);
    }

    // 衝突判定
    if (fabs(s) - r < 0.0f)
        return true; // 衝突している

    return false; // 衝突していない
}

//何かに当たった
void Syari::OnCollision(GameObject* pTarget)
{
    //弾に当たったとき
    if (pTarget->GetObjectName() == "Ball")
    {
       XMFLOAT3 tmp;
       XMStoreFloat3(&tmp, pTarget->GetMoved());

       tmp.x *= 2;
       tmp.y *= -1;
       tmp.z *= 2;
       SetFlipped( XMLoadFloat3(&tmp));
    }
}

void Syari::SetFlipped(XMVECTOR fl)
{
    flipped = fl;
}

XMFLOAT3 Syari::GetUpDistanceDifference()
{
    return upDistanceDifference;
}

