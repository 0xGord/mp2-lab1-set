// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);

TBitField::TBitField(int len)
{
    if (len < 0)
        throw invalid_argument("invalid argument");
    BitLen = len;
    MemLen = (len - 1) / (sizeof(TELEM) * 8) + 1;
    pMem = new TELEM[MemLen];
    for (size_t i = 0; i < MemLen; i++)
        pMem[i] = TELEM();
}

TBitField::TBitField(const TBitField &other) // конструктор копирования
{
    BitLen = other.BitLen;
    MemLen = other.MemLen;
    pMem = new TELEM[MemLen];
    memcpy(pMem, other.pMem, sizeof(TELEM) * other.MemLen);

}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n > BitLen || n < 0)
        throw out_of_range("bit pos is out of range");
    pMem[GetMemIndex(n)] |= GetMemMask(n);
    
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n > BitLen || n < 0)
        throw out_of_range("bit pos is out of range");
     pMem[GetMemIndex(n)] &= (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n > BitLen || n < 0)
        throw out_of_range("bit pos is out of range");
    return (pMem[GetMemIndex(n)] & (GetMemMask(n))) != 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &other) // присваивание
{
    if (&other != this)
    {
        delete[] pMem;
        MemLen = other.MemLen;
        BitLen = other.BitLen;
        pMem = new TELEM[MemLen];
        memcpy(pMem, other.pMem, sizeof(TELEM) * other.MemLen);

    }
    return *this;
}

bool TBitField::operator==(const TBitField& other) const // сравнение
{
    bool flag = true;
    for (size_t i = 0; i < MemLen; i++)
    {
        flag = pMem[i] == other.pMem[i];
        if (flag == false)
            break;
    }
    return flag;
}

bool TBitField::operator!=(const TBitField &other) const // сравнение
{
    return !(*this == other);
}

TBitField TBitField::operator|(const TBitField &other) // операция "или"
{
    TBitField res(max(BitLen, other.BitLen));
    for (int i = 0; i < res.BitLen; i++) {
        if (i < BitLen && GetBit(i) || i < other.BitLen && other.GetBit(i))
            res.SetBit(i);
    }
    return res;
}

TBitField TBitField::operator&(const TBitField &other) // операция "и"
{
   
    TBitField res(max(BitLen, other.BitLen));
    for (int i = 0; i < res.BitLen; i++)
    {
        res.SetBit(i);
        if (i >= BitLen || i >= other.BitLen || (!GetBit(i)) || (!other.GetBit(i)))
            res.ClrBit(i);
    }

    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField temp(BitLen);
    TBitField temp2(BitLen);
    for (int i = 0; i < BitLen; i++) {
        temp2.SetBit(i);
    }
    for (int i = 0; i < MemLen; i++)
        temp.pMem[i] = ~pMem[i];
    temp = temp2 & temp;
    return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int input;
    for (int i = 0; i < bf.BitLen; i++)
    {
        cin >> input;
        if (input == 0 || input == 1)
            bf.SetBit(i);
        else
            throw invalid_argument("invalid argument");
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bf.GetBit(i);
    return ostr;
}
