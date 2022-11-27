#include "framework.h"
#include "resource.h"

Question* question = new Question();
Answer* answer = new Answer();

void Answer::setAnswer(const char* detectedText)
{
	for (int i = 0; i < question->vQuestions.size(); i++)
	{
		if (strstr(detectedText, question->vQuestions[0]))
		{
			_answer = vAnswers[i];
		}
		else
		{
			_answer = "Nothing found.";
		}
	}
}

