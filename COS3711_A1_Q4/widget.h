#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <QStandardItem>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStringList>
#include <QAbstractItemView>
#include <QModelIndex>
#include <QDate>
#include <QColor>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSortFilterProxyModel>
#include "delegate.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void createGUI();

private:
    QLineEdit *Author;
    QLineEdit *Title;
    QLineEdit *Journal;
    QLineEdit *Pages;
    QSpinBox *Year;
    QSpinBox *Volume;
    QSpinBox *Issue;
    QPushButton *AddButton;
    QPushButton *RemoveButton;
    QTableView *tableView;
    QStandardItemModel *model;
    QSortFilterProxyModel *proxyModel;
    QComboBox *optionsList;
    QLineEdit *filterInput;
    QPushButton *FindButton;
    QPushButton *ResetButton;
    Delegate *delegator;

private slots:
    void addClicked();
    void removeClicked();
    void setColour(QStandardItem *item);
    void findClicked();
    void resetClicked();
};
#endif // WIDGET_H
