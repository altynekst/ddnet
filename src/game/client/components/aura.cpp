#include "aura.h"
#include <game/client/gameclient.h>
#include <engine/client/console.h>

CAura::CAura()
{
    m_RainbowTime = 0.0f;
    m_RainbowEnabled = false;
}

void CAura::OnInit()
{
    // Инициализация компонента
}

void CAura::OnConsoleInit()
{
    // Регистрируем команду в консоли
    Console()->Register("aura_rainbow", "i[enable]", CFGFLAG_CLIENT, 
        [](IConsole::IResult *pResult, void *pUserData) {
            CAura *pAura = (CAura *)pUserData;
            pAura->ToggleRainbow(pResult->GetInteger(0) != 0);
        }, this, "Toggle rainbow aura effect");
    
    Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "aura", 
        "Rainbow command registered. Use 'aura_rainbow 1' to enable.");
}

void CAura::ToggleRainbow(bool Enable)
{
    m_RainbowEnabled = Enable;
    Console()->Print(IConsole::OUTPUT_LEVEL_STANDARD, "aura", 
        Enable ? "Rainbow aura effect enabled!" : "Rainbow aura effect disabled!");
}

void CAura::OnRender()
{
    if(!m_RainbowEnabled)
        return;
    
    // Обновляем время для анимации
    m_RainbowTime += Client()->RenderFrameTime();
    
    // Создаем радужный эффект (изменение оттенка со временем)
    float Hue = fmod(m_RainbowTime * 0.5f, 1.0f); // Полный цикл за 2 секунды
    
    // Здесь можно добавить код применения эффекта к игроку
    // Например, изменение цвета тей или добавление частиц вокруг него
    // Пример: m_pClient->m_pGameClient->GetPlayerColor() = HSLA(Hue, 1.0f, 0.5f);
    
    // Для теста можно выводить в лог
    // dbg_msg("aura", "Rainbow hue: %.2f", Hue);
}