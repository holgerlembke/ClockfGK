/*
    Gehäuseteile für
    
        clockLCD2004 Uhr 
    
    Drei Anschraubteile
         
*/

$fn = $preview ? 20 : 200;

// allg. Dicke der Platte
bh = 8.0;

// Standbogen
bogenda = 68.0;
bogendi = 55.0;

// LCD
lcdlochab = 55.0;
lcdlochdmi = 3.2;
lcdlochdma = bh;
lcdlochl=bh+2.0;
lcdlochl2 = 10.0;     // Überstand auf der Seite
lcdlochofs = 17.0;
lcdtlen = 72.0;
lcdofsx = 12.2;
lcdofsy = 24.90;

pcbabs=(19.5+26.0)/2.0;
pcbha = 24.0;
pcbhb = 11.0;
pcbofsx = -21.0;
pcbofsy = 24.0;


// 0, 1, 2 für die drei Teile
zusammenbau(0);
translate([28,56,0]) rotate([0,0,-90])  zusammenbau(1);
translate([-25,90,0]) rotate([0,0,180]) zusammenbau(2);

//------------------------------------------------------------------------------------
module zusammenbau(part) {
    difference() {
        union() {
            bogen();
            if (part!=1) {
                lcdhalter();
            }
            if (part!=2) {
                pcbhalter();
            }
        }
        if (part!=2) {
            union() {
                translate([pcbofsx,pcbofsy,0]) {
                    translate([0,-50,0]) rotate([-90,-50,0]) cylinder(h=150,d=lcdlochdmi);
                    translate([pcbabs,-50,0]) rotate([-90,0,0]) cylinder(h=150,d=lcdlochdmi);
                }
            }
        }
    }
}

//------------------------------------------------------------------------------------
module pcbhalter() {
    translate([pcbofsx,pcbofsy,0])
    difference() {
        union() {
            translate([0,-(pcbha-pcbhb),0]) rotate([-90,0,0]) cylinder(h=pcbha,d=bh);
            translate([pcbabs,0,0]) rotate([-90,0,0]) cylinder(h=pcbhb,d=bh);
        }
        union() {
            rotate([-90,0,0]) cylinder(h=pcbha,d=lcdlochdmi);
            translate([pcbabs,0,0]) rotate([-90,0,0]) cylinder(h=pcbhb,d=lcdlochdmi);
        }
    }
}

//------------------------------------------------------------------------------------
module lcdhalter() {
    translate([lcdofsx,lcdofsy,-bh/2])
    difference() {
        union() {
            cube([bh,lcdtlen,bh]);
            translate([-(lcdlochl-bh)/2,lcdlochofs,bh/2]) rotate([0,90,0]) cylinder(h=lcdlochl+lcdlochl2,d=lcdlochdma);
            translate([-(lcdlochl-bh)/2,lcdlochofs+lcdlochab,bh/2]) rotate([0,90,0]) cylinder(h=lcdlochl+lcdlochl2,d=lcdlochdma);
        }
        union() {
            translate([-(lcdlochl-bh)/2,lcdlochofs,bh/2]) rotate([0,90,0]) cylinder(h=lcdlochl+lcdlochl2,d=lcdlochdmi);
            translate([-(lcdlochl-bh)/2,lcdlochofs+lcdlochab,bh/2]) rotate([0,90,0]) cylinder(h=lcdlochl+lcdlochl2,d=lcdlochdmi);
        }
    }
}

//------------------------------------------------------------------------------------
module bogen() {
    translate([0,0,-bh/2])
    intersection() {
        difference() {
            cylinder(h=bh,d=bogenda);
            cylinder(h=bh,d=bogendi);
        }
        translate([-bogenda/2.0,0,0]) cube([bogenda,bogenda,bh]);
    }
}

