#include "musicmanager.h"

MusicManager::MusicManager(QObject *parent)
    : QObject(parent),bgMusicPlayList(this),bgMusic(this),jumpMusic(this),launchMusic(this),muted(false)
{
    bgMusicPlayList.addMedia(QUrl("qrc:/bgm/bgm/dango.mp3"));
    bgMusicPlayList.setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    bgMusic.setPlaylist(&bgMusicPlayList);
    bgMusic.setVolume(20);

    jumpMusic.setMedia(QUrl("qrc:/bgm/bgm/jump.mp3"));
    jumpMusic.setVolume(10);

    launchMusic.setMedia(QUrl("qrc:/bgm/bgm/magicBullet.mp3"));
    launchMusic.setVolume(20);

    successMusic.setMedia(QUrl("qrc:/bgm/bgm/success.mp3"));
    successMusic.setVolume(20);

    gameOverMusic.setMedia(QUrl("qrc:/bgm/bgm/gameOver.mp3"));
    gameOverMusic.setVolume(20);
}

void MusicManager::playBGMusic()
{
    if(!muted){
        bgMusic.play();
    }
}

void MusicManager::stopBGMusic()
{
    bgMusic.stop();
}

void MusicManager::setBGMusicVolume(int volume)
{
    if(volume>=0&&volume<=100){
        bgMusic.setVolume(volume);
    }
}

int MusicManager::getBGMusicVolume() const
{
    return bgMusic.volume();
}

void MusicManager::playJumpMusic()
{
    if(!muted){
        jumpMusic.play();
    }
}

void MusicManager::stopJumpMusic()
{
    jumpMusic.stop();
}

void MusicManager::setJumpMusicVolume(int volume)
{
    if(volume>=0&&volume<=100){
        jumpMusic.setVolume(volume);
    }
}

void MusicManager::testJumpMusic()
{
    jumpMusic.play();
}

int MusicManager::getJumpMusicVolume() const
{
    return jumpMusic.volume();
}

void MusicManager::playLaunchMusic()
{
    if(!muted){
        launchMusic.play();
    }
}

void MusicManager::stopLaunchMusic()
{
    launchMusic.stop();
}

void MusicManager::setLaunchMusicVolume(int volume)
{
    if(volume>=0&&volume<=100){
        launchMusic.setVolume(volume);
    }
}

void MusicManager::testLaunchMusic()
{
    launchMusic.play();
}

int MusicManager::getLaunchMusicVolume() const
{
    return launchMusic.volume();
}

void MusicManager::playSuccessMusic()
{
    if(!muted){
        successMusic.play();
    }
}

void MusicManager::stopSuccessMusic()
{
    successMusic.stop();
}

void MusicManager::setSuccessMusicVolume(int volume)
{
    if(volume>=0&&volume<=100){
        successMusic.setVolume(volume);
    }
}

void MusicManager::testSuccessMusic()
{
    successMusic.play();
}

int MusicManager::getSuccessMusicVolume() const
{
    return successMusic.volume();
}

void MusicManager::playGameOverMusic()
{
    if(!muted){
        gameOverMusic.play();
    }
}

void MusicManager::stopGameOverMusic()
{
    gameOverMusic.stop();
}

void MusicManager::setGameOverMusicVolume(int volume)
{
    if(volume>=0&&volume<=100){
        gameOverMusic.setVolume(volume);
    }
}

void MusicManager::testGameOverMusic()
{
    gameOverMusic.play();
}

int MusicManager::getGameOverMusicVolume() const
{
    return gameOverMusic.volume();
}

void MusicManager::setMuted(bool muted)
{
    this->muted = muted;
    if(muted){
        bgMusic.stop();
        jumpMusic.stop();
        launchMusic.stop();
    }else{
        bgMusic.play();
    }
}
