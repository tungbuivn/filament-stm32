#pragma once
#include "tbt_thread.h"
#include "home.h"
#include <vector>
#include "base.h"
using namespace std;
class ManagerPage : public BaseThread {
  int page;
  vector<BasePage*> pages;
  static bool onRotate(EventData *);
  static bool onClick(EventData *);
  static bool gotoPage(EventData *);
  static bool onOffStateChange(EventData *);
public:
  ManagerPage();
  void execute() override;
 

};