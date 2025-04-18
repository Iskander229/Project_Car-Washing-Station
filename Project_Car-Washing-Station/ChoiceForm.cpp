#include "ChoiceForm.h"
#include <string>
#include <sstream>

void ChoiceForm::printOptions()
{
	for (int i = 0; i < options.size(); i++) {
		std::cout << "    " << (i + 1) << ". " << options.at(i).content << std::endl;
	}
}

ChoiceForm::ChoiceForm(std::string question_)
{
	question = question_;
}


void ChoiceForm::AddChoice(std::string option, std::function<void()> callback)
{
	options.push_back(ChoiceFormOption(option, callback));
}

void ChoiceForm::AskUser()
{
	std::cout << std::endl << question << std::endl;
	printOptions();

    int response = -1;

    while (true) {
        std::string line;
        std::cout << "Enter your choice number: ";
        std::getline(std::cin, line); // Read the whole line
        std::stringstream ss(line); // A handler that takes a line and reads it into different ways
        ss >> response;
        
        // If the user enters wrong data, the response will be -1
        if (response > 0 && response <= options.size()) {
            options.at(response - 1).callback();
            return;
        }
        else {
            std::cout << "Invalid input. Please enter a valid integer." << std::endl;
        }
    }

}
