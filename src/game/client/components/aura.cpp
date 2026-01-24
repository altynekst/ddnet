#include "hax.h"
#include <engine/console.h>
#include <engine/shared/config.h> // Для доступа к настройкам
#include <base/color.h> // Для работы с цветами

// Функция-обработчик для команды консоли
static void ConToggleRainbow(IConsole::IResult *pResult, void *pUserData)
{
    CHax *pHax = (CHax *)pUserData;
    pHax->ToggleRainbow(pResult->GetInteger(0) != 0);
}

CHax::CHax()
{
    m_RainbowTime = 0.0f;
    m_RainbowEnabled = false;
}

void CHax::OnInit()
{
    // Инициализация
}

void CHax::OnConsoleInit()
{
    // Регистрируем команду в консоли
    Console()->Register("cl_rainbow", "i", CFGFLAG_CLIENT, ConToggleRainbow, this, 
        "Toggle rainbow skin effect (0=off, 1=on)");
}

void CHax::ToggleRainbow(bool Enable)
{
    m_RainbowEnabled = Enable;
    
    if (!Enable)
    {
        // Если выключаем, сбрасываем цвета на те, что были в настройках
        str_copy(g_Config.m_ClColorBody, g_Config.m_ClDefaultColorBody, sizeof(g_Config.m_ClColorBody));
        str_copy(g_Config.m_ClColorFeet, g_Config.m_ClDefaultColorFeet, sizeof(g_Config.m_ClColorFeet));
    }
    
    m_pClient->Console()->Print(IConsole::OUTPUT_CLIENT, "Hax", 
        Enable ? "Rainbow skin ENABLED." : "Rainbow skin DISABLED.");
}

void CHax::OnRender()
{
    if (!m_RainbowEnabled)
        return;

    // 1. Обновляем время
    m_RainbowTime += Client()->RenderFrameTime() * 0.5f; // Скорость смены цвета (0.5f - средняя)
    if (m_RainbowTime > 1.0f)
        m_RainbowTime -= 1.0f;

    // 2. Вычисляем новый цвет (используем HSL для плавного перехода)
    // HSLtoRGB - это функция из base/color.h
    vec3 RgbColor = HSLtoRGB(vec3(m_RainbowTime, 1.0f, 0.5f)); 

    // 3. Преобразуем RGB в формат, который использует DDNet (целое число)
    int NewColor = (int)(RgbColor.r * 255.0f) | 
                   (int)(RgbColor.g * 255.0f) << 8 | 
                   (int)(RgbColor.b * 255.0f) << 16;

    // 4. Применяем цвет к настройкам скина// Мы меняем настройки, которые отправляются на сервер
    g_Config.m_ClColorBody = NewColor;
    g_Config.m_ClColorFeet = NewColor;

    // 5. Убеждаемся, что используются кастомные цвета
    g_Config.m_ClUseCustomColor = 1;}