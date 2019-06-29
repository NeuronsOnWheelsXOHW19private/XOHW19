#include "hls_stream.h"
#include <cmath>
#include <string.h>

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
struct stream_out_data{
	float data;
	bool last;
};

float relu(float num);
float sigmoid(float numero);
void kernel(hls::stream<float> &in, hls::stream<stream_out_data> &out){
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
float peso;
float bias;
float input;
float bfc4 = 0.09739377349615097;
stream_out_data temp;

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
							input = in.read();
							peso  = in.read();
							sol=sol+input * peso;
						}
					}
				}
				sol = sol + bias;
				temp.data=relu(sol);
				temp.last=0;
				out.write(temp);
				sol = 0;
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
							input = in.read();
							peso  = in.read();
							sol=sol+input * peso;
						}
					}
				}
				sol = sol + bias;
				temp.data=relu(sol);
				temp.last=0;
				out.write(temp);
				sol = 0;
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
							input = in.read();
							peso  = in.read();
							sol=sol+input * peso;
						}
					}
				}
				sol = sol + bias;
				temp.data=relu(sol);
				temp.last=0;
				out.write(temp);
				sol = 0;
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
							input = in.read();
							peso  = in.read();
							sol=sol+input * peso;
						}
					}
				}
				sol = sol + bias;
				temp.data=relu(sol);
				temp.last=0;
				out.write(temp);
				sol = 0;
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
							input = in.read();
							peso  = in.read();
							sol=sol+input * peso;
						}
					}
				}
				sol = sol + bias;
				temp.data=relu(sol);
				temp.last=0;
				out.write(temp);
				sol = 0;
			}
		}
		i = i + 1;
	}
//End of con. Layers-- Reshape before the fully connected layers

//Start of fully connected layers
//Fully connected layer1
i = 0;
j = 0;
sol = 0.0;
for(i=0;i<100;i++){
	for(j=0;j<1152;j++){
		input = in.read();
		peso  = in.read();
		sol=sol+input * peso;
	}
	sol = sol + bias;
	temp.data=relu(sol);
	temp.last=0;
	out.write(temp);
	sol = 0;
}
//fully connected layer 2
i = 0;
j = 0;
for(i=0;i<50;i++){
	for(j=0;j<100;j++){
		input = in.read();
		peso  = in.read();
		sol=sol+input * peso;
	}
	sol = sol + bias;
	temp.data=relu(sol);
	temp.last=0;
	out.write(temp);
	sol = 0;
}
//fully connected layer 3
i = 0;
j = 0;
for(i=0;i<10;i++){
	for(j=0;j<50;j++){
		input = in.read();
		peso  = in.read();
		sol=sol+input * peso;

	}
	sol = sol + bias;
	temp.data=relu(sol);
	temp.last=0;
	out.write(temp);
	sol = 0;
}
//fully connected layer 4
j = 0;
for(j=0;j<10;j++){
		input = in.read();
		peso  = in.read();
		sol=sol+input * peso;
	}
fc4out = sol+bfc4;
temp.data= 3*sigmoid(fc4out);
temp.last=1;
out.write(temp);
}
float relu(float num){
		if(num>0){
			return num;
		}
		if (num<=0) {
			return 0.0;
		}
	}
	float sigmoid(float numero){

		return (1 / (1+ exp(-numero)));

	}








