#include "hpreducer.h"

HPReducer::HPReducer(int HPReduce) : _HPReduce(HPReduce)
{}

int HPReducer::getHPReduce() const
{
    return _HPReduce;
}
