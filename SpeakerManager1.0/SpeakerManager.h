#pragma once 
#ifndef _SPEAKERMANAGER_
#define _SPEAKERMANAGER_

#include "speaker.h"

#include <map>
#include <vector>
#include <string>
//选手管理类
class SpeakerManager{
public:
	//构造函数
	SpeakerManager();

	//析构函数
	~SpeakerManager();

	//菜单功能
	void show_Menu();

	//退出系统
	void exitSystem();

	//初始化容器和属性
	void initSpeaker();

	//创建12名选手
	void createSpeaker();

	//开始比赛
	void startSpeaker();

	//抽签
	void speakerDraw();

	//比赛
	void speakerContest();

	//显示得分
	void showScore();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	//显示往届记录
	void showRecord();

	//清空文件
	void clearRecord();

	//存放比赛轮数 
	int m_Index;

	//保存第一轮比赛选手编号容器
	std::vector<int>v1;

	//第一轮晋级选手编号容器
	std::vector<int>v2;

	//胜出前三名选手编号容器
	std::vector<int>vVictory;

	//存放编号以及对应具体选手容器
	std::map<int, Speaker>m_Speaker;

	//判断文件是否为空
	bool fileIsEmpty;

	//存放往届记录的容器
	std::map<int, std::vector<std::string>>m_Record;
};

#endif