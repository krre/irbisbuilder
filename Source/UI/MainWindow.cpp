#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Core/Defines.h"
#include <QtWidgets>

MainWindow::MainWindow(const QString& filePath) :
        _filePath(filePath),
        _ui(new Ui::MainWindow) {
    _ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete _ui;
}

void MainWindow::on_actionOpen_triggered() {
    QString workspaceDir = QString(); // TODO: Set workspace
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Irbis File"), workspaceDir, "Irbis (*.irbis);;All Files(*.*)");
    if (!filePath.isEmpty()) {
        qDebug() << "open" << filePath;
    }
}

void MainWindow::on_actionExit_triggered() {
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox::about(this, tr("About %1").arg(APP_NAME),
        tr("<h3>%1 %2</h3> \
           Based on Qt %3<br> \
           Build on %4<br><br> \
           <a href=%5>%5</a><br><br> \
           Copyright © 2017, Vladimir Zarypov").
           arg(APP_NAME).arg(APP_VERSION_STR).arg(QT_VERSION_STR).arg(__DATE__).arg(APP_URL));
}
