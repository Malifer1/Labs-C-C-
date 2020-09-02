#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


const char* msgs[] = { "0. Сохранить и выйти", "1. Добавить вершину", "2. Добавить ребро", "3. Удалить вершину",
"4. Найти кратчайший путь между двумя вершинами", "5. Вывести граф", "6. Провести таймирование" };
const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
const char* errmsgs[] = { "Вершина добавлена\n\n", "Вершина с введёнными координатами уже существует\n\n",
"Ребро добавлено\n\n", "Ребро между введёнными вершинами уже существует\n\n" };

int getInt(int* rc) {
	int a;
	char c;
	while (1) {
		if (scanf("%d%c", &a, &c)) {
			if (c == '\n') {
				if (a >= 0) {
					*rc = a;
					return 1;
				}
			}
			else {
				if (c == ' ' || c == '\t') {
					while (c == ' ' || c == '\t') {
						scanf("%c", &c);
					}
					if (c == '\n') {
						if (a >= 0) {
							*rc = a;
							return 1;
						}
					}
				}
			}
		}
		printf("Недопустимый ввод, повторите попытку: \n");
		scanf("%*[^\n]");
	}
	return 1;
}

int dialog(const char* msgs[], int N) {
	int rc;
	int i;
	do {
		for (i = 0; i < N; ++i)
			puts(msgs[i]);
		printf("Ваш выбор --> ");
		getInt(&rc);
		if (rc < 0 || rc >= N)
			system("cls");
	} while (rc < 0 || rc >= N);
	return rc;
}

char* getstr() {
	char* ptr = (char*)malloc(1);
	char buf[10];
	int n, len = 0;
	*ptr = '\0';
	do
	{
		n = scanf_s("%9[^\n]", buf, 10);
		if (n < 0)
		{
			free(ptr);
			ptr = NULL;
			continue;
		}
		if (n == 0) {
			scanf_s("%*c");
		}
		else {
			len += strlen(buf);
			ptr = (char*)realloc(ptr, (len + 1) * sizeof(char));
			strncat_s(ptr, len + 1, buf, 10);
		}
	} while (n > 0);
	return ptr;
}

int Init();
int Save();
int D_Load();
int Generate();
int AddVertex();
int AddEdge();
int Delete();
int Path();
int ShowPath();
int Load();

const int Max = 100;

struct Vertex* Find();

typedef struct Vertex {
	int number;
	int x, y;
	struct Adj* adj;
} Vertex;

typedef struct Adj {
	Vertex* v;
	struct Adj* next;
} Adj;

typedef struct Graph {
	int vc;
	Vertex** vertex;
	FILE* fd;
	char* fname;
} Graph;

int D_AddVertex(Graph*),
D_AddEdge(Graph*),
D_Delete(Graph*),
D_Path(Graph*),
D_Show(Graph*),
D_Timing(Graph*);
int (*fptr[])(Graph*) = { NULL, D_AddVertex, D_AddEdge, D_Delete, D_Path, D_Show, D_Timing };


int main() {
	system("chcp 1251");
	system("cls");
	int rc;
	Graph graph = { 0, (Vertex**)malloc(sizeof(Vertex*)), NULL };
	Init(&graph);
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](&graph))
			break;
	Save(&graph);
	return 0;
}

int Init(Graph* graph) {
	int d;
	printf("0: Загрузить граф\n1: Сгенерировать случайный граф\nВаш выбор --> ");
	while (getInt(&d)) {
		if (d == 0) {
			D_Load(graph);
			break;
		}
		if (d == 1) {
			Generate(graph);
			break;
		}
		system("cls");
		printf("0: Загрузить граф\n1: Сгенерировать случайный граф\nВаш выбор --> ");
	}
	return 1;
}

int D_AddVertex(Graph* graph) {
	int x, y;
	printf("Введите координату x: ");
	getInt(&x);
	printf("Введите координату y: ");
	getInt(&y);
	system("cls");
	printf("%s", errmsgs[AddVertex(graph, x, y)]);
	return 1;
}

int AddVertex(Graph* graph, int x, int y) {
	int i;
	for (i = 0; i < graph->vc; i++) {
		if (graph->vertex[i]->x == x &&
			graph->vertex[i]->y == y) {
			return 1;
		}
	}
	graph->vertex = (Vertex**)realloc(graph->vertex, (graph->vc + 1) * sizeof(Vertex*));
	graph->vertex[graph->vc] = (Vertex*)malloc(sizeof(Vertex));
	graph->vertex[graph->vc]->number = graph->vc;
	graph->vertex[graph->vc]->x = x;
	graph->vertex[graph->vc]->y = y;
	graph->vertex[graph->vc]->adj = NULL;
	graph->vc++;
	return 0;
} 

int D_AddEdge(Graph* graph) {
	int x1, y1, x2, y2;
	printf("Введите координату x первой вершины: ");
	getInt(&x1);
	printf("Введите координату y первой вершины: ");
	getInt(&y1);
	printf("Введите координату x второй вершины: ");
	getInt(&x2);
	printf("Введите координату y второй вершины: ");
	getInt(&y2);
	system("cls");
	Vertex* v1 = Find(graph, x1, y1);
	Vertex* v2 = Find(graph, x2, y2);
	if (v1 == NULL || v2 == NULL) {
		printf("Среди введённых вершин есть несуществующие\n\n");
		return 1;
	}
	if (v1 == v2) {
		printf("Нельзя провести ребро между одной и той же вершиной\n\n");
		return 1;
	}
	printf("%s", errmsgs[AddEdge(graph, v1, v2) + 2]);
	return 1;
}

int AddEdge(Graph* graph, Vertex* v1, Vertex* v2) {
	if (v1 == v2)
		return 1;
	Adj* cur;
	if (v1->adj == NULL) {
		v1->adj = (Adj*)malloc(sizeof(Adj));
		v1->adj->v = v2;
		v1->adj->next = NULL;
	}
	else {
		cur = v1->adj;
		while (cur != NULL) {
			if (cur->v == v2)
				return 1;
			if (cur->next == NULL)
				break;
			cur = cur->next;
		}
		cur->next = (Adj*)malloc(sizeof(Adj));
		cur = cur->next;
		cur->v = v2;
		cur->next = NULL;
	}
	if (v2->adj == NULL) {
		v2->adj = (Adj*)malloc(sizeof(Adj));
		v2->adj->v = v1;
		v2->adj->next = NULL;
	}
	else {
		cur = v2->adj;
		while (cur->next != NULL) 
			cur = cur->next;
		cur->next = (Adj*)malloc(sizeof(Adj));
		cur = cur->next;
		cur->v = v1;
		cur->next = NULL;
	}
	return 0;
}

int D_Delete(Graph* graph) {
	int x, y;
	printf("Введите координату x: ");
	getInt(&x);
	printf("Введите координату y: ");
	getInt(&y);
	system("cls");
	Vertex* vertex = Find(graph, x, y);
	if (vertex == NULL) {
		printf("Введённая вершина не найдена\n\n");
		return 1;
	}
	Delete(graph, vertex);
	printf("Вершина удалена\n\n");
	return 1;
}

int Delete(Graph* graph, Vertex* vertex) {
	int i = 0;
	Adj* tmp = vertex->adj;
	Adj* tmp1 = NULL;
	Adj* p;
	while (tmp != NULL) {
		tmp1 = tmp->v->adj;
		if (tmp1->v == vertex) {
			if (tmp1->next != NULL) {
				tmp->v->adj = tmp1->next;
				free(tmp1);
			}
			else {
				tmp->v->adj = NULL;
				free(tmp1);
			}
		}
		else {
			while (tmp1->next->v != vertex)
				tmp1 = tmp1->next;
			if (tmp1->next->next != NULL) {
				p = tmp1->next;
				tmp1->next = p->next;
				free(p);
			}
			else {
				free(tmp1->next);
				tmp1->next = NULL;
			}
		}
		p = tmp;
		tmp = tmp->next;
		free(p);
	}
	i = vertex->number;
	free(vertex);
	graph->vertex[i] = graph->vertex[graph->vc - 1];
	graph->vertex[i]->number = i;
	graph->vc--;
	return 1;
}

int D_Path(Graph* graph) {
	int x1, y1, x2, y2;
	printf("Введите координату x первой вершины: ");
	getInt(&x1);
	printf("Введите координату y первой вершины: ");
	getInt(&y1);
	printf("Введите координату x второй вершины: ");
	getInt(&x2);
	printf("Введите координату y второй вершины: ");
	getInt(&y2);
	system("cls");
	Vertex* v1 = Find(graph, x1, y1);
	Vertex* v2 = Find(graph, x2, y2);
	if (v1 == NULL || v2 == NULL) {
		printf("Среди введённых вершин есть несуществующие\n\n");
		return 1;
	}
	if (v1 == v2) {
		printf("Найден путь длиной 0:\n(%d, %d)->(%d, %d)\n\n", v1->x, v1->y, v2->x, v2->y);
		return 1;
	}
	char* messages[] = { "", "Точки не связаны" };
	printf("%s", messages[Path(graph, v1, v2, 0)]);
	printf("\n\n");
	return 1;
}

int Path(Graph* graph, Vertex* v1, Vertex* v2, int timing) {
	int s = 0;
	int e = 1;
	int i;
	int* color = (int*)malloc(graph->vc * sizeof(int));		//0 - белый, 1 - серый, 2 - чёрный
	int* d = (int*)malloc(graph->vc * sizeof(int));
	Vertex** pred = (Vertex**)malloc(graph->vc * sizeof(Vertex*));
	Vertex** Q = (Vertex**)malloc((graph->vc + 1) * sizeof(Vertex*));
	Adj* tmp;
	for (i = 0; i < graph->vc; i++) {
		color[i] = 0;
		d[i] = 0;
		pred[i] = NULL;
		Q[i + 1] = NULL;
	}
	Q[0] = v1;
	color[v1->number] = 1;
	d[v1->number] = 0;
	while (Q[s] != NULL) {
		tmp = Q[s]->adj;							//Q[i] - проверяемая серая вершина из очереди
		while (tmp != NULL) {					//tmp - вершина из списка смежных к проверяемой
			if (color[tmp->v->number] == 0) {
				color[tmp->v->number] = 1;
				d[tmp->v->number] = d[Q[s]->number] + 1;
				pred[tmp->v->number] = Q[s];
				Q[e] = tmp->v;
				e++;
			}
			tmp = tmp->next;
		}
		color[Q[s]->number] = 2;
		s++;
	}
	free(color);
	if (pred[v2->number] == NULL) {
		return 1;
	}
	if (timing)
		return 0;
	ShowPath(pred, v1, v2, d[v2->number]);
	return 0;
}


int ShowPath(Vertex** pred, Vertex* v1, Vertex* v2, int d) {
	Vertex* cur = pred[v2->number];
	int i;
	int* m;
	m = (int*)malloc(2 * (d + 1) * sizeof(int));
	m[0] = v2->x;
	m[1] = v2->y;
	for (i = 1; i < d + 1; i++) {
		m[i * 2] = cur->x;
		m[i * 2 + 1] = cur->y;
		cur = pred[cur->number];
	}
	printf("Найден путь длиной %d:\n", d);
	printf("(%d, %d)", m[2 * d], m[2 * d + 1]);
	for (i = d - 1; i >= 0; i--) {
		printf("->(%d, %d)", m[2 * i], m[2 * i + 1]);
	}
	return 0;
}

int D_Show(Graph* graph) {
	int i;
	Adj* cur;
	system("cls");
	if (graph->vc == 0) {
		printf("В графе нет ни одной вершины\n\n");
		return 1;
	}
	for (i = 0; i < graph->vc; i++) {
		printf("(%d, %d): ", graph->vertex[i]->x, graph->vertex[i]->y);
		cur = graph->vertex[i]->adj;
		while (cur != NULL) {
			printf("(%d, %d) ", cur->v->x, cur->v->y);
			cur = cur->next;
		}
		printf("\n");
	}
	printf("\n");
	return 1;
}

int Generate(Graph* graph) {
	printf("Введите название файла: ");
	graph->fname = getstr();
	fopen_s(&(graph->fd), graph->fname, "w+b");
	fclose(graph->fd);
	int i = 0;
	int nv, ne, x, y;
	int* xm;
	int* ym;
	xm = (int*)malloc(sizeof(int));
	ym = (int*)malloc(sizeof(int));
	while (printf("Введите желаемое количество вершин: ")) {
		getInt(&nv);
		if (nv > Max * Max) {
			system("cls");
			printf("Такое количество вершин недопустимо в данной конфигурации\n");
			continue;
		}
		if (nv == 0) {
			system("cls");
			free(xm);
			free(ym);
			printf("Был создан пустой граф\n\n");
			return 1;
		}
		break;
	}
	while (printf("Введите желаемое количество рёбер, но не больше чем %d: ", nv * (nv - 1) / 2)) {
		getInt(&ne);
		if (ne > nv * (nv - 1) / 2) {
			system("cls");
			printf("Вы ввели слишком большое число\n");
			continue;
		}
		break;
	}
	srand(time(0));
	while (i < nv) {
		x = (rand() * rand()) % Max;
		y = (rand() * rand()) % Max;
		if (!AddVertex(graph, x, y)) {
			xm = (int*)realloc(xm, (i + 1) * sizeof(int));
			ym = (int*)realloc(ym, (i + 1) * sizeof(int));
			xm[i] = x;
			ym[i] = y;
			i++;
		}
	}
	i = 0;
	while (i < ne) {
		x = (rand() * rand()) % nv;
		y = (rand() * rand()) % nv;
		if (!AddEdge(graph, Find(graph, xm[x], ym[x]), Find(graph, xm[y], ym[y])))
			i++;
	}
	free(xm);
	free(ym);
	system("cls");
	printf("Граф сгенерирован\n\n");
	return 1;
}

Vertex* Find(Graph* graph, int x, int y) {
	int i;
	for (i = 0; i < graph->vc; i++) {
		if (graph->vertex[i]->x == x && graph->vertex[i]->y == y)
			return graph->vertex[i];
	}
	return NULL;
}

int D_Timing(Graph* graph) {
	Vertex* v1;
	Vertex* v2;
	clock_t first, last;
	system("cls");
	int i = 0;
	int nv = 100, ne = 300, x, y;
	int* xm;
	int* ym;
	xm = (int*)malloc(sizeof(int));
	ym = (int*)malloc(sizeof(int));
	int t, k = 0;
	srand(time(0));
	for (t = 0; t < 50; t++) {
		i = t * nv;
		while (i < nv * (t+1)) {
			x = (rand() * rand()) % Max;
			y = (rand() * rand()) % Max;
			if (!AddVertex(graph, x, y)) {
				xm = (int*)realloc(xm, (i + 1) * sizeof(int));
				ym = (int*)realloc(ym, (i + 1) * sizeof(int));
				xm[i] = x;
				ym[i] = y;
				i++;
			}
		}
		i = 0;
		while (i < ne) {
			x = (rand() * rand()) % (nv * (t + 1));
			y = (rand() * rand()) % (nv * (t + 1));
			if (!AddEdge(graph, Find(graph, xm[x], ym[x]), Find(graph, xm[y], ym[y])))
				i++;
		}
		i = 0;
		k = 0;
		first = clock();
		while (i < ne) {
			x = (rand() * rand()) % (nv * (t + 1));
			y = (rand() * rand()) % (nv * (t + 1));
			v1 = Find(graph, xm[x], ym[x]);
			v2 = Find(graph, xm[y], ym[y]);
			if (v1 == NULL || v2 == NULL)
				continue;
			if (!Path(graph, v1, v2, 1)){
				k++;
			}
			i++;
		}
		last = clock();
		printf("Тест #%d: %d вершин, %d рёбер, найдено %d/%d путей, время: %d\n", t + 1, nv * (t + 1), ne * (t + 1), k, ne*(t+1), last - first);
		printf("%d\n", last - first);
	}
	printf("\n\n");
	free(xm);
	free(ym);
	return 1;
}

int D_Load(Graph* graph) {
	do {
		printf("Введите имя файла: ");
		graph->fname = getstr();
		if (graph->fname == NULL)
			return 0;
	} while (Load(graph, graph->fname) == 0);
	system("cls");
	printf("Граф загружен\n\n");
	return 1;
}

int Load(Graph* graph, char* fname) {
	int x = 0, y = 0;
	Vertex* v1;
	Vertex* v2;
	fopen_s(&(graph->fd), fname, "r+b");
	if (graph->fd == NULL) {
		system("cls");
		printf("Файла с указанным именем не существует\n\n");
		return 0;
	}
	fread(&x, sizeof(int), 1, graph->fd);
	fread(&y, sizeof(int), 1, graph->fd);
	while (x != -1 && y != -1) {
		AddVertex(graph, x, y);
		fread(&x, sizeof(int), 1, graph->fd);
		fread(&y, sizeof(int), 1, graph->fd);
	}
	fread(&x, sizeof(int), 1, graph->fd);
	fread(&y, sizeof(int), 1, graph->fd);
	while (x != -1 && y != -1) {
		v1 = Find(graph, x, y);
		fread(&x, sizeof(int), 1, graph->fd);
		fread(&y, sizeof(int), 1, graph->fd);
		v2 = Find(graph, x, y);
		AddEdge(graph, v1, v2);
		fread(&x, sizeof(int), 1, graph->fd);
		fread(&y, sizeof(int), 1, graph->fd);
	}
	fclose(graph->fd);
	return 1;
}

int Save(Graph* graph) {
	Adj* tmp;
	int i;
	int vc = graph->vc;
	int u = -1;
	fopen_s(&(graph->fd), graph->fname, "w+b");
	fseek(graph->fd, 0, SEEK_SET);
	for (i = 0; i < graph->vc; i++) {
		fwrite(&graph->vertex[i]->x, sizeof(int), 1, graph->fd);
		fwrite(&graph->vertex[i]->y, sizeof(int), 1, graph->fd);
	}
	fwrite(&u, sizeof(int), 1, graph->fd);
	fwrite(&u, sizeof(int), 1, graph->fd);
	for (i = 0; i < vc; i++) {
		tmp = graph->vertex[0]->adj;
		while (tmp != NULL) {
			fwrite(&graph->vertex[0]->x, sizeof(int), 1, graph->fd);
			fwrite(&graph->vertex[0]->y, sizeof(int), 1, graph->fd);
			fwrite(&tmp->v->x, sizeof(int), 1, graph->fd);
			fwrite(&tmp->v->y, sizeof(int), 1, graph->fd);
			tmp = tmp->next;
		}
		Delete(graph, graph->vertex[0]);
	}
	fwrite(&u, sizeof(int), 1, graph->fd);
	fwrite(&u, sizeof(int), 1, graph->fd);
	fclose(graph->fd);
	return 0;
}