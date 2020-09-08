#ifndef HPREDUCER_H
#define HPREDUCER_H


class HPReducer
{
public:
    HPReducer(int HPReduce = 1);
    int getHPReduce() const;

protected:
    int HPReduce;
};

#endif // HPREDUCER_H
