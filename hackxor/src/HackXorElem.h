#ifndef __HACK_XOR_ELEM_H__
#define __HACK_XOR_ELEM_H__

#include <QString>
#include <QByteArray>
#include <QVector>
#include <iostream>


class HackXorElem {
	public:
		HackXorElem();
		void addChar(unsigned char ch);
		void filter(unsigned char ch);
		void printPossibleSolution();
		void setAlphabetKey(QByteArray &arr);
		void setAlphabetText(QByteArray &arr);
		
		QVector<unsigned char> &getPossibleSolution();
		unsigned char &getChar(int i);
		
		
	private:
		QVector<unsigned char> m_alphabet;
		QVector<unsigned char> m_alphabetKey;
		QString m_strAlphabetKey;
		QVector<unsigned char> m_vect;
		QVector<unsigned char> m_possible_solution;
};

#endif //__HACK_XOR_ELEM_H__
