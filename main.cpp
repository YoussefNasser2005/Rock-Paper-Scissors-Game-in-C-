#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };
enum enWinner { Player1 = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
    short RoundNumber = 0;
    enGameChoice Player1Choice;
    enGameChoice ComputerChoice;
    enWinner Winner;
    string WinnerName;
};

struct stGameResults
{
    short GameRounds = 0;
    short Player1WinTimes = 0;
    short ComputerWinTimes = 0;
    short DrawTimes = 0;
    enWinner GameWinner;
    string WinnerName = "";
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

enGameChoice GetComputerChoice()
{
    return (enGameChoice)RandomNumber(1, 3);
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
    if (RoundInfo.Player1Choice == RoundInfo.ComputerChoice)
        return enWinner::Draw;

    switch (RoundInfo.Player1Choice)
    {
    case enGameChoice::Stone:
        return (RoundInfo.ComputerChoice == enGameChoice::Paper) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Paper:
        return (RoundInfo.ComputerChoice == enGameChoice::Scissors) ? enWinner::Computer : enWinner::Player1;
    case enGameChoice::Scissors:
        return (RoundInfo.ComputerChoice == enGameChoice::Stone) ? enWinner::Computer : enWinner::Player1;
    }
}

enWinner WhoWonTheGame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes) return enWinner::Player1;
    else if (ComputerWinTimes > Player1WinTimes) return enWinner::Computer;
    else return enWinner::Draw;
}

string ChoiceName(enGameChoice Choice)
{
    string arrGameChoices[3] = { "Stone", "Paper", "Scissors" };
    return arrGameChoices[Choice - 1];
}

string WinnerName(enWinner Winner)
{
    string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
    return arrWinnerName[Winner - 1];
}

enGameChoice ReadPlayer1Choice()
{
    short Choice;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 3);
    return (enGameChoice)Choice;
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
    cout << "\n____________ Round [" << RoundInfo.RoundNumber << "] ____________\n\n";
    cout << "Player1 Choice: " << ChoiceName(RoundInfo.Player1Choice) << endl;
    cout << "Computer Choice: " << ChoiceName(RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
    cout << "_________________________________________\n" << endl;
}

stGameResults PlayGame(short HowManyRounds)
{
    stRoundInfo RoundInfo;
    short Player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;

    for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins:\n";
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.Player1Choice = ReadPlayer1Choice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.Winner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        if (RoundInfo.Winner == enWinner::Player1)
        {
            Player1WinTimes++;
            system("color 2F");
        }
        else if (RoundInfo.Winner == enWinner::Computer)
        {
            ComputerWinTimes++;
            system("color 4F");
        }
        else
        {
            DrawTimes++;
            system("color 6F");
        }

        PrintRoundResults(RoundInfo);

        cout << "\nPress any key to continue to next round...";
        system("pause >nul");
    }

    return { HowManyRounds, Player1WinTimes, ComputerWinTimes, DrawTimes, WhoWonTheGame(Player1WinTimes, ComputerWinTimes), WinnerName(WhoWonTheGame(Player1WinTimes, ComputerWinTimes)) };
}

void ShowFinalResults(stGameResults Results)
{
    if (Results.GameWinner == enWinner::Player1)
        system("color 2F");
    else if (Results.GameWinner == enWinner::Computer)
        system("color 4F");
    else
        system("color 6F");

    system("cls");
    cout << "\n\n\n\t\t\t=========== Final Game Results ===========\n\n";
    cout << "\t\t\tTotal Rounds        : " << Results.GameRounds << endl;
    cout << "\t\t\tPlayer1 Wins        : " << Results.Player1WinTimes << endl;
    cout << "\t\t\tComputer Wins       : " << Results.ComputerWinTimes << endl;
    cout << "\t\t\tDraws              : " << Results.DrawTimes << endl;
    cout << "\t\t\tFinal Winner        : " << Results.WinnerName << endl;
    cout << "\n\t\t\t==========================================\n";
}

short HowManyRounds()
{
    short NumberOfRounds;
    cout << "How Many Of Rounds You Want To Play? ";
    cin >> NumberOfRounds;
    return NumberOfRounds;
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        system("cls");
        stGameResults GameResults = PlayGame(HowManyRounds());
        ShowFinalResults(GameResults);

        cout << "\nDo you want to play again? (Y/N): ";
        cin >> PlayAgain;

        system("color 07");

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
