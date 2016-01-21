/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2016 UniPro <ugene@unipro.ru>
 * http://ugene.unipro.ru
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include "system/GTClipboard.h"
#include "utils/GTThread.h"

#include <QApplication>
#include <QClipboard>
#include <QFileInfo>
#include <QMimeData>
#include <QUrl>

namespace HI {

#define GT_CLASS_NAME "GTClipboard"

#define GT_METHOD_NAME "text"
QString GTClipboard::text(GUITestOpStatus &os) {
    GTGlobals::sleep(300);

    // check that clipboard contains text
    QString clipboardText;
    class Scenario : public CustomScenario {
    public:
        Scenario(QString &_text) : text(_text){}
        void run(GUITestOpStatus &os) {
            Q_UNUSED(os);
            QClipboard *clipboard = QApplication::clipboard();

            GT_CHECK(clipboard != NULL, "Clipboard is NULL");
            const QMimeData *mimeData = clipboard->mimeData();
            GT_CHECK(mimeData != NULL, "Clipboard MimeData is NULL");

            GT_CHECK(mimeData->hasText() == true, "Clipboard doesn't contain text data");
            QString clipboardText = mimeData->text();
            text = clipboardText;
            // need to clear clipboard, UGENE will crash on close otherwise because of Qt assert
            clipboard->clear();
        }
    private:
        QString &text;
    };

    GTThread::runInMainThread(os, new Scenario(clipboardText));
    GTThread::waitForMainThread(os);
    return clipboardText;
}
#undef GT_METHOD_NAME

#define GT_METHOD_NAME "setText"
void GTClipboard::setText(GUITestOpStatus &os, QString text ){
    class Scenario : public CustomScenario {
    public:
        Scenario(const QString &_text) : text(_text){}
        void run(GUITestOpStatus &os) {
            Q_UNUSED(os);
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->clear();
            clipboard->setText(text);
        }
    private:
        QString text;
    };

    GTThread::runInMainThread(os, new Scenario(text));
    GTThread::waitForMainThread(os);
}

#undef GT_METHOD_NAME

namespace {
    QList<QUrl> toLocalQUrls(GUITestOpStatus &os, const QList<QString> &urls) {
        QList<QUrl> qurls;
        foreach (const QString &url, urls) {
            QFileInfo fi(url);
            if (fi.makeAbsolute()) {
                QString absolutePath = fi.absoluteFilePath();
                qurls.append(QUrl::fromLocalFile(absolutePath));
            } else {
                os.setError("Cannot make an absolute path");
                return qurls;
            }
        }
        return qurls;
    }
}

#define GT_METHOD_NAME "setUrls"
void GTClipboard::setUrls(GUITestOpStatus &os, const QList<QString> &urls) {
    class Scenario : public CustomScenario {
        QList<QUrl> urls;
    public:
        Scenario(const QList<QUrl> &urls) : urls(urls) {}

        void run(GUITestOpStatus &os) {
            Q_UNUSED(os);
            QMimeData *urlMime = new QMimeData();
            urlMime->setUrls(urls);

            QClipboard *clipboard = QApplication::clipboard();
            clipboard->clear();
            clipboard->setMimeData(urlMime);
        }
    };

    QList<QUrl> qurls = toLocalQUrls(os, urls);
    GTThread::runInMainThread(os, new Scenario(qurls));
    GTThread::waitForMainThread(os);
}

#undef GT_METHOD_NAME

#define GT_METHOD_NAME "clear"
void GTClipboard::clear(GUITestOpStatus &os){
    class Scenario : public CustomScenario {
    public:
        Scenario(){}
        void run(GUITestOpStatus &os) {
            Q_UNUSED(os);
            QClipboard *clipboard = QApplication::clipboard();
            clipboard->clear();
        }
    };

    GTThread::runInMainThread(os, new Scenario());
    GTThread::waitForMainThread(os);
}
#undef GT_METHOD_NAME


#undef GT_CLASS_NAME

} //namespace
