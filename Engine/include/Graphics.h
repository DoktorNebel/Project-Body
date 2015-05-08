#pragma once

#define GLEW_STATIC

#include "GL\glew.h"
#include "Content.h"
#include "Sprite.h"
#include <vector>
#include "Camera.h"

namespace se
{
	struct EngineSettings;


    class Graphics
    {
    private:

        unsigned int vertexBuffer;
        unsigned int indexBuffer;
        unsigned int matricesBuffer;
        unsigned int uvBuffer;
        unsigned int colorBuffer;
        unsigned int vao;
        unsigned int programId;
        std::vector<unsigned int> textureIds;
        std::vector<Vector2> textureSizes;
        std::vector<std::vector<Matrix>> matrices;
        std::vector<std::vector<Vector2>> uvs;
        std::vector <std::vector<se::Vector4>> colors;
		float renderWidth;
		float renderHeight;

    public:

        Graphics();
        Graphics(EngineSettings& settings);
        ~Graphics();

    private:

        void loadShaders();

    public:

        void addSprite(Sprite& sprite);
        void draw(Camera* camera);
    };
}
