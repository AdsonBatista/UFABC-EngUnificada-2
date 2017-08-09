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

          do { // Se sensor 1 (botão de pânico) não apertado faça...
            TextOut(15, LCD_LINE1, "OK", true);   //TextOut (int x, int y, string str,options)
            Wait(3000); // Espera 3s antes de fazer qualquer coisa

            do {// Se sensor 2 (sensor de lixo) não apertado faça...
              TextOut(15, LCD_LINE1, "livre", true);
             // luminosidade 
             NumOut(15, LCD_LINE3, SENSOR_3,true);
             // cacamba
              NumOut(15, LCD_LINE5, SENSOR_2,true);
             //panico 
             NumOut(15, LCD_LINE7, SENSOR_1,true); 
              Wait(3000);

              do { // sol/chuva - Se sensor 3...
                TextOut(15, LCD_LINE1, "Sol", true);
                Wait(1000);               // Espera 1s
                ligar();                  // Executa subrotina ligar
              } while (SENSOR_3 > 40);    // Condição de saida do "do"
                  // é necessario esse if? acho que não testar sem.
                  TextOut(15, LCD_LINE1, "Chuva", true);
                  Wait(800);              // Espera 1s
                  desligar();             // Executa subrotina ligar
             
          } while (SENSOR_2 != 0);                  //Saida do do "Livre/Cheio"
                // Saio do "do" "livre/Cheio" e faço isso
                TextOut(15, LCD_LINE1, "Cheio", true); // Aviso que está cheio
                desligar();                            // executo a rotina desligar
                Wait(5000);                            // espero 3s
            
            }while (SENSOR_1 == 1);  // Saida do "do" Panico
              // Quando saio do "do" apertodo ele para tudo
              Off(OUT_ABC);
              // TextOut (int x, int y, string str,options)
              TextOut(15, LCD_LINE1, "Panico", true);
              Wait(25000); // Espera 15s antes de desligar tudo
            
          }
      
