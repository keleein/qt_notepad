#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowIcon(QIcon(":/icon/notepad"));

    //初始化当前文件
    filename = "";

    filemenu = menuBar()->addMenu("文件");

    newfile = new QAction("新建");
    newfile->setIcon(QIcon(":/icon/newfile.png"));
    newfile->setShortcut(QKeySequence::New);
    newfile->setStatusTip("新建文件...");

    openfile = new QAction("打开");
    openfile->setIcon(QIcon(":/icon/openfile.png"));
    openfile->setShortcut(QKeySequence::Open);
    openfile->setStatusTip("打开文件...");

    savefile = new QAction("保存");
    savefile->setIcon(QIcon(":/icon/savefile.png"));
    savefile->setShortcut(QKeySequence::Save);
    savefile->setStatusTip("保存文件...");

    saveasfile = new QAction("另存为");
    saveasfile->setIcon(QIcon(":/icon/saveasfile.png"));
    saveasfile->setShortcut(QKeySequence::SaveAs);
    saveasfile->setStatusTip("另存为...");

    closefile = new QAction("关闭");
    closefile->setIcon(QIcon(":/icon/closefile.png"));
    closefile->setShortcut(QKeySequence::Close);
    closefile->setStatusTip("关闭文件...");

    exit = new QAction("退出");
    exit->setIcon(QIcon(":/icon/exit.png"));
    exit->setShortcut(QKeySequence::fromString("shift + e"));
    exit->setStatusTip("退出");

    filemenu->addAction(newfile);
    filemenu->addAction(openfile);
    filemenu->addAction(savefile);
    filemenu->addAction(saveasfile);
    filemenu->addAction(closefile);
    filemenu->addSeparator();
    filemenu->addAction(exit);

    editmenu = menuBar()->addMenu("编辑");

    font_format = new QAction("字体格式");
    font_format->setIcon(QIcon(":/icon/font_format.png"));
    font_format->setShortcut(QKeySequence::fromString("shift + f"));
    font_format->setStatusTip("字体格式...");

    font_color = new QAction("字体颜色");
    font_color->setIcon(QIcon(":/icon/font_color.png"));
    font_color->setShortcut(QKeySequence::fromString("shift + c"));
    font_color->setStatusTip("字体颜色...");

    copyac = new QAction("复制");
    copyac->setIcon(QIcon(":/icon/copy.png"));
    copyac->setShortcut(QKeySequence::Copy);
    copyac->setStatusTip("复制...");

    cutac = new QAction("剪切");
    cutac->setIcon(QIcon(":/icon/cut.png"));
    cutac->setShortcut(QKeySequence::Cut);
    cutac->setStatusTip("剪切...");

    pasteac = new QAction("粘贴");
    pasteac->setIcon(QIcon(":/icon/paste.png"));
    pasteac->setShortcut(QKeySequence::Paste);
    pasteac->setStatusTip("粘贴...");

    selectAll = new QAction("全选");
    selectAll->setIcon(QIcon(":/icon/selectAll.png"));
    selectAll->setShortcut(QKeySequence::SelectAll);
    selectAll->setStatusTip("全选...");

    editmenu->addAction(copyac);
    editmenu->addAction(cutac);
    editmenu->addAction(pasteac);
    editmenu->addAction(selectAll);
    editmenu->addAction(font_format);
    editmenu->addAction(font_color);

    aboutmenu = menuBar()->addMenu("关于");

    update = new QAction("检查更新");
    update->setIcon(QIcon(":/icon/update.png"));
    update->setShortcut(QKeySequence::fromString("shift + u"));
    update->setStatusTip("检查更新...");

    developer = new QAction("开发者");
    developer->setIcon(QIcon(":/icon/developer.png"));
    developer->setShortcut(QKeySequence::fromString("shift + d"));
    developer->setStatusTip("开发者...");

    aboutmenu->addAction(update);
    aboutmenu->addAction(developer);

    filebar = addToolBar("文件");
    filebar->addAction(newfile);
    filebar->addAction(newfile);
    filebar->addAction(openfile);
    filebar->addAction(savefile);
    filebar->addAction(saveasfile);
    filebar->addAction(closefile);

    editbar = addToolBar("编辑");
    editbar->addAction(copyac);
    editbar->addAction(cutac);
    editbar->addAction(pasteac);
    editbar->addAction(selectAll);
    editbar->addAction(font_format);
    editbar->addAction(font_color);

    aboutbar = addToolBar("关于");
    aboutbar->addAction(update);
    aboutbar->addAction(developer);

    te = new QTextEdit;
    te->setMinimumSize(640,480);
    setCentralWidget(te);
    te->setStyleSheet("background: white"); //qt中textedit的背景色默认是透明的，需要修改StyleSheet

    statusBar();

    //事件绑定
    connect(openfile,SIGNAL(triggered(bool)),this,SLOT(open_file()));
    connect(savefile,SIGNAL(triggered(bool)),this,SLOT(save_file()));
    connect(saveasfile,SIGNAL(triggered(bool)),this,SLOT(saveas_file()));
    connect(newfile,SIGNAL(triggered(bool)),this,SLOT(new_file()));
    connect(closefile,SIGNAL(triggered(bool)),this,SLOT(close_file()));

    connect(exit,SIGNAL(triggered(bool)),this,SLOT(exit_prog()));

    connect(font_format,SIGNAL(triggered(bool)),this,SLOT(font_select()));
    connect(font_color,SIGNAL(triggered(bool)),this,SLOT(color_select()));

    connect(copyac,SIGNAL(triggered(bool)),this,SLOT(copy_ac()));
    connect(cutac,SIGNAL(triggered(bool)),this,SLOT(cut_ac()));
    connect(pasteac,SIGNAL(triggered(bool)),this,SLOT(paste_ac()));
    connect(selectAll,SIGNAL(triggered(bool)),this,SLOT(select_all()));

    connect(update,SIGNAL(triggered(bool)),this,SLOT(update_test()));
    connect(developer,SIGNAL(triggered(bool)),this,SLOT(developer_tips()));
}

MainWindow::~MainWindow() {}

void MainWindow::open_file()
{
    if(!filename.isEmpty())
    {
        //当前存在文件被编辑，无论是否编辑过都直接保存
        save_file();
        te->clear();
    }
    filename = QFileDialog::getOpenFileName(this,"选择打开文件...","./",tr("Text files (*.txt *.cpp *.c)"));
    if(filename == "")
        return;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,"警告","文件打开失败: "+file.errorString());
        return;
    }
    while(!file.atEnd())
    {
        QByteArray data = file.readAll();
        te->setText(data);
    }
    file.close();
}

void MainWindow::save_file()
{
    if(filename.isEmpty())
    {
        filename = QFileDialog::getSaveFileName(this,"保存文件到","./",tr("Text files (*.txt *.cpp *.c)"));
    }
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        QMessageBox::warning(this,"警告","文件保存失败: "+file.errorString());
        return;
    }
    QString str = te->toHtml();
    file.write(str.toStdString().c_str(),str.length());
    file.close();
}

void MainWindow::saveas_file()
{
    filename = QFileDialog::getSaveFileName(this,"另存文件为","./",tr("Text files (*.txt *.cpp *.c)"));
    save_file();
}

void MainWindow::new_file()
{
    filename = QFileDialog::getSaveFileName(this,"请新建文件","./",tr("Text files (*.txt *.cpp *.c)"));
    te->clear();
}

void MainWindow::close_file()
{
    save_file();
    te->clear();
    filename = "";
}

void MainWindow::exit_prog()
{
    te->clear();
    filename = "";
    this->close();
}

void MainWindow::font_select()
{
    bool ok;
    QFont my_font = QFontDialog::getFont(&ok,this);
    if(ok)
    {
        qDebug() << "字体设置";
        te->setFont(my_font);
    }
    else
    {
        QMessageBox::warning(this,"waring","取消字体设置");
    }
}

void MainWindow::color_select()
{
    QColor color = QColorDialog::getColor();
    if(color.isValid())
        te->setTextColor(color);
}

void MainWindow::copy_ac()
{
    te->copy();
}

void MainWindow::cut_ac()
{
    te->cut();
}

void MainWindow::paste_ac()
{
    te->paste();
}

void MainWindow::select_all()
{
    te->selectAll();
}

void MainWindow::update_test()
{
    QMessageBox::information(this,"更新检查","正在进行更新检查...");
}

void MainWindow::developer_tips()
{
    QMessageBox::information(this,"开发者信息","notepad :: 邱钢");
}
