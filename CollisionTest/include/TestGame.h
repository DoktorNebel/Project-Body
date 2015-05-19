#include "IGame.h"

namespace test
{
    class TestGame : public se::IGame
    {
    private:

        std::vector<se::Sprite> lines;
        se::Sprite sprite;
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