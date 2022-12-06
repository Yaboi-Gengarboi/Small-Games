// RPGTest
// Player.hpp
// Created on 2022-10-04 by Justyn Durnford
// Last modified on 2022-11-21 by Justyn Durnford
// Header file for the Player class.

#pragma once

#include "Namespace.hpp"

#include "Entity.hpp"
#include "Enums.hpp"
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
    Ptr<Room> room;
    FloatRect hitbox;
    array<Collision, 4> vertexStates;
    TravelMethod travelMethod;

    static const float WALK_SPEED;
    static const float RUN_SPEED;
    static const float SPRITE_WIDTH;
    static const float SPRITE_HEIGHT;

    // 
    Player();

    // 
    Player(u16 new_id, const string& new_name, const Vector2f& new_position, const Vector2f& new_velocity, 
           Ptr<const Direction> new_direction, Ptr<Room> new_room);

    // 
    static void loadFail(const path& filepath, const wstring& message);

    // 
    void loadSpriteData(const path& folder);

    // 
    Vector2uz getTilePosition() const;

    //
    void updateVertextStates();

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
    bool isMoving() const;

    // 
    void update(Duration dt, InputManager& input_manager);

    // 
    void render(RenderWindow& window);
};

extern shared_ptr<Player> player;