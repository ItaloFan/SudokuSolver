#include "keymap.h"

KeyMap::KeyMap()
{
}

bool KeyMap::up(char key)
{
    if (key == 0x77 || key == 0x6B)
    {
        return true;
    }
    return false;
}

bool KeyMap::left(char key)
{
    if (key == 0x61 || key == 0x68)
    {
        return true;
    }
    return false;
}

bool KeyMap::down(char key)
{
    if (key == 0x73 || key == 0x6A)
    {
        return true;
    }
    return false;
}
bool KeyMap::right(char key)
{
    if (key == 0x64 || key == 0x6C)
    {
        return true;
    }
    return false;
}
bool KeyMap::quit(char key)
{
    if (key == 0x1B || key == 0x51 || key == 0x71)
    {
        return true;
    }
    return false;
}
bool KeyMap::reset(char key)
{
    if (key == 0x52 || key == 0x72)
    {
        return true;
    }
    return false;
}

bool KeyMap::confirm(char key)
{
    if (key == 0x0D)
    {
        return true;
    }
    return false;
}
