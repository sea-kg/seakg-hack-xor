#include <string.h>
#include <iostream>
#include <algorithm>
#include <wsjcpp_core.h>
#include "seakg_hack_xor.h"

void printUsage(const std::string &sExecName) {
    std::cout << "\n  Usage: \n"
        << "    Crypt: " << sExecName << " xor orig_filepath key_filepath crypted_filepath \n"
        << "    Decrypt: " << sExecName << " xor crypted_filepath key_filepath decrypted_filepath \n"
        << "    Hack: " << sExecName << " hack crypted_filepath key_length key_alphabet_filepath text_alphabet_filepath\n"
        << "    Generate Key Alphabets: " << sExecName << " generate to_dirpath\n"
        << "\n"
    ;
}

int main(int argc, const char* argv[]) {
    std::string TAG = "MAIN";
    std::string appName = std::string(WSJCPP_NAME);
    std::string appVersion = std::string(WSJCPP_VERSION);
    if (!WSJCppCore::dirExists(".logs")) {
        WSJCppCore::makeDir(".logs");
    }
    WSJCppLog::setPrefixLogFile("seakg-hack-xor");
    WSJCppLog::setLogDirectory(".logs");
    std::vector<std::string> vArgs;

    for (int i = 0; i < argc; i++) {
        vArgs.push_back(std::string(argv[i]));
    }
    std::string sExecName = vArgs[0];
    if (vArgs.size() < 2) {
        printUsage(sExecName);
        return -1;
    }

    std::string sSubCommand = vArgs[1];

    if (sSubCommand == "help" || sSubCommand == "--help" || sSubCommand == "-h") {
        printUsage(sExecName);
        return 0;
    } else if (sSubCommand == "generate") {
        if (vArgs.size() != 3) {
            printUsage(sExecName);
            return -1;
        } else {
            if (!SeakgHackXor::generateBasicFilesWithAlphabets(vArgs[2])) {
                return -1;
            }
        }
    } else if (sSubCommand == "xor") {
        if (vArgs.size() != 5) {
            printUsage(sExecName);
            return -1;
        } else {
            if (!SeakgHackXor::makeFileXor(vArgs[2],vArgs[3],vArgs[4])) {
                return -1;
            }
        }
    } else if (sSubCommand == "hack") {
        if (vArgs.size() != 6) {
            printUsage(sExecName);
            return -1;
        } else {
            WSJCppLog::info(TAG, "Hello! It's program for hack xor.");
            int nKeyLength = atoi(vArgs[3].c_str());
            if (!SeakgHackXor::hackFileXor(vArgs[2], nKeyLength, vArgs[4], vArgs[5])) {
                return -1;
            }
        }
    } else {
        WSJCppLog::err(TAG, "Unknown subcommand '" + sSubCommand + "'");
        return -1;
    }
    return 0;
}

