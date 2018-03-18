#include "mainwindow.hpp"
#include "insertdialog.hpp"
#include "renderer.hpp"

#include "linkedlisthandler.hpp"
#include "doublelinkedlisthandler.hpp"
#include "hashmaphandler.hpp"
#include "arrayhandler.hpp"

#include <QMenuBar>
#include <QMenu>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QInputDialog>

constexpr int DEFAULT_VALUE {0};
constexpr int MINIMUM_VALUE {0};
constexpr int MAXIMUM_VALUE {100};
constexpr int STEP {1};

class MainWindow::Impl
{

public:

    QMenu* linkedListMenu;
    QMenu* doubleLinkedListMenu;
    QMenu* arrayMenu;
    QMenu* hashmapMenu;

    QAction* createLinkedListAction;
    QAction* insertAtTheEndLinkedListAction;
    QAction* insertAtTheBeginningLinkedListAction;
    QAction* insertAfterLinkedListAction;
    QAction* atLinkedListAction;
    QAction* dropAtLinkedListAction;
    QAction* dropAtTheEndLinkedListAction;

    QAction* createDoubleLinkedListAction;
    QAction* insertAtTheBeginningDoubleLinkedListAction;
    QAction* insertAtTheEndDoubleLinkedListAction;
    QAction* dropAtDoubleLinkedListAction;

    QAction* createArrayAction;
    QAction* dropArrayAction;

    QAction* createHashmapAction;

    QGraphicsView* view;
    QGraphicsScene* scene;

    LinkedListHandler linkedListHandler;
    DoubleLinkedListHandler doubleLinkedListHandler;
    HashmapHandler hashmapHandler;
    ArrayHandler arrayHandler;
};

/**
 *
 */
MainWindow::MainWindow() : impl(std::make_unique<Impl>())
{
    constexpr int WINDOW_WIDTH {800};
    constexpr int WINDOW_HEIGHT {600};
    setMinimumSize(
        WINDOW_WIDTH,
        WINDOW_HEIGHT
    );

    auto& view = impl->view;
    auto& scene = impl->scene;

    scene = new QGraphicsScene();
    view = new QGraphicsView(scene);

    /* set here in order to use the window dimensions */
    constexpr int WINDOW_ORIGINS {0};
    constexpr int SCENE_MARGINS {50};
    scene->setSceneRect(
        QRectF(
            WINDOW_ORIGINS,
            WINDOW_ORIGINS,
            WINDOW_WIDTH - SCENE_MARGINS,
            WINDOW_HEIGHT - SCENE_MARGINS
        )
    );

    auto& createLinkedListAction = impl->createLinkedListAction;
    auto& insertAtTheEndLinkedListAction =
        impl->insertAtTheEndLinkedListAction;
    auto& insertAtTheBeginningLinkedListAction =
        impl->insertAtTheBeginningLinkedListAction;
    auto& insertAfterLinkedListAction = impl->insertAfterLinkedListAction;
    auto& atLinkedListAction = impl->atLinkedListAction;
    auto& dropAtLinkedListAction = impl->dropAtLinkedListAction;
    auto& dropAtTheEndLinkedListAction = impl->dropAtTheEndLinkedListAction;

    auto& createDoubleLinkedListAction = impl->createDoubleLinkedListAction;
    auto& insertAtTheBeginningDoubleLinkedListAction =
        impl->insertAtTheBeginningDoubleLinkedListAction;
    auto& insertAtTheEndDoubleLinkedListAction =
        impl->insertAtTheEndDoubleLinkedListAction;
    auto& dropAtDoubleLinkedListAction = impl->dropAtDoubleLinkedListAction;

    auto& createArrayAction = impl->createArrayAction;
    auto& dropArrayAction = impl->dropArrayAction;

    auto& createHashmapAction = impl->createHashmapAction;

    createLinkedListAction = new QAction("Create");
    connect(
        createLinkedListAction,
        SIGNAL(triggered()),
        this,
        SLOT(createLinkedList())
    );

    insertAtTheEndLinkedListAction = new QAction("Insert at the end");
    connect(
        insertAtTheEndLinkedListAction,
        SIGNAL(triggered()),
        this,
        SLOT(insertAtTheEndLinkedList())
    );

    insertAtTheBeginningLinkedListAction = new QAction("Insert at the beginning");
    connect(
        insertAtTheBeginningLinkedListAction,
        SIGNAL(triggered()),
        this,
        SLOT(insertAtTheBeginningLinkedList())
    );

    insertAfterLinkedListAction = new QAction("Insert after");
    connect(
        insertAfterLinkedListAction,
        SIGNAL(triggered()),
        this,
        SLOT(insertAfterLinkedList())
    );

    atLinkedListAction = new QAction("At");
    connect(
        atLinkedListAction,
        SIGNAL(triggered()),
        this,
        SLOT(atLinkedList())
    );

    dropAtLinkedListAction = new QAction("Drop at");
    connect(
        dropAtLinkedListAction,
        SIGNAL(triggered()),
        this,
        SLOT(dropAtLinkedList())
    );

    dropAtTheEndLinkedListAction = new QAction("Drop at the end");
    connect(
        dropAtTheEndLinkedListAction,
        SIGNAL(triggered()),
        this,
        SLOT(dropAtTheEndLinkedList())
    );

    createDoubleLinkedListAction = new QAction("Create");
    connect(
        createDoubleLinkedListAction,
        SIGNAL(triggered()),
        this,
        SLOT(createDoubleLinkedList())
    );

    insertAtTheEndDoubleLinkedListAction = new QAction("Insert at the end");
    connect(
        insertAtTheEndDoubleLinkedListAction,
        SIGNAL(triggered()),
        this,
        SLOT(insertAtTheEndDoubleLinkedList())
    );

    insertAtTheBeginningDoubleLinkedListAction = new QAction("Insert at the beginning");
    connect(
        insertAtTheBeginningDoubleLinkedListAction,
        SIGNAL(triggered()),
        this,
        SLOT(insertAtTheBeginningDoubleLinkedList())
    );

    dropAtDoubleLinkedListAction = new QAction("Drop at");
    connect(
        dropAtDoubleLinkedListAction,
        SIGNAL(triggered()),
        this,
        SLOT(dropAtDoubleLinkedList())
    );

    createArrayAction = new QAction("Create (malloc)");
    connect(
        createArrayAction,
        SIGNAL(triggered()),
        this,
        SLOT(createArray())
    );

    dropArrayAction = new QAction("Drop (free)");
    connect(
        dropArrayAction,
        SIGNAL(triggered()),
        this,
        SLOT(dropArray())
    );

    createHashmapAction = new QAction("Create");
    connect(
        createHashmapAction,
        SIGNAL(triggered()),
        this,
        SLOT(createHashmap())
    );

    auto& linkedListMenu = impl->linkedListMenu;
    linkedListMenu = menuBar()->addMenu("Linked list");
    linkedListMenu->addAction(createLinkedListAction);
    linkedListMenu->addAction(insertAtTheEndLinkedListAction);
    linkedListMenu->addAction(insertAtTheBeginningLinkedListAction);
    linkedListMenu->addAction(insertAfterLinkedListAction);
    linkedListMenu->addAction(atLinkedListAction);
    linkedListMenu->addAction(dropAtLinkedListAction);
    linkedListMenu->addAction(dropAtTheEndLinkedListAction);

    auto& doubleLinkedListMenu = impl->doubleLinkedListMenu;
    doubleLinkedListMenu = menuBar()->addMenu("Double linked list");
    doubleLinkedListMenu->addAction(createDoubleLinkedListAction);
    doubleLinkedListMenu->addAction(insertAtTheBeginningDoubleLinkedListAction);
    doubleLinkedListMenu->addAction(insertAtTheEndDoubleLinkedListAction);
    doubleLinkedListMenu->addAction(dropAtDoubleLinkedListAction);

    auto& arrayMenu = impl->arrayMenu;
    arrayMenu = menuBar()->addMenu("Array");
    arrayMenu->addAction(createArrayAction);
    arrayMenu->addAction(dropArrayAction);

    auto& hashmapMenu = impl->hashmapMenu;
    hashmapMenu = menuBar()->addMenu("Hashmap");
    hashmapMenu->addAction(createHashmapAction);

    initializeMenusOptions();

    setCentralWidget(view);
}

/**
 *
 */
MainWindow::~MainWindow() = default;

/**
 *
 */
void MainWindow::createLinkedList()
{
    bool set {false};

    const int data = QInputDialog::getInt(
        this,
        "Linked list",
        "Linked list first node data:",
        DEFAULT_VALUE,
        MINIMUM_VALUE,
        MAXIMUM_VALUE,
        STEP,
        &set
    );

    if (!set) {
        return;
    }

    auto& linkedListHandler = impl->linkedListHandler;
    linkedListHandler.createLinkedList(data);
    ::render(
        impl->scene,
        &linkedListHandler
    );

    impl->createLinkedListAction->setEnabled(false);
    impl->createDoubleLinkedListAction->setEnabled(false);
    impl->createArrayAction->setEnabled(false);
    impl->createHashmapAction->setEnabled(false);

    impl->insertAtTheEndLinkedListAction->setEnabled(true);
    impl->insertAtTheBeginningLinkedListAction->setEnabled(true);
    impl->insertAfterLinkedListAction->setEnabled(true);
    impl->atLinkedListAction->setEnabled(true);
    impl->dropAtLinkedListAction->setEnabled(true);
    impl->dropAtTheEndLinkedListAction->setEnabled(true);
}

/**
 *
 */
void MainWindow::insertAtTheEndLinkedList()
{
    bool set {false};

    const int data = QInputDialog::getInt(
        this,
        "Linked list",
        "Last data to insert:",
        DEFAULT_VALUE,
        MINIMUM_VALUE,
        MAXIMUM_VALUE,
        STEP,
        &set
    );

    if (!set) {
        return;
    }

    auto& linkedListHandler = impl->linkedListHandler;
    linkedListHandler.insertAtTheEndLinkedList(data);
    ::render(
        impl->scene,
        &linkedListHandler
    );
}

/**
 *
 */
void MainWindow::insertAtTheBeginningLinkedList()
{
    bool set {false};

    const int data = QInputDialog::getInt(
        this,
        "Linked list",
        "First data to insert:",
        DEFAULT_VALUE,
        MINIMUM_VALUE,
        MAXIMUM_VALUE,
        STEP,
        &set
    );

    if (!set) {
        return;
    }

    auto& linkedListHandler = impl->linkedListHandler;
    linkedListHandler.insertAtTheBeginningLinkedList(data);
    ::render(
        impl->scene,
        &linkedListHandler
    );
}

/**
 *
 */
void MainWindow::insertAfterLinkedList()
{
    auto& linkedListHandler = impl->linkedListHandler;

    const auto maximumIndex = linkedListHandler.getLinkedListLastIndex();
    InsertDialog* dialog = new InsertDialog(maximumIndex);

    auto ok = dialog->exec();
    if (ok == QDialog::Rejected)
    {
        return;
    }

    linkedListHandler.insertAfterLinkedList(
        dialog->getIndex(),
        dialog->getData()
    );
    ::render(
        impl->scene,
        &linkedListHandler
    );
}

/**
 *
 */
void MainWindow::atLinkedList()
{
    bool set {false};

    auto& linkedListHandler = impl->linkedListHandler;

    const int index = QInputDialog::getInt(
        this,
        "Linked list",
        "Get data at index:",
        DEFAULT_VALUE,
        MINIMUM_VALUE,
        linkedListHandler.getLinkedListLastIndex(),
        STEP,
        &set
    );

    if (!set) {
        return;
    }

    auto& scene = impl->scene;
    linkedListHandler.selectItem(
        scene,
        index
    );
    ::render(
        scene,
        &linkedListHandler
    );
}

/**
 *
 */
void MainWindow::dropAtLinkedList()
{
    bool set {false};

    auto& linkedListHandler = impl->linkedListHandler;

    const int index = QInputDialog::getInt(
        this,
        "Linked list",
        "Drop at index:",
        DEFAULT_VALUE,
        MINIMUM_VALUE,
        linkedListHandler.getLinkedListLastIndex(),
        STEP,
        &set
    );

    if (!set) {
        return;
    }

    linkedListHandler.dropAtIndexLinkedList(index);
    ::render(
        impl->scene,
        &linkedListHandler
    );

    if (linkedListHandler.getSize() == 0)
    {
        initializeMenusOptions();
    }
}

/**
 *
 */
void MainWindow::dropAtTheEndLinkedList()
{
    auto& linkedListHandler = impl->linkedListHandler;

    linkedListHandler.dropAtTheEndLinkedList();
    ::render(
        impl->scene,
        &linkedListHandler
    );

    if (linkedListHandler.getSize() == 0)
    {
        initializeMenusOptions();
    }
}

/**
 *
 */
void MainWindow::createDoubleLinkedList()
{
    bool set {false};

    const int data = QInputDialog::getInt(
        this,
        "Double linked list",
        "Double linked list first node data:",
        DEFAULT_VALUE,
        MINIMUM_VALUE,
        MAXIMUM_VALUE,
        STEP,
        &set
    );

    if (!set) {
        return;
    }

    auto& doubleLinkedListHandler = impl->doubleLinkedListHandler;
    doubleLinkedListHandler.createDoubleLinkedList(data);
    ::render(
        impl->scene,
        &doubleLinkedListHandler
    );

    impl->createLinkedListAction->setEnabled(false);
    impl->createDoubleLinkedListAction->setEnabled(false);
    impl->createArrayAction->setEnabled(false);
    impl->createHashmapAction->setEnabled(false);

    impl->insertAtTheEndDoubleLinkedListAction->setEnabled(true);
    impl->insertAtTheBeginningDoubleLinkedListAction->setEnabled(true);
    impl->dropAtDoubleLinkedListAction->setEnabled(true);
}

/**
 *
 */
void MainWindow::insertAtTheEndDoubleLinkedList()
{
    bool set {false};

    const int data = QInputDialog::getInt(
        this,
        "Double linked list",
        "Last data to insert:",
        DEFAULT_VALUE,
        MINIMUM_VALUE,
        MAXIMUM_VALUE,
        STEP,
        &set
    );

    if (!set) {
        return;
    }

    auto& doubleLinkedListHandler = impl->doubleLinkedListHandler;
    doubleLinkedListHandler.insertAtTheEndDoubleLinkedList(data);
    ::render(
        impl->scene,
        &doubleLinkedListHandler
    );
}

/**
 *
 */
void MainWindow::insertAtTheBeginningDoubleLinkedList()
{
    bool set {false};

    const int data = QInputDialog::getInt(
        this,
        "Double linked list",
        "First data to insert:",
        DEFAULT_VALUE,
        MINIMUM_VALUE,
        MAXIMUM_VALUE,
        STEP,
        &set
    );

    if (!set) {
        return;
    }

    auto& doubleLinkedListHandler = impl->doubleLinkedListHandler;
    doubleLinkedListHandler.insertAtTheBeginningDoubleLinkedList(data);
    ::render(
        impl->scene,
        &doubleLinkedListHandler
    );
}

/**
 *
 */
void MainWindow::dropAtDoubleLinkedList()
{
    bool set {false};

    auto& doubleLinkedListHandler = impl->doubleLinkedListHandler;

    const unsigned int index = QInputDialog::getInt(
        this,
        "Double linked list",
        "Drop at index:",
        DEFAULT_VALUE,
        MINIMUM_VALUE,
        doubleLinkedListHandler.getLastIndex(),
        STEP,
        &set
    );

    if (!set) {
        return;
    }

    doubleLinkedListHandler.dropAtDoubleLinkedList(index);
    ::render(
        impl->scene,
        &doubleLinkedListHandler
    );

    if (doubleLinkedListHandler.getSize() == 0)
    {
        initializeMenusOptions();
    }
}

/**
 *
 */
void MainWindow::createArray()
{
    bool set {false};

    constexpr int ARRAY_SIZE_MINIMUM_VALUE {1}; 
    const int size = QInputDialog::getInt(
        this,
        "Array",
        "Fixed size of the array:",
        DEFAULT_VALUE,
        ARRAY_SIZE_MINIMUM_VALUE,
        MAXIMUM_VALUE,
        STEP,
        &set
    );

    if (!set) {
        return;
    }

    const auto& arrayHandler = impl->arrayHandler;
    arrayHandler.createArray(static_cast<std::size_t>(size));

    impl->createLinkedListAction->setEnabled(false);
    impl->createDoubleLinkedListAction->setEnabled(false);
    impl->createHashmapAction->setEnabled(false);

    impl->createArrayAction->setEnabled(false);
    impl->dropArrayAction->setEnabled(true);

    ::renderArray(
        impl->scene,
        &arrayHandler
    );
}

/**
 *
 */
void MainWindow::dropArray()
{
    impl->arrayHandler.dropArray();

    initializeMenusOptions();

    impl->scene->clear();
}

/**
 *
 */
void MainWindow::createHashmap()
{
    bool set {false};

    const int size = QInputDialog::getInt(
        this,
        "Hashmap",
        "Size of the hashmap:",
        DEFAULT_VALUE,
        MINIMUM_VALUE,
        MAXIMUM_VALUE,
        STEP,
        &set
    );

    if (!set) {
        return;
    }

    auto& hashmapHandler = impl->hashmapHandler;
    hashmapHandler.createHashmap(size);

    /* TODO: rendering */
}

/**
 *
 */
void MainWindow::initializeMenusOptions()
{
    impl->createLinkedListAction->setEnabled(true);
    impl->createDoubleLinkedListAction->setEnabled(true);
    impl->createArrayAction->setEnabled(true);

    impl->insertAtTheEndLinkedListAction->setEnabled(false);
    impl->insertAtTheBeginningLinkedListAction->setEnabled(false);
    impl->insertAfterLinkedListAction->setEnabled(false);
    impl->atLinkedListAction->setEnabled(false);
    impl->dropAtLinkedListAction->setEnabled(false);
    impl->insertAtTheEndDoubleLinkedListAction->setEnabled(false);
    impl->insertAtTheBeginningDoubleLinkedListAction->setEnabled(false);
    impl->dropAtDoubleLinkedListAction->setEnabled(false);
    impl->dropAtTheEndLinkedListAction->setEnabled(false);
    impl->dropArrayAction->setEnabled(false);
}
