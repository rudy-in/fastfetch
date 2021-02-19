#include "fastfetch.h"

void ffPrintBattery(FFstate* state)
{
    int scanned;

    FILE* fullFile = fopen("/sys/class/power_supply/BAT0/charge_full", "r");
    if(fullFile == NULL)
    {
        if(state->showErrors)
            ffPrintError(state, "Battery", "fopen(\"/sys/class/power_supply/BAT0/charge_full\", \"r\") == NULL");
        return;
    }
    uint32_t full;
    scanned = fscanf(fullFile, "%u", &full);
    if(scanned != 1)
    {
        if(state->showErrors)
            ffPrintError(state, "Battery", "fscanf(fullFile, \"%u\", &full) != 1");
        return;
    }
    fclose(fullFile);

    FILE* nowFile = fopen("/sys/class/power_supply/BAT0/charge_now", "r");
    if(nowFile == NULL)
    {
        if(state->showErrors)
            ffPrintError(state, "Battery", "fopen(\"/sys/class/power_supply/BAT0/charge_now\", \"r\") == NULL");
        return;
    }
    uint32_t now;
    scanned = fscanf(nowFile, "%u", &now);
    if(scanned != 1)
    {
        if(state->showErrors)
            ffPrintError(state, "Battery", "fscanf(nowFile, \"%u\", &now) != 1");
        return;
    }
    fclose(nowFile);

    FILE* statusFile = fopen("/sys/class/power_supply/BAT0/status", "r");
    if(statusFile == NULL)
    {
        if(state->showErrors)
            ffPrintError(state, "Battery", "fopen(\"/sys/class/power_supply/BAT0/status\", \"r\") == NULL");
        return;
    }
    char status[256];
    scanned = fscanf(statusFile, "%s", status);
    if(scanned != 1)
    {
        if(state->showErrors)
            ffPrintError(state, "Battery", "fscanf(statusFile, \"%u\", &status) != 1");
        return;
    }
    fclose(statusFile);

    uint32_t percentage = (now / (double) full) * 100;

    ffPrintLogoAndKey(state, "Battery");
    printf("%u%% [%s]\n", percentage, status);
}