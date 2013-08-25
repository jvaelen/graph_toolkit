#ifndef PROPERTYOBSERVER_H
#define PROPERTYOBSERVER_H

#include <QList>
#include <QWidget>

class PropertyField;
class PropertyVisitorPM;
class PropertyVisitor;
class QGroupBox;
class QGridLayout;
class QVBoxLayout;
class QPushButton;

class PropertyObserver : public QWidget
{
    Q_OBJECT
public:
    PropertyObserver(QWidget* parent = 0);
    // clears all the PropertyFields
    ~PropertyObserver();
    // creates the property fields and links these with the proberty visitors so that they can be observed
    void initPropertyObserver(const PropertyVisitorPM& propertyVisitorPM);
    // returns true if there already propertyfields being visited
    bool hasPropertyFields() {return (_propertyFields.empty());}
private slots:
    void updateAllProperties();
private:
    bool _inited;
    void createNewPropertyField(PropertyVisitor* propertyVisitor);
    QList<PropertyField*> _propertyFields;
    QGridLayout* _widgetLayout;
    QVBoxLayout* _groupBoxLayout;
    QGroupBox* _groupBox;
    QPushButton* _updateALL;
};

#endif // PROPERTYOBSERVER_H
