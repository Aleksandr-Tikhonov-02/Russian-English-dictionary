#ifndef _ORDERED_LIST_
#define _ORDERED_LIST_

#include <iosfwd>
#include <string>

class OrderedList
{
public:
  OrderedList(): head_(nullptr), tail_(nullptr), count_(0) {}
  OrderedList(std::string meaning);
  OrderedList(const OrderedList& src) = delete;
  OrderedList(OrderedList&& src) noexcept = delete;
  OrderedList& operator=(const OrderedList& src) = delete;
  OrderedList& operator=(OrderedList&& src) noexcept = delete;
  ~OrderedList();


  int getCount() const;
  bool insertItem(const std::string& meaning);
  void print(std::ostream& out);

private:
  struct listNode
  {
    std::string meaning_;
    listNode* next_;
    listNode(std::string meaning, listNode* next = nullptr): 
      meaning_(meaning), next_(next) 
    {};
  };
  void insertTail(const std::string& meaning);
  void insertTail(listNode* x);
  int count_;
  listNode* head_;
  listNode* tail_;
};

#endif
