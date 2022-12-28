/*111610054 岡　颯人*/                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         #include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define OX 8
#define VOID 0
#define BLACK 1
#define WHITE 2
#define NEXT 3

typedef struct {
	int t;
	int x1, y1;
	int x2, y2;
	int get;
	int w;
}ITTE;

char Board[OX][OX] = {
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,2,1,0,0,0},
{0,0,0,1,2,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0}
};

char point[OX][OX] = {
	{ 30,-12,0,-1,-1,0,-12,30 },
	{ -12,-15,-3,-3,-3,-3,-15,-12 },
	{ 0,-3,0,-1,-1,0,-3,0 },
	{ -1,-3,-1,-1,-1,-1,-3,-1 },
	{ -1,-3,-1,-1,-1,-1,-3,-1 },
	{ 0,-3,0,-1,-1,0,-3,0 },
	{ -12,-15,-3,-3,-3,-3,-15,-12 },
	{ 30,-12,0,-1,-1,0,-12,30 } };

void ShowAll(void);
void prtResult(void);
int NextTurn(int t, int x, int y, int n, ITTE te[]);
int NextTurnAll(int t, ITTE te[]);
void TurnOver(int t, int x, int y);
void clearNextMark(void);
void computer(int n, ITTE te[], int* x, int* y);

int main(void)
{
	int t, x, y, n;
	char* color[] = { "","●","〇" };
	ITTE te[OX * OX];
	srand(time(NULL));

	t = BLACK;
	n = NextTurnAll(t, te);
	ShowAll();

	for (;;) {
		if (t == BLACK) {
			printf("\n%sの手[行列](ex.34):", color[t]);
			scanf("%1d%1d", &y, &x);
			if (Board[y][x] != NEXT) {
				printf("そこには置けません！\n");
				continue;
			}
		}
		else {
			computer(n, te, &x, &y);
			printf("\n%sは:(%1d%1d)に打ちます。\n", color[t], y, x);
		}
		clearNextMark();
		TurnOver(t, x, y);
		t = t % 2 + 1;
		n = NextTurnAll(t, te);
		if (n == 0) {
			printf("%sはパスです。\n", color[t]);
			t = t % 2 + 1;
			n = NextTurnAll(t, te);
			if (n == 0) {
				prtResult();
				return 0;
			}
		}
		ShowAll();
	}
}
void ShowAll(void)
{
	int x, y;
	char* d[4] = { "・","●","〇","※" };

	printf("\n  ０１２３４５６７\n");
	for (y = 0;y < OX;y++) {
		printf("%2d", y);
		for (x = 0;x < OX;x++) {
			printf("%s", d[Board[y][x]]);
			
		}
		printf("\n");
	}
}
int NextTurnAll(int t, ITTE te[])
{
	int x, y;
	int n = 0;

	for (y = 0;y < OX;y++)
	for (x = 0;x < OX;x++) {
		if (Board[y][x] == t) {
			n = NextTurn(t, x, y, n, te);
		}

	}
	return n;
}
int NextTurn(int t, int x, int y, int n, ITTE te[])
{
	int dx, dy, s, x2, y2;
	int out = 0;
	int get;

	te[n].t = t;
	te[n].x1 = x;
	te[n].y1 = y;

	if (t == BLACK)s = WHITE;
	else s = BLACK;

	for (dy = -1;dy <= 1;dy++) {
		for (dx = -1;dx <= 1;dx++) {
			if (dy == 0 && dx == 0) continue;
			get = 0;
			x2 = x + dx;
			y2 = y + dy;
			get++;
			if (x2 < 0 || OX <= x2 || y2 < 0 || OX <= y2)continue;
			if (Board[y2][x2] != s)continue;
			do {
				x2 += dx;
				y2 += dy;
				get++;
				if (x2 < 0 || OX <= x2 || y2 < 0 || OX <= y2) {
					out = -1;
					break;
				}
			} while (Board[y2][x2] == s);
			if (out < 0) {
				out = 0;
				continue;
			}
			if ((Board[y2][x2] == VOID) || (Board[y2][x2] == NEXT)) {
				te[n].x2 = x2;
				te[n].y2 = y2;
				te[n].get = get;
				n++;
				Board[y2][x2] = NEXT;
			}
		}
	}
	return n;
}
void TurnOver(int t, int x, int y)
{
	int n, dx, dy, s, x2, y2;
	int canx[8], cany[8];

	if (t == BLACK)s = WHITE;
	else if (t == WHITE)s = BLACK;
	else printf("TurnOver:error!\n");

	Board[y][x] = t;

	for (dy = -1;dy <= 1;dy++) {
		for (dx = -1;dx <= 1;dx++) {
			if (dy == 0 && dx == 0) continue;
			n = 0;
			x2 = x + dx;
			y2 = y + dy;
			if (x2 < 0 || OX <= x2 || y2 < 0 || OX <= y2)continue;
			if (Board[y2][x2] != s)continue;
			canx[n] = x2;
			cany[n] = y2;
			n++;
			for (;;) {
				x2 += dx;
				y2 += dy;
				if (x2 < 0 || OX <= x2 || y2 < 0 || OX <= y2) {
					break;
				}
				else if (Board[y2][x2] == s) {
					canx[n] = x2;
					cany[n] = y2;
					n++;
				}
				else if (Board[y2][x2] == t) {
					for (n--;n >= 0;n--)Board[cany[n]][canx[n]] = t;
					break;
				}
				else {
					break;
				}
			}
		}
	}
}
void clearNextMark(void)
{
	int x, y;
	for (y = 0;y < OX;y++)
		for (x = 0;x < OX;x++)
			if (Board[y][x] == NEXT)Board[y][x] = VOID;

}
void prtResult(void)
{
	int x, y, white = 0, black = 0;
	printf("ゲーム終了です。\n");
	ShowAll();
	for(y=0;y<OX;y++)
		for (x = 0;x < OX;x++) {
			if (Board[y][x] == WHITE)white++;
			if (Board[y][x] == BLACK)black++;
		}
	printf("\n●%d個,〇%d個\n",black,white);
	if (black > white) {
		printf("●の勝ちです。\n");
	}
	else if (white > black) {
		printf("〇の勝ちです。\n");
	}
	else {
		printf("引き分け。\n");
	}
}
void computer(int n, ITTE te[], int* x, int* y)
{
	int com, i, j = 0, tmp[64] = { 0 }, a = 0;
	/*com = rand() % n;*/

	for (i = 0; i < n; i++) {
		if (te[com].get < te[i].get) {
			com = i;
		}
	}

	for (i = 0; i < n; i++) {
		if (te[com].get = te[i].get) {
			tmp[j] = i;
			j++;
		}
	}
	for (i = 0; i < j; i++) {
		if (point[te[tmp[a]].x2][te[tmp[a]].y2] < point[te[tmp[i]].x2][te[tmp[i]].y2]) {
			a = i;
			com = tmp[a];
		}
	}
	*x = te[com].x2;
	*y = te[com].y2;
}




