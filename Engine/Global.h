#pragma once
#include <iostream>
#include <vector>
#include "Direct3D.h"


//安全にメモリを開放するためのマクロ
#define SAFE_DELETE(p) {if ((p)!=nullptr) { delete (p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if ((p)!=nullptr) { delete[] (p); (p)=nullptr;}}
#define SAFE_RELEASE(p) {if ((p)!=nullptr) { p->Release(); (p)=nullptr;}}

//配列の要素数を知るためのマクロ
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

