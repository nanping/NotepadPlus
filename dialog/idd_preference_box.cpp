#include "idd_preference_box.h"
#include "ui_idd_preference_box.h"
#include "parameters.h"
#include "tools.h"
#include <QFileInfo>
#include <QDir>

static Parameters *pParameter=Parameters::getInstancePtr();

IDD_PREFERENCE_BOX::IDD_PREFERENCE_BOX(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IDD_PREFERENCE_BOX)
{
    ui->setupUi(this);
    ui->IDD_PREFERENCE_BAR_BOX->setLayout(ui->IDD_PREFERENCE_BAR_BOX_layout);
    ui->IDD_PREFERENCE_MARGEIN_BOX->setLayout(ui->IDD_PREFERENCE_MARGEIN_BOX_layout);
    ui->IDC_LIST_DLGTITLE->addItems({"General","Editing","New Document","Default Directory","Recent Files History",
                                     "File Association","Language","Highlighting","Print","Backup","Auto-Completion",
                                     "Multi-Instance","Delimiter","Cloud","Search Engine","MISC."});
    ui->IDC_LIST_DLGTITLE->setCurrentRow(0);
    LanguageChanged();

    init_IDD_PREFERENCE_BAR_BOX();
    connect(ui->IDC_LIST_DLGTITLE,&QListWidget::itemSelectionChanged,this,&IDD_PREFERENCE_BOX::itemSelectionChanged);
    connect(pParameter,&Parameters::LanguageChanged,this,&IDD_PREFERENCE_BOX::LanguageChanged);
}

IDD_PREFERENCE_BOX::~IDD_PREFERENCE_BOX()
{
    delete ui;
}

void IDD_PREFERENCE_BOX::init_IDD_PREFERENCE_BAR_BOX()
{
    loadSupportLanuages();

    QString v;
    auto pConfig=pParameter->getConfigPtr();
    ui->IDC_CHECK_HIDE->setChecked(!pConfig->equalToolBar_visible("yes"));
    v=pConfig->getToolBarValue("standard");
    if(v.compare("small",Qt::CaseInsensitive)==0)
    {
        ui->IDC_RADIO_SMALLICON->setChecked(true);
    }
    else if(v.compare("large",Qt::CaseInsensitive)==0)
    {
        ui->IDC_RADIO_BIGICON->setChecked(true);
    }
    else {
        ui->IDC_RADIO_STANDARD->setChecked(true);
    }
    ui->IDC_CHECK_SHOWSTATUSBAR->setChecked(pConfig->equalStatusBarValue("show"));
    ui->IDC_CHECK_TAB_HIDE->setChecked(pConfig->equalTabBar_hide("yes"));
    ui->IDC_CHECK_TAB_MULTILINE->setChecked(pConfig->equalTabBar_multiLine("yes"));
    ui->IDC_CHECK_TAB_VERTICAL->setChecked(pConfig->equalTabBar_vertical("yes"));
    ui->IDC_CHECK_REDUCE->setChecked(pConfig->equalTabBar_reduce("yes"));
    ui->IDC_CHECK_DBCLICK2CLOSE->setChecked(pConfig->equalTabBar_doubleClick2Close("yes"));
    ui->IDC_CHECK_LOCK->setChecked(pConfig->equalTabBar_drawTopBar("yes"));
    ui->IDC_CHECK_ORANGE->setChecked(pConfig->equalTabBar_dragAndDrop("yes"));
    ui->IDC_CHECK_DRAWINACTIVE->setChecked(pConfig->equalTabBar_drawInactiveTab("yes"));
    ui->IDC_CHECK_ENABLETABCLOSE->setChecked(pConfig->equalTabBar_closeButton("yes"));
    ui->IDC_CHECK_TAB_LAST_EXIT->setChecked(pConfig->equalTabBar_quitOnEmpty("yes"));
    ui->IDC_CHECK_HIDEMENUBAR->setChecked(pConfig->equalMenuBarValue("yes"));

    connect(ui->IDC_COMBO_LOCALIZATION,QOverload<int>::of(&QComboBox::currentIndexChanged),this,&IDD_PREFERENCE_BOX::comboIndexChanged);
    connect(ui->IDC_CHECK_HIDE,&QCheckBox::stateChanged,this,&IDD_PREFERENCE_BOX::CheckBoxStateChanged);
    connect(ui->IDC_RADIO_SMALLICON,&QRadioButton::released,this,&IDD_PREFERENCE_BOX::RadioBtnClick);
    connect(ui->IDC_RADIO_BIGICON,&QRadioButton::released,this,&IDD_PREFERENCE_BOX::RadioBtnClick);
    connect(ui->IDC_RADIO_STANDARD,&QRadioButton::released,this,&IDD_PREFERENCE_BOX::RadioBtnClick);

    connect(ui->IDC_CHECK_SHOWSTATUSBAR,&QCheckBox::stateChanged,this,&IDD_PREFERENCE_BOX::CheckBoxStateChanged);
    connect(ui->IDC_CHECK_TAB_HIDE,&QCheckBox::stateChanged,this,&IDD_PREFERENCE_BOX::CheckBoxStateChanged);
    connect(ui->IDC_CHECK_TAB_MULTILINE,&QCheckBox::stateChanged,this,&IDD_PREFERENCE_BOX::CheckBoxStateChanged);
    connect(ui->IDC_CHECK_TAB_VERTICAL,&QCheckBox::stateChanged,this,&IDD_PREFERENCE_BOX::CheckBoxStateChanged);
    connect(ui->IDC_CHECK_REDUCE,&QCheckBox::stateChanged,this,&IDD_PREFERENCE_BOX::CheckBoxStateChanged);
    connect(ui->IDC_CHECK_DBCLICK2CLOSE,&QCheckBox::stateChanged,this,&IDD_PREFERENCE_BOX::CheckBoxStateChanged);
    connect(ui->IDC_CHECK_LOCK,&QCheckBox::stateChanged,this,&IDD_PREFERENCE_BOX::CheckBoxStateChanged);
    connect(ui->IDC_CHECK_ORANGE,&QCheckBox::stateChanged,this,&IDD_PREFERENCE_BOX::CheckBoxStateChanged);
    connect(ui->IDC_CHECK_DRAWINACTIVE,&QCheckBox::stateChanged,this,&IDD_PREFERENCE_BOX::CheckBoxStateChanged);
    connect(ui->IDC_CHECK_ENABLETABCLOSE,&QCheckBox::stateChanged,this,&IDD_PREFERENCE_BOX::CheckBoxStateChanged);
    connect(ui->IDC_CHECK_TAB_LAST_EXIT,&QCheckBox::stateChanged,this,&IDD_PREFERENCE_BOX::CheckBoxStateChanged);
    connect(ui->IDC_CHECK_HIDEMENUBAR,&QCheckBox::stateChanged,this,&IDD_PREFERENCE_BOX::CheckBoxStateChanged);
}

void IDD_PREFERENCE_BOX::itemSelectionChanged()
{
    auto row=ui->IDC_LIST_DLGTITLE->currentRow();
    if(row<0) return;
    ui->stackedWidget->setCurrentIndex(row);
}

void IDD_PREFERENCE_BOX::loadSupportLanuages()
{
    UILanguage *pLan=UILanguage::getInstancePtr();
    QFileInfo fInfo(pLan->getFileName());
    ui->IDC_COMBO_LOCALIZATION->clear();
    auto types=pLan->getLanTypes();
    auto keys=types.keys();
    auto pConfig=pParameter->getConfigPtr();
    auto lanType=pConfig->getLanType();
    for(int i=0,size=keys.size();i<size;i++)
    {
        auto fileName=pathCombine({fInfo.path(),types[keys[i]]});
        if(fileExists(fileName)) {
            ui->IDC_COMBO_LOCALIZATION->addItem(keys[i]);
            if(lanType.compare(keys[i],Qt::CaseInsensitive)==0) {
                ui->IDC_COMBO_LOCALIZATION->setCurrentIndex(ui->IDC_COMBO_LOCALIZATION->count()-1);
            }
        }
    }
}

void IDD_PREFERENCE_BOX::comboIndexChanged(int index)
{
    QComboBox *cmb=qobject_cast<QComboBox*>(sender());
    if(cmb->objectName().compare("IDC_COMBO_LOCALIZATION",Qt::CaseInsensitive)==0)
    {
        auto s=cmb->itemText(index);
        auto pConfig=pParameter->getConfigPtr();
        pConfig->setlanguageValue(s);
        pParameter->changeLanguage(s);
    }
}

void IDD_PREFERENCE_BOX::CheckBoxStateChanged(int /*state*/)
{
    bool fg;
    QCheckBox *chk=qobject_cast<QCheckBox *>(sender());
    QString objName=chk->objectName();
    if(objName.compare("IDC_CHECK_HIDE",Qt::CaseInsensitive)==0)
    {
        fg=chk->isChecked();
        auto pConfig=pParameter->getConfigPtr();
        pConfig->setToolBar_visible(!fg ? "yes":"no",MSG_TOOLBAR_CHANGE,&fg);
    }
}

void IDD_PREFERENCE_BOX::RadioBtnClick()
{
    QRadioButton *btn=qobject_cast<QRadioButton *>(sender());
    QString objName=btn->objectName();
    if(objName.compare("IDC_RADIO_SMALLICON",Qt::CaseInsensitive)==0 ||
       objName.compare("IDC_RADIO_BIGICON",Qt::CaseInsensitive)==0 ||
       objName.compare("IDC_RADIO_STANDARD",Qt::CaseInsensitive)==0)
    {
        auto pConfig=pParameter->getConfigPtr();
        pConfig->setToolBarValue(ui->IDC_RADIO_SMALLICON->isChecked() ? "small":(ui->IDC_RADIO_BIGICON->isChecked() ? "large":"standard"));
    }
}

void IDD_PREFERENCE_BOX::LanguageChanged()
{
    UILanguage *pLan=UILanguage::getInstancePtr();
    QString objName,v,fx,
            parentName=this->objectName();
    setWindowTitle(pLan->getDialogAttr(parentName,"title"));
    v=pLan->getDialogAttr(QString("%1/Item[@id='IDC_BUTTON_CLOSE']").arg(parentName),"name");
    if(!v.isEmpty()) ui->IDC_BUTTON_CLOSE->setText(v);
    for(int i=0,size=ui->stackedWidget->count();i<size;i++)
    {
        auto parent=ui->stackedWidget->widget(i);
        objName=parent->objectName();
        fx=QString("%1/%2").arg(parentName).arg(objName);
        v=pLan->getDialogAttr(fx,"title");
        if(!v.isEmpty()) ui->IDC_LIST_DLGTITLE->item(i)->setText(v);

        auto lst=parent->findChildren<QWidget *>(QString(),Qt::FindChildrenRecursively);
        for(int j=0,jsize=lst.count();j<jsize;j++)
        {
            if(lst[j]->inherits("QCheckBox") || lst[j]->inherits("QRadioButton") || lst[j]->inherits("QPushButton") ||
                    lst[j]->inherits("QLabel") || lst[j]->inherits("QGroupBox"))
            {
                v=pLan->getDialogAttr(QString("%1/Item[@id='%2']").arg(fx).arg(lst[j]->objectName()),"name");
                if(v.isEmpty()) continue;
                if(lst[j]->inherits("QCheckBox"))
                {
                    static_cast<QCheckBox *>(lst[j])->setText(v);
                }
                else if(lst[j]->inherits("QRadioButton"))
                {
                    static_cast<QRadioButton *>(lst[j])->setText(v);
                }
                else if(lst[j]->inherits("QPushButton"))
                {
                    static_cast<QPushButton *>(lst[j])->setText(v);
                }
                else if(lst[j]->inherits("QLabel"))
                {
                    static_cast<QLabel *>(lst[j])->setText(v);
                }
                else if(lst[j]->inherits("QGroupBox"))
                {
                    static_cast<QGroupBox *>(lst[j])->setTitle(v);
                }
            }
        }

    }
}
