#include "SpeakerManager.h"

#include <deque>
#include <numeric>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
//构造函数
SpeakerManager::SpeakerManager(){
	//初始化容器和属性
	this->initSpeaker();

	//初始化 12 名选手
	this->createSpeaker();

	//加载往届记录
	this->loadRecord();
}

SpeakerManager::~SpeakerManager() = default;

//菜单功能
void SpeakerManager::show_Menu() {
	std::cout << "********************************************" << std::endl;
	std::cout << "*************  欢迎参加演讲比赛 ************" << std::endl;
	std::cout << "*************  1.开始演讲比赛  *************" << std::endl;
	std::cout << "*************  2.查看往届记录  *************" << std::endl;
	std::cout << "*************  3.清空比赛记录  *************" << std::endl;
	std::cout << "*************  0.退出比赛程序  *************" << std::endl;
	std::cout << "********************************************" << std::endl;
	std::cout << std::endl;
}

//退出系统
void SpeakerManager::exitSystem() {
	std::cout << "欢迎下次使用" << std::endl;
	system("pause");
	exit(0);
}

//初始化容器和属性
void SpeakerManager::initSpeaker() {
	this->v1.clear();
	this->v2.clear();
	this->m_Index = 1;
	this->vVictory.clear();
	this->m_Record.clear();
	this->m_Speaker.clear();
}

//初始化 12 名选手  
void SpeakerManager::createSpeaker() {
	std::string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		std::string name = "选手";
		name += nameSeed[i];

		//创建选手
		Speaker sp(name);

		//创建选手编号 并且放入到v1容器中
		this->v1.push_back(i + 10001);

		//选手编号以及对应选手 放入到map容器中
		this->m_Speaker.insert(std::make_pair(i + 10001, sp));
	}
}

//开始比赛  比赛整个流程控制函数
void SpeakerManager::startSpeaker(){
	//第一轮开始比赛
	//1、抽签
	this->speakerDraw();
	//2、比赛
	this->speakerContest();
	//3、显示晋级结果
	this->showScore();

	//第二轮开始比赛
	this->m_Index++;
	//1、抽签
	this->speakerDraw();
	//2、比赛
	speakerContest();
	//3、显示最终结果
	this->showScore();
	//4、保存分数到文件中
	this->saveRecord();

	//重置比赛 ，获取记录
	//初始化容器和属性
	this->initSpeaker();

	//创建12名选手
	this->createSpeaker();

	//加载往届记录
	this->loadRecord();

	std::cout << "本届比赛完毕！" << std::endl;
	system("pause");
	system("cls");
}

//抽签
void SpeakerManager::speakerDraw() {
	std::cout << "第 << " << this->m_Index << " >> 轮比赛选手正在抽签" << std::endl;
	std::cout << "--------------------------" << std::endl;
	std::cout << "抽签后演讲顺序如下： " << std::endl;

	if (this->m_Index == 1) {
		//第一轮比赛
		random_shuffle(v1.begin(), v1.end());
		for (std::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
	else {
		//第二轮比赛
		random_shuffle(v2.begin(), v2.end());
		for (std::vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "--------------------------" << std::endl;
	system("pause");
	std::cout << std::endl;
}

//比赛
void SpeakerManager::speakerContest() {
	std::cout << "----------- 第" << this->m_Index << " 轮比赛正式开始 --------------" << std::endl;

	//准备临时容器 存放小组成绩
	std::multimap<double, int, std::greater<double>> groupScore;

	int num = 0; //记录人员个数 6人一组

	std::vector<int> v_Src;//比赛选手容器
	if (this->m_Index == 1){
		v_Src = v1;
	}
	else{
		v_Src = v2;
	}

	//遍历所有选手进行比赛
	for (std::vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;
		//评委打分
		std::deque<double>d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;   // 600 ~ 1000
			//std::cout << score << " ";
			d.push_back(score);
		}
		//std::cout << std::endl;

		sort(d.begin(), d.end(), std::greater<double>());//排序
		d.pop_front(); //去除最高分
		d.pop_back(); //去除最低分

		double sum = accumulate(d.begin(), d.end(), 0.0f); //总分
		double avg = sum / (double)d.size();  //平均分

		//打印平均分
		//std::cout << "编号： " << *it << " 姓名： " << this->m_Speaker[*it].m_Name << " 获取平均分： " << avg << std::endl;

		//将平均分放入到 map容器里
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//将打分数据 放入到临时小组容器中
		groupScore.insert(std::make_pair(avg, *it)); //key是得分，value是具体选手编号
		//每6人取出前三名
		if (num % 6 == 0) {
			std::cout << "第" << num / 6 << "小组比赛名次： " << std::endl;
			for (std::multimap<double, int, std::greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				std::cout << "编号： " << it->second << " 姓名： " << this->m_Speaker[it->second].m_Name << " 成绩： "
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << std::endl;
			}

			//取走前三名
			int count = 0;
			for (std::multimap<double, int, std::greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++) {
				if (this->m_Index == 1) {
					v2.push_back((*it).second);
				}
				else {
					vVictory.push_back((*it).second);
				}
			}

			groupScore.clear(); //小组容器清空
			std::cout << std::endl;

		}
	}

	std::cout << "------------------ 第" << this->m_Index << "轮比赛完毕 --------------" << std::endl;
	system("pause");

}

//显示得分
void SpeakerManager::showScore() {
	std::cout << "------------------ 第" << this->m_Index << "轮晋级选手信息如下： -------------------" << std::endl;

	std::vector<int>v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}

	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		std::cout << "选手编号： " << *it << " 姓名： " << this->m_Speaker[*it].m_Name << " 得分： " <<
			this->m_Speaker[*it].m_Score[this->m_Index - 1] << std::endl;
	}
	std::cout << std::endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

//保存记录
void SpeakerManager::saveRecord() {
	std::ofstream ofs;
	ofs.open("speaker.csv", std::ios::out | std::ios::app); // 用追加的方式写文件

	//将每个选手数据 写入到文件中
	for (std::vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << std::endl;

	//关闭
	ofs.close();
	std::cout << "记录已经保存" << std::endl;

	//更改文件不为空状态
	this->fileIsEmpty = false;
}

//读取记录
void SpeakerManager::loadRecord() {
	std::ifstream ifs("speaker.csv", std::ios::in); //读文件

	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//std::cout << "文件不存在" << std::endl;
		ifs.close();
		return;
	}

	//文件清空情况
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//std::cout << "文件为空" << std::endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件不为空
	this->fileIsEmpty = false;

	ifs.putback(ch); // 将上面读取的单个字符 放回来

	std::string data;
	int index = 0;

	while (ifs >> data) {
		//std::cout << data << std::endl;
		//10002,86.675,10009,81.3,10007,78.55,

		std::vector<std::string>v; //存放6个string字符串

		int pos = -1;//查到","位置的变量
		int start = 0;

		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				//没有找到情况
				break;
			}
			std::string temp = data.substr(start, pos - start);
			//std::cout << temp << std::endl;
			v.push_back(temp);
			start = pos + 1;
		}

		this->m_Record.insert(make_pair(index, v));
		index++;
	}

	ifs.close();

	//for (map<int, vector<string>>::iterator it = m_Record.begin(); it != m_Record.end(); it++)
	//{
	//	std::cout << it->first << "冠军编号： " << it->second[0] << " 分数： " << it->second[1] << std::endl;
	//}
}

//显示往届记录
void SpeakerManager::showRecord() {
	if (this->fileIsEmpty) {
		std::cout << "文件为空或者文件不存在！" << std::endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			std::cout << "第" << i + 1 << "届 "
				<< "冠军编号：" << this->m_Record[i][0] << " 得分： " << this->m_Record[i][1] << " "
				<< "亚军编号：" << this->m_Record[i][2] << " 得分： " << this->m_Record[i][3] << " "
				<< "季军编号：" << this->m_Record[i][4] << " 得分： " << this->m_Record[i][5] << std::endl;
		}
	}


	system("pause");
	system("cls");
}

//清空文件
void SpeakerManager::clearRecord() {
	std::cout << "是否确定清空文件？" << std::endl;
	std::cout << "1、是" << std::endl;
	std::cout << "2、否" << std::endl;

	int select = 0;

	std::cin >> select;

	if (select == 1) {
		//确认清空
		std::ofstream ofs("speaker.csv", std::ios::trunc);
		ofs.close();

		//初始化容器和属性
		this->initSpeaker();

		//创建12名选手
		this->createSpeaker();

		//加载往届记录
		this->loadRecord();

		std::cout << "清空成功！" << std::endl;
	}

	system("pause");
	system("cls");
}