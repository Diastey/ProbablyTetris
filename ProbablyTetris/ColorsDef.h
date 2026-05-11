#pragma once

struct Colors
{
	int R;
	int G;
	int B;
};

class PieceColors
{
public:
	static constexpr Colors Cyan{ 0, 255, 255 };
	static constexpr Colors Blue{ 64, 64, 255 };
	static constexpr Colors Orange{ 255, 165, 0 };
	static constexpr Colors Yellow{ 255, 255, 0 };
	static constexpr Colors Green{ 0, 255, 0 };
	static constexpr Colors Purple{ 224, 0, 224 };
	static constexpr Colors Red{ 255, 0, 0 };
	static constexpr Colors White{ 255, 255, 255 };
	static constexpr Colors Gray{ 128, 128, 128 };
	static constexpr Colors Dark{ 0, 0, 0 };
};