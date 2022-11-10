// RPGTest
// Player.cpp
// Created on 2022-10-04 by Justyn Durnford
// Last modified on 2022-11-09 by Justyn Durnford
// Source file for the Player class.

#include "Player.hpp"

#include "GameConstants.hpp"

#include "IntegerTypedefs.hpp"

#include "SFMLFunctions.hpp"

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

void Player::move(float vel_x, float vel_y, Duration dt)
{
    Vector2f new_position(position);
    new_position.x += vel_x * dt.count();
    new_position.y -= vel_y * dt.count();

    hitbox.setVertex(new_position);
    updateVertexCollisionStates();

    Vector2uz tile(room->relativeTile(new_position));

    if (vertexCollisionStates[0] && vertexCollisionStates[1])
        new_position.y = (tile.y + 1) * TILE_LENGTH * SCALE;
    if (vertexCollisionStates[0] && vertexCollisionStates[2])
        new_position.x = (tile.x + 1) * TILE_LENGTH * SCALE;
    if (vertexCollisionStates[1] && vertexCollisionStates[3])
        new_position.x = (tile.x + 0) * TILE_LENGTH * SCALE;
    if (vertexCollisionStates[2] && vertexCollisionStates[3])
        new_position.y = (tile.y + 0) * TILE_LENGTH * SCALE;

    // This should never happen, but just in case, make sure player is in bounds of the room sprite.
    clamp(new_position.x, 0.0f, static_cast<float>(room->collision.colCount()) * TILE_LENGTH * SCALE - PLAYER_SPRITE_WIDTH);
    clamp(new_position.y, 0.0f, static_cast<float>(room->collision.rowCount()) * TILE_LENGTH * SCALE - PLAYER_SPRITE_HEIGHT);

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

void Player::updateVertexCollisionStates()
{
    vertexCollisionStates[0] = room->getTileCollision(hitbox.topLeft());
    vertexCollisionStates[1] = room->getTileCollision(hitbox.topRight());
    vertexCollisionStates[2] = room->getTileCollision(hitbox.bottomLeft());
    vertexCollisionStates[3] = room->getTileCollision(hitbox.bottomRight());
}

bool Player::isMoving() const
{
    return velocity != VECTOR_ZERO;
}

void Player::update(Duration dt)
{
    Ptr<const Direction> direction = inputManager->getCurrentDirection();

    if (direction == nullptr)
    {
        velocity.x = 0.0f;
        velocity.y = 0.0f;
    }
    else
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