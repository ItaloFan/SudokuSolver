#ifndef KEYMAP_H
#define KEYMAP_H

class KeyMap
{
public:
    KeyMap();
    bool up(char key);
    bool down(char key);
    bool left(char key);
    bool right(char key);
    bool quit(char key);
    bool reset(char key);
    bool confirm(char key);
};

#endif