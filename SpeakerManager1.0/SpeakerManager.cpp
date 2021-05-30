#include "SpeakerManager.h"

#include <deque>
#include <numeric>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <functional>
//���캯��
SpeakerManager::SpeakerManager(){
	//��ʼ������������
	this->initSpeaker();

	//��ʼ�� 12 ��ѡ��
	this->createSpeaker();

	//���������¼
	this->loadRecord();
}

SpeakerManager::~SpeakerManager() = default;

//�˵�����
void SpeakerManager::show_Menu() {
	std::cout << "********************************************" << std::endl;
	std::cout << "*************  ��ӭ�μ��ݽ����� ************" << std::endl;
	std::cout << "*************  1.��ʼ�ݽ�����  *************" << std::endl;
	std::cout << "*************  2.�鿴�����¼  *************" << std::endl;
	std::cout << "*************  3.��ձ�����¼  *************" << std::endl;
	std::cout << "*************  0.�˳���������  *************" << std::endl;
	std::cout << "********************************************" << std::endl;
	std::cout << std::endl;
}

//�˳�ϵͳ
void SpeakerManager::exitSystem() {
	std::cout << "��ӭ�´�ʹ��" << std::endl;
	system("pause");
	exit(0);
}

//��ʼ������������
void SpeakerManager::initSpeaker() {
	this->v1.clear();
	this->v2.clear();
	this->m_Index = 1;
	this->vVictory.clear();
	this->m_Record.clear();
	this->m_Speaker.clear();
}

//��ʼ�� 12 ��ѡ��  
void SpeakerManager::createSpeaker() {
	std::string nameSeed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameSeed.size(); i++) {
		std::string name = "ѡ��";
		name += nameSeed[i];

		//����ѡ��
		Speaker sp(name);

		//����ѡ�ֱ�� ���ҷ��뵽v1������
		this->v1.push_back(i + 10001);

		//ѡ�ֱ���Լ���Ӧѡ�� ���뵽map������
		this->m_Speaker.insert(std::make_pair(i + 10001, sp));
	}
}

//��ʼ����  �����������̿��ƺ���
void SpeakerManager::startSpeaker(){
	//��һ�ֿ�ʼ����
	//1����ǩ
	this->speakerDraw();
	//2������
	this->speakerContest();
	//3����ʾ�������
	this->showScore();

	//�ڶ��ֿ�ʼ����
	this->m_Index++;
	//1����ǩ
	this->speakerDraw();
	//2������
	speakerContest();
	//3����ʾ���ս��
	this->showScore();
	//4������������ļ���
	this->saveRecord();

	//���ñ��� ����ȡ��¼
	//��ʼ������������
	this->initSpeaker();

	//����12��ѡ��
	this->createSpeaker();

	//���������¼
	this->loadRecord();

	std::cout << "���������ϣ�" << std::endl;
	system("pause");
	system("cls");
}

//��ǩ
void SpeakerManager::speakerDraw() {
	std::cout << "�� << " << this->m_Index << " >> �ֱ���ѡ�����ڳ�ǩ" << std::endl;
	std::cout << "--------------------------" << std::endl;
	std::cout << "��ǩ���ݽ�˳�����£� " << std::endl;

	if (this->m_Index == 1) {
		//��һ�ֱ���
		random_shuffle(v1.begin(), v1.end());
		for (std::vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
	else {
		//�ڶ��ֱ���
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

//����
void SpeakerManager::speakerContest() {
	std::cout << "----------- ��" << this->m_Index << " �ֱ�����ʽ��ʼ --------------" << std::endl;

	//׼����ʱ���� ���С��ɼ�
	std::multimap<double, int, std::greater<double>> groupScore;

	int num = 0; //��¼��Ա���� 6��һ��

	std::vector<int> v_Src;//����ѡ������
	if (this->m_Index == 1){
		v_Src = v1;
	}
	else{
		v_Src = v2;
	}

	//��������ѡ�ֽ��б���
	for (std::vector<int>::iterator it = v_Src.begin(); it != v_Src.end(); it++) {
		num++;
		//��ί���
		std::deque<double>d;
		for (int i = 0; i < 10; i++) {
			double score = (rand() % 401 + 600) / 10.f;   // 600 ~ 1000
			//std::cout << score << " ";
			d.push_back(score);
		}
		//std::cout << std::endl;

		sort(d.begin(), d.end(), std::greater<double>());//����
		d.pop_front(); //ȥ����߷�
		d.pop_back(); //ȥ����ͷ�

		double sum = accumulate(d.begin(), d.end(), 0.0f); //�ܷ�
		double avg = sum / (double)d.size();  //ƽ����

		//��ӡƽ����
		//std::cout << "��ţ� " << *it << " ������ " << this->m_Speaker[*it].m_Name << " ��ȡƽ���֣� " << avg << std::endl;

		//��ƽ���ַ��뵽 map������
		this->m_Speaker[*it].m_Score[this->m_Index - 1] = avg;

		//��������� ���뵽��ʱС��������
		groupScore.insert(std::make_pair(avg, *it)); //key�ǵ÷֣�value�Ǿ���ѡ�ֱ��
		//ÿ6��ȡ��ǰ����
		if (num % 6 == 0) {
			std::cout << "��" << num / 6 << "С��������Σ� " << std::endl;
			for (std::multimap<double, int, std::greater<double>>::iterator it = groupScore.begin(); it != groupScore.end(); it++) {
				std::cout << "��ţ� " << it->second << " ������ " << this->m_Speaker[it->second].m_Name << " �ɼ��� "
					<< this->m_Speaker[it->second].m_Score[this->m_Index - 1] << std::endl;
			}

			//ȡ��ǰ����
			int count = 0;
			for (std::multimap<double, int, std::greater<double>>::iterator it = groupScore.begin(); it != groupScore.end() && count < 3; it++, count++) {
				if (this->m_Index == 1) {
					v2.push_back((*it).second);
				}
				else {
					vVictory.push_back((*it).second);
				}
			}

			groupScore.clear(); //С���������
			std::cout << std::endl;

		}
	}

	std::cout << "------------------ ��" << this->m_Index << "�ֱ������ --------------" << std::endl;
	system("pause");

}

//��ʾ�÷�
void SpeakerManager::showScore() {
	std::cout << "------------------ ��" << this->m_Index << "�ֽ���ѡ����Ϣ���£� -------------------" << std::endl;

	std::vector<int>v;
	if (this->m_Index == 1) {
		v = v2;
	}
	else {
		v = vVictory;
	}

	for (std::vector<int>::iterator it = v.begin(); it != v.end(); it++) {
		std::cout << "ѡ�ֱ�ţ� " << *it << " ������ " << this->m_Speaker[*it].m_Name << " �÷֣� " <<
			this->m_Speaker[*it].m_Score[this->m_Index - 1] << std::endl;
	}
	std::cout << std::endl;

	system("pause");
	system("cls");
	this->show_Menu();
}

//�����¼
void SpeakerManager::saveRecord() {
	std::ofstream ofs;
	ofs.open("speaker.csv", std::ios::out | std::ios::app); // ��׷�ӵķ�ʽд�ļ�

	//��ÿ��ѡ������ д�뵽�ļ���
	for (std::vector<int>::iterator it = vVictory.begin(); it != vVictory.end(); it++) {
		ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
	}
	ofs << std::endl;

	//�ر�
	ofs.close();
	std::cout << "��¼�Ѿ�����" << std::endl;

	//�����ļ���Ϊ��״̬
	this->fileIsEmpty = false;
}

//��ȡ��¼
void SpeakerManager::loadRecord() {
	std::ifstream ifs("speaker.csv", std::ios::in); //���ļ�

	if (!ifs.is_open()) {
		this->fileIsEmpty = true;
		//std::cout << "�ļ�������" << std::endl;
		ifs.close();
		return;
	}

	//�ļ�������
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		//std::cout << "�ļ�Ϊ��" << std::endl;
		this->fileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ���Ϊ��
	this->fileIsEmpty = false;

	ifs.putback(ch); // �������ȡ�ĵ����ַ� �Ż���

	std::string data;
	int index = 0;

	while (ifs >> data) {
		//std::cout << data << std::endl;
		//10002,86.675,10009,81.3,10007,78.55,

		std::vector<std::string>v; //���6��string�ַ���

		int pos = -1;//�鵽","λ�õı���
		int start = 0;

		while (true) {
			pos = data.find(",", start);
			if (pos == -1) {
				//û���ҵ����
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
	//	std::cout << it->first << "�ھ���ţ� " << it->second[0] << " ������ " << it->second[1] << std::endl;
	//}
}

//��ʾ�����¼
void SpeakerManager::showRecord() {
	if (this->fileIsEmpty) {
		std::cout << "�ļ�Ϊ�ջ����ļ������ڣ�" << std::endl;
	}
	else {
		for (int i = 0; i < this->m_Record.size(); i++) {
			std::cout << "��" << i + 1 << "�� "
				<< "�ھ���ţ�" << this->m_Record[i][0] << " �÷֣� " << this->m_Record[i][1] << " "
				<< "�Ǿ���ţ�" << this->m_Record[i][2] << " �÷֣� " << this->m_Record[i][3] << " "
				<< "������ţ�" << this->m_Record[i][4] << " �÷֣� " << this->m_Record[i][5] << std::endl;
		}
	}


	system("pause");
	system("cls");
}

//����ļ�
void SpeakerManager::clearRecord() {
	std::cout << "�Ƿ�ȷ������ļ���" << std::endl;
	std::cout << "1����" << std::endl;
	std::cout << "2����" << std::endl;

	int select = 0;

	std::cin >> select;

	if (select == 1) {
		//ȷ�����
		std::ofstream ofs("speaker.csv", std::ios::trunc);
		ofs.close();

		//��ʼ������������
		this->initSpeaker();

		//����12��ѡ��
		this->createSpeaker();

		//���������¼
		this->loadRecord();

		std::cout << "��ճɹ���" << std::endl;
	}

	system("pause");
	system("cls");
}