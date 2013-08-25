/* Author: Jeroen Vaelen
   Description: for more information relating TSPLib file formats see http://comopt.ifi.uni-heidelberg.de/software/TSPLIB95/DOC.PS
   */

#ifndef TSPLIBREADER_H
#define TSPLIBREADER_H

/* @BALAZS en MEZELF:
  1. We supporten niet alle keywords, wat als de user ene invoegt die we ni supporten
  OFWEL een error throwen en tegen de user zeggen van fix uw file beke
  OF shit ignoren en gewoon tekenen (als da gaat, als die zegt van buuuhd as 3d gaat da obv ni)

  2. We tekenen atm de coords ma ik heb gemerkt da da vaak te dicht op elkaar is, hoe fixe?

  3. De edges moet ik nog trekke ma das gewoon TREKKE, heb da nog ni gedaan omda ik met u die file wil bekijken van TSP
     en dan wil interpreten van hoe we die edges trekken dan is da buh 1 regel code fzo
  */

#include "formathandlerstate.h"
#include <QStringList>

class TSPLibReader : public FormatHandlerState
{
public:
    TSPLibReader();
    void doIO();
    string getDescription() const { return description(); }
    string getExtension() const { return extention(); }
    static string extention() {return "tsp";}
    static string description() { return "TSPLIB is a library of sample instances for the TSP (and related problems) from various "
                "sources and of various types."; }

private:

    QStringList SUPPTYPES;
    QStringList SUPPWEIGHTTYPES;
    QStringList IGNORETYPES;

    void parseSpecification(QTextStream& in);
    void parseData(QTextStream& in);
    void validate(QString par, QStringList list);
};

#endif // TSPLIBREADER_H
