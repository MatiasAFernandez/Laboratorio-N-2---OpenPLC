void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void LAB2_OPENPLC_init__(LAB2_OPENPLC *data__, BOOL retain) {
  __INIT_LOCATED(BOOL,__IX0_0,data__->BTN_CONTROL,retain)
  __INIT_LOCATED_VALUE(data__->BTN_CONTROL,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(INT,__MW0_0,data__->PRESION,retain)
  __INIT_LOCATED_VALUE(data__->PRESION,300)
  __INIT_LOCATED(BOOL,__QX0_0,data__->LED_EMERGENCIA,retain)
  __INIT_LOCATED_VALUE(data__->LED_EMERGENCIA,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_1,data__->FLAG_AUMENTAR,retain)
  __INIT_LOCATED_VALUE(data__->FLAG_AUMENTAR,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_2,data__->FLAG_DISMINUIR,retain)
  __INIT_LOCATED_VALUE(data__->FLAG_DISMINUIR,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_3,data__->EMERGENCIA_ACTIVA,retain)
  __INIT_LOCATED_VALUE(data__->EMERGENCIA_ACTIVA,__BOOL_LITERAL(FALSE))
  __INIT_LOCATED(BOOL,__QX0_4,data__->FLAG_RELOJ_ON,retain)
  __INIT_LOCATED_VALUE(data__->FLAG_RELOJ_ON,__BOOL_LITERAL(FALSE))
  __INIT_VAR(data__->PULSO,__BOOL_LITERAL(FALSE),retain)
  R_TRIG_init__(&data__->AUX_TRIG,retain);
  SR_init__(&data__->SR_AUMENTAR,retain);
  SR_init__(&data__->SR_EMERGENCIA,retain);
  SR_init__(&data__->SR_DISMINUIR,retain);
  TON_init__(&data__->TON_RELOJ,retain);
  R_TRIG_init__(&data__->R_TRIG_RELOJ,retain);
  SR_init__(&data__->SR_RELOJ,retain);
  __INIT_VAR(data__->_TMP_NOT6_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_NOT5_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_AND4_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_AND10_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_OR9_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_AND25_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_AND24_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_SUB27_OUT,0,retain)
  __INIT_VAR(data__->_TMP_SEL28_OUT,0,retain)
  __INIT_VAR(data__->_TMP_ADD26_OUT,0,retain)
  __INIT_VAR(data__->_TMP_SEL37_OUT,0,retain)
  __INIT_VAR(data__->_TMP_GE12_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_EQ15_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_NOT19_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->_TMP_NOT47_OUT,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LAB2_OPENPLC_body__(LAB2_OPENPLC *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->AUX_TRIG.,CLK,,__GET_LOCATED(data__->BTN_CONTROL,));
  R_TRIG_body__(&data__->AUX_TRIG);
  __SET_VAR(data__->,_TMP_NOT6_OUT,,!(__GET_LOCATED(data__->FLAG_AUMENTAR,)));
  __SET_VAR(data__->,_TMP_NOT5_OUT,,!(__GET_LOCATED(data__->EMERGENCIA_ACTIVA,)));
  __SET_VAR(data__->,_TMP_AND4_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)3,
    (BOOL)__GET_VAR(data__->AUX_TRIG.Q,),
    (BOOL)__GET_VAR(data__->_TMP_NOT6_OUT,),
    (BOOL)__GET_VAR(data__->_TMP_NOT5_OUT,)));
  __SET_VAR(data__->,_TMP_AND10_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->AUX_TRIG.Q,),
    (BOOL)__GET_LOCATED(data__->FLAG_AUMENTAR,)));
  __SET_VAR(data__->,_TMP_OR9_OUT,,OR__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->_TMP_AND10_OUT,),
    (BOOL)__GET_LOCATED(data__->EMERGENCIA_ACTIVA,)));
  __SET_VAR(data__->SR_AUMENTAR.,S1,,__GET_VAR(data__->_TMP_AND4_OUT,));
  __SET_VAR(data__->SR_AUMENTAR.,R,,__GET_VAR(data__->_TMP_OR9_OUT,));
  SR_body__(&data__->SR_AUMENTAR);
  __SET_LOCATED(data__->,FLAG_AUMENTAR,,__GET_VAR(data__->SR_AUMENTAR.Q1,));
  __SET_VAR(data__->,_TMP_AND25_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->PULSO,),
    (BOOL)__GET_LOCATED(data__->FLAG_AUMENTAR,)));
  __SET_VAR(data__->,_TMP_AND24_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->PULSO,),
    (BOOL)__GET_LOCATED(data__->FLAG_DISMINUIR,)));
  __SET_VAR(data__->,_TMP_SUB27_OUT,,SUB__INT__INT__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (INT)__GET_LOCATED(data__->PRESION,),
    (INT)1));
  __SET_VAR(data__->,_TMP_SEL28_OUT,,SEL__INT__BOOL__INT__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (BOOL)__GET_VAR(data__->_TMP_AND24_OUT,),
    (INT)__GET_LOCATED(data__->PRESION,),
    (INT)__GET_VAR(data__->_TMP_SUB27_OUT,)));
  __SET_VAR(data__->,_TMP_ADD26_OUT,,ADD__INT__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_LOCATED(data__->PRESION,),
    (INT)1));
  __SET_VAR(data__->,_TMP_SEL37_OUT,,SEL__INT__BOOL__INT__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (BOOL)__GET_VAR(data__->_TMP_AND25_OUT,),
    (INT)__GET_VAR(data__->_TMP_SEL28_OUT,),
    (INT)__GET_VAR(data__->_TMP_ADD26_OUT,)));
  __SET_LOCATED(data__->,PRESION,,__GET_VAR(data__->_TMP_SEL37_OUT,));
  __SET_VAR(data__->,_TMP_GE12_OUT,,GE__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_LOCATED(data__->PRESION,),
    (INT)460));
  __SET_VAR(data__->,_TMP_EQ15_OUT,,EQ__BOOL__INT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (INT)__GET_LOCATED(data__->PRESION,),
    (INT)300));
  __SET_VAR(data__->SR_EMERGENCIA.,S1,,__GET_VAR(data__->_TMP_GE12_OUT,));
  __SET_VAR(data__->SR_EMERGENCIA.,R,,__GET_VAR(data__->_TMP_EQ15_OUT,));
  SR_body__(&data__->SR_EMERGENCIA);
  __SET_LOCATED(data__->,EMERGENCIA_ACTIVA,,__GET_VAR(data__->SR_EMERGENCIA.Q1,));
  __SET_LOCATED(data__->,LED_EMERGENCIA,,__GET_LOCATED(data__->EMERGENCIA_ACTIVA,));
  __SET_VAR(data__->,_TMP_NOT19_OUT,,!(__GET_LOCATED(data__->EMERGENCIA_ACTIVA,)));
  __SET_VAR(data__->SR_DISMINUIR.,S1,,__GET_LOCATED(data__->EMERGENCIA_ACTIVA,));
  __SET_VAR(data__->SR_DISMINUIR.,R,,__GET_VAR(data__->_TMP_NOT19_OUT,));
  SR_body__(&data__->SR_DISMINUIR);
  __SET_LOCATED(data__->,FLAG_DISMINUIR,,__GET_VAR(data__->SR_DISMINUIR.Q1,));
  __SET_VAR(data__->TON_RELOJ.,IN,,__GET_LOCATED(data__->FLAG_RELOJ_ON,));
  TON_body__(&data__->TON_RELOJ);
  __SET_VAR(data__->,_TMP_NOT47_OUT,,!(__GET_VAR(data__->TON_RELOJ.Q,)));
  __SET_VAR(data__->SR_RELOJ.,S1,,__GET_VAR(data__->_TMP_NOT47_OUT,));
  __SET_VAR(data__->SR_RELOJ.,R,,__GET_VAR(data__->TON_RELOJ.Q,));
  SR_body__(&data__->SR_RELOJ);
  __SET_LOCATED(data__->,FLAG_RELOJ_ON,,__GET_VAR(data__->SR_RELOJ.Q1,));
  __SET_VAR(data__->R_TRIG_RELOJ.,CLK,,__GET_LOCATED(data__->FLAG_RELOJ_ON,));
  R_TRIG_body__(&data__->R_TRIG_RELOJ);
  __SET_VAR(data__->,PULSO,,__GET_VAR(data__->R_TRIG_RELOJ.Q,));

  goto __end;

__end:
  return;
} // LAB2_OPENPLC_body__() 





