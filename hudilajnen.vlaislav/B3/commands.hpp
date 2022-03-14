#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include <map>
#include "interface.hpp"

struct LinkName
{
  std::string &name;
};

struct LinkContact
{
  std::string &contact;
};

struct LinkBookmark
{
  std::string &bookmark;
};

void readCommand(const std::string &inputCommand, Interface &interface, std::ostream &out);

void executeAdd(std::istream &input, std::ostream &out, Interface &interface);

void executeStore(std::istream &input, std::ostream &out, Interface &interface);

void executeInsert(std::istream &input, std::ostream &out, Interface &interface);

void executeDelete(std::istream &input, std::ostream &out, Interface &interface);

void executeShow(std::istream &input, std::ostream &out, Interface &interface);

void executeMove(std::istream &input, std::ostream &out, Interface &interface);

std::istream &operator>>(std::istream &input, LinkName name);

std::istream &operator>>(std::istream &input, LinkContact contact);

std::istream &operator>>(std::istream &input, LinkBookmark bookmark);

const std::map<std::string, void (*)(std::istream &, std::ostream &, Interface &)> commandsMap(
    {
        {"add",    executeAdd},
        {"store",  executeStore},
        {"insert", executeInsert},
        {"delete", executeDelete},
        {"show",   executeShow},
        {"move",   executeMove}
    });

#endif
