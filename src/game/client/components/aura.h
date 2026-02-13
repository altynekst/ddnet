#ifndef GAME_CLIENT_COMPONENTS_AURA_H
#define GAME_CLIENT_COMPONENTS_AURA_H

#include <game/client/component.h>

class CAura : public CComponent
{
private:
    // Переменная для отслеживания времени (для радужного эффекта)
    float m_RainbowTime; 
    // Флаг для включения/отключения радуги
    bool m_RainbowEnabled; 

public:
    CAura();

    // Переопределение методов
    virtual void OnInit();
    virtual void OnRender(); // Для изменения цвета/эффектов
    virtual void OnConsoleInit(); // Для регистрации команды в консоли

    // Функция для включения/отключения радуги
    void ToggleRainbow(bool Enable);
};

#endif