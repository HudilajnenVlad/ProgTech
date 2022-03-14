#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <string>
#include <memory>
#include <list>

class PhoneBook
{
public:
  struct contact_t
  {
    std::string number;
    std::string name;
  };

  typedef std::list<contact_t>::iterator iterator;

  iterator insert(iterator pos, const contact_t &contact);

  void pushBack(const contact_t &contact);

  void replace(iterator pos, contact_t contact);

  iterator erase(iterator pos);

  iterator begin();

  iterator end();

  int size() const;

  bool isEmpty() const;

private:
  std::list<contact_t> contactList_;
};

#endif
