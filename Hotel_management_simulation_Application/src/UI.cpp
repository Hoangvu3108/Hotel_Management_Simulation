#include "../inc/UI.hpp"
#include <iostream>

int UI:: getUserChoice(const string & prompt)
    {
        int choice;
        std :: cout << prompt;
        std :: cin >> choice;
        return choice;
    }
float UI :: getUserChoiceFloat(const string & prompt)
    {
        float choice;
        std :: cout << prompt;
        std :: cin >> choice;
        return choice;
    }
void UI :: displayMessage (const string & message)
    {
        std :: cout << message << std :: endl; // Displays a message to the user
    }
string  UI:: getUserInput (const string & prompt)
    {
        std :: string input;
        std :: cout << prompt;
        std :: cin >> input;
        return input; // Returns the user input 
    }
