#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include "proc.h"

bool isIntNumber(std::string);
std::string ExtractFilenameFromPath(std::string);
void DisplayHelpInformations();
void ParseCommandAndRun(std::string, int, char *[], Photo &);

#endif