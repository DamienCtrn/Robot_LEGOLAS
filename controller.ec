const
  kp_teta : real;
  ki_teta : real;
  Te : real;
  pi : real;
  
node controller
  (Cg: real;
  Cd: real;
  Jean_Michel: int;
  Jean_Ren__: bool)
returns
  (v_d: real;
  v_g: real);

var
  V13_w_001: bool;
  V282_w_001: bool;
  V283_w_003: bool;
  V284_w_004: bool;
  V285_w_005: bool;
  V286_w_008: bool;
  V287_w_010: bool;
  V288_w_011: bool;
  V289_w_013: bool;
  V290_w_014: bool;
  V291_w_016: bool;
  V292_w_001: bool;
  V293_w_004: bool;
  V294_w_005: bool;
  V295_w_001: bool;
  V296_w_004: bool;
  V297_w_005: bool;
  V298_w_001: bool;
  V299_w_004: bool;
  V300_w_005: bool;
  V321_w_002: real;
  V322_w_003: real;
  V323_w_004: real;
  V324_w_005: real;
  V325_w_008: real;
  V326_w_000: real;
  V327_w_001: real;
  V328_w_002: real;
  V329_w_007: real;
  V330_w_008: real;
  V331_w_009: real;
  V332_w_010: real;
  V333_w_011: real;
  V334_w_012: real;
  V335_w_013: real;
  V336_w_014: real;
  V337_w_015: real;
  V338_w_016: real;
  V339_w_004: real;

let
  v_d = (if V13_w_001 then 0.200000 else V325_w_008);
  v_g = (if V13_w_001 then V323_w_004 else V321_w_002);
  V13_w_001 = (V292_w_001 and V293_w_004);
  V282_w_001 = (V295_w_001 and V296_w_004);
  V283_w_003 = (V282_w_001 and V286_w_008);
  V284_w_004 = (Jean_Michel <= 10);
  V285_w_005 = (Cd <= 30.000000);
  V286_w_008 = (Cd >= 70.000000);
  V287_w_010 = (V13_w_001 and V285_w_005);
  V288_w_011 = (V298_w_001 and V299_w_004);
  V289_w_013 = (false -> (pre V290_w_014));
  V290_w_014 = (V288_w_011 and V285_w_005);
  V291_w_016 = (V289_w_013 or Jean_Ren__);
  V292_w_001 = (V294_w_005 or V284_w_004);
  V293_w_004 = (not V291_w_016);
  V294_w_005 = (false -> (pre V13_w_001));
  V295_w_001 = (V297_w_005 or V287_w_010);
  V296_w_004 = (not V291_w_016);
  V297_w_005 = (false -> (pre V282_w_001));
  V298_w_001 = (V300_w_005 or V283_w_003);
  V299_w_004 = (not V291_w_016);
  V300_w_005 = (false -> (pre V288_w_011));
  V321_w_002 = (0.500000 * V335_w_013);
  V322_w_003 = ((pi / 200.000000) * V339_w_004);
  V323_w_004 = (-1.000000 * 0.200000);
  V324_w_005 = (Cd + Cg);
  V325_w_008 = (0.500000 * V336_w_014);
  V326_w_000 = (0.000000 -> (pre V328_w_002));
  V327_w_001 = (Te * V322_w_003);
  V328_w_002 = (V327_w_001 + V326_w_000);
  V329_w_007 = (V338_w_016 + V337_w_015);
  V330_w_008 = ((-V332_w_010) + V333_w_011);
  V331_w_009 = (2.000000 * V330_w_008);
  V332_w_010 = (if (V334_w_012 < 0.000000) then (-V334_w_012) else V334_w_012);
  V333_w_011 = (0.005000 * V324_w_005);
  V334_w_012 = (2.000000 * V329_w_007);
  V335_w_013 = ((-V329_w_007) + V331_w_009);
  V336_w_014 = (V329_w_007 + V331_w_009);
  V337_w_015 = (kp_teta * V322_w_003);
  V338_w_016 = (ki_teta * V326_w_000);
  V339_w_004 = (Cd - Cg);
tel

