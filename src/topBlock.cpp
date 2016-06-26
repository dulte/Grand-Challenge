#include "topBlock.h"
#include "getVar.h"

top_block::top_block()
{
    getVar *pGetVarTop = new getVar();

    downwardPushForce = pGetVarTop->get("downPushForce");

    delete pGetVarTop;
}

top_block::~top_block()
{
    type = blockType::top;
}

void top_block::calculateForces()
{
    this->InternalForces();
    yForce -= downwardPushForce;
}


