#ifndef UI_HPP
#define UI_HPP
#include "Std_Types.hpp"
class UI
{
    public:
        static int getUserChoice(const string& prompt); // Displays the main menu and returns the user's choice
        static float getUserChoiceFloat(const string &propmt); // Displays the main menu and returns the user's choice as a float
        static void displayMessage(const string &message); // Displays a message to the user
        static string getUserInput(const string &prompt); // Gets user input from the console
};
#endif // UI_HPP