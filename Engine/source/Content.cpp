#include "Content.h"

#include "GL\glew.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "tinydir.h"
#include "Color.h"
#include "MathFunctions.h"
#include <FreeType\ft2build.h>
#include FT_FREETYPE_H

namespace se
{
	std::vector<std::string> Content::spriteNames = std::vector<std::string>();
    std::vector<Sprite> Content::sprites = std::vector<Sprite>();
    std::vector<Polygon> Content::hitboxes = std::vector<Polygon>();
    std::vector<Font> Content::fonts = std::vector<Font>();
    std::vector<std::string> Content::fontNames = std::vector<std::string>();


	std::vector<se::Vector2> Content::generateHitbox(se::Color* image, int imageWidth, int imageHeight, se::Sprite& sprite, char alphaTolerance, float angleTolerance)
    {
        std::vector<se::Vector2> hitboxPoints;
		se::Vector2 lastPixel = se::Vector2(-1.0f, -1.0f);
        float angle;
        float tolerance = angleTolerance * 0.0174532925f;
        bool resetAngle = true;
        se::Rectangle texRect = sprite.getTextureRect();

		if (sprite.getTextureRect().left == 390)
			int bla = 5;

        //left to right
        for (int y = (int)texRect.top; y < (int)texRect.bottom; ++y)
        {
            for (int x = (int)texRect.left; x < (int)texRect.right; ++x)
            {
                if (image[y * imageWidth + x].a > alphaTolerance)
                {
                    if (hitboxPoints.size() > 0)
                    {
                        float newAngle = abs(atan2(y - lastPixel.y, x - lastPixel.x));
                        if (resetAngle)
                        {
                            angle = newAngle;
                            resetAngle = false;
                        }

                        if (lastPixel.x != -1.0f && se::Math::Distance(se::Vector2((float)x, (float)y), lastPixel) > 20.0f)
                        {
                            hitboxPoints.push_back(lastPixel);
                            resetAngle = true;
                        }
						if (abs(newAngle - angle) > tolerance)
                        {
                            hitboxPoints.push_back(se::Vector2((float)x, (float)y));
                            resetAngle = true;
                        }
                    }
                    else if (hitboxPoints.size() == 0)
                    {
                        hitboxPoints.push_back(se::Vector2((float)x, (float)y));
                    }

                    lastPixel = se::Vector2((float)x, (float)y);

                    break;
                }
				else if (x == texRect.right - 1 && lastPixel.x != -1.0f)
                {
                    hitboxPoints.push_back(lastPixel);
                }
            }
        }

		if (lastPixel.x != -1.0f)
		{
			hitboxPoints.push_back(lastPixel);
		}
		lastPixel = se::Vector2(-1.0f, -1.0f);

        //bottom to top
        for (int x = (int)hitboxPoints.back().x + 1; x < (int)texRect.right; ++x)
        {
            for (int y = (int)texRect.bottom; y > (int)texRect.top; --y)
            {
				if (image[y * imageWidth + x].a > alphaTolerance)
                {
                    float newAngle = abs(atan2(y - lastPixel.y, x - lastPixel.x));
                    if (resetAngle)
                    {
                        angle = newAngle;
                        resetAngle = false;
                    }

                    if (lastPixel.x != -1.0f && se::Math::Distance(se::Vector2((float)x, (float)y), lastPixel) > 20.0f)
                    {
                        hitboxPoints.push_back(lastPixel);
                        resetAngle = true;
                    }
					if (abs(newAngle - angle) > tolerance)
                    {
                        hitboxPoints.push_back(se::Vector2((float)x, (float)y));
                        resetAngle = true;
                    }

                    lastPixel = se::Vector2((float)x, (float)y);

                    break;
                }
				else if (y == (int)texRect.top + 1 && lastPixel.x != -1.0f)
                {
                    hitboxPoints.push_back(lastPixel);
                }
            }
        }

		if (lastPixel.x != -1.0f)
		{
			hitboxPoints.push_back(lastPixel);
		}
		lastPixel = se::Vector2(-1.0f, -1.0f);

        //right to left
        for (int y = (int)hitboxPoints.back().y - 1; y > (int)texRect.top; --y)
        {
            for (int x = (int)texRect.right; x > (int)texRect.left; --x)
            {
				if (image[y * imageWidth + x].a > alphaTolerance)
                {
                    float newAngle = abs(atan2(y - lastPixel.y, x - lastPixel.x));
                    if (resetAngle)
                    {
                        angle = newAngle;
                        resetAngle = false;
                    }

                    if (lastPixel.x != -1.0f && se::Math::Distance(se::Vector2((float)x, (float)y), lastPixel) > 20.0f)
                    {
                        hitboxPoints.push_back(lastPixel);
                        resetAngle = true;
                    }
					if (abs(newAngle - angle) > tolerance)
                    {
                        hitboxPoints.push_back(se::Vector2((float)x, (float)y));
                        resetAngle = true;
                    }

                    lastPixel = se::Vector2((float)x, (float)y);

                    break;
                }
				else if (x == (int)texRect.left + 1 && lastPixel.x != -1.0f)
                {
                    hitboxPoints.push_back(lastPixel);
                }
            }
        }

		if (lastPixel.x != -1.0f)
		{
			hitboxPoints.push_back(lastPixel);
		}
		lastPixel = se::Vector2(-1.0f, -1.0f);

        //top to bottom
        for (int x = (int)hitboxPoints.back().x - 1; x > (int)hitboxPoints[0].x; --x)
        {
            for (int y = (int)texRect.top; y < (int)texRect.bottom; ++y)
            {
				if (image[y * imageWidth + x].a > alphaTolerance)
                {
                    float newAngle = abs(atan2(y - lastPixel.y, x - lastPixel.x));
                    if (resetAngle)
                    {
                        angle = newAngle;
                        resetAngle = false;
                    }

                    if (lastPixel.x != -1.0f && se::Math::Distance(se::Vector2((float)x, (float)y), lastPixel) > 20.0f)
                    {
                        hitboxPoints.push_back(lastPixel);
                        resetAngle = true;
                    }
                    if (abs(newAngle - angle) > tolerance)
                    {
                        hitboxPoints.push_back(se::Vector2((float)x, (float)y));
                        resetAngle = true;
                    }

                    lastPixel = se::Vector2((float)x, (float)y);

                    break;
                }
				else if (y == (int)texRect.bottom - 1 && lastPixel.x != -1.0f)
                {
                    hitboxPoints.push_back(lastPixel);
                }
            }
		}

		if (lastPixel.x != -1.0f)
		{
			hitboxPoints.push_back(lastPixel);
		}

        unsigned int size = hitboxPoints.size() - 1;
        for (unsigned int i = 0; i < size; ++i)
        {
            if (Math::Distance(hitboxPoints[i], hitboxPoints[i + 1]) < 5.0f)
            {
                Vector2 newPoint = (hitboxPoints[i] + hitboxPoints[i + 1]) / 2.0f;
                hitboxPoints[i] = newPoint;
                hitboxPoints.erase(hitboxPoints.begin() + i + 1);
                --size;
            }
        }

        if (Math::Distance(hitboxPoints[0], hitboxPoints.back()) < 5.0f)
        {
            Vector2 newPoint = (hitboxPoints[0] + hitboxPoints.back()) / 2.0f;
            hitboxPoints[0] = newPoint;
            hitboxPoints.pop_back();
            --size;
        }

        for (unsigned int i = 0; i < hitboxPoints.size(); ++i)
		{
			hitboxPoints[i] -= se::Vector2(texRect.left + sprite.getWidth() / 2.0f, texRect.top + sprite.getHeight() / 2.0f);
			hitboxPoints[i] *= se::Vector2(1.0f, -1.0f);
		}

        return hitboxPoints;
    }


    void Content::loadTextures(std::vector<unsigned int>& ids, std::vector<Vector2>& sizes)
    {
        std::vector<std::string> texturePaths;
        std::vector<std::string> spritemapPaths;

        //get filenames
        tinydir_dir dir;
        tinydir_open_sorted(&dir, "../Content/Textures");

        for (unsigned int i = 0; i < dir.n_files; ++i)
        {
            tinydir_file file;
            tinydir_readfile_n(&dir, &file, i);

            if (!file.is_dir && strcmp(file.name, "Thumbs.db"))
            {
                texturePaths.push_back(file.path);
            }
        }

        tinydir_close(&dir);

        tinydir_open_sorted(&dir, "../Content/Spritemaps");

        for (unsigned int i = 0; i < dir.n_files; ++i)
        {
            tinydir_file file;
            tinydir_readfile_n(&dir, &file, i);

			if (!file.is_dir && strcmp(file.name, "Thumbs.db"))
            {
                spritemapPaths.push_back(file.path);
            }
        }

        tinydir_close(&dir);


        for (unsigned int i = 0; i < texturePaths.size(); ++i)
		{
            //load texture
            int x, y, n;
            unsigned char* image = stbi_load(texturePaths[i].c_str(), &x, &y, &n, 4);

            sizes.push_back(Vector2((float)x, (float)y));
            ids.push_back(0);
            glGenTextures(1, &ids[i]);
            glBindTexture(GL_TEXTURE_2D, ids[i]);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
            glBindTexture(GL_TEXTURE_2D, 0);

            int startSprite = Content::sprites.size();

            FILE* map = fopen(spritemapPaths[i].c_str(), "r");

            //generate sprites in texture
            char name[256];
            int xPos, yPos, width, height;
            while (fscanf(map, "%s = %d %d %d %d", name, &xPos, &yPos, &width, &height) != EOF)
            {
                Rectangle rect((float)yPos, (float)yPos + (float)height, (float)xPos, (float)xPos + (float)width);
                Sprite sprite(ids[i], rect, Vector2(0, 0), (float)width, (float)height);

                Content::spriteNames.push_back(name);
                Content::sprites.push_back(sprite);
            }

            fclose(map);

            //look for existing hitboxes
            std::vector<std::string> boxNames;
            tinydir_open_sorted(&dir, "");

            for (unsigned int j = 0; j < dir.n_files; ++j)
            {
                tinydir_file file;
                tinydir_readfile_n(&dir, &file, j);

                if (!file.is_dir && strcmp(file.name, "Thumbs.db"))
                {
                    char name[128];
                    sscanf(file.name, "%[^.]", name);
                    boxNames.push_back(name);
                }
            }
                
            tinydir_close(&dir);

            //generate hitboxes
            for (unsigned int j = startSprite; j < Content::sprites.size(); ++j)
            {
                if (std::find(boxNames.begin(), boxNames.end(), Content::spriteNames[j]) != boxNames.end())
                {
                    std::vector<se::Vector2> points;

                    std::string path = "../Content/Hitboxes/" + Content::spriteNames[j] + ".txt";
                    FILE* file = fopen(path.c_str(), "r");

                    float boxX, boxY;
                    while (scanf("%f %f", &boxX, &boxY))
                    {
                        points.push_back(se::Vector2(boxX, boxY));
                    }

                    fclose(file);

                    Content::hitboxes.push_back(Polygon(points));
                }
                else
                {
					std::vector<se::Vector2> bla = Content::generateHitbox((se::Color*)image, x, y, Content::sprites[j], 0, 40.0f);
                    Content::hitboxes.push_back(Polygon(bla));
                }
            }

            stbi_image_free(image);
        }
    }


    void Content::loadFonts(std::vector<unsigned int>& ids, std::vector<Vector2>& sizes)
    {
        std::vector<std::string> fontPaths;

        //get filenames
        tinydir_dir dir;
        tinydir_open_sorted(&dir, "../Content/Fonts");

        for (unsigned int i = 0; i < dir.n_files; ++i)
        {
            tinydir_file file;
            tinydir_readfile_n(&dir, &file, i);

            if (!file.is_dir && strcmp(file.name, "Thumbs.db"))
            {
                fontPaths.push_back(file.path);
            }
        }

        tinydir_close(&dir);
        
        FT_Library library;
        FT_Init_FreeType(&library);

        //generate fontmaps
        for (unsigned int i = 0; i < fontPaths.size(); ++i)
        {
            FT_Face face;
            FT_New_Face(library, fontPaths[i].c_str(), 0, &face);
            FT_Set_Pixel_Sizes(face, 0, 32);

            std::vector<FT_Bitmap> bitmaps;

            unsigned int totalWidth = 0;
            unsigned int index;
            char code = (char)FT_Get_First_Char(face, &index);

            while (index != 0)
            {
                FT_Load_Char(face, code, FT_LOAD_RENDER);
                bitmaps.push_back(face->glyph->bitmap);
                totalWidth += face->glyph->bitmap.width;
                //TODO: generate complete bitmap
                code = (char)FT_Get_Next_Char(face, code, &index);
            }

            FT_Done_Face(face);
        }

        FT_Done_FreeType(library);
    }


    Sprite Content::getSprite(std::string name)
    {
		int pos = std::find(Content::spriteNames.begin(), Content::spriteNames.end(), name) - Content::spriteNames.begin();

		return Content::sprites[pos];
    }


    Polygon Content::getHitbox(std::string spriteName)
    {
        int pos = std::find(Content::spriteNames.begin(), Content::spriteNames.end(), spriteName) - Content::spriteNames.begin();

        return Content::hitboxes[pos];
    }


    Font* Content::getFont(std::string name)
    {
        int pos = std::find(Content::fontNames.begin(), Content::fontNames.end(), name) - Content::fontNames.begin();

        return &Content::fonts[pos];
    }
}