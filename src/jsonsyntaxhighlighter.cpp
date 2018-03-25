/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/
#include "jsonsyntaxhighlighter.h"

#include <QRegExp>
#include <QDebug>
#include <QTextCharFormat>
#include <QTextDocument>

JsonSyntaxHighlighter::JsonSyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
   HighlightingRule rule;

   // numbers
   rule.pattern = QRegExp("([-0-9.]+)(?!([^\"]*\"[\\s]*\\:))");
   rule.format.setForeground(QColor("#ff00ff"));
   rules.append(rule);

   // key
   rule.pattern = QRegExp ("(\"[^\"]*\")");
   rule.format.setForeground(QColor("#2f5ccb"));
   rules.append(rule);

   // value
   rule.pattern = QRegExp(":\\s*([\"](?:[^\"])*[\"])");
   rule.format.setForeground(QColor("#aa0000"));
   rules.append(rule);

   // reserved words
   rule.pattern = QRegExp("(true|false|null)(?!\"[^\"]*\")");
   rule.format.setForeground(QColor("#aaaa00"));
   rules.append(rule);
}

void JsonSyntaxHighlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, rules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);

        while (index >= 0) {
            index = expression.pos(1);
            int length = expression.cap(1).length();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
}
