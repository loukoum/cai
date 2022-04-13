#pragma once

class Game;

enum class GameResult { WHITE_WINS, BLACK_WINS, WHITE_WINS_TIME, BLACK_WINS_TIME, DRAW, DRAW_NO_MOVES };

#include "game/player.h"
#include "game/board.h"

#include <utility>
#include <vector>

class Game {
private:
	ChessBoard m_board;
	Player* m_white;
	Player* m_black;
	Player* m_current;
	std::vector<std::pair<const Player*, ChessBoard>> m_moves;
	int m_maxMoves;

public:
	Game() = delete;
	Game(const Game& other) = delete;
	Game(const ChessBoard& board, Player* white, Player* black)
		: Game(board, white, black, 0) { }
	Game(const ChessBoard& board, Player* white, Player* black, int maxMoves)
		: m_board(board), m_white(white), m_black(black), m_current(m_white), m_maxMoves(maxMoves) { }

	GameResult start(bool verbose, bool saveMoves);
	inline void printBoard() const { m_board.printBoard(); }
};

