#include <iostream>
#include <cstdlib>  
#include <string>
#include <ctime>
using namespace std;

enum enQuestionLvl { easy = 1, med = 2, hard = 3, mixLvl = 4 };

enum enOperationType { add = 1, sub = 2, multiply = 3, divide = 4, mixOp = 5 };  

struct stGameResults
{
    short number_of_questions = 0;
    enQuestionLvl questions_lvl = mixLvl;  
    enOperationType operating_type = mixOp;
    short number_of_right_answers = 0;
    short number_of_wrong_answers = 0;
    bool pass = false;
};

struct stQuestion  
{
    int number1, number2;
    char operater;
    int result;
};

int random(int min, int max) {
    return rand() % (max - min + 1) + min;
}

char randomOperator() {
    char operators[] = { '+', '-', '*', '/' };
    int randomIndex = rand() % 4;
    return operators[randomIndex];
}

short ReadNumberOfQuestions(string msg) {
    short number_of_questions = 0;
    cout << msg << endl;
    cin >> number_of_questions;
    return number_of_questions;
}

enQuestionLvl ReadQuestionLvl() {
    int question_lvl;
    cout << "Enter question level  Level [1] Easy ,Level [2] Med ,Level [3] Hard ,level [4] Mix ?" << endl;
    cin >> question_lvl;

    switch (question_lvl) {
    case 1:
        return easy;
    case 2:
        return med;
    case 3:
        return hard;
    default:
        return mixLvl;  
    }
}

enOperationType ReadOperationType() { 
    int operation_type;
    cout << "Enter Operation type   [1] Add , [2] Sub , [3] Multiply , [4] Divide,[5] Mix ?" << endl;
    cin >> operation_type;

    switch (operation_type) {
    case 1:
        return add;
    case 2:
        return sub;
    case 3:
        return multiply;
    case 4:
        return divide;
    default:
        return mixOp;  
    }
}

stQuestion GenerateQuestion(stGameResults Game_results) {  
    stQuestion Question;  

    
    switch (Game_results.questions_lvl) {
    case easy:
        Question.number1 = random(1, 10);
        Question.number2 = random(1, 10);
        break;
    case med:
        Question.number1 = random(10, 100);
        Question.number2 = random(10, 100);
        break;
    case hard:
        Question.number1 = random(100, 1000);
        Question.number2 = random(100, 1000);
        break;
    case mixLvl:  
        Question.number1 = random(1, 1000);
        Question.number2 = random(1, 1000);
        break;
    }

   
    switch (Game_results.operating_type) {
    case add:
        Question.operater = '+';
        Question.result = Question.number1 + Question.number2;
        break;
    case sub:
        Question.operater = '-';
        Question.result = Question.number1 - Question.number2;
        break;
    case divide:
        Question.operater = '/';
        
        if (Question.number2 == 0) Question.number2 = 1;
        Question.result = Question.number1 / Question.number2;
        break;
    case multiply:
        Question.operater = '*';
        Question.result = Question.number1 * Question.number2;
        break;
    case mixOp:  
        Question.operater = randomOperator();
        switch (Question.operater) {
        case '+':
            Question.result = Question.number1 + Question.number2;
            break;
        case '-':
            Question.result = Question.number1 - Question.number2;
            break;
        case '/':
            
            if (Question.number2 == 0) Question.number2 = 1;
            Question.result = Question.number1 / Question.number2;
            break;
        case '*':
            Question.result = Question.number1 * Question.number2;
            break;
        }
        break;
    }

   
    cout << Question.number1 << endl;
    cout << Question.number2 << endl;
    cout << Question.operater << endl;
    cout << "_____________________" << endl;

    return Question;
}

int ReadUserAnswer() {
    int user_answer;
    cin >> user_answer;
    return user_answer;
}

bool CheckAnswer(stQuestion Question, int user_answer) {  
    if (user_answer == Question.result) {
        cout << "Right Answer :)" << endl;
        system("color 2F");
        
        return true;
    }
    else {
        cout << "Wrong Answer :(" << endl;
        cout << "The right answer is: " << Question.result << endl;
        system("color 4F");
        cout << "\a" << endl;
        return false;
    }
}

stGameResults PlayGame(short number_of_questions) {
    stGameResults Game_results;
    Game_results.number_of_questions = number_of_questions;
    Game_results.questions_lvl = ReadQuestionLvl();
    Game_results.operating_type = ReadOperationType();  // Fixed function name

    for (short i = 0; i < number_of_questions; i++) {
        printf("Question [%d/%d]\n", i + 1, number_of_questions);
        stQuestion Question = GenerateQuestion(Game_results);  // Fixed struct name
        int user_answer = ReadUserAnswer();

        if (CheckAnswer(Question, user_answer)) {
            Game_results.number_of_right_answers++;
        }
        else {
            Game_results.number_of_wrong_answers++;
        }
    }

    
    Game_results.pass = (Game_results.number_of_right_answers >= Game_results.number_of_wrong_answers);
    return Game_results;
}

void PrintGameResults(stGameResults game_results) {
    cout << "____________________________________________" << endl;
    if (game_results.pass) {
        system("color 2F");
        cout << "Final result is pass :)" << endl;
    }
    else {
        system("color 4F");
        cout << "Final result is Fail :(" << endl;
    }
    cout << "____________________________________________" << endl;

    cout << "Number of questions : " << game_results.number_of_questions << endl;
    cout << "Question level : ";
    switch (game_results.questions_lvl) {
    case easy:
        cout << "Easy" << endl;
        break;
    case med:
        cout << "Medium" << endl;
        break;
    case hard:
        cout << "Hard" << endl;
        break;
    case mixLvl:  
        cout << "Mix" << endl;
        break;
    }

    cout << "Operator Type : ";
    switch (game_results.operating_type) {
    case add:
        cout << "Add" << endl;
        break;
    case sub:
        cout << "Sub" << endl;
        break;
    case divide:
        cout << "Divide" << endl;
        break;
    case multiply:
        cout << "Multiply" << endl;
        break;
    case mixOp:  
        cout << "Mix" << endl;
        break;
    }

    cout << "Number of Right answers: " << game_results.number_of_right_answers << endl;
    cout << "Number of Wrong answers: " << game_results.number_of_wrong_answers << endl;
    cout << "______________________________________________________________________" << endl;
}

void Game() {
    char play_again = 'n';
    do {
        system("color 07"); 
        short number_of_questions = ReadNumberOfQuestions("How many questions you want to answer ?");
        stGameResults game_results = PlayGame(number_of_questions);
        PrintGameResults(game_results);
        cout << "Do you want to play again? y/n" << endl;
        cin >> play_again;
        system("cls");
    } while (tolower(play_again) == 'y');
}

int main()
{
    srand((unsigned int)time(0));  
    Game();
    return 0;
}