#include "mainwindow.h"
#include "pointscene.h"
#include "all_math.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myScene = new PointScene(this);
    ui->graphicsView->setSceneRect(0, 0,
                                   ui->graphicsView->width(),
                                   ui->graphicsView->height());

    ui->graphicsView->setBackgroundBrush(Qt::black);
    ui->graphicsView->setScene(myScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    QRectF rect = ui->graphicsView->viewport()->rect();
    myScene->setSceneRect(rect);
}

void MainWindow::on_btn_calc_clicked()
{
    if (myScene->points.empty()) return;

    if (circleVisual) {
        myScene->removeItem(circleVisual);
        delete circleVisual;
        circleVisual = nullptr;
    }

    Circle result = all_math::find_min_circle(myScene->points);

    QPen pen(Qt::red);
    pen.setWidth(2);
    QBrush brush(QColor(0, 255, 255, 60));

    double diameter = result.radius * 2;
    double topLeftX = result.center.x() - result.radius;
    double topLeftY = result.center.y() - result.radius;

    circleVisual = myScene->addEllipse(
        topLeftX,
        topLeftY,
        diameter,
        diameter,
        pen,
        brush
        );

    circleVisual->setZValue(-1);

    ui->label_result->setText(QString("Центр: (%1; %2), Радиус: %3")
                                  .arg(result.center.x(), 0, 'f', 2)
                                  .arg(result.center.y(), 0, 'f', 2)
                                  .arg(result.radius, 0, 'f', 2));
}


void MainWindow::on_btn_clear_clicked()
{
    myScene->clear();
    myScene->points.clear();

    circleVisual = nullptr;

    ui->label_result->setText("Центр: (0, 0), Радиус: 0");
}



