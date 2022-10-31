// SmallRPG
// Player.cpp
// Created on 2022-07-24 by Justyn Durnford
// Last modified on 2022-08-03 by Justyn Durnford
// Source file for the Player class.

#include "Player.hpp"

#include "GameConstants.hpp"

#include "IntegerTypedefs.hpp"
using jlib::u8;
using jlib::i32;

#include "SFMLFunctions.hpp"

#include <filesystem>
using std::filesystem::path;
using std::filesystem::exists;

#include <iostream>
using std::wcout;
using std::wcerr;

// File contents:
// NAME 
// DIR POS_X POS_Y
Player::Player(const path& folder)
{
    path datafile(folder / L"data.txt");

    if (!exists(datafile))
    {
        wcerr << L"ERROR: Could not locate file: " << datafile << L'\n';
        exit(1);
    }
    else
    {
        FileManager fileman(datafile);

        try
        {
            name = fileman.readLine();

            
            i32 dir_id = fileman.get<i32>();
            position.x = fileman.get<i32>();
            position.y = fileman.get<i32>();

            spritePosition = position * TILE_LENGTH;

            switch (dir_id)
            {
                case Direction::UP:
                    direction = &jlib::UP;
                break;

                case Direction::RIGHT:
                    direction = &jlib::RIGHT;
                break;

                case Direction::DOWN:
                    direction = &jlib::DOWN;
                break;

                case Direction::LEFT:
                    direction = &jlib::LEFT;
                break;

                default:
                    direction = nullptr; // Should never happen.
                break;
            }


        }
        catch (...)
        {
            wcerr << L"ERROR: Could not read from file: " << datafile << L'\n';
            wcerr << L"The file may be corrupted.\n";
            exit(1);
        }

        path texturefile(folder / L"texture.png");

        if (!exists(texturefile))
        {
            wcerr << L"ERROR: Could not locate file: " << texturefile << L'\n';
            exit(1);
        }
        else
        {
            create_texture(texture, texturefile);

            for (size_t i = 0; i < walkingSprites.size(); ++i)
            {
                walkingSprites[i] = AnimatedSprite(texture, Vector2i(0 + (164 * i), 0), 1, 4, 4, 16, 16, 4);
                walkingSprites[i].sprite.setScale(3.0f, 3.0f);
            }
        }
    }
}

void Player::update(Duration dt, Ptr<InputManager> inputManager, Ptr<Room> room)
{
    spritePosition.x = position.x * TILE_LENGTH * SCALE - 16.0f;
    spritePosition.y = position.y * TILE_LENGTH * SCALE - 48.0f;

    if (inputManager->getKeyState(Keyboard::W))
        direction = &jlib::UP;
    else if (inputManager->getKeyState(Keyboard::D))
        direction = &jlib::RIGHT;
    else if (inputManager->getKeyState(Keyboard::S))
        direction = &jlib::DOWN;
    else if (inputManager->getKeyState(Keyboard::A))
        direction = &jlib::LEFT;


    walkingSprites[direction->id].sprite.setPosition(spritePosition.x, spritePosition.y);
}

void Player::render(Ptr<RenderWindow> window)
{
    walkingSprites[direction->id].render(window);
}