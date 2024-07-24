#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <cmath>
#include "GameObject.hpp"

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, 'A', 'B')
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  clear_buffer() - set all pixels in buffer to 'black'
//  is_window_active() - returns true if window is active
//  schedule_quit_game() - quit game after act()

const float speed = 5;
const float radius = 100;

GameObject* firstPlayer;
GameObject* secondPlayer;

float timeCounter = 0;
int currentDirection = 1;
bool isSpacePressed = false;

void processInput();
void processPlayerMovement(float delta);
void processPlayer(GameObject* player, bool isMirrored);

// initialize game data in this function
void initialize()
{
    firstPlayer = new GameObject(Vector2D(0, 0), BoxCollider(Vector2D(40, 40)));
    secondPlayer = new GameObject(Vector2D(0, 0), BoxCollider(Vector2D(40, 40)));
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    processInput();
    processPlayerMovement(dt);
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
    // clear backbuffer
    memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
    firstPlayer->Render((uint32_t*)buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
    secondPlayer->Render((uint32_t*)buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

// free game data in this function
void finalize()
{
    free(firstPlayer);
    free(secondPlayer);
}

void processInput() {
    if (!is_key_pressed(VK_SPACE) && isSpacePressed) {
        isSpacePressed = false;
    }

    if (is_key_pressed(VK_SPACE) && !isSpacePressed) {
        currentDirection *= -1;
        isSpacePressed = true;
    }

    if (is_key_pressed(VK_ESCAPE))
        schedule_quit_game();
}

void processPlayerMovement(float delta) {
    timeCounter += delta * speed * currentDirection;
    processPlayer(firstPlayer, false);
    processPlayer(secondPlayer, true);
}

void processPlayer(GameObject* player, bool isMirrored) {
    int mirroring = isMirrored ? -1 : 1;

    float xOffset = SCREEN_WIDTH / 2;
    float yOffset = SCREEN_HEIGHT / 2;

    float x = mirroring * cos(timeCounter) * radius + xOffset;
    float y = mirroring * sin(timeCounter) * radius + yOffset;

    player->SetPosition(Vector2D(x, y));
}
