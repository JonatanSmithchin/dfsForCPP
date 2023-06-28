#include "BlockIndexRBTree.h"
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
BlockIndexRBTree::BlockIndexRBTree() :BlockIndex() {
	rson = NULL;
	lson = NULL;
	fa = NULL;
	son = NULL;
	key = -1;
	RB = true;
	TF = false;
}
BlockIndexRBTree::BlockIndexRBTree(BlockIndexRBTree* Fa, int Key, string blockid, int Size, int GenerationTimeStamp) :BlockIndex(blockid, Size, GenerationTimeStamp) {
	rson = NULL;
	lson = NULL;
	fa = Fa;
	son = NULL;
	key = Key;
	RB = true;
	TF = true;
}
void BlockIndexRBTree::left_turn(BlockIndexRBTree** b) {
	BlockIndexRBTree* a = *b;
	BlockIndexRBTree* rs = a->rson;
	a->rson = rs->lson;
	a->rson->fa = a;
	rs->lson = a;
	rs->fa = a->fa;
	if (a->fa->lson == a) a->fa->lson = rs;
	else a->fa->rson = rs;
	a->fa = rs;
}
void BlockIndexRBTree::right_turn(BlockIndexRBTree** b) {
	BlockIndexRBTree* a = *b;
	BlockIndexRBTree* ls = a->lson;
	a->lson = ls->rson;
	a->lson->fa = a;
	ls->rson = a;
	ls->fa = a->fa;
	if (a->fa->lson == a) a->fa->lson = ls;
	else a->fa->rson = ls;
	a->fa = ls;
}
BlockIndexRBTree* BlockIndexRBTree::MakeNULLSon() {
	BlockIndexRBTree *l;
	BlockIndexRBTree r;
	l = &r;
	return l;
}
BlockIndexRBTree* BlockIndexRBTree::brother(BlockIndexRBTree** a) {
	BlockIndexRBTree* t = *a;
	if (t->fa->lson == t) {
		return t->fa->rson;
	}
	else return t->fa->lson;
}
void BlockIndexRBTree::incheck(BlockIndexRBTree** root, BlockIndexRBTree** a) {
	BlockIndexRBTree* temp = *a;
	if (temp == (*root)->lson) {
		temp->RB = black;
		return;
	}
	if (temp->fa->RB == red) {
		if (temp->fa == (*root)->lson) {
			temp->fa->RB = black;
			return;
		}
		if (brother(&(temp->fa))->RB == red) {
			temp->fa->fa->RB = red;
			temp->fa->RB = black;
			brother(&(temp->fa))->RB = black;
			if (temp->fa->fa == (*root)->lson) temp->fa->fa->RB = black;
			else incheck(root, &(temp->fa->fa));
		}
		else if (brother(&(temp->fa))->RB == black) {
			if (temp->fa->fa->lson == temp->fa && temp->fa->lson == temp) {
				temp->fa->RB = black;
				temp->fa->fa->RB = red;
				right_turn(&(temp->fa->fa));
			}
			else if (temp->fa->fa->lson == temp->fa && temp->fa->lson != temp) {
				left_turn(&(temp->fa));
				incheck(root, &(temp->lson));
			}
			else if (temp->fa->fa->lson != temp->fa && temp->fa->lson != temp) {
				temp->fa->RB = black;
				temp->fa->fa->RB = red;
				left_turn(&(temp->fa->fa));
			}
			else if (temp->fa->fa->lson != temp->fa && temp->fa->lson == temp) {
				right_turn(&(temp->fa));
				incheck(root, &(temp->rson));
			}
		}
	}

}
void BlockIndexRBTree::insert(BlockIndexRBTree** root, int x, string blockid, int Size, int GenerationTimeStamp) {
	BlockIndexRBTree* tmp;
	BlockIndexRBTree tm(NULL, x, blockid, Size, GenerationTimeStamp);
	tmp = &tm;
	tmp->RB = red;
	tmp->lson = MakeNULLSon();
	tmp->rson = MakeNULLSon();
	tmp->lson->fa = tmp;
	tmp->rson->fa = tmp;
	if ((*root)->lson == NULL) {
		tmp->RB = black;
		tmp->fa = *root;
		tmp->fa->lson = tmp;
		return;
	}
	BlockIndexRBTree* t = (*root)->lson;
	while (t) {
		if (t->key > tmp->key) {
			if (t->lson->TF == false) {
				free(t->lson);
				t->lson = tmp;
				tmp->fa = t;
				t = NULL;
				incheck(root, &tmp);
			}
			else t = t->lson;
		}
		else {
			if (t->key == tmp->key) return;
			if (t->rson->TF == false) {
				free(t->rson);
				t->rson = tmp;
				tmp->fa = t;
				t = NULL;
				incheck(root, &tmp);
			}
			else t = t->rson;
		}
	}
}
void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
BlockIndexRBTree* BlockIndexRBTree::FindMidOrderSuccessorNode(BlockIndexRBTree** a) {
	BlockIndexRBTree* temp = *a;
	temp = temp->rson;
	while (temp->lson->TF != false) {
		temp = temp->lson;
	}
	return temp;
}
void BlockIndexRBTree::movecheck(BlockIndexRBTree** root, BlockIndexRBTree** a) {
	BlockIndexRBTree* temp = *a;
	if (temp == (*root)->lson) return;
	if (brother(&temp)->RB == red) {
		temp->fa->RB = red;
		brother(&temp)->RB = black;
		if (temp->fa->lson == temp) {
			left_turn(&(temp->fa));
			left_turn(&(temp->fa));
		}
		else {
			right_turn(&(temp->fa));
			right_turn(&(temp->fa));
		}
	}
	else {
		if (brother(&temp)->lson->RB == black && brother(&temp)->rson->RB == black) {
			if (temp->fa->RB == red) {
				temp->fa->RB = black;
				brother(&temp)->RB = red;
			}
			else {
				brother(&temp)->RB = red;
				movecheck(root, &(temp->fa));
			}
		}
		else {
			if (temp->fa->lson == temp && brother(&temp)->rson->RB == black) {
				BlockIndexRBTree* bro = brother(&temp);
				bro->RB = red;
				bro->lson->RB = black;
				right_turn(&bro);
			}
			else if (temp->fa->rson == temp && brother(&temp)->lson->RB == black) {
				BlockIndexRBTree* bro = brother(&temp);
				bro->RB = red;
				bro->rson->RB = black;
				left_turn(&bro);
			}
			if (temp->fa->lson == temp && brother(&temp)->rson->RB == red) {
				brother(&temp)->RB = temp->fa->RB;
				temp->fa->RB = black;
				brother(&temp)->rson->RB = black;
				left_turn(&(temp->fa));
			}
			else if (temp->fa->rson == temp && brother(&temp)->lson->RB == red) {
				brother(&temp)->RB = temp->fa->RB;
				temp->fa->RB = black;
				brother(&temp)->lson->RB = black;
				right_turn(&(temp->fa));
			}
		}
	}
}
void BlockIndexRBTree::remove(BlockIndexRBTree** root, int x) {
	BlockIndexRBTree* temp = (*root)->lson;
	while (temp->key != x) {
		if (temp->key > x) {
			if (temp->lson->TF == false) return;
			else temp = temp->lson;
		}
		else {
			if (temp->rson->TF == false) return;
			else temp = temp->rson;
		}
	}
	BlockIndexRBTree* t;
	if (temp->lson->TF != false && temp->rson->TF != false) {
		t = FindMidOrderSuccessorNode(&temp);
		swap(t->key, temp->key);
		temp = t;
	}
	///
	if (temp->lson->TF != false || temp->rson->TF != false) {
		temp->RB = red;
		if (temp->lson->TF != false) {
			temp->lson->RB = black;
			right_turn(&temp);
		}
		else {
			temp->rson->RB = black;
			left_turn(&temp);
		}
	}
	else if (temp->RB == black) {
		if (temp->fa->RB == red) {
			if (temp->fa->lson == temp) {
				left_turn(&(temp->fa));
			}
			else right_turn(&(temp->fa));
		}
		else {
			if (brother(&temp)->RB == red) {
				brother(&temp)->RB = black;
				temp->fa->RB = red;
				if (temp->fa->lson == temp) {
					left_turn(&(temp->fa));
					left_turn(&(temp->fa));
				}
				else {
					right_turn(&(temp->fa));
					right_turn(&(temp->fa));
				}
			}
			else {
				if (brother(&temp)->lson->TF != false || brother(&temp)->rson->TF != false) {
					BlockIndexRBTree* bro = brother(&temp);
					if (temp->fa->lson == temp && bro->rson->TF == false) {
						bro->lson->RB = black;
						bro->RB = red;
						right_turn(&bro);
					}
					else if (temp->fa->rson == temp && bro->lson->TF == false) {
						bro->rson->RB = black;
						bro->RB = red;
						left_turn(&bro);
					}
					if (temp->fa->lson == temp && brother(&temp)->rson->TF != false) {
						brother(&temp)->rson->RB = black;
						left_turn(&(temp->fa));
					}
					else if (temp->fa->rson == temp && brother(&temp)->lson->TF != false) {
						brother(&temp)->lson->RB = black;
						left_turn(&(temp->fa));
					}
				}
				else {
					brother(&temp)->RB = red;
					movecheck(root, &(temp->fa));
				}
			}
		}
	}
	if (temp->fa->lson == temp) {
		temp->fa->lson = MakeNULLSon();
		temp->fa->lson->fa = temp->fa;
	}
	else {
		temp->fa->rson = MakeNULLSon();
		temp->fa->rson->fa = temp->fa;
	}
	free(temp->lson);
	free(temp->rson);
	free(temp);
}
//need update
int BlockIndexRBTree::inquire(BlockIndexRBTree** root, int x, string name) {
	BlockIndexRBTree* temp = (*root)->lson;
	int cnt = 0;
	while (++cnt) {
		if (temp->key > x) {
			if (temp->lson->TF != false) {
				temp = temp->lson;
				continue;
			}
			else return NULL;
		}
		if (temp->key < x) {
			if (temp->rson->TF != false) {
				temp = temp->rson;
				continue;
			}
			else return NULL;
		}
		if (temp->key == x) {
			printf("depth:%d\n", cnt);
			return temp;/////////////////////////////////////////////
		}
	}
}

