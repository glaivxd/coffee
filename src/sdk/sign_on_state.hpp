#pragma once

enum class SignOnState
{
    NONE = 0,
    CHALLENGE = 1,
    CONNECTED = 2,
    NEW = 3,
    PRESPAWN = 4,
    SPAWN = 5,
    FULL = 6,
    CHANGELEVEL = 7,
};