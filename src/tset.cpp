// ����, ���, ���� "������ ����������������-2", �++, ���
//
// tset.cpp - Copyright (c) ������� �.�. 04.10.2001
//   ������������ ��� Microsoft Visual Studio 2008 �������� �.�. (19.04.2015)
//
// ��������� - ���������� ����� ������� ����

#include "tset.h"

TSet::TSet(int mp)
{
}

// ����������� �����������
TSet::TSet(const TSet &s)
{
}

// ����������� �������������� ����
TSet::TSet(const TBitField &bf)
{
}

TSet::operator TBitField()
{  
}

int TSet::GetMaxPower(void) const // �������� ����. �-�� ��-���
{
}

int TSet::IsMember(const int Elem) const // ������� ���������?
{
}

void TSet::InsElem(const int Elem) // ��������� �������� ���������
{
}

void TSet::DelElem(const int Elem) // ���������� �������� ���������
{
}

// ���������-������������� ��������

TSet& TSet::operator=(const TSet &s) // ������������
{  
}

int TSet::operator==(const TSet &s) const // ���������
{
}

int TSet::operator!=(const TSet &s) const // ���������
{
}

TSet TSet::operator+(const TSet &s) // �����������
{
}

TSet TSet::operator+(const int Elem) // ����������� � ���������
{
}

TSet TSet::operator-(const int Elem) // �������� � ���������
{
}

TSet TSet::operator*(const TSet &s) // �����������
{
}

TSet TSet::operator~(void) // ����������
{
}

// ���������� �����/������

istream &operator>>(istream &istr, TSet &s) // ����
{
}

ostream& operator<<(ostream &ostr, const TSet &s) // �����
{
}
