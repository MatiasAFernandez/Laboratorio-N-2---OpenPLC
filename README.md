# ⚙️ Laboratorio N° 2: OpenPLC - Sistema de Emergencia para Planta de Vapor


## 📜 Descripción del Proyecto

Este repositorio contiene la reimplementación y documentación de un lazo de control de un **sistema de emergencia por sobrepresión** en una planta simulada de producción y distribución de vapor, utilizando la plataforma **OpenPLC** y el lenguaje **Function Block Diagram (FBD)**. El proyecto fue desarrollado para la asignatura **Tecnologías para la automatización** de la carrera **Ingeniería en Sistemas de Información** de la **Universidad Tecnológica Nacional, Facultad Regional Resistencia (UTN-FRRe)**.

---

## 🎯 Fin del Programa

El objetivo principal del programa es **mantener la presión de la planta dentro de límites seguros** a través de un sistema de emergencia.

1.  **Función principal:** Permite a un operador **incrementar la presión** de la planta (simulada) mediante un botón.
2.  **Sistema de Emergencia:** Activa automáticamente un mecanismo de corrección (apertura de válvulas de alivio) si la presión alcanza o supera un **valor límite máximo de 460 Kpa**, para reducirla hasta un **valor estable de 300 Kpa**.
3.  **Seguridad:** Mientras el sistema de emergencia está activo, se **anula la función del botón de incremento** para evitar que la presión siga subiendo.

---

## 🧠 Funcionamiento General

El programa simula un lazo de control con las siguientes características:

* **Variable Controlada:** `Presion` (valor actual, en Kpa), inicializada en **300 Kpa**.
* **Referencia/Límite:** **460 Kpa** (valor máximo permitido).

El funcionamiento se basa en estados de control:

1.  **Aumento de Presión:** Un botón (`Btn_Control`) actúa como *toggle* para iniciar/detener el incremento de la variable `Presion` a una tasa de **1 unidad por segundo**.
2.  **Activación de Emergencia:** Se utiliza un comparador (`GE`) que, al detectar que `Presion >= 460 Kpa`, activa el *flag* `Emergencia_Activa` y el LED de emergencia (`LED_Emergencia`).
3.  **Corrección/Disminución:** Una vez activa la emergencia, se anula el botón de aumento y se inicia la disminución de la `Presion` a una tasa de **1 unidad por segundo** mediante el *flag* `Flag_Disminuir`.
4.  **Desactivación de Emergencia:** Cuando la `Presion` alcanza el valor estable inicial de **300 Kpa** (verificado por un comparador `EQ`), el sistema de emergencia se desactiva, permitiendo reanudar el proceso de aumento.

---

## 🛠️ Tecnologías y Herramientas

* **Plataforma de Programación:** **OpenPLC Editor**
* **Lenguaje de Programación:** **Function Block Diagram (FBD)**
* **Hardware de Destino:** **Raspberry Pi Pico W** (Simulación o Despliegue)
* **Actuadores/Sensores Simulados:**
    * **Entrada Digital:** `Btn_Control` (Botón para iniciar/detener aumento de presión).
    * **Salida Digital:** `LED_Emergencia` (Indicador visual de emergencia activa).

### Mapeo de E/S Digitales y Analógicas (Raspberry Pi Pico W)

| Tipo | Variables | Pines (Arduino Notation) |
| :--- | :--- | :--- |
| **Digital Inputs** | `Btn_Control` | **%IX0.0** (Pin **6**) |
| **Digital Outputs**| `LED_Emergencia`, `Flag_Aumentar`, `Flag_Disminuir`, `Emergencia_Activa`, `Flag_Reloj_ON` | **%QX0.0** a **%QX0.4** (Pines **14 a 18**)|
| **Analog Inputs** | | 26, 27, 28 |
| **Analog Outputs**| | 4, 5 |

*(Nota: Los pines de OpenPLC siguen la notación de Arduino para la Raspberry Pi Pico W, como se detalla en la documentación original.)*

---

## 📄 Estructura del Diagrama FBD

El diagrama de bloques se divide lógicamente en cuatro secciones principales:

1.  **Sección 1: Control del Botón y Banderas de Estado**
    * Gestiona el comportamiento *toggle* del `Btn_Control` mediante un bloque **R_TRIG** (`Aux_Trig`) y el *flip-flop* **SR** (`SR_Aumentar`) para activar/desactivar `Flag_Aumentar`.
    * Asegura que no se pueda aumentar la presión si `Emergencia_Activa` es **True**.
    * Controla el indicador visual `LED_Emergencia`.
2.  **Sección 2: Generación del Pulso de Tiempo**
    * Crea una señal de reloj booleana (`Pulso_5Hz`) que alterna entre **True** y **False** a una tasa de **1 unidad/segundo** (usando **TON**, **R_TRIG** y **SR**).
    * Esta señal habilita las operaciones de suma y resta a un ritmo constante.
3.  **Sección 3: Modificación de la Presión**
    * Contiene los bloques **ADD** y **SUB** para aumentar o disminuir la variable `Presion` en 1 unidad.
    * Las operaciones están habilitadas por los *flags* de estado (`Flag_Aumentar` y `Flag_Disminuir`) junto con el pulso de tiempo.
    * Los bloques **SEL** garantizan que solo una operación (ADD o SUB) afecte a `Presion` en un momento dado.
4.  **Sección 4: Lógica del Sistema de Emergencia**
    * Bloque **GE** (`Presion` **>=** **460**): Activa el *flip-flop* **SR** (`SR_Emergencia`) para establecer `Emergencia_Activa`.
    * Bloque **EQ** (`Presion` **==** **300**): Genera un **Reset** al *flip-flop* **SR** para desactivar `Emergencia_Activa`.

---

## 👥 Integrantes del Grupo N°6 “Los Autómatas”

| Nombre Completo |
| :--- |
| Fernandez Matias |
| Insaurralde Mariano |
| Maurel Garcete, Philippe |
| Sánchez, Franco |
| Rodas, Sebastián |

---

## 👨‍🏫 Profesores

* Ing. Arturo Castaño
* Ing. Dominga C. Aquino
* Aux. Carlos G. Pérez
