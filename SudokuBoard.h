#include <vector>
#include "BoardCords.h"

#pragma once
class SudokuBoard
{
private:
	std::vector<short> board[9][9];
public:
	SudokuBoard(std::vector<std::vector<short>> _table);

	void SetValue(BoardCords cords, short _value);
	std::vector<short>& GetValues(BoardCords cords);

	std::vector<std::vector<short>> ConvertToTable();
	bool IsSolved();
};

