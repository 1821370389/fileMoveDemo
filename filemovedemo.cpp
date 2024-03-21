#include "filemovedemo.h"
#include "./ui_filemovedemo.h"

#include <QButtonGroup>

struct fileMoveDemoArgs
{
    QButtonGroup* buttonGroup;
    QHBoxLayout* layout_ButtonGroup;
    QWidget* tempWidget;
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
    delete ui;
    delete args->buttonGroup;
    delete args->tempWidget;
    delete args;
}


void fileMoveDemo::addPathButton()
{
    // 切换显示状态
    bool isWidgetVisible = ui->widget->isVisible();
    ui->widget->setVisible(!isWidgetVisible);

    // 如果临时窗口不存在，则创建临时窗口
    if (!args->tempWidget)
    {
        args->tempWidget = new QWidget(ui->widget);
        ui->horizontalLayout_2->addWidget(args->tempWidget);

        

        // 创建按钮
        QPushButton* backButton = new QPushButton("Back", args->tempWidget);
        connect(backButton, &QPushButton::clicked, this, [=]() {
            ui->widget->setVisible(true);
            args->tempWidget->setVisible(false);
        });

        // 设置布局
        QVBoxLayout* layout = new QVBoxLayout(args->tempWidget);
        layout->addWidget(new QLabel("This is a temporary window.", args->tempWidget));
        layout->addWidget(backButton);

        args->tempWidget->setLayout(layout);
    }
    
    args->tempWidget->setVisible(isWidgetVisible);
}
