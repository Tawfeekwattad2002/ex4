



#include <stdio.h>
#include <string.h>


/***************************
******** Menu Items ********
****************************/

#define REVERSE 1
#define PALINDROME 2
#define SENTENCES 3
#define ZIP 4
#define SUDOKU 5
#define EXIT 6


/***************************
*** DIMENSION PARAMETERS ***
****************************/

#define LONGEST_TERM 20
#define LONGEST_SENTENCE 62
#define MAX_NUMBER_OF_TERMS 10

#define ZIP_MAX_GRID_SIZE 20

#define SUDOKU_GRID_SIZE 9
#define SUDOKU_SUBGRID_SIZE 3


/***************************
* USER INTEFACE PROTOTYPES *
****************************/

void task1ReversePhrase();
void task2CheckPalindrome();
void task3GenerateSentences();
void task4SolveZipBoard();
void task5SolveSudoku();


/****************************
* IMPLEMENTATION PROTOTYPES *
*****************************/

void task1ReversePhraseImplementation();
int task2CheckPalindromeImplementation(int);
void task3GenerateSentencesImplementation(char[][LONGEST_TERM+1], int, char[][LONGEST_TERM+1], int,
                                            char[][LONGEST_TERM+1], int);
int task4SolveZipBoardImplementation(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                        char[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], int, int, int, int);
int task5SolveSudokuImplementation(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);


/******************************
* HELPER FUNCTIONS PROTOTYPES *
*******************************/

int readTerms(char[][LONGEST_TERM+1], int, char[]);
void printSudoku(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);
int solveZipHelper(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],char[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],int,int,int,int,int,int,int);
int checkRow(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int,int,int);
int checkCol(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int,int,int);
int checkBox(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int,int,int,int);
int isValid(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int,int,int);
int solveSudokuHelper(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int,int);
int tryNumber(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int,int);

/******************************
********** MAIN MENU **********
*******************************/

int main()
{
    int task;
    do
    {
        printf("Please choose a task (1-5) or 6 to exit:\n");
        printf("%d. Reverse a phrase\n", REVERSE);
        printf("%d. Check Palindrome\n", PALINDROME);
        printf("%d. Generate sentences\n", SENTENCES);
        printf("%d. Solve Zip Board\n", ZIP);
        printf("%d. Solve Sudoku\n", SUDOKU);
        printf("%d. Exit\n", EXIT);

        scanf(" %d", &task);
        scanf("%*c");
        switch (task)
        {
        case REVERSE:
            task1ReversePhrase();
            break;
        case PALINDROME:
            task2CheckPalindrome();
            break;
        case SENTENCES:
            task3GenerateSentences();
            break;
        case ZIP:
            task4SolveZipBoard();
            break;
        case SUDOKU:
            task5SolveSudoku();
            break;
        case EXIT:
            printf("Goodbye!\n");
            break;
        default:
            printf("Please choose a task number from the list.\n");
            break;
        }
        printf("\n=============================\n\n");
    } while (task != EXIT);

    return 0;
}


/***************************
****** USER INTERFACE ******
****************************/


void task1ReversePhrase()
{
    printf("Please insert the phrase to reverse:\n");
    task1ReversePhraseImplementation();
    printf("\n");
}


void task2CheckPalindrome()
{
    printf("Please insert the phrase length:\n");
    int n;
    scanf("%d", &n);
    printf("Please insert the phrase to check:\n");
    scanf(" ");
    if (task2CheckPalindromeImplementation(n))
        printf("The phrase is a palindrome.\n");
    else
        printf("The phrase is not a palindrome.\n");
}


void task3GenerateSentences()
{
    char subjects[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    char verbs[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    char objects[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    int subjectsCount, verbsCount, objectsCount;

    subjectsCount=readTerms(subjects, MAX_NUMBER_OF_TERMS, "subjects");
    verbsCount=readTerms(verbs, MAX_NUMBER_OF_TERMS, "verbs");
    objectsCount=readTerms(objects, MAX_NUMBER_OF_TERMS, "objects");
    printf("List of Sentences:\n");
    task3GenerateSentencesImplementation(subjects, subjectsCount, verbs, verbsCount, objects, objectsCount);
}


void task4SolveZipBoard()
{
    int size;
    int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    int row, col;
    int highest=0;
    printf("Please enter the board size:\n");
    scanf("%d", &size);
    if (size < 1 || size > ZIP_MAX_GRID_SIZE)
    {
        printf("Invalid board size.\n");
        return;
    }

    printf("Please enter the grid:\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 1)
            {
                row = i;
                col = j;
            }
            if(board[i][j]>highest){
                highest=board[i][j];
            }
        }
    }
    if (task4SolveZipBoardImplementation(board, solution, size, row, col, highest))
    {
        printf("Solution:\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%c ", solution[i][j] ? solution[i][j] : 'X');
            }
            printf("\n");
        }
    }
    else
    {
        printf("No solution exists.\n");
    }
}


void task5SolveSudoku()
{
    printf("Please enter the sudoku board:\n");
    int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE] = {0};
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }
    if (task5SolveSudokuImplementation(board))
    {
        printf("Solution found:\n");
        printSudoku(board);
    }
    else
    {
        printf("No solution exists.\n");
    }
}


/***************************
********* HELPERS **********
****************************/


int readTerms(char terms[][LONGEST_TERM+1], int maxNumOfTerms, char type[]){
    int termsCount;
    printf("Please insert number of %s:\n", type);
    scanf("%d", &termsCount);
    if(termsCount < 1 || termsCount > maxNumOfTerms){
        termsCount = maxNumOfTerms;
    }
    printf("Please insert the list of %s:\n", type);
    for(int i=0;i<termsCount;i++){
        printf("%d. ",i+1);
        scanf(" %[^\n]",terms[i]);
    }
    return termsCount;
}

int checkRow(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int row,int num,int col){
    if (col>=SUDOKU_GRID_SIZE)
        return 1;
    if (board[row][col]==num)
        return 0;
    return checkRow(board,row,num,col+1);
}

int checkCol(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int col,int num,int row){
    if (row>=SUDOKU_GRID_SIZE)
        return 1;
    if (board[row][col]==num)
        return 0;
    return checkCol(board,col,num,row+1);
}

int checkBox(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int startRow,int startCol,int num,int pos){
    if (pos>=9)
        return 1;
    int row=startRow+pos/3;
    int col=startCol+pos%3;
    if (board[row][col]==num)
        return 0;
    return checkBox(board,startRow,startCol,num,pos+1);
}

int isValid(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int row,int col,int num){
    int boxStartRow=(row/3)*3;
    int boxStartCol=(col/3)*3;
    return checkRow(board,row,num,0)&&
           checkCol(board,col,num,0)&&
           checkBox(board,boxStartRow,boxStartCol,num,0);
}

int tryNumber(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int pos,int num){
    int row=pos/9;
    int col=pos%9;

    if (num>9)
        return 0;
    if (isValid(board,row,col,num)){
        board[row][col]=num;
        if (solveSudokuHelper(board, pos + 1, 1))
            return 1;
        board[row][col]=0;
    }
    return tryNumber(board,pos,num+1);
}

int solveSudokuHelper(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE],int pos,int num){
    if (pos>=81)
        return 1;
    int row=pos/9;
    int col=pos%9;

    if (board[row][col]!=0)
        return solveSudokuHelper(board, pos + 1, 1);
    return tryNumber(board, pos, num);
}

void printSudoku(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE])
{
    printf("+-------+-------+-------+\n");
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        printf("| ");
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            if (board[i][j] == 0)
                printf(". ");
            printf("%d ", board[i][j]);

            if ((j + 1) % SUDOKU_SUBGRID_SIZE == 0)
                printf("| ");
        }
        printf("\n");
        if ((i + 1) % SUDOKU_SUBGRID_SIZE == 0)
            printf("+-------+-------+-------+\n");
    }
}
int solveZipHelper(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                   char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                   int size,int row,int col,int visited,int nextRequired,int highest,int dir){

    if (visited==size*size){
        if (board[row][col]==highest){
            solution[row][col]='X';
            return 1;
        }
        return 0;
    }

    if (dir>=4){
        return 0;
    }

    int newR,newC;
    char dirChar;

    if (dir==0){
        newR=row-1;
        newC=col;
        dirChar='U';
    } else if (dir==1){
        newR=row+1;
        newC=col;
        dirChar='D';
    } else if (dir==2){
        newR=row;
        newC=col-1;
        dirChar='L';
    } else {
        newR=row;
        newC=col+1;
        dirChar='R';
    }
    if (newR>=0&&newR<size&&newC>=0&&newC<size&&solution[newR][newC]==0){

        int newNextRequired=nextRequired;
        int validMove=1;

        if (board[newR][newC]>0){
            if (board[newR][newC]!=nextRequired){
                validMove=0;
            } else {
                newNextRequired++;
            }
        }

        if (validMove){
            solution[row][col]=dirChar;
            if (solveZipHelper(board,solution,size,newR,newC,visited+1,newNextRequired,highest,0)){
                return 1;
            }
            solution[row][col]=0;
        }
    }
    return solveZipHelper(board,solution,size,row,col,visited,nextRequired,highest,dir+1);
}
/***************************
*********** TODO ***********
****************************/


void task1ReversePhraseImplementation(){
     static int printed=0;

    if (!printed){
        printed=1;
        printf("The reversed phrase is:\n");
    }
    char c=getchar();
    if (c!='\n' && c!=EOF) {
        task1ReversePhraseImplementation();
        putchar(c);
    }
    else printed=0;
}


int task2CheckPalindromeImplementation(int length){
    if (length<=0){
        return 1;
    }
    if (length==1){
        getchar();
        return 1;
    }
    char first=getchar();
    int middle=task2CheckPalindromeImplementation(length - 2);
    char last=getchar();

    return (first==last)&&middle;
}


void task3GenerateSentencesImplementation(char subjects[][LONGEST_TERM+1], int subjectsCount,
                                            char verbs[][LONGEST_TERM+1], int verbsCount,
                                            char objects[][LONGEST_TERM+1], int objectsCount) {
    static int subj=0,verb=0,obj=0,num=1;

    if (subj>=subjectsCount){
        subj=0;
        verb=0;
        obj=0;
        num=1;
        return;
    }

    printf("%d. %s %s %s\n",num++,subjects[subj],verbs[verb],objects[obj]);
    obj++;
    if (obj>=objectsCount) {
        obj=0;
        verb++;
        if (verb>=verbsCount){
            verb=0;
            subj++;
        }
    }
        task3GenerateSentencesImplementation(subjects,subjectsCount,verbs,verbsCount,objects,objectsCount);
    }

int task4SolveZipBoardImplementation(int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                    char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                    int size, int startR, int startC, int highest){
    return solveZipHelper(board,solution,size,startR,startC,1,2,highest,0);
}


int task5SolveSudokuImplementation(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]){
    return solveSudokuHelper(board,0,1);
}