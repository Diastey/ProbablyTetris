#pragma once
#include "ColorsUtil.h"

struct Vec2
{
	const int xIndex;
	const int yIndex;
};

struct Tetrimino
{
	Vec2 pieces[4];
	Colors color;
};

class TetriminoShapes
{
public:
	static constexpr Tetrimino I = { {
		{ -1, 0 }, { 0, 0 }, { 1, 0 }, { 2, 0 }
	},PieceColors::Cyan };

	static constexpr Tetrimino J = { {
		{ -1, 0 }, { 0, 0 }, { 1, 0 }, { -1, 1 }
	},PieceColors::Blue };

	static constexpr Tetrimino L = { {
		{ -1, 0 }, { 0, 0 }, { 1, 0 }, { 1, 1 }
	},PieceColors::Orange };

	static constexpr Tetrimino O = { {
		{ 0, 0 }, { 1, 0 }, { 0, 1 }, { 1, 1 }
	},PieceColors::Yellow };

	static constexpr Tetrimino S = { {
		{ 0, 0 }, { 1, 0 }, { -1, 1 }, { 0, 1 }
	},PieceColors::Green };

	static constexpr Tetrimino T = { {
		{ -1, 0 }, { 0, 0 }, { 1, 0 }, { 0, 1 }
	},PieceColors::Purple };

	static constexpr Tetrimino Z = { {
		{ -1, 0 }, { 0, 0 }, { 0, 1 }, { 1, 1 }
	},PieceColors::Red };
};