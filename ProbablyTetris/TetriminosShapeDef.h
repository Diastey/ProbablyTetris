#pragma once
#include "ColorsDef.h"
#include "Vec2Struct.h"
#include <array>

struct Tetrimino
{
	Vec2 pieces[4];
	int pieceMatrixSize;
	Vec2f pivotPoint;
	Colors color;
};

class TetriminoShapes
{
public:
	static constexpr Tetrimino I = { {
		{ -2, 0 }, { -1, 0 }, { 0, 0 }, { 1, 0 }
	},4,{ -0.5, -0.5 },PieceColors::Cyan };

	static constexpr Tetrimino J = { {
		{ -1, 1 }, { -1, 0 }, { 0, 0 }, { 1, 0 }
	},3,{ 0, 0 },PieceColors::Blue };

	static constexpr Tetrimino L = { {
		{ -1, 0 }, { 0, 0 }, { 1, 0 }, { 1, 1 }
	},3,{ 0, 0 },PieceColors::Orange };

	static constexpr Tetrimino O = { {
		{ -1, 0 }, { 0, 0 }, { -1, -1 }, { 0, -1 }
	},2,{ -0.5, -0.5 },PieceColors::Yellow };

	static constexpr Tetrimino S = { {
		{ 0, 1 }, { 1, 1 }, { -1, 0 }, { 0, 0 }
	},3,{ 0, 0 },PieceColors::Green };

	static constexpr Tetrimino T = { {
		{ 0, 1 }, { -1, 0 }, { 0, 0 }, { 1, 0 }
	},3,{ 0, 0 },PieceColors::Purple };

	static constexpr Tetrimino Z = { {
		{ -1, 1 }, { 0, 1 }, { 0, 0 }, { 1, 0 }
	},3,{ 0, 0 },PieceColors::Red };

	static constexpr std::array<Tetrimino, 7> All = {
		I, J, L, O, S, T, Z
	};

	static constexpr Tetrimino Silhouette = { {
		{ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }
	},0,{ 0, 0 },PieceColors::Gray };
};