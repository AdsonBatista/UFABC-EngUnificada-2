// Primeiro ela inicia o processo
	Liga BT
	Conecta o BT
	recebe sinal da mensagem
	Liga motor pá para descer {}
	Liga motor esteira {}
	Liga motor pá para rotacionar {}
	Monitora S_T
	if(S_T=1){
		// contato no sensor de toque
		Emite aviso
		Desligo motor rotacionamento da pá{}
		Liga motor - pá subir {}
		Tempo de espera {} //lixo da esteira subir
		Desligo motor da esteira {}
		}

// Panico - Para todo sistema se 0 sistema funciona se 1 sistema desliga

if(panico=0){
	//Panico ==0 - Sistema funciona normal
	//verifica estado do BT (ou do texto) de x em x tempo // b=0 -> Tempo limpo b=1 -> tipo esse ocorre sempre independente do resto.
	if(b=0){
		// B=0 => Tempo bom
		// Se tempo bom ele pode fazer duas coisa dependendo do estado anterior
		// se Sai de tempo ruim para tempo bom) B_1=1 então ela liga.
		// se tempo anteior(B_1) é bom então ela continua funcionando em regime permanente	
		if(B_1=0){
			//funciona em regime permanente - mantem tudo funcionando
			// pá baixa
			// motor da pá ligado
			// motor da esteira ligada
			// monitorando sensor de toque
		}else{
			//B_1=1 -> execulta procedimento para ligar
			monitora sensor de toque na caçamba (S_T)
			//se sensor de toque S_T=0 - sem contato
			if(S_T=0){
			Liga motor pá para descer {}
			Liga motor esteira {}
			Liga motor pá para rotacionar {}
			Monitora S_T
			if(S_T=1){
				// contato no sensor de toque
				Emite aviso
				Desligo motor rotacionamento da pá{}
				Liga motor - pá subir {}
				Tempo de espera {} //lixo da esteira subir
				Desligo motor da esteira {}
				}
			}
		}
	}else{
		// B=1 => tempo ruim
		// Se tempo ruim ele pode fazer duas coisa dependendo do estado anterior
		// se Sai de tempo bom para tempo ruim) B_1=0 então ela delisga.
		// se tempo anteior(B_1) é ruim então ela continua parada
		if(B_1=0){
			//B_1=0 -> execulta procedimento para desligar
			Desligo motor rotacionamento da pá{}
			Liga motor pá subir {}
			Tempo de espera {}
			Desligo motor da esteira {}
			Monitora S_T
			if (S_T=1) {
				Emite aviso
			}
		}else{
			não faz nada (continua desligada lendo o BT ou o texto)
		}	
	}
}else{
	// Panico==1 - Sistema para de funcionar
	// Condição botão de pânico só irá funcionar se o sistema estiver em funcionamento pleno.
	desligo motor rotacionamento da pá{}
	liga motor pá subir {}
	Tempo de espera {}
	desligo motor da esteira {}
}
