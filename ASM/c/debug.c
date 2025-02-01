#include "debug.h"

extern bool CFG_CUSTOM_MAPS;

extern u16 play_sfx;

const static colorRGBA8_t debug_text_color_yellow = { 0xE0, 0xE0, 0x10, 0xFF };
const static colorRGBA8_t debug_text_color_red    = { 0xE0, 0x00, 0x00, 0xFF };

static warp_t dungeon_warps[] = {
    { 0x0,   "Inside the Deku Tree"        },
    { 0x4,   "Dodongo's Cavern"            },
    { 0x28,  "Inside Jabu-Jabu's Belly"    },
    { 0x169, "Forest Temple"               },
    { 0x165, "Fire Temple"                 },
    { 0x10,  "Water Temple"                },
    { 0x37,  "Shadow Temple"               },
    { 0x82,  "Spirit Temple"               },
    { 0x88,  "Ice Cavern"                  },
    { 0x98,  "Bottom of the Well"          },
    { 0x486, "Thieves' Hideout"            },
    { 0x8,   "Gerudo Training Ground"      },
    { 0x467, "Ganon's Castle"              },
    { 0x41B, "Ganon's Tower"               },
};

static warp_t overworld_warps[] = {
    { 0x443, "Kokiri Forest"               },
    { 0x11E, "Lost Woods"                  },
    { 0xFC,  "Sacred Forest Meadow"        },
    { 0x157, "Lon Lon Ranch"               },
    { 0x1FD, "Hyrule Field (Market)"       },
    { 0x181, "Hyrule Field (River)"        },
    { 0x189, "Hyrule Field (Lake)"         },
    { 0xB1,  "Market"                      },
    { 0x138, "Hyrule Castle"               },
    { 0x13A, "Outside Ganon's Castle"      },
    { 0x7A,  "Castle Courtyard"            },
    { 0x400, "Zelda's Courtyard"           },
    { 0x138, "Hyrule Castle"               },
    { 0x13A, "Outside Ganon's Castle"      },
    { 0xDB,  "Kakariko Village"            },
    { 0xE4,  "Graveyard"                   },
    { 0x13D, "Death Mountain Trail (Base)" },
    { 0x1BD, "Death Mountain Trail (Top)"  },
    { 0x14D, "Goron City"                  },
    { 0x246, "Death Mountain Crater"       },
    { 0xEA,  "Zora's River"                },
    { 0x108, "Zora's Domain"               },
    { 0x225, "Zora's Fountain"             },
    { 0x102, "Lake Hylia"                  },
    { 0x117, "Gerudo Valley"               },
    { 0x129, "Gerudo Fortress"             },
    { 0x130, "Haunted Wastelands"          },
    { 0x123, "Desert Colossus"             },
    { 0x7A,  "Castle Courtyard"            },
    { 0x400, "Zelda's Courtyard"           },
    { 0x053, "Temple of Time (Entrance)"   },
    { 0x2CA, "Temple of Time (Pedestal)"   },
};

static warp_t bosses_warps[] = {
    { 0x40F, "Gohma's Lair"                },
    { 0x40B, "King Dodongo's Lair"         },
    { 0x301, "Barinade's Lair"             },
    { 0xC,   "Phantom Ganon' Lair"         },
    { 0x305, "Volvagia's Lair"             },
    { 0x417, "Morpha's Lair"               },
    { 0x413, "Bongo Bongo's Lair"          },
    { 0x8D,  "Twinrova's Lair (Nabooru)"   },
    { 0x5EC, "Twinrova's Lair (Boss)"      },
    { 0x41F, "Ganondorf's Lair"            },
    { 0x517, "Ganon's Battle Arena"        },
};

static room_t inside_the_deku_tree_rooms[] = {
    { { -4,     0,     554  }, 32768, "Entrance"                      }, // 0
    { { -500,   400,   500  }, 57900, "Path to Slingshot"             }, // 1
    { { -1002,  400,   1000 }, 57436, "Slingshot Room"                }, // 2
    { { -198,  -845,  -285  }, 48980, "Basement"                      }, // 3
    { { -80,   -880,   660  }, 0,     "Room to Water Challenge"       }, // 4
    { { -428,  -880,   961  }, 49050, "Path Across Water"             }, // 5
    { { -1610, -760,   1075 }, 49000, "Room after Water Challenge"    }, // 6
    { { -1855, -760,   700  }, 32768, "Three-Way Room"                }, // 7
    { { -2485, -760,  -510  }, 40960, "Gold Skulltula Room"           }, // 8
    { { -614,  -1881, -388  }, 34300, "Boss Door Room"                }, // 9
    { { -651,   800,  -1    }, 49050, "Three Rising Pillars"          }, // 10
};

static room_t dodongos_cavern_rooms[] = {
    { { -3,     0,     369  }, 32768, "Entrance"                      }, // 0
    { {  1380, -1,    -325  }, 16384, "Baby Dodongo Hallway"          }, // 1
    { { -927,   0,    -1525 }, 49050, "Rising Staircase"              }, // 2
    { {  3565,  100,  -1365 }, 32768, "Lizalfos Mini-Boss"            }, // 3
    { {  2650,  100,  -2500 }, 43008, "Green Cave"                    }, // 4
    { { -1955,  531,  -650  }, 0,     "Armos Pushing Challenge"       }, // 5
    { {  1835,  411,  -1560 }, 32768, "Large Pillars Hall: Subroom"   }, // 6
    { {  7,     76,   -2057 }, 32768, "Boss Door Room"                }, // 7
    { {  880,   76,   -2785 }, 16384, "Labyrinth"                     }, // 8
    { {  1392,  531,  -316  }, 16384, "Large Pillars Hall"            }, // 9
    { {  2460,  531,  -325  }, 16384, "Jump Across One Pillar"        }, // 10
    { {  2565,  0,     250  }, 0,     "Baby Dodongo Hallway: Subroom" }, // 11
    { {  3700,  531,  -920  }, 49050, "Jump Across Two Pillars"       }, // 12
    { {  2435,  100,  -2980 }, 32768, "Green Cave: Subroom"           }, // 13
    { {  1475,  76,   -4310 }, 32768, "Labyrinth: Subroom"            }, // 14
    { { -1960, -1,    -635  }, 0,     "Rising Staircase: Subroom"     }, // 15
};

static room_t inside_jabu_jabus_belly_rooms[] = {
    { { -3,    -226,   369  }, 32768, "Entrance"                      }, // 0
    { {  0,    -320,  -1245 }, 32768, "Main Hall"                     }, // 1
    { {  0,    -340,  -2610 }, 32768, "Ruto Meeting Room"             }, // 2
    { {  231,  -1113, -3228 }, 29920, "Ruto Fallen Down Basement"     }, // 3
    { { -1355,  80,   -2140 }, 0,     "Room to Upper Main Hall"       }, // 4
    { {  750,  -320,  -1705 }, 16384, "Boss Door Room"                }, // 5
    { { -1090, -1025, -3325 }, 49152, "Giant Octo Mini-Boss"          }, // 6
    { {  6,    -340,  -4074 }, 32666, "Three-Way Fork"                }, // 7
    { {  0,    -340,  -5400 }, 32666, "North Fork Room"               }, // 8
    { {  1180, -340,  -4690 }, 16384, "East Fork Room"                }, // 9
    { { -1180, -340,  -4690 }, 49152, "West Fork Room"                }, // 10
    { {  660,  -340,  -5290 }, 32768, "North-East Fork Room"          }, // 11
    { { -660,  -340,  -5290 }, 32768, "North-West Fork Room"          }, // 12
    { { -700,  -1113, -2640 }, 55808, "Lone Room in Basement"         }, // 13
    { {  500,  -1113, -3225 }, 16384, "Boomerang Hall"                }, // 14
};

static room_t forest_temple_rooms[] = {
    { {  110,   309,   641  }, 32768, "Entrance"                      }, // 0
    { {  120,   359,  -15   }, 32768, "Entrance Hallway"              }, // 1
    { {  118,   383,  -660  }, 32768, "Elevator Hall"                 }, // 2
    { {  1500,  463,  -1440 }, 49152, "East Elevator Hall"            }, // 3
    { {  120,   470,  -2600 }, 32768, "North Elevator Hallway"        }, // 4
    { { -825,   394,  -1440 }, 49152, "West Elevator Hallway"         }, // 5
    { { -280,   827,  -3320 }, 16384, "Stalfos Mini-Boss"             }, // 6
    { {  960,   261,  -2285 }, 24576, "East Courtyard"                }, // 7
    { { -725,   259,  -2285 }, 40960, "West Courtyard"                }, // 8
    { { -1040, -236,  -1775 }, 16384, "Sewers"                        }, // 9
    { {  300,   800,  -2810 }, 49152, "Hallway Connecting Courtyards" }, // 10
    { { -1447,  383,  -1439 }, 49152, "Tall Block Pushing Hall"       }, // 11
    { { -1328,  1228, -3326 }, 16282, "Joelle's Hall"                 }, // 12
    { {  586,   827,  -3322 }, 16282, "Beth's Hall"                   }, // 13
    { {  2000,  1228, -1750 }, 0,     "Rotating Platforms Hall"       }, // 14
    { {  1979,  403,  -3404 }, 16282, "Chess Hall"                    }, // 15
    { {  1990,  493,  -1755 }, 0,     "Amy's Block Puzzle"            }, // 16
    { {  120,  -779,  -1750 }, 32768, "Boss Door Shifting Hall"       }, // 17
    { { -1810,  523,  -2045 }, 49152, "West Courtyard: Subroom"       }, // 18
    { { -1765,  1238, -3130 }, 32768, "West Twisted Hallway"          }, // 19
    { {  1765,  1228, -3325 }, 16282, "East Twisted Hallway"          }, // 20
    { { -1760,  443,  -3320 }, 0,     "West Courtyard: Fallen Room"   }, // 21
};

static room_t fire_temple_rooms[] = {
    { {  5,     0,     846  }, 32768, "Entrance"                      }, // 0
    { {  490,   200,   0    }, 16384, "Lava Cave"                     }, // 1
    { { -490,   200,   0    }, 49152, "Boss Door Hall"                }, // 2
    { { -55,    0,    -1240 }, 49152, "Entrance: Flare Dancer"        }, // 3
    { {  2989,  2060,  0    }, 49152, "Fire Slug Room"                }, // 4
    { {  2660,  2800,  0    }, 16384, "Boulder Maze"                  }, // 5
    { {  1550,  2800, -260  }, 0,     "Narrow Three-Way Bridge"       }, // 6
    { {  1580,  4000, -525  }, 0,     "Room to East Tower"            }, // 7
    { {  1580,  4400, -509  }, 0,     "East Tower"                    }, // 8
    { {  270,   2940,  190  }, 49152, "Hallway Connecting Towers"     }, // 9
    { { -640,   2940,  190  }, 49152, "Fire Wall Maze"                }, // 10
    { { -1780,  2800,  240  }, 32768, "Fire Wall Maze: Hallway"       }, // 11
    { { -2630,  4000,  160  }, 16384, "Room to West Tower"            }, // 12
    { { -2289,  4400,  19   }, 16384, "West Tower"                    }, // 13
    { { -2270,  4180, -815  }, 24576, "Hidden Stairs Room"            }, // 14
    { {  280,   0,     60   }, 32768, "Entrance: Torch Slug Hall"     }, // 15
    { {  1400,  2940, -630  }, 49152, "Fire Wall Death Room"          }, // 16
    { { -280,   0,    -830  }, 0,     "Entrance: Goron"               }, // 17
    { {  235,   0,    -940  }, 32768, "Entrance: Tile Room"           }, // 18
    { {  1560,  240,  -1590 }, 32768, "Lava Cave: Tile Room"          }, // 19
    { {  1560,  100,  -1630 }, 32768, "Lava Cave: North Goron"        }, // 20
    { {  2765,  200,   0    }, 16384, "Flaming Elevator"              }, // 21
    { {  1560,  200,   1645 }, 0,     "Lava Cave: South Goron"        }, // 22
    { {  1780,  2800, -1565 }, 32768, "Boulder Maze: Goron"           }, // 23
    { { -2715,  2840, -100  }, 57344, "Fire Wall Maze: Flare Dancer"  }, // 24
    { { -1010,  2800, -955  }, 24576, "Fire Wall Maze: Subroom"       }, // 25
};

static room_t water_temple_rooms[] = {
    { { -184,   780,   759  }, 32768, "Central Hall"                  }, // 0
    { { -180,   460,  -320  }, 0,     "Central Pillar"                }, // 1
    { { -180,  -500,   310  }, 0,     "Flooded Basement"              }, // 2
    { { -445,   0,     620  }, 49152, "Lower Level: South"            }, // 3
    { {  660,   460,  -560  }, 32768, "Mid Level: East"               }, // 4
    { { -940,   780,  -180  }, 49152, "Waterfall Room"                }, // 5
    { { -2940,  760,  -180  }, 49152, "Dragon Statues Room"           }, // 6
    { { -3120,  1060, -3820 }, 32768, "Longshot Room"                 }, // 7
    { { -1140,  60,   -1810 }, 32768, "Spinning Water Room"           }, // 8
    { { -1145,  60,   -1640 }, 0,     "Water Pillar Room"             }, // 9
    { { -930,   460,  -170  }, 49152, "Upper Level: West"             }, // 10
    { { -175,   820,  -1325 }, 32768, "Spike Trap Corridor"           }, // 11
    { { -180,   0,    -1870 }, 32768, "Rolling Boulder Room"          }, // 12
    { { -3124,  1060, -1747 }, 32666, "Room of Illusions"             }, // 13
    { { -620,   120,  -3670 }, 16384, "Stinger Room"                  }, // 14
    { { -880,   120,  -2770 }, 32768, "Three Water Pillars Room"      }, // 15
    { { -1275,  108,  -2770 }, 32768, "Rolling Boulder Subroom"       }, // 16
    { {  987,   780,   181  }, 16384, "Ruto Hall"                     }, // 17
    { {  1275,  0,     185  }, 16384, "Lower Ruto Room"               }, // 18
    { {  1275,  780,   185  }, 16384, "Upper Ruto Room"               }, // 19
    { {  660,   780,   50   }, 0,     "Mid Level: South"              }, // 20
    { { -3113,  380,  -4222 }, 4759,  "Raging Water Cave"             }, // 21
};

static room_t shadow_temple_rooms[] = {
    { { -175,  -63,   -180  }, 49152, "Room of Illusion"              }, // 0
    { { -795,  -63,   -740  }, 32768, "Room of Illusion: Room #1"     }, // 1
    { { -254,  -63,    594  }, 32768, "Entrance"                      }, // 2
    { { -2745, -1363, -150  }, 0,     "Boss Door Room"                }, // 3
    { { -2130, -63,   -400  }, 49152, "Room of Illusion: Dead Hand"   }, // 4
    { {  2880, -543,   50   }, 16384, "Beamos Corridor: Entrance"     }, // 5
    { {  3360, -543,  -500  }, 32768, "Scythe Shortcut Room"          }, // 6
    { {  3360, -543,   600  }, 0,     "Beamos Corridor: Subroom"      }, // 7
    { {  4164, -983,   1366 }, 49152, "Guillotine Hallway"            }, // 8
    { {  3780, -983,   1545 }, 0,     "Guillotine Cave"               }, // 9
    { {  1227, -1343,  3853 }, 49152, "Falling Spike Blocks Room"     }, // 10
    { {  2477, -1343,  1393 }, 32666, "Invisible Spike Room"          }, // 11
    { { -5120, -1363, -1585 }, 49152, "Giant Skull Jars Room #2"      }, // 12
    { { -4305, -1363, -2370 }, 32768, "Wooden Spike Traps Room"       }, // 13
    { {  1900, -1343,  1090 }, 49152, "Giant Skull Jars Room #1"      }, // 14
    { { -3662, -1363, -1585 }, 49152, "Invisible Maze"                }, // 15
    { {  4677, -1143,  2474 }, 32768, "Invisible Scythe Room"         }, // 16
    { { -4305, -1363, -780  }, 0,     "Sacrificial Room"              }, // 17
    { {  2480, -1203,  715  }, 32768, "Wind Fans Room"                }, // 18
    { {  4785, -1363, -125  }, 16384, "Wind Fans Subroom"             }, // 19
    { {  4390, -1363, -710  }, 32768, "Wind Fans Gibdo Hallway"       }, // 20
    { {  4387, -1363, -1486 }, 32768, "River of Death"                }, // 21
};

static room_t spirit_temple_rooms[] = {
    { {  868,  -50,    2    }, 16384, "Entrance"                      }, // 0
    { { -768,  -50,   -1    }, 49152, "Main Corridor"                 }, // 1
    { { -685,   30,   -600  }, 22528, "Main Corridor: East"           }, // 2
    { { -1445,  30,   -600  }, 43008, "Main Corridor: West"           }, // 3
    { { -1060,  40,   -1180 }, 32768, "Bombiwa Rock Room"             }, // 4
    { {  692,   480,  -838  }, 49152, "Colossus Room"                 }, // 5
    { {  100,   463,  -60   }, 16384, "Entrance Shortcut Room"        }, // 6
    { { -580,   813,  -500  }, 0,     "Colossus Room: West Corridor"  }, // 7
    { { -1050,  843,  -210  }, 49152, "Sun Face Block Pushing Room"   }, // 8
    { { -1700,  843,   530  }, 0,     "West Iron Knuckle Hallway"     }, // 9
    { { -1700,  1003,  1240 }, 0,     "West Iron Knuckle Room"        }, // 10
    { { -1000,  1003,  1475 }, 16384, "Colossus Hand Exit"            }, // 11
    { {  1570, -130,  -1660 }, 32768, "Rolling Boulder Subroom"       }, // 12
    { {  1430,  30,   -600  }, 21504, "Rolling Boulder Room"          }, // 13
    { {  680,   30,   -600  }, 43008, "Quicksand Room"                }, // 14
    { {  1126,  480,  -1281 }, 16384, "Trap Room With Mirror"         }, // 15
    { {  700,   813,  -500  }, 0,     "Colossus Room: East Corridor"  }, // 16
    { {  1150,  843,  -210  }, 16384, "Time Block Puzzle Room"        }, // 17
    { {  1787,  843,   152  }, 16282, "Armos & Sun Face Room"         }, // 18
    { {  1960,  843,   530  }, 0,     "East Iron Knuckle Hallway"     }, // 19
    { {  1960,  1003,  1240 }, 0,     "East Iron Knuckle Room"        }, // 20
    { {  1890,  843,  -480  }, 32768, "Armos & Sun Face Subroom"      }, // 21
    { {  680,   1633, -1070 }, 32768, "Triforce Corridor: Subroom"    }, // 22
    { {  930,   843,   150  }, 49152, "Moving Trap Wall"              }, // 23
    { {  680,   1543, -510  }, 32768, "Triforce Corridor"             }, // 24
    { {  268,   1733, -828  }, 49152, "Mirror Platform Room"          }, // 25
    { { -300,   1733, -830  }, 49152, "Rotating Mirror Statues Room"  }, // 26
    { { -865,   30,   -1505 }, 40960, "Main Corridor: Anubis"         }, // 27
};

static room_t ice_cavern_rooms[] = {
    { {  16,    0,     2678 }, 32768, "Entrance"                      }, // 0
    { { -50,    3,     1790 }, 32768, "Open Room #1"                  }, // 1
    { { -235,   7,     585  }, 33536, "Hallway to Room #2"            }, // 2
    { {  285,   38,    63   }, 32768, "Open Room #2"                  }, // 3
    { { -360,   18,   -350  }, 41472, "Hallway to Ice Block Puzzle"   }, // 4
    { { -720,   60,   -960  }, 49152, "Ice Block Puzzle Room"         }, // 5
    { { -1280,  150,   20   }, 0,     "Hallway to Mini-Boss"          }, // 6
    { { -1290,  280,   780  }, 8400,  "Mini-Boss Room"                }, // 7
    { {  1000,  172,  -640  }, 22000, "Hallway to Pillars"            }, // 8
    { {  662,   52,   -1656 }, 32768, "Pillars Room"                  }, // 9
    { { -810,   98,    1270 }, 8400,  "Room to Exit"                  }, // 10
    { {  740,  -34,    235  }, 14500, "Blue Fire Altar"               }, // 11
};

static room_t bottom_of_the_well_rooms[] = {
    { {  0,    -12,    117  }, 32768, "Entrance & Main Area"          }, // 0
    { { -555,  -720,  -300  }, 16384, "Bottom Pit"                    }, // 1
    { { -1650,  0,    -739  }, 49152, "Coffins Room"                  }, // 2
    { {  1140,  0,    -1339 }, 0,     "Room With Grates"              }, // 3
    { {  975,  -20,    205  }, 16384, "Dead Hand Room"                }, // 4
    { {  450,   0,    -970  }, 32768, "Invisible Floor Room"          }, // 5
    { { -415,   0,    -970  }, 32768, "Skull Wall Room"               }, // 6
};

static room_t thieves_hideout_rooms[] = {
    { {  1100, -160,  -3045 }, 16384, "Break Room"                    }, // 0
    { {  1061,  0,    -2037 }, 32768, "Shiro's Prison Cell"           }, // 1
    { { -296,   0,    -2951 }, 16384, "Ichiro's Prison Cell"          }, // 2
    { {  840,   104,  -980  }, 16384, "Kitchen"                       }, // 3
    { { -105,   0,    -335  }, 16384, "Sabooro's Prison Cell"         }, // 4
    { {  1102,  120,   30   }, 0,     "Jiro's Prison Cell"            }, // 5
};

static room_t gerudo_training_ground_rooms[] = {
    { { -61,   -160,   182  }, 32768, "Entrance"                      }, // 0
    { { -1060, -80,   -180  }, 49152, "Driftsand Fight Challenge"     }, // 1
    { { -1583, -80,   -707  }, 32768, "Hookshot Challenge"            }, // 2
    { { -1579,  160,  -2254 }, 32768, "Fake Room"                     }, // 3
    { { -689,   239,  -2751 }, 16282, "Eye Statue Challenge"          }, // 4
    { {  1440, -81,   -2480 }, 32768, "Hammer Challenge"              }, // 5
    { {  1448, -81,   -2320 }, 65434, "Lava Challenge"                }, // 6
    { {  960,  -80,   -180  }, 16384, "Lizalfos Challenge"            }, // 7
    { { -60,   -80,   -1170 }, 32768, "Central Crates Room"           }, // 8
    { {  2009, -240,  -1463 }, 16282, "Underwater Challenge"          }, // 9
    { { -1575,  159,  -3570 }, 32768, "Isolated Room"                 }, // 10
};

static room_t ganons_castle_rooms[] = {
    { { -9,     420,   2283 }, 32768, "Entrance"                      }, // 0
    { {  0,     150,   490  }, 32768, "Main Lobby"                    }, // 1
    { {  1319, -240,  -835  }, 16282, "Water Trial #1"                }, // 2
    { {  2440, -250,  -840  }, 16282, "Water Trial #2"                }, // 3
    { {  3560, -240,  -840  }, 16282, "Water Barrier"                 }, // 4
    { {  662,   150,   302  }, 5383,  "Forest Trial #1"               }, // 5
    { {  1205,  110,   1245 }, 5383,  "Forest Trial #2"               }, // 6
    { {  1825,  110,   2315 }, 5383,  "Forest Barrier"                }, // 7
    { { -2340, -240,  -840  }, 49050, "Light Trial #2"                }, // 8
    { { -1406, -240,  -840  }, 49050, "Light Trial #1"                }, // 9
    { { -2990, -240,  -840  }, 49050, "Fake Light Barrier"            }, // 10
    { { -3825, -210,  -840  }, 49050, "Light Barrier"                 }, // 11
    { {  660,   150,  -1982 }, 27385, "Shadow Trial"                  }, // 12
    { {  2155,  210,  -4570 }, 27385, "Shadow Barrier"                }, // 13
    { { -648,   150,  -1990 }, 38151, "Fire Trial"                    }, // 14
    { { -2000,  153,  -3925 }, 38151, "Fire Barrier"                  }, // 15
    { {  0,    -240,   450  }, 0,     "Deku Scrubs Area"              }, // 16
    { { -647,   150,   277  }, 60074, "Spirit Trial #1"               }, // 17
    { { -1320,  152,   650  }, 42752, "Spirit Trial #2"               }, // 18
    { { -1330,  150,   1465 }, 59904, "Spirit Barrier"                }, // 19
};

static room_t ganons_tower_rooms[] = {
    { { -340,   0,     0    }, 16282, "Lower Room: Lizalfos"          }, // 0
    { {  570,   40,    0    }, 16282, "Staircase #1"                  }, // 1
    { {  0,     260,  -325  }, 0,     "Middle Room: Stalfos"          }, // 2
    { {  0,     300,   560  }, 0,     "Staircase #2"                  }, // 3
    { {  335,   528,   0    }, 49152, "Upper Room: Iron Knuckles"     }, // 4
    { { -565,   560,   0    }, 49152, "Staircase #3"                  }, // 5
    { {  565,   800,   0    }, 16282, "Staircase #4 to Boss Door"     }, // 6
    { {  220,  -220,   980  }, 32768, "Entrance"                      }, // 7
    { {  0,     800,   440  }, 32768, "Lower Boss Lair"               }, // 8
};

static menu_category_t menu_categories[] = { { "Dungeons"     }, { "Overworld"              }, { "Bosses"         }, { "Upgrades" }, { "Progression" }, { "Switch Age" }, };
static upgrade_t       upgrades[]        = { { "Magic"        }, { "Double Defense"         }, { "Biggoron Sword" }, };

static progression_t progressions[] = {
    { "Talked Malon Castle",      EVENT,                      EVENTCHKINF_TALKED_TO_MALON_FIRST_TIME   },
    { "Got Weird Egg",            EVENT,                      EVENTCHKINF_RECEIVED_WEIRD_EGG           },
    { "Talon Woken Castle",       EVENT,                      EVENTCHKINF_TALON_WOKEN_IN_CASTLE        },
    { "Talon Woken Kakariko",     EVENT,                      EVENTCHKINF_TALON_WOKEN_IN_KAKARIKO      },
    { "Talon Returned Castle",    EVENT,                      EVENTCHKINF_TALON_RETURNED_FROM_CASTLE   },
    { "Talon Returned Kakariko",  EVENT,                      EVENTCHKINF_TALON_RETURNED_FROM_KAKARIKO },
    { "Zelda Visited",            EVENT,                      EVENTCHKINF_VISITED_ZELDA                },
    { "Zelda Fleed",              EVENT,                      EVENTCHKINF_ZELDA_FLEED_FROM_CASTLE      },
    { "Gave Zelda's Letter",      INFTABLE,                   INFTABLE_GIVEN_ZELDAS_LETTER             },
    { "Gave Letter King Zora",    EVENT,                      EVENTCHKINF_GAVE_LETTER_TO_KING_ZORA     },
    { "Opened Jabu-Jabu",         EVENT,                      EVENTCHKINF_OPENED_JABU_JABU             },
    { "Opened Door of Time",      EVENT,                      EVENTCHKINF_OPENED_DOOR_OF_TIME          },
    { "Pulled Master Sword",      EVENT,                      EVENTCHKINF_MASTER_SWORD_CS              },
    { "Learned Song of Storms",   EVENT,                      EVENTCHKINF_LEARNED_SONG_OF_STORMS       },
    { "Learned Prelude of Light", EVENT,                      EVENTCHKINF_LEARNED_PRELUDE_OF_LIGHT_CS  },
    { "Activated Scarecrow",      EVENT,                      EVENTCHKINF_SCARECROW_ACTIVATED          },
    { "Epona Obtained",           EVENT,                      EVENTCHKINF_EPONA_OBTAINED               },
    { "Race Cow Unlocked",        EVENT,                      EVENTCHKINF_HORSE_RACE_COW_UNLOCK        },
    { "Carpenters Freed",         CARPENTERS,                 EVENTCHKINF_CARPENTERS_FREE(0)           },
    { "Deku Tree Died",           EVENT,                      EVENTCHKINF_DEKU_TREE_DIED               },
    { "Got Kokiri's Emerald",     EVENT,                      EVENTCHKINF_GOT_KOKIRIS_EMERALD          },
    { "Got Goron's Ruby",         EVENT,                      EVENTCHKINF_GOT_GORONS_RUBY              },
    { "Got Zora's Sapphire",      EVENT,                      EVENTCHKINF_GOT_ZORAS_SAPPHIRE           },
    { "Cleansed Kokiri Forest",   EVENT,                      EVENTCHKINF_CLEANSED_KOKIRI_FOREST       },
    { "Cleansed Death Mountain",  EVENT,                      EVENTCHKINF_CLEANSED_DEATH_MOUNTAIN      },
    { "Cleansed Lake Hylia",      EVENT,                      EVENTCHKINF_CLEANSED_LAKE_HYLIA          },
    { "Unfrozen King Zora",       INFTABLE,                   INFTABLE_UNFROZEN_KING_ZORA              },
    { "Restored Lake Hylia",      EVENT,                      EVENTCHKINF_RESTORED_LAKE_HYLIA          },
    { "Shadow Attacks Kakariko",  EVENT,                      EVENTCHKINF_SHADOW_ATTACKS_KAKARIKO      },
    { "Fast Windmill",            EVENT,                      EVENTCHKINF_FAST_WINDMILL                },
    { "Drained Well",             EVENT,                      EVENTCHKINF_DRAINED_WELL                 },
    { "Sheik Reveal",             EVENT,                      EVENTCHKINF_SHEIK_REVEAL_CS              },
    { "Rainbow Bridge",           EVENT,                      EVENTCHKINF_CREATED_RAINBOW_BRIDGE       },
    { "Killed Gohma",             SCENE_DEKU_TREE_BOSS,       1,                                       },
    { "Killed King Dodongo",      SCENE_DODONGOS_CAVERN_BOSS, 1,                                       },
    { "Killed Barinade",          SCENE_JABU_JABU_BOSS,       1,                                       },
    { "Killed Phantom Ganon",     SCENE_FOREST_TEMPLE_BOSS,   1,                                       },
    { "Killed Volvagia",          SCENE_FIRE_TEMPLE_BOSS,     1,                                       },
    { "Killed Morpha",            SCENE_WATER_TEMPLE_BOSS,    1,                                       },
    { "Killed Bongo Bongo",       SCENE_SHADOW_TEMPLE_BOSS,   1                                        },
    { "Killed Nabooru",           NABOORU,                    5                                        },
    { "Killed Twinrova",          SCENE_SPIRIT_TEMPLE_BOSS,   3                                        },
    { "Completed Mask Quest",     MASK,                       0,                                       },
    { "Got Bottle Cucco Lady",    ITEM,                       ITEMGETINF_BOTTLE_CUCCO_LADY             },
    { "Got Pocket Egg",           ITEM,                       ITEMGETINF_POCKET_EGG                    },
    { "Got Cojiro",               ITEM,                       ITEMGETINF_COJIRO                        },
};

const static rooms_t dungeon_rooms[] = {
    { ARRAY_SIZE(inside_the_deku_tree_rooms), inside_the_deku_tree_rooms }, { ARRAY_SIZE(dodongos_cavern_rooms), dodongos_cavern_rooms    }, { ARRAY_SIZE(inside_jabu_jabus_belly_rooms), inside_jabu_jabus_belly_rooms },
    { ARRAY_SIZE(forest_temple_rooms),        forest_temple_rooms        }, { ARRAY_SIZE(fire_temple_rooms),     fire_temple_rooms        }, { ARRAY_SIZE(water_temple_rooms),            water_temple_rooms            },
    { ARRAY_SIZE(shadow_temple_rooms),        shadow_temple_rooms        }, { ARRAY_SIZE(spirit_temple_rooms),   spirit_temple_rooms      }, { ARRAY_SIZE(ice_cavern_rooms),              ice_cavern_rooms              },
    { ARRAY_SIZE(bottom_of_the_well_rooms),   bottom_of_the_well_rooms   }, { ARRAY_SIZE(thieves_hideout_rooms), thieves_hideout_rooms    }, { ARRAY_SIZE(gerudo_training_ground_rooms),  gerudo_training_ground_rooms  },
    { ARRAY_SIZE(ganons_castle_rooms),        ganons_castle_rooms        }, { ARRAY_SIZE(ganons_tower_rooms),    ganons_tower_rooms       },
};

void reset_map_select() {
    current_menu_indexes.sub_menu_index = 0;
}

static s32 warp_to_scene_index = -1;

void execute_warp() {
    z64_game.entrance_index  = z64_file.entrance_index = warp_to_scene_index;
    z64_game.scene_load_flag = 0x14;
    warp_to_scene_index      = -1;
}

void handle_map_select() {
    if (warp_to_scene_index >= 0) {
        z64_game.pause_ctxt.debugState = 0;
        if (z64_game.pause_ctxt.state == PAUSE_STATE_MAIN)
            z64_game.common.input[0].raw.pad.s = z64_game.common.input[0].pad_pressed.s = true;
        else if (z64_game.pause_ctxt.state == PAUSE_STATE_OFF)
            execute_warp();
        return;
    }
    
    if (z64_game.pause_ctxt.debugState != 4 || CFG_OPTIONS_MENU < 3)
        return;
    
    pad_t pad_pressed = z64_game.common.input[0].pad_pressed;
    
    if (pad_pressed.du || pad_pressed.dr || pad_pressed.dd || pad_pressed.dl)
        play_sfx = 0x4839;
    else if (pad_pressed.a)
        play_sfx = 0x483B;
    else if (pad_pressed.b)
        play_sfx = 0x483A;
    
    s8* index;
    u8  elements;
    
    if (current_menu_indexes.sub_menu_index == 0) {
        index    = &current_menu_indexes.main_index;
        elements = ARRAY_SIZE(menu_categories) - 1;
        
        if (pad_pressed.b)
            return_to_options_menu();
        else if (pad_pressed.a) {
            if (CFG_CUSTOM_MAPS && current_menu_indexes.main_index <= 2) {
                play_sfx = 0x4806;
                return;
            }
            
            if (current_menu_indexes.main_index == 5) {
                z64_file.link_age ^= z64_game.link_age;
                z64_game.link_age ^= z64_file.link_age;
                z64_file.link_age ^= z64_game.link_age;
                z64_game.link_age = !z64_game.link_age;
                
                if (z64_game.scene_index <= 0x1A || z64_game.scene_index > 0x3A) {
                    z64_Play_SetupRespawnPoint(&z64_game, 1, 0xDFF);
                    z64_file.respawn_flag = 2;
                }
                else z64_game.fadeout_transition = 2;
                
                warp_to_scene_index = z64_file.entrance_index;
            }
            else if (current_menu_indexes.sub_menu_index < 2)
                current_menu_indexes.sub_menu_index++;
        }
    }
    else { // in a sub menu
        if (pad_pressed.b)
            current_menu_indexes.sub_menu_index--;
        
        switch (current_menu_indexes.main_index) {
            case 0: // Dungeons
                if (current_menu_indexes.sub_menu_index < 2) { // Dungeons
                    index    = &current_menu_indexes.dungeon_index;
                    elements = ARRAY_SIZE(dungeon_warps) - 1;
                    
                    if (pad_pressed.a && !CFG_CUSTOM_MAPS) {
                        current_menu_indexes.sub_menu_index++;
                        current_menu_indexes.room_index = 0;
                    }
                }
                else { // Dungeon Rooms
                    index    = &current_menu_indexes.room_index;
                    elements = dungeon_rooms[current_menu_indexes.dungeon_index].number_of_rooms - 1;
                    
                    if (pad_pressed.a && !CFG_CUSTOM_MAPS) {
                        z64_Play_SetupRespawnPoint(&z64_game, 1, 0xDFF);
                        room_t* room                                    = &dungeon_rooms[current_menu_indexes.dungeon_index].room[current_menu_indexes.room_index];
                        z64_file.respawn[RESPAWN_MODE_RETURN].pos.x     = (float)room->pos.x;
                        z64_file.respawn[RESPAWN_MODE_RETURN].pos.y     = (float)room->pos.y;
                        z64_file.respawn[RESPAWN_MODE_RETURN].pos.z     = (float)room->pos.z;
                        z64_file.respawn[RESPAWN_MODE_RETURN].yaw       = room->yaw;
                        z64_file.respawn[RESPAWN_MODE_RETURN].roomIndex = current_menu_indexes.room_index;
                        z64_file.respawn_flag                           = 2;
                        warp_to_scene_index                             = dungeon_warps[current_menu_indexes.dungeon_index].entrance_index;
                    }
                }
                break;
            
            case 1: // Overworld
                index    = &current_menu_indexes.overworld_index;
                elements = ARRAY_SIZE(overworld_warps) - 1;
                
                if (pad_pressed.a && !CFG_CUSTOM_MAPS) {
                    z64_game.fadeout_transition = 2;
                    warp_to_scene_index         = overworld_warps[current_menu_indexes.overworld_index].entrance_index;
                }
                break;
            
            case 2: // Bosses
                index    = &current_menu_indexes.boss_index;
                elements = ARRAY_SIZE(bosses_warps) - 1;
                
                if (pad_pressed.a && !CFG_CUSTOM_MAPS) {
                    z64_game.fadeout_transition = 2;
                    warp_to_scene_index         = bosses_warps[current_menu_indexes.boss_index].entrance_index;
                }
                break;
            
            case 3: // Upgrades
                index    = &current_menu_indexes.upgrade_index;
                elements = ARRAY_SIZE(upgrades) - 1;
                
                if (pad_pressed.a) {
                    switch (current_menu_indexes.upgrade_index) {
                        case 0: // Magic
                            switch (z64_file.magic_capacity_set) {
                                case 0:
                                    z64_file.magic_capacity_set = z64_file.magic_acquired = 1;
                                    z64_file.magic_capacity     = 0;
                                    z64_file.magic_meter_size   = z64_file.magic          = 0x30;
                                    break;
                                
                                case 1:
                                    z64_file.magic_capacity_set = 2;
                                    z64_file.magic_acquired     = z64_file.magic_capacity = 1;
                                    z64_file.magic_meter_size   = z64_file.magic          = 0x60;
                                    break;
                                
                                default:
                                    z64_file.magic_capacity_set = z64_file.magic_acquired = z64_file.magic_capacity = z64_file.magic_meter_size =  z64_file.magic = 0;
                                    break;
                            }
                            break;
                        
                        case 1: // Double Defense
                            z64_file.double_defense ^= 1;
                            z64_file.defense_hearts  = z64_file.double_defense ? 20 : 0;
                            break;
                            
                        case 2: // Biggoron Sword
                            z64_file.bgs_flag ^= 1;
                            break;
                    }
                }
                break;
                
            case 4: // Progressions
                index                     = &current_menu_indexes.progression_index;
                elements                  = ARRAY_SIZE(progressions) - 1;
                progression_t progression = progressions[current_menu_indexes.progression_index];
                
                if (pad_pressed.a) {
                    switch (progression.type) {
                        case EVENT:
                            TOGGLE_EVENTCHKINF(progression.flag);
                            break;
                        case ITEM:
                            TOGGLE_ITEMGETINF( progression.flag);
                            break;
                        case INFTABLE:
                            TOGGLE_INFTABLE(   progression.flag);
                            break;
                        case CARPENTERS:
                            if (!GET_EVENTCHKINF(EVENTCHKINF_CARPENTERS_FREE(0))) {
                                for (u8 i=0; i<4; i++)
                                    SET_EVENTCHKINF(EVENTCHKINF_CARPENTERS_FREE(i));
                            }
                            else {
                                for (u8 i=0; i<4; i++)
                                    CLEAR_EVENTCHKINF(EVENTCHKINF_CARPENTERS_FREE(i));
                            }
                            break;
                        case NABOORU:
                            u16 nabooru_event_flags[] = { EVENTCHKINF_DEFEATED_NABOORU_KNUCKLE, EVENTCHKINF_STARTED_NABOORU_KNUCKLE, EVENTCHKINF_DEFEATED_NABOORU_KNUCKLE_CS };

                            if (!GET_EVENTCHKINF(EVENTCHKINF_DEFEATED_NABOORU_KNUCKLE)) {
                                for (u8 i=0; i<sizeof(nabooru_event_flags)/sizeof(nabooru_event_flags[0]); i++)
                                    SET_EVENTCHKINF(nabooru_event_flags[i]);
                                z64_file.scene_flags[SCENE_SPIRIT_TEMPLE_BOSS].swch |= (1 << progression.flag);
                            }
                            else {
                                for (u8 i=0; i<sizeof(nabooru_event_flags)/sizeof(nabooru_event_flags[0]); i++)
                                    CLEAR_EVENTCHKINF(nabooru_event_flags[i]);
                                z64_file.scene_flags[SCENE_SPIRIT_TEMPLE_BOSS].swch &= ~(1 << progression.flag);
                            }
                            break;
                        case MASK:
                            u16 item_flags[]  = { ITEMGETINF_BORROWED_KEATON_MASK, ITEMGETINF_BORROWED_SKULL_MASK, ITEMGETINF_BORROWED_SPOOKY_MASK, ITEMGETINF_BORROWED_BUNNY_HOOD,   ITEMGETINF_SOLD_KEATON_MASK,
                                                            ITEMGETINF_SOLD_SKULL_MASK,      ITEMGETINF_SOLD_SPOOKY_MASK,    ITEMGETINF_SOLD_BUNNY_HOOD,      ITEMGETINF_OTHER_MASKS_AVAILABLE, ITEMGETINF_MASK_OF_TRUTH_LOANED };
                            u16 event_flags[] = { EVENTCHKINF_PAID_BACK_KEATON_MASK, EVENTCHKINF_PAID_BACK_SKULL_MASK, EVENTCHKINF_PAID_BACK_SPOOKY_MASK, EVENTCHKINF_PAID_BACK_BUNNY_HOOD };
                        
                            if (!GET_ITEMGETINF(ITEMGETINF_BORROWED_KEATON_MASK)) {
                                for (u8 i=0; i<sizeof(item_flags)/sizeof(item_flags[0]); i++)
                                    SET_ITEMGETINF(item_flags[i]);
                                for (u8 i=0; i<sizeof(event_flags)/sizeof(event_flags[0]); i++)
                                    SET_EVENTCHKINF(event_flags[i]);
                            }
                            else {
                                for (u8 i=0; i<sizeof(item_flags)/sizeof(item_flags[0]); i++)
                                    CLEAR_ITEMGETINF(item_flags[i]);
                                for (u8 i=0; i<sizeof(event_flags)/sizeof(event_flags[0]); i++)
                                    CLEAR_EVENTCHKINF(event_flags[i]);
                            }
                            break;
                        default:
                            z64_file.scene_flags[progression.type].clear ^= (1 << progression.flag);
                            break;
                    }
                }
                break;
        }
    }
    
    if (pad_pressed.dd || pad_pressed.cd)
        (*index)++;
    else if (pad_pressed.du || pad_pressed.cu)
        (*index)--;
    else if (pad_pressed.dl || pad_pressed.cl)
        (*index) -= ROWS;
    else if (pad_pressed.dr || pad_pressed.cr)
        (*index) += ROWS;
    
    if (*index < 0)
        *index = elements;
    else if (*index > elements)
        *index = 0;
}

const u16 bg_left = (Z64_SCREEN_WIDTH  - BG_WIDTH)  / 2;
const u16 bg_top  = (Z64_SCREEN_HEIGHT - BG_HEIGHT) / 2;
const u16 left    = bg_left + PADDING;

bool draw_map_select(z64_disp_buf_t* db) {
    if (z64_game.pause_ctxt.debugState != 4 || CFG_OPTIONS_MENU < 3)
        return false;
    
    menu_category_t* category;
    
    gDPSetCombineMode(db->p++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
    gDPSetPrimColor(db->p++, 0, 0, 0x00, 0x00, 0x00, 0xD0);
    gSPTextureRectangle(db->p++, bg_left * 4, bg_top * 4, (bg_left + BG_WIDTH) * 4, (bg_top + BG_HEIGHT) * 4, 0, 0, 0, 1024, 1024);
    gDPSetCombineMode(db->p++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    if (current_menu_indexes.sub_menu_index == 0) {
        for (u8 i=0; i<6; i++) {
            menu_category_t *d = &(menu_categories[i]);
            if (i != current_menu_indexes.main_index)
                if (!CFG_CUSTOM_MAPS || i > 2)
                    text_print(d->name, left + 5, (bg_top + ((ICON_SIZE + PADDING) * i) + 1) + 5);
                else text_print_color(d->name, left + 5, (bg_top + ((ICON_SIZE + PADDING) * i) + 1) + 5, debug_text_color_red);
        }
        category = &(menu_categories[current_menu_indexes.main_index]);
        text_print_color(category->name, left + 5, (bg_top + ((ICON_SIZE + PADDING) * current_menu_indexes.main_index) + 1) + 5, debug_text_color_yellow);
    }
    else {
        switch (current_menu_indexes.main_index) {
            case 0: // Dungeons
                if (current_menu_indexes.sub_menu_index == 1) {
                    draw_items(dungeon_warps, current_menu_indexes.dungeon_index, ARRAY_SIZE(dungeon_warps), WARPS);
                    draw_page_counter(current_menu_indexes.dungeon_index, ARRAY_SIZE(dungeon_warps));
                }
                else {
                    u8 index    = current_menu_indexes.room_index;
                    u8 elements = dungeon_rooms[current_menu_indexes.dungeon_index].number_of_rooms;
                    u8 start    = (index / ROWS) * ROWS; 
                    u8 max      = (start + ROWS > elements) ? elements - start : ROWS;
                    
                    room_t* roomset = dungeon_rooms[current_menu_indexes.dungeon_index].room;
                    for (u8 i=0; i<max; i++) {
                        if (i + start != index)
                             text_print      (roomset[i + start].name, left + 5, (bg_top + ((ICON_SIZE + PADDING) * i) + 1) + 5);
                        else text_print_color(roomset[i + start].name, left + 5, (bg_top + ((ICON_SIZE + PADDING) * i) + 1) + 5, debug_text_color_yellow);
                    }
                    draw_page_counter(index, elements);
                }
                break;
                
            case 1: // Overworld
                draw_items(overworld_warps, current_menu_indexes.overworld_index, ARRAY_SIZE(overworld_warps), WARPS);
                draw_page_counter(current_menu_indexes.overworld_index, ARRAY_SIZE(overworld_warps));
                break;
                
            case 2: // Bosses
                draw_items(bosses_warps, current_menu_indexes.boss_index, ARRAY_SIZE(bosses_warps), WARPS);
                draw_page_counter(current_menu_indexes.boss_index, ARRAY_SIZE(bosses_warps));
                break;
                
            case 3: // Upgrades
                draw_items(upgrades, current_menu_indexes.upgrade_index, ARRAY_SIZE(upgrades), UPGRADES);
                draw_page_counter(current_menu_indexes.upgrade_index, ARRAY_SIZE(upgrades));  
                break;
            
            case 4: // Progressions
                draw_items(progressions, current_menu_indexes.progression_index, ARRAY_SIZE(progressions), PROGRESSIONS);
                draw_page_counter(current_menu_indexes.progression_index, ARRAY_SIZE(progressions));  
                break;
        }
        
    }
    
    draw_timeofday(db);
    text_flush(db);
    return true;
}

void draw_page_counter(u8 index, u16 elements) {
    u8 start = (index / ROWS) * ROWS; 
    
    char page[9] = "Page: 1/1";
    page[6] = '0' + (start       ) / ROWS + 1;
    page[8] = '0' + (elements - 1) / ROWS + 1;
    text_set_size(4, 7);
    text_print(page, bg_left + BG_WIDTH - 40, bg_top + BG_HEIGHT - 10);
    text_set_size(8, 14);
}

void draw_items(void* items, u8 index, u16 elements, u8 type) {
    u8          start    = (index / ROWS) * ROWS; 
    u8          max      = (start + ROWS > elements) ? elements - start : ROWS;
    char        value[2] = "0";
    const char* name;
    u8          save;
    
    for (u8 i=0; i<max; i++) {
        u8 curr = i + start;
        
        switch (type) {
            case WARPS:
                name = ((warp_t*)items)[curr].name;
                break;
            case UPGRADES:
                upgrade_t* upgrades = ((upgrade_t*)items);
            
                switch (curr) {
                    case 0:
                        save = z64_file.magic_capacity_set;
                        break;
                    case 1:
                        save = z64_file.double_defense;
                        break;
                    case 2:
                        save = z64_file.bgs_flag;
                        break;
                }
            
                name     = upgrades[curr].name;
                value[0] = '0' + save;
                text_print(value, left + BG_WIDTH - 20, (bg_top + ((ICON_SIZE + PADDING) * i) + 1) + 5);
                break;
            case PROGRESSIONS:
                progression_t* progressions = ((progression_t*)items);
            
                switch (progressions[curr].type) {
                    case EVENT:
                        save = GET_EVENTCHKINF(progressions[curr].flag) ? 1 : 0;
                        break;
                    case ITEM:
                        save = GET_ITEMGETINF( progressions[curr].flag) ? 1 : 0;
                        break;
                    case INFTABLE:
                         save = GET_INFTABLE(  progressions[curr].flag) ? 1 : 0;
                        break;
                    case CARPENTERS:
                        save = (GET_EVENTCHKINF(EVENTCHKINF_CARPENTERS_FREE(0)) && GET_EVENTCHKINF(EVENTCHKINF_CARPENTERS_FREE(1)) && GET_EVENTCHKINF(EVENTCHKINF_CARPENTERS_FREE(2)) && GET_EVENTCHKINF(EVENTCHKINF_CARPENTERS_FREE(3))) ? 1 : 0;
                        break;
                    case NABOORU:
                        save = (GET_EVENTCHKINF(EVENTCHKINF_DEFEATED_NABOORU_KNUCKLE) && GET_EVENTCHKINF(EVENTCHKINF_STARTED_NABOORU_KNUCKLE) && GET_EVENTCHKINF(EVENTCHKINF_DEFEATED_NABOORU_KNUCKLE_CS) && (z64_file.scene_flags[SCENE_SPIRIT_TEMPLE_BOSS].swch &= (1 << progressions[curr].flag))) ? 1 : 0;
                        break;
                    case MASK:
                        save = GET_ITEMGETINF(ITEMGETINF_OTHER_MASKS_AVAILABLE) ? 1 : 0;
                        break;
                    default:
                        save = z64_file.scene_flags[progressions[curr].type].clear & (1 << progressions[curr].flag) ? 1 : 0;
                        break;
                }
            
                name     = progressions[curr].name;
                value[0] = '0' + save;
                text_print(value, left + BG_WIDTH - 20, (bg_top + ((ICON_SIZE + PADDING) * i) + 1) + 5);
                break;
        }

        if (curr != index)
             text_print(      name, left + 5, (bg_top + ((ICON_SIZE + PADDING) * i) + 1) + 5);
        else text_print_color(name, left + 5, (bg_top + ((ICON_SIZE + PADDING) * i) + 1) + 5, debug_text_color_yellow);
    }
}

void draw_timeofday(z64_disp_buf_t* db) {
    if (current_menu_indexes.main_index == 0 && current_menu_indexes.sub_menu_index == 2)
        return;
    
    u8 digits[4];
    digits[0]            = 0;
    double timeInSeconds = z64_file.day_time * (24.0f * 60.0f / 0x10000);
    digits[1]            = timeInSeconds / 60.0f;
    
    while (digits[1] >= 10) {
        digits[0]++;
        digits[1] -= 10;
    }
    
    digits[2] = 0;
    digits[3] = (s16)timeInSeconds % 60;
    
    while (digits[3] >= 10) {
        digits[2]++;
        digits[3] -= 10;
    }
    
    u8 hours           = digits[0] * 10 + digits[1];
    colorRGBA8_t color = { 0xFF, 0xFF, 0xFF, 0xFF};
    u16 total_w        = 4 * counter_digit_sprite.tile_w + font_sprite.tile_w;
    u16 draw_x         = Z64_SCREEN_WIDTH / 2 - total_w / 2;
    u16 draw_y_text    = Z64_SCREEN_HEIGHT - (counter_digit_sprite.tile_h * 1.5) + 1;
    
    if (digits[0] == 0)
        draw_x += counter_digit_sprite.tile_w;
    draw_int(db, hours, draw_x, draw_y_text, color);
    
    if (digits[0] == 0)
        draw_x -= counter_digit_sprite.tile_w;
    text_print(":", draw_x + 2 * counter_digit_sprite.tile_w, draw_y_text);
    
    u8 minutes = digits[2] * 10 + digits[3];
    
    if (digits[2] == 0) {
        draw_int(db, 0, draw_x + 2*counter_digit_sprite.tile_w + font_sprite.tile_w, draw_y_text, color);
        draw_x += counter_digit_sprite.tile_w;
    }
    
    draw_int(db, minutes, draw_x + 2*counter_digit_sprite.tile_w + font_sprite.tile_w, draw_y_text, color);
}