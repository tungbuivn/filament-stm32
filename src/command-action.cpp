#include "serialcmd.h"
#include "mylcd.h"

CommandAction::~CommandAction()
{
}
CommandAction::CommandAction(std::string s) : BaseThread()
{
    cmd=s;
    type = THREAD_EXECUTION::ONCE;
}
void CommandAction::execute()
{
    // Serial.println("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx");
    TBT_THC(5, 
    ,,
            // Serial.print("Execute action: ");
            // Serial.println(cmd.c_str()),
            // {
            //     char *buf = new char[cmd.size()];
            //     strcpy(buf,cmd.c_str());
            //     // mylcd.setText(0,2,buf);
            //     delete[] buf;
            // },
           
            // Serial.print("next action: "),
            // Serial.print("force action: "),
            );
}