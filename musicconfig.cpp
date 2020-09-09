#include "musicconfig.h"
#include "ui_musicconfig.h"

MusicConfig::MusicConfig(int bgMusicVolume, int jumpMusicVolume, int launchMusicVolume,int successMusicVolume, int gameOverMusicVolume, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MusicConfig)
{
    ui->setupUi(this);
    ui->pushButton->setFlat(true);
    ui->pushButton->setEnabled(false);
    QIcon icon(QPixmap::fromImage(QImage(":/icons/icon/play.png")));
    ui->jumpMusicButton->setFlat(true);
    ui->jumpMusicButton->setIcon(icon);
    ui->launchMusicButton->setFlat(true);
    ui->launchMusicButton->setIcon(icon);
    ui->successMusicButton->setFlat(true);
    ui->successMusicButton->setIcon(icon);
    ui->gameOverMusicButton->setFlat(true);
    ui->gameOverMusicButton->setIcon(icon);

    ui->bgMusicSlider->setMinimum(0);
    ui->bgMusicSlider->setMaximum(100);
    ui->bgMusicSlider->setValue(bgMusicVolume);
    ui->bgMusicSlider->setSingleStep(5);

    ui->jumpMusicSlider->setMinimum(0);
    ui->jumpMusicSlider->setMaximum(100);
    ui->jumpMusicSlider->setValue(jumpMusicVolume);
    ui->jumpMusicSlider->setSingleStep(5);

    ui->launchMusicSlider->setMinimum(0);
    ui->launchMusicSlider->setMaximum(100);
    ui->launchMusicSlider->setValue(launchMusicVolume);
    ui->launchMusicSlider->setSingleStep(5);

    ui->successMusicSlider->setMinimum(0);
    ui->successMusicSlider->setMaximum(100);
    ui->successMusicSlider->setValue(successMusicVolume);
    ui->successMusicSlider->setSingleStep(5);

    ui->gameOverMusicSlider->setMinimum(0);
    ui->gameOverMusicSlider->setMaximum(100);
    ui->gameOverMusicSlider->setValue(gameOverMusicVolume);
    ui->gameOverMusicSlider->setSingleStep(5);
}

MusicConfig::~MusicConfig()
{
    delete ui;
}

QSlider *MusicConfig::getBGMusicSlider() const
{
    return ui->bgMusicSlider;
}

QSlider *MusicConfig::getJumpMusicSlider() const
{
    return ui->jumpMusicSlider;
}

QSlider *MusicConfig::getLaunchMusicSlider() const
{
    return ui->launchMusicSlider;
}

QSlider *MusicConfig::getSuccessMusicSlider() const
{
    return ui->successMusicSlider;
}

QSlider *MusicConfig::getGameOverMusicSlider() const
{
    return ui->gameOverMusicSlider;
}

QPushButton *MusicConfig::getJumpMusicButton() const
{
    return ui->jumpMusicButton;
}

QPushButton *MusicConfig::getLaunchMusicButton() const
{
    return ui->launchMusicButton;
}

QPushButton *MusicConfig::getSuccessMusicButton() const
{
    return ui->successMusicButton;
}

QPushButton *MusicConfig::getGameOverMusicButton() const
{
    return ui->gameOverMusicButton;
}
