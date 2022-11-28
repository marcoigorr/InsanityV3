#pragma once


class Question
{
public:
	std::vector<const char*> vQuestions = { "During a routine inspection" };
};

class Answer
{
public:
	std::string _answer;
	void setAnswer(const char* detectedText);

	std::vector<std::string> vAnswers = { "spyware" };
};


extern Question* question;
extern Answer* answer;

