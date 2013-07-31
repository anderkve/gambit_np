//  GAMBIT: Global and Modular BSM Inference Tool
//  *********************************************
/// \file
///  Utility Functions for the Gambit Scanner
//
//  *********************************************
//
//  Authors
//  =======
//
//  (add name and date if you modify)
//
///  \author Gregory Martinez (gregory.david.martinez@gmail.com)
///  \date July 2013
//
//  *********************************************

#ifndef __scanner_utils_hpp__
#define __scanner_utils_hpp__

#include <string>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace GAMBIT
{
        namespace Scanner
        {
                bool GAMBIT_SCANNER_EXIT = true;
                
                const unsigned char missingParameter = 0x01;
                const unsigned char missingModel = 0x02;
                const unsigned char tooManyModels = 0x04;
                const unsigned char tooManyParamters = 0x08;
                const unsigned char noRange = 0x10;
                const unsigned char cyclicSames = 0x20;
                const unsigned char badSames = 0x40;

                const unsigned char dummyParam = 0x01;
                const unsigned char fixedParam = 0x02;
                const unsigned char singleParam = 0x04;
                const unsigned char multiParam = 0x08;
                const unsigned char fixedMultiParam = 0x10;
                
                int defout;
                
                void gambitScannerExit(void)
                { 
                        if (GAMBIT_SCANNER_EXIT) 
                        {
                                dup2(defout, STDOUT_FILENO); 
                                printf("Gambit has been terminated, please press enter to continue ... "); 
                                getchar();}
                                
                        }
                
                FILE *LaunchLogWindow(string &file)
                {
                        char *name = tempnam(NULL, NULL);
                        mkfifo(name, 0777);
                        if(fork() == 0)
                        {
                                //sprintf(cmd, "xterm -e cat %s", name);
                                std::string cmd = string("xterm -T ") + file +  string(" -e cat ") + string(name);
                                system(cmd.c_str());
                                //exit(0);
                        }
                        return fopen(name, "w");
                }
        };
};

#endif