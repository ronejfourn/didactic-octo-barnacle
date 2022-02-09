#pragma once
#include "entity.h"
#include <vector>

class Weapon;
class Enemy;

class Player : public Entity {
    Weapon *_weapon;
public:
    Player();
    Player(float center_x, float center_y);
    void Restart(float center_x, float center_y);

    void MoveUp   ();
    void MoveLeft ();
    void MoveDown ();
    void MoveRight();

    void Update(float deltatime);
    void Draw(Graphics *g, Vec2f offset) override;
    void TakeDamage(float damage) override;
    void Seek(Vec2f pos) override;
    void Die() override;

    void Attack();
    void Collision(std::vector<Enemy *> enemies, Map &map, float deltatime);
};
