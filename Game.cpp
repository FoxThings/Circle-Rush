#include "Engine.h"
#include <stdlib.h>
#include <memory.h>
#include <cmath>
#include "GameObject.hpp"
#include "Renderer.hpp"
#include "ObjectsFactory.hpp"
#include <time.h>
#include "Simulation.hpp"

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

const float speed = 4;
const float radius = 150;

GameObject* firstPlayer;
GameObject* secondPlayer;
std::list<Bullet> bullets;

GameObject* ui1Digits;
GameObject* ui10Digits;
GameObject* ui100Digits;

int score = 0;
float timeCounter = 0;
int currentDirection = 1;
bool isSpacePressed = false;

float bulletsIntervalInSeconds = 2;

void processInput();
void processPlayerMovement(float delta);
void processPlayer(GameObject* player, bool isMirrored);
void processBullets(float delta);
float randomRange(int left, int right);
void updateUi();

Renderer* renderer;
Simulation* simulation;
ObjectsFactory* factory;

Sprite* enemySprite;
Sprite* friendSprite;
Sprite* playerSprite;
std::vector<Sprite*> numbers;

// initialize game data in this function
void initialize()
{
    srand((uint32_t)time(NULL));

    renderer = new Renderer((uint32_t*)buffer, SCREEN_WIDTH, SCREEN_HEIGHT);
    simulation = new Simulation();
    factory = new ObjectsFactory(renderer, simulation);

    enemySprite = new Sprite("./assets/Enemy.png");
    friendSprite = new Sprite("./assets/Friend.png");
    playerSprite = new Sprite("./assets/Player.png");
    for (int i = 0; i <= 9; ++i) {
        Sprite* number = new Sprite(std::string("./assets/font/") + std::to_string(i) + std::string(".png"));
        numbers.push_back(number);
    }

    ui1Digits = factory->Instantiate(Vector2D(SCREEN_WIDTH - 70, SCREEN_HEIGHT - 70), numbers[0], BoxCollider(Vector2D(30, 40)));
    ui10Digits = factory->Instantiate(Vector2D(SCREEN_WIDTH - 140, SCREEN_HEIGHT - 70), numbers[0], BoxCollider(Vector2D(30, 40)));
    ui100Digits = factory->Instantiate(Vector2D(SCREEN_WIDTH - 210, SCREEN_HEIGHT - 70), numbers[0], BoxCollider(Vector2D(30, 40)));

    firstPlayer = factory->Instantiate(Vector2D(0, 0), playerSprite, BoxCollider(Vector2D(30, 40)));
    secondPlayer = factory->Instantiate(Vector2D(0, 0), playerSprite, BoxCollider(Vector2D(30, 40)));

    bullets = std::list<Bullet>();
}

// free game data in this function
void finalize()
{
    factory->Destroy(firstPlayer);
    factory->Destroy(secondPlayer);

    free(enemySprite);
    free(friendSprite);
    free(playerSprite);
    for (int i = 0; i <= 9; ++i) {
        free(numbers[i]);
    }
    numbers.clear();

    free(renderer);
    free(simulation);
    free(factory);
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
    processInput();
    processPlayerMovement(dt);
    processBullets(dt);

    simulation->Update();
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

        // 1 : 1
        bool* isFriend = new bool(randomRange(0, 1) == 0);
        Sprite* sprite = *isFriend ? friendSprite : enemySprite;
        
        GameObject* obj = factory->Instantiate(
            spawnPoint,
            sprite,
            BoxCollider(
                Vector2D(20, 30),
                [isFriend](BoxCollider* self, BoxCollider* other) {
                    if (other == &firstPlayer->collider || other == &secondPlayer->collider) {
                        if (*isFriend) {
                            ++score;
                        }
                        else {
                            score = 0;
                        }
                        updateUi();

                        free(isFriend);

                        GameObject* obj = simulation->GetObjectByCollider(self);
                        for (std::list<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it) {
                            if (it->object == obj) {
                                bullets.erase(it);
                                break;
                            }
                        }
                        factory->Destroy(obj);
                    }
                }
            )
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

void updateUi() {
    ui1Digits->ChangeSprite(numbers[score % 10]);
    ui10Digits->ChangeSprite(numbers[score / 10 % 10]);
    ui100Digits->ChangeSprite(numbers[score / 100 % 10]);
}

float randomRange(int left, int right) {
    return (float)(std::rand() % (right - left + 1) + left);
}

void draw()
{
    renderer->Update();
}
