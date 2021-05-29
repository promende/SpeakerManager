#pragma once 
#ifndef _SPEAKERMANAGER_
#define _SPEAKERMANAGER_

#include <iostream>
#include <vector>
#include <map>
#include "speaker.h"
#include <algorithm>
#include <deque>
#include <functional>
#include <numeric>
#include <string>
#include <fstream>

//����ݽ�������
class SpeakerManager{
public:
	//���캯��
	SpeakerManager();

	//�˵�����
	void show_Menu();

	//�˳�ϵͳ
	void exitSystem();

	//��������
	~SpeakerManager();

	//��ʼ������������
	void initSpeech();

	//����12��ѡ��
	void createSpeaker();

	//��ʼ����  �����������̿��ƺ���
	void startSpeech();

	//��ǩ
	void speechDraw();

	//����
	void speechContest();

	//��ʾ�÷�
	void showScore();

	//�����¼
	void saveRecord();

	//��ȡ��¼
	void loadRecord();

	//��ʾ�����¼
	void showRecord();

	//����ļ�
	void clearRecord();


	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	//��������¼������
	std::map<int, std::vector<std::string>>m_Record;

	//��Ա����
	//�����һ�ֱ���ѡ�ֱ������
	std::vector<int>v1;

	//��һ�ֽ���ѡ�ֱ������
	std::vector<int>v2;

	//ʤ��ǰ����ѡ�ֱ������
	std::vector<int>vVictory;

	//��ű���Լ���Ӧ����ѡ������
	std::map<int, Speaker>m_Speaker;

	//��ű������� 
	int m_Index;

};

#endif