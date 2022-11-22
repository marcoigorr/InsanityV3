#include "framework.h"
#include "resource.h"

Question* question = new Question();
Answer* answer = new Answer();

void Answer::setAnswer(const char* detectedText)
{
	for (unsigned int i = 0; i < question->vQuestions.size(); i++)
	{
		if (strstr(question->vQuestions[i], detectedText))
		{
			_answer = vAnswers[i];
		}
	}
}

