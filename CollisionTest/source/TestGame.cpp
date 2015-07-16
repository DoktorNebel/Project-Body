#include "TestGame.h"

#include "Content.h"
#include "MathFunctions.h"
#include "stb_image.h"
#include "InputActions.h"
#include "Input.h"

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
		se::Engine::setActiveCamera(this->camera);

        se::Input::bindKeyboardKeyAction(InputAction::Left, sf::Keyboard::Left);
        se::Input::bindKeyboardKeyAction(InputAction::Right, sf::Keyboard::Right);
        se::Input::bindKeyboardKeyAction(InputAction::Up, sf::Keyboard::Up);
        se::Input::bindKeyboardKeyAction(InputAction::Down, sf::Keyboard::Down);
        se::Input::bindKeyboardKeyAction(InputAction::RotateLeft, sf::Keyboard::Q);
        se::Input::bindKeyboardKeyAction(InputAction::RotateRight, sf::Keyboard::E);
        se::Input::bindKeyboardKeyAction(InputAction::ScaleUp, sf::Keyboard::W);
        se::Input::bindKeyboardKeyAction(InputAction::ScaleDown, sf::Keyboard::S);
        
        this->sprite = se::Content::getSprite("Eck-Links-Oben");
        this->sprite.scale(se::Vector2(1.5f, 1.5f));
        
        this->poly = se::Content::getHitbox("Eck-Links-Oben");
        
        
        this->sprite2 = se::Content::getSprite("KillaBug1");
        this->sprite2.scale(se::Vector2(1.0f, 1.0f));
		
        this->poly2 = se::Content::getHitbox("KillaBug1");
        
        this->text = se::Text(se::Content::getFont("calibri.ttf"), "Your mother sucks cocks\nin hell!", se::Vector2(0.0f, 0.0f), se::Vector2(1.0f, 1.0f), 0.0f, se::Vector4(1.0f, 1.0f, 1.0f, 1.0f), se::Text::Alignment::Left);

        struct Test
        {
            unsigned int texture;
            se::Rectangle textureRect;
            se::Vector2 position;
            se::Vector2 size;
            float width;
            float height;
            float rotation;
            float depth;
            se::Vector4 color;
        };

        Test test =
        {
            1,
            se::Rectangle(0, 4096, 0, 4096),
            se::Vector2(500, -500),
            se::Vector2(1.5f, 1.5f),
            4096,
            4096,
            0.0f,
            0.0f,
            se::Vector4(1.0f, 1.0f, 1.0f, 1.0f)
        };

        memcpy(&this->textureTest, &test, sizeof(test));
    }


    void TestGame::update(float elapsedTime)
    {
        this->textureTest.move(se::Vector2(se::Input::getActionValue(InputAction::Right) - se::Input::getActionValue(InputAction::Left), se::Input::getActionValue(InputAction::Up) - se::Input::getActionValue(InputAction::Down)) * se::Vector2(200.0f, 200.0f) * elapsedTime);
        this->sprite.rotate((se::Input::getActionValue(InputAction::RotateLeft) - se::Input::getActionValue(InputAction::RotateRight)) * 200.0f * elapsedTime);
        this->sprite.setScale(this->text.getScale() + se::Vector2(2.0f, 2.0f) * (se::Input::getActionValue(InputAction::ScaleUp) - se::Input::getActionValue(InputAction::ScaleDown)) * elapsedTime);
        
        this->poly.setRotation(this->sprite.getRotation());
        this->poly.setScale(this->sprite.getScale());
        this->poly.setPosition(this->sprite.getPosition());
        
        this->lines.clear();
        
        se::Sprite line = se::Content::getSprite("Pixel");
        
        se::Vector2 projectionNormal;
        float projectionScalar;
        if (this->poly.overlap(this->poly2, &projectionNormal, &projectionScalar))
        {
            line.setColor(se::Vector4(1.0f, 1.0f, 1.0f, 1.0f));
            line.setPosition(se::Vector2(-200.0f, -200.0f));
            line.setScale(se::Vector2(projectionScalar, 2.0f));
            line.setRotation(atan2(projectionNormal.y, projectionNormal.x) * 57.2957795f);
            this->lines.push_back(line);
        
            line.setColor(se::Vector4(1.0f, 0.0f, 0.0f, 1.0f));
        }
        else
        {
            line.setColor(se::Vector4(0.0f, 1.0f, 0.0f, 1.0f));
        }
        
        se::Vector2 lastPoint = this->poly.getPoints()[0];
        
        se::Vector2 pos = lastPoint + (this->poly.getPoints().back() - lastPoint) / 2;
        se::Vector2 scale = se::Vector2(se::Math::Distance(this->poly.getPoints().back(), lastPoint), 2.0f);
        float rotation = atan2(this->poly.getPoints().back().y - lastPoint.y, this->poly.getPoints().back().x - lastPoint.x) * 57.2957795f;
        
        line.setPosition(pos);
        line.setScale(scale);
        line.setRotation(rotation);
        
        this->lines.push_back(line);
        
        for (unsigned int i = 1; i < this->poly.getPoints().size(); ++i)
        {
            pos = lastPoint + (this->poly.getPoints()[i] - lastPoint) / 2;
            scale = se::Vector2(se::Math::Distance(this->poly.getPoints()[i], lastPoint), 2.0f);
            rotation = atan2(this->poly.getPoints()[i].y - lastPoint.y, this->poly.getPoints()[i].x - lastPoint.x) * 57.2957795f;
        
            line.setPosition(pos);
            line.setScale(scale);
            line.setRotation(rotation);
            this->lines.push_back(line);
        
            lastPoint = this->poly.getPoints()[i];
        }
        
        
        lastPoint = this->poly2.getPoints()[0];
        
        pos = lastPoint + (this->poly2.getPoints().back() - lastPoint) / 2;
        scale = se::Vector2(se::Math::Distance(this->poly2.getPoints().back(), lastPoint), 2.0f);
        rotation = atan2(this->poly2.getPoints().back().y - lastPoint.y, this->poly2.getPoints().back().x - lastPoint.x) * 57.2957795f;
        
        line.setPosition(pos);
        line.setScale(scale);
        line.setRotation(rotation);
        this->lines.push_back(line);
        
        for (unsigned int i = 1; i < this->poly2.getPoints().size(); ++i)
        {
            pos = lastPoint + (this->poly2.getPoints()[i] - lastPoint) / 2;
            scale = se::Vector2(se::Math::Distance(this->poly2.getPoints()[i], lastPoint), 2.0f);
            rotation = atan2(this->poly2.getPoints()[i].y - lastPoint.y, this->poly2.getPoints()[i].x - lastPoint.x) * 57.2957795f;
        
            line.setPosition(pos);
            line.setScale(scale);
            line.setRotation(rotation);
            this->lines.push_back(line);
        
            lastPoint = this->poly2.getPoints()[i];
        }
        
        //se::Rectangle textRect = this->text.getRect();
        //if (textRect.overlap(this->sprite.getRect()))
        //{
        //    line.setColor(se::Vector4(0.0f, 0.0f, 1.0f, 1.0f));
        //}
        //
        //line.setPosition(se::Vector2(textRect.left + (textRect.right - textRect.left) / 2.0f, textRect.top));
        //line.setScale(se::Vector2((textRect.right - textRect.left), 1.0f));
        //line.setRotation(0.0f);
        //this->lines.push_back(line);
        //
        //line.setPosition(se::Vector2(textRect.right, textRect.top + (textRect.bottom - textRect.top) / 2.0f));
        //line.setScale(se::Vector2((textRect.bottom - textRect.top), 1.0f));
        //line.setRotation(90.0f);
        //this->lines.push_back(line);
        //
        //line.setPosition(se::Vector2(textRect.left + (textRect.right - textRect.left) / 2.0f, textRect.bottom));
        //line.setScale(se::Vector2((textRect.right - textRect.left), 1.0f));
        //line.setRotation(0.0f);
        //this->lines.push_back(line);
        //
        //line.setPosition(se::Vector2(textRect.left, textRect.top + (textRect.bottom - textRect.top) / 2.0f));
        //line.setScale(se::Vector2((textRect.bottom - textRect.top), 1.0f));
        //line.setRotation(90.0f);
        //this->lines.push_back(line);
    }


    void TestGame::draw()
    {
        //se::Engine::draw(this->sprite2);
        //se::Engine::draw(this->sprite);
        //for (unsigned int i = 0; i < this->lines.size(); ++i)
        //{
        //    se::Engine::draw(this->lines[i]);
        //}
        se::Engine::draw(this->textureTest);
        //se::Engine::draw(this->text);
    }


    void TestGame::close()
    {

    }
}