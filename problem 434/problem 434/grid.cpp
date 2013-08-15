#include "grid.h"

//___________________________________________________
// CELL
//___________________________________________________

cell::cell() {
	dia = false;
	checking = false;
	fixed = false;

	n = ne = e = se = s = sw = w = nw =	NULL;
}

cell::~cell() {
	if(n != NULL) {
		delete n;
		n = NULL;
	}

	if(ne != NULL) {
		delete ne;
		ne = NULL;
	}

	if(e != NULL) {
		delete e;
		e = NULL;
	}

	if(se != NULL) {
		delete se;
		se= NULL;
	}

	if(s != NULL) {
		delete s;
		s = NULL;
	}

	if(sw != NULL) {
		delete sw;
		sw = NULL;
	}

	if(w != NULL) {
		delete w;
		w = NULL;
	}

	if(nw != NULL) {
		delete nw;
		nw = NULL;
	}
	
}





//___________________________________________________
// GRID
//___________________________________________________

// [0]_1_2_3_---_w
// [1]_1_2_3_---_w
//  |
// [h]_1_2_3_---_w

grid::grid() {
	graph = NULL;
	w = h = 0;
}

grid::grid(const int &height, const int &width) {
	h = height;
	w = width;

	graph = new cell*[h];
	for(int i=0; i<h; ++i) {
		graph[i] = new cell[w];
	}

	cell *cur = NULL;
	for(int i=0; i<h; ++i) {
		for(int j=0; j<w; ++j) {
			cur = &graph[i][j];
			if(i-1>=0)
				cur->n = &graph[i-1][j];
			if(i-1>=0 && j+1<w)
				cur->ne = &graph[i-1][j+1];
			if(j+1<w)
				cur->e = &graph[i][j+1];
			if(i+1<h && j+1<w)
				cur->se = &graph[i+1][j+1];
			if(i+1<h)
				cur->s = &graph[i+1][j];
			if(i+1<h && j-1>=0)
				cur->sw = &graph[i+1][j-1];
			if(j-1>=0)
				cur->w = &graph[i][j-1];
			if(i-1>=0 && j-1>=0)
				cur->nw = &graph[i-1][j-1];
		}

	}

}

grid::~grid() {
	for(int i=0; i<w; ++i) {
		if(graph[i] != NULL) {
			delete []graph[i];
			graph[i] = NULL;
		}
	}

	if(graph != NULL)
		delete []graph;
	graph = NULL;
}




bool grid::is_checking(const int &row, const int &column) {
	if(row>=1 && row<=h && column>=1 && column<=w && graph[row-1][column-1].checking==true)
		return true;
	return false;
}

bool grid::is_dia(const int &row, const int &column) {
	if(row>=1 && row<=h && column>=1 && column<=w && graph[row-1][column-1].dia==true)
		return true;
	return false;
}

bool grid::is_fixed(const int &row, const int &column) {
	if(row>=1 && row<=h && column>=1 && column<=w && graph[row-1][column-1].fixed==true)
		return true;
	return false;
}


bool grid::set_diagonal(const int &row, const int &column) {
	if(row>=1 && row<=h && column>=1 && column<=w) {
		graph[row-1][column-1].dia = true;
		return true;
	}
	return false;	// row and column out of range
}

bool grid::unset_diagonal(const int &row, const int &column) {
	if(row>=1 && row<=h && column>=1 && column<=w) {
		graph[row-1][column-1].dia = false;
		return false;
	}
	return false;	// row and column out of range
}

bool grid::set_checking(const int &row, const int &column) {
	if(row>=1 && row<=h && column>=1 && column<=w) {
		graph[row-1][column-1].checking = true;
		return false;
	}
	return false;	// row and column out of range
}

bool grid::unset_checking(const int &row, const int &column) {
	if(row>=1 && row<=h && column>=1 && column<=w) {
		graph[row-1][column-1].checking = false;
		return false;
	}
	return false;	// row and column out of range
}

bool grid::set_fixed(const int &row, const int &column) {
	if(row>=1 && row<=h && column>=1 && column<=w) {
		graph[row-1][column-1].fixed = true;
		return false;
	}
	return false;	// row and column out of range
}

bool grid::unset_fixed(const int &row, const int &column) {
	if(row>=1 && row<=h && column>=1 && column<=w) {
		graph[row-1][column-1].fixed = false;
		return false;
	}
	return false;	// row and column out of range
}


//int grid::check_fixed(const int &row, const int &column) {
//	// return -1: row and column out of range
//	// return 0: not fixed
//	// return 1: fixed
//	// return 2: checking
//
//	if(row<1 || row>h || column<1 || column>h)
//		return -1;
//	if(is_fixed(row, column))
//		return 1;
//
//	if(is_checking(row, column))
//		return 2;
//
//	set_checking(row, column);
//		
//	if(graph[row-1][column-1].dia == true) {
//		set_fixed(row, column);
//		unset_checking(row, column);
//		return 1;
//	}
//
//	// in case this cell is not being checked by another proccess, 
//	// or the address is not out of range or not fixed. Check the surrond cell.
//	int count = 0;
//	if(check_fixed(graph[row-1][column-1].)
//}
