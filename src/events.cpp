#include "events.h"


EventData::~EventData() {
  
}

Events::Events()
{
}

void Events::execute() {

}
void Events::addListener(const EventType event, FN_CALLBACK cb) {
    // debug_printf("add listener: %d \n",event);
    const auto it = callbacks.find(event);
    LIST_CALLBACK *lst;
    if (it == callbacks.end()) {
        lst = new LIST_CALLBACK();
        callbacks[event] = lst;
    } else {
        lst = it->second;
    }
    lst->push_back(cb);
}

void Events::dispatchMessage(EventType event,EventData *data) {
    // debug_printf("dispatch message: %d \n",event);
    if (const auto it = callbacks.find(event); it != callbacks.end()) {
        const auto lst = it->second;
        int n=lst->size();
        for (int i = 0; i < n; i++) {
            FN_CALLBACK fn = lst->at(i);
            if (fn(data)) break;
        }
    }
}
