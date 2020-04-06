#include "SudokuBoard.h"
#include <algorithm>
#include <array>

SudokuBoard::SudokuBoard(std::vector<std::vector<short>> _table)
{	// Initialize board with known values
	for (size_t column = 0; column < 9; column++) {
		for (size_t row = 0; row < 9; row++) {
			if (_table[column][row] != 0) {
				board[column][row].push_back(_table[column][row]);
			}
		}
	}

	// Initialize board with possible values
	for (size_t column = 0; column < 9; column++) {
		for (size_t row = 0; row < 9; row++) {
			if (board[column][row].empty()) {
				std::vector<short> excluded_values;

				// Exclude values from column
				for (size_t tmp_column = 0; tmp_column < 9; tmp_column++) {
					if (board[tmp_column][row].size() == 1) {
						excluded_values.push_back(board[tmp_column][row][0]);
					}
				}
				// Exclude values from row
				for (size_t tmp_row = 0; tmp_row < 9; tmp_row++) {
					if (board[column][tmp_row].size() == 1) {
						excluded_values.push_back(board[column][tmp_row][0]);
					}
				}

				// Exclude values from square
				size_t column_begin = 0, column_end = 0;
				size_t row_begin = 0, row_end = 0;
				if (0 <= column && column < 3) { column_begin = 0; column_end = 3; }
				else if (3 <= column && column < 6) { column_begin = 3; column_end = 6; }
				else if (6 <= column && column < 9) { column_begin = 6; column_end = 9; }

				if (0 <= row && row < 3) { row_begin = 0; row_end = 3; }
				else if (3 <= row && row < 6) { row_begin = 3; row_end = 6; }
				else if (6 <= row && row < 9) { row_begin = 6; row_end = 9; }

				for (size_t tmp_column = column_begin; tmp_column < column_end; tmp_column++) {
					for (size_t tmp_row = row_begin; tmp_row < row_end; tmp_row++) {
						if (board[tmp_column][tmp_row].size() == 1) {
							excluded_values.push_back(board[tmp_column][tmp_row][0]);
						}
					}
				}

				// Set possible values
				std::sort(excluded_values.begin(), excluded_values.end());
				board[column][row].clear();
				for (size_t i = 1; i <= 9; i++) {
					if (std::find(excluded_values.begin(), excluded_values.end(), i) == excluded_values.end()) {
						board[column][row].push_back(i);
					}
				}
			}
		}
	}
}

void SudokuBoard::SetValue(BoardCords cords, short _value)
{
	board[cords.column][cords.row].clear();
	board[cords.column][cords.row].push_back(_value);
}

std::vector<short>& SudokuBoard::GetValues(BoardCords cords)
{
	return board[cords.column][cords.row];
}

std::vector<std::vector<short>> SudokuBoard::ConvertToTable()
{
	std::vector<std::vector<short>> result(9, std::vector<short>());
	for (size_t column = 0; column < 9; column++) {
		result[column] = std::vector<short>(9, 0);
		for (size_t row = 0; row < 9; row++) {
			if (board[column][row].size() == 1) {
				result[column][row] = board[column][row][0];
			}
			else {
				result[column][row] = 0;
			}
		}
	}
	return result;
}

bool SudokuBoard::IsSolved()
{
	int count = 0;
	auto board_array = ConvertToTable();
	for (size_t column = 0; column < 9; column++) {
		for (size_t row = 0; row < 9; row++) {
			count += board_array[column][row];
		}
	}
	return count == 405;
}
