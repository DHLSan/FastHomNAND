# FastHomNAND
Acceleration of TFHE-based Homomorphic NAND Gate on FPGA

Fully homomorphic encryption (FHE) allows secure operation of signal processing in the cloud. The encrypted signals that we send to the cloud can be processed without decrypting the signals. Recently, many studies have been done on different variants for the FHE construct. These variants include complex and compute-heavy computational algorithms. As an example of these algorithms; bootstrapping, forward, and reverse FFT transformations can be given. In this study, the Torus (TFHE) fast full homomorphic encryption library was analyzed on an embedded system. NTT has been added to the THFE library, which is thought to be an advantage for embedded systems. With the added NTT, the system was tested Ultra96-V2 and the results were compared. TFHE, which we propose with NTT application, performs better in multiplying ring polynomials than FFT versions of TFHE on embedded platform. Also,Homomorphic NAND gate operation accelerated with efficient polynomial multiplication system thanks to NTT.

![ntt](https://user-images.githubusercontent.com/58776510/124762788-f2881080-df3b-11eb-8c91-96c610ef32a4.png)


## Team and Project Information
- University name: Eskisehir Technical University
- Students: Batuhan Bulut (batuhanbulut@eskisehir.edu.tr)
- Supervisor: Assist. Prof. Dr. Ismail San (isan@eskisehir.edu.tr)
-  Team Number : xohw21-198
- The Board Used In Project: Ultra96-V2
- Youtube Link for Detailed Presentation :  https://www.youtube.com/watch?app=desktop&v=Yz9s4SajXfA&t=5s

Welcome to the FastHomNAND project. This project is based on a Fully Homomorphic Libary which name is TFHE. You can find in the following link: https://github.com/tfhe/tfhe

In this study, we present NTT-based polynomial multiplication for TFHE polynomial computation on embedded software system instead of using FFT-based polynomial multiplication on TFHE.
This study aims to observe the efficiency of polynomial multiplications on embedded systems and thus speed up the homomorphic NAND gate operation. Using the NTT-based polynomial multiplication method, the homomorphic NAND gate operation in the TFHE system on the Ultra96-V2 Board has been accelerated with software and hardware-based improvements.

## Project dependencies 

In order to use the above-mentioned TFHE library, a flag compatible with C+11 directives must be set on the compiler.

THE library needs a high stack size of about 300MB. Default values should be changed on Complier and a compatible value should be assigned to this value.

The codes shared in this project are about the polynomial multiplication operation that limits the homomorphic Nand gate function. The homomorphic NAND gate logic gate is also accelerated in direct proportion to the acceleration coefficient of this processing.


## What do the files contain ?

- #### Vitis HLS 2020.2
    This folder contains the generated ntt_IPS core from Vitis HLS.
- #### Vitis 2020.2
    This folder contains the C source files used for building the rest of the design as the software side of the project.
- ### Vivado 2020.2
This folder contains hardware design of project.
- ### Project Report
This folder contains detailed report of FastHomNAND
  

