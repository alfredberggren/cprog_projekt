# CPROG Projekt (GlobuleGobble)

Spelmotor skriven med c++ och SDL2, samt ett enkelt spel som tillämpar spelmotorn.

## Projektmedlemmar

Alfred Berggren<br/>
Kristian Remnelius<br/>
Jesper Nilsson<br/>

## Förutsättningar

SDL2 måste vara installerat på datorn som bygger spelet och spelmotorn.<br/>
Katalogen resources/ måste finnas under katalogen 'build/debug/', alltså samma katalog där filen 'play' finns efter build OM cwd är 'build/debug/' när spelet körs.<br/>
Om cwd är projektets huvudkatalog när spelet körs så räcker det med resource-katalogen i projektets huvudkatalog.<br/>

## Build

Byggs genom att köra 'make' i projektets huvudkatalog med en individuellt anpassad makefile.<br/>
* [make] - bygger spelet. Den bifogade Makefilen fungerar i nuläget på windowssystem och kan behöva anpassas ifall annat operativsystem användes.<br/>

## Körning

Spelet körs antingen från kommandotolken genom att exekvera filen 'play', under katalogen 'build/debug/'.<br/>
Spelet kan även köras från filhanteraren genom att klicka på filen.<br/>

## Testning

Spelet kan testas genom att använda pil upp och ned för att öka spelarens karaktär utan att behöva äta något. Detta gör det lätt att testa kollisionsdetektering när man är större än sina motståndare.<br/>
I kommandotolken för spelet kommer statusuppdateringar visas när entiteter skapas och frigörs för att påvisa motorns minneshantering.<br/>

## Hur man spelar

* Använd muspekaren för att styra spelaren (grön varelse). Försök att äta andra spelare (röda varelser) och mat (stillastående 'planeter') genom att styra spelaren mot dessa. Spelet har förlorats när din spelare blir uppäten av en av de röda varelserna. Man vinner spelet när man har ätit upp alla röda varelser.<br/>
* Spelaren kan endast äta objekt som är mindre än sig själv. Om man kolliderar med en fiende som är större än sig själv så förlorar man.<br/>
* När man kolliderar med ett objekt som är mindre än sig själv och 'äter upp' den, så ökar spelarens storlek med arean av objektet som åts upp.<br/>
* Ät mat (planeter) genom att kollidera med dem. Detta laddar upp spelarens boost. När man har ätit 15 planeter så kan man aktivera boost vilket ökar spelarens hastighet temporärt.<br/>
* De röda varelserna (motståndare) rör sig enligt en algoritmen i NPC.char_move(). De rör sig i huvudsak mot det närmsta objekt som är mindre än de själva, men avviker från detta mönster ifall den närmsta entiteten är större än de själva, i vilket fall de försöker rymma. Fiendernas tillstånd kan ses från vilken textur som de vid en given tidpunkt renderar (när de flyr används en textur där de ser rädda ut o.s.v.)<br/>

### Keybindings

* `[ESC] - pausar spelet`
* `[retur] - återupptar spelet efter paus`
* `[q] - avslutar spelet`
* `[PIL NED] - minskar spelarens storlek (för testning)`
* `[PIL UPP] - ökar spelarens storlek (för testning)`
* `[BLANKSTEG] - aktiverar boost om boost är tillgänglig`
