#ifndef RANKINFO_H
#define RANKINFO_H

#include <QString>
#include <QTime>

struct RankInfo{
    QString date;
    QString time;
    QString point;
    QString passTime;
    RankInfo() = default;
    RankInfo(const QString& date, const QString& time, const QString& point, const QString& passTime)
        :date(date),time(time),point(point),passTime(passTime){}
};

struct RankInfoCmp{
    bool operator()(const RankInfo& rankinfo1, const RankInfo& rankinfo2){
        int point1 = rankinfo1.point.toInt();
        int point2 = rankinfo2.point.toInt();
        int passTime1 = QTime::fromString(rankinfo1.passTime,"hh:mm:ss").hour()*3600 + QTime::fromString(rankinfo1.passTime,"hh:mm:ss").minute()*60+QTime::fromString(rankinfo1.passTime,"hh:mm:ss").second();
        int passTime2 = QTime::fromString(rankinfo2.passTime,"hh:mm:ss").hour()*3600 + QTime::fromString(rankinfo2.passTime,"hh:mm:ss").minute()*60+QTime::fromString(rankinfo2.passTime,"hh:mm:ss").second();
        return !(point1<point2||(point1==point2&&passTime1>passTime2));
    }
};

#endif // RANKINFO_H
