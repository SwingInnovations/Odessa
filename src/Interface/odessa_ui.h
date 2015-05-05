#ifndef ODESSA_UI_H
#define ODESSA_UI_H

#include "QSettings"

class Odessa_UI
{
public:
    Odessa_UI();
    ~Odessa_UI();
    double getUI_Scale();
public slots:
    void setUIScale(double);
private:
    double m_uiScale;
    void writePrefs();
    void readPrefs();
};
Q_DECLARE_METATYPE(Odessa_UI);

#endif // ODESSA_UI_H
