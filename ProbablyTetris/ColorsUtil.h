#pragma once

struct Colors
{
	const int R;
	const int G;
	const int B;
};

class PieceColors
{
public:
	static constexpr Colors Cyan{ 0, 255, 255 };
	static constexpr Colors Blue{ 0, 0, 255 };
	static constexpr Colors Red{ 255, 0, 0 };
	static constexpr Colors Purple{ 128, 0, 128 };
	static constexpr Colors Green{ 0, 255, 0 };
	static constexpr Colors Yellow{ 255, 255, 0 };
	static constexpr Colors Orange{ 255, 165, 0 };
	static constexpr Colors White{ 255, 255, 255 };
};