/*
    Gehäuseteile für
    
        st7567s Uhr 
    
    ein Teil
    
    Platte B ist eine 30 mm x 44 mm Prototyp-PCB aus einer 
    3 cm x 7 cm Platte geschntten. Gibts bei Aliexpress.
    
    Löcher sind aufgebohrt auf 3 mm, 8 und 15 Löcher auseinander.
    
    Am besten, dieses Ding ausdrucken und ausprobieren!
 
    Zum Verschrauben:
       -- 4 x M3 x 14 mit Mutter 
       -- 4 x M2 x 12 mit Mutter
       
    zum Verbinden
       -- 4 Pin Header male/female    
         
*/

$fn = $preview ? 20 : 200;


/*
         +=================================+
         |A                     +===========+                           A|
         |                       |  B                    B  |                               |
         |                       |                            |                               |
         |                       |                            |                               |
         |                       |                            |                               |
         |                       |                            |                               |
         |                       |                            |                               |
         |                       |                            |                               |
         |                       |                            |                               |
         |                       |                            |                               |
         |                       |                            |                               |
         |                       |                            |                               |
         |                       |                            |                               |
         |                       |  B                    B  |                               |
         |A                    +===========+                            A|
         +=================================+
*/


// Loch B
lBdmi = 3.2;
lBdma = 7.3;
lBx = (7*2.54);
lBy = (14*2.54);
lBh = 5.0;
lBofsx = 0.0;
lBofsy = -0.0;

// Loch A
lAdmi = 2.2;
lAdma = 7.5;
lAx = (53.5+48.5)/2.0;
lAy = (42.9+37.9)/2.0;
lAh =  lBh + 11 + 1.5;

// Schraube für Loch A, M2 x 10, Mutter da = 4.4
// Senkung von unten ins Säule
lAIh = lAh - 6.0;
IAIdm = 5.1;

// Platte
lPx = lAx + 10.0;
lPy = lAy + 10.0;
lPd = 5.0;
// Innenaussparung wg. Material sparen
lPxl = lPx - 10.0;
lPyl = lPy - 23.0;

// Senkung für Schraubenköpfe
dmh = 3.0;
dmsk = 6.2;
dd = 1.0;

difference() {
    union() {
        translate([lBofsx,lBofsy,0])
        for (x=[-1:2:1]) {
            for (y=[-1:2:1]) {
                translate([x*lBx/2.0,y*lBy/2.0,0]) bodenplatteFuss(lBdma,lBh,dd);
            }
        }
        for (x=[-1:2:1]) {
            for (y=[-1:2:1]) {
                translate([x*lAx/2.0,y*lAy/2.0,0]) bodenplatteFuss(lAdma,lAh,dd);
            }
        }
        translate([-lPx/2.0,-lPy/2.0,-lPd]) cube([lPx,lPy,lPd]);
    }
    union() {
        translate([lBofsx,lBofsy,0])
        for (x=[-1:2:1]) {
            for (y=[-1:2:1]) {
                translate([x*lBx/2.0,y*lBy/2.0,-20]) cylinder(h=lBh+50,d=lBdmi);
                translate([x*lBx/2.0,y*lBy/2.0,-lPd]) cylinder(h=dmh,d=dmsk);
            }
        }
        for (x=[-1:2:1]) {
            for (y=[-1:2:1]) {
                translate([x*lAx/2.0,y*lAy/2.0,-20]) cylinder(h=lAh+50,d=lAdmi);
                translate([x*lAx/2.0,y*lAy/2.0,-lPd]) cylinder(h=dmh,d=dmsk);
                translate([x*lAx/2.0,y*lAy/2.0,-lPd]) cylinder(h=lAIh+lPd,d=IAIdm);
            }
        }
        for (x=[-1:1:1]) {
            for (y=[-1:1:1]) {
                translate([x*18,y*12,-10]) cylinder(d=10,h=20);                
            }
        }

        translate([-lPxl/2.0+lBofsx,-lPyl/2.0+lBofsy,-lPd-1]) cube([lPxl,lPyl,lPd+2]);
    }
}    

module bodenplatteFuss(da, hs, dd) {
    cylinder(d=da,h=hs);
    cylinder_to_plate(r1=da/2.0,r2=da/2.0+dd,h=dd);
}

//https://reprap.org/forum/read.php?247,205920
module torus(r1, r2, h, center=false) {
    torus_pipe_r=(r2-r1)/2;
    translate([0,0,center?0:h/2])
    rotate_extrude(convexity = 10)
    translate([r2-torus_pipe_r, 0, 0])
    scale([1,1/(torus_pipe_r*2)*h,1])
    circle(r = torus_pipe_r);
}

//https://reprap.org/forum/read.php?247,205920
module cylinder_to_plate(r1,r2, h, center=false) {
    translate([0,0,center?-h/2:0])
    difference() {
        difference() {
            cylinder(h=h,r1=r2,r2=r2);
            cylinder(h=h,r1=r1,r2=r1);
        }
        torus(r1=r1, r2=r2+r2-r1,h=h*2);
    }
}

