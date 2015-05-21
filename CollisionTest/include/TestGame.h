#include "IGame.h"

namespace test
{
    class TestGame : public se::IGame
    {
    private:

        se::Polygon poly;
        se::Polygon poly2;
        std::vector<se::Sprite> lines;
        se::Sprite sprite;
        se::Sprite sprite2;
		se::Camera camera;

    public:

        TestGame();
        ~TestGame();

    public:

        virtual void initialize();
        virtual void update(float elapsedTime);
        virtual void draw();
        virtual void close();
    };
}