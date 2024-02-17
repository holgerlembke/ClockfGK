/*
    Gehäuseteile für
    
        303WifiLC01 Uhr 
    
    in Polymethylmethacrylat (PMMA, Acrylglas) - Röhre
         
*/

$fn = $preview ? 20 : 200;

rohrad = 40.0+0.4;
rohrid = 36.0 - 0.4;

dh1 = 2.0;
dh2 = 6.0;

lcdb = 26.0;
lcdh = 11.0;
lcdt = 2.0;
lcdofsx = 6.0;
lcdofsy = 0;

usbb = 12.0;
usbl = 8.0;
usbdm = 10.0;
usbofsx = -0;


deckela();
translate([rohrad+2,0,0]) deckelb();

//+++++++++++++++++++++++++++++++++++++++++++++++
module deckela() {
    difference() {
        enddeckel();
        union() {
            color("blue")
            translate([-lcdh/2.0-lcdofsx,-lcdb/2.0,dh2+dh1-lcdt]) cube([lcdh,lcdb,lcdt]);
            // usb-Loch
            color("blue")
            translate([0,0,0]) {
                translate([-usbl/2.0-usbofsx,-usbb/2.0,-2]) cube([usbl,usbb,20]);
                translate([-usbofsx,0,-2]) cylinder(d=usbdm,h=4);
            }
        }
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++
module deckelb() {
    difference() {
        enddeckel();
        union() {
            color("blue")
            translate([-lcdh/2.0+lcdofsx,-lcdb/2.0,dh2+dh1-lcdt]) cube([lcdh,lcdb,lcdt]);
        }
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++
module enddeckel() {
    difference() {
        union() {
            cylinder(h=dh1,d=rohrad);
            translate([0,0,dh1]) cylinder(h=dh2,d=rohrid);
            
            translate([-rohrad/2.0,0,0]) cube([rohrad,rohrad/2.0+1,dh2+dh1]);
        }
        union() {
            color("gray")
            union() {
                difference() {
                    translate([0,0,dh1]) cylinder(h=dh2,d=rohrad+0.3);
                    translate([0,0,dh1]) cylinder(h=dh2,d=rohrid);
                }
            }
        }
    }
}