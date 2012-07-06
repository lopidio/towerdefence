#include <SFML/Graphics.hpp>
#include <iostream>
#include "machine/GameMachine.h"

using namespace sf;

int main()
{
        machine::GameMachine::GetInstance()->run();
        delete machine::GameMachine::GetInstance();

        return 0;
}
