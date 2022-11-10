// RPGTest
// Player.hpp
// Created on 2022-10-04 by Justyn Durnford
// Last modified on 2022-11-09 by Justyn Durnford
// Header file for the Player class.

#pragma once

#include "Namespace.hpp"

#include "Entity.hpp"

#include "InputManager.hpp"

#include "Room.hpp"

// 
class Player : public IDObject, public Entity
{
    public:

    Texture texture;
    array<AnimatedSprite, 8> walkingSprites;
    Ptr<const Direction> lastDirection;
    Ptr<const Direction> currentDirection;
    Ptr<InputManager> inputManager;
    Ptr<Room> room;
    FloatRect hitbox;
    array<Collision, 4> vertexCollisionStates;

    // 
    Player();

    // 
    Player(u16 new_id, const string& new_name, const Vector2f& new_position, const Vector2f& new_velocity, 
           Ptr<const Direction> new_direction, Ptr<InputManager> new_inputManager, Ptr<Room> new_room);

    // 
    static void loadFail(const path& filepath, const wstring& message);

    // 
    void loadSpriteData(const path& folder);

    // 
    Vector2uz getTilePosition() const;

    // 
    void move(float vel_x, float vel_y, Duration dt);

    // 
    void move(const Vector2f& vel, Duration dt);

    // 
    void setPosition(float pos_x, float pos_y);

    // 
    void setPosition(const Vector2f& pos);

    // 
    void setPositionToTile(size_t tile_x, size_t tile_y);

    // 
    void setPositionToTile(const Vector2uz& tile);

    // 
    void updateVertexCollisionStates();

    // 
    bool isMoving() const;

    // 
    void update(Duration dt);

    // 
    void render(RenderWindow& window);
};