// Copyright (c) 2011-2013 The Testcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef Testcoin_QT_QVALUECOMBOBOX_H
#define Testcoin_QT_QVALUECOMBOBOX_H

#include <QComboBox>
#include <QVariant>

/* QComboBox that can be used with QDataWidgetMapper to select ordinal values from a model. */
class QValueComboBox : public QComboBox
{
    Q_OBJECT

    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged USER true)

public:
    explicit QValueComboBox(QWidget *parent = 0);

    QVariant value() const;
    void setValue(const QVariant &value);

    /** Specify model role to use as ordinal value (defaults to Qt::UserRole) */
    void setRole(int role);

signals:
    void valueChanged();

private:
    int role;

private slots:
    void handleSelectionChanged(int idx);
};

#endif // Testcoin_QT_QVALUECOMBOBOX_H