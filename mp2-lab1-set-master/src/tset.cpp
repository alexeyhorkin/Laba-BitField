// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	if (mp < 0)
		throw 1;
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.GetMaxPower();
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
  return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if((Elem<MaxPower)&(Elem >= 0))
	if (BitField.GetBit(Elem) == 1) 
    return 1;
	else return 0;
	else throw "Elem<0";
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (!IsMember(Elem))
		BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (IsMember(Elem))
		BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
  return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
		return 0;
	else if (BitField != s.BitField)
		return 0;
	else return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
		return 1;
	else if (BitField != s.BitField)
		return 1;
	else return 0;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet res (BitField | s.BitField);

	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet res(*this);
	if (!IsMember(Elem))
		res.InsElem(Elem);
	return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet res(*this);
	if (IsMember(Elem))
		res.BitField.ClrBit(Elem);
	return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet res(BitField & s.BitField);
  return res;
}

TSet TSet::operator~(void) // дополнение
{
	
	TSet a(~BitField);
	return a;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  return ostr;
}
