﻿#include "stdafx.h"
#include "qdialogs.h"
#include <QMessageBox>


//////////////////////////////////////////////////////////////////////


QInputOctalDialog::QInputOctalDialog(QWidget *parent, const QString & title, const QString & prompt, quint16 * value)
    : QDialog(parent, nullptr)
{
    m_result = value;

    char buffer[8];
    PrintOctalValue(buffer, *value);

    setWindowTitle(title);
    resize(340, 120);
    m_label.setText(prompt);
    m_layout.addWidget(&m_label);
    m_edit.setText(buffer);
    m_edit.selectAll();
    m_layout.addWidget(&m_edit);
    m_layout.addWidget(&m_spacer);
    m_buttons.setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QObject::connect(&m_buttons, SIGNAL(rejected()), this, SLOT(reject()));
    QObject::connect(&m_buttons, SIGNAL(accepted()), this, SLOT(accept()));
    m_layout.addWidget(&m_buttons);
    setLayout(&m_layout);
}

void QInputOctalDialog::accept()
{
    quint16 value;
    if (! ParseOctalValue(m_edit.text().toLatin1().data(), &value))
    {
        QMessageBox::warning(this, nullptr, "Please enter correct octal value.");
        return;
    }

    *m_result = value;
    QDialog::accept();
}


//////////////////////////////////////////////////////////////////////


QAboutDialog::QAboutDialog(QWidget * parent)
    : QDialog(parent, nullptr)
{
    setWindowTitle(tr("About"));

    m_topLabel.setText(tr("BKBTL Qt Version 1.0\nCopyright (C) 2009-2020"));
    m_linkLabel.setText(tr("<a href=\"https://github.com/nzeemin/bkbtl-qt\">https://github.com/nzeemin/bkbtl-qt</a>"));
    m_authorsLabel.setText(tr("Author:\r\nNikita Zimin (nzeemin@gmail.com)"));
    m_thanksLabel.setText(tr("Special thanks to:\nAlexey Kisly"));
    m_bottomLabel.setText(tr("Build date:\t%1 %2\nQt version:\t%3").arg(__DATE__).arg(__TIME__).arg(QT_VERSION_STR));

    m_linkLabel.setOpenExternalLinks(true);

    setMinimumSize(260, 320);

    m_layout.addWidget(&m_topLabel);
    m_layout.addWidget(&m_linkLabel);
    m_layout.addWidget(&m_authorsLabel);
    m_layout.addWidget(&m_thanksLabel);
    m_layout.addWidget(&m_bottomLabel);
    m_buttons.setStandardButtons(QDialogButtonBox::Ok);
    QObject::connect(&m_buttons, SIGNAL(accepted()), this, SLOT(accept()));
    m_layout.addWidget(&m_buttons);
    setLayout(&m_layout);
}


//////////////////////////////////////////////////////////////////////
