#ifndef RANKINFO_H
#define RANKINFO_H

#include <QString>

struct RankInfo{
    QString date;
    QString time;
    QString point;
    QString passTime;
    RankInfo() = default;
    RankInfo(const QString& date, const QString& time, const QString& point, const QString& passTime)
        :date(date),time(time),point(point),passTime(passTime){}
};

#endif // RANKINFO_H
