#include "seakg_hack_xor.h"
#include <wsjcpp_core.h>
#include <algorithm>

// ---------------------------------------------------------------------

bool SeakgHackXor::makeFileXor(
    const std::string &sFromFilename,
    const std::string &sKeyFilename,
    const std::string &sToFilename
) {
    std::string TAG = "SeakgHackXor::makeFileXor";
    if (!WSJCppCore::fileExists(sFromFilename)) {
        WSJCppLog::err(TAG, "Input file did not exists '" + sFromFilename + "'");
        return false;
    }

    if (!WSJCppCore::fileExists(sKeyFilename)) {
        WSJCppLog::err(TAG, "Key file did not exists '" + sKeyFilename + "'");
        return false;
    }

    char *pInputBuffer = nullptr;
    int nBufferSize = 0;
    if (!WSJCppCore::readFileToBuffer(sFromFilename, &pInputBuffer, nBufferSize)) {
        return false;
    }

    char *pKeyBuffer = nullptr;
    int nKeyBufferSize = 0;
    if (!WSJCppCore::readFileToBuffer(sKeyFilename, &pKeyBuffer, nKeyBufferSize)) {
        delete[] pInputBuffer;
        return false;
    }

    char *pOutputBuffer = new char[nBufferSize];
    if (!SeakgHackXor::makeXor(pInputBuffer, nBufferSize, &pOutputBuffer, pKeyBuffer, nKeyBufferSize)) {
        delete[] pInputBuffer;
        delete[] pOutputBuffer;
        delete[] pKeyBuffer;
        return false;
    }

    WSJCppCore::writeFile(sToFilename, pOutputBuffer, nBufferSize);
    delete[] pInputBuffer;
    delete[] pOutputBuffer;
    delete[] pKeyBuffer;
    return true;
};

// ---------------------------------------------------------------------

bool SeakgHackXor::makeXor(
    const char *pInputBuffer, const int nBufferSize,
    char *pOutputBuffer[], // pInputBuffer and pOutputBuffer must have same size
    const char *pKeyBuffer, const int nKeySize
) {
    std::string TAG = "SeakgHackXor::makeXor";
    if (nKeySize <= 0) {
        WSJCppLog::throw_err(TAG, "Key size must be more then 0");
    }
    if (nBufferSize <= 0) {
        WSJCppLog::throw_err(TAG, "Buffer size must be more then 0");
    }
	int ik = 0;
	for (int i = 0; i < nBufferSize; i++) {
        unsigned char cInput = pInputBuffer[i];
        unsigned char cKey = pKeyBuffer[ik];
        unsigned char cResult = cInput ^ cKey;
        // std::cout << (int)cInput << " ^ " << (int) cKey << " = " << (int) cResult << std::endl;
		(*pOutputBuffer)[i] = cResult;
		ik++;
		if (ik >= nKeySize) {
			ik = 0;
		}
	}
    return true;
}

// ---------------------------------------------------------------------

bool SeakgHackXor::hackFileXor(
    const std::string &sCryptedFilename,
    int nKeyLength,
    const std::string &sKeyAlphabetFilename,
    const std::string &sTextAlphabetFilename
) {
    std::string TAG = "SeakgHackXor::hackFileXor";

    if (nKeyLength <= 0) {
        WSJCppLog::err(TAG, "Key length must be more then 0, but got '" + std::to_string(nKeyLength) + "'");
        return false;
    }
    if (!WSJCppCore::fileExists(sCryptedFilename)) {
        WSJCppLog::err(TAG, "Input file did not exists '" + sCryptedFilename + "'");
        return false;
    }

    if (!WSJCppCore::fileExists(sKeyAlphabetFilename)) {
        WSJCppLog::err(TAG, "Key alphabet file did not exists '" + sKeyAlphabetFilename + "'");
        return false;
    }

    if (!WSJCppCore::fileExists(sTextAlphabetFilename)) {
        WSJCppLog::err(TAG, "Text alphabet file did not exists '" + sTextAlphabetFilename + "'");
        return false;
    }

    char *pBuffer = nullptr;
    int nBufferSize = 0;
    if (!WSJCppCore::readFileToBuffer(sCryptedFilename, &pBuffer, nBufferSize)) {
        return false;
    }

    char *pKeyAlphabetBuffer = nullptr;
    int nKeyAlphabetBufferSize = 0;
    if (!WSJCppCore::readFileToBuffer(sKeyAlphabetFilename, &pKeyAlphabetBuffer, nKeyAlphabetBufferSize)) {
        delete[] pBuffer;
        return false;
    }

    char *pTextAlphabetBuffer = nullptr;
    int nTextAlphabetBufferSize = 0;
    if (!WSJCppCore::readFileToBuffer(sTextAlphabetFilename, &pTextAlphabetBuffer, nTextAlphabetBufferSize)) {
        delete[] pBuffer;
        delete[] pKeyAlphabetBuffer;
        return false;
    }
    
    if (!SeakgHackXor::hackXor(
        pBuffer, nBufferSize, 
        nKeyLength, 
        pKeyAlphabetBuffer, nKeyAlphabetBufferSize, 
        pTextAlphabetBuffer, nTextAlphabetBufferSize
    )) {
        delete[] pBuffer;
        delete[] pKeyAlphabetBuffer;
        delete[] pTextAlphabetBuffer;
        return false;
    }

    // WSJCppCore::writeFile(sToFilename, pOutputBuffer, nBufferSize);
    delete[] pBuffer;
    delete[] pKeyAlphabetBuffer;
    delete[] pTextAlphabetBuffer;
    return true;
}

// ---------------------------------------------------------------------

bool SeakgHackXor::hackXor(
    const char *pBuffer, const int nBufferSize,
    int nKeyLength,
    const char *pKeyAlphabetBuffer, const int nKeyAlphabetBufferSize,
    const char *pTextAlphabetBuffer, const int nTextAlphabetBufferSize
) {
    std::string TAG = "SeakgHackXor::hackXor";

    if (nKeyAlphabetBufferSize <= 0) {
        WSJCppLog::err(TAG, "Key Alphabet Length must be more then 0");
        return false;
    }

    if (nTextAlphabetBufferSize <= 0) {
        WSJCppLog::err(TAG, "Text Alphabet Length must be more then 0");
        return false;
    } 

    // init 
    std::vector<SeakgHackXorElement *> vElements;
	for (int i = 0; i < nKeyLength; i++) {
		SeakgHackXorElement *pElement = new SeakgHackXorElement();
		pElement->setAlphabetKey(pKeyAlphabetBuffer, nKeyAlphabetBufferSize);
		pElement->setAlphabetText(pTextAlphabetBuffer, nTextAlphabetBufferSize);
		vElements.push_back(pElement);
	}

    // filtering of expected values
    for (int i = 0; i < nKeyLength; i++) {		
		int c = i;
		while (c < nBufferSize) {
			vElements[i]->addChar(pBuffer[c]);
			c += nKeyLength;
		}
	}
	

    // check the solutions
    int nEmptySolutions = 0;
    bool bOneSolution = true;
    int nMoreThenOneSolutions = 0;
	for (int i = 0; i < nKeyLength; i++) {
        int nPossibleSolutionsSize = vElements[i]->getPossibleSolution().size();
        if (nPossibleSolutionsSize == 0) {
            nEmptySolutions++;
        }
        if (nPossibleSolutionsSize != 1) {
            bOneSolution = false;
        }
        if (nPossibleSolutionsSize > 1) {
            nMoreThenOneSolutions++;
        }
	}

    if (nEmptySolutions == nKeyLength) {
        WSJCppLog::err(TAG, "Not found possible solutions");
        return false;
    }


    if (nMoreThenOneSolutions > 0) {
        WSJCppLog::warn(TAG, "Difference solutions have");
    }
    // std::cout << "K[" << i << "] = ";
	// vElements[i]->printPossibleSolution();

    if (bOneSolution) {
        WSJCppLog::ok(TAG, "Found one solution: ");
        std::cout << "Hex   : [";
        for (int i = 0; i < nKeyLength; i++) {
            std::cout << SeakgHackXor::char2hexString(vElements[i]->getChar(0));
        }
        std::cout << "]" << std::endl;

        std::cout << "String: [";
        for (int i = 0; i < nKeyLength; i++) {
            std::cout << vElements[i]->getChar(0);
        }
        std::cout << "]" << std::endl;
    } else {
        

        WSJCppLog::warn(TAG, "Found several solutions, printed keys (HEX): ");
        for (int i = 0; i < nKeyLength; i++) {
            std::cout << "HEX   : possible_key[" << i << "] = {";
            for (int n = 0; n < vElements[i]->getPossibleSolution().size(); n++) {
                if (n > 0) {
                    std::cout << ", ";
                }
                std::cout << SeakgHackXor::char2hexString(vElements[i]->getChar(n));
            }
            
            std::cout << "}" << std::endl;
        }
        WSJCppLog::warn(TAG, "Found several solutions, printed keys (Printable keys): ");
        for (int i = 0; i < nKeyLength; i++) {
            std::cout << "String: possible_key[" << i << "] = {";
            for (int n = 0; n < vElements[i]->getPossibleSolution().size(); n++) {
                unsigned char c = vElements[i]->getChar(n);
                if (n > 0) {
                    std::cout << ", ";
                }
                if (isprint(c)) {
                    std::cout << c;
                } else {
                    std::cout << "0x" + SeakgHackXor::char2hexString(c);
                }
                
            }
            
            std::cout << "}" << std::endl;
        }
        int nCombinations = 1;
        for (int i = 0; i < nKeyLength; i++) {
            int nSize = vElements[i]->getPossibleSolution().size();
            if (nSize > 0) {
                nCombinations = nCombinations * nSize;
            } 
        }
        WSJCppLog::warn(TAG, "Found several solutions, all possible combinations: " + std::to_string(nCombinations));
    }

	/*for (int i = 0; i < nKeyLength; i++) {
		if (vElements[i]->getPossibleSolution().size() == 1) {
			std::cout << vElements[i]->getChar(0);
		} else {
			std::cout << "[";
			for (int f=0; f < vElements[i]->getPossibleSolution().size(); f++) {
				std::cout << vElements[i]->getChar(f);
			}
			std::cout << "]";
		}
	}*/
	
    for (int i = 0; i < nKeyLength; i++) {
        delete (vElements[i]);
        vElements[i] = nullptr;
    }
    vElements.clear();
    return false;
}

// ---------------------------------------------------------------------

bool SeakgHackXor::generateBasicFilesWithAlphabets(const std::string& sDirName) {
    std::string TAG = "SeakgHackXor::generateBasicFilesWithAlphabets";
    if (!WSJCppCore::dirExists(sDirName)) {
        WSJCppLog::err(TAG, "Folder not exists '" + sDirName + "'");
        return false;
    }
    char *pAlphabet256 = new char[256];
    for (int i = 0; i < 256; i++) {
        pAlphabet256[i] = i;
    }
    WSJCppCore::writeFile(sDirName + "/alphabet256", pAlphabet256, 256);
    WSJCppLog::info(TAG, sDirName + "/alphabet256");

    std::string sEnglish = "\n\t\r "
        "QWERTYUIOPASDFGHJKLZXCVBNM"
        "qwertyuiopasdfghjklzxcvbnm"
        "!@#$%^&*()_+1234567890-="
        "'\"/?;:.><,?\\|";
    WSJCppCore::writeFile(sDirName + "/alphabet_text_english", sEnglish.c_str(), sEnglish.length());
    WSJCppLog::info(TAG, sDirName + "/alphabet_text_english");

    return true;
}

// ---------------------------------------------------------------------

std::string SeakgHackXor::char2hexString(unsigned char n) {
    std::string sRet;
    for (int i = 0; i < 2; i++) {
        sRet += "0123456789abcdef"[n % 16];
        n >>= 4;
    }
    return std::string(sRet.rbegin(), sRet.rend());
}

// ---------------------------------------------------------------------
// SeakgHackXorElement

SeakgHackXorElement::SeakgHackXorElement() {
    TAG = "SeakgHackXorElem";
};

// ---------------------------------------------------------------------

void SeakgHackXorElement::setAlphabetKey(const char *pBuffer, int nBufferSize) {
	m_vPossibleSolution.clear();
	for (int i = 0; i < nBufferSize; i++) {
        unsigned char c = pBuffer[i];
        if (std::find(m_vPossibleSolution.begin(), m_vPossibleSolution.end(), c) == m_vPossibleSolution.end()) {
            m_vPossibleSolution.push_back(c);
        }
	}
}

// ---------------------------------------------------------------------

void SeakgHackXorElement::setAlphabetText(const char *pBuffer, int nBufferSize) {
	m_vAlphabet.clear();
	for (int i = 0; i < nBufferSize; i++) {
        unsigned char c = pBuffer[i];
        if (std::find(m_vAlphabet.begin(), m_vAlphabet.end(), c) == m_vAlphabet.end()) {
            m_vAlphabet.push_back(c);
        }
	}
}

// ---------------------------------------------------------------------

void SeakgHackXorElement::addChar(unsigned char ch) {
	m_vect.push_back(ch);
	filter(ch);
};

// ---------------------------------------------------------------------

void SeakgHackXorElement::filter(unsigned char ch) {
	for (int k1 = 0; k1 < m_vPossibleSolution.size(); k1++) {
		int p = 0;
		unsigned char k = m_vPossibleSolution[k1];
		for (int t1 = 0; t1 < m_vAlphabet.size(); t1++) {
			unsigned char t = m_vAlphabet[t1];
			if ((t ^ k) == ch) {
                p++;
            }
		}
		
        std::vector<unsigned char>::iterator it;
        it = std::find(m_vPossibleSolution.begin(), m_vPossibleSolution.end(), k);
        if (p == 0 && it != m_vPossibleSolution.end()) {
			int size = m_vPossibleSolution.size();
			m_vPossibleSolution.erase(it);
			if (size != m_vPossibleSolution.size()+1) {
                WSJCppLog::warn(TAG, "Warning");
            }
		}
	}
};

// ---------------------------------------------------------------------

void SeakgHackXorElement::printPossibleSolution() {
	std::cout << " size(" << m_vPossibleSolution.size() << "/" << m_vAlphabet.size() << ") ";
	for (int i = 0; i < m_vPossibleSolution.size(); i++) {
		std::cout << (i == 0 ? "" : ", ");
		std::cout << m_vPossibleSolution[i] << " (" << (int)m_vPossibleSolution[i] << ")";
	}
	std::cout << "\n";
}

// ---------------------------------------------------------------------

const std::vector<unsigned char> & SeakgHackXorElement::getPossibleSolution() {
	return m_vPossibleSolution;
};

// ---------------------------------------------------------------------

unsigned char & SeakgHackXorElement::getChar(int i) {
	return m_vPossibleSolution[i];
}

// ---------------------------------------------------------------------
