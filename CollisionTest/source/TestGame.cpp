#include "TestGame.h"

#include "Content.h"
#include "MathFunctions.h"

namespace test
{
    TestGame::TestGame()
    {

    }


    TestGame::~TestGame()
    {

    }


    void TestGame::initialize()
    {
        sprite = se::Content::getSprite("KillaBug1");
        se::Polygon poly = se::Content::getHitbox("KillaBug1");

        se::Vector2 lastPoint = poly.points[0];
        for (int i = 1; i < poly.points.size(); ++i)
        {
            se::Vector2 pos = lastPoint + (poly.points[i] - lastPoint) / 2;
            se::Vector2 scale = se::Vector2(se::Math::Distance(poly.points[i], lastPoint), 1.0f);
            float rotation = atan2(poly.points[i].y - lastPoint.y, poly.points[i].x - lastPoint.x);

            se::Sprite line = se::Content::getSprite("Pixel");
            line.setPosition(pos);
            line.setScale(scale);
            line.setRotation(rotation);
            this->lines.push_back(line);

            lastPoint = poly.points[i];
        }
    }


    void TestGame::update(float elapsedTime)
    {

    }


    void TestGame::draw()
    {
        se::Engine::draw(this->sprite);
        for (int i = 0; i < this->lines.size(); ++i)
        {
            se::Engine::draw(this->lines[i]);
        }
    }


    void TestGame::close()
    {

    }
}