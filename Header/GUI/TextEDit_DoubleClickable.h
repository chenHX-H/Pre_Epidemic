//
// Created by chenhonxinh on 2021/12/26.
//

#ifndef PRE_EPIDEMIC_TEXTEDIT_DOUBLECLICKABLE_H
#define PRE_EPIDEMIC_TEXTEDIT_DOUBLECLICKABLE_H

#include <QTextEdit>
class TextEDit_DoubleClickable:public QTextEdit{
    Q_OBJECT
protected:
    void mouseDoubleClickEvent(QMouseEvent *e) override {
        QTextEdit::mouseDoubleClickEvent(e);
        emit onDoubleClicked();
    }
    signals:
            void onDoubleClicked();
};


#endif //PRE_EPIDEMIC_TEXTEDIT_DOUBLECLICKABLE_H
