#ifndef MUSICMANAGER_H
#define MUSICMANAGER_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

class MusicManager : public QObject {
    Q_OBJECT

public:

    MusicManager(QObject *parent = nullptr);

public slots:

    void playBGMusic();
    void stopBGMusic();
    void setBGMusicVolume(int volume);
    int  getBGMusicVolume() const;

    void playJumpMusic();
    void stopJumpMusic();
    void setJumpMusicVolume(int volume);
    void testJumpMusic();
    int  getJumpMusicVolume() const;

    void playLaunchMusic();
    void stopLaunchMusic();
    void setLaunchMusicVolume(int volume);
    void testLaunchMusic();
    int  getLaunchMusicVolume() const;

    void playSuccessMusic();
    void stopSuccessMusic();
    void setSuccessMusicVolume(int volume);
    void testSuccessMusic();
    int  getSuccessMusicVolume() const;

    void playGameOverMusic();
    void stopGameOverMusic();
    void setGameOverMusicVolume(int volume);
    void testGameOverMusic();
    int  getGameOverMusicVolume() const;

    void setMuted(bool muted);

protected:

    QMediaPlaylist bgMusicPlayList;
    QMediaPlayer bgMusic;
    QMediaPlayer jumpMusic;
    QMediaPlayer launchMusic;
    QMediaPlayer successMusic;
    QMediaPlayer gameOverMusic;
    bool muted;
};

#endif // MUSICMANAGER_H
