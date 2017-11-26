#include "Editor3D.h"
#include "Graphics/ComponentBuilder.h"
#include "Graphics/OnTopEffect.h"
#include <QtWidgets>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QPlaneMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DRender/QCamera>
#include <Qt3DRender/QCameraLens>
#include <Qt3DRender/QMaterial>
#include <Qt3DRender/QParameter>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>

Editor3D::Editor3D(const QString& filePath) {
    Qt3DExtras::Qt3DWindow* view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    QWidget* container = QWidget::createWindowContainer(view);
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(container);

    Qt3DCore::QEntity* scene = createScene();

    camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);

    Qt3DExtras::QOrbitCameraController* cameraController = new Qt3DExtras::QOrbitCameraController(scene);
#ifdef Q_OS_WIN
    cameraController->setLinearSpeed(50.0f);
    cameraController->setLookSpeed(180.0f);
#else
    cameraController->setLinearSpeed(500.0f);
    cameraController->setLookSpeed(1800.0f);
#endif
    cameraController->setCamera(camera);

    view->setRootEntity(scene);

    resetViewport();
}

void Editor3D::resetViewport() {
    camera->setPosition(QVector3D(0, -2, 2));
    camera->setViewCenter(QVector3D(0, 0 ,0));
    camera->setUpVector(QVector3D(0, 1, 0));
}

Qt3DCore::QEntity* Editor3D::createScene() {
    Qt3DCore::QEntity* rootEntity = new Qt3DCore::QEntity;

    gridPlane = createGridPlane(rootEntity);
    axises = createOriginAxises(rootEntity);

    return rootEntity;
}

Qt3DCore::QEntity* Editor3D::createGridPlane(Qt3DCore::QEntity* parent) {
    Qt3DCore::QEntity* planeEntity = new Qt3DCore::QEntity(parent);

    Qt3DRender::QGeometryRenderer* planeMesh = ComponentBuilder::createGridPlaneMesh(11);
    planeEntity->addComponent(planeMesh);

    Qt3DRender::QMaterial* material = new Qt3DExtras::QPhongMaterial;
    planeEntity->addComponent(material);

    return planeEntity;
}

Qt3DCore::QEntity* Editor3D::createOriginAxises(Qt3DCore::QEntity* parent) {
    Qt3DCore::QEntity* axisesEntity = new Qt3DCore::QEntity(parent);

    // X axis
    Qt3DCore::QEntity* axisXEntity = new Qt3DCore::QEntity(axisesEntity);

    Qt3DRender::QGeometryRenderer* axisXMesh = ComponentBuilder::createLineMesh(QVector3D(0, 0, 0), QVector3D(1, 0, 0));
    axisXEntity->addComponent(axisXMesh);

    Qt3DRender::QMaterial* materialX = new Qt3DRender::QMaterial;
    materialX->setEffect(new OnTopEffect());
    materialX->addParameter(new Qt3DRender::QParameter(QStringLiteral("handleColor"), QColor(Qt::red)));
    axisXEntity->addComponent(materialX);

    // Y axis
    Qt3DCore::QEntity* axisYEntity = new Qt3DCore::QEntity(axisesEntity);

    Qt3DRender::QGeometryRenderer* axisYMesh = ComponentBuilder::createLineMesh(QVector3D(0, 0, 0), QVector3D(0, 1, 0));
    axisXEntity->addComponent(axisYMesh);

    Qt3DRender::QMaterial* materialY = new Qt3DRender::QMaterial;
    materialY->setEffect(new OnTopEffect());
    materialY->addParameter(new Qt3DRender::QParameter(QStringLiteral("handleColor"), QColor(Qt::green)));
    axisYEntity->addComponent(materialY);

    // Z axis
    Qt3DCore::QEntity* axisZEntity = new Qt3DCore::QEntity(axisesEntity);

    Qt3DRender::QGeometryRenderer* axisZMesh = ComponentBuilder::createLineMesh(QVector3D(0, 0, 0), QVector3D(0, 0, 1));
    axisXEntity->addComponent(axisZMesh);

    Qt3DRender::QMaterial* materialZ = new Qt3DRender::QMaterial;
    materialZ->setEffect(new OnTopEffect());
    materialZ->addParameter(new Qt3DRender::QParameter(QStringLiteral("handleColor"), QColor(Qt::green)));
    axisZEntity->addComponent(materialZ);

    return axisesEntity;
}
