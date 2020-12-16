#include "Lab1.h"


const char* msgs[] = { "0. �����", "1. �������� �� ������� ������� (� ������ ������������� �������� � ������ ���������, �������� ����������������)", "2. ������� �������� ������� � �������������� �� ������" };

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

const int SZ = 4;

namespace Lab1 {

	// ������� ����� ������ ����� 
	int getInt(int& a) {
		int rc = 0;
		cin >> a;
		if (!cin.good())
			rc = 1;				// ���������� ������ �����
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return rc;
	}


	// ����� ������ ������������
	int dialog(const char* msgs[], int N) {
		const char* errmsgs = "";
		int rc, i, n;
		do {
			puts(errmsgs);
			errmsgs = "������! ��������� ����:!";
			for (i = 0; i < N; ++i)					// ����� ������ �����������
				puts(msgs[i]);
			printf("��������: --> ");
		} while (getInt(rc) < 0 || rc >= N);
		return rc;
	}


	// ������� ����� ���-�� ����� � ��������
	void Input(SparseMatrix& matrix) {
		const char* em = "�������� ����� (����� ������ ���� �����������). ���������� ��� ���:\n--> ";	// ������� ��������� �� ������
		cout << "������� ���-�� �����: --> ";
		while (getInt(matrix.m) || (matrix.m < 1))	// ���������� ������ ����� ��� ����� �����
			cout << em;
		cout << "������� ���-�� ��������: --> ";
		while (getInt(matrix.n) || (matrix.n < 1))	// ���������� ������ ����� ��� ����� �����
			cout << em;
	}


	//������� ���������� ����� ������-������ � �������
	void AddNewRow(SparseMatrix* matrix, int i, int j, int val) {
		SparseMatrixRowList* Rows = matrix->Rowlist;		// ��������� �� ������ �����
		/* 1 ������: ������ ���� */
		if (!matrix->Rowlist) {
			matrix->Rowlist = new SparseMatrixRowList();
			matrix->Rowlist->i = i;
			matrix->Rowlist->next = nullptr;
			matrix->Rowlist->row = nullptr;
			AddToRow(&(matrix->Rowlist->row), j, val);
		}
		else {
			/* ���������� ��������� �� ��� �������, ������� ����� ������ ����� ������*/
			while (Rows && (i > Rows->i))
				Rows = Rows->next;
			/* 2 ������: ����� ������ ��� ����������. ����� ��������� ������� � ������ ������ */
			if (Rows && (i == Rows->i))
				AddToRow(&(Rows->row), j, val);
			else {
				SparseMatrixRowList* NewElem = new SparseMatrixRowList();
				NewElem->i = i;
				NewElem->row = nullptr;
				SparseMatrixRowList* RowsPrev = matrix->Rowlist;
				while ((RowsPrev->next != Rows) && (RowsPrev != Rows))
					RowsPrev = RowsPrev->next;
				/* 3 ������: ������� ����������� � ������ */
				if (RowsPrev == Rows) {
					matrix->Rowlist = NewElem;
					NewElem->next = Rows;
					AddToRow(&(matrix->Rowlist->row), j, val);
				}
				/* 4 ������: ������� ���������� */
				else {
					NewElem->next = Rows;
					RowsPrev->next = NewElem;
					AddToRow(&(NewElem->row), j, val);
				}
			}
		}
	}



	// ������� ���������� ������ �� �������� �������� � ������-������
	void AddToRow(RowOfSparseMatrix** row, int j, int val) {
		/* �������� ������������� ���������� �������� � ������ ��������� */
		RowOfSparseMatrix* tmp = *row;
		while (tmp) {
			if (tmp->j == j) {
				tmp->val = val;
				return;
			}
			tmp = tmp->next;
		}
		tmp = *row;
		/* 1 ������: ������ ���� */
		if (!tmp) {
			(*row) = new RowOfSparseMatrix();
			(*row)->j = j;
			(*row)->val = val;
			(*row)->next = nullptr;
		}
		else {
			/* ���������� ��������� �� ��� �������, ������� ����� ������ ����� ������*/
			while (tmp && (j > tmp->j))
				tmp = tmp->next;
			/* 2 ������: ���� ������� � ������ ��������� ��� ���� */
			if (tmp && (j == tmp->j))
				tmp->val = val;
			else {
				RowOfSparseMatrix* NewElem = new RowOfSparseMatrix();
				NewElem->j = j;
				NewElem->val = val;
				NewElem->next = nullptr;
				RowOfSparseMatrix* tmpPrev = (*row);
				while ((tmpPrev->next != tmp) && (tmpPrev != tmp))
					tmpPrev = tmpPrev->next;
				/* 3 ������: ������� ����������� � ������ */
				if (tmpPrev == tmp) {
					(*row) = NewElem;
					NewElem->next = tmp;
				}
				/* 4 ������: ������� ���������� */
				else {
					NewElem->next = tmp;
					tmpPrev->next = NewElem;
				}
			}
		}
	}



	// ������� ���������� ������ ���������� �������� � �������
	int D_Add(SparseMatrix* matrix) {
		int i, j, val;
		const char* em = "�������� ������ (����� ������ ���� ����������� � �� ��������� �� ������� �������). ���������� ��� ���:\n --> ";
		cout << "������� ������ ������: --> ";
		while ((getInt(i) < 0) || (i >= matrix->m))
			cout << em;
		cout << "������� ������ �������: --> ";
		while ((getInt(j) < 0) || (j >= matrix->n))
			cout << em;
		cout << "������� �������� ��������: --> ";
		while ((getInt(val) < 0) || (!val))
			cout << "������ ����� (����� ������ ���� ����� � �������� �� ����). ���������� ��� ���:\n --> ";
		AddNewRow(matrix, i, j, val);
		return 1;
	}



	// ������� ������ ������� � �������� �������
	int D_Show(SparseMatrix* matrix) {
		SparseMatrixRowList* Row = matrix->Rowlist;
		/* ��� ������ ������ */
		for (int i = 0; i < matrix->m; ++i) {
			if (Row && Row->i == i) {
				RowOfSparseMatrix* now = Row->row;
				for (int j = 0; j < matrix->n; ++j) {
					if (now && now->j == j) {
						cout << setw(4) << right << now->val;
						now = now->next;
					}
					else
						cout << "   0";
				}
				cout << endl;
				Row = Row->next;
			}
			else {
				for (int j = 0; j < matrix->n; ++j) {

					cout << "   0";
				}
				cout << endl;
			}
		}
		SparseMatrix* ResultMatrix = CreateNewMatrix(matrix);
		return 1;
	}


	// ������� ����������� ������������ ������
	bool CheckPol(RowOfSparseMatrix* row, SparseMatrix* matrix)
	{
		bool flag = 1;
		if (row == nullptr)
			return flag;
		if (matrix->Rowlist == nullptr)
			return flag;
		int str_length = 1;
		RowOfSparseMatrix *row1, *row2, *row3;
		row1 = row;
		row2 = row;
		row3 = row;
		while (row->next != nullptr)
		{
			str_length++;
			row = row->next;
		}
		while (flag)
		{
			for (int i = 0; i < str_length; i++)
			{
				if (row2->next != nullptr)
				{
					row2 = row2->next;
				}
			}

			if ((row1->val != row2->val) || (row1->j != matrix->n - row2->j - 1))
				flag = 0;
			else
			{
				str_length = str_length - 1;
				if (str_length <= 0)
					break;
				row1 = row1->next;
				row2 = row;
			}
		}
		return flag;
	}


	// ������� ���������� ���-�� ������������ ����� � �������
	int CheckPolMtx(SparseMatrix* matrix)
	{
		int count = 0;
		SparseMatrixRowList* RowList_cpy = nullptr;
		RowList_cpy = matrix->Rowlist;
		if (matrix->Rowlist == nullptr)
			return matrix->m;
		for (int i = 0; i < matrix->m; i++)
		{
			if (i != matrix->Rowlist->i)
				count++;
			else
			{
				if (CheckPol(matrix->Rowlist->row, matrix))
					count++;
				if (matrix->Rowlist->next != nullptr)
					matrix->Rowlist = matrix->Rowlist->next;
			}
		}
		matrix->Rowlist = RowList_cpy;
		return count;
	}

	SparseMatrix* CreateNewMatrix(SparseMatrix* matrix) {
		SparseMatrix* ResultMatrix = new SparseMatrix;		// �������������� ����������� �������
		ResultMatrix->m = CheckPolMtx(matrix);
		ResultMatrix->n = matrix->n;
		ResultMatrix->Rowlist = nullptr;
		SparseMatrixRowList* rows = matrix->Rowlist;
		while (rows) {
			RowOfSparseMatrix* now = rows->row;
			if (CheckPol(now, matrix))
			{
				while (now) {
					AddNewRow(ResultMatrix, rows->i, now->j, now->val);
					now = now->next;
				}
			}
			else
			{
				while (now)
					now = now->next;
			}
			rows = rows->next;
		}
		// ����� �������������� �������
		cout << endl << endl;
		rows = ResultMatrix->Rowlist;
		for (int i = 0; i < ResultMatrix->m; ++i) {
			if (rows) {
				RowOfSparseMatrix* now = rows->row;
				for (int j = 0; j < ResultMatrix->n; ++j) {
					if (now && now->j == j) {
						cout << setw(SZ) << right << now->val;
						now = now->next;
					}
					else
						cout << setw(SZ) << right << "0";
				}
				cout << endl;
				rows = rows->next;
			}
			else {
				for (int j = 0; j < matrix->n; ++j) {

					cout << setw(SZ) << right << "0";
				}
				cout << endl;
			}
		}
		return ResultMatrix;
	}


	// ������� �������� 
	void Delete(SparseMatrix* matrix) {
		SparseMatrixRowList* rows = matrix->Rowlist;
		while (rows) {
			matrix->Rowlist = matrix->Rowlist->next;
			RowOfSparseMatrix* tmp = rows->row;
			while (tmp) {
				rows->row = rows->row->next;
				delete tmp;
				tmp = rows->row;
			}
			rows = matrix->Rowlist;
		}
	}

	
	
}