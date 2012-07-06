#ifndef GAMESTATE_H
#define GAMESTATE_H

namespace machine
{
        class GameState
        {
                public:
                        GameState();
                        virtual ~GameState();
                        virtual void init();
                        virtual void load();
                        virtual void unload();
                        virtual void update() = 0;
                        virtual void draw() const = 0;
                protected:
                private:
                        //backgroung imagem
                        //métodos sobrecarregáveis
        };
}
#endif // GAMESTATE_H
