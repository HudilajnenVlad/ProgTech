#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <list>
#include <string>
#include <iostream>
#include "phone-book.hpp"

const std::string INVALID_COMMAND_ERROR = "<INVALID COMMAND>\n";
const std::string INVALID_BOOKMARK_ERROR = "<INVALID BOOKMARK>\n";
const std::string INVALID_STEP_ERROR = "<INVALID STEP>\n";
const std::string EMPTY = "<EMPTY>\n";

class Interface
{
public:
  struct bookmark_t
  {
    std::string name;
    std::list<PhoneBook::contact_t>::iterator contact;
  };

  typedef std::list<bookmark_t>::iterator iterator;

  Interface();

  void add(const std::string &number, const std::string &name);

  void store(const std::string &firstMark, const std::string &secondMark, std::ostream &out);

  void insert(const std::string &pos, const std::string &markName, const std::string &number, const std::string &name,
      std::ostream &out);

  void deleteMark(const std::string &markName, std::ostream &out);

  void show(const std::string &markName, std::ostream &out);

  void move(const std::string &markName, int steps, std::ostream &out);

  void move(const std::string &markName, const std::string &place, std::ostream &out);

private:
  PhoneBook phoneBook_;
  std::list<bookmark_t> bookmarkList_;

  iterator findMark(const std::string &markName);
};

#endif
