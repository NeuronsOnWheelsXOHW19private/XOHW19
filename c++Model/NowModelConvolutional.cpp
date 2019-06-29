#include <fstream>
#include <cmath>
#include <iostream>
#include <cstdlib>
#define L1_weight_width 5
#define L1_outchannels 24
#define L1_HBoard 98
#define L1_Vboard 31
#define L1_in_channels 3
#define L1_stride 2
#define L2_weight_width 5
#define L2_outchannels 36
#define L2_HBoard 47
#define L2_Vboard 14
#define L2_in_channels 24
#define L2_stride 2
#define L3_weight_width 5
#define L3_outchannels 48
#define L3_HBoard 22
#define L3_Vboard 5
#define L3_in_channels 36
#define L3_stride 2
#define L4_weight_width 3
#define L4_outchannels 64
#define L4_HBoard 20
#define L4_Vboard 3
#define L4_in_channels 48
#define L4_stride 1
#define L5_weight_width 3
#define L5_outchannels 64
#define L5_HBoard 18
#define L5_Vboard 1
#define L5_in_channels 64
#define L5_stride 1
using namespace std;
float relu(float num);
float sigmoid(float numero);
float fastSigmoid(float numero);
int main(){
float input[66][200][3]; //immagine in input
float L1_output[31][98][24];
float L2_output[14][47][36];
float L3_output[5][22][48];
float L4_output[3][20][64];
float L5_output[1][18][64];
float fc1out[100];
float fc2out[50];
float fc3out[10];
float fc4out;
int outCH=0;
int inCH=0;
int riga=0;
int col=0;
float sol=0.0;
int i=0;
int j=0;
int h=0;
int t=0;
float s;
// i pesi dei conv. Layer
float wc1[5][5][3][24];
float wc2[5][5][24][36];
float wc3[5][5][36][48];
float wc4[3][3][48][64];
float wc5[3][3][64][64];
float output = 10.0;
//Bias of con. layer
float bc1[24];
float bc2[36];
float bc3[48];
float bc4[64];
float bc5[64];
//i pesi dei fully Connected
float fc1[1152][100];
float fc2[100][50];
float fc3[50][10];
float fc4[10];
//bias dei fully connnected
float bfc1[100];
float bfc2[50];
float bfc3[10];
float bfc4 = 0.09739377349615097;
// Inizializzazione dell'input
ifstream take("C:\NeuronsOnWheels\TestInput\input167.txt");
for(i=0;i<66;i++){
 	for(j=0;j<200;j++){
    	for(t=0;t<3;t++){
    		take >> s;
            input[i][j][t] = s;
        }
	}
}
take.close();
//Parte l'inizializzazione dei pesi
i=0;
j=0;
h=0;
t=0;
ifstream take1("C:\NeuronsOnWheels\weights\Wc1Now.txt");
for (i=0; i<24;i++){
	for (j=0; j<3;j++){
		for (h=0; h<5;h++){
			for (t=0; t<5;t++){
				take1 >> s;
                wc1[h][t][j][i]=s; //il result[s] verrà preso dalla riga s-esima del file

            }
        }
    }
}
take1.close();
i=0;
j=0;
h=0;
t=0;
ifstream take2("C:\NeuronsOnWheels\weights\Wc2Now.txt");

for (i=0; i<36;i++){
	for (j=0; j<24;j++){
		for (h=0; h<5;h++){
			for (t=0; t<5;t++){
                take2 >> s;
				wc2[h][t][j][i]=s; //il result[s] verrà preso dalla riga s-esima del file
            }
        }
    }
}
take2.close();
ifstream take3("C:\NeuronsOnWheels\weights\Wc3Now.txt");
i=0;
j=0;
h=0;
t=0;
for (i=0; i<48;i++){
	for (j=0; j<36;j++){
		for (h=0; h<5;h++){
			for (t=0; t<5;t++){
                take3 >> s;
				wc3[h][t][j][i]=s; //il result[s] verrà preso dalla riga s-esima del file
            }
        }
    }
}
take3.close();
ifstream take4("C:\NeuronsOnWheels\weights\Wc4Now.txt");
i=0;
j=0;
h=0;
t=0;
for (i=0; i<64;i++){
	for (j=0; j<48;j++){
		for (h=0; h<3;h++){
			for (t=0; t<3;t++){
                take4 >> s;
				wc4[h][t][j][i]=s; //il result[s] verrà preso dalla riga s-esima del file
            }
        }
    }
}

take4.close();
ifstream take5("C:\NeuronsOnWheels\weights\Wc5Now.txt");
i=0;
j=0;
h=0;
t=0;
for (i=0; i<64;i++){
	for (j=0; j<64;j++){
		for (h=0; h<3;h++){
			for (t=0; t<3;t++){
				take5 >> s;
                wc5[h][t][j][i]=s; //il result[s] verrà preso dalla riga s-esima del file
            }
        }
    }
}
take5.close();
//inizializzaione dei pesi dei fully connected
ifstream take6("C:\NeuronsOnWheels\weights\fc1Now.txt");
i=0;
j=0;
h=0;
t=0;
for (h=0; h<1152; h++){
	for (t=0; t<100; t++){
        take6 >> s;
		fc1[h][t]=s;
	}
}

take6.close();
ifstream take7("C:\NeuronsOnWheels\weights\fc2Now.txt");
h=0;
t=0;
for (h=0; h<100; h++){
	for (t=0; t<50; t++){
        take7 >> s;
		fc2[h][t]=s;
	}
}
take7.close();

ifstream take8("C:\NeuronsOnWheels\weights\fc3Now.txt");
h=0;
t=0;
for (h=0; h<50; h++){
	for (t=0; t<10; t++){
        take8 >> s;
		fc3[h][t]=s;
	}
} 
take8.close();
ifstream take9("C:\NeuronsOnWheels\weights\fc4Now.txt");
h=0;
t=0;
for (h=0; h<10; h++){
    take9 >> s;
	fc4[h]=s;
}       
take9.close();
//Inizializzazione dei bias
h=0;
ifstream take10("C:\NeuronsOnWheels\Bias\bc1Now.txt");
for (h=0; h<24; h++){
        take10 >> s;
		bc1[h] = s;
}      
h=0;
take10.close();
ifstream take11;
take11.open("C:\NeuronsOnWheels\Bias\bc2Now.txt");
for (h=0; h<36; h++){
        take11 >> s;
		bc2[h] = s;
}       
h=0;
ifstream take12("C:\NeuronsOnWheels\Bias\bc3Now.txt");
for (h=0; h<48; h++){
        take12 >> s;
		bc3[h] = s;
}      
h=0;
take12.close();
ifstream take13("C:\NeuronsOnWheels\Bias\bc4Now.txt");
for (h=0; h<64; h++){
        take13 >> s;
		bc4[h] = s;
}      
take13.close();
h=0;
ifstream take14("C:\NeuronsOnWheels\Bias\bc5Now.txt");
for (h=0; h<64; h++){
        take14 >> s;
		bc5[h] = s;
}      
h=0;
take14.close();
ifstream take15("C:\NeuronsOnWheels\Bias\bfc1Now.txt");
for (h=0; h<100; h++){
        take15 >> s;
		bfc1[h] = s;
}      
h=0;
take15.close();
ifstream take16("C:\NeuronsOnWheels\Bias\bfc2Now.txt");
for (h=0; h<50; h++){
        take16 >> s;
		bfc2[h] = s;
}      
h=0;
take16.close();
ifstream take17;
take17.open("C:\NeuronsOnWheels\Bias\bfc3Now.txt");
for (h=0; h<10; h++){
        take17 >> s;
		bfc3[h] = s;
}     
        
        
        
//finisce inizializzazione dei pesi
//**********START*********
//***********OF***********
//**********NOW***********
//*********MODEL**********
outCH=0;
inCH=0;
riga=0;
col=0;
sol=0;
i=0;
j=0;
h=0;
t=0;
for(outCH=0; outCH<L1_outchannels; outCH++){
		for (j=0; j<L1_Vboard; j++){
			for(h=0; h<L1_HBoard; h++){
				for(inCH=0; inCH<L1_in_channels; inCH++){
					for(riga=0; riga<L1_weight_width; riga++){
						for(col=0; col<L1_weight_width; col++){
							fpgain.write(input[riga+L1_stride*j][col+L1_stride*h][inCH]);
							fpgain.write(wc1[riga][col][inCH][outCH];);
							 
						}	//non raggiunge ultime righe (fino a 198) fare +1 in tutti i cicli
					}
				}
				fpgain.write(bc1[i]);
				risultato=fpgaout.read();
				L1_output[j][h][outCH] = risultato.data;
			}
		}
		i = i + 1;
	}

outCH=0;
inCH=0;
riga=0;
col=0;
sol=0;
i=0;
j=0;
h=0;
t=0;
for(outCH=0; outCH<L2_outchannels; outCH++){
		for (j=0; j<L2_Vboard; j++){
			for(h=0; h<L2_HBoard; h++){
				for(inCH=0; inCH<L2_in_channels; inCH++){
					for(riga=0; riga<L2_weight_width; riga++){
						for(col=0; col<L2_weight_width; col++){
							fpgain.write(L1_output[riga+L2_stride*j][col+L2_stride*h][inCH]);
							fpgain.write(wc2[riga][col][inCH][outCH]);
						}
					}
				}
				fpgain.write(bc2[i]);
				risultato=fpgaout.read();
				L2_output[j][h][outCH] = risultato.data;
			
				sol=0;
			}
		}
		i = i + 1;
	}
outCH=0;
inCH=0;
riga=0;
col=0;
sol=0;
i=0;
j=0;
h=0;
t=0;
for(outCH=0; outCH<L3_outchannels; outCH++){
		for (j=0; j<L3_Vboard; j++){
			for(h=0; h<L3_HBoard; h++){
				for(inCH=0; inCH<L1_in_channels; inCH++){
					for(riga=0; riga<L3_weight_width; riga++){
						for(col=0; col<L3_weight_width; col++){
							fpgain.write(L2_output[riga+L3_stride*j][col+L3_stride*h][inCH]);
							fpgain.write(wc3[riga][col][inCH][outCH]);
						}	//non raggiunge ultime righe (fino a 198) fare +1 in tutti i cicli
					}
				}
				fpgain.write(bc2[i]);
				risultato=fpgaout.read();
				L3_output[j][h][outCH] = risultato.data;
			
				sol=0;
			}
		}
		i = i + 1;
	}
outCH=0;
inCH=0;
riga=0;
col=0;
sol=0;
i=0;
j=0;
h=0;
t=0;
for(outCH=0; outCH<L4_outchannels; outCH++){
		for (j=0; j<L4_Vboard; j++){
			for(h=0; h<L4_HBoard; h++){
				for(inCH=0; inCH<L4_in_channels; inCH++){
					for(riga=0; riga<L4_weight_width; riga++){
						for(col=0; col<L4_weight_width; col++){
							fpgain.write(L3_output[riga+L4_stride*j][col+L4_stride*h][inCH]);
							fpgain.write(wc4[riga][col][inCH][outCH]);
						}	
					}
				}
				fpgain.write(bc4[i]);
				risultato=fpgaout.read();
				L4_output[j][h][outCH] = risultato.data;
				sol=0;
			}
		}
		i = i + 1;
	}
outCH=0;
inCH=0;
riga=0;
col=0;
sol=0;
i=0;
j=0;
h=0;
t=0;
for(outCH=0; outCH<L5_outchannels; outCH++){
		for (j=0; j<L5_Vboard; j++){
			for(h=0; h<L5_HBoard; h++){
				for(inCH=0; inCH<L5_in_channels; inCH++){
					for(riga=0; riga<L5_weight_width; riga++){
						for(col=0; col<L5_weight_width; col++){
							fpgain.write(L4_output[riga+L5_stride*j][col+L5_stride*h][inCH]);
							fpgain.write(wc5[riga][col][inCH][outCH]);
						}	
					}
				}
				fpgain.write(bc5[i]);
				risultato=fpgaout.read();
				L5_output[j][h][outCH] = risultato.data;
				sol=0;
			}
		}
		i = i + 1;
	}
//End of con. Layers-- Reshape before the fully connected layers
float reshape[1152];
int c = 0;
i = 0;
j = 0;
h = 0;
// prova a togliere il ciclo della j
for(i=0;i<L5_outchannels;i++){
			for(h=0;h<18;h++){
				reshape[c]=L5_output[0][h][i];
				c=c+1;
			}
	}
//Start of fully connected layers
//Fully connected layer1
i = 0;
j = 0;
sol = 0.0;
for(i=0;i<100;i++){
	for(j=0;j<1152;j++){
		fpgain.write(reshape[j]);
		fpgain.write(fc1[j][i]);
	}
	fpgain.write(bfc1[i]);
	risultato=fpgaout.read();
	fc1out[i] = risultato.data;
	sol=0;
}
//fully connected layer 2
i = 0;
j = 0;
for(i=0;i<50;i++){
	for(j=0;j<100;j++){
		fpgain.write(fc1out[j]);
		fpgain.write(fc2[j][i]);
	}
	fpgain.write(bfc2[i]);
	risultato=fpgaout.read();
	fc2out[i] = risultato.data;
	sol=0;
}
//fully connected layer 3
i = 0;
j = 0;
for(i=0;i<10;i++){
	for(j=0;j<50;j++){
		fpgain.write(fc2out[j]);
		fpgain.write(fc3[j][i]);

	}
	fpgain.write(bfc3[i]);
	risultato=fpgaout.read();
	fc3out[i] = risultato.data;
	sol=0;
}
//fully connected layer 4
j = 0;	
for(j=0;j<10;j++){
		fpgain.write(fc3out[j]);
		fpgain.write(fc4[j]);
	}

risultato=fpgaout.read();
cout << "risultato=" << output <<endl;
return 0;
}
float relu(float num){
	if(num>0){
		return num;
	}
	if (num<=0) {
		return 0;
	}
}
float sigmoid(float numero){

	return (1 / (1+ exp(-numero)));
}
//nel caso velocizzare ulteriormente il calcolo
float fastSigmoid(float numero){
	return (numero / (1 + abs(numero)));
}

/////
////
////QUA INIZIA FPGA






















#include <fstream>
#include <cmath>
#include <iostream>
#include <cstdlib>
#define L1_weight_width 5
#define L1_outchannels 24
#define L1_HBoard 98
#define L1_Vboard 31
#define L1_in_channels 3
#define L1_stride 2
#define L2_weight_width 5
#define L2_outchannels 36
#define L2_HBoard 47
#define L2_Vboard 14
#define L2_in_channels 24
#define L2_stride 2
#define L3_weight_width 5
#define L3_outchannels 48
#define L3_HBoard 22
#define L3_Vboard 5
#define L3_in_channels 36
#define L3_stride 2
#define L4_weight_width 3
#define L4_outchannels 64
#define L4_HBoard 20
#define L4_Vboard 3
#define L4_in_channels 48
#define L4_stride 1
#define L5_weight_width 3
#define L5_outchannels 64
#define L5_HBoard 18
#define L5_Vboard 1
#define L5_in_channels 64
#define L5_stride 1
using namespace std;
float relu(float num);
float sigmoid(float numero);
float fastSigmoid(float numero);
int main(){
float input[66][200][3]; //immagine in input
float L1_output[31][98][24];
float L2_output[14][47][36];
float L3_output[5][22][48];
float L4_output[3][20][64];
float L5_output[1][18][64];
float fc1out[100];
float fc2out[50];
float fc3out[10];
float fc4out;
int outCH=0;
int inCH=0;
int riga=0;
int col=0;
float sol=0.0;
int i=0;
int j=0;
int h=0;
int t=0;
float s;
// i pesi dei conv. Layer
float wc1[5][5][3][24];
float wc2[5][5][24][36];
float wc3[5][5][36][48];
float wc4[3][3][48][64];
float wc5[3][3][64][64];
float output = 10.0;
//Bias of con. layer
float bc1[24];
float bc2[36];
float bc3[48];
float bc4[64];
float bc5[64];
//i pesi dei fully Connected
float fc1[1152][100];
float fc2[100][50];
float fc3[50][10];
float fc4[10];
//bias dei fully connnected
float bfc1[100];
float bfc2[50];
float bfc3[10];
float bfc4 = 0.09739377349615097;
// Inizializzazione dell'input
ifstream take("input167.txt");
for(i=0;i<66;i++){
 	for(j=0;j<200;j++){
    	for(t=0;t<3;t++){
    		take >> s;
            input[i][j][t] = s;
        }
	}
}
take.close();
//Parte l'inizializzazione dei pesi
i=0;
j=0;
h=0;
t=0;
ifstream take1("Wc1Now.txt");
for (i=0; i<24;i++){
	for (j=0; j<3;j++){
		for (h=0; h<5;h++){
			for (t=0; t<5;t++){
				take1 >> s;
                wc1[h][t][j][i]=s; //il result[s] verrà preso dalla riga s-esima del file

            }
        }
    }
}
take1.close();
i=0;
j=0;
h=0;
t=0;
ifstream take2("Wc2Now.txt");

for (i=0; i<36;i++){
	for (j=0; j<24;j++){
		for (h=0; h<5;h++){
			for (t=0; t<5;t++){
                take2 >> s;
				wc2[h][t][j][i]=s; //il result[s] verrà preso dalla riga s-esima del file
            }
        }
    }
}
take2.close();
ifstream take3("Wc3Now.txt");
i=0;
j=0;
h=0;
t=0;
for (i=0; i<48;i++){
	for (j=0; j<36;j++){
		for (h=0; h<5;h++){
			for (t=0; t<5;t++){
                take3 >> s;
				wc3[h][t][j][i]=s; //il result[s] verrà preso dalla riga s-esima del file
            }
        }
    }
}
take3.close();
ifstream take4("Wc4Now.txt");
i=0;
j=0;
h=0;
t=0;
for (i=0; i<64;i++){
	for (j=0; j<48;j++){
		for (h=0; h<3;h++){
			for (t=0; t<3;t++){
                take4 >> s;
				wc4[h][t][j][i]=s; //il result[s] verrà preso dalla riga s-esima del file
            }
        }
    }
}

take4.close();
ifstream take5("Wc5Now.txt");
i=0;
j=0;
h=0;
t=0;
for (i=0; i<64;i++){
	for (j=0; j<64;j++){
		for (h=0; h<3;h++){
			for (t=0; t<3;t++){
				take5 >> s;
                wc5[h][t][j][i]=s; //il result[s] verrà preso dalla riga s-esima del file
            }
        }
    }
}
take5.close();
//inizializzaione dei pesi dei fully connected
ifstream take6("fc1Now.txt");
i=0;
j=0;
h=0;
t=0;
for (h=0; h<1152; h++){
	for (t=0; t<100; t++){
        take6 >> s;
		fc1[h][t]=s;
	}
}

take6.close();
ifstream take7("fc2Now.txt");
h=0;
t=0;
for (h=0; h<100; h++){
	for (t=0; t<50; t++){
        take7 >> s;
		fc2[h][t]=s;
	}
}
take7.close();

ifstream take8("fc3Now.txt");
h=0;
t=0;
for (h=0; h<50; h++){
	for (t=0; t<10; t++){
        take8 >> s;
		fc3[h][t]=s;
	}
} 
take8.close();
ifstream take9("fc4Now.txt");
h=0;
t=0;
for (h=0; h<10; h++){
    take9 >> s;
	fc4[h]=s;
}       
take9.close();
//Inizializzazione dei bias
h=0;
ifstream take10("bc1Now.txt");
for (h=0; h<24; h++){
        take10 >> s;
		bc1[h] = s;
}      
h=0;
take10.close();
ifstream take11;
take11.open("bc2Now.txt");
for (h=0; h<36; h++){
        take11 >> s;
		bc2[h] = s;
}       
h=0;
ifstream take12("bc3Now.txt");
for (h=0; h<48; h++){
        take12 >> s;
		bc3[h] = s;
}      
h=0;
take12.close();
ifstream take13("bc4Now.txt");
for (h=0; h<64; h++){
        take13 >> s;
		bc4[h] = s;
}      
take13.close();
h=0;
ifstream take14("bc5Now.txt");
for (h=0; h<64; h++){
        take14 >> s;
		bc5[h] = s;
}      
h=0;
take14.close();
ifstream take15("bfc1Now.txt");
for (h=0; h<100; h++){
        take15 >> s;
		bfc1[h] = s;
}      
h=0;
take15.close();
ifstream take16("bfc2Now.txt");
for (h=0; h<50; h++){
        take16 >> s;
		bfc2[h] = s;
}      
h=0;
take16.close();
ifstream take17;
take17.open("bfc3Now.txt");
for (h=0; h<10; h++){
        take17 >> s;
		bfc3[h] = s;
}     
        
        
        
//finisce inizializzazione dei pesi
//**********START*********
//***********OF***********
//**********NOW***********
//*********MODEL**********
outCH=0;
inCH=0;
riga=0;
col=0;
sol=0;
i=0;
j=0;
h=0;
t=0;
for(outCH=0; outCH<L1_outchannels; outCH++){
		for (j=0; j<L1_Vboard; j++){
			for(h=0; h<L1_HBoard; h++){
				for(inCH=0; inCH<L1_in_channels; inCH++){
					for(riga=0; riga<L1_weight_width; riga++){
						for(col=0; col<L1_weight_width; col++){
							sol=sol+input[riga+L1_stride*j][col+L1_stride*h][inCH]*wc1[riga][col][inCH][outCH]; // non raggiunge l'ultima cella di memoria
						}	//non raggiunge ultime righe (fino a 198) fare +1 in tutti i cicli
					}
				}
				L1_output[j][h][outCH]= relu(sol+bc1[i]);
				
				sol=0;
			}
		}
		i = i + 1;
	}

outCH=0;
inCH=0;
riga=0;
col=0;
sol=0;
i=0;
j=0;
h=0;
t=0;
for(outCH=0; outCH<L2_outchannels; outCH++){
		for (j=0; j<L2_Vboard; j++){
			for(h=0; h<L2_HBoard; h++){
				for(inCH=0; inCH<L2_in_channels; inCH++){
					for(riga=0; riga<L2_weight_width; riga++){
						for(col=0; col<L2_weight_width; col++){
							sol=sol+L1_output[riga+L2_stride*j][col+L2_stride*h][inCH]*wc2[riga][col][inCH][outCH];
						}
					}
				}
				L2_output[j][h][outCH]= relu(sol+bc2[i]);
			
				sol=0;
			}
		}
		i = i + 1;
	}
outCH=0;
inCH=0;
riga=0;
col=0;
sol=0;
i=0;
j=0;
h=0;
t=0;
for(outCH=0; outCH<L3_outchannels; outCH++){
		for (j=0; j<L3_Vboard; j++){
			for(h=0; h<L3_HBoard; h++){
				for(inCH=0; inCH<L1_in_channels; inCH++){
					for(riga=0; riga<L3_weight_width; riga++){
						for(col=0; col<L3_weight_width; col++){
							sol=sol+L2_output[riga+L3_stride*j][col+L3_stride*h][inCH]*wc3[riga][col][inCH][outCH];
						}	//non raggiunge ultime righe (fino a 198) fare +1 in tutti i cicli
					}
				}
				L3_output[j][h][outCH]= relu(sol+bc3[i]);
			
				sol=0;
			}
		}
		i = i + 1;
	}
outCH=0;
inCH=0;
riga=0;
col=0;
sol=0;
i=0;
j=0;
h=0;
t=0;
for(outCH=0; outCH<L4_outchannels; outCH++){
		for (j=0; j<L4_Vboard; j++){
			for(h=0; h<L4_HBoard; h++){
				for(inCH=0; inCH<L4_in_channels; inCH++){
					for(riga=0; riga<L4_weight_width; riga++){
						for(col=0; col<L4_weight_width; col++){
							sol=sol+L3_output[riga+L4_stride*j][col+L4_stride*h][inCH]*wc4[riga][col][inCH][outCH];
						}	
					}
				}//non raggiunge ultime righe (fino a 198) fare +1 in tutti i cicli
				L4_output[j][h][outCH]= relu(sol+bc4[i]);
				
				sol=0;
			}
		}
		i = i + 1;
	}
outCH=0;
inCH=0;
riga=0;
col=0;
sol=0;
i=0;
j=0;
h=0;
t=0;
for(outCH=0; outCH<L5_outchannels; outCH++){
		for (j=0; j<L5_Vboard; j++){
			for(h=0; h<L5_HBoard; h++){
				for(inCH=0; inCH<L5_in_channels; inCH++){
					for(riga=0; riga<L5_weight_width; riga++){
						for(col=0; col<L5_weight_width; col++){
							sol=sol+L4_output[riga+L5_stride*j][col+L5_stride*h][inCH]*wc5[riga][col][inCH][outCH];
						}	
					}
				}
				L5_output[j][h][outCH]= relu(sol+bc5[i]);
				sol=0;
			}
		}
		i = i + 1;
	}
//End of con. Layers-- Reshape before the fully connected layers
float reshape[1152];
int c = 0;
i = 0;
j = 0;
h = 0;
// prova a togliere il ciclo della j
for(i=0;i<L5_outchannels;i++){
			for(h=0;h<18;h++){
				reshape[c]=L5_output[0][h][i];
				c=c+1;
			}
	}
//Start of fully connected layers
//Fully connected layer1
i = 0;
j = 0;
sol = 0.0;
for(i=0;i<100;i++){
	for(j=0;j<1152;j++){
		sol = sol+ (reshape[j] * fc1[j][i]);
	}
	fc1out[i] = relu(sol+bfc1[i]);
	sol=0;
}
//fully connected layer 2
i = 0;
j = 0;
for(i=0;i<50;i++){
	for(j=0;j<100;j++){
		sol= sol+fc1out[j]*fc2[j][i];
	}
	fc2out[i] = relu(sol+bfc2[i]);
	sol=0;
}
//fully connected layer 3
i = 0;
j = 0;
for(i=0;i<10;i++){
	for(j=0;j<50;j++){
		sol= sol+fc2out[j]*fc3[j][i];

	}
	fc3out[i] = relu(sol+bfc3[i]);
	sol=0;
}
//fully connected layer 4
j = 0;	
for(j=0;j<10;j++){
		sol= sol+fc3out[j]*fc4[j];
	}
fc4out = sol+bfc4;
output = 3*sigmoid(fc4out);
cout << "risultato=" << output <<endl;
return 0;
}
float relu(float num){
	if(num>0){
		return num;
	}
	if (num<=0) {
		return 0;
	}
}
float sigmoid(float numero){

	return (1 / (1+ exp(-numero)));
}
//nel caso velocizzare ulteriormente il calcolo
float fastSigmoid(float numero){
	return (numero / (1 + abs(numero)));
}

