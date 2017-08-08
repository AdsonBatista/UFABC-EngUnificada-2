      sub ligar() {
        // porta, velocidade, angulo, the proportional part P(t), the integrative part I(t) and the derivative part D(t)
        RotateMotorPID(OUT_A, 100, -90, 40, 40, 90);
        // espera 3000ms para fazer outra coisa
        Wait(3000);
        //ligo a esteira com 10% do motor
        OnFwd(OUT_C, 10);
        //ligo a pá com 100% do motor
        OnFwd(OUT_B, 100);
      }

      sub desligar() {
        // paro as pa
        Stop(OUT_B);
        // porta, velocidade, angulo, the proportional part P(t), the integrative part I(t) and the derivative part D(t)
        RotateMotorPID(OUT_A, 100, 90, 40, 40, 90);
        // espera 3000ms para fazer outra coisa
        Wait(8000);
        // paro esteira
        Stop(OUT_C);
      }

      // enquanto panico não pertado ele faz algo
      task main() {
        SetSensor(IN_1, SENSOR_TOUCH); // define sensor entrada 1 como sensor de toque {panico}
        SetSensor(IN_2, SENSOR_TOUCH); // define sensor entrada 2 como sensor de toque {coletor de lixo}
        SetSensorColorFull(IN_3); // define sensor de cor na entrada 3 utilizando todas as corres {sensor de chuva}
        //SetSensorColorFull(S3);		// uma apostila seta assim

        do { // Se sensor 1 não apertado faça...
          //TextOut (int x, int y, string str,options)
          TextOut(15, LCD_LINE1, "OK", true);
          Wait(5000);
          //colocar rotina aqui
          do {
            TextOut(15, LCD_LINE1, "livre", true);
            Wait(5000);
            // sensor de cor
            if (SENSOR_3 != INPUT_REDCOLOR) { //se ele não esta vendo vermelho
              TextOut(15, LCD_LINE1, "Sol", true);
              Wait(5000);
              ligar();
            } else {
              TextOut(15, LCD_LINE1, "Chuva", true);
              Wait(5000);
              desligar();
            }

          }while(SENSOR_2 != 0){
            desligar();
            TextOut(15, LCD_LINE1, "Cheio", true);
            Wait(5000);
          }
        }while(SENSOR_1 == 0){
          //se panico apertodo ele para tudo
          Off(OUT_ABC);
          //TextOut (int x, int y, string str,options)
          TextOut(15, LCD_LINE1, "Panico", true);
          Wait(5000);
        }
      }
