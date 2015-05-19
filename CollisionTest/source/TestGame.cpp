#include "TestGame.h"

#include "Content.h"
#include "MathFunctions.h"
#include "stb_image.h"

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

        this->sprite = se::Content::getSprite("Eck-Links-Oben");
		
        se::Polygon poly = se::Content::getHitbox("Eck-Links-Oben");
		
        se::Vector2 lastPoint = poly.points[0];
        for (int i = 1; i < poly.points.size(); ++i)
        {
            se::Vector2 pos = lastPoint + (poly.points[i] - lastPoint) / 2;
            se::Vector2 scale = se::Vector2(se::Math::Distance(poly.points[i], lastPoint), 2.0f);
			float rotation = atan2(poly.points[i].y - lastPoint.y, poly.points[i].x - lastPoint.x) * 57.2957795f;
		
            se::Sprite line = se::Content::getSprite("Pixel");
            line.setPosition(pos);
            line.setScale(scale);
            line.setRotation(rotation);
			line.setColor(se::Vector4(0.0f, 1.0f, 0.0f, 1.0f));
			this->lines.push_back(line);
		
            lastPoint = poly.points[i];
        }

		//se::Sprite bug = se::Content::getSprite("KillaBug1");
		//int x, y, n;
		//unsigned char* image = stbi_load("../Content/Textures/test.png", &x, &y, &n, 4);
		//se::Color* rgbaImage = (se::Color*)image;
		//
		//for (int i = bug.getTextureRect().top; i < bug.getTextureRect().bottom; ++i)
		//{
		//	for (int j = bug.getTextureRect().left; j < bug.getTextureRect().right; ++j)
		//	{
		//		se::Color color = rgbaImage[i * x + j];
		//		se::Sprite pixel = se::Content::getSprite("Pixel");
		//		pixel.setPosition(se::Vector2(j - bug.getTextureRect().left, i - bug.getTextureRect().top));
		//		pixel.setColor(se::Vector4(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f));
		//		this->lines.push_back(pixel);
		//	}
		//}
		//
		//stbi_image_free(image);
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