#include "musicmanager.h"

MusicManager::MusicManager(QObject *parent): QObject(parent),bgMusicPlayList(this),bgMusic(this),jumpMusic(this),launchMusic(this)
{
    bgMusicPlayList.addMedia(QUrl("qrc:/bgm/bgm/dango.mp3"));
    bgMusicPlayList.setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    bgMusic.setPlaylist(&bgMusicPlayList);
    bgMusic.setVolume(20);

    jumpMusic.setMedia(QUrl("qrc:/bgm/bgm/jump.mp3"));
    jumpMusic.setVolume(20);

    launchMusic.setMedia(QUrl("qrc:/bgm/bgm/magicBullet.mp3"));
    jumpMusic.setVolume(20);
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

void MusicManager::playLaunchMusic()
{
    launchMusic.play();
}

void MusicManager::stopLaunchMusic()
{
    launchMusic.stop();
}

void MusicManager::setLaunchMusic(int volume)
{
    if(volume>=0&&volume<=100){
        launchMusic.setVolume(volume);
    }
}
