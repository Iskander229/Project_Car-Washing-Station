#pragma once

#include <iostream>
#include <vector>
#include <functional>

struct ChoiceFormOption {
	std::string content;
	std::function<void()> callback;

	ChoiceFormOption(const std::string& content, const std::function<void()>& callback)
		: content(content), callback(callback)
	{
	}
};

class ChoiceForm
{

private:
	std::string question;
	std::vector<ChoiceFormOption> options;


	void printOptions();

public:
	ChoiceForm(std::string question_);

	void AddChoice(std::string option, std::function<void()> callback);

	void AskUser();
};

