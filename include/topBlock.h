#ifndef TOPBLOCK_H
#define TOPBLOCK_H

#include <block.h>


class top_block : public block
{
    public:
        double downwardPushForce;



        top_block();
        ~top_block();

        void calculateForces();

    protected:

    private:
};

#endif // TOPBLOCK_H
