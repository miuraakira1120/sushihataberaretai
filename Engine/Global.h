#pragma once
#include <iostream>
#include <vector>
#include "Direct3D.h"


//���S�Ƀ��������J�����邽�߂̃}�N��
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

//�z��̗v�f����m�邽�߂̃}�N��
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

