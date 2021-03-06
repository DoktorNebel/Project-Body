#include "Rectangle.h"


namespace se
{
    Rectangle::Rectangle(float top, float bottom, float left, float right)
        : top(top)
        , bottom(bottom)
        , left(left)
        , right(right)
    {
    }


    Rectangle::~Rectangle()
    {
    }


    bool Rectangle::overlap(Rectangle rect)
    {
        return this->top < rect.bottom && this->bottom > rect.top && this->left < rect.right && this->right > rect.left;
    }
}