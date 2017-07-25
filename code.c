//Bluetooth
//0 tempo limpo
//1 tempo sujo
#
define BT_CONN 0
// st variavel de esta do do BT
# define st 0
// Out_A motor desce e sobe a pá
// Out_B motor gira a pá
// Out_C motor esteira
# define P 40 // the proportional part P(t), the integrative part I(t) and the derivative part D(t)
# define I 40 //
# define D 90 //

# define INBOX 1# define OUTBOX 5
//------------------------------------------------------------------
// verifica se tem conexao de BT se nao tem nem liga
sub BTCheck(int conn) {
    if (!BluetoothStatus(conn) == NO_ERR) {
      TextOut(5, LCD_LINE2, "Error");
      Wait(1000);
      Stop(true);
    }
    //------------------------------------------------------------------
    // sub rotina Tem chuva 
    //------------------------------------------------------------------
    sub temchuva() {
        //cria o valor in
        int in ;
        // checa o estado do BT se 0 manda erro (BT OFF)
        BTCheck(0); //check master connection
        // recebe do mestre um valor
        ReceiveRemoteNumber(INBOX, true, in );
        // a variavel de estado do BT fica igual valor lido
        st == in ;
      }
      //------------------------------------------------------------------
      // sub rotina desce pá
      //------------------------------------------------------------------
    sub desce_pa() {
      // porta, velocidade, angulo, the proportional part P(t), the integrative part I(t) and the derivative part D(t)
      RotateMotorPID(OUT_A, 100, 90, P, I, D);
      // espera 3000ms para fazer outra coisa
      Wait(3000);
    }

    //------------------------------------------------------------------
    // sub rotina sobe pá
    //------------------------------------------------------------------
    sub sobe_pa() {
      // porta, velocidade, angulo, the proportional part P(t), the integrative part I(t) and the derivative part D(t)
      RotateMotorPID(OUT_A, 100, -90, P, I, D);
      // espera 3000ms para fazer outra coisa
      Wait(3000);
    }

    task main() {
        SetSensor(IN_1, SENSOR_TOUCH);
// estado inicial é esse
        desce_pa();
            //ligo a pá com 100% do motor
            OnFwd(OUT_B, 100);
            //ligo a esteira com 10% do motor
            OnFwd(OUT_C, 10);
        //*****************************************************************
        //botao de panico
        do {
          temchuva();
          if (st == 0) {
            desce_pa();
            //ligo a pá com 100% do motor
            OnFwd(OUT_B, 100);
            //ligo a esteira com 10% do motor
            OnFwd(OUT_C, 10);
            while (st == 0) {
              temchuva();
            }
              if(st==1){
                  // paro as pa
                  stop(OUT_B);
                  // subo
                  sobe_pa();
                  // espero
                  Wait(5000);
                  // paro esteira
                  stop(OUT_B);
                  
              }
          }
          while (SENSOR_TOUCH == 1);

        }
      }
      //------------------------------------------------------------------
