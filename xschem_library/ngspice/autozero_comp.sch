v {xschem version=3.1.0 file_version=1.2
}
G {}
K {}
V {}
S {}
E {}
L 3 250 -310 250 -120 {}
L 3 410 -310 410 -170 {}
L 3 570 -310 570 -120 {}
L 4 150 -100 250 -100 {}
L 4 250 -120 250 -100 {}
L 4 250 -120 570 -120 {}
L 4 570 -120 570 -100 {}
L 4 570 -100 690 -100 {}
L 4 150 -170 410 -170 {}
L 4 410 -170 410 -150 {}
L 4 410 -150 570 -150 {}
L 4 570 -170 570 -150 {}
L 4 570 -170 690 -170 {}
L 7 1090 -260 2520 -260 {}
B 2 300 -1060 760 -900 {flags=graph
y1 = 0
y2 = 0.93
divy = 5
x1=6.17604e-08
x2=4.71882e-07
divx=5
subdivx=4
unitx=n
node="cal
saout"
color="4 5"
dataset=-1}
B 2 300 -1200 760 -1070 {flags=graph
y1 = 0.647319
y2 = 0.652563
divy = 5
x1=6.17604e-08
x2=4.71882e-07
unitx=n
divx=5
subdivx=4
node="plus
minus"
color="4 5"
dataset=-1}
B 2 300 -1300 760 -1200 {flags=graph
y1 = 0
y2 = 1
divy = 5
x1=6.17604e-08
x2=4.71882e-07
unitx=n
divx=5
subdivx=4
node="en
cal"
color="4 4"
dataset=-1
digital=1
ypos1=0.0602914
ypos2=0.292255}
T {CAL} 140 -180 0 1 0.4 0.4 {}
T {EN} 140 -130 0 1 0.4 0.4 {}
T {CALIBRATION
  30ns} 400 -300 0 1 0.4 0.4 {}
T {SENSING
  30ns} 530 -300 0 1 0.4 0.4 {}
T {OFF} 660 -300 0 1 0.4 0.4 {}
T {OFF} 210 -300 0 1 0.4 0.4 {}
T {NGSPICE MISMATCH SIMULATION} 1210 -310 0 0 0.8 0.8 {}
T {Offset-compensated comparator. Detects +/- 2mv differential signal on PLUS, MINUS.
Output on SAOUT
Gaussian Threshold variation (via delvto parameter) is added to all MOS transistors.} 1110 -240 0 0 0.6 0.6 {}
T {.param ABSVAR=0.05
delvto='agauss(0,ABSVAR,3)'} 1390 -120 0 0 0.6 0.6 {layer=8}
T {Select one or more graphs (and no other objects)
and use arrow keys to zoom / pan waveforms} 310 -1380 0 0 0.3 0.3 {}
N 120 -470 120 -450 {lab=TEMPERAT}
N 160 -1180 190 -1180 {lab=VSS}
N 160 -1150 160 -1130 {lab=VSS}
N 160 -1230 160 -1210 {lab=VSSI}
N 1120 -1100 1150 -1100 {lab=VSS}
N 1120 -1330 1150 -1330 {lab=VCC}
N 1090 -1400 1120 -1400 {lab=VCC}
N 1120 -1400 1120 -1360 {lab=VCC}
N 1090 -970 1120 -970 {lab=VSSI}
N 1120 -1010 1120 -970 {lab=VSSI}
N 980 -1100 1080 -1100 {lab=ZERO0}
N 980 -1260 980 -1100 {lab=ZERO0}
N 900 -1260 980 -1260 {lab=ZERO0}
N 790 -1260 820 -1260 {lab=OUTDIFF}
N 790 -1440 790 -1260 {lab=OUTDIFF}
N 790 -1440 1220 -1440 {lab=OUTDIFF}
N 1120 -1260 1220 -1260 {lab=OUTDIFF}
N 1610 -1100 1640 -1100 {lab=VSS}
N 1610 -1330 1640 -1330 {lab=VCC}
N 1580 -1400 1610 -1400 {lab=VCC}
N 1610 -1400 1610 -1360 {lab=VCC}
N 1580 -970 1610 -970 {lab=VSSI}
N 1610 -1010 1610 -970 {lab=VSSI}
N 1470 -1100 1570 -1100 {lab=ZERO1}
N 1470 -1260 1470 -1100 {lab=ZERO1}
N 1390 -1260 1470 -1260 {lab=ZERO1}
N 1280 -1260 1310 -1260 {lab=SAOUTF}
N 1280 -1440 1280 -1260 {lab=SAOUTF}
N 1280 -1440 1710 -1440 {lab=SAOUTF}
N 1610 -1260 1710 -1260 {lab=SAOUTF}
N 1220 -1440 1220 -1260 {lab=OUTDIFF}
N 1120 -1300 1120 -1260 {lab=OUTDIFF}
N 980 -1330 980 -1260 {lab=ZERO0}
N 1610 -1300 1610 -1260 {lab=SAOUTF}
N 1470 -1330 1470 -1260 {lab=ZERO1}
N 1710 -1440 1710 -1260 {lab=SAOUTF}
N 890 -640 920 -640 {lab=VSS}
N 1060 -640 1090 -640 {lab=VSS}
N 1090 -800 1120 -800 {lab=VCC}
N 860 -800 890 -800 {lab=VCC}
N 930 -800 1050 -800 {lab=GN}
N 930 -800 930 -770 {lab=GN}
N 890 -770 930 -770 {lab=GN}
N 890 -770 890 -670 {lab=GN}
N 1090 -710 1090 -670 {lab=OUTDIFF}
N 890 -860 890 -830 {lab=VCC}
N 990 -860 1090 -860 {lab=VCC}
N 1090 -860 1090 -830 {lab=VCC}
N 1090 -610 1090 -590 {lab=SN}
N 990 -590 1090 -590 {lab=SN}
N 890 -610 890 -590 {lab=SN}
N 990 -510 1020 -510 {lab=VSS}
N 990 -590 990 -540 {lab=SN}
N 990 -880 990 -860 {lab=VCC}
N 960 -380 990 -380 {lab=VSSI}
N 990 -420 990 -380 {lab=VSSI}
N 1470 -510 1500 -510 {lab=VSS}
N 1470 -800 1500 -800 {lab=VCC}
N 1440 -870 1470 -870 {lab=VCC}
N 1470 -870 1470 -830 {lab=VCC}
N 1440 -380 1470 -380 {lab=VSSI}
N 1470 -420 1470 -380 {lab=VSSI}
N 1470 -710 1470 -540 {lab=SAOUTF}
N 1220 -710 1360 -710 {lab=OUTDIFF}
N 890 -860 990 -860 {lab=VCC}
N 890 -590 990 -590 {lab=SN}
N 1120 -1260 1120 -1130 {lab=OUTDIFF}
N 1610 -1260 1610 -1130 {lab=SAOUTF}
N 1360 -710 1360 -510 {lab=OUTDIFF}
N 1220 -1260 1220 -710 {lab=OUTDIFF}
N 1710 -1260 1710 -710 {lab=SAOUTF}
N 1710 -710 1850 -710 {lab=SAOUTF}
N 1090 -710 1220 -710 {lab=OUTDIFF}
N 1090 -770 1090 -710 {lab=OUTDIFF}
N 1360 -800 1360 -710 {lab=OUTDIFF}
N 1470 -1330 1570 -1330 {lab=ZERO1}
N 980 -1330 1080 -1330 {lab=ZERO0}
N 1360 -800 1430 -800 {lab=OUTDIFF}
N 1360 -510 1430 -510 {lab=OUTDIFF}
N 1960 -510 1990 -510 {lab=VSS}
N 1960 -800 1990 -800 {lab=VCC}
N 1930 -870 1960 -870 {lab=VCC}
N 1960 -870 1960 -830 {lab=VCC}
N 1930 -380 1960 -380 {lab=VSSI}
N 1960 -420 1960 -380 {lab=VSSI}
N 1960 -710 1960 -540 {lab=SAOUT}
N 1850 -710 1850 -510 {lab=SAOUTF}
N 2100 -1100 2130 -1100 {lab=VSS}
N 2100 -1330 2130 -1330 {lab=VCC}
N 2070 -1400 2100 -1400 {lab=VCC}
N 2100 -1400 2100 -1360 {lab=VCC}
N 2070 -970 2100 -970 {lab=VSSI}
N 2100 -1010 2100 -970 {lab=VSSI}
N 1960 -1100 2060 -1100 {lab=ZERO2}
N 1960 -1260 1960 -1100 {lab=ZERO2}
N 1880 -1260 1960 -1260 {lab=ZERO2}
N 1770 -1260 1800 -1260 {lab=SAOUT}
N 1770 -1440 1770 -1260 {lab=SAOUT}
N 1770 -1440 2290 -1440 {lab=SAOUT}
N 2100 -1260 2290 -1260 {lab=SAOUT}
N 2100 -1300 2100 -1260 {lab=SAOUT}
N 1960 -1330 1960 -1260 {lab=ZERO2}
N 2290 -1440 2290 -1260 {lab=SAOUT}
N 2100 -1260 2100 -1130 {lab=SAOUT}
N 2290 -1260 2290 -710 {lab=SAOUT}
N 1960 -1330 2060 -1330 {lab=ZERO2}
N 1850 -800 1920 -800 {lab=SAOUTF}
N 1850 -510 1920 -510 {lab=SAOUTF}
N 1470 -710 1710 -710 {lab=SAOUTF}
N 1960 -710 2290 -710 {lab=SAOUT}
N 1850 -800 1850 -710 {lab=SAOUTF}
N 1960 -770 1960 -710 {lab=SAOUT}
N 1470 -770 1470 -710 {lab=SAOUTF}
N 2180 -810 2210 -810 {lab=VCC}
N 2150 -880 2180 -880 {lab=VCC}
N 2180 -880 2180 -840 {lab=VCC}
N 2180 -780 2180 -710 {lab=SAOUT}
N 590 -680 620 -680 {lab=VCC}
N 420 -740 420 -710 {lab=SP}
N 520 -740 620 -740 {lab=SP}
N 620 -740 620 -710 {lab=SP}
N 420 -740 520 -740 {lab=SP}
N 420 -680 450 -680 {lab=VCC}
N 390 -550 420 -550 {lab=VSS}
N 620 -550 650 -550 {lab=VSS}
N 460 -550 580 -550 {lab=GP}
N 460 -580 460 -550 {lab=GP}
N 420 -580 460 -580 {lab=GP}
N 420 -650 420 -580 {lab=GP}
N 620 -650 620 -580 {lab=OUTDIFF}
N 620 -520 620 -500 {lab=VSSI}
N 420 -500 620 -500 {lab=VSSI}
N 420 -520 420 -500 {lab=VSSI}
N 490 -460 520 -460 {lab=VSSI}
N 520 -500 520 -460 {lab=VSSI}
N 530 -810 560 -810 {lab=VCC}
N 530 -780 530 -740 {lab=SP}
N 530 -860 530 -840 {lab=VCC}
N 620 -610 680 -610 {lab=OUTDIFF}
C {title.sym} 160 -30 0 0 {name=l1 author="Stefan Schippers"}
C {ipin.sym} 110 -850 0 0 { name=p92 lab=CAL }
C {ipin.sym} 110 -910 0 0 { name=p93 lab=PLUS }
C {ipin.sym} 110 -950 0 0 { name=p94 lab=MINUS }
C {ipin.sym} 110 -990 0 0 { name=p95 lab=EN }
C {ipin.sym} 110 -780 0 0 { name=p96 lab=VSS }
C {ipin.sym} 110 -810 0 0 { name=p97 lab=VCC }
C {vsource_arith.sym} 120 -420 0 0 {name=E5 VOL=temper MAX=200 MIN=-200}
C {lab_pin.sym} 120 -470 0 1 {name=p113 lab=TEMPERAT}
C {lab_pin.sym} 120 -390 0 0 {name=p114 lab=VSS}
C {opin.sym} 130 -900 0 0 { name=p116 lab=SAOUT }
C {lab_pin.sym} 200 -570 0 1 {name=p126 lab=CALB}
C {lab_pin.sym} 120 -570 0 0 {name=l50 lab=CAL}
C {code.sym} 840 -190 0 0 {name=STIMULI 
only_toplevel=true
xxplace=end
value="* .option SCALE=1e-6 
.option method=gear $$ seed=12
.param VCC=0.9
.param VDL='VCC/2+0.2'
.param ABSVAR=0.05
.temp 25

** to generate following file: 
** copy .../share/doc/xschem/ngspice/stimuli.autozero_comp to simulation directory
** then do 'Simulation->Utile Stimuli Editor (GUI)' and press 'Translate'
.include \\"stimuli_autozero_comp.cir\\"

** download models from here: 
** http://ptm.asu.edu/modelcard/2006/130nm_bulk.pm
** and save to 'models_autozero_comp.txt' in simulation directory
.include \\"models_autozero_comp.txt\\"


* .tran 0.1n 900n uic

.control
  let run=1
  
  dowhile run <= 10
    if run > 1
      reset
      set appendwrite
    end
    * save saout cal i(vvcc) en plus minus saoutf outdiff
    save all
    tran 0.1n 900n uic
    write autozero_comp.raw
    let run = run + 1
  end
.endc
"}
C {inv-2.sym} 160 -570 0 0 {name=x14 m=1 
+ wn=0.6u ln=0.2u
+ wp=1u lp=0.2u
+ VCCPIN=VCC VCCBPIN=VCC VSSPIN=VSS VSSBPIN=VSS}
C {inv-2.sym} 160 -700 0 0 {name=x5 m=1 
+ wn=0.6u ln=0.2u
+ wp=1u lp=0.2u
+ VCCPIN=VCC VCCBPIN=VCC VSSPIN=VSS VSSBPIN=VSS}
C {lab_pin.sym} 120 -700 0 0 {name=p15 lab=CALB}
C {lab_pin.sym} 200 -700 0 1 {name=l4 lab=CALBB}
C {lab_pin.sym} 190 -1180 0 1 {name=p283 lab=VSS}
C {lab_pin.sym} 120 -1180 0 0 {name=l56 lab=EN}
C {lab_pin.sym} 160 -1130 0 0 {name=p284 lab=VSS}
C {lab_pin.sym} 160 -1230 0 0 {name=p199 lab=VSSI}
C {nmos4-v.sym} 140 -1180 0 0 {name=M67 verilog_gate=nmos del=50,50,50 model=nmos w=5u l=0.13u extra="delvto='agauss(0,ABSVAR,3)'"}
C {parax_cap.sym} 160 -1120 0 0 {name=c38  value=2p}
C {passgate.sym} 860 -1260 0 1 {name=x1 m=1 
+ wn=0.4u ln=0.13u
+ wp=0.4u lp=0.13u
+ VCCBPIN=VCC VSSBPIN=VSS extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 860 -1290 0 1 {name=l19 sig_type=std_logic lab=CALB}
C {lab_pin.sym} 860 -1230 0 1 {name=l44 sig_type=std_logic lab=CALBB}
C {nmos4-v.sym} 1100 -1100 0 0 {name=M3 verilog_gate=nmos del=50,50,50 model=nmos w=1.0u l=1.0u extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 1150 -1100 0 1 {name=p179 lab=VSS}
C {pmos4-v.sym} 1100 -1330 0 0 {name=M4 verilog_gate=pmos del=50,50,50 model=pmos w=2.0u l=1.0u extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 1150 -1330 0 1 {name=p180 lab=VCC}
C {lab_pin.sym} 1090 -1400 0 0 {name=p181 lab=VCC}
C {lab_pin.sym} 1090 -970 0 0 {name=p182 lab=VSSI}
C {passgate.sym} 1350 -1260 0 1 {name=x2 m=1 
+ wn=0.4u ln=0.13u
+ wp=0.4u lp=0.13u
+ VCCBPIN=VCC VSSBPIN=VSS  extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 1350 -1290 0 1 {name=l45 sig_type=std_logic lab=CALB}
C {lab_pin.sym} 1350 -1230 0 1 {name=l46 sig_type=std_logic lab=CALBB}
C {nmos4-v.sym} 1590 -1100 0 0 {name=M7 verilog_gate=nmos del=50,50,50 model=nmos w=1.3u l=1.0u extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 1640 -1100 0 1 {name=p183 lab=VSS}
C {pmos4-v.sym} 1590 -1330 0 0 {name=M9 verilog_gate=pmos del=50,50,50 model=pmos w=2.6u l=1.0u extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 1640 -1330 0 1 {name=p184 lab=VCC}
C {lab_pin.sym} 1580 -1400 0 0 {name=p185 lab=VCC}
C {lab_pin.sym} 1580 -970 0 0 {name=p186 lab=VSSI}
C {lab_pin.sym} 1470 -1320 0 0 {name=l47 lab=ZERO1}
C {lab_pin.sym} 980 -1320 0 0 {name=l48 lab=ZERO0}
C {nmos4-v.sym} 870 -640 0 0 {name=M20 verilog_gate=nmos del=50,50,50 model=nmos w=2u l=0.4u extra="delvto='agauss(0,ABSVAR,3)'"}
C {nmos4-v.sym} 1110 -640 0 1 {name=M8 verilog_gate=nmos del=50,50,50 model=nmos w=2u l=0.4u extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 920 -640 0 1 {name=p187 lab=VSS}
C {lab_pin.sym} 1060 -640 0 0 {name=p188 lab=VSS}
C {pmos4-v.sym} 1070 -800 0 0 {name=M30 verilog_gate=pmos del=50,50,50 model=pmos w=2u l=0.5u extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 1120 -800 0 1 {name=p189 lab=VCC}
C {pmos4-v.sym} 910 -800 0 1 {name=M12 verilog_gate=pmos del=50,50,50 model=pmos w=2u l=0.5u extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 860 -800 0 0 {name=p190 lab=VCC}
C {nmos4-v.sym} 970 -510 0 0 {name=M32 verilog_gate=nmos del=50,50,50 model=nmos w=1u l=0.5u  extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 1020 -510 0 1 {name=p191 lab=VSS}
C {lab_pin.sym} 990 -880 0 0 {name=p192 lab=VCC}
C {lab_pin.sym} 960 -380 0 0 {name=p193 lab=VSSI}
C {nmos4-v.sym} 1450 -510 0 0 {name=M17 verilog_gate=nmos del=50,50,50 model=nmos w=1u l=0.5u extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 1500 -510 0 1 {name=p194 lab=VSS}
C {pmos4-v.sym} 1450 -800 0 0 {name=M13 verilog_gate=pmos del=50,50,50 model=pmos w=2u l=0.5u extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 1500 -800 0 1 {name=p195 lab=VCC}
C {lab_pin.sym} 1440 -870 0 0 {name=p196 lab=VCC}
C {lab_pin.sym} 1440 -380 0 0 {name=p197 lab=VSSI}
C {lab_pin.sym} 1710 -750 0 0 {name=l49 lab=SAOUTF}
C {parax_cap.sym} 1540 -700 0 0 {name=c3  value=4f}
C {lab_pin.sym} 1220 -750 0 0 {name=l51 lab=OUTDIFF}
C {lab_pin.sym} 990 -570 0 0 {name=l52 lab=SN}
C {lab_pin.sym} 930 -770 0 1 {name=l53 lab=GN}
C {parax_cap.sym} 980 -790 0 0 {name=c5  value=4f}
C {parax_cap.sym} 910 -580 0 0 {name=c30  value=2f}
C {parax_cap.sym} 1180 -700 0 0 {name=c31  value=4f}
C {lab_pin.sym} 950 -510 0 0 {name=p198 lab=GN}
C {lab_pin.sym} 1130 -640 0 1 {name=l54 lab=PLUS}
C {lab_pin.sym} 850 -640 0 0 {name=l55 lab=MINUS}
C {ammeter.sym} 990 -450 0 0 {name=v2}
C {ammeter.sym} 1470 -450 0 0 {name=v3}
C {ammeter.sym} 1610 -1040 0 0 {name=v4}
C {ammeter.sym} 1120 -1040 0 0 {name=v6}
C {nmos4-v.sym} 1940 -510 0 0 {name=M19 verilog_gate=nmos del=50,50,50 model=nmos w=1u l=0.5u extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 1990 -510 0 1 {name=p9 lab=VSS}
C {pmos4-v.sym} 1940 -800 0 0 {name=M21 verilog_gate=pmos del=50,50,50 model=pmos w=2u l=0.5u extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 1990 -800 0 1 {name=p10 lab=VCC}
C {lab_pin.sym} 1930 -870 0 0 {name=p11 lab=VCC}
C {lab_pin.sym} 1930 -380 0 0 {name=p12 lab=VSSI}
C {parax_cap.sym} 2030 -700 0 0 {name=c1  value=4f}
C {ammeter.sym} 1960 -450 0 0 {name=v1}
C {lab_pin.sym} 2290 -710 0 1 {name=l3 lab=SAOUT}
C {passgate.sym} 1840 -1260 0 1 {name=x3 m=1 
+ wn=0.4u ln=0.13u
+ wp=0.4u lp=0.13u
+ VCCBPIN=VCC VSSBPIN=VSS  extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 1840 -1290 0 1 {name=l5 sig_type=std_logic lab=CALB}
C {lab_pin.sym} 1840 -1230 0 1 {name=l6 sig_type=std_logic lab=CALBB}
C {nmos4-v.sym} 2080 -1100 0 0 {name=M23 verilog_gate=nmos del=50,50,50 model=nmos w=1.5u l=1.0u extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 2130 -1100 0 1 {name=p13 lab=VSS}
C {pmos4-v.sym} 2080 -1330 0 0 {name=M24 verilog_gate=pmos del=50,50,50 model=pmos w=3u l=1.0u extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 2130 -1330 0 1 {name=p14 lab=VCC}
C {lab_pin.sym} 2070 -1400 0 0 {name=p16 lab=VCC}
C {lab_pin.sym} 2070 -970 0 0 {name=p17 lab=VSSI}
C {lab_pin.sym} 1960 -1320 0 0 {name=l8 lab=ZERO2}
C {ammeter.sym} 2100 -1040 0 0 {name=v5}
C {pmos4-v.sym} 2160 -810 0 0 {name=M6 verilog_gate=pmos del=50,50,50 model=pmos w=0.6u l=0.2u extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 2210 -810 0 1 {name=p18 lab=VCC}
C {lab_pin.sym} 2150 -880 0 0 {name=p19 lab=VCC}
C {lab_pin.sym} 2140 -810 0 0 {name=l2 lab=EN}
C {pmos4-v.sym} 640 -680 0 1 {name=M18 verilog_gate=pmos del=50,50,50 model=pmos w=4u l=0.4u  extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 590 -680 0 0 {name=p20 lab=VCC}
C {pmos4-v.sym} 400 -680 0 0 {name=M25 verilog_gate=pmos del=50,50,50 model=pmos w=4u l=0.4u  extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 450 -680 0 1 {name=p21 lab=VCC}
C {lab_pin.sym} 390 -550 0 0 {name=p22 lab=VSS}
C {lab_pin.sym} 650 -550 0 1 {name=p23 lab=VSS}
C {lab_pin.sym} 490 -460 0 0 {name=p24 lab=VSSI}
C {pmos4-v.sym} 510 -810 0 0 {name=M28 verilog_gate=pmos del=50,50,50 model=pmos w=2u l=0.5u  extra="delvto='agauss(0,ABSVAR,3)'"}
C {lab_pin.sym} 560 -810 0 1 {name=p25 lab=VCC}
C {lab_pin.sym} 530 -860 0 0 {name=p26 lab=VCC}
C {lab_pin.sym} 490 -810 0 0 {name=l7 lab=GP}
C {lab_pin.sym} 460 -580 0 1 {name=l9 lab=GP}
C {lab_pin.sym} 380 -680 0 0 {name=l10 lab=MINUS}
C {lab_pin.sym} 660 -680 0 1 {name=l11 lab=PLUS}
C {lab_pin.sym} 680 -610 0 1 {name=l12 lab=OUTDIFF}
C {nmos4-v.sym} 600 -550 0 0 {name=M26 verilog_gate=nmos del=50,50,50 model=nmos w=1u l=0.5u extra="delvto='agauss(0,ABSVAR,3)'"}
C {nmos4-v.sym} 440 -550 0 1 {name=M1 verilog_gate=nmos del=50,50,50 model=nmos w=1u l=0.5u extra="delvto='agauss(0,ABSVAR,3)'"}
C {parax_cap.sym} 500 -540 0 0 {name=c2  value=4f}
C {lab_pin.sym} 530 -760 0 0 {name=l13 lab=SP}
C {launcher.sym} 930 -260 0 0 {name=h2 
descr="Simulate" 
tclcommand="xschem netlist; xschem simulate"}
C {parax_cap.sym} 980 -1090 0 0 {name=c4  value=5f}
C {parax_cap.sym} 1470 -1090 0 0 {name=c6  value=5f}
C {parax_cap.sym} 1960 -1090 0 0 {name=c7  value=5f}
C {launcher.sym} 315 -1415 0 0 {name=h1 
descr="Select arrow and 
Ctrl-Left-Click to load/unload waveforms" 
tclcommand="
xschem raw_read $netlist_dir/[file tail [file rootname [xschem get current_name]]].raw
"
}
C {ngspice_probe.sym} 890 -700 0 0 {name=r1}
C {ngspice_probe.sym} 660 -680 0 0 {name=r1}
C {ngspice_probe.sym} 380 -680 0 1 {name=r1}
C {ngspice_probe.sym} 1130 -640 0 0 {name=r1}
C {ngspice_probe.sym} 850 -640 0 1 {name=r2}
C {ngspice_probe.sym} 1000 -590 0 0 {name=r1}
C {ngspice_probe.sym} 1260 -710 0 0 {name=r1}
C {ngspice_probe.sym} 1600 -710 0 0 {name=r1}
C {ngspice_probe.sym} 2100 -710 0 0 {name=r1}
C {ngspice_probe.sym} 1610 -1390 0 0 {name=r1}
C {ngspice_probe.sym} 1470 -1200 0 0 {name=r1}
C {ngspice_probe.sym} 980 -1200 0 0 {name=r1}
C {ngspice_probe.sym} 1040 -860 0 0 {name=r1}
C {ngspice_probe.sym} 530 -860 0 0 {name=r1}
C {ngspice_probe.sym} 200 -570 0 0 {name=r1}
C {ngspice_probe.sym} 120 -570 0 1 {name=r1}
C {ngspice_probe.sym} 200 -700 0 0 {name=r1}
C {ngspice_probe.sym} 120 -470 0 0 {name=r1}
C {ngspice_probe.sym} 1960 -1200 0 0 {name=r1}
