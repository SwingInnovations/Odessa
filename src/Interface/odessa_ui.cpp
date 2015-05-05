#include "odessa_ui.h"

Odessa_UI::Odessa_UI()
{
    if(m_uiScale == NULL){
        m_uiScale = 1.0;
    }else{
        readPrefs();
    }
}

double Odessa_UI::getUI_Scale(){
    return m_uiScale;
}

void Odessa_UI::setUIScale(double scale){
    m_uiScale = scale;
}

void Odessa_UI::readPrefs(){
    QSettings settings("SwingInnovations", "Odessa");
    m_uiScale = settings.value("UI_Scale").toDouble();
}

void Odessa_UI::writePrefs(){
    QSettings settings("SwingInnovations", "Odessa");
    settings.setValue("UI_Scale", m_uiScale);
}

Odessa_UI::~Odessa_UI()
{
    writePrefs();
}

