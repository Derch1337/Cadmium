#pragma once



struct CGlobalVarsBase_t
{
    float flRealTime;                // +0x00
    int flFrameCount;            // +0x04
    float flAbsFrameTime;            // +0x08
    float flCurtime;                // +0x0C
    float flFrameTime;            // +0x10
    int maxClients;                // +0x14
    int tickcount;                // +0x18
    float flIntervalTick;            // +0x1C
    float flInterAmount;            // +0x20
    int simTicksThisFrame;        // +0x24
    int networkProtocol;        // +0x28
};