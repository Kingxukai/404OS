
/home/wxk/Desktop/404OS/oskernel2023-404os/user/build/riscv64/yield:     file format elf64-littleriscv


Disassembly of section .text:

0000000000001000 <_start>:
.section .text.entry
.globl _start
_start:
    mv a0, sp
    1000:	850a                	mv	a0,sp
    tail __start_main
    1002:	a86d                	j	10bc <__start_main>

0000000000001004 <test_yield>:

/*
理想结果：三个子进程交替输出
*/

int test_yield(){
    1004:	7179                	addi	sp,sp,-48
    TEST_START(__func__);
    1006:	00001517          	auipc	a0,0x1
    100a:	eea50513          	addi	a0,a0,-278 # 1ef0 <__clone+0x2e>
int test_yield(){
    100e:	f406                	sd	ra,40(sp)
    1010:	f022                	sd	s0,32(sp)
    1012:	e84a                	sd	s2,16(sp)
    1014:	e44e                	sd	s3,8(sp)
    1016:	ec26                	sd	s1,24(sp)
    TEST_START(__func__);
    1018:	316000ef          	jal	ra,132e <puts>
    101c:	00001517          	auipc	a0,0x1
    1020:	f5c50513          	addi	a0,a0,-164 # 1f78 <__func__.0>
    1024:	30a000ef          	jal	ra,132e <puts>
    1028:	00001517          	auipc	a0,0x1
    102c:	ee050513          	addi	a0,a0,-288 # 1f08 <__clone+0x46>
    1030:	2fe000ef          	jal	ra,132e <puts>

    for (int i = 0; i < 3; ++i){
    1034:	4401                	li	s0,0
        if(fork() == 0){
	    for (int j = 0; j< 5; ++j){
                sched_yield();
                printf("  I am child process: %d. iteration %d.\n", getpid(), i);
    1036:	00001917          	auipc	s2,0x1
    103a:	ee290913          	addi	s2,s2,-286 # 1f18 <__clone+0x56>
    for (int i = 0; i < 3; ++i){
    103e:	498d                	li	s3,3
        if(fork() == 0){
    1040:	479000ef          	jal	ra,1cb8 <fork>
    1044:	c521                	beqz	a0,108c <test_yield+0x88>
    for (int i = 0; i < 3; ++i){
    1046:	2405                	addiw	s0,s0,1
    1048:	ff341ce3          	bne	s0,s3,1040 <test_yield+0x3c>
	    }
	    exit(0);
        }
    }
    wait(NULL);
    104c:	4501                	li	a0,0
    104e:	551000ef          	jal	ra,1d9e <wait>
    wait(NULL);
    1052:	4501                	li	a0,0
    1054:	54b000ef          	jal	ra,1d9e <wait>
    wait(NULL);
    1058:	4501                	li	a0,0
    105a:	545000ef          	jal	ra,1d9e <wait>
    TEST_END(__func__);
    105e:	00001517          	auipc	a0,0x1
    1062:	eea50513          	addi	a0,a0,-278 # 1f48 <__clone+0x86>
    1066:	2c8000ef          	jal	ra,132e <puts>
    106a:	00001517          	auipc	a0,0x1
    106e:	f0e50513          	addi	a0,a0,-242 # 1f78 <__func__.0>
    1072:	2bc000ef          	jal	ra,132e <puts>
}
    1076:	7402                	ld	s0,32(sp)
    1078:	70a2                	ld	ra,40(sp)
    107a:	64e2                	ld	s1,24(sp)
    107c:	6942                	ld	s2,16(sp)
    107e:	69a2                	ld	s3,8(sp)
    TEST_END(__func__);
    1080:	00001517          	auipc	a0,0x1
    1084:	e8850513          	addi	a0,a0,-376 # 1f08 <__clone+0x46>
}
    1088:	6145                	addi	sp,sp,48
    TEST_END(__func__);
    108a:	a455                	j	132e <puts>
    108c:	4495                	li	s1,5
                sched_yield();
    108e:	41f000ef          	jal	ra,1cac <sched_yield>
                printf("  I am child process: %d. iteration %d.\n", getpid(), i);
    1092:	403000ef          	jal	ra,1c94 <getpid>
    1096:	85aa                	mv	a1,a0
	    for (int j = 0; j< 5; ++j){
    1098:	34fd                	addiw	s1,s1,-1
                printf("  I am child process: %d. iteration %d.\n", getpid(), i);
    109a:	8622                	mv	a2,s0
    109c:	854a                	mv	a0,s2
    109e:	2b2000ef          	jal	ra,1350 <printf>
	    for (int j = 0; j< 5; ++j){
    10a2:	f4f5                	bnez	s1,108e <test_yield+0x8a>
	    exit(0);
    10a4:	4501                	li	a0,0
    10a6:	435000ef          	jal	ra,1cda <exit>
    10aa:	bf71                	j	1046 <test_yield+0x42>

00000000000010ac <main>:

int main(void) {
    10ac:	1141                	addi	sp,sp,-16
    10ae:	e406                	sd	ra,8(sp)
    test_yield();
    10b0:	f55ff0ef          	jal	ra,1004 <test_yield>
    return 0;
}
    10b4:	60a2                	ld	ra,8(sp)
    10b6:	4501                	li	a0,0
    10b8:	0141                	addi	sp,sp,16
    10ba:	8082                	ret

00000000000010bc <__start_main>:
#include <unistd.h>

extern int main();

int __start_main(long *p)
{
    10bc:	85aa                	mv	a1,a0
	int argc = p[0];
	char **argv = (void *)(p+1);

	exit(main(argc, argv));
    10be:	4108                	lw	a0,0(a0)
{
    10c0:	1141                	addi	sp,sp,-16
	exit(main(argc, argv));
    10c2:	05a1                	addi	a1,a1,8
{
    10c4:	e406                	sd	ra,8(sp)
	exit(main(argc, argv));
    10c6:	fe7ff0ef          	jal	ra,10ac <main>
    10ca:	411000ef          	jal	ra,1cda <exit>
	return 0;
}
    10ce:	60a2                	ld	ra,8(sp)
    10d0:	4501                	li	a0,0
    10d2:	0141                	addi	sp,sp,16
    10d4:	8082                	ret

00000000000010d6 <printint.constprop.0>:
    write(f, s, l);
}

static char digits[] = "0123456789abcdef";

static void printint(int xx, int base, int sign)
    10d6:	7179                	addi	sp,sp,-48
    10d8:	f406                	sd	ra,40(sp)
{
    char buf[16 + 1];
    int i;
    uint x;

    if (sign && (sign = xx < 0))
    10da:	12054b63          	bltz	a0,1210 <printint.constprop.0+0x13a>

    buf[16] = 0;
    i = 15;
    do
    {
        buf[i--] = digits[x % base];
    10de:	02b577bb          	remuw	a5,a0,a1
    10e2:	00001617          	auipc	a2,0x1
    10e6:	ea660613          	addi	a2,a2,-346 # 1f88 <digits>
    buf[16] = 0;
    10ea:	00010c23          	sb	zero,24(sp)
        buf[i--] = digits[x % base];
    10ee:	0005871b          	sext.w	a4,a1
    10f2:	1782                	slli	a5,a5,0x20
    10f4:	9381                	srli	a5,a5,0x20
    10f6:	97b2                	add	a5,a5,a2
    10f8:	0007c783          	lbu	a5,0(a5)
    } while ((x /= base) != 0);
    10fc:	02b5583b          	divuw	a6,a0,a1
        buf[i--] = digits[x % base];
    1100:	00f10ba3          	sb	a5,23(sp)
    } while ((x /= base) != 0);
    1104:	1cb56363          	bltu	a0,a1,12ca <printint.constprop.0+0x1f4>
        buf[i--] = digits[x % base];
    1108:	45b9                	li	a1,14
    110a:	02e877bb          	remuw	a5,a6,a4
    110e:	1782                	slli	a5,a5,0x20
    1110:	9381                	srli	a5,a5,0x20
    1112:	97b2                	add	a5,a5,a2
    1114:	0007c783          	lbu	a5,0(a5)
    } while ((x /= base) != 0);
    1118:	02e856bb          	divuw	a3,a6,a4
        buf[i--] = digits[x % base];
    111c:	00f10b23          	sb	a5,22(sp)
    } while ((x /= base) != 0);
    1120:	0ce86e63          	bltu	a6,a4,11fc <printint.constprop.0+0x126>
        buf[i--] = digits[x % base];
    1124:	02e6f5bb          	remuw	a1,a3,a4
    } while ((x /= base) != 0);
    1128:	02e6d7bb          	divuw	a5,a3,a4
        buf[i--] = digits[x % base];
    112c:	1582                	slli	a1,a1,0x20
    112e:	9181                	srli	a1,a1,0x20
    1130:	95b2                	add	a1,a1,a2
    1132:	0005c583          	lbu	a1,0(a1)
    1136:	00b10aa3          	sb	a1,21(sp)
    } while ((x /= base) != 0);
    113a:	0007859b          	sext.w	a1,a5
    113e:	12e6ec63          	bltu	a3,a4,1276 <printint.constprop.0+0x1a0>
        buf[i--] = digits[x % base];
    1142:	02e7f6bb          	remuw	a3,a5,a4
    1146:	1682                	slli	a3,a3,0x20
    1148:	9281                	srli	a3,a3,0x20
    114a:	96b2                	add	a3,a3,a2
    114c:	0006c683          	lbu	a3,0(a3)
    } while ((x /= base) != 0);
    1150:	02e7d83b          	divuw	a6,a5,a4
        buf[i--] = digits[x % base];
    1154:	00d10a23          	sb	a3,20(sp)
    } while ((x /= base) != 0);
    1158:	12e5e863          	bltu	a1,a4,1288 <printint.constprop.0+0x1b2>
        buf[i--] = digits[x % base];
    115c:	02e876bb          	remuw	a3,a6,a4
    1160:	1682                	slli	a3,a3,0x20
    1162:	9281                	srli	a3,a3,0x20
    1164:	96b2                	add	a3,a3,a2
    1166:	0006c683          	lbu	a3,0(a3)
    } while ((x /= base) != 0);
    116a:	02e855bb          	divuw	a1,a6,a4
        buf[i--] = digits[x % base];
    116e:	00d109a3          	sb	a3,19(sp)
    } while ((x /= base) != 0);
    1172:	12e86463          	bltu	a6,a4,129a <printint.constprop.0+0x1c4>
        buf[i--] = digits[x % base];
    1176:	02e5f6bb          	remuw	a3,a1,a4
    117a:	1682                	slli	a3,a3,0x20
    117c:	9281                	srli	a3,a3,0x20
    117e:	96b2                	add	a3,a3,a2
    1180:	0006c683          	lbu	a3,0(a3)
    } while ((x /= base) != 0);
    1184:	02e5d83b          	divuw	a6,a1,a4
        buf[i--] = digits[x % base];
    1188:	00d10923          	sb	a3,18(sp)
    } while ((x /= base) != 0);
    118c:	0ce5ec63          	bltu	a1,a4,1264 <printint.constprop.0+0x18e>
        buf[i--] = digits[x % base];
    1190:	02e876bb          	remuw	a3,a6,a4
    1194:	1682                	slli	a3,a3,0x20
    1196:	9281                	srli	a3,a3,0x20
    1198:	96b2                	add	a3,a3,a2
    119a:	0006c683          	lbu	a3,0(a3)
    } while ((x /= base) != 0);
    119e:	02e855bb          	divuw	a1,a6,a4
        buf[i--] = digits[x % base];
    11a2:	00d108a3          	sb	a3,17(sp)
    } while ((x /= base) != 0);
    11a6:	10e86963          	bltu	a6,a4,12b8 <printint.constprop.0+0x1e2>
        buf[i--] = digits[x % base];
    11aa:	02e5f6bb          	remuw	a3,a1,a4
    11ae:	1682                	slli	a3,a3,0x20
    11b0:	9281                	srli	a3,a3,0x20
    11b2:	96b2                	add	a3,a3,a2
    11b4:	0006c683          	lbu	a3,0(a3)
    } while ((x /= base) != 0);
    11b8:	02e5d83b          	divuw	a6,a1,a4
        buf[i--] = digits[x % base];
    11bc:	00d10823          	sb	a3,16(sp)
    } while ((x /= base) != 0);
    11c0:	10e5e763          	bltu	a1,a4,12ce <printint.constprop.0+0x1f8>
        buf[i--] = digits[x % base];
    11c4:	02e876bb          	remuw	a3,a6,a4
    11c8:	1682                	slli	a3,a3,0x20
    11ca:	9281                	srli	a3,a3,0x20
    11cc:	96b2                	add	a3,a3,a2
    11ce:	0006c683          	lbu	a3,0(a3)
    } while ((x /= base) != 0);
    11d2:	02e857bb          	divuw	a5,a6,a4
        buf[i--] = digits[x % base];
    11d6:	00d107a3          	sb	a3,15(sp)
    } while ((x /= base) != 0);
    11da:	10e86363          	bltu	a6,a4,12e0 <printint.constprop.0+0x20a>
        buf[i--] = digits[x % base];
    11de:	1782                	slli	a5,a5,0x20
    11e0:	9381                	srli	a5,a5,0x20
    11e2:	97b2                	add	a5,a5,a2
    11e4:	0007c783          	lbu	a5,0(a5)
    11e8:	4599                	li	a1,6
    11ea:	00f10723          	sb	a5,14(sp)

    if (sign)
    11ee:	00055763          	bgez	a0,11fc <printint.constprop.0+0x126>
        buf[i--] = '-';
    11f2:	02d00793          	li	a5,45
    11f6:	00f106a3          	sb	a5,13(sp)
        buf[i--] = digits[x % base];
    11fa:	4595                	li	a1,5
    write(f, s, l);
    11fc:	003c                	addi	a5,sp,8
    11fe:	4641                	li	a2,16
    1200:	9e0d                	subw	a2,a2,a1
    1202:	4505                	li	a0,1
    1204:	95be                	add	a1,a1,a5
    1206:	285000ef          	jal	ra,1c8a <write>
    i++;
    if (i < 0)
        puts("printint error");
    out(stdout, buf + i, 16 - i);
}
    120a:	70a2                	ld	ra,40(sp)
    120c:	6145                	addi	sp,sp,48
    120e:	8082                	ret
        x = -xx;
    1210:	40a0083b          	negw	a6,a0
        buf[i--] = digits[x % base];
    1214:	02b877bb          	remuw	a5,a6,a1
    1218:	00001617          	auipc	a2,0x1
    121c:	d7060613          	addi	a2,a2,-656 # 1f88 <digits>
    buf[16] = 0;
    1220:	00010c23          	sb	zero,24(sp)
        buf[i--] = digits[x % base];
    1224:	0005871b          	sext.w	a4,a1
    1228:	1782                	slli	a5,a5,0x20
    122a:	9381                	srli	a5,a5,0x20
    122c:	97b2                	add	a5,a5,a2
    122e:	0007c783          	lbu	a5,0(a5)
    } while ((x /= base) != 0);
    1232:	02b858bb          	divuw	a7,a6,a1
        buf[i--] = digits[x % base];
    1236:	00f10ba3          	sb	a5,23(sp)
    } while ((x /= base) != 0);
    123a:	06b86963          	bltu	a6,a1,12ac <printint.constprop.0+0x1d6>
        buf[i--] = digits[x % base];
    123e:	02e8f7bb          	remuw	a5,a7,a4
    1242:	1782                	slli	a5,a5,0x20
    1244:	9381                	srli	a5,a5,0x20
    1246:	97b2                	add	a5,a5,a2
    1248:	0007c783          	lbu	a5,0(a5)
    } while ((x /= base) != 0);
    124c:	02e8d6bb          	divuw	a3,a7,a4
        buf[i--] = digits[x % base];
    1250:	00f10b23          	sb	a5,22(sp)
    } while ((x /= base) != 0);
    1254:	ece8f8e3          	bgeu	a7,a4,1124 <printint.constprop.0+0x4e>
        buf[i--] = '-';
    1258:	02d00793          	li	a5,45
    125c:	00f10aa3          	sb	a5,21(sp)
        buf[i--] = digits[x % base];
    1260:	45b5                	li	a1,13
    1262:	bf69                	j	11fc <printint.constprop.0+0x126>
    1264:	45a9                	li	a1,10
    if (sign)
    1266:	f8055be3          	bgez	a0,11fc <printint.constprop.0+0x126>
        buf[i--] = '-';
    126a:	02d00793          	li	a5,45
    126e:	00f108a3          	sb	a5,17(sp)
        buf[i--] = digits[x % base];
    1272:	45a5                	li	a1,9
    1274:	b761                	j	11fc <printint.constprop.0+0x126>
    1276:	45b5                	li	a1,13
    if (sign)
    1278:	f80552e3          	bgez	a0,11fc <printint.constprop.0+0x126>
        buf[i--] = '-';
    127c:	02d00793          	li	a5,45
    1280:	00f10a23          	sb	a5,20(sp)
        buf[i--] = digits[x % base];
    1284:	45b1                	li	a1,12
    1286:	bf9d                	j	11fc <printint.constprop.0+0x126>
    1288:	45b1                	li	a1,12
    if (sign)
    128a:	f60559e3          	bgez	a0,11fc <printint.constprop.0+0x126>
        buf[i--] = '-';
    128e:	02d00793          	li	a5,45
    1292:	00f109a3          	sb	a5,19(sp)
        buf[i--] = digits[x % base];
    1296:	45ad                	li	a1,11
    1298:	b795                	j	11fc <printint.constprop.0+0x126>
    129a:	45ad                	li	a1,11
    if (sign)
    129c:	f60550e3          	bgez	a0,11fc <printint.constprop.0+0x126>
        buf[i--] = '-';
    12a0:	02d00793          	li	a5,45
    12a4:	00f10923          	sb	a5,18(sp)
        buf[i--] = digits[x % base];
    12a8:	45a9                	li	a1,10
    12aa:	bf89                	j	11fc <printint.constprop.0+0x126>
        buf[i--] = '-';
    12ac:	02d00793          	li	a5,45
    12b0:	00f10b23          	sb	a5,22(sp)
        buf[i--] = digits[x % base];
    12b4:	45b9                	li	a1,14
    12b6:	b799                	j	11fc <printint.constprop.0+0x126>
    12b8:	45a5                	li	a1,9
    if (sign)
    12ba:	f40551e3          	bgez	a0,11fc <printint.constprop.0+0x126>
        buf[i--] = '-';
    12be:	02d00793          	li	a5,45
    12c2:	00f10823          	sb	a5,16(sp)
        buf[i--] = digits[x % base];
    12c6:	45a1                	li	a1,8
    12c8:	bf15                	j	11fc <printint.constprop.0+0x126>
    i = 15;
    12ca:	45bd                	li	a1,15
    12cc:	bf05                	j	11fc <printint.constprop.0+0x126>
        buf[i--] = digits[x % base];
    12ce:	45a1                	li	a1,8
    if (sign)
    12d0:	f20556e3          	bgez	a0,11fc <printint.constprop.0+0x126>
        buf[i--] = '-';
    12d4:	02d00793          	li	a5,45
    12d8:	00f107a3          	sb	a5,15(sp)
        buf[i--] = digits[x % base];
    12dc:	459d                	li	a1,7
    12de:	bf39                	j	11fc <printint.constprop.0+0x126>
    12e0:	459d                	li	a1,7
    if (sign)
    12e2:	f0055de3          	bgez	a0,11fc <printint.constprop.0+0x126>
        buf[i--] = '-';
    12e6:	02d00793          	li	a5,45
    12ea:	00f10723          	sb	a5,14(sp)
        buf[i--] = digits[x % base];
    12ee:	4599                	li	a1,6
    12f0:	b731                	j	11fc <printint.constprop.0+0x126>

00000000000012f2 <getchar>:
{
    12f2:	1101                	addi	sp,sp,-32
    read(stdin, &byte, 1);
    12f4:	00f10593          	addi	a1,sp,15
    12f8:	4605                	li	a2,1
    12fa:	4501                	li	a0,0
{
    12fc:	ec06                	sd	ra,24(sp)
    char byte = 0;
    12fe:	000107a3          	sb	zero,15(sp)
    read(stdin, &byte, 1);
    1302:	17f000ef          	jal	ra,1c80 <read>
}
    1306:	60e2                	ld	ra,24(sp)
    1308:	00f14503          	lbu	a0,15(sp)
    130c:	6105                	addi	sp,sp,32
    130e:	8082                	ret

0000000000001310 <putchar>:
{
    1310:	1101                	addi	sp,sp,-32
    1312:	87aa                	mv	a5,a0
    return write(stdout, &byte, 1);
    1314:	00f10593          	addi	a1,sp,15
    1318:	4605                	li	a2,1
    131a:	4505                	li	a0,1
{
    131c:	ec06                	sd	ra,24(sp)
    char byte = c;
    131e:	00f107a3          	sb	a5,15(sp)
    return write(stdout, &byte, 1);
    1322:	169000ef          	jal	ra,1c8a <write>
}
    1326:	60e2                	ld	ra,24(sp)
    1328:	2501                	sext.w	a0,a0
    132a:	6105                	addi	sp,sp,32
    132c:	8082                	ret

000000000000132e <puts>:
{
    132e:	1141                	addi	sp,sp,-16
    1330:	e406                	sd	ra,8(sp)
    1332:	e022                	sd	s0,0(sp)
    1334:	842a                	mv	s0,a0
    r = -(write(stdout, s, strlen(s)) < 0);
    1336:	570000ef          	jal	ra,18a6 <strlen>
    133a:	862a                	mv	a2,a0
    133c:	85a2                	mv	a1,s0
    133e:	4505                	li	a0,1
    1340:	14b000ef          	jal	ra,1c8a <write>
}
    1344:	60a2                	ld	ra,8(sp)
    1346:	6402                	ld	s0,0(sp)
    r = -(write(stdout, s, strlen(s)) < 0);
    1348:	957d                	srai	a0,a0,0x3f
    return r;
    134a:	2501                	sext.w	a0,a0
}
    134c:	0141                	addi	sp,sp,16
    134e:	8082                	ret

0000000000001350 <printf>:
    out(stdout, buf, i);
}

// Print to the console. only understands %d, %x, %p, %s.
void printf(const char *fmt, ...)
{
    1350:	7131                	addi	sp,sp,-192
    1352:	f53e                	sd	a5,168(sp)
    va_list ap;
    int cnt = 0, l = 0;
    char *a, *z, *s = (char *)fmt, str;
    int f = stdout;

    va_start(ap, fmt);
    1354:	013c                	addi	a5,sp,136
{
    1356:	f0ca                	sd	s2,96(sp)
    1358:	ecce                	sd	s3,88(sp)
    135a:	e8d2                	sd	s4,80(sp)
    135c:	e4d6                	sd	s5,72(sp)
    135e:	e0da                	sd	s6,64(sp)
    1360:	fc5e                	sd	s7,56(sp)
    1362:	fc86                	sd	ra,120(sp)
    1364:	f8a2                	sd	s0,112(sp)
    1366:	f4a6                	sd	s1,104(sp)
    1368:	e52e                	sd	a1,136(sp)
    136a:	e932                	sd	a2,144(sp)
    136c:	ed36                	sd	a3,152(sp)
    136e:	f13a                	sd	a4,160(sp)
    1370:	f942                	sd	a6,176(sp)
    1372:	fd46                	sd	a7,184(sp)
    va_start(ap, fmt);
    1374:	e03e                	sd	a5,0(sp)
    for (;;)
    {
        if (!*s)
            break;
        for (a = s; *s && *s != '%'; s++)
    1376:	02500913          	li	s2,37
        out(f, a, l);
        if (l)
            continue;
        if (s[1] == 0)
            break;
        switch (s[1])
    137a:	07300a13          	li	s4,115
        case 'p':
            printptr(va_arg(ap, uint64));
            break;
        case 's':
            if ((a = va_arg(ap, char *)) == 0)
                a = "(null)";
    137e:	00001b97          	auipc	s7,0x1
    1382:	bdab8b93          	addi	s7,s7,-1062 # 1f58 <__clone+0x96>
        switch (s[1])
    1386:	07800a93          	li	s5,120
    138a:	06400b13          	li	s6,100
        buf[i++] = digits[x >> (sizeof(uint64) * 8 - 4)];
    138e:	00001997          	auipc	s3,0x1
    1392:	bfa98993          	addi	s3,s3,-1030 # 1f88 <digits>
        if (!*s)
    1396:	00054783          	lbu	a5,0(a0)
    139a:	16078c63          	beqz	a5,1512 <printf+0x1c2>
    139e:	862a                	mv	a2,a0
        for (a = s; *s && *s != '%'; s++)
    13a0:	19278463          	beq	a5,s2,1528 <printf+0x1d8>
    13a4:	00164783          	lbu	a5,1(a2)
    13a8:	0605                	addi	a2,a2,1
    13aa:	fbfd                	bnez	a5,13a0 <printf+0x50>
    13ac:	84b2                	mv	s1,a2
        l = z - a;
    13ae:	40a6043b          	subw	s0,a2,a0
    write(f, s, l);
    13b2:	85aa                	mv	a1,a0
    13b4:	8622                	mv	a2,s0
    13b6:	4505                	li	a0,1
    13b8:	0d3000ef          	jal	ra,1c8a <write>
        if (l)
    13bc:	18041f63          	bnez	s0,155a <printf+0x20a>
        if (s[1] == 0)
    13c0:	0014c783          	lbu	a5,1(s1)
    13c4:	14078763          	beqz	a5,1512 <printf+0x1c2>
        switch (s[1])
    13c8:	1d478163          	beq	a5,s4,158a <printf+0x23a>
    13cc:	18fa6963          	bltu	s4,a5,155e <printf+0x20e>
    13d0:	1b678363          	beq	a5,s6,1576 <printf+0x226>
    13d4:	07000713          	li	a4,112
    13d8:	1ce79c63          	bne	a5,a4,15b0 <printf+0x260>
            printptr(va_arg(ap, uint64));
    13dc:	6702                	ld	a4,0(sp)
    buf[i++] = '0';
    13de:	03000793          	li	a5,48
    13e2:	00f10423          	sb	a5,8(sp)
            printptr(va_arg(ap, uint64));
    13e6:	631c                	ld	a5,0(a4)
    13e8:	0721                	addi	a4,a4,8
    13ea:	e03a                	sd	a4,0(sp)
    for (j = 0; j < (sizeof(uint64) * 2); j++, x <<= 4)
    13ec:	00479f93          	slli	t6,a5,0x4
    13f0:	00879f13          	slli	t5,a5,0x8
    13f4:	00c79e93          	slli	t4,a5,0xc
    13f8:	01079e13          	slli	t3,a5,0x10
    13fc:	01479313          	slli	t1,a5,0x14
    1400:	01879893          	slli	a7,a5,0x18
    1404:	01c79713          	slli	a4,a5,0x1c
    1408:	02479813          	slli	a6,a5,0x24
    140c:	02879513          	slli	a0,a5,0x28
    1410:	02c79593          	slli	a1,a5,0x2c
    1414:	03079613          	slli	a2,a5,0x30
        buf[i++] = digits[x >> (sizeof(uint64) * 8 - 4)];
    1418:	03c7d293          	srli	t0,a5,0x3c
    141c:	01c7d39b          	srliw	t2,a5,0x1c
    for (j = 0; j < (sizeof(uint64) * 2); j++, x <<= 4)
    1420:	03479693          	slli	a3,a5,0x34
        buf[i++] = digits[x >> (sizeof(uint64) * 8 - 4)];
    1424:	03cfdf93          	srli	t6,t6,0x3c
    1428:	03cf5f13          	srli	t5,t5,0x3c
    142c:	03cede93          	srli	t4,t4,0x3c
    1430:	03ce5e13          	srli	t3,t3,0x3c
    1434:	03c35313          	srli	t1,t1,0x3c
    1438:	03c8d893          	srli	a7,a7,0x3c
    143c:	9371                	srli	a4,a4,0x3c
    143e:	03c85813          	srli	a6,a6,0x3c
    1442:	9171                	srli	a0,a0,0x3c
    1444:	91f1                	srli	a1,a1,0x3c
    1446:	9271                	srli	a2,a2,0x3c
    1448:	974e                	add	a4,a4,s3
    144a:	92f1                	srli	a3,a3,0x3c
    144c:	92ce                	add	t0,t0,s3
    144e:	9fce                	add	t6,t6,s3
    1450:	9f4e                	add	t5,t5,s3
    1452:	9ece                	add	t4,t4,s3
    1454:	9e4e                	add	t3,t3,s3
    1456:	934e                	add	t1,t1,s3
    1458:	98ce                	add	a7,a7,s3
    145a:	93ce                	add	t2,t2,s3
    145c:	984e                	add	a6,a6,s3
    145e:	954e                	add	a0,a0,s3
    1460:	95ce                	add	a1,a1,s3
    1462:	964e                	add	a2,a2,s3
    1464:	0002c283          	lbu	t0,0(t0)
    1468:	000fcf83          	lbu	t6,0(t6)
    146c:	000f4f03          	lbu	t5,0(t5)
    1470:	000ece83          	lbu	t4,0(t4)
    1474:	000e4e03          	lbu	t3,0(t3)
    1478:	00034303          	lbu	t1,0(t1)
    147c:	0008c883          	lbu	a7,0(a7)
    1480:	00074403          	lbu	s0,0(a4)
    1484:	0003c383          	lbu	t2,0(t2)
    1488:	00084803          	lbu	a6,0(a6)
    148c:	00054503          	lbu	a0,0(a0)
    1490:	0005c583          	lbu	a1,0(a1)
    1494:	00064603          	lbu	a2,0(a2)
    1498:	00d98733          	add	a4,s3,a3
    149c:	00074683          	lbu	a3,0(a4)
    for (j = 0; j < (sizeof(uint64) * 2); j++, x <<= 4)
    14a0:	03879713          	slli	a4,a5,0x38
        buf[i++] = digits[x >> (sizeof(uint64) * 8 - 4)];
    14a4:	9371                	srli	a4,a4,0x3c
    14a6:	8bbd                	andi	a5,a5,15
    14a8:	00510523          	sb	t0,10(sp)
    14ac:	01f105a3          	sb	t6,11(sp)
    14b0:	01e10623          	sb	t5,12(sp)
    14b4:	01d106a3          	sb	t4,13(sp)
    14b8:	01c10723          	sb	t3,14(sp)
    14bc:	006107a3          	sb	t1,15(sp)
    14c0:	01110823          	sb	a7,16(sp)
    14c4:	00710923          	sb	t2,18(sp)
    14c8:	010109a3          	sb	a6,19(sp)
    14cc:	00a10a23          	sb	a0,20(sp)
    14d0:	00b10aa3          	sb	a1,21(sp)
    14d4:	00c10b23          	sb	a2,22(sp)
    buf[i++] = 'x';
    14d8:	015104a3          	sb	s5,9(sp)
        buf[i++] = digits[x >> (sizeof(uint64) * 8 - 4)];
    14dc:	008108a3          	sb	s0,17(sp)
    14e0:	974e                	add	a4,a4,s3
    14e2:	97ce                	add	a5,a5,s3
    14e4:	00d10ba3          	sb	a3,23(sp)
    14e8:	00074703          	lbu	a4,0(a4)
    14ec:	0007c783          	lbu	a5,0(a5)
    write(f, s, l);
    14f0:	4649                	li	a2,18
    14f2:	002c                	addi	a1,sp,8
    14f4:	4505                	li	a0,1
        buf[i++] = digits[x >> (sizeof(uint64) * 8 - 4)];
    14f6:	00e10c23          	sb	a4,24(sp)
    14fa:	00f10ca3          	sb	a5,25(sp)
    buf[i] = 0;
    14fe:	00010d23          	sb	zero,26(sp)
    write(f, s, l);
    1502:	788000ef          	jal	ra,1c8a <write>
            // Print unknown % sequence to draw attention.
            putchar('%');
            putchar(s[1]);
            break;
        }
        s += 2;
    1506:	00248513          	addi	a0,s1,2
        if (!*s)
    150a:	00054783          	lbu	a5,0(a0)
    150e:	e80798e3          	bnez	a5,139e <printf+0x4e>
    }
    va_end(ap);
}
    1512:	70e6                	ld	ra,120(sp)
    1514:	7446                	ld	s0,112(sp)
    1516:	74a6                	ld	s1,104(sp)
    1518:	7906                	ld	s2,96(sp)
    151a:	69e6                	ld	s3,88(sp)
    151c:	6a46                	ld	s4,80(sp)
    151e:	6aa6                	ld	s5,72(sp)
    1520:	6b06                	ld	s6,64(sp)
    1522:	7be2                	ld	s7,56(sp)
    1524:	6129                	addi	sp,sp,192
    1526:	8082                	ret
        for (z = s; s[0] == '%' && s[1] == '%'; z++, s += 2)
    1528:	00064783          	lbu	a5,0(a2)
    152c:	84b2                	mv	s1,a2
    152e:	01278963          	beq	a5,s2,1540 <printf+0x1f0>
    1532:	bdb5                	j	13ae <printf+0x5e>
    1534:	0024c783          	lbu	a5,2(s1)
    1538:	0605                	addi	a2,a2,1
    153a:	0489                	addi	s1,s1,2
    153c:	e72799e3          	bne	a5,s2,13ae <printf+0x5e>
    1540:	0014c783          	lbu	a5,1(s1)
    1544:	ff2788e3          	beq	a5,s2,1534 <printf+0x1e4>
        l = z - a;
    1548:	40a6043b          	subw	s0,a2,a0
    write(f, s, l);
    154c:	85aa                	mv	a1,a0
    154e:	8622                	mv	a2,s0
    1550:	4505                	li	a0,1
    1552:	738000ef          	jal	ra,1c8a <write>
        if (l)
    1556:	e60405e3          	beqz	s0,13c0 <printf+0x70>
    155a:	8526                	mv	a0,s1
    155c:	bd2d                	j	1396 <printf+0x46>
        switch (s[1])
    155e:	05579963          	bne	a5,s5,15b0 <printf+0x260>
            printint(va_arg(ap, int), 16, 1);
    1562:	6782                	ld	a5,0(sp)
    1564:	45c1                	li	a1,16
    1566:	4388                	lw	a0,0(a5)
    1568:	07a1                	addi	a5,a5,8
    156a:	e03e                	sd	a5,0(sp)
    156c:	b6bff0ef          	jal	ra,10d6 <printint.constprop.0>
        s += 2;
    1570:	00248513          	addi	a0,s1,2
    1574:	bf59                	j	150a <printf+0x1ba>
            printint(va_arg(ap, int), 10, 1);
    1576:	6782                	ld	a5,0(sp)
    1578:	45a9                	li	a1,10
    157a:	4388                	lw	a0,0(a5)
    157c:	07a1                	addi	a5,a5,8
    157e:	e03e                	sd	a5,0(sp)
    1580:	b57ff0ef          	jal	ra,10d6 <printint.constprop.0>
        s += 2;
    1584:	00248513          	addi	a0,s1,2
    1588:	b749                	j	150a <printf+0x1ba>
            if ((a = va_arg(ap, char *)) == 0)
    158a:	6782                	ld	a5,0(sp)
    158c:	6380                	ld	s0,0(a5)
    158e:	07a1                	addi	a5,a5,8
    1590:	e03e                	sd	a5,0(sp)
    1592:	c031                	beqz	s0,15d6 <printf+0x286>
            l = strnlen(a, 200);
    1594:	0c800593          	li	a1,200
    1598:	8522                	mv	a0,s0
    159a:	3f8000ef          	jal	ra,1992 <strnlen>
    write(f, s, l);
    159e:	0005061b          	sext.w	a2,a0
    15a2:	85a2                	mv	a1,s0
    15a4:	4505                	li	a0,1
    15a6:	6e4000ef          	jal	ra,1c8a <write>
        s += 2;
    15aa:	00248513          	addi	a0,s1,2
    15ae:	bfb1                	j	150a <printf+0x1ba>
    return write(stdout, &byte, 1);
    15b0:	4605                	li	a2,1
    15b2:	002c                	addi	a1,sp,8
    15b4:	4505                	li	a0,1
    char byte = c;
    15b6:	01210423          	sb	s2,8(sp)
    return write(stdout, &byte, 1);
    15ba:	6d0000ef          	jal	ra,1c8a <write>
    char byte = c;
    15be:	0014c783          	lbu	a5,1(s1)
    return write(stdout, &byte, 1);
    15c2:	4605                	li	a2,1
    15c4:	002c                	addi	a1,sp,8
    15c6:	4505                	li	a0,1
    char byte = c;
    15c8:	00f10423          	sb	a5,8(sp)
    return write(stdout, &byte, 1);
    15cc:	6be000ef          	jal	ra,1c8a <write>
        s += 2;
    15d0:	00248513          	addi	a0,s1,2
    15d4:	bf1d                	j	150a <printf+0x1ba>
                a = "(null)";
    15d6:	845e                	mv	s0,s7
    15d8:	bf75                	j	1594 <printf+0x244>

00000000000015da <isspace>:
#define HIGHS (ONES * (UCHAR_MAX / 2 + 1))
#define HASZERO(x) (((x)-ONES) & ~(x)&HIGHS)

int isspace(int c)
{
    return c == ' ' || (unsigned)c - '\t' < 5;
    15da:	02000793          	li	a5,32
    15de:	00f50663          	beq	a0,a5,15ea <isspace+0x10>
    15e2:	355d                	addiw	a0,a0,-9
    15e4:	00553513          	sltiu	a0,a0,5
    15e8:	8082                	ret
    15ea:	4505                	li	a0,1
}
    15ec:	8082                	ret

00000000000015ee <isdigit>:

int isdigit(int c)
{
    return (unsigned)c - '0' < 10;
    15ee:	fd05051b          	addiw	a0,a0,-48
}
    15f2:	00a53513          	sltiu	a0,a0,10
    15f6:	8082                	ret

00000000000015f8 <atoi>:
    return c == ' ' || (unsigned)c - '\t' < 5;
    15f8:	02000613          	li	a2,32
    15fc:	4591                	li	a1,4

int atoi(const char *s)
{
    int n = 0, neg = 0;
    while (isspace(*s))
    15fe:	00054703          	lbu	a4,0(a0)
    return c == ' ' || (unsigned)c - '\t' < 5;
    1602:	ff77069b          	addiw	a3,a4,-9
    1606:	04c70d63          	beq	a4,a2,1660 <atoi+0x68>
    160a:	0007079b          	sext.w	a5,a4
    160e:	04d5f963          	bgeu	a1,a3,1660 <atoi+0x68>
        s++;
    switch (*s)
    1612:	02b00693          	li	a3,43
    1616:	04d70a63          	beq	a4,a3,166a <atoi+0x72>
    161a:	02d00693          	li	a3,45
    161e:	06d70463          	beq	a4,a3,1686 <atoi+0x8e>
        neg = 1;
    case '+':
        s++;
    }
    /* Compute n as a negative number to avoid overflow on INT_MIN */
    while (isdigit(*s))
    1622:	fd07859b          	addiw	a1,a5,-48
    1626:	4625                	li	a2,9
    1628:	873e                	mv	a4,a5
    162a:	86aa                	mv	a3,a0
    int n = 0, neg = 0;
    162c:	4e01                	li	t3,0
    while (isdigit(*s))
    162e:	04b66a63          	bltu	a2,a1,1682 <atoi+0x8a>
    int n = 0, neg = 0;
    1632:	4501                	li	a0,0
    while (isdigit(*s))
    1634:	4825                	li	a6,9
    1636:	0016c603          	lbu	a2,1(a3)
        n = 10 * n - (*s++ - '0');
    163a:	0025179b          	slliw	a5,a0,0x2
    163e:	9d3d                	addw	a0,a0,a5
    1640:	fd07031b          	addiw	t1,a4,-48
    1644:	0015189b          	slliw	a7,a0,0x1
    while (isdigit(*s))
    1648:	fd06059b          	addiw	a1,a2,-48
        n = 10 * n - (*s++ - '0');
    164c:	0685                	addi	a3,a3,1
    164e:	4068853b          	subw	a0,a7,t1
    while (isdigit(*s))
    1652:	0006071b          	sext.w	a4,a2
    1656:	feb870e3          	bgeu	a6,a1,1636 <atoi+0x3e>
    return neg ? n : -n;
    165a:	000e0563          	beqz	t3,1664 <atoi+0x6c>
}
    165e:	8082                	ret
        s++;
    1660:	0505                	addi	a0,a0,1
    1662:	bf71                	j	15fe <atoi+0x6>
    return neg ? n : -n;
    1664:	4113053b          	subw	a0,t1,a7
    1668:	8082                	ret
    while (isdigit(*s))
    166a:	00154783          	lbu	a5,1(a0)
    166e:	4625                	li	a2,9
        s++;
    1670:	00150693          	addi	a3,a0,1
    while (isdigit(*s))
    1674:	fd07859b          	addiw	a1,a5,-48
    1678:	0007871b          	sext.w	a4,a5
    int n = 0, neg = 0;
    167c:	4e01                	li	t3,0
    while (isdigit(*s))
    167e:	fab67ae3          	bgeu	a2,a1,1632 <atoi+0x3a>
    1682:	4501                	li	a0,0
}
    1684:	8082                	ret
    while (isdigit(*s))
    1686:	00154783          	lbu	a5,1(a0)
    168a:	4625                	li	a2,9
        s++;
    168c:	00150693          	addi	a3,a0,1
    while (isdigit(*s))
    1690:	fd07859b          	addiw	a1,a5,-48
    1694:	0007871b          	sext.w	a4,a5
    1698:	feb665e3          	bltu	a2,a1,1682 <atoi+0x8a>
        neg = 1;
    169c:	4e05                	li	t3,1
    169e:	bf51                	j	1632 <atoi+0x3a>

00000000000016a0 <memset>:

void *memset(void *dest, int c, size_t n)
{
    char *p = dest;
    for (int i = 0; i < n; ++i, *(p++) = c)
    16a0:	16060d63          	beqz	a2,181a <memset+0x17a>
    16a4:	40a007b3          	neg	a5,a0
    16a8:	8b9d                	andi	a5,a5,7
    16aa:	00778713          	addi	a4,a5,7
    16ae:	482d                	li	a6,11
    16b0:	0ff5f593          	andi	a1,a1,255
    16b4:	fff60693          	addi	a3,a2,-1
    16b8:	17076263          	bltu	a4,a6,181c <memset+0x17c>
    16bc:	16e6ea63          	bltu	a3,a4,1830 <memset+0x190>
    16c0:	16078563          	beqz	a5,182a <memset+0x18a>
    16c4:	00b50023          	sb	a1,0(a0)
    16c8:	4705                	li	a4,1
    16ca:	00150e93          	addi	t4,a0,1
    16ce:	14e78c63          	beq	a5,a4,1826 <memset+0x186>
    16d2:	00b500a3          	sb	a1,1(a0)
    16d6:	4709                	li	a4,2
    16d8:	00250e93          	addi	t4,a0,2
    16dc:	14e78d63          	beq	a5,a4,1836 <memset+0x196>
    16e0:	00b50123          	sb	a1,2(a0)
    16e4:	470d                	li	a4,3
    16e6:	00350e93          	addi	t4,a0,3
    16ea:	12e78b63          	beq	a5,a4,1820 <memset+0x180>
    16ee:	00b501a3          	sb	a1,3(a0)
    16f2:	4711                	li	a4,4
    16f4:	00450e93          	addi	t4,a0,4
    16f8:	14e78163          	beq	a5,a4,183a <memset+0x19a>
    16fc:	00b50223          	sb	a1,4(a0)
    1700:	4715                	li	a4,5
    1702:	00550e93          	addi	t4,a0,5
    1706:	12e78c63          	beq	a5,a4,183e <memset+0x19e>
    170a:	00b502a3          	sb	a1,5(a0)
    170e:	471d                	li	a4,7
    1710:	00650e93          	addi	t4,a0,6
    1714:	12e79763          	bne	a5,a4,1842 <memset+0x1a2>
    1718:	00750e93          	addi	t4,a0,7
    171c:	00b50323          	sb	a1,6(a0)
    1720:	4f1d                	li	t5,7
    1722:	00859713          	slli	a4,a1,0x8
    1726:	8f4d                	or	a4,a4,a1
    1728:	01059e13          	slli	t3,a1,0x10
    172c:	01c76e33          	or	t3,a4,t3
    1730:	01859313          	slli	t1,a1,0x18
    1734:	006e6333          	or	t1,t3,t1
    1738:	02059893          	slli	a7,a1,0x20
    173c:	011368b3          	or	a7,t1,a7
    1740:	02859813          	slli	a6,a1,0x28
    1744:	40f60333          	sub	t1,a2,a5
    1748:	0108e833          	or	a6,a7,a6
    174c:	03059693          	slli	a3,a1,0x30
    1750:	00d866b3          	or	a3,a6,a3
    1754:	03859713          	slli	a4,a1,0x38
    1758:	97aa                	add	a5,a5,a0
    175a:	ff837813          	andi	a6,t1,-8
    175e:	8f55                	or	a4,a4,a3
    1760:	00f806b3          	add	a3,a6,a5
    1764:	e398                	sd	a4,0(a5)
    1766:	07a1                	addi	a5,a5,8
    1768:	fed79ee3          	bne	a5,a3,1764 <memset+0xc4>
    176c:	ff837693          	andi	a3,t1,-8
    1770:	00de87b3          	add	a5,t4,a3
    1774:	01e6873b          	addw	a4,a3,t5
    1778:	0ad30663          	beq	t1,a3,1824 <memset+0x184>
    177c:	00b78023          	sb	a1,0(a5)
    1780:	0017069b          	addiw	a3,a4,1
    1784:	08c6fb63          	bgeu	a3,a2,181a <memset+0x17a>
    1788:	00b780a3          	sb	a1,1(a5)
    178c:	0027069b          	addiw	a3,a4,2
    1790:	08c6f563          	bgeu	a3,a2,181a <memset+0x17a>
    1794:	00b78123          	sb	a1,2(a5)
    1798:	0037069b          	addiw	a3,a4,3
    179c:	06c6ff63          	bgeu	a3,a2,181a <memset+0x17a>
    17a0:	00b781a3          	sb	a1,3(a5)
    17a4:	0047069b          	addiw	a3,a4,4
    17a8:	06c6f963          	bgeu	a3,a2,181a <memset+0x17a>
    17ac:	00b78223          	sb	a1,4(a5)
    17b0:	0057069b          	addiw	a3,a4,5
    17b4:	06c6f363          	bgeu	a3,a2,181a <memset+0x17a>
    17b8:	00b782a3          	sb	a1,5(a5)
    17bc:	0067069b          	addiw	a3,a4,6
    17c0:	04c6fd63          	bgeu	a3,a2,181a <memset+0x17a>
    17c4:	00b78323          	sb	a1,6(a5)
    17c8:	0077069b          	addiw	a3,a4,7
    17cc:	04c6f763          	bgeu	a3,a2,181a <memset+0x17a>
    17d0:	00b783a3          	sb	a1,7(a5)
    17d4:	0087069b          	addiw	a3,a4,8
    17d8:	04c6f163          	bgeu	a3,a2,181a <memset+0x17a>
    17dc:	00b78423          	sb	a1,8(a5)
    17e0:	0097069b          	addiw	a3,a4,9
    17e4:	02c6fb63          	bgeu	a3,a2,181a <memset+0x17a>
    17e8:	00b784a3          	sb	a1,9(a5)
    17ec:	00a7069b          	addiw	a3,a4,10
    17f0:	02c6f563          	bgeu	a3,a2,181a <memset+0x17a>
    17f4:	00b78523          	sb	a1,10(a5)
    17f8:	00b7069b          	addiw	a3,a4,11
    17fc:	00c6ff63          	bgeu	a3,a2,181a <memset+0x17a>
    1800:	00b785a3          	sb	a1,11(a5)
    1804:	00c7069b          	addiw	a3,a4,12
    1808:	00c6f963          	bgeu	a3,a2,181a <memset+0x17a>
    180c:	00b78623          	sb	a1,12(a5)
    1810:	2735                	addiw	a4,a4,13
    1812:	00c77463          	bgeu	a4,a2,181a <memset+0x17a>
    1816:	00b786a3          	sb	a1,13(a5)
        ;
    return dest;
}
    181a:	8082                	ret
    181c:	472d                	li	a4,11
    181e:	bd79                	j	16bc <memset+0x1c>
    for (int i = 0; i < n; ++i, *(p++) = c)
    1820:	4f0d                	li	t5,3
    1822:	b701                	j	1722 <memset+0x82>
    1824:	8082                	ret
    1826:	4f05                	li	t5,1
    1828:	bded                	j	1722 <memset+0x82>
    182a:	8eaa                	mv	t4,a0
    182c:	4f01                	li	t5,0
    182e:	bdd5                	j	1722 <memset+0x82>
    1830:	87aa                	mv	a5,a0
    1832:	4701                	li	a4,0
    1834:	b7a1                	j	177c <memset+0xdc>
    1836:	4f09                	li	t5,2
    1838:	b5ed                	j	1722 <memset+0x82>
    183a:	4f11                	li	t5,4
    183c:	b5dd                	j	1722 <memset+0x82>
    183e:	4f15                	li	t5,5
    1840:	b5cd                	j	1722 <memset+0x82>
    1842:	4f19                	li	t5,6
    1844:	bdf9                	j	1722 <memset+0x82>

0000000000001846 <strcmp>:

int strcmp(const char *l, const char *r)
{
    for (; *l == *r && *l; l++, r++)
    1846:	00054783          	lbu	a5,0(a0)
    184a:	0005c703          	lbu	a4,0(a1)
    184e:	00e79863          	bne	a5,a4,185e <strcmp+0x18>
    1852:	0505                	addi	a0,a0,1
    1854:	0585                	addi	a1,a1,1
    1856:	fbe5                	bnez	a5,1846 <strcmp>
    1858:	4501                	li	a0,0
        ;
    return *(unsigned char *)l - *(unsigned char *)r;
}
    185a:	9d19                	subw	a0,a0,a4
    185c:	8082                	ret
    return *(unsigned char *)l - *(unsigned char *)r;
    185e:	0007851b          	sext.w	a0,a5
    1862:	bfe5                	j	185a <strcmp+0x14>

0000000000001864 <strncmp>:

int strncmp(const char *_l, const char *_r, size_t n)
{
    const unsigned char *l = (void *)_l, *r = (void *)_r;
    if (!n--)
    1864:	ce05                	beqz	a2,189c <strncmp+0x38>
        return 0;
    for (; *l && *r && n && *l == *r; l++, r++, n--)
    1866:	00054703          	lbu	a4,0(a0)
    186a:	0005c783          	lbu	a5,0(a1)
    186e:	cb0d                	beqz	a4,18a0 <strncmp+0x3c>
    if (!n--)
    1870:	167d                	addi	a2,a2,-1
    1872:	00c506b3          	add	a3,a0,a2
    1876:	a819                	j	188c <strncmp+0x28>
    for (; *l && *r && n && *l == *r; l++, r++, n--)
    1878:	00a68e63          	beq	a3,a0,1894 <strncmp+0x30>
    187c:	0505                	addi	a0,a0,1
    187e:	00e79b63          	bne	a5,a4,1894 <strncmp+0x30>
    1882:	00054703          	lbu	a4,0(a0)
        ;
    return *l - *r;
    1886:	0005c783          	lbu	a5,0(a1)
    for (; *l && *r && n && *l == *r; l++, r++, n--)
    188a:	cb19                	beqz	a4,18a0 <strncmp+0x3c>
    188c:	0005c783          	lbu	a5,0(a1)
    1890:	0585                	addi	a1,a1,1
    1892:	f3fd                	bnez	a5,1878 <strncmp+0x14>
    return *l - *r;
    1894:	0007051b          	sext.w	a0,a4
    1898:	9d1d                	subw	a0,a0,a5
    189a:	8082                	ret
        return 0;
    189c:	4501                	li	a0,0
}
    189e:	8082                	ret
    18a0:	4501                	li	a0,0
    return *l - *r;
    18a2:	9d1d                	subw	a0,a0,a5
    18a4:	8082                	ret

00000000000018a6 <strlen>:
size_t strlen(const char *s)
{
    const char *a = s;
    typedef size_t __attribute__((__may_alias__)) word;
    const word *w;
    for (; (uintptr_t)s % SS; s++)
    18a6:	00757793          	andi	a5,a0,7
    18aa:	cf89                	beqz	a5,18c4 <strlen+0x1e>
    18ac:	87aa                	mv	a5,a0
    18ae:	a029                	j	18b8 <strlen+0x12>
    18b0:	0785                	addi	a5,a5,1
    18b2:	0077f713          	andi	a4,a5,7
    18b6:	cb01                	beqz	a4,18c6 <strlen+0x20>
        if (!*s)
    18b8:	0007c703          	lbu	a4,0(a5)
    18bc:	fb75                	bnez	a4,18b0 <strlen+0xa>
    for (w = (const void *)s; !HASZERO(*w); w++)
        ;
    s = (const void *)w;
    for (; *s; s++)
        ;
    return s - a;
    18be:	40a78533          	sub	a0,a5,a0
}
    18c2:	8082                	ret
    for (; (uintptr_t)s % SS; s++)
    18c4:	87aa                	mv	a5,a0
    for (w = (const void *)s; !HASZERO(*w); w++)
    18c6:	6394                	ld	a3,0(a5)
    18c8:	00000597          	auipc	a1,0x0
    18cc:	6985b583          	ld	a1,1688(a1) # 1f60 <__clone+0x9e>
    18d0:	00000617          	auipc	a2,0x0
    18d4:	69863603          	ld	a2,1688(a2) # 1f68 <__clone+0xa6>
    18d8:	a019                	j	18de <strlen+0x38>
    18da:	6794                	ld	a3,8(a5)
    18dc:	07a1                	addi	a5,a5,8
    18de:	00b68733          	add	a4,a3,a1
    18e2:	fff6c693          	not	a3,a3
    18e6:	8f75                	and	a4,a4,a3
    18e8:	8f71                	and	a4,a4,a2
    18ea:	db65                	beqz	a4,18da <strlen+0x34>
    for (; *s; s++)
    18ec:	0007c703          	lbu	a4,0(a5)
    18f0:	d779                	beqz	a4,18be <strlen+0x18>
    18f2:	0017c703          	lbu	a4,1(a5)
    18f6:	0785                	addi	a5,a5,1
    18f8:	d379                	beqz	a4,18be <strlen+0x18>
    18fa:	0017c703          	lbu	a4,1(a5)
    18fe:	0785                	addi	a5,a5,1
    1900:	fb6d                	bnez	a4,18f2 <strlen+0x4c>
    1902:	bf75                	j	18be <strlen+0x18>

0000000000001904 <memchr>:

void *memchr(const void *src, int c, size_t n)
{
    const unsigned char *s = src;
    c = (unsigned char)c;
    for (; ((uintptr_t)s & ALIGN) && n && *s != c; s++, n--)
    1904:	00757713          	andi	a4,a0,7
{
    1908:	87aa                	mv	a5,a0
    c = (unsigned char)c;
    190a:	0ff5f593          	andi	a1,a1,255
    for (; ((uintptr_t)s & ALIGN) && n && *s != c; s++, n--)
    190e:	cb19                	beqz	a4,1924 <memchr+0x20>
    1910:	ce25                	beqz	a2,1988 <memchr+0x84>
    1912:	0007c703          	lbu	a4,0(a5)
    1916:	04b70e63          	beq	a4,a1,1972 <memchr+0x6e>
    191a:	0785                	addi	a5,a5,1
    191c:	0077f713          	andi	a4,a5,7
    1920:	167d                	addi	a2,a2,-1
    1922:	f77d                	bnez	a4,1910 <memchr+0xc>
            ;
        s = (const void *)w;
    }
    for (; n && *s != c; s++, n--)
        ;
    return n ? (void *)s : 0;
    1924:	4501                	li	a0,0
    if (n && *s != c)
    1926:	c235                	beqz	a2,198a <memchr+0x86>
    1928:	0007c703          	lbu	a4,0(a5)
    192c:	04b70363          	beq	a4,a1,1972 <memchr+0x6e>
        size_t k = ONES * c;
    1930:	00000517          	auipc	a0,0x0
    1934:	64053503          	ld	a0,1600(a0) # 1f70 <__clone+0xae>
        for (w = (const void *)s; n >= SS && !HASZERO(*w ^ k); w++, n -= SS)
    1938:	471d                	li	a4,7
        size_t k = ONES * c;
    193a:	02a58533          	mul	a0,a1,a0
        for (w = (const void *)s; n >= SS && !HASZERO(*w ^ k); w++, n -= SS)
    193e:	02c77a63          	bgeu	a4,a2,1972 <memchr+0x6e>
    1942:	00000897          	auipc	a7,0x0
    1946:	61e8b883          	ld	a7,1566(a7) # 1f60 <__clone+0x9e>
    194a:	00000817          	auipc	a6,0x0
    194e:	61e83803          	ld	a6,1566(a6) # 1f68 <__clone+0xa6>
    1952:	431d                	li	t1,7
    1954:	a029                	j	195e <memchr+0x5a>
    1956:	1661                	addi	a2,a2,-8
    1958:	07a1                	addi	a5,a5,8
    195a:	02c37963          	bgeu	t1,a2,198c <memchr+0x88>
    195e:	6398                	ld	a4,0(a5)
    1960:	8f29                	xor	a4,a4,a0
    1962:	011706b3          	add	a3,a4,a7
    1966:	fff74713          	not	a4,a4
    196a:	8f75                	and	a4,a4,a3
    196c:	01077733          	and	a4,a4,a6
    1970:	d37d                	beqz	a4,1956 <memchr+0x52>
    1972:	853e                	mv	a0,a5
    1974:	97b2                	add	a5,a5,a2
    1976:	a021                	j	197e <memchr+0x7a>
    for (; n && *s != c; s++, n--)
    1978:	0505                	addi	a0,a0,1
    197a:	00f50763          	beq	a0,a5,1988 <memchr+0x84>
    197e:	00054703          	lbu	a4,0(a0)
    1982:	feb71be3          	bne	a4,a1,1978 <memchr+0x74>
    1986:	8082                	ret
    return n ? (void *)s : 0;
    1988:	4501                	li	a0,0
}
    198a:	8082                	ret
    return n ? (void *)s : 0;
    198c:	4501                	li	a0,0
    for (; n && *s != c; s++, n--)
    198e:	f275                	bnez	a2,1972 <memchr+0x6e>
}
    1990:	8082                	ret

0000000000001992 <strnlen>:

size_t strnlen(const char *s, size_t n)
{
    1992:	1101                	addi	sp,sp,-32
    1994:	e822                	sd	s0,16(sp)
    const char *p = memchr(s, 0, n);
    1996:	862e                	mv	a2,a1
{
    1998:	842e                	mv	s0,a1
    const char *p = memchr(s, 0, n);
    199a:	4581                	li	a1,0
{
    199c:	e426                	sd	s1,8(sp)
    199e:	ec06                	sd	ra,24(sp)
    19a0:	84aa                	mv	s1,a0
    const char *p = memchr(s, 0, n);
    19a2:	f63ff0ef          	jal	ra,1904 <memchr>
    return p ? p - s : n;
    19a6:	c519                	beqz	a0,19b4 <strnlen+0x22>
}
    19a8:	60e2                	ld	ra,24(sp)
    19aa:	6442                	ld	s0,16(sp)
    return p ? p - s : n;
    19ac:	8d05                	sub	a0,a0,s1
}
    19ae:	64a2                	ld	s1,8(sp)
    19b0:	6105                	addi	sp,sp,32
    19b2:	8082                	ret
    19b4:	60e2                	ld	ra,24(sp)
    return p ? p - s : n;
    19b6:	8522                	mv	a0,s0
}
    19b8:	6442                	ld	s0,16(sp)
    19ba:	64a2                	ld	s1,8(sp)
    19bc:	6105                	addi	sp,sp,32
    19be:	8082                	ret

00000000000019c0 <strcpy>:
char *strcpy(char *restrict d, const char *s)
{
    typedef size_t __attribute__((__may_alias__)) word;
    word *wd;
    const word *ws;
    if ((uintptr_t)s % SS == (uintptr_t)d % SS)
    19c0:	00b547b3          	xor	a5,a0,a1
    19c4:	8b9d                	andi	a5,a5,7
    19c6:	eb95                	bnez	a5,19fa <strcpy+0x3a>
    {
        for (; (uintptr_t)s % SS; s++, d++)
    19c8:	0075f793          	andi	a5,a1,7
    19cc:	e7b1                	bnez	a5,1a18 <strcpy+0x58>
            if (!(*d = *s))
                return d;
        wd = (void *)d;
        ws = (const void *)s;
        for (; !HASZERO(*ws); *wd++ = *ws++)
    19ce:	6198                	ld	a4,0(a1)
    19d0:	00000617          	auipc	a2,0x0
    19d4:	59063603          	ld	a2,1424(a2) # 1f60 <__clone+0x9e>
    19d8:	00000817          	auipc	a6,0x0
    19dc:	59083803          	ld	a6,1424(a6) # 1f68 <__clone+0xa6>
    19e0:	a029                	j	19ea <strcpy+0x2a>
    19e2:	e118                	sd	a4,0(a0)
    19e4:	6598                	ld	a4,8(a1)
    19e6:	05a1                	addi	a1,a1,8
    19e8:	0521                	addi	a0,a0,8
    19ea:	00c707b3          	add	a5,a4,a2
    19ee:	fff74693          	not	a3,a4
    19f2:	8ff5                	and	a5,a5,a3
    19f4:	0107f7b3          	and	a5,a5,a6
    19f8:	d7ed                	beqz	a5,19e2 <strcpy+0x22>
            ;
        d = (void *)wd;
        s = (const void *)ws;
    }
    for (; (*d = *s); s++, d++)
    19fa:	0005c783          	lbu	a5,0(a1)
    19fe:	00f50023          	sb	a5,0(a0)
    1a02:	c785                	beqz	a5,1a2a <strcpy+0x6a>
    1a04:	0015c783          	lbu	a5,1(a1)
    1a08:	0505                	addi	a0,a0,1
    1a0a:	0585                	addi	a1,a1,1
    1a0c:	00f50023          	sb	a5,0(a0)
    1a10:	fbf5                	bnez	a5,1a04 <strcpy+0x44>
        ;
    return d;
}
    1a12:	8082                	ret
        for (; (uintptr_t)s % SS; s++, d++)
    1a14:	0505                	addi	a0,a0,1
    1a16:	df45                	beqz	a4,19ce <strcpy+0xe>
            if (!(*d = *s))
    1a18:	0005c783          	lbu	a5,0(a1)
        for (; (uintptr_t)s % SS; s++, d++)
    1a1c:	0585                	addi	a1,a1,1
    1a1e:	0075f713          	andi	a4,a1,7
            if (!(*d = *s))
    1a22:	00f50023          	sb	a5,0(a0)
    1a26:	f7fd                	bnez	a5,1a14 <strcpy+0x54>
}
    1a28:	8082                	ret
    1a2a:	8082                	ret

0000000000001a2c <strncpy>:
char *strncpy(char *restrict d, const char *s, size_t n)
{
    typedef size_t __attribute__((__may_alias__)) word;
    word *wd;
    const word *ws;
    if (((uintptr_t)s & ALIGN) == ((uintptr_t)d & ALIGN))
    1a2c:	00b547b3          	xor	a5,a0,a1
    1a30:	8b9d                	andi	a5,a5,7
    1a32:	1a079863          	bnez	a5,1be2 <strncpy+0x1b6>
    {
        for (; ((uintptr_t)s & ALIGN) && n && (*d = *s); n--, s++, d++)
    1a36:	0075f793          	andi	a5,a1,7
    1a3a:	16078463          	beqz	a5,1ba2 <strncpy+0x176>
    1a3e:	ea01                	bnez	a2,1a4e <strncpy+0x22>
    1a40:	a421                	j	1c48 <strncpy+0x21c>
    1a42:	167d                	addi	a2,a2,-1
    1a44:	0505                	addi	a0,a0,1
    1a46:	14070e63          	beqz	a4,1ba2 <strncpy+0x176>
    1a4a:	1a060863          	beqz	a2,1bfa <strncpy+0x1ce>
    1a4e:	0005c783          	lbu	a5,0(a1)
    1a52:	0585                	addi	a1,a1,1
    1a54:	0075f713          	andi	a4,a1,7
    1a58:	00f50023          	sb	a5,0(a0)
    1a5c:	f3fd                	bnez	a5,1a42 <strncpy+0x16>
    1a5e:	4805                	li	a6,1
    1a60:	1a061863          	bnez	a2,1c10 <strncpy+0x1e4>
    1a64:	40a007b3          	neg	a5,a0
    1a68:	8b9d                	andi	a5,a5,7
    1a6a:	4681                	li	a3,0
    1a6c:	18061a63          	bnez	a2,1c00 <strncpy+0x1d4>
    1a70:	00778713          	addi	a4,a5,7
    1a74:	45ad                	li	a1,11
    1a76:	18b76363          	bltu	a4,a1,1bfc <strncpy+0x1d0>
    1a7a:	1ae6eb63          	bltu	a3,a4,1c30 <strncpy+0x204>
    1a7e:	1a078363          	beqz	a5,1c24 <strncpy+0x1f8>
    for (int i = 0; i < n; ++i, *(p++) = c)
    1a82:	00050023          	sb	zero,0(a0)
    1a86:	4685                	li	a3,1
    1a88:	00150713          	addi	a4,a0,1
    1a8c:	18d78f63          	beq	a5,a3,1c2a <strncpy+0x1fe>
    1a90:	000500a3          	sb	zero,1(a0)
    1a94:	4689                	li	a3,2
    1a96:	00250713          	addi	a4,a0,2
    1a9a:	18d78e63          	beq	a5,a3,1c36 <strncpy+0x20a>
    1a9e:	00050123          	sb	zero,2(a0)
    1aa2:	468d                	li	a3,3
    1aa4:	00350713          	addi	a4,a0,3
    1aa8:	16d78c63          	beq	a5,a3,1c20 <strncpy+0x1f4>
    1aac:	000501a3          	sb	zero,3(a0)
    1ab0:	4691                	li	a3,4
    1ab2:	00450713          	addi	a4,a0,4
    1ab6:	18d78263          	beq	a5,a3,1c3a <strncpy+0x20e>
    1aba:	00050223          	sb	zero,4(a0)
    1abe:	4695                	li	a3,5
    1ac0:	00550713          	addi	a4,a0,5
    1ac4:	16d78d63          	beq	a5,a3,1c3e <strncpy+0x212>
    1ac8:	000502a3          	sb	zero,5(a0)
    1acc:	469d                	li	a3,7
    1ace:	00650713          	addi	a4,a0,6
    1ad2:	16d79863          	bne	a5,a3,1c42 <strncpy+0x216>
    1ad6:	00750713          	addi	a4,a0,7
    1ada:	00050323          	sb	zero,6(a0)
    1ade:	40f80833          	sub	a6,a6,a5
    1ae2:	ff887593          	andi	a1,a6,-8
    1ae6:	97aa                	add	a5,a5,a0
    1ae8:	95be                	add	a1,a1,a5
    1aea:	0007b023          	sd	zero,0(a5)
    1aee:	07a1                	addi	a5,a5,8
    1af0:	feb79de3          	bne	a5,a1,1aea <strncpy+0xbe>
    1af4:	ff887593          	andi	a1,a6,-8
    1af8:	9ead                	addw	a3,a3,a1
    1afa:	00b707b3          	add	a5,a4,a1
    1afe:	12b80863          	beq	a6,a1,1c2e <strncpy+0x202>
    1b02:	00078023          	sb	zero,0(a5)
    1b06:	0016871b          	addiw	a4,a3,1
    1b0a:	0ec77863          	bgeu	a4,a2,1bfa <strncpy+0x1ce>
    1b0e:	000780a3          	sb	zero,1(a5)
    1b12:	0026871b          	addiw	a4,a3,2
    1b16:	0ec77263          	bgeu	a4,a2,1bfa <strncpy+0x1ce>
    1b1a:	00078123          	sb	zero,2(a5)
    1b1e:	0036871b          	addiw	a4,a3,3
    1b22:	0cc77c63          	bgeu	a4,a2,1bfa <strncpy+0x1ce>
    1b26:	000781a3          	sb	zero,3(a5)
    1b2a:	0046871b          	addiw	a4,a3,4
    1b2e:	0cc77663          	bgeu	a4,a2,1bfa <strncpy+0x1ce>
    1b32:	00078223          	sb	zero,4(a5)
    1b36:	0056871b          	addiw	a4,a3,5
    1b3a:	0cc77063          	bgeu	a4,a2,1bfa <strncpy+0x1ce>
    1b3e:	000782a3          	sb	zero,5(a5)
    1b42:	0066871b          	addiw	a4,a3,6
    1b46:	0ac77a63          	bgeu	a4,a2,1bfa <strncpy+0x1ce>
    1b4a:	00078323          	sb	zero,6(a5)
    1b4e:	0076871b          	addiw	a4,a3,7
    1b52:	0ac77463          	bgeu	a4,a2,1bfa <strncpy+0x1ce>
    1b56:	000783a3          	sb	zero,7(a5)
    1b5a:	0086871b          	addiw	a4,a3,8
    1b5e:	08c77e63          	bgeu	a4,a2,1bfa <strncpy+0x1ce>
    1b62:	00078423          	sb	zero,8(a5)
    1b66:	0096871b          	addiw	a4,a3,9
    1b6a:	08c77863          	bgeu	a4,a2,1bfa <strncpy+0x1ce>
    1b6e:	000784a3          	sb	zero,9(a5)
    1b72:	00a6871b          	addiw	a4,a3,10
    1b76:	08c77263          	bgeu	a4,a2,1bfa <strncpy+0x1ce>
    1b7a:	00078523          	sb	zero,10(a5)
    1b7e:	00b6871b          	addiw	a4,a3,11
    1b82:	06c77c63          	bgeu	a4,a2,1bfa <strncpy+0x1ce>
    1b86:	000785a3          	sb	zero,11(a5)
    1b8a:	00c6871b          	addiw	a4,a3,12
    1b8e:	06c77663          	bgeu	a4,a2,1bfa <strncpy+0x1ce>
    1b92:	00078623          	sb	zero,12(a5)
    1b96:	26b5                	addiw	a3,a3,13
    1b98:	06c6f163          	bgeu	a3,a2,1bfa <strncpy+0x1ce>
    1b9c:	000786a3          	sb	zero,13(a5)
    1ba0:	8082                	ret
            ;
        if (!n || !*s)
    1ba2:	c645                	beqz	a2,1c4a <strncpy+0x21e>
    1ba4:	0005c783          	lbu	a5,0(a1)
    1ba8:	ea078be3          	beqz	a5,1a5e <strncpy+0x32>
            goto tail;
        wd = (void *)d;
        ws = (const void *)s;
        for (; n >= sizeof(size_t) && !HASZERO(*ws); n -= sizeof(size_t), ws++, wd++)
    1bac:	479d                	li	a5,7
    1bae:	02c7ff63          	bgeu	a5,a2,1bec <strncpy+0x1c0>
    1bb2:	00000897          	auipc	a7,0x0
    1bb6:	3ae8b883          	ld	a7,942(a7) # 1f60 <__clone+0x9e>
    1bba:	00000817          	auipc	a6,0x0
    1bbe:	3ae83803          	ld	a6,942(a6) # 1f68 <__clone+0xa6>
    1bc2:	431d                	li	t1,7
    1bc4:	6198                	ld	a4,0(a1)
    1bc6:	011707b3          	add	a5,a4,a7
    1bca:	fff74693          	not	a3,a4
    1bce:	8ff5                	and	a5,a5,a3
    1bd0:	0107f7b3          	and	a5,a5,a6
    1bd4:	ef81                	bnez	a5,1bec <strncpy+0x1c0>
            *wd = *ws;
    1bd6:	e118                	sd	a4,0(a0)
        for (; n >= sizeof(size_t) && !HASZERO(*ws); n -= sizeof(size_t), ws++, wd++)
    1bd8:	1661                	addi	a2,a2,-8
    1bda:	05a1                	addi	a1,a1,8
    1bdc:	0521                	addi	a0,a0,8
    1bde:	fec363e3          	bltu	t1,a2,1bc4 <strncpy+0x198>
        d = (void *)wd;
        s = (const void *)ws;
    }
    for (; n && (*d = *s); n--, s++, d++)
    1be2:	e609                	bnez	a2,1bec <strncpy+0x1c0>
    1be4:	a08d                	j	1c46 <strncpy+0x21a>
    1be6:	167d                	addi	a2,a2,-1
    1be8:	0505                	addi	a0,a0,1
    1bea:	ca01                	beqz	a2,1bfa <strncpy+0x1ce>
    1bec:	0005c783          	lbu	a5,0(a1)
    1bf0:	0585                	addi	a1,a1,1
    1bf2:	00f50023          	sb	a5,0(a0)
    1bf6:	fbe5                	bnez	a5,1be6 <strncpy+0x1ba>
        ;
tail:
    1bf8:	b59d                	j	1a5e <strncpy+0x32>
    memset(d, 0, n);
    return d;
}
    1bfa:	8082                	ret
    1bfc:	472d                	li	a4,11
    1bfe:	bdb5                	j	1a7a <strncpy+0x4e>
    1c00:	00778713          	addi	a4,a5,7
    1c04:	45ad                	li	a1,11
    1c06:	fff60693          	addi	a3,a2,-1
    1c0a:	e6b778e3          	bgeu	a4,a1,1a7a <strncpy+0x4e>
    1c0e:	b7fd                	j	1bfc <strncpy+0x1d0>
    1c10:	40a007b3          	neg	a5,a0
    1c14:	8832                	mv	a6,a2
    1c16:	8b9d                	andi	a5,a5,7
    1c18:	4681                	li	a3,0
    1c1a:	e4060be3          	beqz	a2,1a70 <strncpy+0x44>
    1c1e:	b7cd                	j	1c00 <strncpy+0x1d4>
    for (int i = 0; i < n; ++i, *(p++) = c)
    1c20:	468d                	li	a3,3
    1c22:	bd75                	j	1ade <strncpy+0xb2>
    1c24:	872a                	mv	a4,a0
    1c26:	4681                	li	a3,0
    1c28:	bd5d                	j	1ade <strncpy+0xb2>
    1c2a:	4685                	li	a3,1
    1c2c:	bd4d                	j	1ade <strncpy+0xb2>
    1c2e:	8082                	ret
    1c30:	87aa                	mv	a5,a0
    1c32:	4681                	li	a3,0
    1c34:	b5f9                	j	1b02 <strncpy+0xd6>
    1c36:	4689                	li	a3,2
    1c38:	b55d                	j	1ade <strncpy+0xb2>
    1c3a:	4691                	li	a3,4
    1c3c:	b54d                	j	1ade <strncpy+0xb2>
    1c3e:	4695                	li	a3,5
    1c40:	bd79                	j	1ade <strncpy+0xb2>
    1c42:	4699                	li	a3,6
    1c44:	bd69                	j	1ade <strncpy+0xb2>
    1c46:	8082                	ret
    1c48:	8082                	ret
    1c4a:	8082                	ret

0000000000001c4c <open>:
#include <unistd.h>

#include "syscall.h"

int open(const char *path, int flags)
{
    1c4c:	87aa                	mv	a5,a0
    1c4e:	862e                	mv	a2,a1
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
}

static inline long __syscall4(long n, long a, long b, long c, long d)
{
    register long a7 __asm__("a7") = n;
    1c50:	03800893          	li	a7,56
    register long a0 __asm__("a0") = a;
    1c54:	f9c00513          	li	a0,-100
    register long a1 __asm__("a1") = b;
    1c58:	85be                	mv	a1,a5
    register long a2 __asm__("a2") = c;
    register long a3 __asm__("a3") = d;
    1c5a:	4689                	li	a3,2
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3))
    1c5c:	00000073          	ecall
    return syscall(SYS_openat, AT_FDCWD, path, flags, O_RDWR);
}
    1c60:	2501                	sext.w	a0,a0
    1c62:	8082                	ret

0000000000001c64 <openat>:
    register long a7 __asm__("a7") = n;
    1c64:	03800893          	li	a7,56
    register long a3 __asm__("a3") = d;
    1c68:	18000693          	li	a3,384
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3))
    1c6c:	00000073          	ecall

int openat(int dirfd,const char *path, int flags)
{
    return syscall(SYS_openat, dirfd, path, flags, 0600);
}
    1c70:	2501                	sext.w	a0,a0
    1c72:	8082                	ret

0000000000001c74 <close>:
    register long a7 __asm__("a7") = n;
    1c74:	03900893          	li	a7,57
    __asm_syscall("r"(a7), "0"(a0))
    1c78:	00000073          	ecall

int close(int fd)
{
    return syscall(SYS_close, fd);
}
    1c7c:	2501                	sext.w	a0,a0
    1c7e:	8082                	ret

0000000000001c80 <read>:
    register long a7 __asm__("a7") = n;
    1c80:	03f00893          	li	a7,63
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1c84:	00000073          	ecall

ssize_t read(int fd, void *buf, size_t len)
{
    return syscall(SYS_read, fd, buf, len);
}
    1c88:	8082                	ret

0000000000001c8a <write>:
    register long a7 __asm__("a7") = n;
    1c8a:	04000893          	li	a7,64
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1c8e:	00000073          	ecall

ssize_t write(int fd, const void *buf, size_t len)
{
    return syscall(SYS_write, fd, buf, len);
}
    1c92:	8082                	ret

0000000000001c94 <getpid>:
    register long a7 __asm__("a7") = n;
    1c94:	0ac00893          	li	a7,172
    __asm_syscall("r"(a7))
    1c98:	00000073          	ecall

pid_t getpid(void)
{
    return syscall(SYS_getpid);
}
    1c9c:	2501                	sext.w	a0,a0
    1c9e:	8082                	ret

0000000000001ca0 <getppid>:
    register long a7 __asm__("a7") = n;
    1ca0:	0ad00893          	li	a7,173
    __asm_syscall("r"(a7))
    1ca4:	00000073          	ecall

pid_t getppid(void)
{
    return syscall(SYS_getppid);
}
    1ca8:	2501                	sext.w	a0,a0
    1caa:	8082                	ret

0000000000001cac <sched_yield>:
    register long a7 __asm__("a7") = n;
    1cac:	07c00893          	li	a7,124
    __asm_syscall("r"(a7))
    1cb0:	00000073          	ecall

int sched_yield(void)
{
    return syscall(SYS_sched_yield);
}
    1cb4:	2501                	sext.w	a0,a0
    1cb6:	8082                	ret

0000000000001cb8 <fork>:
    register long a7 __asm__("a7") = n;
    1cb8:	0dc00893          	li	a7,220
    register long a0 __asm__("a0") = a;
    1cbc:	4545                	li	a0,17
    register long a1 __asm__("a1") = b;
    1cbe:	4581                	li	a1,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1cc0:	00000073          	ecall

pid_t fork(void)
{
    return syscall(SYS_clone, SIGCHLD, 0);
}
    1cc4:	2501                	sext.w	a0,a0
    1cc6:	8082                	ret

0000000000001cc8 <clone>:

pid_t clone(int (*fn)(void *arg), void *arg, void *stack, size_t stack_size, unsigned long flags)
{
    1cc8:	85b2                	mv	a1,a2
    1cca:	863a                	mv	a2,a4
    if (stack)
    1ccc:	c191                	beqz	a1,1cd0 <clone+0x8>
	stack += stack_size;
    1cce:	95b6                	add	a1,a1,a3

    return __clone(fn, stack, flags, NULL, NULL, NULL);
    1cd0:	4781                	li	a5,0
    1cd2:	4701                	li	a4,0
    1cd4:	4681                	li	a3,0
    1cd6:	2601                	sext.w	a2,a2
    1cd8:	a2ed                	j	1ec2 <__clone>

0000000000001cda <exit>:
    register long a7 __asm__("a7") = n;
    1cda:	05d00893          	li	a7,93
    __asm_syscall("r"(a7), "0"(a0))
    1cde:	00000073          	ecall
    //return syscall(SYS_clone, fn, stack, flags, NULL, NULL, NULL);
}
void exit(int code)
{
    syscall(SYS_exit, code);
}
    1ce2:	8082                	ret

0000000000001ce4 <waitpid>:
    register long a7 __asm__("a7") = n;
    1ce4:	10400893          	li	a7,260
    register long a3 __asm__("a3") = d;
    1ce8:	4681                	li	a3,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3))
    1cea:	00000073          	ecall

int waitpid(int pid, int *code, int options)
{
    return syscall(SYS_wait4, pid, code, options, 0);
}
    1cee:	2501                	sext.w	a0,a0
    1cf0:	8082                	ret

0000000000001cf2 <exec>:
    register long a7 __asm__("a7") = n;
    1cf2:	0dd00893          	li	a7,221
    __asm_syscall("r"(a7), "0"(a0))
    1cf6:	00000073          	ecall

int exec(char *name)
{
    return syscall(SYS_execve, name);
}
    1cfa:	2501                	sext.w	a0,a0
    1cfc:	8082                	ret

0000000000001cfe <execve>:
    register long a7 __asm__("a7") = n;
    1cfe:	0dd00893          	li	a7,221
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1d02:	00000073          	ecall

int execve(const char *name, char *const argv[], char *const argp[])
{
    return syscall(SYS_execve, name, argv, argp);
}
    1d06:	2501                	sext.w	a0,a0
    1d08:	8082                	ret

0000000000001d0a <times>:
    register long a7 __asm__("a7") = n;
    1d0a:	09900893          	li	a7,153
    __asm_syscall("r"(a7), "0"(a0))
    1d0e:	00000073          	ecall

int times(void *mytimes)
{
	return syscall(SYS_times, mytimes);
}
    1d12:	2501                	sext.w	a0,a0
    1d14:	8082                	ret

0000000000001d16 <get_time>:

int64 get_time()
{
    1d16:	1141                	addi	sp,sp,-16
    register long a7 __asm__("a7") = n;
    1d18:	0a900893          	li	a7,169
    register long a0 __asm__("a0") = a;
    1d1c:	850a                	mv	a0,sp
    register long a1 __asm__("a1") = b;
    1d1e:	4581                	li	a1,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1d20:	00000073          	ecall
    TimeVal time;
    int err = sys_get_time(&time, 0);
    if (err == 0)
    1d24:	2501                	sext.w	a0,a0
    1d26:	ed09                	bnez	a0,1d40 <get_time+0x2a>
    {
        return ((time.sec & 0xffff) * 1000 + time.usec / 1000);
    1d28:	67a2                	ld	a5,8(sp)
    1d2a:	3e800713          	li	a4,1000
    1d2e:	00015503          	lhu	a0,0(sp)
    1d32:	02e7d7b3          	divu	a5,a5,a4
    1d36:	02e50533          	mul	a0,a0,a4
    1d3a:	953e                	add	a0,a0,a5
    }
    else
    {
        return -1;
    }
}
    1d3c:	0141                	addi	sp,sp,16
    1d3e:	8082                	ret
        return -1;
    1d40:	557d                	li	a0,-1
    1d42:	bfed                	j	1d3c <get_time+0x26>

0000000000001d44 <sys_get_time>:
    register long a7 __asm__("a7") = n;
    1d44:	0a900893          	li	a7,169
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1d48:	00000073          	ecall

int sys_get_time(TimeVal *ts, int tz)
{
    return syscall(SYS_gettimeofday, ts, tz);
}
    1d4c:	2501                	sext.w	a0,a0
    1d4e:	8082                	ret

0000000000001d50 <time>:
    register long a7 __asm__("a7") = n;
    1d50:	42600893          	li	a7,1062
    __asm_syscall("r"(a7), "0"(a0))
    1d54:	00000073          	ecall

int time(unsigned long *tloc)
{
    return syscall(SYS_time, tloc);
}
    1d58:	2501                	sext.w	a0,a0
    1d5a:	8082                	ret

0000000000001d5c <sleep>:

int sleep(unsigned long long time)
{
    1d5c:	1141                	addi	sp,sp,-16
    TimeVal tv = {.sec = time, .usec = 0};
    1d5e:	e02a                	sd	a0,0(sp)
    register long a0 __asm__("a0") = a;
    1d60:	850a                	mv	a0,sp
    1d62:	e402                	sd	zero,8(sp)
    register long a7 __asm__("a7") = n;
    1d64:	06500893          	li	a7,101
    register long a1 __asm__("a1") = b;
    1d68:	85aa                	mv	a1,a0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1d6a:	00000073          	ecall
    if (syscall(SYS_nanosleep, &tv, &tv)) return tv.sec;
    1d6e:	e501                	bnez	a0,1d76 <sleep+0x1a>
    return 0;
    1d70:	4501                	li	a0,0
}
    1d72:	0141                	addi	sp,sp,16
    1d74:	8082                	ret
    if (syscall(SYS_nanosleep, &tv, &tv)) return tv.sec;
    1d76:	4502                	lw	a0,0(sp)
}
    1d78:	0141                	addi	sp,sp,16
    1d7a:	8082                	ret

0000000000001d7c <set_priority>:
    register long a7 __asm__("a7") = n;
    1d7c:	08c00893          	li	a7,140
    __asm_syscall("r"(a7), "0"(a0))
    1d80:	00000073          	ecall

int set_priority(int prio)
{
    return syscall(SYS_setpriority, prio);
}
    1d84:	2501                	sext.w	a0,a0
    1d86:	8082                	ret

0000000000001d88 <mmap>:
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4))
}

static inline long __syscall6(long n, long a, long b, long c, long d, long e, long f)
{
    register long a7 __asm__("a7") = n;
    1d88:	0de00893          	li	a7,222
    register long a1 __asm__("a1") = b;
    register long a2 __asm__("a2") = c;
    register long a3 __asm__("a3") = d;
    register long a4 __asm__("a4") = e;
    register long a5 __asm__("a5") = f;
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5))
    1d8c:	00000073          	ecall

void *mmap(void *start, size_t len, int prot, int flags, int fd, off_t off)
{
    return syscall(SYS_mmap, start, len, prot, flags, fd, off);
}
    1d90:	8082                	ret

0000000000001d92 <munmap>:
    register long a7 __asm__("a7") = n;
    1d92:	0d700893          	li	a7,215
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1d96:	00000073          	ecall

int munmap(void *start, size_t len)
{
    return syscall(SYS_munmap, start, len);
}
    1d9a:	2501                	sext.w	a0,a0
    1d9c:	8082                	ret

0000000000001d9e <wait>:

int wait(int *code)
{
    1d9e:	85aa                	mv	a1,a0
    register long a7 __asm__("a7") = n;
    1da0:	10400893          	li	a7,260
    register long a0 __asm__("a0") = a;
    1da4:	557d                	li	a0,-1
    register long a2 __asm__("a2") = c;
    1da6:	4601                	li	a2,0
    register long a3 __asm__("a3") = d;
    1da8:	4681                	li	a3,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3))
    1daa:	00000073          	ecall
    return waitpid((int)-1, code, 0);
}
    1dae:	2501                	sext.w	a0,a0
    1db0:	8082                	ret

0000000000001db2 <spawn>:
    register long a7 __asm__("a7") = n;
    1db2:	19000893          	li	a7,400
    __asm_syscall("r"(a7), "0"(a0))
    1db6:	00000073          	ecall

int spawn(char *file)
{
    return syscall(SYS_spawn, file);
}
    1dba:	2501                	sext.w	a0,a0
    1dbc:	8082                	ret

0000000000001dbe <mailread>:
    register long a7 __asm__("a7") = n;
    1dbe:	19100893          	li	a7,401
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1dc2:	00000073          	ecall

int mailread(void *buf, int len)
{
    return syscall(SYS_mailread, buf, len);
}
    1dc6:	2501                	sext.w	a0,a0
    1dc8:	8082                	ret

0000000000001dca <mailwrite>:
    register long a7 __asm__("a7") = n;
    1dca:	19200893          	li	a7,402
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1dce:	00000073          	ecall

int mailwrite(int pid, void *buf, int len)
{
    return syscall(SYS_mailwrite, pid, buf, len);
}
    1dd2:	2501                	sext.w	a0,a0
    1dd4:	8082                	ret

0000000000001dd6 <fstat>:
    register long a7 __asm__("a7") = n;
    1dd6:	05000893          	li	a7,80
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1dda:	00000073          	ecall

int fstat(int fd, struct kstat *st)
{
    return syscall(SYS_fstat, fd, st);
}
    1dde:	2501                	sext.w	a0,a0
    1de0:	8082                	ret

0000000000001de2 <sys_linkat>:
    register long a4 __asm__("a4") = e;
    1de2:	1702                	slli	a4,a4,0x20
    register long a7 __asm__("a7") = n;
    1de4:	02500893          	li	a7,37
    register long a4 __asm__("a4") = e;
    1de8:	9301                	srli	a4,a4,0x20
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4))
    1dea:	00000073          	ecall

int sys_linkat(int olddirfd, char *oldpath, int newdirfd, char *newpath, unsigned int flags)
{
    return syscall(SYS_linkat, olddirfd, oldpath, newdirfd, newpath, flags);
}
    1dee:	2501                	sext.w	a0,a0
    1df0:	8082                	ret

0000000000001df2 <sys_unlinkat>:
    register long a2 __asm__("a2") = c;
    1df2:	1602                	slli	a2,a2,0x20
    register long a7 __asm__("a7") = n;
    1df4:	02300893          	li	a7,35
    register long a2 __asm__("a2") = c;
    1df8:	9201                	srli	a2,a2,0x20
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1dfa:	00000073          	ecall

int sys_unlinkat(int dirfd, char *path, unsigned int flags)
{
    return syscall(SYS_unlinkat, dirfd, path, flags);
}
    1dfe:	2501                	sext.w	a0,a0
    1e00:	8082                	ret

0000000000001e02 <link>:

int link(char *old_path, char *new_path)
{
    1e02:	87aa                	mv	a5,a0
    1e04:	86ae                	mv	a3,a1
    register long a7 __asm__("a7") = n;
    1e06:	02500893          	li	a7,37
    register long a0 __asm__("a0") = a;
    1e0a:	f9c00513          	li	a0,-100
    register long a1 __asm__("a1") = b;
    1e0e:	85be                	mv	a1,a5
    register long a2 __asm__("a2") = c;
    1e10:	f9c00613          	li	a2,-100
    register long a4 __asm__("a4") = e;
    1e14:	4701                	li	a4,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4))
    1e16:	00000073          	ecall
    return sys_linkat(AT_FDCWD, old_path, AT_FDCWD, new_path, 0);
}
    1e1a:	2501                	sext.w	a0,a0
    1e1c:	8082                	ret

0000000000001e1e <unlink>:

int unlink(char *path)
{
    1e1e:	85aa                	mv	a1,a0
    register long a7 __asm__("a7") = n;
    1e20:	02300893          	li	a7,35
    register long a0 __asm__("a0") = a;
    1e24:	f9c00513          	li	a0,-100
    register long a2 __asm__("a2") = c;
    1e28:	4601                	li	a2,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1e2a:	00000073          	ecall
    return sys_unlinkat(AT_FDCWD, path, 0);
}
    1e2e:	2501                	sext.w	a0,a0
    1e30:	8082                	ret

0000000000001e32 <uname>:
    register long a7 __asm__("a7") = n;
    1e32:	0a000893          	li	a7,160
    __asm_syscall("r"(a7), "0"(a0))
    1e36:	00000073          	ecall

int uname(void *buf)
{
    return syscall(SYS_uname, buf);
}
    1e3a:	2501                	sext.w	a0,a0
    1e3c:	8082                	ret

0000000000001e3e <brk>:
    register long a7 __asm__("a7") = n;
    1e3e:	0d600893          	li	a7,214
    __asm_syscall("r"(a7), "0"(a0))
    1e42:	00000073          	ecall

int brk(void *addr)
{
    return syscall(SYS_brk, addr);
}
    1e46:	2501                	sext.w	a0,a0
    1e48:	8082                	ret

0000000000001e4a <getcwd>:
    register long a7 __asm__("a7") = n;
    1e4a:	48c5                	li	a7,17
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1e4c:	00000073          	ecall

char *getcwd(char *buf, size_t size){
    return syscall(SYS_getcwd, buf, size);
}
    1e50:	8082                	ret

0000000000001e52 <chdir>:
    register long a7 __asm__("a7") = n;
    1e52:	03100893          	li	a7,49
    __asm_syscall("r"(a7), "0"(a0))
    1e56:	00000073          	ecall

int chdir(const char *path){
    return syscall(SYS_chdir, path);
}
    1e5a:	2501                	sext.w	a0,a0
    1e5c:	8082                	ret

0000000000001e5e <mkdir>:

int mkdir(const char *path, mode_t mode){
    1e5e:	862e                	mv	a2,a1
    1e60:	87aa                	mv	a5,a0
    register long a2 __asm__("a2") = c;
    1e62:	1602                	slli	a2,a2,0x20
    register long a7 __asm__("a7") = n;
    1e64:	02200893          	li	a7,34
    register long a0 __asm__("a0") = a;
    1e68:	f9c00513          	li	a0,-100
    register long a1 __asm__("a1") = b;
    1e6c:	85be                	mv	a1,a5
    register long a2 __asm__("a2") = c;
    1e6e:	9201                	srli	a2,a2,0x20
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1e70:	00000073          	ecall
    return syscall(SYS_mkdirat, AT_FDCWD, path, mode);
}
    1e74:	2501                	sext.w	a0,a0
    1e76:	8082                	ret

0000000000001e78 <getdents>:
    register long a7 __asm__("a7") = n;
    1e78:	03d00893          	li	a7,61
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1e7c:	00000073          	ecall

int getdents(int fd, struct linux_dirent64 *dirp64, unsigned long len){
    //return syscall(SYS_getdents64, fd, dirp64, len);
    return syscall(SYS_getdents64, fd, dirp64, len);
}
    1e80:	2501                	sext.w	a0,a0
    1e82:	8082                	ret

0000000000001e84 <pipe>:
    register long a7 __asm__("a7") = n;
    1e84:	03b00893          	li	a7,59
    register long a1 __asm__("a1") = b;
    1e88:	4581                	li	a1,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1e8a:	00000073          	ecall

int pipe(int fd[2]){
    return syscall(SYS_pipe2, fd, 0);
}
    1e8e:	2501                	sext.w	a0,a0
    1e90:	8082                	ret

0000000000001e92 <dup>:
    register long a7 __asm__("a7") = n;
    1e92:	48dd                	li	a7,23
    __asm_syscall("r"(a7), "0"(a0))
    1e94:	00000073          	ecall

int dup(int fd){
    return syscall(SYS_dup, fd);
}
    1e98:	2501                	sext.w	a0,a0
    1e9a:	8082                	ret

0000000000001e9c <dup2>:
    register long a7 __asm__("a7") = n;
    1e9c:	48e1                	li	a7,24
    register long a2 __asm__("a2") = c;
    1e9e:	4601                	li	a2,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1ea0:	00000073          	ecall

int dup2(int old, int new){
    return syscall(SYS_dup3, old, new, 0);
}
    1ea4:	2501                	sext.w	a0,a0
    1ea6:	8082                	ret

0000000000001ea8 <mount>:
    register long a7 __asm__("a7") = n;
    1ea8:	02800893          	li	a7,40
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4))
    1eac:	00000073          	ecall

int mount(const char *special, const char *dir, const char *fstype, unsigned long flags, const void *data)
{
        return syscall(SYS_mount, special, dir, fstype, flags, data);
}
    1eb0:	2501                	sext.w	a0,a0
    1eb2:	8082                	ret

0000000000001eb4 <umount>:
    register long a7 __asm__("a7") = n;
    1eb4:	02700893          	li	a7,39
    register long a1 __asm__("a1") = b;
    1eb8:	4581                	li	a1,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1eba:	00000073          	ecall

int umount(const char *special)
{
        return syscall(SYS_umount2, special, 0);
}
    1ebe:	2501                	sext.w	a0,a0
    1ec0:	8082                	ret

0000000000001ec2 <__clone>:

.global __clone
.type  __clone, %function
__clone:
	# Save func and arg to stack
	addi a1, a1, -16
    1ec2:	15c1                	addi	a1,a1,-16
	sd a0, 0(a1)
    1ec4:	e188                	sd	a0,0(a1)
	sd a3, 8(a1)
    1ec6:	e594                	sd	a3,8(a1)

	# Call SYS_clone
	mv a0, a2
    1ec8:	8532                	mv	a0,a2
	mv a2, a4
    1eca:	863a                	mv	a2,a4
	mv a3, a5
    1ecc:	86be                	mv	a3,a5
	mv a4, a6
    1ece:	8742                	mv	a4,a6
	li a7, 220 # SYS_clone
    1ed0:	0dc00893          	li	a7,220
	ecall
    1ed4:	00000073          	ecall

	beqz a0, 1f
    1ed8:	c111                	beqz	a0,1edc <__clone+0x1a>
	# Parent
	ret
    1eda:	8082                	ret

	# Child
1:      ld a1, 0(sp)
    1edc:	6582                	ld	a1,0(sp)
	ld a0, 8(sp)
    1ede:	6522                	ld	a0,8(sp)
	jalr a1
    1ee0:	9582                	jalr	a1

	# Exit
	li a7, 93 # SYS_exit
    1ee2:	05d00893          	li	a7,93
	ecall
    1ee6:	00000073          	ecall
