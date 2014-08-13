// Gmsh project created on Wed Aug  7 12:26:40 2013

h = 30;	// Height of the elliptic cylinder
a = 37.5;
b = 75;
p = 282.84;	// period
lc1 = 10;
lc2 = 100;
L1 = 110;	  // Thickness of the coating
L2 = 1390;  // Height of the 1st block in the substrate
L3 = 10000; // Height of the 2nd block in the substrate

// ------------------------------------------------------------------------
// Points
// ------------------------------------------------------------------------
// Elliptic cylinder
Point(1) = {0, 0, 0, lc1};
Point(2) = {a, 0, 0, lc1};
Point(3) = {0, b, 0, lc1};
Point(4) = {-a, 0, 0, lc1};
Point(5) = {0, -b, 0, lc1};
Point(6) = {0, 0, h, lc1};
Point(7) = {a, 0, h, lc1};
Point(8) = {0, b, h, lc1};
Point(9) = {-a, 0, h, lc1};
Point(10) = {0, -b, h, lc1};

// coating top
Point(11) = {p/2, p/2, 0, lc1};
Point(12) = {-p/2, p/2, 0, lc1};
Point(13) = {-p/2, -p/2, 0, lc1};
Point(14) = {p/2, -p/2, 0, lc1};

// Substrate/coating
Point(15) = {p/2, p/2, -L1, lc1};
Point(16) = {-p/2, p/2, -L1, lc1};
Point(17) = {-p/2, -p/2, -L1, lc1};
Point(18) = {p/2, -p/2, -L1, lc1};

// Substrate middle
Point(19) = {p/2, p/2, -L1-L2, lc2};
Point(20) = {-p/2, p/2, -L1-L2, lc2};
Point(21) = {-p/2, -p/2, -L1-L2, lc2};
Point(22) = {p/2, -p/2, -L1-L2, lc2};

// Substrate bottom
Point(23) = {p/2, p/2, -L1-L2-L3, lc2};
Point(24) = {-p/2, p/2, -L1-L2-L3, lc2};
Point(25) = {-p/2, -p/2, -L1-L2-L3, lc2};
Point(26) = {p/2, -p/2, -L1-L2-L3, lc2};

// ------------------------------------------------------------------------
// Lines
// ------------------------------------------------------------------------
// Elliptic cylinder
Ellipse(1) = {2, 1, 2, 3};
Ellipse(2) = {3, 1, 4, 4};
Ellipse(3) = {4, 1, 4, 5};
Ellipse(4) = {5, 1, 2, 2};
Ellipse(5) = {7, 6, 7, 8};
Ellipse(6) = {8, 6, 9, 9};
Ellipse(7) = {9, 6, 9, 10};
Ellipse(8) = {10, 6, 7, 7};
Line(9) = {2, 7};
Line(10) = {3, 8};
Line(11) = {4, 9};
Line(12) = {5, 10};

// Coating top
Line(13) = {11, 12};
Line(14) = {12, 13};
Line(15) = {13, 14};
Line(16) = {14, 11};

// Substrate/coating
Line(17) = {15, 16};
Line(18) = {16, 17};
Line(19) = {17, 18};
Line(20) = {18, 15};

// Substrate middle
Line(21) = {19, 20};
Line(22) = {20, 21};
Line(23) = {21, 22};
Line(24) = {22, 19};

// Substrate bottom
Line(25) = {23, 24};
Line(26) = {24, 25};
Line(27) = {25, 26};
Line(28) = {26, 23};

// Substrate vertical lines (coating)
Line(29) = {11, 15};
Line(30) = {12, 16};
Line(31) = {13, 17};
Line(32) = {14, 18};

// Substrate vertical lines (top-middle)
Line(33) = {15, 19};
Line(34) = {16, 20};
Line(35) = {17, 21};
Line(36) = {18, 22};

// Substrate vertical lines (middle-bottom)
Line(37) = {19, 23};
Line(38) = {20, 24};
Line(39) = {21, 25};
Line(40) = {22, 26};

// ------------------------------------------------------------------------
// Surfaces
// ------------------------------------------------------------------------
Line Loop(33) = {5, 6, 7, 8};
Plane Surface(34) = {33};	// Elliptic cylinder top
Line Loop(35) = {1, 2, 3, 4};
Plane Surface(36) = {35};	// Elliptic cylinder bottom
Line Loop(37) = {9, 5, -10, -1};
Ruled Surface(38) = {37};	// Elliptic cylinder sides
Line Loop(39) = {10, 6, -11, -2};
Ruled Surface(40) = {39};
Line Loop(41) = {11, 7, -12, -3};
Ruled Surface(42) = {41};
Line Loop(43) = {12, 8, -9, -4};
Ruled Surface(44) = {43};

Line Loop(45) = {13, 14, 15, 16};
Plane Surface(46) = {35, 45};	// Coating top (with a hole)
Line Loop(47) = {17, 18, 19, 20};
Plane Surface(48) = {47};	// Interface b/w substrate/coating
Line Loop(49) = {21, 22, 23, 24};
Plane Surface(50) = {49};	// Substrate middle
Line Loop(51) = {25, 26, 27, 28};
Plane Surface(52) = {51};	// Substrate bottom

Line Loop(53) = {13, 30, -17, -29};
Plane Surface(54) = {53};	// Coating back
Line Loop(55) = {14, 31, -18, -30};
Plane Surface(56) = {55};	// Coating left
Line Loop(57) = {15, 32, -19, -31};
Plane Surface(58) = {57};	// Coating front
Line Loop(59) = {16, 29, -20, -32};
Plane Surface(60) = {59};	// Coating right

Line Loop(61) = {17, 34, -21, -33};
Plane Surface(62) = {61};	// Substrate back (top-middle)
Line Loop(63) = {18, 35, -22, -34};
Plane Surface(64) = {63};	// Substrate left (top-middle)
Line Loop(65) = {19, 36, -23, -35};
Plane Surface(66) = {65};	// Substrate front (top-middle)
Line Loop(67) = {20, 33, -24, -36};
Plane Surface(68) = {67};	// Substrate right (top-middle)

Line Loop(69) = {21, 38, -25, -37};
Plane Surface(70) = {69};	// Substrate back (middle-bottom)
Line Loop(71) = {22, 39, -26, -38};
Plane Surface(72) = {71};	// Substrate left (middle-bottom)
Line Loop(73) = {23, 40, -27, -39};
Plane Surface(74) = {73};	// Substrate front (middle-bottom)
Line Loop(75) = {24, 37, -28, -40};
Plane Surface(76) = {75};	// Substrate right (middle-bottom)

// Force mesh of the substrate sides to match the opposite side
Periodic Surface(58) {-15, 31, 19, -32} = (54) {13, 30, -17, -29}; // Coating back-front
Periodic Surface(60) {-16, 32, 20, -29} = (56) {14, 31, -18, -30}; // Coating left-right
Periodic Surface(66) {-19, 35, 23, -36} = (62) {17, 34, -21, -33}; // Substrate (top-middle) back-front
Periodic Surface(68) {-20, 36, 24, -33} = (64) {18, 35, -22, -34}; // Substrate (top-middle) left-right
Periodic Surface(74) {-23, 39, 27, -40} = (70) {21, 38, -25, -37}; // Substrate (middle-bottom) back-front
Periodic Surface(76) {-24, 40, 28, -37} = (72) {22, 39, -26, -38}; // Substrate (middle-bottom) left-right

// ------------------------------------------------------------------------
// Volumes
// ------------------------------------------------------------------------
Surface Loop(1) = {40, 38, 44, 42, 34, 36};
Volume(1) = {1};	// Elliptic cylinder
Surface Loop(2) = {36, 46, 54, 56, 58, 60, 48};
Volume(2) = {2};	// Coating
Surface Loop(3) = {48, 62, 64, 66, 68, 70, 72, 74, 76, 52};
Volume(3) = {3};	// Substrate (top-middle-bottom)

// ------------------------------------------------------------------------
// Physical groups
// ------------------------------------------------------------------------
Physical Surface(1) = {34};	// Elliptical cylinder top
Physical Surface(2) = {36};	// Elliptical cylinder bottom
Physical Surface(3) = {44, 38, 40, 42};	// Elliptical cylinder side
Physical Surface(4) = {46};	// Coating top
Physical Surface(5) = {48};	// Interface b/w coating and substrate
Physical Surface(6) = {52};	// Substrate bottom

// Coating sides
Physical Surface(8) = {54};	// back
Physical Surface(9) = {56};	// left
Physical Surface(10) = {58};	// front
Physical Surface(11) = {60};	// right

// Substrate sides top
Physical Surface(12) = {62};	// back
Physical Surface(13) = {64};	// left
Physical Surface(14) = {66};	// front
Physical Surface(15) = {68};	// right

// Substrate sides bottom
Physical Surface(16) = {70};	// back
Physical Surface(17) = {72};	// left
Physical Surface(18) = {74};	// front
Physical Surface(19) = {76};	// right

// Volumes
Physical Volume(1) = {1};	// Elliptical cylinder
Physical Volume(2) = {2};	// Substrate
Physical Volume(3) = {3};	// Substrate
