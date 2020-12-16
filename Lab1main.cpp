
/* ���� 1. ������� 30.
	�� �������� ������ �������� ������������� ������ ����������� ������� ����� ����� [aij], i = 1, �, m, j = 1, �, n.  �������� m � n ������� �� �������� � �������� �� �������� ������.
������������ ����� �������, �������� � �� i-�� ������ �������� �� i-�� ������ �������� �������, ���������� ������������.
�������� � ���������� ������� ������� � �������� ����� � ������������ �������������.*/


#include "Lab1.h"

using namespace Lab1;

extern const char* msgs[];




/* ������ ���������� �� ������� - ��� ���������� ������ �������; ������� ������������ ������� � ������ ������������� ������ �������������� ������� �������� ����������� � ������ ����������� */
int(*fptr[])(SparseMatrix*) = { NULL, D_Add, D_Show };


int main() {
	setlocale(0, "");
	SparseMatrix SourceMatrix = { 0, 0, nullptr };		// �������� ����������� �������
	SparseMatrix ResultMatrix = { 0 , 0, nullptr };		// �������������� �������
	Input(SourceMatrix);
	int rc;
	while (rc = dialog(msgs, NMsgs))
		if (!fptr[rc](&SourceMatrix))
			break;
	Delete(&SourceMatrix);
	Delete(&ResultMatrix);
	return 0;
}