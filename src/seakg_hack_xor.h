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

		static bool hackFileXor(
            const std::string &sCryptedFilename,
			int nKeyLength,
            const std::string &sKeyAlphabetFilename,
            const std::string &sTextAlphabetFilename
        );

		static bool hackXor(
			const char *pBuffer, const int nBufferSize,
			int nKeyLength,
			const char *pKeyAlphabetBuffer, const int nKeyAlphabetBufferSize,
			const char *pTextAlphabetBuffer, const int nTextAlphabetBufferSize
        );

		static bool generateBasicFilesWithAlphabets(const std::string& sDirName);
		static std::string char2hexString(unsigned char n);
};

// ---------------------------------------------------------------------

class SeakgHackXorElement {
	public:
		SeakgHackXorElement();
		void addChar(unsigned char ch);
		void filter(unsigned char ch);
		void printPossibleSolution();
		void setAlphabetKey(const char *pBuffer, int nBufferSize);
		void setAlphabetText(const char *pBuffer, int nBufferSize);
		
		const std::vector<unsigned char> &getPossibleSolution();
		unsigned char &getChar(int i);
		
		
	private:
        std::string TAG;
		std::vector<unsigned char> m_vAlphabet;
		std::vector<unsigned char> m_vAlphabetKey;
		std::string m_sAlphabetKey;
		std::vector<unsigned char> m_vect;
		std::vector<unsigned char> m_vPossibleSolution;
};

#endif // SEAKG_HACK_XOR_H