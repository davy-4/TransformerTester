//----VARIABLES----
//transformer dimensions
tLength=7.87;
tWidth=5.23;
tDepth=tWidth;
tHeight=5.59;
tpinWidth=0.76;
pinSpacing=1.5;
pinDepth=2;
//casing dimensisons
wallWidth=1;
extraPinInset=0.1;
//pogo pin dimensions
pogoDiameter=1.49;
pogoHoleDiameter=1.49;//as reccomended by datasheet
pogoLength=4;//length of main body of pin
pogoPositionRatio=0.7;//where the pogo hole is positioned, 0 is on the outside of the inset, 1 is on the inside of the inset
pogoLipRadius=1;
pogoLipHeight=0.5;
holePadding=0.1;
pogoProtection=2.5;//eqivalent slot on the bottom for protecting the bottom of the pogo pins from damage. set to 0 to disable this, reccommended set to pogostemlength+0.5
//miscellaenious
$tol=0.01;
$fn=32;
$clear=0.4;//clearance
//==============
//DERIVED VARIABLES
//==============

//Casing
innerCasingLength=tLength+(2*$clear);
innerCasingWidth=tWidth+(2*$clear);
innerCasingHeight=pogoLength+pogoProtection+pinDepth;
outerCasingLength=innerCasingLength+2*wallWidth;//Length of outer casing
outerCasingWidth=innerCasingWidth+2*(2*wallWidth+pogoHoleDiameter);//Depth of outer casing
outerCasingHeight=innerCasingHeight-2*$tol;//Height of outer casing

scale(10){
    difference(){
    //outside
    cube([outerCasingLength,//Length of outer casing 
        outerCasingWidth, //Depth of outer casing
        outerCasingHeight]);//Height of outer casing
    {
    //inner cube
    translate([outerCasingLength/2-innerCasingLength/2,
        outerCasingWidth/2-innerCasingWidth/2,
        -$tol]) 
        cube([
        innerCasingLength,
        innerCasingWidth, 
        innerCasingHeight]);
    
    pinInset(0);
    pinInset(1);
    pinInset(2);
    //pinInset(3);}
    }
    pogoHoles(0,true);
    pogoHoles(2,true);
    pogoHoles(1,true);
    
    
}}

module pinInset(pinNum){
    
    width=tpinWidth+2*$clear+holePadding;
    if (width<pogoLipRadius*2+pogoDiameter+holePadding){
	width=pogoLipRadius*2+pogoDiameter+holePadding;}
    depth=outerCasingWidth+2*$tol;
    height=pinDepth;
    xoffset=extraPinInset+pinSpacing+(pinSpacing+width)*pinNum; //how far the pin is placed from the origin along the x axis
    //bottominset
    translate([xoffset,-$tol,-$tol])
        cube([width,depth,pogoProtection]);
    //topinset
    translate([xoffset,-$tol,pogoLength+pogoProtection+height+$tol-height])
        cube([width,depth,height]);
    }
module pogoHoles(pinNum,includeLip){
    pinInsetWidth=tpinWidth+2*$clear+holePadding;
    radius=pogoHoleDiameter/2;
    height=50;
    xoffset=extraPinInset+pinSpacing+(pinSpacing+pinInsetWidth)*pinNum; //how far the pin is placed from the origin along the x axis
    
    translate([xoffset+pinInsetWidth/2,(radius+wallWidth*2*pogoPositionRatio),height/2]){
        cylinder(h=height,r=radius,center=true);
    if(includeLip){
        translate([0,0,-(height/2)+pogoProtection])
        cylinder(h=pogoLipHeight,r=pogoLipRadius,center=true);
        }}
    
    translate([xoffset+pinInsetWidth/2,outerCasingWidth-(radius+wallWidth*2*pogoPositionRatio),height/2]){
        cylinder(h=height,r=radius,center=true);
        if(includeLip){
        translate([0,0,-(height/2)+pogoProtection])
        cylinder(h=pogoLipHeight,r=pogoLipRadius,center=true);
        }}}
    