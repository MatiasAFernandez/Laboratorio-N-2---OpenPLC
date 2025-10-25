TYPE
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := INFO;
END_TYPE

FUNCTION_BLOCK LOGGER
  VAR_INPUT
    TRIG : BOOL;
    MSG : STRING;
    LEVEL : LOGLEVEL := INFO;
  END_VAR
  VAR
    TRIG0 : BOOL;
  END_VAR

  IF TRIG AND NOT TRIG0 THEN
  {{
   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  }}
  END_IF;
  TRIG0:=TRIG;
END_FUNCTION_BLOCK


PROGRAM Lab2_OpenPLC
  VAR
    Btn_Control AT %IX0.0 : BOOL := FALSE;
    Presion AT %MW0.0 : INT := 300;
    LED_Emergencia AT %QX0.0 : BOOL := FALSE;
    Flag_Aumentar AT %QX0.1 : BOOL := FALSE;
    Flag_Disminuir AT %QX0.2 : BOOL := FALSE;
    Emergencia_Activa AT %QX0.3 : BOOL := FALSE;
    Flag_Reloj_ON AT %QX0.4 : BOOL := FALSE;
  END_VAR
  VAR
    Pulso : BOOL;
    Aux_Trig : R_TRIG;
    SR_Aumentar : SR;
    SR_Emergencia : SR;
    SR_Disminuir : SR;
    TON_Reloj : TON;
    R_TRIG_Reloj : R_TRIG;
    SR_Reloj : SR;
    _TMP_NOT6_OUT : BOOL;
    _TMP_NOT5_OUT : BOOL;
    _TMP_AND4_OUT : BOOL;
    _TMP_AND10_OUT : BOOL;
    _TMP_OR9_OUT : BOOL;
    _TMP_AND25_OUT : BOOL;
    _TMP_AND24_OUT : BOOL;
    _TMP_SUB27_OUT : INT;
    _TMP_SEL28_OUT : INT;
    _TMP_ADD26_OUT : INT;
    _TMP_SEL37_OUT : INT;
    _TMP_GE12_OUT : BOOL;
    _TMP_EQ15_OUT : BOOL;
    _TMP_NOT19_OUT : BOOL;
    _TMP_NOT47_OUT : BOOL;
  END_VAR

  Aux_Trig(CLK := Btn_Control);
  _TMP_NOT6_OUT := NOT(Flag_Aumentar);
  _TMP_NOT5_OUT := NOT(Emergencia_Activa);
  _TMP_AND4_OUT := AND(Aux_Trig.Q, _TMP_NOT6_OUT, _TMP_NOT5_OUT);
  _TMP_AND10_OUT := AND(Aux_Trig.Q, Flag_Aumentar);
  _TMP_OR9_OUT := OR(_TMP_AND10_OUT, Emergencia_Activa);
  SR_Aumentar(S1 := _TMP_AND4_OUT, R := _TMP_OR9_OUT);
  Flag_Aumentar := SR_Aumentar.Q1;
  _TMP_AND25_OUT := AND(Pulso, Flag_Aumentar);
  _TMP_AND24_OUT := AND(Pulso, Flag_Disminuir);
  _TMP_SUB27_OUT := SUB(Presion, 1);
  _TMP_SEL28_OUT := SEL(_TMP_AND24_OUT, Presion, _TMP_SUB27_OUT);
  _TMP_ADD26_OUT := ADD(Presion, 1);
  _TMP_SEL37_OUT := SEL(_TMP_AND25_OUT, _TMP_SEL28_OUT, _TMP_ADD26_OUT);
  Presion := _TMP_SEL37_OUT;
  _TMP_GE12_OUT := GE(Presion, 460);
  _TMP_EQ15_OUT := EQ(Presion, 300);
  SR_Emergencia(S1 := _TMP_GE12_OUT, R := _TMP_EQ15_OUT);
  Emergencia_Activa := SR_Emergencia.Q1;
  LED_Emergencia := Emergencia_Activa;
  _TMP_NOT19_OUT := NOT(Emergencia_Activa);
  SR_Disminuir(S1 := Emergencia_Activa, R := _TMP_NOT19_OUT);
  Flag_Disminuir := SR_Disminuir.Q1;
  TON_Reloj(IN := Flag_Reloj_ON);
  _TMP_NOT47_OUT := NOT(TON_Reloj.Q);
  SR_Reloj(S1 := _TMP_NOT47_OUT, R := TON_Reloj.Q);
  Flag_Reloj_ON := SR_Reloj.Q1;
  R_TRIG_Reloj(CLK := Flag_Reloj_ON);
  Pulso := R_TRIG_Reloj.Q;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#20ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : Lab2_OpenPLC;
  END_RESOURCE
END_CONFIGURATION
