#ifndef IDD_PREFERENCE_BOX_H
#define IDD_PREFERENCE_BOX_H

#include <QDialog>

namespace Ui {
class IDD_PREFERENCE_BOX;
}

class IDD_PREFERENCE_BOX : public QDialog
{
    Q_OBJECT

public:
    explicit IDD_PREFERENCE_BOX(QWidget *parent = nullptr);
    ~IDD_PREFERENCE_BOX();
private:
    Ui::IDD_PREFERENCE_BOX *ui;

    void init_IDD_PREFERENCE_BAR_BOX();
    void itemSelectionChanged();
    void loadSupportLanuages();
    void comboIndexChanged(int index);
    void CheckBoxStateChanged(int state);
    void RadioBtnClick();

private slots:
    //接收语言变更通知后，更新UI界面
    void  LanguageChanged();
};

#endif // IDD_PREFERENCE_BOX_H
