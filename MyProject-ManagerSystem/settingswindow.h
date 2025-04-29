#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QSpinBox>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QCheckBox>


class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = nullptr);

private:
    QComboBox *resolutionComboBox;
    QTextEdit *infoTextEdit;
    QPushButton *applyBtn;
    QVBoxLayout *mainLayout;
    QCheckBox *rememberLoginCheckBox;

signals:
    void windowSizeChanged(int width, int height);
};

#endif // SETTINGSWINDOW_H
