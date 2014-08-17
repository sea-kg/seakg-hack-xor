#include "HackXorElem.h"

HackXorElem::HackXorElem() {
};

void HackXorElem::setAlphabetKey(QByteArray &arr) {
	m_possible_solution.clear();
	for (int i = 0; i < arr.size(); i++) {
		if (!m_possible_solution.contains(arr[i]))
			m_possible_solution.push_back(arr[i]);
	}
}

void HackXorElem::setAlphabetText(QByteArray &arr) {
	m_alphabet.clear();
	for (int i = 0; i < arr.size(); i++) {
		if (!m_alphabet.contains(arr[i]))
			m_alphabet.push_back(arr[i]);
	}
}

void HackXorElem::addChar(unsigned char ch) {
	m_vect.push_back(ch);
	filter(ch);
};

void HackXorElem::filter(unsigned char ch) {
	for (int k1 = 0; k1 < m_possible_solution.size(); k1++) {
		int p = 0;
		unsigned char k = m_possible_solution[k1];
		for (int t1 = 0; t1 < m_alphabet.size(); t1++) {
			unsigned char t = m_alphabet[t1];
			if ((t ^ k) == ch)
				p++;
		}
		
		if (p == 0 && m_possible_solution.contains(k)) {
			int size = m_possible_solution.size();
			m_possible_solution.remove(m_possible_solution.indexOf(k));
			if (size != m_possible_solution.size()+1)
			  std::cout << "Warning!!!\n";
		}
	}
};

void HackXorElem::printPossibleSolution() {
	std::cout << " size(" << m_possible_solution.size() << "/" << m_alphabet.size() << ") ";
	for (int i = 0; i < m_possible_solution.size(); i++) {
		std::cout << (i == 0 ? "" : ", ");
		std::cout << m_possible_solution[i] << " (" << (int)m_possible_solution[i] << ")";
	}
	std::cout << "\n";
}

QVector<unsigned char> & HackXorElem::getPossibleSolution() {
	return m_possible_solution;
};

unsigned char & HackXorElem::getChar(int i) {
	return m_possible_solution[i];
} 
