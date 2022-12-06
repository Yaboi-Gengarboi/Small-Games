// RPGTest
// Player.cpp
// Created on 2022-10-04 by Justyn Durnford
// Last modified on 2022-11-21 by Justyn Durnford
// Source file for the Player class.

#include "Player.hpp"

#include "GameConstants.hpp"

#include "IntegerTypedefs.hpp"

#include "Resources.hpp"

#include "SFMLFunctions.hpp"

const float Player::WALK_SPEED = TILE_LENGTH * SCALE * 4.0f;
const float Player::RUN_SPEED = WALK_SPEED * 1.5f;
const float Player::SPRITE_WIDTH = TILE_LENGTH * SCALE;
const float Player::SPRITE_HEIGHT = TILE_LENGTH * SCALE;

Player::Player() : IDObject(), Entity()
{

}

Player::Player(u16 new_id, const string& new_name, const Vector2f& new_position, const Vector2f& new_velocity,
               Ptr<const Direction> new_direction, Ptr<Room> new_room)
    : IDObject(new_id, new_name), Entity(new_position, new_velocity)
{
    currentDirection = new_direction;
    room = new_room;
    hitbox.setVertex(position);
    hitbox.setDimensions(TILE_LENGTH * SCALE, TILE_LENGTH * SCALE);
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

void Player::updateVertextStates()
{
    vertexStates[0] = room->getTileCollision(hitbox.topLeft());
    vertexStates[1] = room->getTileCollision(hitbox.topRight());
    vertexStates[2] = room->getTileCollision(hitbox.bottomLeft());
    vertexStates[3] = room->getTileCollision(hitbox.bottomRight());
}

void Player::move(float vel_x, float vel_y, Duration dt)
{
    static Vector2f new_position(position);
    static float dx, dy;
    new_position.x += vel_x * dt.count();
    new_position.y -= vel_y * dt.count();

    hitbox.setVertex(new_position);
    updateVertextStates();

    Vector2uz tile(room->relativeTile(new_position));

    /*/////////////////////////////////////////////////////////////////////////////////////////////
    ///                                                                                         ///
    ///    VERTEX STATES:                                                                       ///
    ///                                                                                         ///
    ///   [0]----------[1]   > Each vertex will either be in a SOLID or EMPTY tile.             ///
    ///    |            |    > Some travel methods may effect how the player interacts with     ///
    ///    |            |    some tiles.                                                        ///
    ///    |            |    > Using a combination of SOLID or EMPTY states with the            ///
    ///    |            |    direction the player is facing, we can decide if the player is     ///
    ///   [2]----------[3]   in a wall and how they should be pushed out if so.                 ///
    ///                                                                                         ///
    /////////////////////////////////////////////////////////////////////////////////////////////*/

    if (currentDirection)
    {
        switch (currentDirection->id)
        {
            case Direction::NORTH:

                if (is_tile_solid(vertexStates[0], travelMethod) ||
                    is_tile_solid(vertexStates[1], travelMethod))
                {
                    new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE + 0.01f;
                    velocity = VECTOR_ZERO;
                }

            break;

            case Direction::NORTHEAST:

                if (is_tile_solid(vertexStates[0], travelMethod) &&
                    is_tile_solid(vertexStates[1], travelMethod) &&
                    is_tile_solid(vertexStates[3], travelMethod))
                {
                    new_position.x = (tile.x + 0) * TILE_LENGTH * SCALE - 0.01f;
                    new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE + 0.01f;
                    velocity = VECTOR_ZERO;
                }
                else if (is_tile_solid(vertexStates[0], travelMethod) &&
                         is_tile_solid(vertexStates[1], travelMethod))
                {
                    new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE + 0.01f;
                    velocity.y = 0.0f;
                }
                else if (is_tile_solid(vertexStates[1], travelMethod) &&
                         is_tile_solid(vertexStates[3], travelMethod))
                {
                    new_position.x = (tile.x + 0) * TILE_LENGTH * SCALE - 0.01f;
                    velocity.x = 0.0f;
                }
                else if (is_tile_solid(vertexStates[0], travelMethod))
                {
                    dx = hitbox.maximumX() - ((tile.x + 1) * TILE_LENGTH * SCALE);
                    dy = hitbox.maximumY() - ((tile.y + 1) * TILE_LENGTH * SCALE);

                    if (dx >= dy)
                    {
                        new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE + 0.01f;
                        velocity.x = 0.0f;
                    }
                    else
                    {
                        new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE + 0.01f;
                        velocity.y = 0.0f;
                    }
                }
                else if (is_tile_solid(vertexStates[1], travelMethod))
                {
                    dx = ((tile.x + 1) * TILE_LENGTH * SCALE) - hitbox.minimumX();
                    dy = hitbox.maximumY() - ((tile.y + 1) * TILE_LENGTH * SCALE);

                    if (dx >= dy)
                    {
                        new_position.x = (tile.x + 0) * TILE_LENGTH * SCALE - 0.01f;
                        velocity.x = 0.0f;
                    }
                    else
                    {
                        new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE + 0.01f;
                        velocity.y = 0.0f;
                    }
                }
                else if (is_tile_solid(vertexStates[3], travelMethod))
                {
                    dx = ((tile.x + 1) * TILE_LENGTH * SCALE) - hitbox.minimumX();
                    dy = ((tile.y + 1) * TILE_LENGTH * SCALE) - hitbox.minimumY();

                    if (dx >= dy)
                    {
                        new_position.x = (tile.x + 0) * TILE_LENGTH * SCALE - 0.01f;
                        velocity.x = 0.0f;
                    }
                    else
                    {
                        new_position.y = (tile.y + 0) * TILE_LENGTH * SCALE + 0.01f;
                        velocity.y = 0.0f;
                    }
                }

            break;

            case Direction::EAST:

                if (is_tile_solid(vertexStates[1], travelMethod) ||
                    is_tile_solid(vertexStates[3], travelMethod))
                {
                    new_position.x = (tile.x + 0) * TILE_LENGTH * SCALE - 0.01f;
                    velocity = VECTOR_ZERO;
                }

            break;

            case Direction::SOUTHEAST:

                if (is_tile_solid(vertexStates[1], travelMethod) &&
                    is_tile_solid(vertexStates[2], travelMethod) &&
                    is_tile_solid(vertexStates[3], travelMethod))
                {
                    new_position.x = (tile.x + 0) * TILE_LENGTH * SCALE - 0.01f;
                    new_position.y = (tile.y + 0) * TILE_LENGTH * SCALE - 0.01f;
                    velocity = VECTOR_ZERO;
                }
                else if (is_tile_solid(vertexStates[2], travelMethod) &&
                         is_tile_solid(vertexStates[3], travelMethod))
                {
                    new_position.y = (tile.y + 0) * TILE_LENGTH * SCALE - 0.01f;
                    velocity.y = 0;
                }
                else if (is_tile_solid(vertexStates[1], travelMethod) &&
                         is_tile_solid(vertexStates[3], travelMethod))
                {
                    new_position.x = (tile.x + 0) * TILE_LENGTH * SCALE - 0.01f;
                    velocity.x = 0;
                }
                else if (is_tile_solid(vertexStates[1], travelMethod))
                {
                    dx = ((tile.x + 1) * TILE_LENGTH * SCALE) - hitbox.minimumX();
                    dy = hitbox.maximumY() - ((tile.y + 1) * TILE_LENGTH * SCALE);

                    if (dx >= dy)
                    {
                        new_position.x = (tile.x + 0) * TILE_LENGTH * SCALE - 0.01f;
                        velocity.x = 0;
                    }
                    else
                    {
                        new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE - 0.01f;
                        velocity.y = 0;
                    }
                }
                else if (is_tile_solid(vertexStates[2], travelMethod))
                {
                    dx = hitbox.maximumX() - ((tile.x + 1) * TILE_LENGTH * SCALE);
                    dy = ((tile.y + 1) * TILE_LENGTH * SCALE) - hitbox.minimumY();

                    if (dx >= dy)
                    {
                        new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE + 0.01f;
                        velocity.x = 0;
                    }
                    else
                    {
                        new_position.y = (tile.y + 0) * TILE_LENGTH * SCALE - 0.01f;
                        velocity.y = 0;
                    }
                }
                else if (is_tile_solid(vertexStates[3], travelMethod))
                {
                    dx = ((tile.x + 1) * TILE_LENGTH * SCALE) - hitbox.minimumX();
                    dy = ((tile.y + 1) * TILE_LENGTH * SCALE) - hitbox.minimumY();

                    if (dx >= dy)
                    {
                        new_position.x = (tile.x + 0) * TILE_LENGTH * SCALE - 0.01f;
                        velocity.x = 0;
                    }
                    else
                    {
                        new_position.y = (tile.y + 0) * TILE_LENGTH * SCALE - 0.01f;
                        velocity.y = 0;
                    }
                }

            break;

            case Direction::SOUTH:

                if (is_tile_solid(vertexStates[2], travelMethod) ||
                    is_tile_solid(vertexStates[3], travelMethod))
                {
                    new_position.y = (tile.y + 0) * TILE_LENGTH * SCALE - 0.01f;
                    velocity = VECTOR_ZERO;
                }

            break;

            case Direction::SOUTHWEST:

                if (is_tile_solid(vertexStates[0], travelMethod) &&
                    is_tile_solid(vertexStates[2], travelMethod) &&
                    is_tile_solid(vertexStates[3], travelMethod))
                {
                    new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE + 0.01f;
                    new_position.y = (tile.y + 0) * TILE_LENGTH * SCALE - 0.01f;
                    velocity = VECTOR_ZERO;
                }
                else if (is_tile_solid(vertexStates[0], travelMethod) &&
                         is_tile_solid(vertexStates[2], travelMethod))
                {
                    new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE + 0.01f;
                    velocity.x = 0.0f;
                }
                else if (is_tile_solid(vertexStates[2], travelMethod) &&
                         is_tile_solid(vertexStates[3], travelMethod))
                {
                    new_position.y = (tile.y + 0) * TILE_LENGTH * SCALE - 0.01f;
                    velocity.y = 0.0f;
                }
                else if (is_tile_solid(vertexStates[0], travelMethod))
                {
                    dx = hitbox.maximumX() - ((tile.x + 1) * TILE_LENGTH * SCALE);
                    dy = hitbox.maximumY() - ((tile.y + 1) * TILE_LENGTH * SCALE);

                    if (dx >= dy)
                    {
                        new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE + 0.01f;
                        velocity.x = 0.0f;
                    }
                    else
                    {
                        new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE + 0.01f;
                        velocity.y = 0.0f;
                    }
                }
                else if (is_tile_solid(vertexStates[2], travelMethod))
                {
                    dx = hitbox.maximumX() - ((tile.x + 1) * TILE_LENGTH * SCALE);
                    dy = ((tile.y + 1) * TILE_LENGTH * SCALE) - hitbox.minimumY();

                    if (dx >= dy)
                    {
                        new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE + 0.01f;
                        velocity.x = 0.0f;
                    }
                    else
                    {
                        new_position.y = (tile.y + 0) * TILE_LENGTH * SCALE - 0.01f;
                        velocity.y = 0.0f;
                    }
                }
                else if (is_tile_solid(vertexStates[3], travelMethod))
                {
                    dx = ((tile.x + 1) * TILE_LENGTH * SCALE) - hitbox.minimumX();
                    dy = ((tile.y + 1) * TILE_LENGTH * SCALE) - hitbox.minimumY();

                    if (dx >= dy)
                    {
                        new_position.x = (tile.x + 0) * TILE_LENGTH * SCALE - 0.01f;
                        velocity.x = 0.0f;
                    }
                    else
                    {
                        new_position.y = (tile.y + 0) * TILE_LENGTH * SCALE - 0.01f;
                        velocity.y = 0.0f;
                    }
                }

            break;

            case Direction::WEST:

                if (is_tile_solid(vertexStates[0], travelMethod) ||
                    is_tile_solid(vertexStates[2], travelMethod))
                {
                    new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE + 0.01f;
                    velocity = VECTOR_ZERO;
                }

            break;

            case Direction::NORTHWEST:

                if (is_tile_solid(vertexStates[0], travelMethod) &&
                    is_tile_solid(vertexStates[1], travelMethod) &&
                    is_tile_solid(vertexStates[2], travelMethod))
                {
                    new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE + 0.01f;
                    new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE + 0.01f;
                    velocity = VECTOR_ZERO;
                }
                else if (is_tile_solid(vertexStates[0], travelMethod) &&
                         is_tile_solid(vertexStates[1], travelMethod))
                {
                    new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE + 0.01f;
                    velocity.y = 0.0f;
                }
                else if (is_tile_solid(vertexStates[0], travelMethod) &&
                         is_tile_solid(vertexStates[2], travelMethod))
                {
                    new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE + 0.01f;
                    velocity.x = 0.0f;
                }
                else if (is_tile_solid(vertexStates[0], travelMethod))
                {
                    dx = hitbox.maximumX() - ((tile.x + 1) * TILE_LENGTH * SCALE);
                    dy = hitbox.maximumY() - ((tile.y + 1) * TILE_LENGTH * SCALE);

                    if (dx >= dy)
                    {
                        new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE + 0.01f;
                        velocity.x = 0.0f;
                    }
                    else
                    {
                        new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE + 0.01f;
                        velocity.y = 0.0f;
                    }
                }
                else if (is_tile_solid(vertexStates[1], travelMethod))
                {
                    dx = ((tile.x + 1) * TILE_LENGTH * SCALE) - hitbox.minimumX();
                    dy = hitbox.maximumY() - ((tile.y + 1) * TILE_LENGTH * SCALE);

                    if (dx >= dy)
                    {
                        new_position.x = (tile.x + 0) * TILE_LENGTH * SCALE - 0.01f;
                        velocity.x = 0.0f;
                    }
                    else
                    {
                        new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE + 0.01f;
                        velocity.y = 0.0f;
                    }
                }
                else if (is_tile_solid(vertexStates[2], travelMethod))
                {
                    dx = hitbox.maximumX() - ((tile.x + 1) * TILE_LENGTH * SCALE);
                    dy = ((tile.y + 1) * TILE_LENGTH * SCALE) - hitbox.minimumY();

                    if (dx >= dy)
                    {
                        new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE + 0.01f;
                        velocity.x = 0.0f;
                    }
                    else
                    {
                        new_position.y = (tile.y + 0) * TILE_LENGTH * SCALE - 0.01f;
                        velocity.y = 0.0f;
                    }
                }

            break;

            default: /* Should never happen. */ break;
        }
    }

    // This should never happen, but just in case, make sure player is in bounds of the room sprite.
    clamp(new_position.x, 0.0f, static_cast<float>(room->collision.colCount()) * TILE_LENGTH * SCALE - SPRITE_WIDTH);
    clamp(new_position.y, 0.0f, static_cast<float>(room->collision.rowCount()) * TILE_LENGTH * SCALE - SPRITE_HEIGHT);

    position = new_position;
}

void Player::move(const Vector2f& vel, Duration dt)
{
    move(vel.x, vel.y, dt);
}

void Player::setPosition(float pos_x, float pos_y)
{
    position.set(pos_x, pos_y);
    hitbox.setVertex(position);
}

void Player::setPosition(const Vector2f& pos)
{
    position = pos;
    hitbox.setVertex(position);
}

void Player::setPositionToTile(size_t tile_x, size_t tile_y)
{
    position.x = tile_x * TILE_LENGTH * SCALE;
    position.y = tile_y * TILE_LENGTH * SCALE;
}

void Player::setPositionToTile(const Vector2uz& tile)
{
    position.x = tile.x * TILE_LENGTH * SCALE;
    position.y = tile.y * TILE_LENGTH * SCALE; 
}

bool Player::isMoving() const
{
    return velocity != VECTOR_ZERO;
}

void Player::update(Duration dt, InputManager& input_manager)
{
    Ptr<const Direction> direction = input_manager.getCurrentDirection();

    if (direction == nullptr)
    {
        velocity.x = 0.0f;
        velocity.y = 0.0f;
    }
    else
    {
        currentDirection = direction;

        if (input_manager.getKeyState(Keyboard::LShift) || input_manager.getButtonState(Gamepad::Button::B))
            travelMethod = TravelMethod::RUNNING;
        else
            travelMethod = TravelMethod::WALKING;

        switch (travelMethod)
        {
            case TravelMethod::WALKING:
            velocity = currentDirection->unitVector * WALK_SPEED;
            break;

            case TravelMethod::RUNNING:
            velocity = currentDirection->unitVector * RUN_SPEED;
            break;

            default: /* Should never happen. */ break;
        }

        move(velocity, dt);
        walkingSprites[currentDirection->id].sprite.setPosition(position.x, position.y);
    }
}

void Player::render(RenderWindow& window)
{
    if (currentDirection)
        walkingSprites[currentDirection->id].render(window);
}