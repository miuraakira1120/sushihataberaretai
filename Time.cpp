//#include "Time.h"
//#include <vector>
//
////�萔�錾
//namespace
//{
//	//60�i�@
//	const char HEX = 60;
//	const unsigned int TIMER_MAX = 100;
//}
//
////�ϐ�
//namespace
//{
//	char Hours_;
//	char Minuts_;
//	std::vector<double> Seconds_[TIMER_MAX];
//	bool Lock_ = true;		//���݂̏�ԂŌŒ肷�邩
//	std::vector<int> CountFps_;	//���݂̃t���[�����[�g���i�[���Ă�������
//	int FPS_;		//���������ɍő�t���[�����[�g���i�[���Ă���
//	int LookAt_;	//�z��̂ǂ������邩
//	float fps[TIMER_MAX]; 
//	std::vector<int> timer; //�e�^�C�}�[
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
//		CountFps_.clear();		//�O�̂��߂̏�����
//		CountFps_.reserve(FPS);	//�v�f�����m�ۂ��Ă���
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
//			//�ő�t���[�����[�g�𒴂��邱�Ƃ͂Ȃ��̂�
//			if (CountFps_.at(i) < FPS_)
//				CountFps_.at(i)++;
//		}
//
//		LookAt_++;
//		if (LookAt_ >= FPS_)
//			LookAt_ -= FPS_;
//
//		//Lock����Ă�����X�V���Ȃ�
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