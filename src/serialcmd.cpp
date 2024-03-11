#include "serialcmd.h"

SerialCmd::SerialCmd() : BaseThread()
{
    cmdCount = 0;
    act = NULL;
};
void SerialCmd::processCommand()
{
    if ((cmdCount > 0) && (act == NULL))
    {
        cmdCount--;
        char buf[22];
        int p = 0;
        bool done = false;
        while (!done)
        {
            char c = data.front();
            data.pop();
            if ((c != 0xA) && (c != 0xD) && (p < 20))
            {
                buf[p++] = c;
                buf[p] = '\0';
            }

            done = c == 0xD;
        }
        std::string s(buf);
        if (p > 0)
        {

            // Serial.print(p);
            act = new CommandAction(s);
        }

        // Serial.print("full command: ");
        Serial.println(buf);
    }
}
void SerialCmd::readSerial()
{
    if (Serial.available() > 0)
    {
        char incomingByte = Serial.read();
        Serial.print(incomingByte);
        data.push(incomingByte);
        if (incomingByte == 0xD)
        {
            cmdCount++;
        }
    }
}
void SerialCmd::handleTask()
{

    if (act != NULL)
    {
        // Serial.println("create command");
        act->execute();
        if (act->isFinished())
        {

            delete this->act;
            act = NULL;
        }
    }
}
void SerialCmd::execute()
{
    // Serial.println("Looop =================");
    TBT_THC(3, ,
            readSerial(),
            processCommand(),
            handleTask(),

    )
}