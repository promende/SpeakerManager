#include "SpeakerManager.h"

#include <ctime>
#include <vector>
#include <string>
#include <iostream>
int main(){
	srand((unsigned int)time(NULL));//随机数种子
	SpeakerManager manager;			//创建管理类对象

	int choice = 0;					//用于存储用户输入
	while (true) {
		manager.show_Menu();

		std::cout << "请输入您的选择： " << std::endl;
		std::cin >> choice;

		switch (choice) {
		case 1: // 开始比赛
			manager.startSpeaker();
			break;
		case 2: //查看往届比赛记录
			manager.showRecord();
			break;
		case 3:  //清空比赛记录
			manager.clearRecord();
			break;
		case 0:  //退出系统
			manager.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}

	system("pause");

	return 0;
}