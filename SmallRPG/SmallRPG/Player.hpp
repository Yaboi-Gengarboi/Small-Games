// SmallRPG
// Player.hpp
// Created on 2022-07-24 by Justyn Durnford
// Last modified on 2022-08-03 by Justyn Durnford
// Header file for the Player class.

#pragma once

#include "AnimatedSprite.hpp"
using jlib::AnimatedSprite;

#include "Direction.hpp"
using jlib::Direction;

#include "FileManager.hpp"
using jlib::FileManager;

#include "InputManager.hpp"

#include "Room.hpp"

#include "Time.hpp"
using jlib::Duration;

#include <array>
using std::array;

#include <filesystem>
using std::filesystem::path;
using std::filesystem::exists;

#include <string>
using std::string;

import Ptr;
using jlib::Ptr;

import Vector2;
using jlib::Vector2f;
using jlib::Vector2i;

class Player
{
    public:

    string name;
    Texture texture;
    array<AnimatedSprite, 4> walkingSprites;
    Ptr<const Direction> direction;
    Vector2i position;
    Vector2i velocity;
    Vector2i spritePosition;
    Vector2i spriteVelocity;

    // 
    Player(const path& folder);

    // 
    void update(Duration dt, Ptr<InputManager> inputManager, Ptr<Room> room);

    // 
    void render(Ptr<RenderWindow> window);
};