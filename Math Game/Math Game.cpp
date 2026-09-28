
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enQuestionLevel {Easy = 1, Med = 2, Hard = 3, LMix = 4};

enum enOperationType {Add = 1, Sub = 2, Mul = 3, Div = 4, OpMix = 5};

enum enPassFail {Pass = 1, Fail = 2};

struct stQustionInfo
{
    short QuestionNumber, TotalQuestionNumber;
    int Num1, Num2, RightAnswer, Answer;
    enOperationType Operation;
    enQuestionLevel Level;

};

struct stGameResult
{
    short RightAnswers, WrongAnswers, TotalQuestions;
    enQuestionLevel Lvl;
    enOperationType OpType;
    enPassFail PassFail;
};

short ReadQuestionsNumber()
{
    short Num = 1;

    do
    {
        cout << "How Many Questions You Want To Answer ?? ";
        cin >> Num;

    } while (Num <= 0);

    return Num;
}

int ReadUserAnswer()
{
    int Answer = 0;

    cin >> Answer;

    return Answer;
}

int RandomNumber(int From, int To)
{
    return ((rand() % (To - From + 1)) + From);
}

enOperationType ReadOperation()
{
    short Op = 2;

    do
    {
        cout << "Enter Operation Type : Add [1], Sub [2], Mul [3], Div [4], Mix [5] : ";
        cin >> Op;

    } while (Op > 5 || Op < 1);

    return enOperationType(Op);
}

enQuestionLevel ReadLevel()
{
    short Level = 1;

    do
    {
        cout << "Enter Questions Level : Easy [1], Med [2], Hard [3], Mix [4] : ";
        cin >> Level;

    } while (Level > 4 || Level < 1);

    return enQuestionLevel(Level);
}

enPassFail CheckPassFail(short RightAnswers, short WrongAnswers)
{
    if (RightAnswers > WrongAnswers)
        return enPassFail::Pass;
    else
        return enPassFail::Fail;
}

int GenerateNumber(stQustionInfo Question)
{
  
    switch (Question.Level)
    {
    case enQuestionLevel::Easy:
        return RandomNumber(1, 10);
        break;
    case enQuestionLevel::Med:
        return RandomNumber(11, 50);
        break;
    case enQuestionLevel::Hard:
        return RandomNumber(51, 100);
        break;
    }
        
}

int GetQuestionRightAnswer(stQustionInfo Question)
{
    switch (Question.Operation)
    { 
    case enOperationType::Add:
        return Question.Num1 + Question.Num2;
        break;
    case enOperationType::Mul:
        return Question.Num1 * Question.Num2;
        break;
    case enOperationType::Div:
        return Question.Num1 / Question.Num2;
        break;
    case enOperationType::Sub:
        return Question.Num1 - Question.Num2;
        break;
    }
}

char GetOperationType(stQustionInfo Question)
{
   
    switch (Question.Operation)
    {
    case enOperationType::Add:
        return '+';
        break;
    case enOperationType::Div:
        return '/';
        break;
    case enOperationType::Mul:
        return '*';
        break;
    case enOperationType::Sub:
        return '-';
        break;
    }
}

bool CheckAnswer(stQustionInfo Question)
{
    if (Question.Answer == Question.RightAnswer)
    {
        system("color 2F");
        cout << "Right Answer :)\n\n" << endl;
        return 1;
    }
    else
    {
        system("color 4F");
        cout << "\aWrong Answer :(  The Right Answer Is : " << Question.RightAnswer << "\n\n" << endl;
        return 0;
    }
}

void PrintQuestion(stQustionInfo Question)
{
    cout << "\nQuestion " << Question.QuestionNumber << "/" << Question.TotalQuestionNumber << endl;

    cout << Question.Num1 << endl;
    cout << GetOperationType(Question) << endl;
    cout << Question.Num2 << endl;

    cout << "-------------" << endl;
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void PrintGameOver()
{
    cout << "\n\n----------------------------------------------------";
    cout << "\n\n----------------------GameOver----------------------";
    cout << "\n\n----------------------------------------------------";
}

void PrintFinalResults(stGameResult Game)
{
    cout << "\n-----------------Game Results-----------------" << endl;

    if (Game.PassFail == enPassFail::Pass)
    {
        system("color 2F");
        cout << "                 You Passed                   " << endl;
    }
    else
    {
        system("color 4F");
        cout << "                 You Failed                   " << endl;
    }
    
    cout <<   "----------------------------------------------" << endl;

    cout << "Number Of Questions     : " << Game.TotalQuestions << endl;

    cout << "Question Level          : ";

    switch (Game.Lvl)
    {
    case enQuestionLevel::Easy:
        cout << "Easy" << endl;
        break;
    case enQuestionLevel::Med:
        cout << "Medium" << endl;
        break;
    case enQuestionLevel::Hard:
        cout << "Hard" << endl;
        break;
    case enQuestionLevel::LMix:
        cout << "Mix" << endl;
        break;
    }

    cout << "Operation Type          : ";

    switch (Game.OpType)
    {
    case enOperationType::Add:
        cout << "Add" << endl;
        break;
    case enOperationType::Sub:
        cout << "Subtract" << endl;
        break;
    case enOperationType::Mul:
        cout << "Mutibly" << endl;
        break;
    case enOperationType::Div:
        cout << "Divide" << endl;
        break;
    case enOperationType::OpMix:
        cout << "Mix" << endl;
        break;
    }

    cout << "Number Of Right Answers : " << Game.RightAnswers << endl;
    cout << "Number Of Wrong Answers : " << Game.WrongAnswers << endl;
}

stGameResult FillGameResult(short RightAnswers, short WrongAnswers, enOperationType Operation, enQuestionLevel Lvl)
{
    stGameResult Game;

    Game.RightAnswers = RightAnswers;
    Game.WrongAnswers = WrongAnswers;
    Game.Lvl = Lvl;
    Game.OpType = Operation;

    return Game;
}

stGameResult PlayGame() 
{
    stQustionInfo Question;
    stGameResult Game;

    short RightAnswers = 0, WrongAnswers = 0;

    Question.TotalQuestionNumber = ReadQuestionsNumber();
    Game.Lvl = ReadLevel();
    Game.OpType = ReadOperation();

    for (short QuestionNumber = 1; QuestionNumber <= Question.TotalQuestionNumber; QuestionNumber++)
    {
        
        
        if (Game.OpType == enOperationType::OpMix)
            Question.Operation = enOperationType(RandomNumber(1, 4));
        else
            Question.Operation = Game.OpType;


        if (Game.Lvl == enQuestionLevel::LMix)
            Question.Level = enQuestionLevel(RandomNumber(1, 3));
        else
            Question.Level = Game.Lvl;

        Question.QuestionNumber = QuestionNumber;
        Question.Num1 = GenerateNumber(Question);
        Question.Num2 = GenerateNumber(Question);
        Question.RightAnswer = GetQuestionRightAnswer(Question);

        PrintQuestion(Question);

        Question.Answer = ReadUserAnswer();

       

        if (CheckAnswer(Question))
            RightAnswers++;
        else
            WrongAnswers++;
    }

    Game = FillGameResult(RightAnswers, WrongAnswers, Game.OpType, Game.Lvl);
    Game.PassFail = CheckPassFail(RightAnswers, WrongAnswers);
    Game.TotalQuestions = Question.TotalQuestionNumber;
    
    return Game;
}

void StartGames()
{
    char Again = 'Y';
    stGameResult Game;

    do
    {
        ResetScreen();
        Game = PlayGame();
        PrintGameOver();

        PrintFinalResults(Game);

        cout << "\n\nDo You Want To Play Again [Y][N] ??  ";
        cin >> Again;

    } while (Again == 'Y' || Again == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGames();

    return 0;
}

