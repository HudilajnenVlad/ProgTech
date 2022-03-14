#include "phone-book.hpp"

PhoneBook::iterator PhoneBook::insert(PhoneBook::iterator pos, const PhoneBook::contact_t &contact)
{
  return contactList_.insert(pos, contact);
}

PhoneBook::iterator PhoneBook::erase(PhoneBook::iterator pos)
{
  return contactList_.erase(pos);
}

void PhoneBook::pushBack(const PhoneBook::contact_t &contact)
{
  contactList_.push_back(contact);
}

void PhoneBook::replace(PhoneBook::iterator pos, PhoneBook::contact_t contact)
{
  pos->name = contact.name;
  pos->number = contact.number;
}

PhoneBook::iterator PhoneBook::begin()
{
  return contactList_.begin();
}

PhoneBook::iterator PhoneBook::end()
{
  return contactList_.end();
}

bool PhoneBook::isEmpty() const
{
  return contactList_.empty();
}

int PhoneBook::size() const
{
  return contactList_.size();
}
