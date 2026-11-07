# Journal-Reference-Manager
# Journal Reference Manager

A C++ application developed using the Qt Framework for managing academic journal article references. The application demonstrates Qt's Model-View architecture through data management, sorting, filtering, input validation and dynamic visual formatting.

## Features

- Article Management: Add and remove journal article references.
- Tabular Data Presentation: Display article records using `QTableView` and `QStandardItemModel`.
- Sorting: Sort article records by any column.
- Filtering: Search records using case-insensitive regular expressions and select the field to search.
- Input Validation: Validate user input using Qt's regular expression validators.
- Publication Year Validation: Check publication years against the current calendar year.
- Dynamic Row Highlighting: Automatically colour records according to their publication age:
  - Red: Publications older than 10 years.
  - Green: Publications within the last 5 years.
  - White: Publications between 6 and 10 years old.
- Editable Records: Modify existing article information directly within the table.

## Article Information

Each journal reference contains the following fields:

Author - Article Author |
Year - Year of Publication |
Title - Article title |
Journal - Name of the journal |
Volume - Journal volume number |
Issue - Journal issue number |
Pages - Article page range 


## Technologies Used

- C++
- Qt Framework
- Qt Widgets
- Qt Model-View Programming
- QStandardItemModel
- QSortFilterProxyModel
- QTableView
- QRegularExpression

## Usage

1. Enter the article information into the corresponding input fields.
2. Select **Add** to insert the reference into the table.
3. Click a column header to sort the records by that field.
4. Select a field from the filtering dropdown.
5. Enter a search expression and click **Find** to filter the displayed records.
6. Click **Reset** to clear the filter and display all records.
7. Select a record and click **Remove** to delete it.
8. Double-click a table cell to edit its contents.

## Implementation Notes

The application uses Qt's Model-View architecture, separating the underlying article data model from its visual presentation. A `QSortFilterProxyModel` provides sorting and filtering functionality without directly modifying the source model.

Publication-age highlighting is calculated dynamically using the system's current calendar year.

## Development Context

Originally developed as part of the COS3711 Advanced Programming module at the University of South Africa (UNISA).

The project demonstrates practical application of Qt/C++ programming, particularly model-view programming, widget development, signal-slot connections and data validation.
