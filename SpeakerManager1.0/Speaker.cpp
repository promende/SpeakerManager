#include "Speaker.h"

//��̬��Ա�����ĳ�ʼ��
int Speaker::maxScoreCount = 100;

//���캯��
Speaker::Speaker() :m_Name(""), m_Score({}) {
	m_Score.resize(maxScoreCount);
}

//���캯��
Speaker::Speaker(std::string name, std::vector<double> score) : m_Name(name), m_Score(score) {
	m_Score.resize(maxScoreCount);
}

//��������
Speaker::~Speaker() = default;