#include <QCoreApplication>
#include <QString>
#include <QFile>
#include <QVector>
// #include <QTextStream>

#include <iostream>
#include "HackXorElem.h"

void recource(QVector<HackXorElem *> &xorBruts, QVector<unsigned char> keys, char *data) {
	int s = keys.size();
	if (keys.size() >= 44) {
		QString str;
		for (int i = 0; i < keys.size(); i++) {
			str += QChar(keys[i] ^ (unsigned char)data[i]);
		}
		std::cout << str.toStdString() << "\n";
		return;
	}
	
	
	for (int i = 0; i < xorBruts[s]->getPossibleSolution().size(); i++) {
		QVector<unsigned char> tmp_keys;
		tmp_keys += keys;
		tmp_keys.push_back(xorBruts[s]->getChar(i));
		recource(xorBruts, tmp_keys, data);
	}
};

int main (int argc, char *argv[])
{
	if (argc != 5) {
		std::cout << "usage: " << argv[0] << " <encrypted-file> <length-key> <file-with-alphabet-for-key> <file-with-alphabet-for-text>\n";
		return -1;
	}
	
	QString sInputFile(argv[1]);
	QString sLengthKey(argv[2]);
	QString sFileAlphabetKey(argv[3]);
	QString sFileAlphabetText(argv[4]);
	
	std::cout << "Hello! It's program for hack xor.\n";

	QFile ifile(sInputFile);
	if(!ifile.open(QIODevice::ReadOnly)) {
		std::cout << "error: '"  <<  sInputFile.toStdString() << "' - " << ifile.errorString().toStdString() << "\n";
		return -2;
	}
	
	QByteArray encryptedText = ifile.readAll();
	
	int lengthKey = sLengthKey.toInt();
	
	QByteArray key;
	key.resize(lengthKey);

	std::cout << "length key: " << key.size() << "\n";

	QFile alph_kfile(sFileAlphabetKey);
	if(!alph_kfile.open(QIODevice::ReadOnly)) {
		std::cout << "error: '"  <<  sFileAlphabetKey.toStdString() << "' - " << alph_kfile.errorString().toStdString() << "\n";
		return -3;
	}
	
	QFile alph_tfile(sFileAlphabetText);
	if(!alph_tfile.open(QIODevice::ReadOnly)) {
		std::cout << "error: '"  <<  sFileAlphabetText.toStdString() << "' - " << alph_tfile.errorString().toStdString() << "\n";
		return -4;
	}
	
	
	QByteArray alphabetKey = alph_kfile.readAll();
	QByteArray alphabetText = alph_tfile.readAll();
	alph_kfile.close();
	alph_tfile.close();

	QVector<HackXorElem *> hackXorElems;
	for (int i = 0; i < lengthKey; i++) {
		HackXorElem *elem = new HackXorElem();
		elem->setAlphabetKey(alphabetKey);
		elem->setAlphabetText(alphabetText);
		hackXorElems.push_back(elem);
	}
	
	for (int i = 0; i < lengthKey; i++) {		
		int c = i;
		while (c < encryptedText.size()) {
			hackXorElems[i]->addChar(encryptedText[c]);
			c += lengthKey;
		}
	}
	
	for (int i = 0; i < lengthKey; i++) {
		std::cout << "K[" << i << "] = ";
		hackXorElems[i]->printPossibleSolution();
	}

	for (int i = 0; i < lengthKey; i++) {
		if (hackXorElems[i]->getPossibleSolution().size() == 1) {
			std::cout << hackXorElems[i]->getChar(0);
		} else {
			std::cout << "[";
			for (int f=0; f < hackXorElems[i]->getPossibleSolution().size(); f++) {
				std::cout << hackXorElems[i]->getChar(f);
			}
			std::cout << "]";
		}
	}
	std::cout << ")\n";
	
	QVector<unsigned char> keys;
	// char *data;
	
	// recource(xorBruts, keys, data);

	return -1;
}
//----------------------------------------------------------------
