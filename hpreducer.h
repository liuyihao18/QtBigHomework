#ifndef HPREDUCER_H
#define HPREDUCER_H


class HPReducer {
public:

    HPReducer(int _HPReduce = 1);
    int getHPReduce() const;

protected:

    int _HPReduce;
};

#endif // HPREDUCER_H
