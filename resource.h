#pragma once


class Question
{
public:
	std::vector<const char*> vQuestions = { "What is the purpose of the OSI physical layer" };
};

class Answer
{
public:
	const char* _answer = "No answer or question found";
	void setAnswer(const char* detectedText);

	std::vector<const char*> vAnswers = { "transmitting bits across the local media" };
};


extern Question* question;
extern Answer* answer;

