#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    QStringList list;
    list << "Author" << "Year" << "Title" << "Journal" << "Volume" << "Issue" << "Pages";

    createGUI();

    delegator = new Delegate(this);
    model = new QStandardItemModel(this);
    proxyModel = new QSortFilterProxyModel(this);
    model->setHorizontalHeaderLabels(list);

    optionsList->addItems(list); //Sets the comboBox with the values of the list
    tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::AnyKeyPressed); //Sets edit mode on the view to edit data in a cell
    tableView->setItemDelegate(delegator);
    proxyModel->setSourceModel(model);
    tableView->setSortingEnabled(true);
    tableView->setModel(proxyModel);

    connect(AddButton, &QPushButton::clicked, this, &Widget::addClicked);
    connect(RemoveButton, &QPushButton::clicked, this, &Widget::removeClicked);
    connect(model, &QStandardItemModel::itemChanged, this, &Widget::setColour);
    connect(FindButton, &QPushButton::clicked, this, &Widget::findClicked);
    connect(ResetButton, &QPushButton::clicked, this, &Widget::resetClicked);
}

Widget::~Widget()
{
}

void Widget::createGUI()
{

    QLabel *AuthorLabel = new QLabel("Author");
    Author = new QLineEdit();
    QRegularExpression authorRE("[a-zA-Z -]+");
    QValidator *authorVal = new QRegularExpressionValidator(authorRE, this);
    Author->setValidator(authorVal);

    QLabel *YearLabel = new QLabel("Year");
    Year = new QSpinBox();
    Year->setRange(1900, 2100);

    QLabel *TitleLabel = new QLabel("Title");
    Title = new QLineEdit();
    QRegularExpression titleRE("(\\b[a-zA-Z]+\\b|\\s+|\\b\\d+\\b)*");
    QValidator *titleVal = new QRegularExpressionValidator(titleRE, this);
    Title->setValidator(titleVal);

    QLabel *JournalLabel = new QLabel("Journal");
    Journal = new QLineEdit();
    Journal->setValidator(titleVal);

    QLabel *VolumeLabel = new QLabel("Volume");
    Volume = new QSpinBox();

    QLabel *IssueLabel = new QLabel("Issue");
    Issue = new QSpinBox();

    QLabel *PagesLabel = new QLabel("Pages");
    Pages = new QLineEdit();
    QRegularExpression PagesRE("[0-9]+( )?-( )?[0-9]+");
    QValidator *PagesVal = new QRegularExpressionValidator(PagesRE, this);
    Pages->setValidator(PagesVal);

    filterInput = new QLineEdit();
    optionsList = new QComboBox();

    AddButton = new QPushButton("Add");
    RemoveButton = new QPushButton("Remove");
    FindButton = new QPushButton("Find");
    ResetButton = new QPushButton("Reset");

    tableView = new QTableView(this);

    QHBoxLayout *mainApp = new QHBoxLayout();
    QVBoxLayout *leftSide = new QVBoxLayout();
    QVBoxLayout *rightSide = new QVBoxLayout();
    QHBoxLayout *firstHori = new QHBoxLayout();
    QHBoxLayout *secondHori = new QHBoxLayout();
    QHBoxLayout *thirdHori = new QHBoxLayout();
    QHBoxLayout *fourthHori = new QHBoxLayout();
    QHBoxLayout *fifthHori = new QHBoxLayout();
    QHBoxLayout *sixthHori = new QHBoxLayout();
    QHBoxLayout *seventhHori = new QHBoxLayout();
    QHBoxLayout *eigthHori = new QHBoxLayout();

    rightSide->addWidget(tableView);
    firstHori->addWidget(AuthorLabel);
    firstHori->addWidget(Author);
    secondHori->addWidget(YearLabel);
    secondHori->addWidget(Year);
    thirdHori->addWidget(TitleLabel);
    thirdHori->addWidget(Title);
    fourthHori->addWidget(JournalLabel);
    fourthHori->addWidget(Journal);
    fifthHori->addWidget(VolumeLabel);
    fifthHori->addWidget(Volume);
    sixthHori->addWidget(IssueLabel);
    sixthHori->addWidget(Issue);
    seventhHori->addWidget(PagesLabel);
    seventhHori->addWidget(Pages);
    eigthHori->addWidget(FindButton);
    eigthHori->addWidget(ResetButton);

    mainApp->addLayout(leftSide);
    mainApp->addLayout(rightSide);
    leftSide->addLayout(firstHori);
    leftSide->addLayout(secondHori);
    leftSide->addLayout(thirdHori);
    leftSide->addLayout(fourthHori);
    leftSide->addLayout(fifthHori);
    leftSide->addLayout(sixthHori);
    leftSide->addLayout(seventhHori);
    leftSide->addWidget(AddButton);
    leftSide->addWidget(RemoveButton);
    leftSide->addWidget(filterInput);
    leftSide->addWidget(optionsList);
    leftSide->addLayout(eigthHori);

    setLayout(mainApp);
}

void Widget::addClicked()
{
    QStandardItem *AuthorItem = new QStandardItem(Author->text());

    QStandardItem *YearItem;

    QDate curDate;
    curDate = QDate::currentDate();
    int currentYear, inputYear;
    currentYear = QString::number(curDate.year()).toInt();
    inputYear = QString::number(Year->value()).toInt();

    if(currentYear < inputYear)
    {
        YearItem = new QStandardItem(QString("Invalid Year"));
    }
    else
    {
        YearItem = new QStandardItem(QString::number(Year->value()));
    }

    QStandardItem *TitleItem = new QStandardItem(Title->text());
    QStandardItem *JournalItem = new QStandardItem(Journal->text());
    QStandardItem *VolumeItem = new QStandardItem(QString::number(Volume->value()));
    QStandardItem *IssueItem = new QStandardItem(QString::number(Issue->value()));
    QStandardItem *PagesItem = new QStandardItem(Pages->text());

    QList<QStandardItem*> itemsRow;
    itemsRow << AuthorItem << YearItem << TitleItem << JournalItem << VolumeItem << IssueItem << PagesItem;

    model->appendRow(itemsRow);

    if(currentYear - inputYear > 10)
    {
        QListIterator<QStandardItem*> itr(itemsRow);
        while(itr.hasNext())
        {
            QColor redColor = Qt::red;

            QBrush brush(redColor);
            QStandardItem* next = itr.next();
            next->setBackground(brush);
        }
    }
    else if(currentYear - inputYear <= 5)
    {
        QListIterator<QStandardItem*> itr(itemsRow);
        while(itr.hasNext())
        {
            QColor greenColor = Qt::green;
            QBrush brush(greenColor);
            QStandardItem* next = itr.next();
            next->setBackground(brush);
        }
    }
}

void Widget::removeClicked()
{
    QModelIndex index = tableView->currentIndex();
    model->removeRows(index.row(), 1); //Removes the row specified at the index and the number is the number of rows removed
}

void Widget::setColour(QStandardItem *item)
{
    model->blockSignals(true);
    int row = item->row();

    QDate curDate;
    curDate = QDate::currentDate();
    int currentYear, inputYear;
    currentYear = QString::number(curDate.year()).toInt();
    QStandardItem *yearItem = model->item(row, 1);
    inputYear = QString(yearItem->text()).toInt();

    if(currentYear - inputYear > 10)
    {
        for(int col = 0; col < model->columnCount(); col++)
        {
            QColor redColor = Qt::red;
            QBrush brush(redColor);
            model->item(row, col)->setBackground(brush);
        }
    }
    else if(currentYear - inputYear <= 5)
    {
        for(int col = 0; col < model->columnCount(); col++)
        {
            QColor greenColor = Qt::green;
            QBrush brush(greenColor);
            model->item(row, col)->setBackground(brush);
        }
    }
    else
    {
        for(int col = 0; col < model->columnCount(); col++)
        {
            QColor greenColor = Qt::white;
            QBrush brush(greenColor);
            model->item(row, col)->setBackground(brush);
        }
    }
    model->blockSignals(false);
}

void Widget::findClicked()
{
    QRegularExpression re(filterInput->text(), QRegularExpression::CaseInsensitiveOption);
    proxyModel->setFilterRegularExpression(re);
    proxyModel->setFilterKeyColumn(optionsList->currentIndex());
}

void Widget::resetClicked()
{
    proxyModel->setFilterRegularExpression(QRegularExpression(""));
    proxyModel->setFilterKeyColumn(optionsList->currentIndex());
}
