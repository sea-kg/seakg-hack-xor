#ifndef SEAKG_HACK_XOR_H
#define SEAKG_HACK_XOR_H

#include <string>
#include <vector>

class SeakgHackXor {
    public:
        static bool makeFileXor(
            const std::string &sFromFilename,
            const std::string &sKeyFilename,
            const std::string &sToFilename
        );

        static bool makeXor(
            const char *pInputBuffer, const int nBufferSize,
            char *pOutputBuffer[], // pInputBuffer and pOutputBuffer must have same size
            const char *pKeyBuffer, const int nKeySize
        );
};

#endif // SEAKG_HACK_XOR_H