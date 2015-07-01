#pragma once

namespace bg
{
	struct InputAction
	{
		enum Type
		{
            Left = 6,
            Right,
            Up,
            Down,
            Shoot,
            StickyShot,
            FasterCheat,
            Medicine1,
            Medicine2,
            Medicine3,
		};
	};
}