#ifndef MUSICCONFIG_H
#define MUSICCONFIG_H

#include <QDialog>
#include <QSlider>
#include <QPushButton>

namespace Ui {
class MusicConfig;
}

class MusicConfig : public QDialog
{
    Q_OBJECT

public:
    explicit MusicConfig(int bgMusicVolume,int jumpMusicVolume,int launchMusicVlume,
                         int successMusicVolume, int gameOverMusicVolume, QWidget *parent = nullptr);
    ~MusicConfig();
    QSlider* getBGMusicSlider() const;
    QSlider* getJumpMusicSlider() const;
    QSlider* getLaunchMusicSlider() const;
    QSlider* getSuccessMusicSlider() const;
    QSlider* getGameOverMusicSlider() const;
    QPushButton* getJumpMusicButton() const;
    QPushButton* getLaunchMusicButton() const;
    QPushButton* getSuccessMusicButton() const;
    QPushButton* getGameOverMusicButton() const;

private:
    Ui::MusicConfig *ui;
};

#endif // MUSICCONFIG_H
