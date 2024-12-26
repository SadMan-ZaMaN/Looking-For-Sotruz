#include "iGraphics.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 500
#define MAX_HIGH_SCORES 5

char userInput[MAX_NAME_LENGTH];
int inputIndex = 0;
bool inputMode = true;
int score = 50;

struct hscore
{
    char name[30];
    int score;
} high_score[MAX_HIGH_SCORES];

int len = 0;

void read_high_scores()
{
    FILE *fp = fopen("Score.txt", "r");
    if (fp != NULL)
    {
        len = 0;
        while (fscanf(fp, "%s %d", high_score[len].name, &high_score[len].score) != EOF && len < MAX_HIGH_SCORES)
        {
            len++;
        }
        fclose(fp);
    }
    else
    {
        printf("Failed to open file.\n");
    }
}

void write_high_scores()
{
    FILE *fp = fopen("Score.txt", "w");
    if (fp != NULL)
    {
        for (int i = 0; i < len; i++)
        {
            fprintf(fp, "%s %d\n", high_score[i].name, high_score[i].score);
        }
        fclose(fp);
    }
    else
    {
        printf("Failed to open file.\n");
    }
}

void add_new_score()
{
    int pos = -1;
    for (int i = 0; i < len; i++)
    {
        if (high_score[i].score < score)
        {
            pos = i;
            break;
        }
    }
    if (pos == -1 && len < MAX_HIGH_SCORES)
    {
        pos = len;
        len++;
    }

    if (pos != -1)
    {
        for (int i = len - 1; i > pos; i--)
        {
            high_score[i] = high_score[i - 1];
        }
        strcpy(high_score[pos].name, userInput);
        high_score[pos].score = score;
    }
}

void show_leaderboard()
{
    iSetColor(255, 0, 0);
    iText(100, 300, "Enter your name: ", GLUT_BITMAP_TIMES_ROMAN_24);

    if (inputMode)
    {
        iText(300, 300, userInput, GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else
    {
        // Displaying the entered name and score
        char displayText[100];
        sprintf(displayText, "Name: %s, Score: %d", userInput, score);
        iText(100, 250, displayText, GLUT_BITMAP_TIMES_ROMAN_24);

        // Displaying the high scores
        int y = 200;
        for (int i = 0; i < len; i++)
        {
            char scoreText[100];
            sprintf(scoreText, "%d. %s: %d", i + 1, high_score[i].name, high_score[i].score);
            iText(100, y, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);
            y -= 30;
        }
    }
}

void iDraw()
{
    iClear();
    show_leaderboard();
}

void iMouseMove(int mx, int my)
{
}

void iMouse(int button, int state, int mx, int my)
{
}

void iKeyboard(unsigned char key)
{
    if (key == 'm')
    {
        score++;
    }
    if (inputMode)
    {
        if (key == '\r')
        { // Enter key to finalize input
            inputMode = false;
            read_high_scores();
            add_new_score();
            write_high_scores();
        }
        else if (key == '\b')
        { // Backspace key to delete character
            if (inputIndex > 0)
            {
                inputIndex--;
                userInput[inputIndex] = '\0';
            }
        }
        else if (inputIndex < MAX_NAME_LENGTH - 1)
        {
            userInput[inputIndex] = key;
            inputIndex++;
            userInput[inputIndex] = '\0';
        }
    }
}

void iSpecialKeyboard(unsigned char key)
{
}


int main()
{
    iInitialize(1000, 400, "Hello");
    return 0;
}
