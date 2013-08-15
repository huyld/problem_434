#pragma once
#include "bigNum.h"
#include <iostream>

using namespace std;
//___________________________________________________
// CELL
//___________________________________________________

class cell {
public:
	bool dia;
	bool checking;
	bool fixed;

	cell();
	~cell();
	cell *n;
	cell *ne;
	cell *e;
	cell *se;
	cell *s;
	cell *sw;
	cell *w;
	cell *nw;
};




//___________________________________________________
// GRID
//___________________________________________________

// [0]_1_2_3_---_w
// [1]_1_2_3_---_w
//  |
// [h]_1_2_3_---_w

class grid {
	cell **graph;
	int w;
	int h;

public:
	grid();
	grid(const int &height, const int &width);
	~grid();

	bool is_checking(const int &row, const int &column);
	bool is_dia(const int &row, const int &column);
	bool is_fixed(const int &row, const int &column);

	bool set_diagonal(const int &row, const int &column);
	bool unset_diagonal(const int &row, const int &column);
	bool set_checking(const int &row, const int &column);
	bool unset_checking(const int &row, const int &column);
	bool set_fixed(const int &row, const int &column);
	bool unset_fixed(const int &row, const int &column);

	//int check_fixed(const int &row, const int &column);
};