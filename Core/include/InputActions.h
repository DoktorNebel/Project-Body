#pragma once

namespace bg
{
	struct InputAction
	{
		enum Type
		{
            Left = 7,
            Right,
            Up,
            Down,
            Shoot,
            StickyShot,
            FasterCheat,
            Pause
		};
	};
}