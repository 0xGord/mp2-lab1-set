// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

// Fake variables used as placeholders in tests
static const int FAKE_INT = -1;
static TBitField FAKE_BITFIELD(1);
static TSet FAKE_SET(1);

TSet::TSet(int mp) : BitField(mp), MaxPower(mp) {}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField), MaxPower(s.MaxPower) {}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf), MaxPower(bf.GetLength()) {}

TSet::operator TBitField()
{
    TBitField bf(BitField);
    return bf;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    if (this != &s)
    {
        BitField = s.BitField;
        MaxPower = s.MaxPower;
    }
    return *this;;
}

bool TSet::operator==(const TSet &s) const // сравнение
{
   
    return BitField == s.BitField && MaxPower == s.MaxPower;
}

bool TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);;
}

TSet TSet::operator+(const TSet &other) // объединение
{
    int size = max(MaxPower, other.MaxPower);
    TSet res(max(MaxPower, other.MaxPower));
    for (int i = 0; i < MaxPower; i++)
        if (BitField.GetBit(i))
            res.BitField.SetBit(i);
    for (int i = 0; i < other.MaxPower; i++)
        if (other.BitField.GetBit(i))
            res.BitField.SetBit(i);
    return res;
}

TSet TSet::operator+(const int elem) // объединение с элементом
{
    InsElem(elem);
    return *this;
}

TSet TSet::operator-(const int elem) // разность с элементом
{
    DelElem(elem);
    return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet result(max(MaxPower, s.MaxPower));
    result.BitField = BitField & s.BitField;
    return result;
}

TSet TSet::operator~(void) // дополнение
{
    TSet ans(MaxPower);
    ans.BitField = ~BitField;
    return ans;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    istr >> s.BitField;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{   
    ostr << "MaxPower: " << s.MaxPower << endl;
    ostr << "Сharacteristic vector: " << s.BitField << '\n';
    return ostr;
}
