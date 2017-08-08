      // OUT_A motor segurana da pá
      // OUT_B motor pá
      // OUT_C motor da esteira
      // IN_1 Sensor de toque - Panico
      // IN_2 sensor de toque - Lixo
      // IN_3 sensor de cor - Chuva - substitui o BT
      // rotina desligar errada
      sub ligar() {
        // porta, velocidade, angulo, the proportional part P(t), the integrative part I(t) and the derivative part D(t)
        RotateMotorPID(OUT_A, 70, 45, 40, 40, 90);
        Wait(3000);
        while (SENSOR_3 < 40) {
          //ligo a esteira com 10% do motor
          OnFwd(OUT_C, 20);
          //ligo a pá com 100% do motor
          OnFwd(OUT_B, 35);
        }
      }

      sub desligar() {
        // paro as pa
        if (SENSOR_3 > 40) {
          Coast(OUT_B); //diminuir o motor
          // porta, velocidade, angulo, the proportional part P(t), the integrative part I(t) and the derivative part D(t)
          RotateMotorPID(OUT_A, 70, -45, 40, 40, 90);
          // espera 3000ms para fazer outra coisa
          Wait(3000);
          // paro esteira
          Off(OUT_C);
        }
      }

      // enquanto panico não pertado ele faz algo
      task main() {
          SetSensor(IN_1, SENSOR_TOUCH); // define sensor entrada 1 como sensor de toque {panico}
          SetSensor(IN_2, SENSOR_TOUCH); // define sensor entrada 2 como sensor de toque {coletor de lixo}
          //SetSensor(S3,SENSOR_COLORRED,100); // define sensor de cor na entrada 3 utilizando todas as corres {sensor de chuva}
          //SetSensorColorFull(S3);		// uma apostila seta assim
          SetSensorLight(S3); // uma apostila seta assim

          do { // Se sensor 1 não apertado faça...
            //TextOut (int x, int y, string str,options)
            TextOut(15, LCD_LINE1, "OK", true);
            Wait(5000);
            //colocar rotina aqui
            do {
              TextOut(15, LCD_LINE1, "livre", true);
              Wait(5000);
              // sensor de cor
              do { //se ele não esta vendo vermelho
                TextOut(15, LCD_LINE1, "Sol", true);
                Wait(5000);
                ligar();
              } while (SENSOR_3 > 40); //condição de saida do do

              if (SENSOR_3 > 40) { // sai do do e l^isso
                {
                  TextOut(15, LCD_LINE1, "Chuva", true);
                  Wait(800);
                  desligar();
                }
              }
              while (SENSOR_2 != 0);
              if (SENSOR_2 != 0) {
                TextOut(15, LCD_LINE1, "Cheio", true);
                desligar();
                Wait(5000);
              }
            } while (SENSOR_1 == 0)
            if (SENSOR_1 == 0) {
              //se panico apertodo ele para tudo
              Off(OUT_ABC);
              //TextOut (int x, int y, string str,options)
              TextOut(15, LCD_LINE1, "Panico", true);
              Wait(5000);
            }
          }
