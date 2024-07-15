#pragma once
#include <vector>
#include <functional>
#include <map> 
#include <queue>
#include <functional>
#include "tbt_thread.h"

using namespace std;
class EventData {

public:
    virtual ~EventData();
};
typedef  function<bool(EventData*)> FN_CALLBACK;
typedef  vector<FN_CALLBACK> LIST_CALLBACK;
enum EventType {
    NONE,
    SERIAL_CMD,
    ENCODER_CLICK,
    ENCODER_ROTATE,
    TEMPERATURE_CHANGE,
    BUTTON_TRIGGER,
    SAVE_SETTINGS,
    GOTO_PAGE,
};

class Events :public BaseThread {
private:

    std::map<EventType,LIST_CALLBACK*> callbacks;
public:
    Events();
    void execute() override;
    void addListener(EventType evt, FN_CALLBACK callback);
    void dispatchMessage(EventType evt,EventData* data);
    bool available();
};
extern Events eventSystem;