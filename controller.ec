const
  kp_teta : real;
  ki_teta : real;
  Te : real;
  pi : real;
  
node controller
  (Cg: real;
  Cd: real;
  Jean_Michel: int;
  Jean_Reset: bool)
returns
  (v_d: real;
  v_g: real);

var
  V13_w_001: bool;
  V14_w_002: bool;
  V15_w_003: bool;
  V17_w_005: bool;
  V18_w_006: bool;
  V19_w_007: bool;
  V20_w_008: bool;
  V21_w_009: bool;
  V22_w_010: bool;
  V23_w_011: bool;
  V24_w_012: real;
  V25_w_013: real;
  V26_w_014: real;
  V27_w_015: bool;
  V34_w_022: real;
  V37_w_025: real;
  V158_w_001: bool;
  V159_w_004: bool;
  V160_w_005: bool;
  V177_w_000: real;
  V178_w_001: real;
  V179_w_002: real;
  V180_w_007: real;
  V181_w_008: real;
  V182_w_009: real;
  V183_w_010: real;
  V184_w_011: real;
  V185_w_012: real;
  V186_w_013: real;
  V187_w_014: real;
  V188_w_015: real;
  V189_w_016: real;
  V208_w_001: bool;
  V209_w_004: bool;
  V210_w_005: bool;
  V222_w_001: bool;
  V223_w_004: bool;
  V224_w_005: bool;
  V239_w_004: real;

let
  v_d = (if V22_w_010 then 0.200000 else V26_w_014);
  v_g = (if V22_w_010 then V25_w_013 else V24_w_012);
  V13_w_001 = (V14_w_002 or Jean_Reset);
  V14_w_002 = (false -> (pre V15_w_003));
  V15_w_003 = (V17_w_005 and V27_w_015);
  V17_w_005 = (V222_w_001 and V223_w_004);
  V18_w_006 = (V19_w_007 and V20_w_008);
  V19_w_007 = (V208_w_001 and V209_w_004);
  V20_w_008 = (Cd >= 70.000000);
  V21_w_009 = (V22_w_010 and V27_w_015);
  V22_w_010 = (V158_w_001 and V159_w_004);
  V23_w_011 = (Jean_Michel <= 10);
  V24_w_012 = (0.500000 * V186_w_013);
  V25_w_013 = (-1.000000 * 0.200000);
  V26_w_014 = (0.500000 * V187_w_014);
  V27_w_015 = (Cd <= 30.000000);
  V34_w_022 = ((pi / 200.000000) * V239_w_004);
  V37_w_025 = (Cd + Cg);
  V158_w_001 = (V160_w_005 or V23_w_011);
  V159_w_004 = (not V13_w_001);
  V160_w_005 = (false -> (pre V22_w_010));
  V177_w_000 = (0.000000 -> (pre V179_w_002));
  V178_w_001 = (Te * V34_w_022);
  V179_w_002 = (V178_w_001 + V177_w_000);
  V180_w_007 = (V189_w_016 + V188_w_015);
  V181_w_008 = ((-V183_w_010) + V184_w_011);
  V182_w_009 = (2.000000 * V181_w_008);
  V183_w_010 = (if (V185_w_012 < 0.000000) then (-V185_w_012) else V185_w_012);
  V184_w_011 = (0.005000 * V37_w_025);
  V185_w_012 = (2.000000 * V180_w_007);
  V186_w_013 = ((-V180_w_007) + V182_w_009);
  V187_w_014 = (V180_w_007 + V182_w_009);
  V188_w_015 = (kp_teta * V34_w_022);
  V189_w_016 = (ki_teta * V177_w_000);
  V208_w_001 = (V210_w_005 or V21_w_009);
  V209_w_004 = (not V13_w_001);
  V210_w_005 = (false -> (pre V19_w_007));
  V222_w_001 = (V224_w_005 or V18_w_006);
  V223_w_004 = (not V13_w_001);
  V224_w_005 = (false -> (pre V17_w_005));
  V239_w_004 = (Cd - Cg);
tel

