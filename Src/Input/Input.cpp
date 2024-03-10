#include "Input.h"

int ReadInput()
{
    int c = 0;
    while (1)
    {
        c = 0;

        switch ((c = _getch())) {
        case KEY_VALUE::UP:
            std::cout << "UP" << std::endl;
            return KEY_VALUE::UP;
            break;
        case KEY_VALUE::DOWN:
            std::cout << "DOWN" << std::endl;
            return KEY_VALUE::DOWN;
            break;
        case KEY_VALUE::LEFT:
            std::cout << "LEFT" << std::endl;
            return KEY_VALUE::LEFT;
            break;
        case KEY_VALUE::RIGHT:
            std::cout << "RIGHT" << std::endl;
            return KEY_VALUE::RIGHT;
            break;
        default:
            
            break;
        }

    }
	return 0;
}
