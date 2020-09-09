#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

class MusicManager: public QObject
{
    Q_OBJECT
public:
    MusicManager(QObject* parent=nullptr);

public slots:
    void playBGMusic();
    void stopBGMusic();
    void setBGMusic(int volume);

    void playJumpMusic();
    void stopJumpMusic();
    void setJumpMusic(int volume);

    void playLaunchMusic();
    void stopLaunchMusic();
    void setLaunchMusic(int volume);

protected:
    QMediaPlaylist bgMusicPlayList;
    QMediaPlayer bgMusic;
    QMediaPlayer jumpMusic;
    QMediaPlayer launchMusic;
};

#endif // MUSICMANAGER_H
