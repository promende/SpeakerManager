#pragma once
#ifndef _SPEAKER_
#define _SPEAKER_

#include <vector>
#include <string>
//ѡ����
class Speaker{
private:
	static int maxScoreCount;	 //����ܼ�¼ maxScoreCount �α����ɼ�
public:
	std::string m_Name;			 //����
	std::vector<double> m_Score; //����

	//�޲ι��캯��
	Speaker();

	//�вι��캯��
	Speaker(std::string, std::vector<double> = {});

	//��������
	~Speaker();
};


#endif