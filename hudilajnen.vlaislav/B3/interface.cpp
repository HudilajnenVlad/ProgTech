#include "interface.hpp"
#include <string>
#include <iostream>
#include "phone-book.hpp"

Interface::Interface():
    phoneBook_(),
    bookmarkList_()
{
  bookmarkList_.push_back({"current", phoneBook_.begin()});
}

Interface::iterator Interface::findMark(const std::string &markName)
{
  Interface::iterator i = bookmarkList_.begin();
  while (i != bookmarkList_.end())
  {
    if (i->name == markName)
    {
      return i;
    }
    ++i;
  }
  return i;
}

void Interface::add(const std::string &number, const std::string &name)
{
  phoneBook_.pushBack({number, name});
  if (phoneBook_.begin() == std::prev(phoneBook_.end()))
  {
    bookmarkList_.begin()->contact--;
  }
}

void Interface::store(const std::string &firstMark, const std::string &secondMark, std::ostream &out)
{
  iterator iter = findMark(firstMark);
  if (iter == bookmarkList_.end())
  {
    out << INVALID_BOOKMARK_ERROR;
    return;
  }
  bookmarkList_.push_back({secondMark, iter->contact});
}

void Interface::insert(const std::string &position, const std::string &markName, const std::string &number,
    const std::string &name, std::ostream &out)
{
  if (phoneBook_.isEmpty())
  {
    phoneBook_.pushBack({number, name});
    bookmarkList_.begin()->contact = phoneBook_.begin();
    return;
  }
  iterator iter = findMark(markName);
  if (iter == bookmarkList_.end())
  {
    out << INVALID_BOOKMARK_ERROR;
    return;
  }
  PhoneBook::iterator contactIterator = iter->contact;
  if (position == "before")
  {
    if (contactIterator == phoneBook_.begin())
    {
      contactIterator = phoneBook_.insert(phoneBook_.begin(), {number, name});
    }
    else
    {
      contactIterator = phoneBook_.insert(contactIterator, {number, name});
    }
  }
  else
  {
    contactIterator = phoneBook_.insert(++contactIterator, {number, name});
  }
}

void Interface::deleteMark(const std::string &markName, std::ostream &out)
{
  Interface::iterator bookmark = findMark(markName);
  if (bookmark == bookmarkList_.end())
  {
    out << INVALID_BOOKMARK_ERROR;
    return;
  }
  PhoneBook::iterator contactIterator = bookmark->contact;
  for (iterator i = bookmarkList_.begin(); i != bookmarkList_.end(); ++i)
  {
    if (i->contact == contactIterator)
    {
      if (contactIterator == std::prev(phoneBook_.end()))
      {
        i->contact--;
      }
      else
      {
        i->contact++;
      }
    }
  }
  phoneBook_.erase(contactIterator);
}

void Interface::show(const std::string &markName, std::ostream &out)
{
  iterator iter = findMark(markName);
  if (iter == bookmarkList_.end())
  {
    out << INVALID_BOOKMARK_ERROR;
    return;
  }
  if (phoneBook_.isEmpty())
  {
    out << EMPTY;
    return;
  }
  out << iter->contact->number << ' ' << iter->contact->name << '\n';
}

void Interface::move(const std::string &markName, int steps, std::ostream &out)
{
  iterator iter = findMark(markName);
  if (iter == bookmarkList_.end())
  {
    out << INVALID_BOOKMARK_ERROR;
    return;
  }
  if (steps > 0)
  {
    for (int i = steps; i > 0; --i)
    {
      if (iter->contact == std::prev(phoneBook_.end()))
      {
        iter->contact = phoneBook_.begin();
        continue;
      }
      iter->contact++;
    }
  }
  else if (steps < 0)
  {
    for (int i = -steps; i > 0; --i)
    {
      if (iter->contact == phoneBook_.begin())
      {
        iter->contact = std::prev(phoneBook_.end());
        continue;
      }
      iter->contact--;
    }
  }
}

void Interface::move(const std::string &markName, const std::string &place, std::ostream &out)
{
  iterator iter = findMark(markName);
  if (iter == bookmarkList_.end())
  {
    out << INVALID_BOOKMARK_ERROR;
    return;
  }
  if (place == "first")
  {
    iter->contact = phoneBook_.begin();
  }
  else if (place == "last")
  {
    iter->contact = std::prev(phoneBook_.end());
  }
  else
  {
    out << INVALID_COMMAND_ERROR;
  }
}
