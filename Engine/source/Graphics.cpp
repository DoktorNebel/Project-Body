#include "Graphics.h"

#include "MathFunctions.h"
#include "EngineSettings.h"

namespace se
{
    Graphics::Graphics()
        : vao(0)
        , vertexBuffer(0)
        , indexBuffer(0)
        , matricesBuffer(0)
        , uvBuffer(0)
        , renderWidth(0)
        , renderHeight(0)
    {

    }


	Graphics::Graphics(EngineSettings& settings)
        : vao(0)
        , vertexBuffer(0)
        , indexBuffer(0)
        , matricesBuffer(0)
        , uvBuffer(0)
		, renderWidth(settings.resolutionWidth)
		, renderHeight(settings.resolutionHeight)
    {
        glewInit();

        glGenVertexArrays(1, &this->vao);
        glBindVertexArray(this->vao);

        glGenBuffers(1, &this->vertexBuffer);
        glGenBuffers(1, &this->indexBuffer);
        glGenBuffers(1, &this->matricesBuffer);
        glGenBuffers(1, &this->uvBuffer);
        glGenBuffers(1, &this->colorBuffer);
        

        Vector3 vertices[4] =
        {
            Vector3(-0.5f, -0.5f, 0.0f),
            Vector3(0.5f, -0.5f, 0.0f),
            Vector3(0.5f, 0.5f, 0.0f),
            Vector3(-0.5f, 0.5f, 0.0f)
        };

        unsigned char indices[6] =
        {
            0, 1, 2,
            2, 3, 0
        };

        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, this->matricesBuffer);
        for (int i = 1; i < 5; ++i)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, 4, GL_FLOAT, false, sizeof(Matrix), (const void*)(sizeof(float) * (i - 1) * 4));
            glVertexAttribDivisor(i, 1);
        }

        glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
        for (int i = 5; i < 9; ++i)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, 2, GL_FLOAT, false, sizeof(Vector2) * 4, (const void*)(sizeof(float) * (i - 5) * 2));
            glVertexAttribDivisor(i, 1);
        }

        glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
        glEnableVertexAttribArray(9);
        glVertexAttribPointer(9, 4, GL_FLOAT, false, sizeof(Vector4), 0);
        glVertexAttribDivisor(9, 1);

        glBindVertexArray(0);

        glClearColor(0.01f, 0.05f, 0.15f, 0.0f);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.5f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        Content::loadTextures(this->textureIds, this->textureSizes);
        this->matrices.resize(this->textureIds.size());
        this->uvs.resize(this->textureIds.size());
        this->colors.resize(this->textureIds.size());

        this->loadShaders();
    }


    Graphics::~Graphics()
    {
    }


    void Graphics::loadShaders()
    {
        // Create the shaders
        unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        unsigned int pixelShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        printf("Loading shaders\n");

        // Read the Vertex Shader code from the file
        FILE* file;
        fopen_s(&file, "..\\Content\\Shaders\\vertex.glsl", "rb");
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);

        char* vertexShaderCode = (char*)malloc(size + 1);
        fread(vertexShaderCode, size, 1, file);
        fclose(file);

        vertexShaderCode[size] = 0;


        // Read the Pixel Shader code from the file
        fopen_s(&file, "..\\Content\\Shaders\\fragment.glsl", "rb");
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);

        char* pixelShaderCode = (char*)malloc(size + 1);
        fread(pixelShaderCode, size, 1, file);
        fclose(file);

        pixelShaderCode[size] = 0;


        printf("Compiling Shaders\n");
        // Compile Vertex Shader
        glShaderSource(vertexShaderID, 1, &vertexShaderCode, NULL);
        glCompileShader(vertexShaderID);

        // Compile Pixel Shader
        glShaderSource(pixelShaderID, 1, &pixelShaderCode, NULL);
        glCompileShader(pixelShaderID);


        // Link the program
        unsigned int programID = glCreateProgram();
        glAttachShader(programID, vertexShaderID);
        glAttachShader(programID, pixelShaderID);
        glLinkProgram(programID);

        glDeleteShader(vertexShaderID);
        glDeleteShader(pixelShaderID);

        this->programId = programID;
    }


    void Graphics::addSprite(Sprite& sprite)
    {
        int texturePos = std::find(this->textureIds.begin(), this->textureIds.end(), sprite.getTextureId()) - this->textureIds.begin();
        Vector2 textureSize = this->textureSizes[texturePos];
        Rectangle textureRect = sprite.getTextureRect();

        this->matrices[texturePos].push_back(sprite.getMatrix());

        this->uvs[texturePos].push_back(Vector2(textureRect.left / textureSize.x, textureRect.bottom / textureSize.y));
        this->uvs[texturePos].push_back(Vector2(textureRect.right / textureSize.x, textureRect.bottom / textureSize.y));
        this->uvs[texturePos].push_back(Vector2(textureRect.right / textureSize.x, textureRect.top / textureSize.y));
        this->uvs[texturePos].push_back(Vector2(textureRect.left / textureSize.x, textureRect.top / textureSize.y));

        this->colors[texturePos].push_back(sprite.getColor());
    }


    void Graphics::draw(Camera* camera)
    {
        glViewport(0, 0, this->renderWidth, this->renderHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (camera)
        {
            glUseProgram(this->programId);

            unsigned int viewID = glGetUniformLocation(this->programId, "view");
            unsigned int projectionID = glGetUniformLocation(this->programId, "projection");
            int sampler = glGetUniformLocation(this->programId, "defaultSampler");


            Vector3 camPos = Vector3(camera->getPosition().x, camera->getPosition().y, 0.0f);
            Matrix view = Math::RotationMatrixLookAt(camPos, camPos + Vector3(0, 0, -1));
            Matrix projection = Math::OrthographicMatrix(this->renderWidth * camera->getZoom(), this->renderHeight * camera->getZoom(), 0, 1);
            glUniformMatrix4fv(viewID, 1, 0, &view.v00);
			glUniformMatrix4fv(projectionID, 1, 0, &projection.v00);

            glUniform1i(sampler, 0);

            glBindVertexArray(this->vao);

            for (int i = 0; i < this->textureIds.size(); ++i)
            {
                if (this->matrices[i].size() > 0)
                {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, this->textureIds[i]);

                    glBindBuffer(GL_ARRAY_BUFFER, this->matricesBuffer);
                    glBufferData(GL_ARRAY_BUFFER, this->matrices[i].size() * sizeof(Matrix), &this->matrices[i][0], GL_DYNAMIC_DRAW);

                    glBindBuffer(GL_ARRAY_BUFFER, this->uvBuffer);
                    glBufferData(GL_ARRAY_BUFFER, this->uvs[i].size() * sizeof(Vector2), &this->uvs[i][0], GL_DYNAMIC_DRAW);

                    glBindBuffer(GL_ARRAY_BUFFER, this->colorBuffer);
                    glBufferData(GL_ARRAY_BUFFER, this->colors[i].size() * sizeof(Vector4), &this->colors[i][0], GL_DYNAMIC_DRAW);


                    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, 0, this->matrices[i].size());

                    this->matrices[i].clear();
                    this->uvs[i].clear();
                    this->colors[i].clear();
                }
            }

            glBindVertexArray(0);
        }
    }
}