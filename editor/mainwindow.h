#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include "lcdconverter.h"

#include <QTranslator>

#define EEPROM_RESOURCE ":/res/eeprom_en.bin"

class MainWindow : public QMainWindow, private Ui::MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void updateHexTable(int pos);
    void updateHexTable();

private:
    LcdConverter *lc;
    QString fileName;
    QByteArray eep;
    QString amsr;
    QFont fontHex;

    void readEepromFile(QString name);
    void saveEepromFile(QString name);

    void saveAmsrFile(QString name);
    void fillAmsr();

    void setAudioParam(QDoubleSpinBox *spb, double min, double max, double step, int param);

    double getFreq(int pos);
    void setFreq (double value, int pos);

    int fmStepEep2Index(uint8_t value);
    uint8_t fmStepIndex2Step(uint8_t index);

    QTranslator translator;

private slots:
    void about();
    void aboutQt();

    void openEeprom();
    void saveEeprom();
    void saveEepromAs();
    void loadDefaultEeprom();
    void saveAmsr();

    void updateTranslation(int row, int column);

    void setAudioproc(int proc);
    void setVolume(double value);
    void setBass(double value);
    void setTreble(double value);
    void setBalance(double value);
    void setInput(int value);
    void setInputIcon(int value);
    void setLoudness(int value);
    void setSurround(int value);
    void setEffect3d(int value);
    void setToneDefeat(int value);

    void setTuner(int tuner);
    void setFmfreq(double value);
    void setFmMin(double value);
    void setFmMax(double value);
    void setFmstep1(int value);
    void setFmstep2(int value);
    void setFmmono(int value);
    void setFmRds(int value);
    void setFmctrl();

    void setRemote(int rcType);
    void setRemoteType(int type);
    void setRemoteAddr(int addr);
    void setRemoteCmd(int cmd);
    void setRemoteIndex(int index);
    void calcRemoteSeq();

    void setOther();
    void setSpmode(int value);
    void setSpspeed(int value);
    void setBrstby(int value);
    void setEncres(int value);
    void setExtfunc(int value);
    void setThreshold(int value);
    void setSilence(int value);

    void setLanguage();
    void retranslate(QString lang);
};

#endif // MAINWINDOW_H
