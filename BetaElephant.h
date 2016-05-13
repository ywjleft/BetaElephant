#include <vector>
#include "eleeye/position.h"
using namespace std;

void psigma(const char *const szFen, const int N, const int *const moves, double *const ps);
//szFen�Ǿ����Fen����N���ŷ�������move���ŷ������飨����ΪN���ŷ����飩�������ǲ����޸ĵ�����
//p�ǳ���ΪN�ĸ������飬���Ӧ�ŷ������˳�����ÿ���ŷ���psigma

int ppi(const char *const szFen, const int N, const int *const moves);
//�������ƣ�����P�����ŷ����±�

double value(const char *const szFen);
//�������Fen�����������������v

void genMove(PositionStruct *pos, int K, int* mv){
	int i, nTotal, nLegal;
	MoveStruct mvs[MAX_GEN_MOVES];
	nTotal = pos->GenAllMoves(mvs);
	nLegal = 0;
	for (i = 0; i < nTotal; i++) {
		if (pos->MakeMove(mvs[i].wmv)) {
			pos->UndoMakeMove();
			mv[nLegal] = mvs[i].wmv;
			nLegal++;
		}
	}
	K = nLegal;
}

char* pos2fen(PositionStruct *pos){
	char* c;
	pos->ToFen(c);
	return c;
}

class Node{
public:
	int K; //legal move count
	bool fullyExpanded;
	PositionStruct pos;
	int* move;
	double* P; //prior probability
	double* Q; //action value
	unsigned int* N; //visit count
	Node** C; //children

	int findMaxA(); //�ҵ���ȫ��չNode�����ź���
	int findNew(); //�ҵ�δ��ȫ��չNode����һ����չ�ĺ���
	Node* genNode(int x); //������չ��Node����ʼ��
	int playRollout(); //��ppiģ�⵽��󷵻�ʤ��������0Ϊ����1Ϊʤ
};
