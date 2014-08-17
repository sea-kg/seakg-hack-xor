#include <QCoreApplication>
#include <QString>
#include <QFile>
#include <QByteArray>
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc != 4) {
		std::cout << "usage: " << argv[0] << " <inputfile> <keyfile> <outputfile>\n";
		return -1;
	}
	
	QString sInputFile(argv[1]);
	QString sKeyFile(argv[2]);
	QString sOutputFile(argv[3]);
	
	QFile ifile(sInputFile);
	if(!ifile.open(QIODevice::ReadOnly)) {
		std::cout << "error: '" << sInputFile.toStdString() << "' - " << ifile.errorString().toStdString() << "\n";
		return -1;
	}
	
	QFile kfile(sKeyFile);
	if(!kfile.open(QIODevice::ReadOnly)) {
		std::cout << "error: '" << sKeyFile.toStdString() << "' - " << kfile.errorString().toStdString() << "\n";
		return -2;
	}
	
	QFile ofile(sOutputFile);
	if(!ofile.open(QIODevice::WriteOnly))
	{
		std::cout << "error: '" << sOutputFile.toStdString() << "' - " << ofile.errorString().toStdString() << "\n";
		return -3;
	}
	
	QByteArray opentext = ifile.readAll();
	QByteArray textkey = kfile.readAll();
	
	int ik = 0;
	for (int i = 0; i < opentext.size(); i++) {
		opentext[i] = opentext[i] ^  textkey[ik];
		ik++;
		if (ik >= textkey.size()) {
			ik = 0;
		}
	}
	
	ofile.write(opentext);
	ofile.flush();
	
	ifile.close();
	kfile.close();
	ofile.close();
	return 0;
}
//----------------------------------------------------------------
