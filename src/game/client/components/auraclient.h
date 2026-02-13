#ifndef GAME_CLIENT_AURACLIENT_H
#define GAME_CLIENT_AURACLIENT_H

class CAuraClient {
public:
    // Настройки Visual
    static bool m_UpdateFrozenSkin;
    static bool m_ShowPingCircle;
    static bool m_HideNameplatesSpec;
    static bool m_ShowSkinNames;
    static bool m_FreezeStars;
    static bool m_ColorFrozenTees;
    static bool m_HammerRotate;
    static bool m_WhiteFeet;
    static bool m_HookHitGlow;  // <<< НОВАЯ СТРОКА
    
    // Настройки HUD
    static bool m_ShowScreenCenter;
    static bool m_ShowPosAngle;
    static bool m_ShowCursorSpec;
    static bool m_ShowLastAlive;
    
    // Настройки Input
    static bool m_FastInputs;
    static bool m_ExtraTick;
    static bool m_OldMousePrecision;
    
    // Anti Latency
    static int m_PredictionMargin;
    static bool m_RemovePredictionFrozen;
    
    // Tile Outlines
    static bool m_ShowOutlines;
    static bool m_OutlinesOnlyEntities;
    static bool m_OutlineFreeze;
    static bool m_OutlineWalls;
};

#endif