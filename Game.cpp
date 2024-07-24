#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <cmath>
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "ObjectsFactory.hpp"

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
std::list<GameObject*> bullets;

float timeCounter = 0;
int currentDirection = 1;
bool isSpacePressed = false;

float bulletsIntervalInSeconds = 5;

void processInput();
void processPlayerMovement(float delta);
void processPlayer(GameObject* player, bool isMirrored);
void processBullets(float delta);

Renderer* renderer;
ObjectsFactory* factory;

// initialize game data in this function
void initialize()
{
    renderer = new Renderer((uint32_t*)buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
    factory = new ObjectsFactory(renderer);

    firstPlayer = factory->Instantiate(Vector2D(0, 0), BoxCollider(Vector2D(40, 40)));
    secondPlayer = factory->Instantiate(Vector2D(0, 0), BoxCollider(Vector2D(40, 40)));

    bullets = std::list<GameObject*>();
}

// free game data in this function
void finalize()
{
    factory->Destroy(firstPlayer);
    factory->Destroy(secondPlayer);

    free(renderer);
    free(factory);
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    processInput();
    processPlayerMovement(dt);
    processBullets(dt);
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

void processBullets(float delta) {
    bulletsIntervalInSeconds -= delta;
    if (bulletsIntervalInSeconds < 0) {
        bulletsIntervalInSeconds = 5;

        bullets.push_back(factory->Instantiate(
            Vector2D(SCREEN_WIDTH/2, 20), 
            BoxCollider(Vector2D(20, 20))
        ));
    }
}

void draw()
{
    renderer->Update();
}
