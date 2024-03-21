#include "filemovedemo.h"
#include "./ui_filemovedemo.h"

#include <QButtonGroup>
#include <QTextEdit>
#include <QtWidgets/QSpacerItem>
#include <QFileDialog>

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
    qDebug() << !args->tempWidget;
    if (!args->tempWidget)
    {
        args->tempWidget = new QWidget(ui->widget);
        if(!args->tempWidget)
        {
            return;
        }
        ui->horizontalLayout_2->addWidget(args->tempWidget);

        
        #if 0
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
        #endif 
        QVBoxLayout* mainLayout = new QVBoxLayout(args->tempWidget);
        args->tempWidget->setLayout(mainLayout);
        mainLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding));     // 添加纵向弹簧
        QHBoxLayout* HLayout_ButtonName = new QHBoxLayout();
        QLabel* lablel_ButtonName = new QLabel(args->tempWidget);
        lablel_ButtonName->setText("按钮名称");
        lablel_ButtonName->setMinimumSize(80,20);
        QTextEdit* Edit__ButtonName = new QTextEdit(args->tempWidget);
        HLayout_ButtonName->addWidget(lablel_ButtonName);
        HLayout_ButtonName->addWidget(Edit__ButtonName);
        mainLayout->addLayout(HLayout_ButtonName);

        // 路径选择
        QHBoxLayout* HLayout_ToPath = new QHBoxLayout();
        QLabel* lablel_ToPath = new QLabel(args->tempWidget);
        lablel_ToPath->setText("目标路径");
        lablel_ToPath->setMinimumSize(80, 20);
        QTextEdit* Edit__ToPath = new QTextEdit(args->tempWidget);
        QPushButton* button_ToPath = new QPushButton(args->tempWidget);
        button_ToPath->setText("...");
        HLayout_ToPath->addWidget(lablel_ToPath);
        HLayout_ToPath->addWidget(Edit__ToPath);
        HLayout_ToPath->addWidget(button_ToPath);
        mainLayout->addLayout(HLayout_ToPath);
        connect(button_ToPath, &QPushButton::clicked,[=]()
        {
            QString dirPath = QFileDialog::getExistingDirectory(this, "Select Directory", "./");
            Edit__ToPath->setText(dirPath);
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


    }
    else
    {        args->tempWidget->setVisible(isWidgetVisible);
    }
}
