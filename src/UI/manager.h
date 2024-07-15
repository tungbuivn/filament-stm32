#pragma once
#include "tbt_thread.h"
#include "home.h"
#include <vector>
#include "base.h"
#include "../mylcd.h"
#include "settings.h"
using namespace std;
class ManagerPage : public BaseThread {
  int page;
  vector<BasePage*> pages;
  static bool onRotate(EventData *);
  static bool onClick(EventData *);
  static bool gotoPage(EventData *);
  // static bool onButtonTrigger(EventData *);
  
 
public:
  ManagerPage(LCDThread* lcd,Settings *settings);
  void execute() override;
 

};