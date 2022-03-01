#include "orederedList.hpp"
#include <iostream>
#include <utility>


OrderedList::OrderedList(std::string meaning):
  count_(1)
{
  head_ = tail_ = new listNode(meaning);
}

OrderedList::~OrderedList()
{
  listNode* current = nullptr;
  listNode* next = head_;
  while (next != nullptr)
  {
    current = next;
    next = next->next_;
    delete current;
  }
}

int OrderedList::getCount() const
{
  return count_;
}

bool OrderedList::insertItem(const std::string& meaning)
{
  listNode* previous = nullptr;
  listNode* current = head_;
  if (!current)
  {
    head_ = tail_ = new listNode(meaning);
    count_++;
    return true;
  }
  while(current != nullptr)
  {
    if (meaning == current->meaning_)
    {
      return false;
    }
    if (meaning > current->meaning_)
    {
      previous = current;
      current = current->next_;
    }
    else
    {
      if (previous)
      {
        previous->next_ = new listNode(meaning, current);
        count_++;
        return true;
      }
      else
      {
        head_ = new listNode(meaning, current);
        count_++;
        return true;
      }
    }
  }
  tail_ = previous->next_ = new listNode(meaning);
  count_++;
  return true;
}

void OrderedList::print(std::ostream& out)
{
  listNode* current = head_;
  if (!current)
  {
    out << "List is empty\n";
    return;
  }
  while (current)
  {
    out << " - " << current->meaning_ << '\n';
    current = current->next_;
  }
}

void OrderedList::insertTail(const std::string& meaning)
{
  insertTail(new listNode(meaning));
}

void OrderedList::insertTail(listNode* x)
{
  if (tail_ != nullptr)
  {
    tail_->next_ = x;  
  }
  else
  {
    head_ = x;
  }
  tail_ = x;
  count_++;
}
