#include "iGraphics.h"
#include <bits/stdc++.h>
#include <cstring>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#define MAX_NAME_LENGTH 500
#define MAX_HIGH_SCORES 5

char userInput[MAX_NAME_LENGTH];
int inputIndex = 0;
bool inputMode = false;

struct hscore
{
    char name[30];
    int score;
} high_score[MAX_HIGH_SCORES];

int len = 0;


using namespace std;
int x = 300, y = 300;
bool facingRight = true; // True if player is facing right, false if facing left
int bulletDirection = 1; // 1 for right, -1 for left
int score = 0;
int playerHP = 1000;         // health of player

#define screenWidth 1920
#define screenHeight 1080

#define ENEMYNUMBER 4
#define heroCordinateX 100
#define heroCordinateY 200
int heroCorX = heroCordinateX;      // 1st chapter sesh e player move er jonno
int heroCorY = heroCordinateY;
int heroIndex = 0;
char herowalk[8][30] = {"HeroMovement\\Run\\w0.bmp","HeroMovement\\Run\\w1.bmp","HeroMovement\\Run\\w2.bmp","HeroMovement\\Run\\w3.bmp","HeroMovement\\Run\\w4.bmp","HeroMovement\\Run\\w5.bmp","HeroMovement\\Run\\w6.bmp","HeroMovement\\Run\\w7.bmp"};
char leftwalk[8][30] = {"HeroMovement\\Run\\l0.bmp","HeroMovement\\Run\\l1.bmp","HeroMovement\\Run\\l2.bmp","HeroMovement\\Run\\l3.bmp","HeroMovement\\Run\\l4.bmp","HeroMovement\\Run\\l5.bmp","HeroMovement\\Run\\l6.bmp","HeroMovement\\Run\\l7.bmp"};
bool Menumusic = true;

struct buttonCordinate {
    int x;
    int y;
} bCordinate[4];


char masterchief[6][30] = {"masterchief\\1.bmp","masterchief\\2.bmp","masterchief\\3.bmp","masterchief\\4.bmp","masterchief\\5.bmp","masterchief\\6.bmp"};
char chiefammo[30] = "masterchief\\ammo.bmp";
int mposx, mposy;
char button[4][35] = {"Home\\INSTRUCTIONS.bmp","Home\\PLAY_button.bmp", "Home\\EXIT_button.bmp", "Home\\LEADER_BOARD_button.bmp"};
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
char cannon[45] = "E:\\newproject\\cannon\\cannon1.bmp";
char bomb[45] = "E:\\newproject\\cannon\\bomb1.bmp";
bool bombCollusion = false;
char bomCollusion[3][40] = {"cannon\\collusion10.bmp","cannon\\collusion20.bmp","cannon\\collusion30.bmp"};
char damagedCannon[45] = "E:\\newproject\\cannon\\damaged_cannon.bmp";
bool cannonShow = true; // Flag to check if the cannon is still active
bool cannonDamagedShow = false; // Flag to display the damaged cannon

//grenade
char grenadeimg[60] = "E:\\newproject\\grenade\\grenade2.bmp";
bool grenadeShow = false;

char throwgren[8][20] = {"grenade\\1.bmp","grenade\\2.bmp","grenade\\3.bmp","grenade\\4.bmp","grenade\\5.bmp","grenade\\6.bmp","grenade\\7.bmp","grenade\\8.bmp"};

int cannonHP = 2;
int grenade_x = heroCorX+200;
int grenade_y = heroCordinateY+180;
bool isThrowingGrenade = false;
 int grenadeFrameCounter = 0;

//health kit
char crate[40] = "E:\\newproject\\special\\crate.bmp"; 
int crate_x = 0;
int crate_y = screenHeight; // Start at the top of the screen
bool crateShow = false;

// enemy
char enemyimg[7][50] = {"E:\\newproject\\HeroMovement\\Walk\\6N.bmp", "E:\\newproject\\HeroMovement\\Walk\\5N.bmp", "E:\\newproject\\HeroMovement\\Walk\\4N.bmp", "E:\\newproject\\HeroMovement\\Walk\\3N.bmp", "E:\\newproject\\HeroMovement\\Walk\\2N.bmp", "E:\\newproject\\HeroMovement\\Walk\\1N.bmp", "E:\\newproject\\HeroMovement\\Walk\\0N.bmp"};
char Rightenemyimg[7][50] = {"E:\\newproject\\HeroMovement\\Walk\\6NR.bmp", "E:\\newproject\\HeroMovement\\Walk\\5NR.bmp", "E:\\newproject\\HeroMovement\\Walk\\4NR.bmp", "E:\\newproject\\HeroMovement\\Walk\\3NR.bmp", "E:\\newproject\\HeroMovement\\Walk\\2NR.bmp", "E:\\newproject\\HeroMovement\\Walk\\1NR.bmp", "E:\\newproject\\HeroMovement\\Walk\\0NR.bmp"};
char enemy_shoot[30] = "HeroMovement\\Walk\\shot.bmp";
struct enemyall {
    int enemy_x;
    int enemy_y;
    int enemyindex;
    bool enemyShow;
    int hitCounter;
};

int currentPhase = 1; // Track the current phase
int enemiesKilledInPhase = 0; // Track the number of enemies killed in the current phase
const int enemiesPerPhase = 4; // Number of enemies per phase
const int totalPhases = 3; // Total number of phases

int bullet_x;
int bullet_y;
int bulletSpeed = 65; // Speed of the bullet
bool bulletShow = false; // Flag to check if bullet is shown

char lasergun[40] = "E:\\newproject\\special\\laser.bmp";
char laserbullet[40] = "E:\\newproject\\special\\laserbullet.bmp";
int lasergun_x = 0;
int lasergun_y = 0; 
bool lasergunShow = false;
bool laserGunEquipped = false;
bool laserGunDropped = false;

enemyall enemy[ENEMYNUMBER];

char player_dead[5][45] = {"E:\\newproject\\HeroMovement\\dead\\1N.bmp","E:\\newproject\\HeroMovement\\dead\\2N.bmp","E:\\newproject\\HeroMovement\\dead\\3N.bmp","E:\\newproject\\HeroMovement\\dead\\4N.bmp","E:\\newproject\\HeroMovement\\dead\\5N.bmp"};
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

char bullet[50] = "E:\\newproject\\bullet\\newBullet.bmp";
int kill = 0;

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
        if (high_score[i].score < kill)
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
        high_score[pos].score = kill;
    }
}

void show_leaderboard()
{
    iSetColor(255, 0, 0);
    iText(100, 300, "Enter your name: ", GLUT_BITMAP_TIMES_ROMAN_24);

    if (inputMode)
    {
        iText(400, 300, userInput, GLUT_BITMAP_TIMES_ROMAN_24);
    }
    else
    {
        // Displaying the entered name and score
        char displayText[100];
        sprintf(displayText, "Name: %s, Score: %d", userInput, kill);
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


void moveBullet() {
    if (bulletShow) {
        bullet_x += bulletSpeed;
        // Check collision with enemies
        for (int i = 0; i < ENEMYNUMBER; i++) {
            if (enemy[i].enemyShow && bullet_x >= enemy[i].enemy_x /*&& bullet_y >= enemy[i].enemy_y && bullet_y <= enemy[i].enemy_y + 50*/) {
                enemy[i].hitCounter++; // Increment hit counter
                bulletShow = false; // Hide bullet

                if (enemy[i].hitCounter >= 2) {
                    enemy[i].enemyShow = false; // Hide enemy after 2 hits
                    kill++;
                    enemiesKilledInPhase++; // Increment kill count for the current phase
                    printf("ENEMY KILLED:%d",kill);
                }
                break;
            }
        }
        // Check if the bullet goes out of screen
        if (bullet_x > screenWidth) {
            bulletShow = false;
        }
    }
}

int cr = 0;

void checkKillCountAndDropCrate() {
    if (kill >= 6 && !crateShow && cr < 2) {
        cr++; // 2 bar crate drop
        crateShow = true;
        crate_x = 400 + rand() % (screenWidth - 550); // Randomize x position within screen width
        crate_y = screenHeight; // Start crate at the top
    }
}

void moveAndCheckCrateCollision() {
    if (crateShow) {
        crate_y -= 10; // Adjust the speed as needed
        
        // Define crate dimensions for collision detection
        int crateLeft = crate_x;
        int crateRight = crate_x + 150; // Adjust according to the width of the crate
        int crateTop = crate_y + 200;   // Adjust according to the height of the crate
        int crateBottom = crate_y;

        // Check collision with the player's bullet
        if (bulletShow && bullet_x >= crateLeft && bullet_x <= crateRight && 
            bullet_y >= crateBottom && bullet_y <= crateTop) {
            playerHP += 100;
            if (playerHP > 100) {
                playerHP = 100; // Cap the player's health at 100
            }
            crateShow = false; // Hide the crate after it is collected
            bulletShow = false; // Hide bullet
            printf("\n this code worked as the Crate was collected! now Player HP is : %d\n", playerHP);
        }

        // Hide the crate if it goes out of screen
        if (crate_y < 0) {
            crateShow = false;
        }

        // Display crate
        iShowBMP2(crate_x, crate_y, crate, 0);
    }
}

struct enemyBullet {
    int enemybullet_x;
    int enemybullet_y;
    bool enemybulletShow;
};

enemyBullet enemyBullets[ENEMYNUMBER];
char enemyBulletImage[50] = "E:\\newproject\\bullet\\enemy_bullet.bmp";
int enemyBulletSpeed = 20; // Speed of the enemy bullet

void enemyShoot() {
    if (gamestate == 0)
    {
        for (int i = 0; i < ENEMYNUMBER; i++)
        {
            if (enemy[i].enemyShow && !enemyBullets[i].enemybulletShow)
            {
                enemyBullets[i].enemybulletShow = true;
                enemyBullets[i].enemybullet_x = enemy[i].enemy_x;
                enemyBullets[i].enemybullet_y = enemy[i].enemy_y + 270; // Adjust to the correct starting position
            }
        }
    }
}

int playerHitCount = 0; // Counter for player hits
bool playerVisible = true; // Flag for player visibility

void moveEnemyBullets() {
    if (gamestate == 0)
    {
        for (int i = 0; i < ENEMYNUMBER; i++)
        {
            if (enemyBullets[i].enemybulletShow)
            {
                // Move bullet
                enemyBullets[i].enemybullet_x -= enemyBulletSpeed;

                // Define dimensions for collision detection
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

                    enemyBullets[i].enemybulletShow = false; // Hide bullet immediately
                    playerHP -= 10;
                    // playerHitCount++;
                    // printf("Player hit by enemy bullet at x: %d, y: %d. Hit count: %d\n", bulletLeft, heroCordinateY, playerHitCount);

                    // // Check if player should become invisible
                    // if (playerHitCount >= 4) {
                    //     playerVisible = false;
                    //     printf("Player has become invisible!\n");
                    // }

                    continue; // Skip further processing for this bullet
                }

                // Check if the enemy bullet goes out of screen
                if (enemyBullets[i].enemybullet_x < 0)
                {
                    enemyBullets[i].enemybulletShow = false;
                }
            }
        }
    }
}

void dead(){
    if(playerHP <= 0){
        if (deathFrameCounter < 5) {
            iShowBMP2(heroCorX, heroCorY, player_dead[deathFrameCounter], 0);
            deathFrameCounter++;
        }
        if(deathFrameCounter == 5){
            iShowBMP2(heroCorX, heroCorY, player_dead[4], 0);
        }
    }
}

void cannonAction() {
    if(gamestate == 0 && cannonHP>0){
    // Trigger cannon to shoot a bomb if not already active
    if (!bombShow) {
        bombShow = true;
        bomb_x = cannon_x;
        bomb_y = cannon_y + 50; // Adjust the initial height here
    }

    // Handle bomb movement
    if (bombShow) {
        bomb_x -= 20; // Adjust the speed as needed
        int playerTop = heroCordinateY + heroJumpCordinate + 50; // Adjust the player's height as needed
        int playerBottom = heroCordinateY + heroJumpCordinate;

        // Check collision with the player
        if ((bomb_x >= heroCorX+50 && bomb_x <= heroCorX+200) && (playerBottom < 300)) {         // apatoto playerbottom 300 rakhlam
            playerHP -= 20;
            printf("Cannon Bomb Collision Detected bx%d by%d hy%d\n", bomb_x, bomb_y, playerBottom);
            bombShow = false;
            bombCollusion = true;
        }
        printf("bx%d by%d hb%d\n",bomb_x,bomb_y,playerBottom);
        if (bomb_x < 0) { // Reset the bomb if it goes out of the screen
            bombShow = false;
            bomb_x = cannon_x;
            bomb_y = cannon_y + 50; // Reset the height here
        }
    }
    }
}

void showBombCollusion(){                   // cannon bomb player ke hit korle show korbe
    if(bombCollusion){
        for(int i=0;i<3;i++){
        iShowBMP2(heroCorX+50, 120, bomCollusion[i],0);
        }
        bombCollusion = false;
    }
}

void GrenadeThrow() {
    if (isThrowingGrenade) {
        if (grenadeFrameCounter < 8) {
            iShowBMP2(heroCorX, heroCorY, throwgren[grenadeFrameCounter], 0);
            grenadeFrameCounter++;
        } else {
            isThrowingGrenade = false; // Reset after completing animation
        }
    }
}

void cannondamage() {
    int xaxis = abs(cannon_x - grenade_x);
    int yaxis = abs(cannon_y - grenade_y);
    if (xaxis < 150 && yaxis < 150) {
        cannonHP--;
        // Show bomb collision when grenade hits the cannon
        for (int i = 0; i < 3; i++) {
            iShowBMP2(cannon_x-100, cannon_y, bomCollusion[i], 0);
        }
        grenadeShow = false;
    }
    if (cannonHP == 0) {
        cannonShow = false; // Hide the cannon after it is destroyed
        cannonDamagedShow = true; // Show the damaged cannon
        if(bomb_x < cannon_x){
            while(bomb_x >= 0){
                bomb_x-=20;
            }
            bombShow = false;
        }
    }
    printf("cannon_x: %d, cannon_y: %d, grenade_x: %d, grenade_y: %d\n", cannon_x, cannon_y, grenade_x, grenade_y);
}

void throwGrenade() {
    int mid = abs(cannon_x - heroCorX) / 2;
    if (grenadeShow) {
        // Handle grenade movement in two phases
        if (grenade_x < heroCorX + mid) {
            grenade_x += 20;  // Adjust for smoother movement
            grenade_y += 5;   // Move upward
        } else if (grenade_x >= heroCorX + mid && grenade_x < cannon_x + 200) {
            grenade_x += 20;  // Adjust for smoother movement
            grenade_y -= 5;   // Move downward
        } else {
            grenadeShow = false; // Stop showing the grenade if it goes beyond the target
        }

        // Check and handle collision with the cannon
        cannondamage();

        // Display grenade
        iShowBMP2(grenade_x, grenade_y, grenadeimg, 0);
    }
}

void setEnemyVariables() {
    for(int i = 0; i < ENEMYNUMBER; i++) {
        enemy[i].enemy_x = screenWidth + rand() % 500;
        enemy[i].enemy_y = 200;
        enemy[i].enemyindex = rand() % 7;
        enemy[i].enemyShow = true;
        enemy[i].hitCounter = 0;
        enemyBullets[i].enemybulletShow = false;
    }
}

void checkAndSwitchPhases() {
    if (enemiesKilledInPhase >= enemiesPerPhase) {
        currentPhase++;
        enemiesKilledInPhase = 0;

        if (currentPhase <= totalPhases) {
            setEnemyVariables(); // Initialize new set of enemies
        } else {
            // Handle end of game or next steps after all phases are complete
            printf("All phases complete!\n");
            // You can add code here to end the game or reset for another run
        }
    }
}

void checkPhaseCompletionAndDropLaserGun() {
    if (currentPhase > totalPhases && !lasergunShow && !laserGunDropped) {
        lasergunShow = true;
        laserGunDropped = true; // Ensure laser gun only drops once
        lasergun_x = rand() % (screenWidth - 250); // Randomize x position within screen width
        lasergun_y = heroCordinateY; // Place it on the ground at hero's level
    }
}

void checkPlayerLaserGunInteraction() {
    if (lasergunShow && heroCorX >= lasergun_x - 150 && heroCorX <= lasergun_x + 100 &&
        heroCordinateY >= lasergun_y - 100 && heroCordinateY <= lasergun_y + 100) {
        laserGunEquipped = true;
        lasergunShow = false; // Hide the laser gun after it is collected
        printf("Laser gun collected! Player can now shoot laser bullets.\n");
    }

    // Display laser gun if it's still available
    if (lasergunShow) {
        iShowBMP2(lasergun_x, lasergun_y, lasergun, 0);
    }
}

//STAGE 2 CODES ARE HERE
#define ENEMYNUMBER_STAGE2 6
struct enemyStage2 {
    int enemy_x;
    int enemy_y;
    int enemyIndex;
    bool enemyShow;
    int hitCounter; // Add hitCounter to track the number of hits
};

enemyStage2 enemy2[ENEMYNUMBER_STAGE2];

bool supplyCrateShow = false;
int supplyCrate_x = 900;
int supplyCrate_y = 200;

int stage2 = 0; // Variable to track the current stage (0 for stage 1, 1 for stage 2)
bool stage2EnemiesShow = false;

char bombCollision[3][40] = {"E:\\newproject\\cannon\\collusion10.bmp","E:\\newproject\\cannon\\collusion20.bmp","E:\\newproject\\cannon\\collusion30.bmp"};
int stage2StartTime = 0; // Time when stage 2 should start
bool stage2Ready = false; // Flag to indicate if stage 2 is ready to start
bool flagnew = false;
void checkAndDropSupplyCrate() {
    if (kill >= 12 && cannonDamagedShow && !supplyCrateShow && !flagnew) {
        supplyCrateShow = true;
        printf("Supply crate dropped at x: %d, y: %d\n", supplyCrate_x, supplyCrate_y);
    }
}

void checkPlayerSupplyCrateInteraction() {
    if (supplyCrateShow && heroCorX >= supplyCrate_x - 150 && heroCorX <= supplyCrate_x + 50 &&
        heroCorY >= supplyCrate_y - 50 && heroCorY <= supplyCrate_y + 50 && !flagnew) {
        supplyCrateShow = false; // Hide the supply crate after it is collected
        flagnew = true;
        stage2 = 1; // Start stage 2
        stage2StartTime = GetTickCount(); // Get the current time in milliseconds
        printf("Supply crate collected! Stage 2 will begin.\n");
        playerHP = 100;
    }

    // Display supply crate if it's still available
    if (supplyCrateShow) {
        iShowBMP2(supplyCrate_x, supplyCrate_y, crate, 0);
    }
}

void setEnemyVariablesStage2(int phase) {
    for (int i = 0; i < ENEMYNUMBER_STAGE2; i++) {
        if (phase == 1 && i < 3) {
            enemy2[i].enemy_x = screenWidth + rand() % 500; // Enemies come from the right
            enemy2[i].enemy_y = 200;
            enemy2[i].enemyIndex = rand() % 7;
            enemy2[i].enemyShow = true;
        } else if (phase == 2 && i >= 3) {
            enemy2[i].enemy_x = -200 - rand() % 500; // Enemies come from the left
            enemy2[i].enemy_y = 200;
            enemy2[i].enemyIndex = rand() % 7;
            enemy2[i].enemyShow = true;
        }
        enemy2[i].hitCounter = 0; // Initialize hitCounter
        printf("Enemy %d initialized at x: %d, y: %d\n", i, enemy2[i].enemy_x, enemy2[i].enemy_y); // Debug statement
    }
    stage2EnemiesShow = true;
}

int stage2kill = 0;
int stage2enemy = 0;
void enemyMovementStage2() {
    int enemiesOnScreen = 0; // Track the number of enemies on the screen
    if (stage2EnemiesShow) {
        for (int i = 0; i < ENEMYNUMBER_STAGE2; i++) {
            if (enemy2[i].enemyShow) {
                if (enemiesOnScreen >= 3) {
                    break; // Stop adding more enemies if there are already 3 on screen
                }
                enemiesOnScreen++; // Increment the counter for enemies on screen
                
                if (i < 3) { // First phase enemies come from the right
                    if (enemy2[i].enemy_x > heroCorX) {
                        enemy2[i].enemy_x -= 10; // Move enemies from the right
                        iShowBMP2(enemy2[i].enemy_x, enemy2[i].enemy_y, enemyimg[enemy2[i].enemyIndex], 0);
                    }
                } else { // Last 3 enemies come from the left
                    if (enemy2[i].enemy_x < heroCorX) {
                        enemy2[i].enemy_x += 10; // Move enemies from the left
                        iShowBMP2(enemy2[i].enemy_x, enemy2[i].enemy_y, Rightenemyimg[enemy2[i].enemyIndex], 0);
                    }
                }

                // Check collision with the player
                if (enemy2[i].enemy_x >= heroCorX && enemy2[i].enemy_x <= heroCorX + 100 &&
                    enemy2[i].enemy_y >= heroCorY && enemy2[i].enemy_y <= heroCorY + 280) {
                    playerHP -= 25; // Reduce player's health
                    stage2enemy++;
                    printf("Player hit by enemy! Player HP: %d\n", playerHP);
                    enemy2[i].enemyShow = false; // Hide enemy after collision
                    for(int j = 0; j < 3; j++) {
                        iShowBMP2(enemy2[i].enemy_x, enemy2[i].enemy_y, bombCollision[j], 0); // Show explosion image
                    }
                    if (stage2enemy == 3) {
                        printf("First phase of stage 2 complete. Initializing second phase enemies.\n");
                        setEnemyVariablesStage2(2); // Initialize second phase of stage 2 enemies
                    }
                }
            }
        }
    }
}


void checkAndStartStage2() {
    if (kill >= 12 && stage2 == 0 && cannonDamagedShow) {
        stage2 = 1;
        stage2StartTime = GetTickCount(); // Get the current time in milliseconds
        printf("All stage 1 enemies defeated. Stage 2 will begin in 20 seconds.\n");
    }
}

void updateStageTransition() {
    if (stage2 == 1 && !stage2Ready) {
        int currentTime = GetTickCount(); // Get the current time in milliseconds
        if (currentTime - stage2StartTime >= 10000) { // Check if 20 seconds have passed
            setEnemyVariablesStage2(1); // Initialize first phase of stage 2 enemies
            stage2Ready = true; // Mark stage 2 as ready
            printf("Stage 2 started. First phase enemies will appear.\n");
        }
    }
}

void moveBulletstage2() {
    if (bulletShow) {
        bullet_x += bulletSpeed * bulletDirection; // Update bullet position based on direction
        printf("Bullet at x: %d, direction: %d\n", bullet_x, bulletDirection); // Debug statement

        // Check collision with enemies in stage 2
        for (int i = 0; i < ENEMYNUMBER_STAGE2; i++) {
            // Ensure enemy is within visible screen bounds before considering a collision
            if (enemy2[i].enemyShow && enemy2[i].enemy_x >= 0 && enemy2[i].enemy_x <= screenWidth) {
                if ((bulletDirection == 1 && bullet_x >= enemy2[i].enemy_x) || (bulletDirection == -1 && bullet_x <= enemy2[i].enemy_x)) {
                    enemy2[i].hitCounter++; // Increment hit counter
                    bulletShow = false; // Hide bullet
                    printf("Bullet hit enemy at index %d, enemy_x: %d\n", i, enemy2[i].enemy_x); // Debug statement

                    if (enemy2[i].hitCounter >= 4) {
                        enemy2[i].enemyShow = false; // Hide enemy after 4 hits
                        kill++;
                        stage2enemy++;
                        stage2kill++;
                        printf("ENEMY KILLED: Stage 2: %d\n", stage2kill);

                        if (stage2enemy == 3) {
                            printf("First phase of stage 2 complete. Initializing second phase enemies.\n");
                            setEnemyVariablesStage2(2); // Initialize second phase of stage 2 enemies
                        }
                    }
                    break;
                }
            }
        }
        // Check if the bullet goes out of screen
        if (bullet_x > screenWidth || bullet_x < 0) {
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
int bossHP = 500; // Example health for the boss
bool bossShow = false;
bool bossAmmoShow = false;
int bossAmmo_x;
int bossAmmo_y;
int bossAmmoSpeed = 50; // Speed of the boss's ammo
int bossIndex = 0;
bool bossMoving = true; // Indicates if the boss is moving to its position
bool shootingLowerBullet = true; // True if shooting lower bullet, false if shooting upper bullet
char bossdead[30] = "masterchief\\chiefdead.bmp";
void setMainBoss();
void checkAndStartStage3();
void moveMainBoss();
void checkBossCollision();
void bossShoot();
void moveBossBullets();

void setMainBoss() {
    boss_x = screenWidth + 500; // Start offscreen
    boss_y = 200;
    bossShow = true;
    bossMoving = true; // Start moving the boss
}

void checkAndStartStage3() {
    int check = 12 + stage2kill + (100-playerHP)/25;
    if (check >= 18 && playerHP > 0 && !stage3Ready) {
        stage3Ready = true; // Mark stage 3 as ready
        stage3StartTime = GetTickCount(); // Get the current time in milliseconds
        setMainBoss(); // Initialize main boss
    }
}

void checkBossCollision() {
    if (bulletShow && bullet_x >= boss_x - 100 && bullet_x <= boss_x + 200 && bullet_y >= boss_y && bullet_y <= boss_y + 300) {
        bossHP -= 10; // Reduce boss health
        bulletShow = false; // Hide bullet
        printf("Boss hit! Boss HP: %d\n", bossHP);
        if (bossHP <= 0 && !bossDefeated) {
            bossShow = false; // Hide boss
            bossDefeated = true;
            bossDeathTime = GetTickCount(); // Record the time of boss defeat
            printf("Boss defeated!\n");
            //iShowBMP2(1600,200,bossdead,0);
        }
    }
}

void bossShoot() {
    if (bossShow && !bossAmmoShow) {
        bossAmmoShow = true;
        bossAmmo_x = boss_x;
        if (shootingLowerBullet) {
            bossAmmo_y = 210; // Lower bullet
        } else {
            bossAmmo_y = 410; // Upper bullet increased by 60
        }
        shootingLowerBullet = !shootingLowerBullet; // Alternate for the next shot
    }
}

void moveBossBullets() {
    if (bossAmmoShow) {
        // Move bullet
        bossAmmo_x -= bossAmmoSpeed;

        // Define dimensions for collision detection
        int bulletRight = bossAmmo_x + 20;
        int bulletLeft = bossAmmo_x;
        int playerLeft = heroCorX;
        int playerRight = heroCorX + 100;
        int playerTop = heroCorY + heroJumpCordinate + 280;
        int playerBottom = heroCorY + heroJumpCordinate;

        // Adjust collision detection if the player is sitting
        if (sit) {
            playerTop = heroCorY + heroJumpCordinate + 180; // Adjust to a lower height when sitting
        }

        // Check collision with the player
        if (playerVisible && (bossAmmo_x >= playerLeft && bossAmmo_x <= playerRight) &&
            (bossAmmo_y >= playerBottom && bossAmmo_y <= playerTop)) {
            bossAmmoShow = false; // Hide bullet immediately
            playerHP -= 20;
            printf("Player hit by boss bullet! Player HP: %d\n", playerHP);
        }

        // Check if the boss bullet goes out of screen
        if (bossAmmo_x < 0) {
            bossAmmoShow = false;
        }
    }
}

void moveMainBoss() {
    if (bossShow) {
        if (bossMoving) {
            boss_x -= 10; // Move boss to the left
            if (boss_x <= 1600) { // Stop the boss at position (1600, 200)
                bossMoving = false;
            }
        } else {
            iShowBMP2(boss_x, boss_y, masterchief[bossIndex], 0);
            bossIndex++;
            if (bossIndex >= 6) {
                bossIndex = 0;
            }

            // Boss shooting logic
            if (!bossAmmoShow) {
                bossShoot();
            }

            // Move boss ammo
            moveBossBullets();

            // Display boss ammo
            if (bossAmmoShow) {
                iShowBMP2(bossAmmo_x, bossAmmo_y, chiefammo, 0);
            }
        }
    }
}

void endgame() {
    DWORD currentTime = GetTickCount();

    if (bossDefeated && !finished) {
        PlaySound("E:\\newproject\\Music\\WhatIHaveDone1.wav", NULL, SND_FILENAME | SND_ASYNC);
        finished = true;
        bossDeathTime = currentTime; // Record the time when music started playing
    }

    if (finished && !endgameImageShown && currentTime - bossDeathTime >= 10000) { // 10 seconds have passed
        iShowBMP(0, 0, complete);
        endgameImageShown = true;
    }
    
}

int counter = 1;
int count2 = 1;

void iDraw() {
    iClear();
    printf("KILLLLLLLLLLLL %d\n", kill);
    if (playerHP <= 0) {
        gamestate = 5;
    }
    if (gamestate == -1) {
        iShowBMP(0, 0, homemenu);
        for (int i = 0; i < 4; i++) {
            iShowBMP2(bCordinate[i].x, bCordinate[i].y, button[i], 255);
        }
    } else if (gamestate == 0) { // Game will start
        char displaytext3[100];
        Menumusic = false;
        if (!Menumusic) {
            PlaySound(0, 0, 0);
        }

        iShowBMP(0, 0, background);
        enemyMovement();

        iSetColor(255, 255, 255);
        iText(10, 1050, "PRESS 'B' TO PAUSE", GLUT_BITMAP_TIMES_ROMAN_24);

        char displaytext4[100];
        iSetColor(255, 255, 255);
        sprintf(displaytext4, "SCORE: %d", kill);
        iText(10, 980, displaytext4, GLUT_BITMAP_TIMES_ROMAN_24);

        if (bulletShow) {
            if (laserGunEquipped) {
                iShowBMP2(bullet_x, bullet_y, laserbullet, 0);
            } else {
                iShowBMP2(bullet_x, bullet_y, bullet, 0);
            }
        }

        if (stage2Ready) {
            moveBulletstage2(); // Move bullet in stage 2
            enemyMovementStage2(); // Handle stage 2 enemy movement and collision
            checkAndStartStage3(); // Check if it's time to start stage 3
        } else {
            moveBullet(); // Move bullet in stage 1
        }

        if (stage3Ready) {
            moveMainBoss(); // Handle main boss movement and shooting
            checkBossCollision(); // Check if the boss is hit
            if(bossHP > 0) {
                iSetColor(255, 255, 255);
                sprintf(displaytext3, "BOSS HEALTH: %d", bossHP);
                iText(1400, 1050, displaytext3, GLUT_BITMAP_TIMES_ROMAN_24);
            } else if (bossDefeated) {
                cannonDamagedShow = false;
                iSetColor(255, 255, 255);
                iText(1400, 1050, "MISSION ACCOMPLISHED", GLUT_BITMAP_TIMES_ROMAN_24);
                kill = 30+playerHP;
                if(count2 == 1){
                    inputMode = true;
                    count2++;
                    endgame(); // Call endgame function to play music and show the image after 10 seconds
                }
                
                read_high_scores();
                show_leaderboard();
            }
        }

        for (int i = 0; i < ENEMYNUMBER; i++) {
            if (enemyBullets[i].enemybulletShow) {
                iShowBMP2(enemyBullets[i].enemybullet_x, enemyBullets[i].enemybullet_y, enemyBulletImage, 0);
            }
        }
        moveEnemyBullets();

        if (cannonShow) { // Only show the cannon if it is not destroyed
            iShowBMP2(cannon_x, cannon_y, cannon, 0);
        } else if (cannonDamagedShow) {
            iShowBMP2(cannon_x, cannon_y, damagedCannon, 0);
        }

        // Show cannon bomb
        if (bombShow) {
            iShowBMP2(bomb_x, bomb_y, bomb, 0);
        }
        showBombCollusion(); // Show bomb collision

        GrenadeThrow(); // grenade throw animation
        throwGrenade(); // grenade movement

        if (playerVisible && !isThrowingGrenade) {
            if (jump) {
                if (jumpUp) {
                    iShowBMP2(heroCorX, heroCordinateY + heroJumpCordinate, herojump, 0);
                } else {
                    iShowBMP2(heroCorX, heroCordinateY + heroJumpCordinate, herojump, 0);
                }
            } else if (sit) {
                iShowBMP2(heroCorX, heroCorY, herosit, 0);
            } else if (!standPosition) {
                if (facingRight) {
                    iShowBMP2(heroCorX, heroCorY, herowalk[heroIndex], 0);
                } else {
                    iShowBMP2(heroCorX, heroCorY, leftwalk[heroIndex], 0);
                }
                standCounter++;
                if (standCounter >= 20) {
                    standCounter = 0;
                    heroIndex = 0;
                    standPosition = true;
                }
            } else {
                iShowBMP2(heroCorX, heroCorY, heroStand, 0);
            }
        }

        checkKillCountAndDropCrate(); // Check if crate should drop
        moveAndCheckCrateCollision(); // Move crate and check for collision

        checkPhaseCompletionAndDropLaserGun(); // Check if laser gun should drop
        checkPlayerLaserGunInteraction(); // Check if player collects the laser gun

        checkAndSwitchPhases(); // Check if it's time to switch phases

        checkAndDropSupplyCrate(); // Check if it's time to drop the supply crate
        checkPlayerSupplyCrateInteraction(); // Check if player collects the supply crate

        updateStageTransition(); // Check if it's time to start stage 2

        char displaytext2[100];
        if (playerHP > 0) {
            iSetColor(255, 255, 255);
            sprintf(displaytext2, "Health bar: %d", playerHP);
            iText(900, 1050, displaytext2, GLUT_BITMAP_TIMES_ROMAN_24);
        }

    } else if (gamestate == 1) { // End game
        iShowBMP(0, 0, exitgame);
        exit(0);
    } else if (gamestate == 2) { // Show leaderboard
        iShowBMP(0, 0, fail);
        read_high_scores();
        show_leaderboard();
    }else if(gamestate == 6){
        iShowBMP(0,0,instruct);
    }
    else if (gamestate == 5) { // Player dead
        iShowBMP(0, 0, homemenu);
        Menumusic = true;
        if (Menumusic) {
            PlaySound("E:\\newproject\\Music\\Menu_BGM.wav", NULL, SND_LOOP | SND_ASYNC);
        }

        iShowBMP(0, 0, background);
        //enemyMovement();

        playerVisible = false;
        dead();
        if (counter == 1) {
            inputMode = true;
            counter++;
        }
        read_high_scores();
        show_leaderboard();

        gamestate = 2;
        // iShowBMP(0, 0, fail);
    }

    printf("\nPlayer Health Remaining is: %d\n", playerHP);
    if (playerHP <= 0) {
        iSetColor(255, 0, 0);
        iText(900, 1050, "DEAD", GLUT_BITMAP_TIMES_ROMAN_24);
    }
}



void iMouseMove(int mx, int my) {
    printf("x = %d, y= %d\n", mx, my);
}

void iMouse(int button, int state, int mx, int my) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        for(int i = 0; i < 3; i++) {
            if(mx >= 39 && mx <= 232 && my >= 561 && my <= 618) { // 200x60 size button
                gamestate = 0;
            }
            if(mx >= 39 && mx <= 232 && my >= 445 && my <= 502) { // 200x60 size button
                gamestate = 1;
            }
            if(mx >= 39 && mx <= 232 && my >= 329 && my <= 386) { // 200x60 size button
                gamestate = 2;
            }
            if(mx >= 39 && mx <= 232 && my >= 677 && my <= 734){
                gamestate = 6;
            }
        }
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        //place your codes here
        // x -= 10;
        // y -= 10;
    }
}

bool directionRight = true; // True if 'd' is pressed, false if 'a' is pressed

void iKeyboard(unsigned char key) {
    if (key == 'q') {
        exit(0);
    } else if (key == 'w') {
        if (!jump) {
            jump = true;
            jumpUp = true;
            sit = false;
        }
    } else if (key == 's') {
        sit = true;
    } else if (key == ' ') {
        if (stage2Ready && !bulletShow) { // Only fire a new bullet if no bullet is currently shown in Stage 2
            bulletShow = true;
            bulletDirection = facingRight ? 1 : -1; // Set bullet direction based on facingRight

            if (sit) {
                bullet_x = facingRight ? (heroCorX + 280) : (heroCorX + 200);
                bullet_y = heroCordinateY + 158;
            } else {
                bullet_x = facingRight ? (heroCorX + 280) : (heroCorX + 200);
                bullet_y = heroCordinateY + 280;
            }

            if (laserGunEquipped) {
                iShowBMP2(bullet_x, bullet_y - 5, laserbullet, 0);
            } else {
                iShowBMP2(bullet_x, bullet_y, bullet, 0);
            }
        } else if (!stage2Ready && !bulletShow) { // Handle shooting in other stages
            bulletShow = true;
            if (sit) {
                bullet_x = heroCorX + 280;
                bullet_y = heroCordinateY + 158;
            } else {
                bullet_x = heroCorX + 280;
                bullet_y = heroCordinateY + 280;
            }

            if (laserGunEquipped) {
                iShowBMP2(bullet_x, bullet_y - 5, laserbullet, 0);
            } else {
                iShowBMP2(bullet_x, bullet_y, bullet, 0);
            }
        }
    } else if (key == 'g') {
        if (kill >= 12 && !isThrowingGrenade && !grenadeShow && !jump && cannonHP != 0) {
            isThrowingGrenade = true;
            grenadeFrameCounter = 0;
            grenade_x = heroCorX + 200; // Initialize grenade position
            grenade_y = heroCorY + 180;
            grenadeShow = true; // Set the grenade to show and move
        }
    } else if (key == 'd') {
        if (stage2Ready) { // Only allow direction change and shooting in Stage 2
            facingRight = true; // Player is facing right
            heroCorX += 10;
            heroIndex++;
            if (heroIndex >= 7) {
                heroIndex = 0;
            }
        } else if (currentPhase > 3) { // Other cases for stage 1
            heroCorX += 10;
            heroIndex++;
            if (heroIndex >= 7) {
                heroIndex = 0;
            }
        }

        standPosition = false;
    } else if (key == 'a') {
        if (stage2Ready) { // Only allow direction change and shooting in Stage 2
            facingRight = false; // Player is facing left
            heroCorX -= 10;
            heroIndex++;
            if (heroIndex >= 7) {
                heroIndex = 0;
            }
        } else if (currentPhase > 3) { // Other cases for stage 1
            heroCorX -= 10;
            heroIndex--;
            if (heroIndex < 0) {
                heroIndex = 7;
            }
        }

        standPosition = false;
    }
    else if(key == 'b' && (gamestate==2 || gamestate == 0 || gamestate == 6)){
            gamestate = -1;
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

void iSpecialKeyboard(unsigned char key) {
    if (key == GLUT_KEY_END) {
        exit(0);
    }
}

void change() {
    if(jump) {
        if(jumpUp) {
            heroJumpCordinate += 12;        // jump speed
            if(heroJumpCordinate >= JUMPLIMIT) {
                jumpUp = false;
            }
        } else {
            heroJumpCordinate -= 8;     // jump er por niche namar code
            if(heroJumpCordinate < 0) {
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

int main() {
    setEnemyVariables();

    iSetTimer(60, change);
    iSetTimer(100, change_enemy);
    iSetTimer(1000, enemyShoot);
    iSetTimer(1000, dead);
    iSetTimer(50, cannonAction); // Single timer to handle bomb movement and shooting

    int sum = 100;
    for (int i = 3; i >= 0; i--) { // Home button declaration
        bCordinate[i].x = 50;
        bCordinate[i].y = sum;
        sum += 150;
    }
    // score = kill * 10;
    if (Menumusic) {
        PlaySound("E:\\newproject\\Music\\Menu_BGM.wav", NULL, SND_LOOP | SND_ASYNC);
    }
    if(finished){
        PlaySound("E:\\newproject\\Music\\WhatIHaveDone1.wav", NULL, SND_LOOP | SND_ASYNC);
    }
    // place your own initialization codes here.
    iInitialize(screenWidth, screenHeight, "LookingForSotruz");
    return 0;
}

