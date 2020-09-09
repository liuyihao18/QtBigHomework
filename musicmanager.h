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

    void playLauncherMusic();
    void stioLauncherMusic();
    void setLauncherMusic(int volume);

protected:
    QMediaPlaylist bgMusicPlayList;
    QMediaPlayer bgMusic;
    QMediaPlayer jumpMusic;
    QMediaPlayer launcherMusic;
};

#endif // MUSICMANAGER_H
