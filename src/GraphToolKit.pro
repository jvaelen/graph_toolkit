QT       += core xml gui

CONFIG += static
Win32 {
QMAKE_LFLAGS += -static-libgcc
}
Win64 {
QMAKE_LFLAGS += -static-libgcc
}


SOURCES += \
    main.cpp \
    graph/graph.cpp \
    graph/matrixgraph.cpp \
    graph/listgraph.cpp \
    graph/hybridgraph.cpp \
    graph/hybridGraphState/matrixstate.cpp \
    graph/hybridGraphState/liststate.cpp \
    graph/hybridGraphState/hybridgraphstate.cpp \
    graph/graphComp/edge.cpp \
    graph/graphComp/node.cpp \
    graph/graphComp/label.cpp \
    graph/graphComp/point.cpp \
    graph/graphComp/rgb.cpp \
    observer/observer.cpp \
    fileIO/formatprototypemanager.cpp \
    fileIO/formats/formathandlerstate.cpp \
    fileIO/formats/graph6writer.cpp \
    fileIO/formats/graph6reader.cpp \
    fileIO/formats/sparse6writer.cpp \
    fileIO/formats/graphmlwriter.cpp \
    fileIO/formats/sparse6reader.cpp \
    fileIO/formats/graphmlreader.cpp \
    fileIO/bitvector.cpp \
    visitor/visitor.cpp \
    graphtoolkit.cpp \
    graph/integermatrix.cpp \
    observer/commandline/commandline.cpp \
    observer/subject.cpp \
    exception/uniquenodeex.cpp \
    exception/baseex.cpp \
    exception/uniqueedgeex.cpp \
    exception/unexistingedgeex.cpp \
    exception/unexistingnodeex.cpp \
    fileIO/formathandler.cpp \
    observer/GUI/graphtoolkitwindow.cpp \
    observer/GUI/graphdrawingview.cpp \
    observer/GUI/graphdrawingwidget.cpp \
    observer/GUI/toolswidget.cpp \
    tools/toolhandler.cpp \
    tools/toolstate.cpp \
    tools/selectandmovetool.cpp \
    tools/addnodetool.cpp \
    tools/addedgetool.cpp \
    tools/removenodetool.cpp \
    tools/removeedgetool.cpp \
    exception/fileioex.cpp \
    observer/GUI/newgraphwindow.cpp \
    observer/GUI/graphdrawingscene.cpp \
    observer/GUI/graphicsnode.cpp \
    tools/toolparameters.cpp \
    observer/GUI/graphicsedge.cpp \
    observer/GUI/graphicarrowhead.cpp \
    observer/GUI/exceptionmessagebox.cpp \
    visitor/graphdrawingvisitors/standardlayoutvisitor.cpp \
    fileIO/formats/tsplibreader.cpp \
    visitor/graphdrawingvisitors/forcedirectedvisitor.cpp \
    visitor/algorithmvisitor.cpp \
    visitor/propertyvisitor.cpp \
    exception/invalidformatex.cpp \
    visitor/graphtheoryvisitors/breadthfirstsearchvisitor.cpp \
    visitor/graphtheoryvisitors/searchvisitor.cpp \
    tools/toolpm.cpp \
    tools/toolaction.cpp \
    visitor/graphtheoryvisitors/depthfirstsearchvisitor.cpp \
    visitor/propertyvisitors/undirectedvisitor.cpp \
    visitor/algorithmvisitorpm.cpp \
    visitor/propertyvisitors/connectedvisitor.cpp \
    observer/GUI/selectionobserverwidget.cpp \
    visitor/propertyvisitorpm.cpp \
    observer/GUI/propertyobserver/propertyfield.cpp \
    observer/GUI/propertyobserver/propertyobserver.cpp \
    visitor/propertyvisitors/cyclevisitor.cpp \
    visitor/graphtheoryvisitors/stronglyconnectedcomponentsvisitor.cpp \
    visitor/graphtheoryvisitors/kruskalvisitor.cpp \
    observer/GUI/settingswindow.cpp \
    visitor/graphtheoryvisitors/hamcyclevisitor.cpp \
    visitor/graphtheoryvisitors/hampathvisitor.cpp \
    graph/graphComp/graphcomp.cpp \
    visitor/propertyvisitors/weightedvisitor.cpp \
    exception/invalidgraph.cpp \
    visitor/graphdrawingvisitors/barycentricdrawer.cpp \
    visitor/graphtheoryvisitors/tspvisitor.cpp \
    visitor/propertyvisitors/completevisitor.cpp \
    fileIO/formats/dotreader.cpp \
    fileIO/formats/dotwriter.cpp

HEADERS += \
    graph/graph.h \
    graph/matrixgraph.h \
    graph/listgraph.h \
    graph/hybridgraph.h \
    graph/hybridGraphState/matrixstate.h \
    graph/hybridGraphState/liststate.h \
    graph/hybridGraphState/hybridgraphstate.h \
    graph/graphComp/edge.h \
    graph/graphComp/node.h \
    graph/graphComp/label.h \
    graph/graphComp/point.h \
    graph/graphComp/rgb.h \
    observer/observer.h \
    fileIO/formatprototypemanager.h \
    fileIO/formats/formathandlerstate.h \
    fileIO/formats/graph6writer.h \
    fileIO/formats/graph6reader.h \
    fileIO/formats/sparse6writer.h \
    fileIO/formats/graphmlwriter.h \
    fileIO/formats/sparse6reader.h \
    fileIO/formats/graphmlreader.h \
    fileIO/bitvector.h \
    visitor/visitor.h \
    graphtoolkit.h \
    graph/integermatrix.h \
    observer/commandline/commandline.h \
    observer/subject.h \
    exception/uniquenodeex.h \
    exception/baseex.h \
    exception/uniqueedgeex.h \
    exception/unexistingedgeex.h \
    exception/unexistingnodeex.h \
    fileIO/formathandler.h \
    observer/GUI/graphtoolkitwindow.h \
    observer/GUI/graphdrawingview.h \
    observer/GUI/graphdrawingwidget.h \
    observer/GUI/toolswidget.h \
    tools/toolhandler.h \
    tools/toolstate.h \
    tools/selectandmovetool.h \
    tools/addnodetool.h \
    tools/addedgetool.h \
    tools/removenodetool.h \
    tools/removeedgetool.h \
    exception/fileioex.h \
    observer/GUI/newgraphwindow.h \
    observer/GUI/graphdrawingscene.h \
    observer/GUI/graphicsnode.h \
    tools/toolparameters.h \
    observer/GUI/graphicsedge.h \
    observer/GUI/graphicarrowhead.h \
    observer/GUI/exceptionmessagebox.h \
    visitor/graphdrawingvisitors/standardlayoutvisitor.h \
    fileIO/formats/tsplibreader.h \
    visitor/graphdrawingvisitors/forcedirectedvisitor.h \
    visitor/algorithmvisitor.h \
    visitor/propertyvisitor.h \
    exception/invalidformatex.h \
    visitor/graphtheoryvisitors/breadthfirstsearchvisitor.h \
    visitor/graphtheoryvisitors/searchvisitor.h \
    tools/toolpm.h \
    tools/toolaction.h \
    visitor/graphtheoryvisitors/depthfirstsearchvisitor.h \
    visitor/propertyvisitors/undirectedvisitor.h \
    visitor/algorithmvisitorpm.h \
    visitor/propertyvisitors/connectedvisitor.h \
    observer/GUI/selectionobserverwidget.h \
    visitor/propertyvisitorpm.h \
    observer/GUI/propertyobserver/propertyfield.h \
    observer/GUI/propertyobserver/propertyobserver.h \
    visitor/propertyvisitors/cyclevisitor.h \
    visitor/graphtheoryvisitors/stronglyconnectedcomponentsvisitor.h \
    visitor/graphtheoryvisitors/kruskalvisitor.h \
    observer/GUI/settingswindow.h \
    visitor/graphtheoryvisitors/hamcyclevisitor.h \
    visitor/graphtheoryvisitors/hampathvisitor.h \
    graph/graphComp/graphcomp.h \
    visitor/propertyvisitors/weightedvisitor.h \
    exception/invalidgraph.h \
    visitor/graphdrawingvisitors/barycentricdrawer.h \
    visitor/graphtheoryvisitors/tspvisitor.h \
    visitor/propertyvisitors/completevisitor.h \
    fileIO/formats/dotreader.h \
    fileIO/formats/dotwriter.h

RESOURCES += \
    resources.qrc

QT += gui declarative
