#include "filemovedemo.h"
#include "./ui_filemovedemo.h"

#include <QButtonGroup>
#include <QTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QFileDialog>

struct fileMoveDemoArgs
{
    QButtonGroup* buttonGroup = nullptr;
    QHBoxLayout* layout_ButtonGroup = nullptr;
    QWidget* tempWidget = nullptr;
};

fileMoveDemo::fileMoveDemo(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::fileMoveDemo), args(new fileMoveDemoArgs)
{
    ui->setupUi(this);
    this->setWindowTitle("File Move Demo");

    
    args->buttonGroup = new QButtonGroup(this);
    args->layout_ButtonGroup = new QHBoxLayout(ui->Widget_ButtonGroup);
    connect(ui->action1, &QAction::triggered, this, &fileMoveDemo::addPathButton);
}

fileMoveDemo::~fileMoveDemo()
{
    qDebug() << ui->centralwidget->isAncestorOf(args->tempWidget);
    delete ui;
    delete args;
}


void fileMoveDemo::addPathButton()
{
    // 切换显示状态
    bool isWidgetVisible = ui->widget->isVisible();
    if (isWidgetVisible) ui->widget->setVisible(false);
    else return;

    // 如果临时窗口不存在，则创建临时窗口
    qDebug() << &args->tempWidget;
    
    qDebug() << "tempWidget:" <<args->tempWidget;
    qDebug() << "isAncestorOf:" << ui->centralwidget->isAncestorOf(args->tempWidget);
    // 清除旧的临时窗口
    if (args->tempWidget) {
        delete args->tempWidget;
        args->tempWidget = nullptr; // 设置为 nullptr 防止野指针
    }

    args->tempWidget = new QWidget(ui->centralwidget);
    if (!args->tempWidget)
    {
        return;
    }

    ui->horizontalLayout_2->addWidget(args->tempWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(args->tempWidget);
    args->tempWidget->setLayout(mainLayout);
    mainLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding));     // 添加纵向弹簧
    QHBoxLayout* HLayout_ButtonName = new QHBoxLayout();
    QLabel* lablel_ButtonName = new QLabel(args->tempWidget);
    lablel_ButtonName->setText("按钮名称");
    lablel_ButtonName->setMinimumSize(80,20);
    QTextEdit* Edit_ButtonName = new QTextEdit(args->tempWidget);
    HLayout_ButtonName->addWidget(lablel_ButtonName);
    HLayout_ButtonName->addWidget(Edit_ButtonName);
    mainLayout->addLayout(HLayout_ButtonName);

    // 路径选择
    QHBoxLayout* HLayout_ToPath = new QHBoxLayout();
    QLabel* lablel_ToPath = new QLabel(args->tempWidget);
    lablel_ToPath->setText("目标路径");
    lablel_ToPath->setMinimumSize(80, 20);
    QTextEdit* Edit_ToPath = new QTextEdit(args->tempWidget);
    QPushButton* button_ToPath = new QPushButton(args->tempWidget);
    button_ToPath->setText("...");
    HLayout_ToPath->addWidget(lablel_ToPath);
    HLayout_ToPath->addWidget(Edit_ToPath);
    HLayout_ToPath->addWidget(button_ToPath);
    mainLayout->addLayout(HLayout_ToPath);
    connect(button_ToPath, &QPushButton::clicked, [=]()
    {
        QString dirPath = QFileDialog::getExistingDirectory(this, "选择文件夹", "./");
        Edit_ToPath->setText(dirPath);
    });



    QHBoxLayout* HLayout_ButtonPath = new QHBoxLayout();
    HLayout_ButtonPath->addItem(new QSpacerItem(20, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum));
    QPushButton* BackButton = new QPushButton(args->tempWidget);
    BackButton->setText("Back");
    HLayout_ButtonPath->addWidget(BackButton);
    mainLayout->addLayout(HLayout_ButtonPath);
    connect(BackButton, &QPushButton::clicked, [=]() {
        ui->widget->setVisible(true);
        args->tempWidget->setVisible(false);
    });


    args->tempWidget->setVisible(isWidgetVisible);
    
}
