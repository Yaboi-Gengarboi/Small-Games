// RPGTest
// Player.hpp
// Created on 2022-10-04 by Justyn Durnford
// Last modified on 2022-10-27 by Justyn Durnford
// Header file for the Player class.

#pragma once

#include "AnimatedSprite.hpp"
using jlib::AnimatedSprite;

#include "Direction.hpp"
using jlib::Direction;

#include "Time.hpp"
using jlib::Duration;

#include "Entity.hpp"

#include "InputManager.hpp"

#include "Room.hpp"

#include <array>
using std::array;

#include <string>
using std::string;
using std::wstring;

import Vector2;
using jlib::Vector2f;
using jlib::Vector2uz;
using jlib::to_string;

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
    void update(Duration dt);

    // 
    void render(RenderWindow& window);
};