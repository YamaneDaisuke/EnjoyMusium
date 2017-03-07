module case(){
difference(){
translate([0,0,23/2])cube([95+6+2,72+6+2+2.5,20],center=true);
translate([0,0,23/2+1.5])cube([95+3,72+3+2.5,20],center=true);

translate([24.7,-72/2-3,5+4])
union(){
rotate([90,0,0]) cylinder(r=4,h=5,center=true);
translate([0,0,15/2]) cube([8,5,15],center=true);
}//union

translate([-(47.5-40),72/2+3,5+4])
union(){
translate([+(27-4),0,0])rotate([90,0,0]) cylinder(r=5,h=5,center=true);
translate([-(27-4),0,0])rotate([90,0,0]) cylinder(r=5,h=5,center=true);
cube([27*2-8,5,10],center=true);
}//union
}//diffrence
}//module

case();


