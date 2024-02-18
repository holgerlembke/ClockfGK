# Programmer Wiring

Configure UART to 3.3 V!

```
---------+
         !            \
    5V o !  ---------T \--------> 5 V
         !
    Tx o !  --------------------> Rx 
         !
    Rx o !  --------------------> Tx
         !            \
   Io0 o !  ---------T \--o-----> Gnd   
         !                |
   Gnd o !  --------------o
         !                | 
   Gnd o !  ---------------
         !
---------+
```
Configure UART to 3.3 V!

See https://github.com/maarten-pennings/303WIFILC01/blob/main/1-pcbnets/Schematic_303WIFILC01.png for schematic and details. It would work
without the Io0 switch (press and hold S1 button), but this is way more convinient.


# Buyers Guide

* the clock modul is confusingly named something like "Nixie Tube Wifi Clock Modul 0,8 Zoll"
* Programmer PCB is 2 cm x 8 cm with 6 rows x 28 holes
* Pogo-Pins are named P75-E2 / P75-E3
* Switches are Mini Push Button 8 mm x 8 mm Self Locking
* UART modul is "Ch340g ch340e modul usb ttl". Look out for those that can do 3.3 V and 5 V by jumper. You need 3.3 V!
* Clamp is a Wolfcraft FZR 3016000
