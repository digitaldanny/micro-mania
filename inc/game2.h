#ifndef INC_GAME2_H_
#define INC_GAME2_H_

/*********************************************** Includes ********************************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "G8RTOS.h"
#include "cc3100_usage.h"
#include "GLCD.h"
#include "time.h"
#include "math.h"
#include "common_threads.h"
/*********************************************** Includes ********************************************************************/
#define MAX_NUM_OF_BALLS 20
#define MAX_NUM_OF_PLAYERS 1
#define BALL_SIZE 2
#define ARENA_MAX_X 320
#define ARENA_MAX_Y 240
#define ARENA_MIN_X 0
#define ARENA_MIN_Y 20
/* Maximum ball speed */
#define MAX_BALL_SPEED               4
#define MIN_BALL_SPEED               1
#define LIVES 5
#define BALL_GEN_SLEEP      200 // 10 second increments increasing linearly

/* Background color - Black */
#define BACK_COLOR                   LCD_BLACK
/*********************************************** Game Functions *********************************************************************/

void game2_addHostThreads();    // called by the menu to initialize this game
void game2_addClientThreads();  // called by the menu to initialize this game

/*********************************************** structs *********************************************************************/
#pragma pack ( push, 1)
/*
 * Struct to be sent from the client to the host
 */
typedef struct
{
    uint32_t IP_address;
    int16_t displacement;
    uint8_t playerNumber;
    bool ready;
    bool joined;
    bool acknowledge;
} Game2_SpecificPlayerInfo_t;

/*
 * General player info to be used by both host and client
 * Client responsible for translation
 */
typedef struct
{
    int16_t currentCenterX;
    int16_t currentCenterY;
    uint16_t num_lives;
    uint16_t RunTime;
    uint16_t color;
} Game2_GeneralPlayerInfo_t;
/*
 * Struct of all the balls, only changed by the host
 */
typedef struct
{
    int16_t currentCenterX;
    int16_t currentCenterY;
    uint16_t color;
    bool alive;
    bool kill;
} Game2_Ball_t;


/*
 * Struct to be sent from the host to the client
 */
typedef struct
{
    Game2_SpecificPlayerInfo_t player;
    Game2_GeneralPlayerInfo_t players[MAX_NUM_OF_PLAYERS];
    Game2_Ball_t balls[MAX_NUM_OF_BALLS];
    uint16_t numberOfBalls;
    bool winner;
    bool gameDone;
    uint8_t LEDScores[2];
    uint8_t overallScores[2];
} Game2_GameState_t;
#pragma pack ( pop )

/*
 * Struct of all the previous ball locations, only changed by self for drawing!
 */
typedef struct
{
    int16_t CenterX;
    int16_t CenterY;
}Game2_PrevBall_t;

/*
 * Struct of all the previous players locations, only changed by self for drawing
 */
typedef struct
{
    int16_t CenterX;
    int16_t CenterY;
}Game2_PrevPlayer_t;
/*********************************************** Client Threads *********************************************************************/
/*
 * Thread for client to join game
 */
void Game2_JoinGame();

/*
 * Thread that receives game state packets from host
 */
void Game2_ReceiveDataFromHost();

/*
 * Thread that sends UDP packets to host
 */
void Game2_SendDataToHost();

/*
 * Thread to read client's joystick
 */
void Game2_ReadJoystickClient();

/*
 * End of game for the client
 */
void Game2_EndOfGameClient();

/*********************************************** Client Threads *********************************************************************/


/*********************************************** Host Threads *********************************************************************/
/*
 * Thread for the host to create a game
 */
void Game2_CreateGame();

/*
 * Thread that sends game state to client
 */
void Game2_SendDataToClient();

/*
 * Thread that receives UDP packets from client
 */
void Game2_ReceiveDataFromClient();

/*
 * Thread to read host's joystick
 */
void Game2_ReadJoystickHost();

/*
 * End of game for the host
 */
void Game2_EndOfGameHost();

void Game2_GenerateBall();

void Game2_MoveBall();

void Game2_UpdateBallColors();

/*********************************************** Host Threads *********************************************************************/


/*********************************************** Common Threads *********************************************************************/
/*
 * Idle thread
 */
void Game2_IdleThread();

/*
 * Thread to draw all the objects in the game
 */
void Game2_DrawObjects();


/*********************************************** Common Functions *********************************************************************/

/*
 * Initializes and prints initial game state
 */
void Game2_InitBoardState(uint8_t num_lives, uint16_t P1_runTime, uint16_t P2_runTime);

void Game2_UpdatePlayerStatus();

/*********************************************** Aperiodic Threads *********************************************************************/
void Game2_ButtonPress ( void );

#endif /* INC_GAME2_H_ */
