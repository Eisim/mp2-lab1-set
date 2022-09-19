// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 0) throw std::exception("less than  0");

    BitLen = len;
    if ((unsigned int)(len / (sizeof(TELEM))) * (sizeof(TELEM)) == len) MemLen = len / (sizeof(TELEM));
    else  MemLen = len / (sizeof(TELEM)) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)pMem[i] = 0;
   
   
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM(MemLen);
    for (int i = 0; i < MemLen; i++)pMem[i] = bf.pMem[i];

}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n<0 || n>BitLen) throw std::exception("Index out of range.");
    return (BitLen-n) / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n<0 || n>BitLen) {
        throw std::exception("Index out of range.");
        return TELEM();
    }
    return (1 << ((BitLen - n) -GetMemIndex(n) * sizeof(TELEM) * 8));


}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n<0 || n>BitLen)throw std::exception("Index out of range");
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)]|GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n<0 || n>BitLen)throw std::exception("Index out of range");
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n<0 || n>BitLen) { 
        throw std::exception("Index out of range"); 
        return 0;
    }
    if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0) return 0;
    else return 1;

}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    delete[] pMem;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)pMem[i] = bf.pMem[i];
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen) return 0;
    for (int i = 0; i < MemLen; i++) if (pMem[i] != bf.pMem[i]) return 0;
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !operator==(bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    
    
    int minbitsize=std::min(MemLen,bf.MemLen);
    std::cout << minbitsize;
    TBitField result(0);
    if (BitLen > bf.BitLen) result = *this;
    else result = bf;
    for (int i = 0; i < minbitsize; i++)
        result.pMem[i] = pMem[i] | bf.pMem[i];
    return result;
    
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    return TBitField(0);
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(BitLen);
    int diff = sizeof(TELEM) * 8 * MemLen - BitLen;
    for (int i = 0; i < MemLen; i++) tmp.pMem[i] = ~pMem[i];
    for (int i = sizeof(TELEM) * 8 * MemLen + 1; i < BitLen; i++)
        tmp.ClrBit(i);
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    std::string str;
    istr >> str;
    TBitField tmp(str.size());
    for (int i = 0; i < str.size(); i++) {
        if ((int)str[i] == 49) //49 equal "1"
        {
            tmp.SetBit(i);
        }
    }
    bf = tmp;
    
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    
    for (int i = 0; i < bf.GetLength(); i++) {
        ostr << bf.GetBit(i);
        if (i % (sizeof(TELEM)) == 0 && i!=0)ostr << " ";
    }
    return ostr;
}
