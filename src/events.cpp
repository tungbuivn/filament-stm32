#include "events.h"


EventData::~EventData() {
  
}

Events::Events()
{
}
bool Events::processCallback() {
    EventData* data=eventQueue.front();
    eventQueue.pop();
    // debug_printf("dispatch message: %d \n",eventQueue.size());
    if (const auto it = callbacks.find(data->type); it != callbacks.end()) {
        const auto lst = it->second;
        int n=lst->size();
        
        for (int i = 0; i < n; i++) {
            FN_CALLBACK fn = lst->at(i);
            if (fn(data)) break;
        }
    }
    delete data;
    return false;
}
void Events::execute() {
    TBT_THC(1,
       
        while(eventQueue.size()>0) {
            processCallback();
        }
       
    )

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
void Events::dispatchMessage(EventData *data) {
    // if (data) {
    // EventData *et=data->clone();
    eventQueue.push(data);
    // } 
    
}
void Events::dispatchMessage(EventType event,long long adata) {
    dispatchMessage(new EventData(event,adata));
    // if (data) {
        // EventData *et=new EventData();
        // eventQueue.push(et);
    // } 
    
}

// void Events::dispatchMessage(EventType event,EventData *data) {
//     if (data) {
//         // debug_printf("event post %d",eventQueue.size());
//         data->type=event;
        
//         auto cl=data->clone();
//         eventQueue.push(cl);
//     } 
    
// }
