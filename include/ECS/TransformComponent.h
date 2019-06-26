#pragma once

#include "Components.h"
#include "../Vector2D.h"


struct TransformComponent : public Component
{
    Vector2D position;
    Vector2D velocity;

    Vector2D prefPosition;
    int height = 32;
    int width = 32;
    int scale = 1;

    int speed = 3;

    TransformComponent()
    {
        position.Zero();
    }
    TransformComponent(int scale) : scale(scale)
    {
        position.Zero();
    }
    TransformComponent(float x, float y)
    {
        position.x = x;
        position.y = y;
    }
    TransformComponent(float x, float y, int width, int height, int scale) : height(height), width(width), scale(scale)
    {
        position.x = x;
        position.y = y;
    }
    TransformComponent(float x, float y, int width, int height, int scale, int speed) : height(height), width(width), scale(scale), speed(speed)
    {
        position.x = x;
        position.y = y;
    }

    void init() override
    {
        velocity.Zero();
    }
    void update() override
    {
        prefPosition = position;
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
    void unUpdate()
    {
        position = prefPosition;
    }
};