// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
	if (len < 0)
		throw 1;
	BitLen = len;
	MemLen = (BitLen / BITS_IN_ONE_MEM)+1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i<MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
return  (n / BITS_IN_ONE_MEM);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % BITS_IN_ONE_MEM);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n<0) || (n>BitLen))
		throw 1;
	pMem[GetMemIndex(n)] |= GetMemMask(n);

}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n<0) || (n>BitLen))
		throw 1;
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n<0) || (n>BitLen))
		throw 1;
	if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0)
		return 0;
	else return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen != bf.BitLen)
		delete[]pMem;
		BitLen = bf.BitLen;
	MemLen = (BitLen / BITS_IN_ONE_MEM)+1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];
  return *this;
}

bool TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (MemLen != bf.MemLen)
		return false;
	else if (BitLen != bf.BitLen)
		return false;
	else
	{
		for (int i = 0; i < MemLen - 1; i++)
			if (pMem[i] != bf.pMem[i])
				return false;

		for (int i = (MemLen - 1)*BITS_IN_ONE_MEM; i < BitLen; i++)
		{
			int a;
			int b;
			a = GetBit(i); b = bf.GetBit(i);
			if (a != b) return false;
		}
	}
	return true;
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
	bool res = (*this == bf);
	return !res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	{
		int max;
		int min;
		int y;
		if (BitLen > bf.BitLen)
		{
			y = 0; // This is big
			max = BitLen;
			min = bf.BitLen;
		}
		else {
			y = 1; //bf is big
			max = bf.BitLen;
			min = BitLen;
		}
		TBitField a(max);
		for (int i = 0; i <= GetMemIndex(min); i++) a.pMem[i] = bf.pMem[i] | pMem[i];
		for (int i = (GetMemIndex(min) + 1); i < a.MemLen; i++) if (y == 1) a.pMem[i] = bf.pMem[i]; else a.pMem[i] = pMem[i];
		return a;
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int min;
	if (BitLen >= bf.BitLen)
		min = bf.BitLen;
	else min = BitLen;
	TBitField res (min);
	for (int i = 0; i < res.MemLen; i++)
		res.pMem[i] = pMem[i] & bf.pMem[i];
  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < BitLen; i++)
	{	
		if (GetBit(i) == 0)
			res.SetBit(i);
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int k;
	int z;
    cout << "Enter the Bitlen" << endl;
	cin >> k;
	TBitField A (k);
	cout << "Enter the BitField, please" << endl; 
	for (int i = 0; i < A.BitLen; i++)
	{
		cin >> z;
		if (z == 1)
			A.SetBit(i);
	}
	bf = A;
	
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		if(bf.GetBit(i)==0)
		ostr << 0;
		else ostr << 1;
		ostr << endl;
  return ostr;
}
