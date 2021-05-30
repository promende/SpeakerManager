#include "Speaker.h"

//静态成员变量的初始化
int Speaker::maxScoreCount = 100;

//构造函数
Speaker::Speaker() :m_Name(""), m_Score({}) {
	m_Score.resize(maxScoreCount);
}

//构造函数
Speaker::Speaker(std::string name, std::vector<double> score) : m_Name(name), m_Score(score) {
	m_Score.resize(maxScoreCount);
}

//析构函数
Speaker::~Speaker() = default;