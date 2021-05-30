#pragma once 
#ifndef _SPEAKERMANAGER_
#define _SPEAKERMANAGER_

#include "speaker.h"

#include <map>
#include <vector>
#include <string>
//ѡ�ֹ�����
class SpeakerManager{
public:
	//���캯��
	SpeakerManager();

	//��������
	~SpeakerManager();

	//�˵�����
	void show_Menu();

	//�˳�ϵͳ
	void exitSystem();

	//��ʼ������������
	void initSpeaker();

	//����12��ѡ��
	void createSpeaker();

	//��ʼ����
	void startSpeaker();

	//��ǩ
	void speakerDraw();

	//����
	void speakerContest();

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

	//��ű������� 
	int m_Index;

	//�����һ�ֱ���ѡ�ֱ������
	std::vector<int>v1;

	//��һ�ֽ���ѡ�ֱ������
	std::vector<int>v2;

	//ʤ��ǰ����ѡ�ֱ������
	std::vector<int>vVictory;

	//��ű���Լ���Ӧ����ѡ������
	std::map<int, Speaker>m_Speaker;

	//�ж��ļ��Ƿ�Ϊ��
	bool fileIsEmpty;

	//��������¼������
	std::map<int, std::vector<std::string>>m_Record;
};

#endif