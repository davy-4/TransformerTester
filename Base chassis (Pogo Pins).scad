//----VARIABLES----
//transformer dimensions
tLength=7.87;
tWidth=5.23;
tDepth=tWidth;
tHeight=5.59;
tpinWidth=0.76;
pinSpacing=0.75
;
pinDepth=1;
//casing dimensisons
wallWidth=1;
extraPinInset=0.76;
//pogo pin dimensions
pogoDiameter=1.49;
pogoHoleDiameter=1.78;//as found by holetesting
pogoLength=3.5;//length of main body of pin
pogoPositionRatio=0.7;//where the pogo hole is positioned, 0 is on the outside of the inset, 1 is on the inside of the inset
pogoLipRadius=0.1;
pogoLipHeight=0.5;
holePadding=0.76;
pogoProtection=2.5;//eqivalent slot on the bottom for protecting the bottom of the pogo pins from damage. set to 0 to disable this, reccommended set to pogostemlength+0.5
//miscellaenious
$tol=0.01;
$fn=32;
$clear=0.4;//clearance
//==============
//DERIVED VARIABLES
//==============
//STATIC
lip=true;
numPins=3;
//calculate pin locations
//Middle of each pin can be found with 1.4+2.54*pinNumber starting at pinNumber=0 so:
basePinLoc=[1.4,3.94,6.48];//coordinates on the base trasformer
extraPinOffset=wallWidth+$clear;
pinLoc=[1.4+extraPinOffset,3.94+extraPinOffset,6.48+extraPinOffset];
//top inset for transformer flipped seating
topSlotWidth=tWidth+2*$clear;

//Casing

innerCasingLength=tLength+(2*$clear);
innerCasingWidth=tWidth+(2*$clear)-2;
innerCasingHeight=pogoLength+pogoProtection+pinDepth;

outerCasingLength=innerCasingLength+2*wallWidth;//Length of outer casing
outerCasingWidth=innerCasingWidth+2*(2*wallWidth+pogoHoleDiameter);//Depth of outer casing
outerCasingHeight=innerCasingHeight-2*$tol;//Height of outer casing
extra=0.5;
scale(10){
    difference(){
    //outside
    cube([outerCasingLength,//Length of outer casing 
        outerCasingWidth, //Depth of outer casing
        outerCasingHeight]);//Height of outer casing
        echo(outerCasingHeight)
    {
    //inner cube
    translate([(outerCasingLength)/2-innerCasingLength/2,
        outerCasingWidth/2-innerCasingWidth/2,
        -$tol]) 
        cube([
        innerCasingLength,
        innerCasingWidth, 
        innerCasingHeight]);
    //topslot
        translate([wallWidth+extra/2,outerCasingWidth/2-topSlotWidth/2,outerCasingHeight-pinDepth])
        cube([innerCasingLength-extra,topSlotWidth,pinDepth+$tol]);
    pinInset(0);
    pinInset(1);
    pinInset(2);
    //pinInset(3);}
    }
    
    pogoHoles(0,lip);
    pogoHoles(2,lip);
    pogoHoles(1,lip);
    
    
}} 

module pinInset(pinNum){
    
    width=pogoDiameter+pogoLipRadius*2+holePadding+0.1;
    //if (width<pogoLipRadius*2+pogoDiameter+holePadding){
	//width=pogoLipRadius*2+pogoDiameter+holePadding;}
    depth=outerCasingWidth+2*$tol;
    height=pinDepth;
    
    //bottominset
    translate([pinLoc[pinNum],(depth/2)-$tol,(height/2)-$tol])
        cube([width,depth,pogoProtection],center=true);
    //topinset
    translate([pinLoc[pinNum],(depth/2)-$tol,pogoLength+pogoProtection+height+$tol-height/2])
        cube([width,depth,height],center=true);
    }
module pogoHoles(pinNum,includeLip){
    pinInsetWidth=pogoDiameter+pogoLipRadius*2+holePadding;
    radius=pogoHoleDiameter/2;
    height=50;
    
    
    translate([pinLoc[pinNum],(radius+wallWidth*2*pogoPositionRatio),height/2]){
        cylinder(h=height,r=radius,center=true);
    if(includeLip){
        translate([0,0,-(height/2)+pogoProtection])
        cylinder(h=pogoLipHeight,r=pogoLipRadius,center=true);
        }}
    
    translate([pinLoc[pinNum],outerCasingWidth-(radius+wallWidth*2*pogoPositionRatio),height/2]){
        cylinder(h=height,r=radius,center=true);
        if(includeLip){
        translate([0,0,-(height/2)+pogoProtection])
        cylinder(h=pogoLipHeight,r=pogoLipRadius+pogoDiameter/2,center=true);
        }}}
    
