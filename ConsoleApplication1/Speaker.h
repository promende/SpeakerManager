#pragma once
#ifndef _SPEAKER_
#define _SPEAKER_

#include <vector>
#include <string>
//选手类
class Speaker{
private:
	static int maxScoreCount;	 //最多能记录 maxScoreCount 次比赛成绩
public:
	std::string m_Name;			 //姓名
	std::vector<double> m_Score; //分数

	//无参构造函数
	Speaker();

	//有参构造函数
	Speaker(std::string, std::vector<double> = {});

	//析构函数
	~Speaker();
};


#endif