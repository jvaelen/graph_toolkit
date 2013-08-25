#ifndef GRAPHTOOLKITWINDOW_H
#define GRAPHTOOLKITWINDOW_H

#include <QMainWindow>

#include <QGridLayout>
#include <QGroupBox>

#include "observer/observer.h"
#include "graphdrawingwidget.h"
// this window will be shown when the user wants to create a new graph
#include "observer/GUI/newgraphwindow.h"

class QMenu;
class QAction;
class QActionGroup;
class QTimer;
class QVerticalLayout;
class ToolsWidget;
class SelectionObserverWidget;
class PropertyObserver;
class SettingsWindow;
class TimerChanger;

class GraphToolKitWindow : public QMainWindow, public Observer
{
    Q_OBJECT
public:
    explicit GraphToolKitWindow(QWidget *parent = 0);
    ~GraphToolKitWindow();
    void notify(Subject *subject);
signals:

private slots:
    // closes the current active graph
    void closeGraph();
    // sets the focusGraph in the _graphToolKit
    void setFocusGraph(int index);
    // changes the type of the current active graph, this slot is used in the menu
    void changeFocusGraphType();
    // shows the open dialog to open files and opens the focusGraph
    void openGraph();
    // shows the save dialog to save files and saves the focusGraph
    void saveGraph();
    // executes an algorithm on the current graph
    void doDrawingNormal();
    // does one iteartion of the graphdrawing algorithm
    void doDrawingIterative();
    // executes graph theory algorithm on current graph
    void doTheoryNormal();
    // executes one iterations of the graph theory algorithm
    void doTheoryIterative();
    // is called at the start of an iterative algorithm, it will set up a timer that will call the function about periodically
    void startIterativeGraphDrawingAlgorithm();
    void startIterativeGraphTheoryAlgorithm();
    // calls the random testing graph function of _graphToolKit, will be removed later when loading is implemented for graphmml
    void randomGraph();
    // tells the tools to undo the action
    void undoAction();
    // shows the NewGraphWindow
    void createNewGraph();
    // makes the graph complete
    void makeGraphComplete();
    // shows and handles the settings window, with handle we mean that if the user changes setting here, they are delegated tot the objects that need these settings
    void changeSettings();
    // exports the current focus graph to an image
    void exportAsImage();
    // stops a running algoritm
    void stopAlgorithm();
    // resets the colors for all the nodes in the graph to the default color
    void setDefaultColors();
    // displays the about dialogue
    void aboutApplication();
private: // helpfunctions
    // puts a widget(in this case a window, on the center of the screen
    void centerWindow(QWidget* other);
    // creates the menu structure and adds it to the window
    void createMenu();
    // creates the actions
    void createActions();
    // takes care of the creation of the toolbar, (allocated and initializes the toolbar)
    void createToolbar();
    // populates _mainLayout with all the widgets
    void createWidgets();
    // creates a statusbar, this statusbar guides the user when he is creating graphs
    void createStatusBar();
    // set up all the extra windows that can pop up. windows like NewGraphWindow and settings windows fall under this category
    void createWindows();
    // creates and links the toolbar;
    void createToolsToolBar();
    // updates the QTabWidget with new graphs and removes the ones that have been removed
    void updateGraphViews();
    // adds a GraphDrawingView to the QTabWidget and sets the observer for that graph
    void addGraphToView(Graph* graph);
    // removes a GraphDrawingWidget from the QTabWidget and free's the memory that it used
    void removeGraphFromView(int index);
    // calls addGraphToView only with the new graphs
    void addNewGraphs(vector<Graph*> modelGraphs);
    // finds old graphs and removes these, also frees up memory used by those widgets
    void removeOldGraphs(vector<Graph*> modelGraphs);
    // updates the window title to reflect what the user is doing
    void updateWindowTitle();
    // updates the _tabView to reflect the focusGraph
    void updateFocusGraph();
    // update the GraphStructure submenu to refrlect the type of the focus graph
    void updateGraphStructureMenu();
    // disable everything that has to do with graphediting if there are no graphs, enables otherwise
    void updateAllButtons();
    // creates the actions for the algorithms if there are none yet
    void updateAlgorithmActions();
    // stops an algorithm if there is one running
    void stopRunningAlgorithm();
    // a special function in the sence that it links the specific instance of a selectiontool with the selectionobserver that will show the selection (and make it possible to edit these)
    void linkSelectionTool();
    // link the propertyObserver with the properties int he property visitor PM
    void linkPropertyObsever();
private: // member variables
    int _lastChosenAlgorithm;
    QString _defaultTitle;
    // main layout for widgets
    QGridLayout* _mainLayout;
    QVBoxLayout* _sideBar;
    // widgets
    QTabWidget* _tabView;
    NewGraphWindow* _newGraphWindow;
    SettingsWindow* _settingsWindow;
    // the _mainWidget is used as the centralWidget in the QMainWindow. A layout (_mainLayout) is set in this widget and all other widgets are added in this layout
    QWidget* _mainWidget;
    ToolsWidget* _tools;
    // menu stuff_GraphDrawingAlgorithmTimer
    QMenu* _fileMenu;
    QMenu* _toolsMenu;
    QMenu* _helpMenu;
    QMenu* _graphStructureSubMenu;
    QMenu* _preferencesMenu;
    QMenu* _graphSettingsMenu;
    QMenu* _algorithmMenu;
    QMenu* _GraphDrawingAlgoritmSubMenu;
    QMenu* _GraphTheorySubMenu;
    QMenu* _editMenu;
    // actions
    QAction* _exitAct;
    QAction* _newAct;
    QAction* _closeAct;
    QAction* _saveAct;
    QAction* _saveAsAct;
    QAction* _exportAsImage;
    QAction* _openAct;
    QAction* _aboutAct;
    QAction* _randomGraphAct;
    QAction* _makeComplete;
    QAction* _undoAct;
    QAction* _stopAlgorithm;
    QAction* _setDefaultColors;
    // actions for algoritms
    QList<QAction*> _graphDrawingAlgorithms;
    QList<QAction*> _graphTheoryAlgorithms;
    // brings up the settings dialogue for the application
    QAction* _appSettingsAct;
    // submenu actions to select the graph structure
    QAction* _setHybridAct;
    QAction* _setMatrixAct;
    QAction* _setListAct;
    qint64 _algorithmRan;
    QActionGroup* _structureGroup;
    // this is the subject that we will be observing, and will be set after the first notification
    GraphToolKit* _graphToolKit;
    QVector<Graph*> _workingGraphs;
    SelectionObserverWidget* _selectionObserverWidget;
    // Qttimer that will call the doIteration of an algorithm periodiaclly so that a new iteration can be called
    QTimer* _algorithmTimer;
    PropertyObserver* _propertyObserver;
    // an integer that is incremented after each creation of a graph using the NewGraphWindow, this way the default name for a new graph can be set semi-uniquely
    unsigned newNameCounter;
    unsigned _theoryAlgorithmInterval;
    bool _theoryRunning;
};

#endif // GRAPHTOOLKITWINDOW_H
