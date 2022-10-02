#include "interface.h"
#include "ui_interface.h"
#include "fao.h"



Interface::Interface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Interface)
{
    ui->setupUi(this);
    //添加icon
    this->setWindowIcon(QIcon(":/img/logo.ico"));
    //左边工具组大小锁定
    ui->groupBox_2->setFixedSize(250, 500);
    //表格关闭编辑
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //右边表格隔行变色
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->setPalette(QPalette(Qt::lightGray));
    //左下角listwidget隔行变色
    this->ui->listWidget->setAlternatingRowColors(true);

    //初始化arkList
    this->arkList = new ArkInfo();

    loadArkList();


    //输入栏查找
    connect(ui->findLine, &QLineEdit::editingFinished, [=](){
        //如果输入栏为空跳过
        if(ui->findLine->text() != ""){
            int row = findData(ui->findLine->text());
            if(row != -1) {ui->tableWidget->verticalScrollBar()->setSliderPosition(row);}
        }
    });
    //双击表格打开
    connect(ui->tableWidget, &QTableWidget::cellDoubleClicked, [&](int row){
        QString name = ui->tableWidget->item(row, 0)->text();
        openDir(name);
    });
    //单击表格查找
    connect(ui->tableWidget, &QTableWidget::cellClicked, [&](int row){findData(ui->tableWidget->item(row, 0)->text());});


    //按钮
    connect(ui->outButton, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->deleteButton, &QPushButton::clicked, [=](){ui->textBrowser->clear();});
    connect(ui->addButton, &QPushButton::clicked, this, &Interface::addArk);
    connect(ui->reloadButton, &QPushButton::clicked, this, &Interface::loadArkList);


    //左下角listWidget
    //双击切换ark
    connect(ui->listWidget, &QListWidget::doubleClicked, [&](QModelIndex row){
        switchArk(ui->listWidget->item(row.row())->text());
    });
    //单击显示ark信息
    connect(ui->listWidget, &QListWidget::clicked, [&](QModelIndex row){
        printArkInfo(ui->listWidget->item(row.row())->text());
    });

}

//遍历entitys来填充右边的表格
void Interface::showTable(){
    QStringList headerText;
    headerText << "名称" << "大小";
    this->ui->tableWidget->setColumnCount(headerText.count());
    for(int i=0; i<headerText.count(); i++){
        QTableWidgetItem *headerItem = new QTableWidgetItem(headerText[i]);
        //      设置字体
        QFont font = headerItem->font();
        font.setBold(true); //设置大小写
        font.setPointSize(10);  //设置大小

        headerItem->setFont(font);

        //      装填表格头
        ui->tableWidget->setHorizontalHeaderItem(i,headerItem);
    }
    ui->tableWidget->setColumnWidth(0, 300);
    //装填表格身
    ui->tableWidget->setRowCount(entitys.count());

    for(int i=0; i<entitys.count(); i++){
        QStringList einfo = entitys[i].getList();
        for(int j=0; j<einfo.count(); j++){
            QTableWidgetItem *item = new QTableWidgetItem(einfo[j]);
            QFont font = item->font();
            font.setBold(true);
            item->setFont(font);
            ui->tableWidget->setItem(i, j, item);
        }
    }
}

//遍历arklist来填充左下角列表
void Interface::showList()
{
    ui->listWidget->clear();
    QList<QStringList> list = this->arkList->getInfo();
    for(QStringList ls: list){
        this->ui->listWidget->addItem(ls[1]);
    }
}

//通过‘标志文件’来添加Ark进列表
void Interface::loadArk(QString arkPath)
{
    //做判断
    if(QFile::exists(arkPath)){
        //添加ark
        this->arkList->addArk(arkPath);
    }
}

//通过‘ark_list文件初始化arklist
void Interface::loadArkList()
{
    //清空arkList
    this->arkList->clearArk();
    //读取arklist文件，获取坐标文件路径列表
    QFile arkFile("./ark_list.txt");
    arkFile.open(QIODeviceBase::ReadOnly);
    QStringList arkls = QString(arkFile.readAll()).split("\r\n");
    arkFile.close();
    for(QString ark: arkls){
        loadArk(ark);
    }
    //检测有无可用的路径
    if(this->arkList->getInfo().count() != 0){
        //用列表中第一个Ark初始化path
        QStringList ls = this->arkList->getInfo()[0];
        this->path = ls[0].split('.')[0] + subDir;
        this->ui->label->setText(ls[1]);
    }else{
        this->path = "no data";
    }

    //重置表格
    showList();
    loadEntitys();
    showTable();
}

//根据‘资源名字’来打开资源文件夹
void Interface::openDir(QString entityName)
{
    FAO fao;
    for(Entity entity: entitys){
        QFileInfo info = entity.getFileinfo();
        if(info.baseName() == entityName) {
            fao.openDir(info.absoluteFilePath());
            return;
        }
    }
}

//通过遍历path来更新entitys
void Interface::loadEntitys()
{
    entitys.clear();
    if(entitys.count() > 0){ entitys.removeFirst();}
    FAO fao;
    QFileInfoList files = fao.listDir(path);
    //检测是否找到位置
    if(files.count() == 0){
        ui->textBrowser->setText("该路径没有文件...");
        return;
    }
    for(QFileInfo file: files){
        //去除杂项
        if(file.baseName() == "" || file.baseName() == "." || file.baseName() == "..") continue;
        Entity *entity = new Entity(file);
        entitys.append(*entity);
    }
}

//通过打开文件dialog选择标志文件来添加ark到arklist
void Interface::addArk()
{
     QString fileName = QFileDialog::getOpenFileName(this, "打开定位文件",
                                 "D:/多拉/游戏",
                                 "LoadFile (*.ArkId)");
     //检测有没有选择文件
     if(fileName.isEmpty()){
         return;
     }
     for(QStringList ls: arkList->getInfo()){
         if(fileName == ls[0]){
             QMessageBox::information(this, "重复", "重复登录。");
             return;
         }
     }
     //添加ark到list
     this->arkList->addArk(fileName);
     QList<QStringList> ls = arkList->getInfo();
     QString name = ls[ls.count()-1][1];
     //显示信息到面板
     printArkInfo(name);
     //刷新列表
     showList();
     //切换主表
     switchArk(name);
}

//通过ark name来切换显示的ark
void Interface::switchArk(QString name)
{
    QStringList ls = arkList->findArkByName(name);

    this->path = ls[0].split('.')[0] + subDir;
    // 重新加载entity
    loadEntitys();
    showTable();
    //右边表格label显示
    this->ui->label->setText(name);
    //面板追加显示文件个数
    this->ui->textBrowser->append("共有 "+QString::number(this->ui->tableWidget->rowCount())+" 个结果");
}

//通过ark name 来显示ark信息到面板
void Interface::printArkInfo(QString name)
{
    QString str;
    QStringList ls = this->arkList->findArkByName(name);
    for(int i=1; i<ls.count(); i++){
        str += ls[i] + "\n";
    }
    str += "\n位置：" + ls[0] + "\n";
    ui->textBrowser->setText(str);
}

Interface::~Interface()
{
    delete ui;
}

//通过entity name来找entity并显示信息到面板并返回目标行数
int Interface::findData(QString name){
    //刷新表
    showTable();

    QString str;

    auto items = ui->tableWidget->findItems(name, Qt::MatchContains);
    int reRow;
    if(items.count() == 0){
        str = "没有找到";
        reRow = -1;
    }else{
        str.push_back("一共找到："+ QString::number(items.count()) + " 个结果\n\n");

        QTableWidgetItem *item = items[0];
        reRow = item->row();

        for(QTableWidgetItem *item: items){
            str.push_back("> " + item->text() + "\n");
            int row = item->row();
            for(int i=0; i<ui->tableWidget->columnCount(); i++){
                auto item = ui->tableWidget->item(row,i);

                // 在table中标记行
                item->setBackground(QBrush(QColor(0, 255, 0)));
                item->setForeground(QBrush(QColor(255, 0, 0)));
            }

        }

    }
    ui->textBrowser->setText(str);
    return reRow;
}
