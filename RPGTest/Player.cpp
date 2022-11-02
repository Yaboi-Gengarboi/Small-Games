// RPGTest
// Player.cpp
// Created on 2022-10-04 by Justyn Durnford
// Last modified on 2022-11-01 by Justyn Durnford
// Source file for the Player class.

#pragma warning( disable : 4244 ) 
#pragma warning( disable : 4267 ) 

#include "Player.hpp"

#include "GameConstants.hpp"

#include "IntegerTypedefs.hpp"
using jlib::u8;
using jlib::i32;

#include "SFMLFunctions.hpp"

#include <algorithm>
using std::max;
using std::min;

#include <cmath>
using std::floorf;
using std::fmodf;
using std::lround;

#include <filesystem>
using std::filesystem::path;
using std::filesystem::exists;

#include <fstream>
using std::ifstream;

#include <iostream>
using std::cout;
using std::wcout;
using std::wcerr;

#include <string>
using std::string;
using std::wstring;
using std::getline;

import Clamp;
using jlib::clamp;
using jlib::clamp_max;
using jlib::clamp_min;

Player::Player() : IDObject(), Entity()
{

}

Player::Player(u16 new_id, const string& new_name, const Vector2f& new_position, const Vector2f& new_velocity,
               Ptr<const Direction> new_direction, Ptr<InputManager> new_inputManager, Ptr<Room> new_room)
    : IDObject(new_id, new_name), Entity(new_position, new_velocity)
{
    currentDirection = new_direction;
    inputManager = new_inputManager;
    room = new_room;
}

void Player::loadFail(const path& filepath, const wstring& message)
{
    wcerr << L"Error encountered while reading from file: " << filepath.wstring() << L'\n';
    wcerr << message << L'\n';
    exit(1);
}

void Player::loadSpriteData(const path& folder)
{
    path texturefile(folder / L"player" / L"texture.png");

    if (!exists(texturefile))
        loadFail(texturefile, L"Could not locate file: " + texturefile.wstring());

    create_texture(texture, texturefile);

    for (size_t i = 0; i < walkingSprites.size(); ++i)
    {
        walkingSprites[i] = AnimatedSprite(texture, Vector2i(0, 16 * i), 8, 4, 4, 16, 16, 4);
        walkingSprites[i].sprite.setPosition(position.x, position.y);
        walkingSprites[i].sprite.setScale(SCALE, SCALE);
    }
}

Vector2uz Player::getTilePosition() const
{
    return Vector2uz(static_cast<size_t>(position.x / SCALE / TILE_LENGTH), static_cast<size_t>(position.y / SCALE / TILE_LENGTH));
}

void Player::move(float vel_x, float vel_y, Duration dt)
{
    Vector2f new_position(position);
    new_position.x += vel_x * dt.count();
    new_position.y -= vel_y * dt.count();

    Vector2uz tile(room->relativeTile(new_position));

    try
    {
         // Should never happen.
        if (currentDirection == nullptr)
            throw;

        switch (currentDirection->id)
        {
            case Direction::NORTH:

            if (room->getTileCollision(new_position.x, new_position.y) != Collision::EMPTY)
                new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE;

            break;

            case Direction::NORTHEAST:

            if (room->getTileCollision(new_position.x, new_position.y) != Collision::EMPTY)
                new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE;

            if (room->getTileCollision(new_position.x + PLAYER_SPRITE_WIDTH, new_position.y) != Collision::EMPTY)
                new_position.x = tile.x * TILE_LENGTH * SCALE;

            break;

            case Direction::EAST:

            if (room->getTileCollision(new_position.x + PLAYER_SPRITE_WIDTH, new_position.y) != Collision::EMPTY)
                new_position.x = tile.x * TILE_LENGTH * SCALE;

            break;

            case Direction::SOUTHEAST:

            if (room->getTileCollision(new_position.x, new_position.y + PLAYER_SPRITE_HEIGHT) != Collision::EMPTY)
                new_position.y = (tile.y) * TILE_LENGTH * SCALE;

            if (room->getTileCollision(new_position.x + PLAYER_SPRITE_WIDTH, new_position.y) != Collision::EMPTY)
                new_position.x = tile.x * TILE_LENGTH * SCALE;

            break;

            case Direction::SOUTH:

            if (room->getTileCollision(new_position.x, new_position.y + PLAYER_SPRITE_HEIGHT) != Collision::EMPTY)
                new_position.y = (tile.y) * TILE_LENGTH * SCALE;

            break;

            case Direction::SOUTHWEST:

            if (room->getTileCollision(new_position.x, new_position.y) != Collision::EMPTY)
                new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE;

            if (room->getTileCollision(new_position.x, new_position.y + PLAYER_SPRITE_HEIGHT) != Collision::EMPTY)
                new_position.y = (tile.y) * TILE_LENGTH * SCALE;

            break;

            case Direction::WEST:
            
            if (room->getTileCollision(new_position.x, new_position.y) != Collision::EMPTY)
                new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE;

            break;

            case Direction::NORTHWEST:

            if (room->getTileCollision(new_position.x, new_position.y) != Collision::EMPTY)
                new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE;

            if (room->getTileCollision(new_position.x, new_position.y) != Collision::EMPTY)
                new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE;

            break;

            default: // Should never happen.
            break;
        }
    }
    catch (...) { /* Don't move player. */ }

    // This should never happen, but just in case, make sure player is in bounds of the room sprite.
    clamp(new_position.x, 0.0f, static_cast<float>(room->collision.colCount()) * TILE_LENGTH * SCALE - PLAYER_SPRITE_WIDTH);
    clamp(new_position.y, 0.0f, static_cast<float>(room->collision.rowCount()) * TILE_LENGTH * SCALE - PLAYER_SPRITE_HEIGHT);

    position = new_position;
}

void Player::move(const Vector2f& vel, Duration dt)
{
    move(vel.x, vel.y, dt);
}

void Player::update(Duration dt)
{
    Ptr<const Direction> direction = inputManager->getCurrentDirection();

    if (direction != nullptr)
    {
        currentDirection = direction;
        velocity = currentDirection->unitVector * PLAYER_WALK_SPEED;
        move(velocity, dt);
        walkingSprites[currentDirection->id].sprite.setPosition(position.x, position.y);
    }
}

void Player::render(RenderWindow& window)
{
    if (currentDirection != nullptr)
        walkingSprites[currentDirection->id].render(window);
}