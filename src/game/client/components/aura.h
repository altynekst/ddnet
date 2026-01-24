#ifndef GAME_CLIENT_COMPONENTS_HAX_H
#define GAME_CLIENT_COMPONENTS_HAX_H

#include <game/client/component.h>

class CHax : public CComponent
{
private:
    // Переменная для отслеживания времени (для радужного эффекта)
    float m_RainbowTime; 
    // Флаг для включения/отключения радуги
    bool m_RainbowEnabled; 

public:
    CHax();

    // Переопределение методов
    virtual void OnInit();
    virtual void OnRender(); // Теперь он нам нужен для изменения цвета
    virtual void OnConsoleInit(); // Для регистрации команды в консоли

    // Кастомная функция для включения/отключения радуги
    void ToggleRainbow(bool Enable);
};

#endif