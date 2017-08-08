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
        
          Coast(OUT_B); //diminuir velocidade do motor da Pã
          // porta, velocidade, angulo, the proportional part P(t), the integrative part I(t) and the derivative part D(t)
          RotateMotorPID(OUT_A, 70, -45, 40, 40, 90);
          // espera 3000ms para fazer outra coisa
          Wait(3000);
          // Parar motor da esteira
          Off(OUT_C);
        }

      // enquanto panico não pertado ele faz algo
      task main() {
          SetSensor(IN_1, SENSOR_TOUCH); // define sensor entrada 1 como sensor de toque {panico}
          SetSensor(IN_2, SENSOR_TOUCH); // define sensor entrada 2 como sensor de toque {coletor de lixo}
          SetSensorLight(S3); // uma apostila seta assim

          do { // Se sensor 1 não apertado faça...
            TextOut(15, LCD_LINE1, "OK", true);   //TextOut (int x, int y, string str,options)
            Wait(3000); // Espera 3s antes de fazer qualquer coisa
            
            do {// Se sensor 2 não apertado faça...
              TextOut(15, LCD_LINE1, "livre", true);
              Wait(3000);

              do { // sol/chuva - Se sensor 3...
                TextOut(15, LCD_LINE1, "Sol", true);
                Wait(1000);               // Espera 1s
                ligar();                  // Executa subrotina ligar
              } while (SENSOR_3 > 40);    // Condição de saida do "do" 
                  // é necessario esse if? acho que não testar sem.
              if (SENSOR_3 > 40) { // saio do "do" "sol/chuva" e verifico isso
                {
                  TextOut(15, LCD_LINE1, "Chuva", true);
                  Wait(800);              // Espera 1s
                  desligar();             // Executa subrotina ligar
                }
              }
              while (SENSOR_2 != 0);                  //Saida do do "Livre/Cheio"
              // é necessario esse if? acho que não testar sem.
              if (SENSOR_2 != 0) {                    // saio do "do" "livre/Cheio" e verifico isso
                TextOut(15, LCD_LINE1, "Cheio", true); // Aviso que está cheio
                desligar();                            // executo a rotina desligar
                Wait(5000);                            // espero 3s
              }
            } while (SENSOR_1 == 1)                   // Saida deo sensor Panico
            if (SENSOR_1 == 1) {                      // Saio do "do" "sensor panico" e verifico 
              //se panico apertodo ele para tudo
              Off(OUT_ABC);
              //TextOut (int x, int y, string str,options)
              TextOut(15, LCD_LINE1, "Panico", true);
              Wait(5000);
            }
          }
