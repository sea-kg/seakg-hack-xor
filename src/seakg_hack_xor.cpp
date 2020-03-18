#include "seakg_hack_xor.h"
#include <wsjcpp_core.h>

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