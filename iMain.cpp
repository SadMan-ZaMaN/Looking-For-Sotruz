#include "iGraphics.h"
#include <bits/stdc++.h>
#include <cstring>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 30
#define MAX_HIGH_SCORES 5

char userInput[MAX_NAME_LENGTH];
int inputIndex = 0;
bool inputMode = false;

struct hscore
{
    char myname[MAX_NAME_LENGTH];
    int score;
} high_score[MAX_HIGH_SCORES];

int length = 0;

using namespace std;
int x = 300, y = 300;
bool isfacingRight = true;
int bulletDirection = 1;
int score = 0;
int playerHP = 100;

#define screenWidth 1920
#define screenHeight 1080

#define ENEMYNUMBER 4
#define heroCordinateX 100
#define heroCordinateY 200
int heroCorX = heroCordinateX; // 1st chapter sesh e player move er jonno
int heroCorY = heroCordinateY;
int heroIndex = 0;
char herowalk[8][30] = {"HeroMovement\\Run\\w0.bmp", "HeroMovement\\Run\\w1.bmp", "HeroMovement\\Run\\w2.bmp", "HeroMovement\\Run\\w3.bmp", "HeroMovement\\Run\\w4.bmp", "HeroMovement\\Run\\w5.bmp", "HeroMovement\\Run\\w6.bmp", "HeroMovement\\Run\\w7.bmp"};
char leftwalk[8][30] = {"HeroMovement\\Run\\l0.bmp", "HeroMovement\\Run\\l1.bmp", "HeroMovement\\Run\\l2.bmp", "HeroMovement\\Run\\l3.bmp", "HeroMovement\\Run\\l4.bmp", "HeroMovement\\Run\\l5.bmp", "HeroMovement\\Run\\l6.bmp", "HeroMovement\\Run\\l7.bmp"};

#define MUSIC_NONE 0
#define MUSIC_MENU 1
#define MUSIC_ENDING 2
int currentMusic = MUSIC_NONE;

// iDraw runs every frame, so only start a track when it changes (otherwise it restarts every frame)
void playMusic(int track)
{
    if (track == currentMusic)
    {
        return;
    }
    currentMusic = track;
    if (track == MUSIC_MENU)
    {
        PlaySound("Music\\Menu_BGM.wav", NULL, SND_FILENAME | SND_LOOP | SND_ASYNC);
    }
    else if (track == MUSIC_ENDING)
    {
        PlaySound("Music\\WhatIHaveDone1.wav", NULL, SND_FILENAME | SND_ASYNC);
    }
    else
    {
        PlaySound(NULL, NULL, 0);
    }
}

struct buttonCordinate
{
    int x;
    int y;
} bCordinate[4];

char masterchief[6][30] = {"masterchief\\1.bmp", "masterchief\\2.bmp", "masterchief\\3.bmp", "masterchief\\4.bmp", "masterchief\\5.bmp", "masterchief\\6.bmp"};
char chiefammo[30] = "masterchief\\ammo.bmp";
int mposx, mposy;
char button[4][35] = {"Home\\INSTRUCTIONS.bmp", "Home\\PLAY_button.bmp", "Home\\EXIT_button.bmp", "Home\\LEADER_BOARD_button.bmp"};
char homemenu[40] = "Home\\lookingForSotruz.bmp";
char play[25] = "Home\\PLAY_button.bmp";
char exitgame[25] = "Home\\EXIT_button.bmp";
char leaderboard[35] = "Home\\LEADER_BOARD_button.bmp";

char fail[30] = "img\\MF2.bmp";
char instruct[30] = "img\\INSTRUCTION.bmp";
int gamestate = -1;

char heroStand[30] = "HeroMovement\\Run\\11.bmp";

bool standPosition = true;
int standCounter = 0;

char herojump[50] = "HeroMovement\\Run\\11.bmp";
bool jump = false;
bool jumpUp = false;
bool jumpDown = false;
#define JUMPLIMIT 150
int heroJumpCordinate = 0;

char herosit[50] = "HeroMovement\\Sit\\3.bmp";
bool sit = false;

// cannon & cannon bomb
int cannon_x = 1600;
int cannon_y = 160;
int bomb_x = cannon_x;
int bomb_y = cannon_y;
bool bombShow = false;
char cannon[45] = "cannon\\cannon1.bmp";
char bomb[45] = "cannon\\bomb1.bmp";
bool bombCollusion = false;
char bomCollusion[3][40] = {"cannon\\collusion10.bmp", "cannon\\collusion20.bmp", "cannon\\collusion30.bmp"};
char damagedCannon[45] = "cannon\\damaged_cannon.bmp";
bool cannonShow = true;
bool cannonDamagedShow = false;

// grenade
char grenadeimg[60] = "grenade\\grenade2.bmp";
bool grenadeShow = false;

// there is no grenade\1.bmp, so the throw animation is frames 2 to 8
char throwgren[7][20] = {"grenade\\2.bmp", "grenade\\3.bmp", "grenade\\4.bmp", "grenade\\5.bmp", "grenade\\6.bmp", "grenade\\7.bmp", "grenade\\8.bmp"};

int cannonHP = 2;
int grenade_x = heroCorX + 200;
int grenade_y = heroCordinateY + 180;
bool isThrowingGrenade = false;
int grenadeFrameCounter = 0;

// health kit
char crate[40] = "special\\crate.bmp";
int crate_x = 0;
int crate_y = screenHeight;
bool crateShow = false;

// enemy
char enemyimg[7][50] = {"HeroMovement\\Walk\\6N.bmp", "HeroMovement\\Walk\\5N.bmp", "HeroMovement\\Walk\\4N.bmp", "HeroMovement\\Walk\\3N.bmp", "HeroMovement\\Walk\\2N.bmp", "HeroMovement\\Walk\\1N.bmp", "HeroMovement\\Walk\\0N.bmp"};
char Rightenemyimg[7][50] = {"HeroMovement\\Walk\\6NR.bmp", "HeroMovement\\Walk\\5NR.bmp", "HeroMovement\\Walk\\4NR.bmp", "HeroMovement\\Walk\\3NR.bmp", "HeroMovement\\Walk\\2NR.bmp", "HeroMovement\\Walk\\1NR.bmp", "HeroMovement\\Walk\\0NR.bmp"};
char enemy_shoot[30] = "HeroMovement\\Walk\\shot.bmp";
struct enemyall
{
    int enemy_x;
    int enemy_y;
    int enemyindex;
    bool enemyShow;
    int hitCounter;
};

int currentPhase = 1;
int enemiesKilledInPhase = 0;
const int enemiesPerPhase = 4;
const int totalPhases = 3;

int bullet_x;
int bullet_y;
int bulletSpeed = 65;
bool bulletShow = false;

char lasergun[40] = "special\\laser.bmp";
char laserbullet[40] = "special\\laserbullet.bmp";
int lasergun_x = 0;
int lasergun_y = 0;
bool lasergunShow = false;
bool laserGunEquipped = false;
bool laserGunDropped = false;

enemyall enemy[ENEMYNUMBER];

char player_dead[5][45] = {"HeroMovement\\dead\\1N.bmp", "HeroMovement\\dead\\2N.bmp", "HeroMovement\\dead\\3N.bmp", "HeroMovement\\dead\\4N.bmp", "HeroMovement\\dead\\5N.bmp"};
int deathFrameCounter = 0;

void enemyMovement()
{
    if (gamestate == 0)
    {
        for (int i = 0; i < ENEMYNUMBER; i++)
        {
            if (enemy[i].enemyShow)
            {
                iShowBMP2(enemy[i].enemy_x, enemy[i].enemy_y, enemyimg[enemy[i].enemyindex], 0);
            }
        }
    }
}

char background[30] = "HeroMovement\\BG\\War2.bmp";

char bullet[50] = "bullet\\newBullet.bmp";
int kill = 0;

void read_high_scores()
{
    FILE *fp = fopen("Score.txt", "r");
    if (fp != NULL)
    {
        length = 0;
        // check the count first so we never read past the array, and %29s so a long name can't overflow myname
        while (length < MAX_HIGH_SCORES && fscanf(fp, "%29s %d", high_score[length].myname, &high_score[length].score) == 2)
        {
            length++;
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
        for (int i = 0; i < length; i++)
        {
            fprintf(fp, "%s %d\n", high_score[i].myname, high_score[i].score);
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
    int pos = length;
    for (int i = 0; i < length; i++)
    {
        if (high_score[i].score < kill)
        {
            pos = i;
            break;
        }
    }
    if (pos >= MAX_HIGH_SCORES)
    {
        return; // not in the top 5
    }

    // the list grows until it is full; after that the last score drops off
    if (length < MAX_HIGH_SCORES)
    {
        length++;
    }
    for (int i = length - 1; i > pos; i--)
    {
        high_score[i] = high_score[i - 1];
    }
    strcpy(high_score[pos].myname, userInput);
    high_score[pos].score = kill;
}

// kept above y = 300 so it stays visible when the window is taller than the screen (laptops / display scaling)
void show_leaderboard()
{
    iSetColor(255, 0, 0);

    if (inputMode)
    {
        iText(100, 560, "Enter your name: ", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(400, 560, userInput, GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else
    {
        iText(100, 560, "TOP 5 SCORES", GLUT_BITMAP_TIMES_ROMAN_24);

        char displayText[100];
        if (userInput[0] != '\0') // only after a game where the player entered a name
        {
            sprintf(displayText, "Name: %s, Score: %d", userInput, kill);
            iText(100, 520, displayText, GLUT_BITMAP_TIMES_ROMAN_24);
        }

        int y = 480;
        for (int i = 0; i < length; i++)
        {
            char scoreText[100];
            sprintf(scoreText, "%d. %s: %d", i + 1, high_score[i].myname, high_score[i].score);
            iText(100, y, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);
            y -= 30;
        }
        iText(100, 320, "PRESS 'B' TO GO BACK", GLUT_BITMAP_TIMES_ROMAN_24);
    }
}

void moveBullet()
{
    if (bulletShow)
    {
        bullet_x += bulletSpeed;
        for (int i = 0; i < ENEMYNUMBER; i++)
        {
            if (enemy[i].enemyShow && bullet_x >= enemy[i].enemy_x /*&& bullet_y >= enemy[i].enemy_y && bullet_y <= enemy[i].enemy_y + 50*/)
            {
                enemy[i].hitCounter++;
                bulletShow = false;

                if (enemy[i].hitCounter >= 2)
                {
                    enemy[i].enemyShow = false; // 2 bullet e enemy mara jabe
                    kill++;
                    enemiesKilledInPhase++;
                    printf("ENEMY KILLED:%d", kill);
                }
                break;
            }
        }
        if (bullet_x > screenWidth)
        {
            bulletShow = false;
        }
    }
}

int cr = 0;

void DropCrate()
{
    if (kill >= 6 && !crateShow && cr < 2)
    {
        cr++;
        crateShow = true;
        crate_x = 400 + rand() % (screenWidth - 550);
        crate_y = screenHeight;
    }
}

void moveAndCheckCrateCollision()
{
    if (crateShow)
    {
        crate_y -= 10;

        int crateLeft = crate_x;
        int crateRight = crate_x + 150;
        int crateTop = crate_y + 200;
        int crateBottom = crate_y;

        if (bulletShow && bullet_x >= crateLeft && bullet_x <= crateRight &&
            bullet_y >= crateBottom && bullet_y <= crateTop)
        {
            playerHP += 100;
            if (playerHP > 100)
            {
                playerHP = 100;
            }
            crateShow = false;
            bulletShow = false;
            printf("\n this code worked as the Crate was collected! now Player HP is : %d\n", playerHP);
        }

        if (crate_y < 0)
        {
            crateShow = false;
        }
        iShowBMP2(crate_x, crate_y, crate, 0);
    }
}

struct enemyBullet
{
    int enemybullet_x;
    int enemybullet_y;
    bool enemybulletShow;
};

enemyBullet enemyBullets[ENEMYNUMBER];
char enemyBulletImage[50] = "bullet\\enemy_bullet.bmp";
int enemyBulletSpeed = 20;

void enemyShoot()
{
    if (gamestate == 0)
    {
        for (int i = 0; i < ENEMYNUMBER; i++)
        {
            if (enemy[i].enemyShow && !enemyBullets[i].enemybulletShow)
            {
                enemyBullets[i].enemybulletShow = true;
                enemyBullets[i].enemybullet_x = enemy[i].enemy_x;
                enemyBullets[i].enemybullet_y = enemy[i].enemy_y + 270;
            }
        }
    }
}

int playerHitCount = 0;
bool playerVisible = true;

void stage1moveEnemyBullets()
{
    if (gamestate == 0)
    {
        for (int i = 0; i < ENEMYNUMBER; i++)
        {
            if (enemyBullets[i].enemybulletShow)
            {
                enemyBullets[i].enemybullet_x -= enemyBulletSpeed;

                int playerLeft = heroCordinateX + 150;
                int playerRight = playerLeft + 100;
                int playerTop = heroCordinateY + heroJumpCordinate + 280;

                if (playerVisible && !sit &&
                    playerRight >= enemyBullets[i].enemybullet_x && playerLeft <= enemyBullets[i].enemybullet_x  &&
                    playerTop>=470)
                {
                    enemyBullets[i].enemybulletShow = false;
                    playerHP -= 10;
                    printf("Player hit! HP: %d\n", playerHP);
                    continue;
                }

                if (enemyBullets[i].enemybullet_x < 0)
                {
                    enemyBullets[i].enemybulletShow = false;
                }
            }
        }
    }
}

// stage1moveEnemyBullets()   ikeyboard e giye sit er part ta

/*
void stage1moveEnemyBullets()
{
    if (gamestate == 0)
    {
        for (int i = 0; i < ENEMYNUMBER; i++)
        {
            if (enemyBullets[i].enemybulletShow)
            {
                enemyBullets[i].enemybullet_x -= enemyBulletSpeed;
                int bulletRight = enemyBullets[i].enemybullet_x + 20;
                int bulletLeft = enemyBullets[i].enemybullet_x;
                int playerLeft = heroCordinateX;
                int playerRight = heroCordinateX + 100;
                int playerTop = heroCordinateY + 280;
                int playerBottom = heroCordinateY;

                printf("BR:%d\n", bulletRight);
                printf("BL: %d\n", bulletLeft);
                printf("PR: %d\n", playerRight);
                printf("PL: %d\n", playerLeft);
                // Check collision with the player
                if (playerVisible && (enemyBullets[i].enemybullet_x >= 100 && enemyBullets[i].enemybullet_x < 200) && (!sit))
                {

                    enemyBullets[i].enemybulletShow = false;
                    playerHP -= 10;
                    // playerHitCount++;
                    // printf("Player hit by enemy bullet at x: %d, y: %d. Hit count: %d\n", bulletLeft, heroCordinateY, playerHitCount);

                    // // Check if player should become invisible
                    // if (playerHitCount >= 4) {
                    //     playerVisible = false;
                    //     printf("Player has become invisible!\n");
                    // }

                    continue;
                }
                if (enemyBullets[i].enemybullet_x < 0)
                {
                    enemyBullets[i].enemybulletShow = false;
                }
            }
        }
    }
}
*/

// timer: moves the death animation forward one frame (iDraw draws player_dead[deathFrameCounter])
void dead()
{
    if (playerHP <= 0 && deathFrameCounter < 4)
    {
        deathFrameCounter++;
    }
}

void cannongun()
{
    if (gamestate == 0 && cannonHP > 0)
    {
        if (!bombShow)
        {
            bombShow = true;
            bomb_x = cannon_x;
            bomb_y = cannon_y + 50;
        }

        if (bombShow)
        {
            bomb_x -= 20;
            int playerBottom = heroCordinateY + heroJumpCordinate;

            if ((bomb_x >= heroCorX + 50 && bomb_x <= heroCorX + 200) && (playerBottom < 300))
            { // apatoto playerbottom 300 rakhlam
                playerHP -= 20;
                printf("Cannon Bomb Collision Detected bx%d by%d hy%d\n", bomb_x, bomb_y, playerBottom);
                bombShow = false;
                bombCollusion = true;
            }
            if (bomb_x < 0)
            {
                bombShow = false;
                bomb_x = cannon_x;
                bomb_y = cannon_y + 50;
            }
        }
    }
}

void showBombCollusion()
{
    if (bombCollusion)
    {
        for (int i = 0; i < 3; i++)
        {
            iShowBMP2(heroCorX + 50, 120, bomCollusion[i], 0);
        }
        bombCollusion = false;
    }
}

void GrenadeThrow()
{
    if (isThrowingGrenade)
    {
        if (grenadeFrameCounter < 7)
        {
            iShowBMP2(heroCorX, heroCorY, throwgren[grenadeFrameCounter], 0);
            grenadeFrameCounter++;
        }
        else
        {
            isThrowingGrenade = false;
        }
    }
}

void cannondamage()
{
    int xaxis = abs(cannon_x - grenade_x);
    int yaxis = abs(cannon_y - grenade_y);
    if (xaxis < 150 && yaxis < 150)
    {
        cannonHP--;
        for (int i = 0; i < 3; i++)
        {
            iShowBMP2(cannon_x - 100, cannon_y, bomCollusion[i], 0);
        }
        grenadeShow = false;
    }
    if (cannonHP == 0)
    {
        cannonShow = false;
        cannonDamagedShow = true;
        if (bomb_x < cannon_x)
        {
            while (bomb_x >= 0)
            {
                bomb_x -= 20;
            }
            bombShow = false;
        }
    }
}

void throwGrenade()
{
    int mid = abs(cannon_x - heroCorX) / 2;
    if (grenadeShow)
    {
        if (grenade_x < heroCorX + mid)
        {
            grenade_x += 20;
            grenade_y += 5;
        }
        else if (grenade_x >= heroCorX + mid && grenade_x < cannon_x + 200)
        {
            grenade_x += 20;
            grenade_y -= 5;
        }
        else
        {
            grenadeShow = false;
        }

        cannondamage();

        iShowBMP2(grenade_x, grenade_y, grenadeimg, 0);
    }
}

void setEnemyVariables()
{
    for (int i = 0; i < ENEMYNUMBER; i++)
    {
        enemy[i].enemy_x = screenWidth + rand() % 500;
        enemy[i].enemy_y = 200;
        enemy[i].enemyindex = rand() % 7;
        enemy[i].enemyShow = true;
        enemy[i].hitCounter = 0;
        enemyBullets[i].enemybulletShow = false;
    }
}

void checkAndSwitchPhases()
{
    if (enemiesKilledInPhase >= enemiesPerPhase)
    {
        currentPhase++;
        enemiesKilledInPhase = 0;

        if (currentPhase <= totalPhases)
        {
            setEnemyVariables();
        }
        else
        {
            printf("All phases complete!\n");
        }
    }
}

void DropLaserGun()
{
    if (currentPhase > totalPhases && !lasergunShow && !laserGunDropped)
    {
        lasergunShow = true;
        laserGunDropped = true;
        lasergun_x = rand() % (screenWidth - 250);
        lasergun_y = heroCordinateY;
    }
}

void checkPlayerLaserGunCollusion()
{
    if (lasergunShow && heroCorX >= lasergun_x - 150 && heroCorX <= lasergun_x + 100 &&
        heroCordinateY >= lasergun_y - 100 && heroCordinateY <= lasergun_y + 100)
    {
        laserGunEquipped = true;
        lasergunShow = false;
        printf("Laser gun collected! Player can now shoot laser bullets.\n");
    }
    if (lasergunShow)
    {
        iShowBMP2(lasergun_x, lasergun_y, lasergun, 0);
    }
}

// STAGE 2 CODES ARE HERE
#define ENEMYNUMBER_STAGE2 6
struct enemyStage2
{
    int enemy_x;
    int enemy_y;
    int enemyIndex;
    bool enemyShow;
    int hitCounter;
};

enemyStage2 enemy2[ENEMYNUMBER_STAGE2];

bool supplyCrateShow = false;
int supplyCrate_x = 900;
int supplyCrate_y = 200;

int stage2 = 0;
bool stage2EnemiesShow = false;

char bombCollision[3][40] = {"cannon\\collusion10.bmp", "cannon\\collusion20.bmp", "cannon\\collusion30.bmp"};
int stage2StartTime = 0;
bool stage2Ready = false;
bool flagnew = false;
void checkAndDropSupplyCrate()
{
    if (kill >= 12 && cannonDamagedShow && !supplyCrateShow && !flagnew)
    {
        supplyCrateShow = true;
        printf("Supply crate dropped at x: %d, y: %d\n", supplyCrate_x, supplyCrate_y);
    }
}

void checkPlayerSupplyCratecollusion()
{
    if (supplyCrateShow && heroCorX >= supplyCrate_x - 150 && heroCorX <= supplyCrate_x + 50 &&
        heroCorY >= supplyCrate_y - 50 && heroCorY <= supplyCrate_y + 50 && !flagnew)
    {
        supplyCrateShow = false;
        flagnew = true;
        stage2 = 1; // stage2 suru hobe
        stage2StartTime = GetTickCount();
        printf("Supply crate collected! Stage 2 will begin.\n");
        playerHP = 100;
    }

    if (supplyCrateShow)
    {
        iShowBMP2(supplyCrate_x, supplyCrate_y, crate, 0);
    }
}

void setEnemyVariablesStage2(int phase)
{
    for (int i = 0; i < ENEMYNUMBER_STAGE2; i++)
    {
        if (phase == 1 && i < 3)
        {
            enemy2[i].enemy_x = screenWidth + rand() % 500;
            enemy2[i].enemy_y = 200;
            enemy2[i].enemyIndex = rand() % 7;
            enemy2[i].enemyShow = true;
        }
        else if (phase == 2 && i >= 3)
        {
            enemy2[i].enemy_x = -200 - rand() % 500;
            enemy2[i].enemy_y = 200;
            enemy2[i].enemyIndex = rand() % 7;
            enemy2[i].enemyShow = true;
        }
        enemy2[i].hitCounter = 0;
        printf("Enemy %d initialized at x: %d, y: %d\n", i, enemy2[i].enemy_x, enemy2[i].enemy_y);
    }
    stage2EnemiesShow = true;
}

int stage2kill = 0;
int stage2enemy = 0;
void enemyMovementStage2()
{
    int enemiesOnScreen = 0;
    if (stage2EnemiesShow)
    {
        for (int i = 0; i < ENEMYNUMBER_STAGE2; i++)
        {
            if (enemy2[i].enemyShow)
            {
                if (enemiesOnScreen >= 3)
                {
                    break;
                }
                enemiesOnScreen++;

                if (i < 3)
                {
                    if (enemy2[i].enemy_x > heroCorX)
                    {
                        enemy2[i].enemy_x -= 10;
                        iShowBMP2(enemy2[i].enemy_x, enemy2[i].enemy_y, enemyimg[enemy2[i].enemyIndex], 0);
                    }
                }
                else
                {
                    if (enemy2[i].enemy_x < heroCorX)
                    {
                        enemy2[i].enemy_x += 10;
                        iShowBMP2(enemy2[i].enemy_x, enemy2[i].enemy_y, Rightenemyimg[enemy2[i].enemyIndex], 0);
                    }
                }

                if (enemy2[i].enemy_x >= heroCorX && enemy2[i].enemy_x <= heroCorX + 100 &&
                    enemy2[i].enemy_y >= heroCorY && enemy2[i].enemy_y <= heroCorY + 280)
                {
                    playerHP -= 25;
                    stage2enemy++;
                    printf("Player hit by enemy! Player HP: %d\n", playerHP);
                    enemy2[i].enemyShow = false;
                    for (int j = 0; j < 3; j++)
                    {
                        iShowBMP2(enemy2[i].enemy_x, enemy2[i].enemy_y, bombCollision[j], 0);
                    }
                    if (stage2enemy == 3)
                    {
                        printf("First phase of stage 2 complete. Initializing second phase enemies.\n");
                        setEnemyVariablesStage2(2);
                    }
                }
            }
        }
    }
}

void checkAndStartStage2()
{
    if (kill >= 12 && stage2 == 0 && cannonDamagedShow)
    {
        stage2 = 1;
        stage2StartTime = GetTickCount();
        printf("All stage 1 enemies defeated. Stage 2 will begin in 20 seconds.\n");
    }
}

void updateStageTransition()
{
    if (stage2 == 1 && !stage2Ready)
    {
        int currentTime = GetTickCount();
        if (currentTime - stage2StartTime >= 10000)
        {
            setEnemyVariablesStage2(1);
            stage2Ready = true;
            printf("Stage 2 started. First phase enemies will appear.\n");
        }
    }
}

#define ENEMY_WIDTH 140

void movemyBulletstage2()
{
    if (bulletShow)
    {
        int oldBullet_x = bullet_x;
        bullet_x += bulletSpeed * bulletDirection;

        for (int i = 0; i < ENEMYNUMBER_STAGE2; i++)
        {
            if (enemy2[i].enemyShow && enemy2[i].enemy_x >= 0 && enemy2[i].enemy_x <= screenWidth)
            {
                // only hit an enemy the bullet passed through this frame, so enemies behind the player are safe
                int enemyLeft = enemy2[i].enemy_x;
                int enemyRight = enemy2[i].enemy_x + ENEMY_WIDTH;
                bool hit;
                if (bulletDirection == 1)
                {
                    hit = oldBullet_x <= enemyRight && bullet_x >= enemyLeft;
                }
                else
                {
                    hit = oldBullet_x >= enemyLeft && bullet_x <= enemyRight;
                }

                if (hit)
                {
                    enemy2[i].hitCounter++;
                    bulletShow = false;
                    printf("Bullet hit enemy at index %d, enemy_x: %d\n", i, enemy2[i].enemy_x);

                    if (enemy2[i].hitCounter >= 4)
                    {
                        enemy2[i].enemyShow = false;
                        kill++;
                        stage2enemy++;
                        stage2kill++;
                        printf("ENEMY KILLED: Stage 2: %d\n", stage2kill);

                        if (stage2enemy == 3)
                        {
                            printf("First phase of stage 2 complete. Initializing second phase enemies.\n");
                            setEnemyVariablesStage2(2);
                        }
                    }
                    break;
                }
            }
        }
        if (bullet_x > screenWidth || bullet_x < 0)
        {
            bulletShow = false;
        }
    }
}

// STAGE 3
bool bossDefeated = false;
DWORD bossDeathTime;
bool endgameImageShown = false;
bool finished = false;
char complete[30] = "img\\game.bmp";

bool stage3Ready = false;
int stage3StartTime;
int boss_x;
int boss_y;
int bossHP = 500;
bool bossShow = false;
bool bossAmmoShow = false;
int bossAmmo_x;
int bossAmmo_y;
int bossAmmoSpeed = 50;
int bossIndex = 0;
bool bossMoving = true;
bool shootingLowerBullet = true;
char bossdead[30] = "masterchief\\chiefdead.bmp";

// The boss images are only about as tall as the player, so draw them 1.5x bigger.
// Each image also has some empty space under the feet (in pixels, per frame); it is
// subtracted when drawing so the boss stands on the ground instead of floating.
#define BOSS_SCALE 1.5
int bossFeet[6] = {25, 38, 43, 16, 25, 22};
void setMC();
void checkAndStartStage3();
void moveMC();
void checkBossCollision();
void bossShoot();
void moveMCBullets();

void setMC()
{
    boss_x = screenWidth + 500;
    boss_y = 200; // ground level, same as the player
    bossShow = true;
    bossMoving = true;
}

void checkAndStartStage3()
{
    int check = 12 + stage2kill + (100 - playerHP) / 25;
    if (check >= 18 && playerHP > 0 && !stage3Ready)
    {
        stage3Ready = true;
        stage3StartTime = GetTickCount();
        setMC();
    }
}

void checkBossCollision()
{
    // the scaled boss covers about 330 x 360 pixels from (boss_x, boss_y)
    if (bulletShow && bullet_x >= boss_x && bullet_x <= boss_x + 330 && bullet_y >= boss_y && bullet_y <= boss_y + 360)
    {
        bossHP -= 10;
        bulletShow = false;
        printf("Boss hit! Boss HP: %d\n", bossHP);
        if (bossHP <= 0 && !bossDefeated)
        {
            bossShow = false;
            bossDefeated = true;
            bossDeathTime = GetTickCount();
            printf("Boss defeated!\n");
        }
    }
}

void bossShoot()
{
    if (bossShow && !bossAmmoShow)
    {
        bossAmmoShow = true;
        bossAmmo_x = boss_x;
        if (shootingLowerBullet)
        {
            bossAmmo_y = 210;
        }
        else
        {
            bossAmmo_y = 410;
        }
        shootingLowerBullet = !shootingLowerBullet;
    }
}

void moveMCBullets()
{
    if (bossAmmoShow)
    {
        bossAmmo_x -= bossAmmoSpeed;

        int bulletRight = bossAmmo_x + 20;
        int bulletLeft = bossAmmo_x;
        int playerLeft = heroCorX;
        int playerRight = heroCorX + 100;
        int playerTop = heroCorY + heroJumpCordinate + 280;
        int playerBottom = heroCorY + heroJumpCordinate;

        if (sit)
        {
            playerTop = heroCorY + heroJumpCordinate + 180;
        }

        if (playerVisible && (bossAmmo_x >= playerLeft && bossAmmo_x <= playerRight) &&
            (bossAmmo_y >= playerBottom && bossAmmo_y <= playerTop))
        {
            bossAmmoShow = false;
            playerHP -= 20;
            printf("Player hit by boss bullet! Player HP: %d\n", playerHP);
        }

        if (bossAmmo_x < 0)
        {
            bossAmmoShow = false;
        }
    }
}

void moveMC()
{
    if (bossShow)
    {
        // draw the boss while it walks in too, not only after it stops
        glPixelZoom(BOSS_SCALE, BOSS_SCALE);
        iShowBMP2(boss_x, boss_y - (int)(bossFeet[bossIndex] * BOSS_SCALE), masterchief[bossIndex], 0);
        glPixelZoom(1, 1);
        bossIndex++;
        if (bossIndex >= 6)
        {
            bossIndex = 0;
        }

        if (bossMoving)
        {
            boss_x -= 10;
            if (boss_x <= 1600)
            {
                bossMoving = false;
            }
        }
        else
        {
            if (!bossAmmoShow)
            {
                bossShoot();
            }

            moveMCBullets();

            if (bossAmmoShow)
            {
                iShowBMP2(bossAmmo_x, bossAmmo_y, chiefammo, 0);
            }
        }
    }
}

void endgame()
{
    DWORD currentTime = GetTickCount();

    if (bossDefeated && !finished)
    {
        playMusic(MUSIC_ENDING);
        finished = true;
        bossDeathTime = currentTime;
    }

    // 10 seconds after the boss dies, switch to the credits screen (gamestate 7)
    if (finished && !endgameImageShown && currentTime - bossDeathTime >= 10000)
    {
        endgameImageShown = true;
        gamestate = 7;
    }
}

int count2 = 1;

// puts everything back to how it was at the start, so PLAY works again after winning or dying
void resetGame()
{
    userInput[0] = '\0';
    inputIndex = 0;
    inputMode = false;

    playerHP = 100;
    kill = 0;
    isfacingRight = true;
    bulletDirection = 1;
    heroCorX = heroCordinateX;
    heroCorY = heroCordinateY;
    heroIndex = 0;
    standPosition = true;
    standCounter = 0;
    jump = false;
    jumpUp = false;
    heroJumpCordinate = 0;
    sit = false;
    playerVisible = true;
    deathFrameCounter = 0;
    bulletShow = false;

    // stage 1
    currentPhase = 1;
    enemiesKilledInPhase = 0;
    setEnemyVariables();
    cannonHP = 2;
    cannonShow = true;
    cannonDamagedShow = false;
    bombShow = false;
    bombCollusion = false;
    grenadeShow = false;
    isThrowingGrenade = false;
    grenadeFrameCounter = 0;
    crateShow = false;
    cr = 0;
    lasergunShow = false;
    laserGunEquipped = false;
    laserGunDropped = false;

    // stage 2
    supplyCrateShow = false;
    flagnew = false;
    stage2 = 0;
    stage2Ready = false;
    stage2EnemiesShow = false;
    stage2kill = 0;
    stage2enemy = 0;
    for (int i = 0; i < ENEMYNUMBER_STAGE2; i++)
    {
        enemy2[i].enemyShow = false;
    }

    // stage 3
    stage3Ready = false;
    bossShow = false;
    bossHP = 500;
    bossDefeated = false;
    bossAmmoShow = false;
    bossIndex = 0;
    bossMoving = true;
    shootingLowerBullet = true;
    finished = false;
    endgameImageShown = false;
    count2 = 1;
}

void iDraw()
{
    iClear();
    if (playerHP <= 0 && gamestate == 0)
    {
        gamestate = 5;    // game over screen
        inputMode = true; // ask for the player's name for the leaderboard
    }
    if (gamestate == -1)
    {
        playMusic(MUSIC_MENU);
        iShowBMP(0, 0, homemenu);
        for (int i = 0; i < 4; i++)
        {
            iShowBMP2(bCordinate[i].x, bCordinate[i].y, button[i], 255);
        }
    }
    else if (gamestate == 0)
    {
        char displaytext3[100];
        if (!finished)
        {
            playMusic(MUSIC_NONE); // after the boss dies the ending music keeps playing
        }

        iShowBMP(0, 0, background);
        enemyMovement();

        // drawn early so the boss (who stops where the cannon stands) is drawn in front of the wreck
        if (cannonShow)
        {
            iShowBMP2(cannon_x, cannon_y, cannon, 0);
        }
        else if (cannonDamagedShow)
        {
            iShowBMP2(cannon_x, cannon_y, damagedCannon, 0);
        }

        iSetColor(255, 255, 255);
        iText(10, 1050, "PRESS 'B' TO PAUSE", GLUT_BITMAP_TIMES_ROMAN_24);

        char displaytext4[100];
        iSetColor(255, 255, 255);
        sprintf(displaytext4, "SCORE: %d", kill);
        iText(10, 980, displaytext4, GLUT_BITMAP_TIMES_ROMAN_24);

        if (bulletShow)
        {
            if (laserGunEquipped)
            {
                iShowBMP2(bullet_x, bullet_y, laserbullet, 0);
            }
            else
            {
                iShowBMP2(bullet_x, bullet_y, bullet, 0);
            }
        }

        if (stage2Ready)
        {
            movemyBulletstage2();
            enemyMovementStage2();
            checkAndStartStage3();
        }
        else
        {
            moveBullet();
        }

        if (stage3Ready)
        {
            moveMC();
            checkBossCollision();
            if (bossHP > 0)
            {
                iSetColor(255, 255, 255);
                sprintf(displaytext3, "BOSS HEALTH: %d", bossHP);
                iText(1400, 1050, displaytext3, GLUT_BITMAP_TIMES_ROMAN_24);
            }
            else if (bossDefeated)
            {
                cannonDamagedShow = false;
                iSetColor(255, 255, 255);
                iText(1400, 1050, "MISSION ACCOMPLISHED", GLUT_BITMAP_TIMES_ROMAN_24);
                kill = 30 + playerHP;
                if (count2 == 1)
                {
                    inputMode = true;
                    count2++;
                }
                endgame(); // called every frame so it can switch to the credits after 10 seconds
            }
        }

        for (int i = 0; i < ENEMYNUMBER; i++)
        {
            if (enemyBullets[i].enemybulletShow)
            {
                iShowBMP2(enemyBullets[i].enemybullet_x, enemyBullets[i].enemybullet_y, enemyBulletImage, 0);
            }
        }
        stage1moveEnemyBullets();

        if (bombShow)
        {
            iShowBMP2(bomb_x, bomb_y, bomb, 0);
        }
        showBombCollusion();

        GrenadeThrow();
        throwGrenade();

        if (playerVisible && !isThrowingGrenade)
        {
            if (jump)
            {
                if (jumpUp)
                {
                    iShowBMP2(heroCorX, heroCordinateY + heroJumpCordinate, herojump, 0);
                }
                else
                {
                    iShowBMP2(heroCorX, heroCordinateY + heroJumpCordinate, herojump, 0);
                }
            }
            else if (sit)
            {
                iShowBMP2(heroCorX, heroCorY, herosit, 0);
            }
            else if (!standPosition)
            {
                if (isfacingRight)
                {
                    iShowBMP2(heroCorX, heroCorY, herowalk[heroIndex], 0);
                }
                else
                {
                    iShowBMP2(heroCorX, heroCorY, leftwalk[heroIndex], 0);
                }
                standCounter++;
                if (standCounter >= 20)
                {
                    standCounter = 0;
                    heroIndex = 0;
                    standPosition = true;
                }
            }
            else if (isfacingRight)
            {
                iShowBMP2(heroCorX, heroCorY, heroStand, 0);
            }
            else
            {
                iShowBMP2(heroCorX, heroCorY, leftwalk[0], 0); // there is no left standing image
            }
        }

        DropCrate();
        moveAndCheckCrateCollision();

        DropLaserGun();
        checkPlayerLaserGunCollusion();

        checkAndSwitchPhases();

        checkAndDropSupplyCrate();
        checkPlayerSupplyCratecollusion();

        updateStageTransition();

        char displaytext2[100];
        if (playerHP > 0)
        {
            iSetColor(255, 255, 255);
            sprintf(displaytext2, "Health bar: %d", playerHP);
            iText(900, 1050, displaytext2, GLUT_BITMAP_TIMES_ROMAN_24);
        }

        if (bossDefeated)
        {
            read_high_scores();
            show_leaderboard(); // drawn last so the player sprite doesn't cover it
        }
    }
    else if (gamestate == 1)
    {
        iShowBMP(0, 0, exitgame);
        exit(0);
    }
    else if (gamestate == 2)
    {
        iShowBMP(0, 0, fail);
        read_high_scores();
        show_leaderboard();
    }
    else if (gamestate == 6)
    {
        iShowBMP(0, 0, instruct);
    }
    else if (gamestate == 5)
    {
        // game over: the dead player, name entry, then the leaderboard
        playMusic(MUSIC_MENU);
        iShowBMP(0, 0, background);
        iShowBMP2(heroCorX, heroCorY, player_dead[deathFrameCounter], 0);

        iSetColor(255, 0, 0);
        iText(900, 1050, "DEAD", GLUT_BITMAP_TIMES_ROMAN_24);

        read_high_scores();
        show_leaderboard();
    }
    else if (gamestate == 7)
    {
        // credits after the boss is defeated
        iShowBMP(0, 0, complete);
        read_high_scores();
        show_leaderboard();
    }
}

void iMouseMove(int mx, int my)
{
    printf("x = %d, y= %d\n", mx, my);
}

#define BUTTON_WIDTH 200
#define BUTTON_HEIGHT 60

void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && gamestate == -1) // the buttons only exist on the menu
    {
        // Windows shrinks the window when the screen is smaller than 1920x1080 (or uses display scaling).
        // The button positions get scaled to the window but the 200x60 images don't, so compare in window pixels.
        int winWidth = glutGet(GLUT_WINDOW_WIDTH);
        int winHeight = glutGet(GLUT_WINDOW_HEIGHT);
        int px = mx;                            // iGraphics gives x in window pixels
        int py = my - screenHeight + winHeight; // and y as (screenHeight - pixel row from the top)

        for (int i = 0; i < 4; i++)
        {
            int left = bCordinate[i].x * winWidth / screenWidth;
            int bottom = bCordinate[i].y * winHeight / screenHeight;
            if (px < left || px > left + BUTTON_WIDTH || py < bottom || py > bottom + BUTTON_HEIGHT)
            {
                continue;
            }

            if (i == 0) // INSTRUCTIONS
            {
                gamestate = 6;
            }
            else if (i == 1) // PLAY
            {
                if (playerHP <= 0 || bossDefeated)
                {
                    resetGame(); // last game is over, start a new one
                }
                gamestate = 0;
            }
            else if (i == 2) // EXIT
            {
                gamestate = 1;
            }
            else // LEADER BOARD
            {
                gamestate = 2;
            }
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        // place your codes here
        //  x -= 10;
        //  y -= 10;
    }
}

bool directionRight = true;

void iKeyboard(unsigned char key)
{
    if (inputMode)
    {
        // while the player types their name, keys only go to the name (so 'q' or 'b' in a name doesn't quit)
        if (key == '\r')
        {
            if (inputIndex == 0)
            {
                strcpy(userInput, "Player"); // an empty name would break Score.txt
                inputIndex = strlen(userInput);
            }
            inputMode = false;
            read_high_scores();
            add_new_score();
            write_high_scores();
        }
        else if (key == '\b')
        {
            if (inputIndex > 0)
            {
                inputIndex--;
                userInput[inputIndex] = '\0';
            }
        }
        else if (key >= ' ' && key <= '~' && inputIndex < MAX_NAME_LENGTH - 1)
        {
            userInput[inputIndex] = (key == ' ') ? '_' : key; // Score.txt is split by spaces
            inputIndex++;
            userInput[inputIndex] = '\0';
        }
        return;
    }

    if (key == 'q')
    {
        exit(0);
    }
    if (key == 'b' && (gamestate == 0 || gamestate == 2 || gamestate == 5 || gamestate == 6 || gamestate == 7))
    {
        gamestate = -1;
        return;
    }
    if (gamestate != 0)
    {
        return; // the controls below only work while playing
    }

    if (key == 'w')
    {
        if (!jump)
        {
            jump = true;
            jumpUp = true;
            sit = false;
        }
    }
    else if (key == 's' && heroJumpCordinate==0)
    {
        sit = true;
        
    }
    else if (key == ' ')
    {
        if (stage2Ready && !bulletShow)
        {
            bulletShow = true;
            bulletDirection = isfacingRight ? 1 : -1;

            if (sit)
            {
                bullet_x = isfacingRight ? (heroCorX + 280) : (heroCorX + 200);
                bullet_y = heroCordinateY + 158;
            }
            else
            {
                bullet_x = isfacingRight ? (heroCorX + 280) : (heroCorX + 200);
                bullet_y = heroCordinateY + 280;
            }

            if (laserGunEquipped)
            {
                iShowBMP2(bullet_x, bullet_y - 5, laserbullet, 0);
            }
            else
            {
                iShowBMP2(bullet_x, bullet_y, bullet, 0);
            }
        }
        else if (!stage2Ready && !bulletShow)
        {
            bulletShow = true;
            if (sit)
            {
                bullet_x = heroCorX + 280;
                bullet_y = heroCordinateY + 158;
            }
            else
            {
                bullet_x = heroCorX + 280;
                bullet_y = heroCordinateY + 280;
            }

            if (laserGunEquipped)
            {
                iShowBMP2(bullet_x, bullet_y - 5, laserbullet, 0);
            }
            else
            {
                iShowBMP2(bullet_x, bullet_y, bullet, 0);
            }
        }
    }
    else if (key == 'g')
    {
        if (kill >= 12 && !isThrowingGrenade && !grenadeShow && !jump && cannonHP != 0)
        {
            isThrowingGrenade = true;
            grenadeFrameCounter = 0;
            grenade_x = heroCorX + 200;
            grenade_y = heroCorY + 180;
            grenadeShow = true;
        }
    }
    else if (key == 'd')
    {
        if (stage2Ready)
        {
            isfacingRight = true;
            heroCorX += 10;
            heroIndex++;
            if (heroIndex >= 7)
            {
                heroIndex = 0;
            }
        }
        else if (currentPhase > 3)
        {
            heroCorX += 10;
            heroIndex++;
            if (heroIndex >= 7)
            {
                heroIndex = 0;
            }
        }

        standPosition = false;
    }
    else if (key == 'a')
    {
        if (stage2Ready)
        {
            isfacingRight = false;
            heroCorX -= 10;
            heroIndex++;
            if (heroIndex >= 7)
            {
                heroIndex = 0;
            }
        }
        else if (currentPhase > 3)
        {
            heroCorX -= 10;
            heroIndex--;
            if (heroIndex < 0)
            {
                heroIndex = 7;
            }
        }

        standPosition = false;
    }

    // keep the player on the screen (the body is drawn 177 to 334 pixels from heroCorX)
    if (heroCorX < 0)
    {
        heroCorX = 0;
    }
    if (heroCorX > screenWidth - 335)
    {
        heroCorX = screenWidth - 335;
    }
}

void iSpecialKeyboard(unsigned char key)
{
    if (key == GLUT_KEY_END)
    {
        exit(0);
    }
}

void change()
{
    if (jump)
    {
        if (jumpUp)
        {
            heroJumpCordinate += 12;
            if (heroJumpCordinate >= JUMPLIMIT)
            {
                jumpUp = false;
            }
        }
        else
        {
            heroJumpCordinate -= 8;
            if (heroJumpCordinate < 0)
            {
                jump = false;
                heroJumpCordinate = 0;
            }
        }
    }
}

void change_enemy()
{
    if (gamestate == 0)
    {
        for (int i = 0; i < ENEMYNUMBER; i++)
        {
            if (enemy[i].enemy_x > screenWidth / 2)
            {
                enemy[i].enemy_x -= 10;
            }
            enemy[i].enemyindex++;
            if (enemy[i].enemyindex >= 7)
            {
                enemy[i].enemyindex = 0;
            }
        }
    }
}

int main()
{
    setEnemyVariables();

    iSetTimer(60, change);
    iSetTimer(100, change_enemy);
    iSetTimer(1000, enemyShoot);
    iSetTimer(200, dead);
    iSetTimer(50, cannongun);

    int sum = 100;
    for (int i = 3; i >= 0; i--)
    {
        bCordinate[i].x = 50;
        bCordinate[i].y = sum;
        sum += 150;
    }
    // score = kill * 10;
    playMusic(MUSIC_MENU);
    // place your own initialization codes here.
    iInitialize(screenWidth, screenHeight, "LookingForSotruz");
    return 0;
}