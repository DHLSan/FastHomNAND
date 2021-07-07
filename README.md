# FastHomNAND
Acceleration of TFHE-based Homomorphic NAND Gate on FPGA

Fully homomorphic encryption (FHE) allows secure operation of signal processing in the cloud. The encrypted signals that we send to the cloud can be processed without decrypting the signals. Recently, many studies have been done on different variants for the FHE construct. These variants include complex and compute-heavy computational algorithms. As an example of these algorithms; bootstrapping, forward, and reverse FFT transformations can be given. In this study, the Torus (TFHE) fast full homomorphic encryption library was analyzed on an embedded system. NTT has been added to the THFE library, which is thought to be an advantage for embedded systems. With the added NTT, the system was tested Ultra96-V2 and the results were compared. TFHE, which we propose with NTT application, performs better in multiplying ring polynomials than FFT versions of TFHE on embedded platform. Also,Homomorphic NAND gate operation accelerated with efficient polynomial multiplication system thanks to NTT.

![ntt](https://user-images.githubusercontent.com/58776510/124762788-f2881080-df3b-11eb-8c91-96c610ef32a4.png)

