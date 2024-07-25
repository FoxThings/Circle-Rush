#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <cmath>
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "ObjectsFactory.hpp"
#include <time.h>

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

struct Bullet {
    Bullet(GameObject* obj, Vector2D dir, float speed) : object(obj), direction(dir), speed(speed) {};

    GameObject* object;
    Vector2D direction;
    float speed;
};

const float speed = 5;
const float radius = 100;

GameObject* firstPlayer;
GameObject* secondPlayer;
std::list<Bullet> bullets;

float timeCounter = 0;
int currentDirection = 1;
bool isSpacePressed = false;

float bulletsIntervalInSeconds = 2;

void processInput();
void processPlayerMovement(float delta);
void processPlayer(GameObject* player, bool isMirrored);
void processBullets(float delta);
float randomRange(int left, int right);

Renderer* renderer;
ObjectsFactory* factory;

// initialize game data in this function
void initialize()
{
    srand((uint32_t)time(NULL));

    renderer = new Renderer((uint32_t*)buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
    factory = new ObjectsFactory(renderer);

    firstPlayer = factory->Instantiate(Vector2D(0, 0), BoxCollider(Vector2D(40, 40)));
    secondPlayer = factory->Instantiate(Vector2D(0, 0), BoxCollider(Vector2D(40, 40)));

    bullets = std::list<Bullet>();
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
        bulletsIntervalInSeconds = randomRange(1, 3);

        Vector2D spawnPoint = Vector2D(SCREEN_WIDTH / 2 + randomRange(-300, 300), -20);

        GameObject* obj = factory->Instantiate(
            spawnPoint,
            BoxCollider(Vector2D(20, 20))
        );

        Vector2D center = Vector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        int offsetBounds = int(radius / 2);
        Vector2D offset = Vector2D(randomRange(-offsetBounds, offsetBounds), randomRange(-offsetBounds, offsetBounds));
        Vector2D destination = (center + offset) - spawnPoint;

        bullets.push_back(Bullet(
            obj, 
            destination.Normalize(), 
            randomRange(200, 300)
        ));
    }

    for (std::list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
        it->object->Move(it->direction * it->speed * delta);
    }
}

float randomRange(int left, int right) {
    return (float)(std::rand() % (right - left + 1) + left);
}

void draw()
{
    renderer->Update();
}
