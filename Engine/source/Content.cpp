#include "Content.h"

#include "GL\glew.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "tinydir.h"
#include "Color.h"
#include "MathFunctions.h"
#include <FreeType\ft2build.h>
#include FT_FREETYPE_H
#include <algorithm>

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



        //generate spritesheets
        std::vector<Image> images;

        for (unsigned int i = 0; i < texturePaths.size(); ++i)
        {
            images.push_back(Image());
            images.back().data = stbi_load(texturePaths[i].c_str(), &images.back().x, &images.back().y, &images.back().n, 4);

            char name[128];
            sscanf(texturePaths[i].c_str(), "../Content/Textures/%[^.]", name);
            images.back().spriteName = name;
        }

        std::sort(images.begin(), images.end(), [](const Image& left, const Image& right)
        {
            return left.y > right.y;
        });

        ids.push_back(0);
        glGenTextures(1, &ids.back());
        std::vector<se::Rectangle> rectangles;
        std::vector<se::Vector2> availablePositions;
        availablePositions.push_back(se::Vector2(0, 0));
        float width = 0;
        float height = 0;
        for (unsigned int i = 0; i < images.size(); ++i)
        {
            std::vector<se::Vector2>::iterator iter = availablePositions.begin();
            while (true)
            {
                se::Rectangle rect(iter->y, iter->y + images[i].y, iter->x, iter->x + images[i].x);

                bool valid = true;
                for (unsigned int j = 0; j < rectangles.size(); ++j)
                {
                    if (rectangles[j].overlap(rect) || rect.right > 4096.0f || rect.bottom > 4096.0f)
                    {
                        valid = false;
                        break;
                    }
                }

                if (valid)
                {
                    iter = availablePositions.erase(iter);
                    availablePositions.push_back(se::Vector2(rect.right + 1.0f, rect.top));
                    availablePositions.push_back(se::Vector2(rect.left, rect.bottom + 1.0f));
                    rectangles.push_back(rect);
                    images[i].textureRect = rect;
                    images[i].texture = ids.back();
                    if (rect.right > width)
                        width = rect.right;
                    if (rect.bottom > height)
                        height = rect.bottom;
                    break;
                }
                else
                {
                    ++iter;
                    if (iter == availablePositions.end())
                    {
                        sizes.push_back(se::Vector2(width, height));
                        ids.push_back(0);
                        glGenTextures(1, &ids.back());
                        rectangles.clear();
                        availablePositions.clear();
                        availablePositions.push_back(se::Vector2(0, 0));
                        break;
                    }
                }
            }


            std::sort(availablePositions.begin(), availablePositions.end(), [](const se::Vector2& left, const se::Vector2& right)
            {
                return left.x < right.x;
            });
        }

        sizes.push_back(se::Vector2(width, height));

        for (unsigned int i = 0; i < sizes.size(); ++i)
        {
            int texWidth = 2;
            while (texWidth < sizes[i].x)
                texWidth *= 2;

            int texHeight = 2;
            while (texHeight < sizes[i].y)
                texHeight *= 2;

            sizes[i] = se::Vector2(texWidth, texHeight);

            glBindTexture(GL_TEXTURE_2D, ids[i]);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        unsigned int currentId = 0;
        for (unsigned int i = 0; i < images.size(); ++i)
        {
            if (images[i].texture != currentId)
            {
                currentId = images[i].texture;
                glBindTexture(GL_TEXTURE_2D, currentId);
            }
            Color color = *(Color*)images[i].data;
            int bla = glGetError();
            glTexSubImage2D(GL_TEXTURE_2D, 0, (int)images[i].textureRect.left, (int)images[i].textureRect.top, images[i].x, images[i].y, GL_RGBA, GL_UNSIGNED_BYTE, images[i].data);
            bla = glGetError();
            int fuck = 0;
        }
        glBindTexture(GL_TEXTURE_2D, 0);

     //       Rectangle rect((float)yPos, (float)yPos + (float)height, (float)xPos, (float)xPos + (float)width);
     //       Sprite sprite(ids[i], rect, Vector2(0, 0), (float)width, (float)height);
     //       
     //       Content::spriteNames.push_back(name);
     //       Content::sprites.push_back(sprite);


     //       //look for existing hitboxes
     //       std::vector<std::string> boxNames;
     //       tinydir_open_sorted(&dir, "");

     //       for (unsigned int j = 0; j < dir.n_files; ++j)
     //       {
     //           tinydir_file file;
     //           tinydir_readfile_n(&dir, &file, j);

     //           if (!file.is_dir && strcmp(file.name, "Thumbs.db"))
     //           {
     //               char name[128];
     //               sscanf(file.name, "%[^.]", name);
     //               boxNames.push_back(name);
     //           }
     //       }
     //           
     //       tinydir_close(&dir);

     //       //generate hitboxes
     //       for (unsigned int j = startSprite; j < Content::sprites.size(); ++j)
     //       {
     //           if (std::find(boxNames.begin(), boxNames.end(), Content::spriteNames[j]) != boxNames.end())
     //           {
     //               std::vector<se::Vector2> points;
     //       
     //               std::string path = "../Content/Hitboxes/" + Content::spriteNames[j] + ".txt";
     //               FILE* file = fopen(path.c_str(), "r");
     //       
     //               float boxX, boxY;
     //               while (scanf("%f %f", &boxX, &boxY))
     //               {
     //                   points.push_back(se::Vector2(boxX, boxY));
     //               }
     //       
     //               fclose(file);
     //       
     //               Content::hitboxes.push_back(Polygon(points));
     //           }
     //           else
     //           {
					//std::vector<se::Vector2> bla = Content::generateHitbox((se::Color*)image, x, y, Content::sprites[j], 0, 40.0f);
     //               Content::hitboxes.push_back(Polygon(bla));
     //           }
     //       }
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
            FT_Set_Pixel_Sizes(face, 0, 64);
            

            //load glyphs
            std::vector<char> characters;
            std::vector<Glyph> glyphs;

            unsigned int totalWidth = 0;
            unsigned int maxHeight = 0;
            unsigned int index;
            FT_Load_Char(face, 'T', FT_LOAD_RENDER);
            int tHeight = face->glyph->bitmap_top;
            char code = (char)FT_Get_First_Char(face, &index);

            while (index != 0)
            {
                FT_Load_Char(face, code, FT_LOAD_RENDER);

                characters.push_back(code);

                Glyph glyph;
                glyph.character = code;
                glyph.offset = se::Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top + face->ascender / 64 / 2);
                glyph.width = face->glyph->metrics.width >> 6;
                glyph.height = face->glyph->metrics.height >> 6;
                glyph.advance = face->glyph->metrics.horiAdvance >> 6;
                glyphs.push_back(glyph);

                totalWidth += face->glyph->bitmap.width;
                if (face->glyph->bitmap.rows > maxHeight)
                    maxHeight = face->glyph->bitmap.rows;

                code = (char)FT_Get_Next_Char(face, code, &index);
            }

            //get kerning values
            for (unsigned int j = 0; j < characters.size(); ++j)
            {
                for (unsigned int k = 0; k < characters.size(); ++k)
                {
                    unsigned int firstIndex = FT_Get_Char_Index(face, characters[j]);
                    unsigned int secondIndex = FT_Get_Char_Index(face, characters[k]);
                    FT_Vector kerningVector;
                    FT_Get_Kerning(face, firstIndex, secondIndex, FT_KERNING_DEFAULT, &kerningVector);
                    if (kerningVector.x != 0)
                    {
                        glyphs[j].kerningChars.push_back(characters[k]);
                        glyphs[j].kerningAdvances.push_back(kerningVector.x >> 6);
                    }
                }
            }

            //find out fitting texture dimensions
            int lowestPow2Width = 2;
            while (lowestPow2Width < (int)totalWidth)
            {
                lowestPow2Width *= 2;
            }

            int lowestPow2Height = 2;
            while (lowestPow2Height < (int)maxHeight)
            {
                lowestPow2Height *= 2;
            }

            int difference;
            while ((difference = lowestPow2Width - lowestPow2Height) > 0)
            {
                lowestPow2Width /= 2;
                lowestPow2Height *= 2;
            }

            //generate gl texture
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, lowestPow2Width, lowestPow2Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

            //fill texture
            unsigned int startX = 0;
            unsigned int startY = 0;
            for (unsigned int j = 0; j < characters.size(); ++j)
            {
                FT_Load_Char(face, characters[j], FT_LOAD_RENDER);

                std::vector<Color> buffer(face->glyph->bitmap.width * face->glyph->bitmap.rows);

                if (buffer.size() > 0)
                {
                    if (startX + face->glyph->bitmap.width > (unsigned int)lowestPow2Width)
                    {
                        startX = 0;
                        startY += maxHeight + 1;
                    }

                    for (unsigned int y = 0; y < face->glyph->bitmap.rows; ++y)
                    {
                        for (unsigned int x = 0; x < face->glyph->bitmap.width; ++x)
                        {
                            buffer[y * face->glyph->bitmap.width + x].r = 255;
                            buffer[y * face->glyph->bitmap.width + x].g = 255;
                            buffer[y * face->glyph->bitmap.width + x].b = 255;
                            buffer[y * face->glyph->bitmap.width + x].a = face->glyph->bitmap.buffer[y * face->glyph->bitmap.width + x];
                        }
                    }

                    glTexSubImage2D(GL_TEXTURE_2D, 0, startX, startY, face->glyph->bitmap.width, face->glyph->bitmap.rows, GL_RGBA, GL_UNSIGNED_BYTE, &buffer[0]);
                }

                glyphs[j].textureRect = Rectangle((float)startY, (float)startY + (float)face->glyph->bitmap.rows, (float)startX, (float)startX + (float)face->glyph->bitmap.width);

                startX += face->glyph->bitmap.width + 1;
            }

            glBindTexture(GL_TEXTURE_2D, 0);
            ids.push_back(texture);
            sizes.push_back(Vector2(lowestPow2Width, lowestPow2Height));

            //create font
            Font font(texture, 64, maxHeight, characters, glyphs);
            Content::fonts.push_back(font);
            char fontName[128];
            sscanf(fontPaths[i].c_str(), "../Content/Fonts/%s", fontName);
            Content::fontNames.push_back(fontName);

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