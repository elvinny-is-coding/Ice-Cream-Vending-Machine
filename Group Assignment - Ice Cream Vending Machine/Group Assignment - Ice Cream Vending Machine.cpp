/*
    Group Assignment - Ice Cream Vending Machine
    This program emulates an automated machine which is intended to provide
    the users with a diverse range of products based on the amount of money
    inserted and selection of the product
*/
//Include header that are needed for program to run
#include <iostream>
#include <windows.h>
#include <regex>
#include <iomanip>
#include <fstream>

//Allow std namespace be used without prefix
using namespace std;

//Declare the variable for each ice cream flavor
string iceCreamFlavour[] = { "matcha", "chocolate", "vanilla", "strawberry", "chocolateMint" };
double iceCreamPrice[] = { 3  , 3.5 , 1.75 , 2 , 5 };
int iceCreamQuantity[] = { 35 , 20 , 35 , 45 , 15 };
int iceCreamChosen[] = { 0 , 0 , 0 , 0 ,0 };
int iceCreamID[] = { 1, 2, 3, 4, 5 };

//Initialize variable to determine which ice cream flavor is chosen, and how many.
int ICSelectedFlavour;
int ICSelectedAmount;
string ICDecision;
double paymentTotal;
string paymentMethod;
double paymentAmount;
double paymentRefund;

//To clear screen
void clearScreen()
{
    system("cls");
}


//To change font color
void fontColor(int colour)
{
    //Change font color according to C++ text colouring
    HANDLE hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colour);
}

//Display main menu
void mainMenu()
{
    fontColor(3);
    cout << "  _                                                          " << endl
        << " (_)                                                         " << endl
        << "  _    ___    ___      ___   _ __    ___    __ _   _ __ ___  " << endl
        << " | |  / __|  / _ \\    / __| | '__|  / _ \\  / _` | | '_ ` _ \\ " << endl;
    fontColor(7);
    cout << " | | | (__  |  __/   | (__  | |    |  __/ | (_| | | | | | | |" << endl
        << " |_|  \\___|  \\___|    \\___| |_|     \\___|  \\__,_| |_| |_| |_|" << endl << endl << endl;

    fontColor(3);
    cout << "Choice" << "\t" << "Selection" << "\t\t" << "Price" << "\t\t\t" << "Amount" << endl << endl;

    //Set ice cream price to display 2 decimal point
    cout << setprecision(2) << fixed;

    fontColor(7);
    //For matcha flavor
    cout << iceCreamID[0] << "\t" << iceCreamFlavour[0] << "\t\t\t" << "$" << iceCreamPrice[0] << "\t\t" << "(" << iceCreamQuantity[0] << ")" << " Remaining" << endl;

    //For chocolate flavor
    cout << iceCreamID[1] << "\t" << iceCreamFlavour[1] << "\t\t" << "$" << iceCreamPrice[1] << "\t\t" << "(" << iceCreamQuantity[1] << ")" << " Remaining" << endl;

    //For vanilla flavor
    cout << iceCreamID[2] << "\t" << iceCreamFlavour[2] << "\t\t\t" << "$" << iceCreamPrice[2] << "\t\t" << "(" << iceCreamQuantity[2] << ")" << " Remaining" << endl;

    //For strawberry flavor
    cout << iceCreamID[3] << "\t" << iceCreamFlavour[3] << "\t\t" << "$" << iceCreamPrice[3] << "\t\t" << "(" << iceCreamQuantity[3] << ")" << " Remaining" << endl;

    //For chocolateMint flavor
    cout << iceCreamID[4] << "\t" << iceCreamFlavour[4] << "\t\t" << "$" << iceCreamPrice[4] << "\t\t" << "(" << iceCreamQuantity[4] << ")" << " Remaining" << endl << endl;

    fontColor(7);
}

//Sucessful payment
void paymentReceived()
{
    clearScreen();
    mainMenu();
    fontColor(7);
    cout << endl << "Processing payment.";
    Sleep(1000);

    clearScreen();
    mainMenu();
    fontColor(8);
    cout << endl << "Processing payment..";
    Sleep(1000);

    clearScreen();
    mainMenu();
    fontColor(7);
    cout << endl << "Processing payment...";
    Sleep(1000);

    clearScreen();
    mainMenu();
    cout << endl << "Payment received! Enjoy your ice cream <3";
    Sleep(5000);
    clearScreen();
}

int ICSelectedFlavorCheckSelect(int ICSelectedFlavour)
{
    //Check if selection made is within the choice
    while (ICSelectedFlavour > 5 || ICSelectedFlavour < 1 || cin.fail() || ICSelectedFlavour == 0)
    {
        //Refresh screen
        clearScreen();
        mainMenu();

        if (ICSelectedFlavour > 5)
        {
            //Clear input stream to prevent loops
            cin.clear();
            cin.ignore(INT_MAX, '\n');

            cout << endl << "ERROR : Selection cannot be greater than 5" << endl << endl
                << "Please choose between 1 - 5" << endl;
            cin >> ICSelectedFlavour;
        }
        else if (cin.fail())
        {
            //Clear input stream to prevent loops and clear fail bit
            cin.clear();
            cin.ignore(INT_MAX, '\n');

            cout << endl << "ERROR : Invalid choice is entered" << endl << endl
                << "Please choose between 1 - 5" << endl;
            cin >> ICSelectedFlavour;
        }
        else if (ICSelectedFlavour == 0 && cin.fail() == false)
        {
            //Clear input stream to prevent loops
            cin.clear();
            cin.ignore(INT_MAX, '\n');

            cout << endl << "0 Exit code is entered. "
                << "Program will begin to terminate." << endl;
            Sleep(2000);
            exit(0);
        }
        else if (ICSelectedFlavour < 1)
        {
            //Clear input stream to prevent loops
            cin.clear();
            cin.ignore(INT_MAX, '\n');

            cout << endl << "ERROR : Selection cannot be smaller than 1" << endl << endl
                << "Please choose between 1 - 5" << endl;
            cin >> ICSelectedFlavour;
        }
        else
        {
            cout << endl << "ERROR : Unknown error has occured!"
                << endl << "Program will terminate gracefully." << endl;
            exit(1);
        }
    }
    //Refresh screen
    clearScreen();
    mainMenu();
    return ICSelectedFlavour;
}

int ICSelectedAmountCheck(int ICSelectedAmount, int ICSelectedAmountLeft)
{
    while (ICSelectedAmount == 0 || cin.fail() || ICSelectedAmount < 0 || ICSelectedAmount > ICSelectedAmountLeft)
    {
        //Refresh screen
        clearScreen();
        mainMenu();

        if (cin.fail())
        {
            //Clear input stream to prevent loops
            cin.clear();
            cin.ignore(INT_MAX, '\n');

            cout << endl << "ERROR : Invalid value is entered";
            cout << endl << endl << "Please enter a valid value between 1 - " << ICSelectedAmountLeft << endl;
            cin >> ICSelectedAmount;
            continue;
        }
        else if (ICSelectedAmount == 0 && cin.fail() == false)
        {
            //Clear input stream to prevent loops
            cin.clear();
            cin.ignore(INT_MAX, '\n');

            cout << endl << "ERROR : Quantity of ice cream cannot be 0";
            cout << endl << endl << "Please enter a valid value between 1 - " << ICSelectedAmountLeft << endl;
            cin >> ICSelectedAmount;
            continue;
        }
        else if (ICSelectedAmount < 0)
        {
            //Clear input stream to prevent loops
            cin.clear();
            cin.ignore(INT_MAX, '\n');

            cout << endl << "ERROR : Quantity of ice cream cannot be a negative value";
            cout << endl << endl << "Please enter a valid value between 1 - " << ICSelectedAmountLeft << endl;
            cin >> ICSelectedAmount;
            continue;
        }
        else if (ICSelectedAmount > ICSelectedAmountLeft)
        {
            //Clear input stream to prevent loops
            cin.clear();
            cin.ignore(INT_MAX, '\n');

            cout << endl << "ERROR : The quantity of ice cream selected "
                << "cannot be greater than " << ICSelectedAmountLeft << endl;
            cout << endl << "Please enter a value between 1 - " << ICSelectedAmountLeft << endl;
            cin >> ICSelectedAmount;
            continue;
        }
    }
    //Refresh screen
    clearScreen();
    mainMenu();
    return ICSelectedAmount;
}

string selectionIceCreamYesNoCheck(string YN)
{
    while (true)
    {
        clearScreen();
        mainMenu();
        if ((regex_match(YN, regex("[Nn][Oo]"))) || YN == "1" || (regex_match(YN, regex("[Yy][Ee][Ss]"))) || YN == "0")
        {
            break;
        }
        else
        {
            cout << endl << "ERROR : Invalid choice is entered, please reenter your choice." << endl;
            cout << endl << "Enter 1 or Yes to add to cart.";
            cout << endl << "Enter 0 or No to checkout." << endl;
            cin >> YN;
            continue;
        }
    }
    return YN;
}

string paymentMethodCheck(string paymentMethod)
{
    while (true)
    {
        clearScreen();
        mainMenu();
        if (regex_match(paymentMethod, regex("[Cc][Aa][Rr][Dd]")))
            break;
        else if (regex_match(paymentMethod, regex("[Cc][Aa][Ss][Hh]")))
            break;
        else
        {
            cout << endl << "ERROR : Invalid payment method. Please enter a valid payment method." << endl;
            cout << endl << "Please enter cash or card" << endl;
            cin >> paymentMethod;
        }
    }
    return paymentMethod;
}


int main()
{
    while (true)
    {
        //Display main menu
        mainMenu();

        //exit
        fontColor(3);
        cout << "Enter 0 to exit" << endl << endl;
        fontColor(7);

        //Start of selection menu
        do
        {
            cout << endl << "Please select your choice of ice cream." << endl;
            cin >> ICSelectedFlavour;

            while (true)
            {
                ICSelectedFlavour = ICSelectedFlavorCheckSelect(ICSelectedFlavour);

                if (ICSelectedFlavour == 1)
                {
                    if (iceCreamQuantity[0] == 0)
                    {
                        cout << endl << "ERROR : The " << iceCreamFlavour[0] << " flavour is not currently available";
                        cout << endl << endl << "Please try other flavors instead." << endl;
                        cin >> ICSelectedFlavour;
                        continue;
                    }
                    else
                        break;
                }
                if (ICSelectedFlavour == 2)
                {
                    if (iceCreamQuantity[1] == 0)
                    {
                        cout << endl << "ERROR : The " << iceCreamFlavour[1] << " flavour is not currently available";
                        cout << endl << endl << "Please try other flavors instead." << endl;
                        cin >> ICSelectedFlavour;
                        continue;
                    }
                    else
                        break;
                }
                if (ICSelectedFlavour == 3)
                {
                    if (iceCreamQuantity[2] == 0)
                    {
                        cout << endl << "ERROR : The " << iceCreamFlavour[2] << " flavour is not currently available";
                        cout << endl << endl << "Please try other flavors instead." << endl;
                        cin >> ICSelectedFlavour;
                        continue;
                    }
                    else
                        break;
                }
                if (ICSelectedFlavour == 4)
                {
                    if (iceCreamQuantity[3] == 0)
                    {
                        cout << endl << "ERROR : The " << iceCreamFlavour[3] << " flavour is not currently available";
                        cout << endl << endl << "Please try other flavors instead." << endl;
                        cin >> ICSelectedFlavour;
                        continue;
                    }
                    else
                        break;
                }
                if (ICSelectedFlavour == 5)
                {
                    if (iceCreamQuantity[4] == 0)
                    {
                        cout << endl << "ERROR : The " << iceCreamFlavour[4] << " flavour is not currently available";
                        cout << endl << endl << "Please try other flavors instead." << endl;
                        cin >> ICSelectedFlavour;
                        continue;
                    }
                    else
                        break;
                }
            }

            cout << endl << "How many do you want?" << endl;
            cin >> ICSelectedAmount;

            switch (ICSelectedFlavour)
            {
            case 1:
                ICSelectedAmount = ICSelectedAmountCheck(ICSelectedAmount, iceCreamQuantity[0]);
                iceCreamChosen[0] += ICSelectedAmount;
                iceCreamQuantity[0] -= ICSelectedAmount;
                cout << endl << "You have chosen x" << ICSelectedAmount << " " << iceCreamFlavour[0] << endl;
                break;
            case 2:
                ICSelectedAmount = ICSelectedAmountCheck(ICSelectedAmount, iceCreamQuantity[1]);
                iceCreamChosen[1] += ICSelectedAmount;
                iceCreamQuantity[1] -= ICSelectedAmount;
                cout << endl << "You have chosen x" << ICSelectedAmount << " " << iceCreamFlavour[1] << endl;
                break;
            case 3:
                ICSelectedAmount = ICSelectedAmountCheck(ICSelectedAmount, iceCreamQuantity[2]);
                iceCreamChosen[2] += ICSelectedAmount;
                iceCreamQuantity[2] -= ICSelectedAmount;
                cout << endl << "You have chosen x" << ICSelectedAmount << " " << iceCreamFlavour[2] << endl;
                break;
            case 4:
                ICSelectedAmount = ICSelectedAmountCheck(ICSelectedAmount, iceCreamQuantity[3]);
                iceCreamChosen[3] += ICSelectedAmount;
                iceCreamQuantity[3] -= ICSelectedAmount;
                cout << endl << "You have chosen x" << ICSelectedAmount << " " << iceCreamFlavour[3] << endl;
                break;
            case 5:
                ICSelectedAmount = ICSelectedAmountCheck(ICSelectedAmount, iceCreamQuantity[4]);
                iceCreamChosen[4] += ICSelectedAmount;
                iceCreamQuantity[4] -= ICSelectedAmount;
                cout << endl << "You have chosen x" << ICSelectedAmount << " " << iceCreamFlavour[4] << endl;
                break;
            }

            //Refresh screen
            Sleep(2000);
            clearScreen();
            mainMenu();

            cout << endl << "Do you want to choose another ice cream flavour?" << endl;
            cout << endl << "Current items in cart :";

            fontColor(3);
            if (iceCreamChosen[0] >= 1)
            {
                cout << endl << "x" << iceCreamChosen[0] << "\t" << iceCreamFlavour[0];
            }
            if (iceCreamChosen[1] >= 1)
            {
                cout << endl << "x" << iceCreamChosen[1] << "\t" << iceCreamFlavour[1];
            }
            if (iceCreamChosen[2] >= 1)
            {
                cout << endl << "x" << iceCreamChosen[2] << "\t" << iceCreamFlavour[2];
            }
            if (iceCreamChosen[3] >= 1)
            {
                cout << endl << "x" << iceCreamChosen[3] << "\t" << iceCreamFlavour[3];
            }
            if (iceCreamChosen[4] >= 1)
            {
                cout << endl << "x" << iceCreamChosen[4] << "\t" << iceCreamFlavour[4];
            }

            fontColor(7);
            cout << endl << endl << "Enter Yes or 1 to add to cart";
            cout << endl << "Enter No or 0 to checkout" << endl;
            cin >> ICDecision;

            //Refresh screen
            clearScreen();
            mainMenu();

            ICDecision = selectionIceCreamYesNoCheck(ICDecision);

            if (regex_match(ICDecision, regex("[Nn][Oo]")) || regex_match(ICDecision, regex("[0]")))
                break;

        } while (regex_match(ICDecision, regex("[Yy][Ee][Ss]")) || regex_match(ICDecision, regex("[1]")));


        for (int counter = 0; iceCreamID[counter] < sizeof(iceCreamID); counter++)
        {
            paymentTotal += iceCreamChosen[counter] * iceCreamPrice[counter];
        }

        clearScreen();
        mainMenu();

        cout << endl << "Do you want to pay with cash or card?" << endl;
        cin >> paymentMethod;

        paymentMethod = paymentMethodCheck(paymentMethod);

        clearScreen();
        mainMenu();

        if (regex_match(paymentMethod, regex("[Cc][Aa][Rr][Dd]")))
        {
            cout << endl << "You have chosen card payment method!" << endl;
            Sleep(2000);
            clearScreen();
            mainMenu();
            cout << endl << "Balanced required : $ " << paymentTotal;
            cout << endl << "Balanced given    : $ " << paymentAmount << endl;
            cout << endl << "How much do you wish to pay?" << endl;
            cin >> paymentAmount;

            while (paymentAmount < paymentTotal || paymentAmount == 0 || cin.fail() || paymentAmount < 0)
            {
                clearScreen();
                mainMenu();

                if (paymentAmount == 0 && cin.good())
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');

                    cout << endl << "ERROR : Payment given cannot be zero" << endl;
                    cout << endl << "Balanced required : $ " << paymentTotal;
                    cout << endl << "Balanced given    : $ " << paymentAmount;
                    cout << endl << "Please enter adequate funds for payment" << endl;
                    cin >> paymentAmount;
                    continue;
                }
                if (paymentAmount < 0)
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');

                    cout << endl << "ERROR : Payment given cannot be a negative value" << endl;
                    cout << endl << "Balanced required : $ " << paymentTotal;
                    cout << endl << "Balanced given    : $ " << paymentAmount;
                    cout << endl << "Please enter adequate funds for payment" << endl;
                    cin >> paymentAmount;
                    continue;
                }
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');

                    cout << endl << "ERROR : An invalid value is given" << endl;
                    cout << endl << "Balanced required : $ " << paymentTotal;
                    cout << endl << "Balanced given    : $ " << paymentAmount;
                    cout << endl << "Please enter adequate funds for payment" << endl;
                    cin >> paymentAmount;
                    continue;
                }
                if (paymentAmount < paymentTotal)
                {
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');

                    cout << endl << "ERROR : Payment failed due to insufficient funds" << endl;
                    cout << endl << "Balanced required : $ " << paymentTotal;
                    cout << endl << "Balanced given    : $ " << paymentAmount;
                    cout << endl << "Please enter adequate funds for payment" << endl;
                    cin >> paymentAmount;
                    continue;
                }
                else
                {
                    cout << endl << "ERROR : An unknown error has occured!" << endl
                        << "Terminating program as a failsafe.";
                    Sleep(2000);
                    exit(1);
                }
            }

            paymentRefund = paymentAmount - paymentTotal;

            if (paymentAmount > paymentTotal)
            {
                clearScreen();
                mainMenu();
                cout << endl << "Excess amount is paid.";
                cout << endl << "Refunding $" << paymentRefund << " back to card..." << endl;
                Sleep(2000);
            }
        }

        if (regex_match(paymentMethod, regex("[Cc][Aa][Ss][Hh]")))
        {
            cout << endl << "You have chosen cash payment method!" << endl;
            Sleep(2000);
            clearScreen();
            mainMenu();
            cout << endl << "Balanced required : $ " << paymentTotal;
            cout << endl << "Balanced given    : $ " << paymentAmount << endl;
            cout << endl << "How much do you wish to pay?" << endl;
            cin >> paymentAmount;

            while (paymentAmount < paymentTotal)
            {
                while (paymentAmount < paymentTotal || paymentAmount == 0 || cin.fail() || paymentAmount < 0)
                {
                    clearScreen();
                    mainMenu();

                    if (paymentAmount == 0 && cin.good())
                    {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');

                        cout << endl << "ERROR : Payment given cannot be zero" << endl;
                        cout << endl << "Balanced required : $ " << paymentTotal;
                        cout << endl << "Balanced given    : $ " << paymentAmount;
                        cout << endl << "Please enter adequate funds for payment" << endl;
                        cin >> paymentAmount;
                        continue;
                    }
                    if (paymentAmount < 0)
                    {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');

                        cout << endl << "ERROR : Payment given cannot be a negative value" << endl;
                        cout << endl << "Balanced required : $ " << paymentTotal;
                        cout << endl << "Balanced given    : $ " << paymentAmount;
                        cout << endl << "Please enter adequate funds for payment" << endl;
                        cin >> paymentAmount;
                        continue;
                    }
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');

                        cout << endl << "ERROR : An invalid value is given" << endl;
                        cout << endl << "Balanced required : $ " << paymentTotal;
                        cout << endl << "Balanced given    : $ " << paymentAmount;
                        cout << endl << "Please enter adequate funds for payment" << endl;
                        cin >> paymentAmount;
                        continue;
                    }
                    if (paymentAmount < paymentTotal)
                    {
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');

                        cout << endl << "ERROR : Payment failed due to insufficient funds" << endl;
                        cout << endl << "Balanced required : $ " << paymentTotal;
                        cout << endl << "Balanced given    : $ " << paymentAmount;
                        cout << endl << "Please enter adequate funds for payment" << endl;
                        cin >> paymentAmount;
                        continue;
                    }
                    else
                    {
                        cout << endl << "ERROR : An unknown error has occured!" << endl
                            << "Terminating program as a failsafe.";
                        Sleep(2000);
                        exit(1);
                    }
                }
            }

            paymentRefund = paymentAmount - paymentTotal;

            if (paymentAmount > paymentTotal)
            {
                clearScreen();
                mainMenu();
                cout << endl << "Excess amount is paid.";
                cout << endl << "Refunding $" << paymentRefund << " by cash..." << endl;
                Sleep(2000);
            }
        }

        ofstream receipt;
        receipt.open("Receipt.txt", ios::out);

        if (!receipt)
        {
            cout << "ERROR : Could not produce a receipt";
            exit(1);
        }

        receipt << setprecision(2) << fixed;

        receipt << "Receipt" << endl;

        if (iceCreamChosen[0] >= 1)
        {
            receipt << endl << "x" << iceCreamChosen[0] << " " << iceCreamFlavour[0] << "\t\t\t\t: $ " << iceCreamChosen[0] * iceCreamPrice[0];
        }
        if (iceCreamChosen[1] >= 1)
        {
            receipt << endl << "x" << iceCreamChosen[1] << " " << iceCreamFlavour[1] << "\t\t\t: $ " << iceCreamChosen[1] * iceCreamPrice[1];
        }
        if (iceCreamChosen[2] >= 1)
        {
            receipt << endl << "x" << iceCreamChosen[2] << " " << iceCreamFlavour[2] << "\t\t\t\t: $ " << iceCreamChosen[2] * iceCreamPrice[2];
        }
        if (iceCreamChosen[3] >= 1)
        {
            receipt << endl << "x" << iceCreamChosen[3] << " " << iceCreamFlavour[3] << "\t\t\t: $ " << iceCreamChosen[3] * iceCreamPrice[3];
        }
        if (iceCreamChosen[4] >= 1)
        {
            receipt << endl << "x" << iceCreamChosen[4] << " " << iceCreamFlavour[4] << "\t\t: $ " << iceCreamChosen[4] * iceCreamPrice[4];
        }

        receipt << endl << endl << "Total Cost \t\t\t: $ " << paymentTotal << endl;
        receipt << "Total payment \t\t: $ " << paymentAmount << endl;
        receipt << "Change \t\t\t\t: $ " << paymentRefund << endl;

        receipt.close();

        //Reset value
        for (int counter = 0; iceCreamChosen[counter] < sizeof(iceCreamChosen); counter++)
        {
            iceCreamChosen[counter] = 0;
        }

        paymentTotal = 0;
        paymentAmount = 0;

        clearScreen();
        paymentReceived();

    }
}
