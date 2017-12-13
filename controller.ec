const
  kp_teta : real;
  ki_teta : real;
  Te : real;
  pi : real;
  
node controller
  (Cg: real;
  Cd: real;
  Jean_Michel: int)
returns
  (v_d: real;
  v_g: real);

var
  V11_w_000: bool;
  V12_w_001: bool;
  V13_w_002: bool;
  V14_w_003: bool;
  V15_w_004: real;
  V16_w_005: real;
  V17_w_006: real;
  V18_w_007: bool;
  V19_w_008: bool;
  V26_w_015: real;
  V29_w_018: real;
  V118_w_001: bool;
  V119_w_004: bool;
  V120_w_005: bool;
  V137_w_000: real;
  V138_w_001: real;
  V139_w_002: real;
  V140_w_007: real;
  V141_w_008: real;
  V142_w_009: real;
  V143_w_010: real;
  V144_w_011: real;
  V145_w_012: real;
  V146_w_013: real;
  V147_w_014: real;
  V148_w_015: real;
  V149_w_016: real;
  V171_w_004: real;

let
  v_d = (if V13_w_002 then 100.000000 else V17_w_006);
  v_g = (if V13_w_002 then V16_w_005 else V15_w_004);
  V11_w_000 = (false -> (pre V13_w_002));
  V12_w_001 = (V118_w_001 and V119_w_004);
  V13_w_002 = (V12_w_001 and V19_w_008);
  V14_w_003 = (Jean_Michel <= 10);
  V15_w_004 = (0.500000 * V146_w_013);
  V16_w_005 = (-1.000000 * 100.000000);
  V17_w_006 = (0.500000 * V147_w_014);
  V18_w_007 = (Cg <= 50.000000);
  V19_w_008 = (not (V12_w_001 and V18_w_007));
  V26_w_015 = ((pi / 200.000000) * V171_w_004);
  V29_w_018 = (Cd + Cg);
  V118_w_001 = (V120_w_005 or V14_w_003);
  V119_w_004 = (not V11_w_000);
  V120_w_005 = (false -> (pre V12_w_001));
  V137_w_000 = (0.000000 -> (pre V139_w_002));
  V138_w_001 = (Te * V26_w_015);
  V139_w_002 = (V138_w_001 + V137_w_000);
  V140_w_007 = (V149_w_016 + V148_w_015);
  V141_w_008 = ((-V143_w_010) + V144_w_011);
  V142_w_009 = (2.000000 * V141_w_008);
  V143_w_010 = (if (V145_w_012 < 0.000000) then (-V145_w_012) else V145_w_012);
  V144_w_011 = (0.005000 * V29_w_018);
  V145_w_012 = (2.000000 * V140_w_007);
  V146_w_013 = ((-V140_w_007) + V142_w_009);
  V147_w_014 = (V140_w_007 + V142_w_009);
  V148_w_015 = (kp_teta * V26_w_015);
  V149_w_016 = (ki_teta * V137_w_000);
  V171_w_004 = (Cd - Cg);
tel

