//#include "Time.h"
//#include <vector>
//
////定数宣言
//namespace
//{
//	//60進法
//	const char HEX = 60;
//	const unsigned int TIMER_MAX = 100;
//}
//
////変数
//namespace
//{
//	char Hours_;
//	char Minuts_;
//	std::vector<double> Seconds_[TIMER_MAX];
//	bool Lock_ = true;		//現在の状態で固定するか
//	std::vector<int> CountFps_;	//現在のフレームレートを格納しておくもの
//	int FPS_;		//初期化時に最大フレームレートを格納しておく
//	int LookAt_;	//配列のどこを見るか
//	float fps[TIMER_MAX]; 
//	std::vector<int> timer; //各タイマー
//}
//
//namespace Time
//{
//	void Initialize(int FPS)
//	{
//		Hours_ = 0;
//		Minuts_ = 0;
//		for (int i = 0; i < TIMER_MAX; i++)
//		{
//			Seconds_[i] = 0;
//		}
//		FPS_ = FPS;
//		LookAt_ = 0;
//
//		CountFps_.clear();		//念のための初期化
//		CountFps_.reserve(FPS);	//要素数を確保しておく
//
//		while (CountFps_.size() != CountFps_.capacity())
//		{
//			CountFps_.push_back(FPS);
//		}
//	}
//
//	void Update()
//	{
//		for (int i = 0; i < CountFps_.size(); i++)
//		{
//			//最大フレームレートを超えることはないので
//			if (CountFps_.at(i) < FPS_)
//				CountFps_.at(i)++;
//		}
//
//		LookAt_++;
//		if (LookAt_ >= FPS_)
//			LookAt_ -= FPS_;
//
//		//Lockされていたら更新しない
//		for (int i = 0; i < TIMER_MAX; i++)
//		{
//			if (!Lock_)
//			{
//				fps[i] = CountFps_.at(LookAt_) * 0.98f;
//				Seconds_[i] += 1.0 / fps[i];
//			}
//		}
//		CountFps_.at(LookAt_) = 0;
//	}
//
//	void Reset(int ID)
//	{
//		if (ID >= TIMER_MAX)
//		{
//			return;
//		}
//		Hours_ = 0;
//		Minuts_ = 0;
//		Seconds_[ID] = 0;
//	}
//
//	void Lock(int ID)
//	{
//		if (ID >= TIMER_MAX)
//		{
//			return;
//		}
//		Lock_ = true;
//	}
//
//	void UnLock(int ID)
//	{
//		if (ID >= TIMER_MAX)
//		{
//			return;
//		}
//		Lock_ = false;
//	}
//
//	int GetTimei(int ID)
//	{
//		if (ID >= TIMER_MAX)
//		{
//			return -1;
//		}
//		return (int)Seconds_[ID];
//	}
//	float GetTimef(int ID)
//	{
//		if (ID >= TIMER_MAX)
//		{
//			return -1;
//		}
//		return (float)Seconds_[ID];
//	}
//	double GetTime(int ID)
//	{
//		if (ID >= TIMER_MAX)
//		{
//			return -1;
//		}
//		return Seconds_[ID];
//	}
//	int GetTimerID()
//	{
//		TimerID++;
//		return TimerID - 1;
//	}
//}