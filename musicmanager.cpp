#include "musicmanager.h"

MusicManager::MusicManager(QObject *parent): QObject(parent),bgMusicPlayList(this),bgMusic(this),jumpMusic(this),launcherMusic(this)
{
    bgMusicPlayList.addMedia(QUrl("qrc:/bgm/bgm/dango.mp3"));
    bgMusicPlayList.setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    bgMusic.setPlaylist(&bgMusicPlayList);
    bgMusic.setVolume(20);
}

void MusicManager::playBGMusic()
{
    bgMusic.play();
}

void MusicManager::stopBGMusic()
{
    bgMusic.stop();
}

void MusicManager::setBGMusic(int volume)
{
    if(volume>=0&&volume<=100){
        bgMusic.setVolume(volume);
    }
}

void MusicManager::playJumpMusic()
{
    jumpMusic.play();
}

void MusicManager::stopJumpMusic()
{
    jumpMusic.stop();
}

void MusicManager::setJumpMusic(int volume)
{
    if(volume>=0&&volume<=100){
        jumpMusic.setVolume(volume);
    }
}

void MusicManager::playLauncherMusic()
{
    launcherMusic.play();
}

void MusicManager::stioLauncherMusic()
{
    launcherMusic.stop();
}

void MusicManager::setLauncherMusic(int volume)
{
    if(volume>=0&&volume<=100){
        launcherMusic.setVolume(volume);
    }
}
