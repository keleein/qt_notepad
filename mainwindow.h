#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QTextEdit>
#include <QToolBar>
#include <QStatusBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QFontDialog>
#include <QColorDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMenu *filemenu;
    QAction *newfile,*openfile,*savefile,*saveasfile,*closefile;
    QAction *exit;
    QTextEdit *te;

    QMenu *editmenu;
    QAction *font_format,*font_color;
    QAction *copyac,*cutac,*pasteac,*selectAll;

    QMenu *aboutmenu;
    QAction *update,*developer;

    QToolBar *filebar,*editbar,*aboutbar;

    QString filename;

private slots:
    void open_file();
    void save_file();
    void saveas_file();
    void new_file();
    void close_file();
    void exit_prog();
    void font_select();
    void color_select();
    void copy_ac();
    void cut_ac();
    void paste_ac();
    void select_all();
    void update_test();
    void developer_tips();
};
#endif // MAINWINDOW_H
