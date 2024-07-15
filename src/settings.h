#pragma once
#include "tbt_thread.h"

class Settings : public BaseThread {
public:
    Settings();
    void loadSettings();
    void execute() override;
};

// extern Settings settings;