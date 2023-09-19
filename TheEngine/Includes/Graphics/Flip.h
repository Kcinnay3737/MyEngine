#pragma once

namespace NPEngine
{
	struct Flip
	{
		Flip(bool Horizontal = false, bool Vertical = false);

		bool Horizontal = false;
		bool Vertical = false;
	};
}