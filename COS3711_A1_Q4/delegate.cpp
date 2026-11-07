#include "delegate.h"

Delegate::Delegate(QObject *parent)
    : QItemDelegate{parent}
{

}

QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column() == 0)
    {
        QLineEdit *editor = new QLineEdit(parent);
        QRegularExpression authorRE("[a-zA-Z -]+");
        QValidator *authorVal = new QRegularExpressionValidator(authorRE, parent);
        editor->setValidator(authorVal);
        return editor;
    }
    else if(index.column() == 1)
    {
        QSpinBox *editor = new QSpinBox(parent);
        editor->setMinimum(1950);
        editor->setMaximum(2026);
        return editor;
    }
    else if(index.column() == 2 || index.column() == 3)
    {
        QLineEdit *editor = new QLineEdit(parent);
        QRegularExpression titleJournalRE("(\\b[a-zA-Z]+\\b|\\s+|\\b\\d+\\b)*");
        QValidator *titleJournalVal = new QRegularExpressionValidator(titleJournalRE, parent);
        editor->setValidator(titleJournalVal);
        return editor;
    }
    else if(index.column() == 4 || index.column() == 5)
    {
        QSpinBox *editor = new QSpinBox(parent);
        return editor;
    }
    else if(index.column() == 6)
    {
        QLineEdit *editor = new QLineEdit(parent);
        QRegularExpression PagesRE("[0-9]+( )?-( )?[0-9]+");
        QValidator *PagesVal = new QRegularExpressionValidator(PagesRE, parent);
        editor->setValidator(PagesVal);
        return editor;
    }
}

void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column() == 0 || index.column() == 2 || index.column() == 3 || index.column() == 6)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        lineEdit->setText(value);
    }
    else if(index.column() == 1 || index.column() == 4 || index.column() == 5)
    {
        int value = index.model()->data(index, Qt::EditRole).toInt();
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->setValue(value);
    }
}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.column() == 0 || index.column() == 2 || index.column() == 3 || index.column() == 6)
    {
        QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
        QString value = lineEdit->text();
        model->setData(index, value, Qt::EditRole);
    }
    else if(index.column() == 1 || index.column() == 4 || index.column() == 5)
    {
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->interpretText();
        int value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    }
}

void Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
