#include <iostream>
#include <vector>
#include "SudokuBoard.h"

using namespace std;

std::vector<std::vector<short>> solve_sudoku(SudokuBoard board) {
	BoardCords cords(-1, -1);

	// Find miniimal possible values in board
	for (size_t column = 0; column < 9; column++) {
		for (size_t row = 0; row < 9; row++) {
			auto tmp_values = board.GetValues(BoardCords(column, row));
			if (tmp_values.size() == 0) { return std::vector<std::vector<short>>(); }
			else if (tmp_values.size() > 1 && (cords.column < 0 || cords.row < 0)) { cords = BoardCords(column, row); }
			else if (tmp_values.size() > 1 && tmp_values.size() < board.GetValues(cords).size()) { cords = BoardCords(column, row); }
		}
	}

	// Return result board
	if (cords.column < 0 || cords.row < 0 && board.IsSolved()) {
		return board.ConvertToTable();
	}

	// Check possible subtables
	std::vector<short> possible_values(board.GetValues(cords));
	for (size_t i = 0; i < possible_values.size(); i++) {
		board.SetValue(cords, possible_values[i]);
		auto tmp_result = solve_sudoku(SudokuBoard(board.ConvertToTable()));
		if (tmp_result.size() == 9 && SudokuBoard(tmp_result).IsSolved()) {
			return tmp_result;
		}
	}
}

int main() {
	std::vector<std::vector<short>> sudoku_table
	{
		std::vector<short>{0,7,0,0,3,0,0,5,0},
		std::vector<short>{0,0,0,0,0,0,7,0,0},
		std::vector<short>{0,3,0,0,0,4,0,0,1},
		std::vector<short>{0,4,0,0,0,1,9,0,2},
		std::vector<short>{0,0,6,0,4,0,0,0,5},
		std::vector<short>{8,0,0,0,5,6,0,0,0},
		std::vector<short>{0,1,0,0,0,0,0,0,6},
		std::vector<short>{0,0,0,0,0,5,0,0,4},
		std::vector<short>{2,0,0,0,8,0,0,0,0}
	};

	SudokuBoard board(sudoku_table);
	auto solved_sudoku = solve_sudoku(board);
	for (size_t column = 0; column < 9; column++) {
		for (size_t row = 0; row < 9; row++) {
			std::cout << solved_sudoku[column][row] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}