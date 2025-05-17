# Aufgabe 4

## Virtuelle Adresse 12300
VPN = 12300 ÷ 4096 = 3 (ganzzahlig)
Offset = 12300 mod 4096 = 12300 - 3×4096 = 12300 - 12288 = 12
VPN=3 → Frame = 4 (laut Tabelle)
Physische Adresse = 4 × 4096 + 12 = 16384 + 12 = 16396

## Virtuelle Adresse 16384
VPN = 16384 ÷ 4096 = 4
Offset = 0
VPN=4 → Frame = 3
Physische Adresse = 3 × 4096 + 0 = 12288 + 0 = 12288

## Virtuelle Adresse 32800
VPN = 32800 ÷ 4096 = 8
Offset = 32800 - 8×4096 = 32800 - 32768 = 32
VPN=8 → Frame = 7
Physische Adresse = 7 × 4096 + 32 = 28672 + 32 = 28704
