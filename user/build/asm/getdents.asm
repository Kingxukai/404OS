
/home/wxk/Desktop/404OS/oskernel2023-404os/user/build/riscv64/getdents:     file format elf64-littleriscv


Disassembly of section .text:

0000000000001000 <_start>:
.section .text.entry
.globl _start
_start:
    mv a0, sp
    1000:	850a                	mv	a0,sp
    tail __start_main
    1002:	a0d5                	j	10e6 <__start_main>

0000000000001004 <test_getdents>:
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

char buf[512];
void test_getdents(void){
    1004:	1101                	addi	sp,sp,-32
    TEST_START(__func__);
    1006:	00001517          	auipc	a0,0x1
    100a:	f2250513          	addi	a0,a0,-222 # 1f28 <__clone+0x2a>
void test_getdents(void){
    100e:	ec06                	sd	ra,24(sp)
    1010:	e822                	sd	s0,16(sp)
    1012:	e426                	sd	s1,8(sp)
    TEST_START(__func__);
    1014:	344000ef          	jal	ra,1358 <puts>
    1018:	00001517          	auipc	a0,0x1
    101c:	1c850513          	addi	a0,a0,456 # 21e0 <__func__.0>
    1020:	338000ef          	jal	ra,1358 <puts>
    1024:	00001517          	auipc	a0,0x1
    1028:	f1c50513          	addi	a0,a0,-228 # 1f40 <__clone+0x42>
    102c:	32c000ef          	jal	ra,1358 <puts>
    int fd, nread;
    struct linux_dirent64 *dirp64;
    dirp64 = buf;
    fd = open(".", O_DIRECTORY);
    1030:	002005b7          	lui	a1,0x200
    1034:	00001517          	auipc	a0,0x1
    1038:	f1c50513          	addi	a0,a0,-228 # 1f50 <__clone+0x52>
    103c:	44d000ef          	jal	ra,1c88 <open>
    // fd = open(".", O_RDONLY);
    printf("open fd:%d\n", fd);
    1040:	85aa                	mv	a1,a0
    fd = open(".", O_DIRECTORY);
    1042:	842a                	mv	s0,a0
    printf("open fd:%d\n", fd);
    1044:	00001517          	auipc	a0,0x1
    1048:	f1450513          	addi	a0,a0,-236 # 1f58 <__clone+0x5a>
    104c:	32e000ef          	jal	ra,137a <printf>

	nread = getdents(fd, dirp64, 512);
    1050:	20000613          	li	a2,512
    1054:	00001597          	auipc	a1,0x1
    1058:	f8c58593          	addi	a1,a1,-116 # 1fe0 <buf>
    105c:	8522                	mv	a0,s0
    105e:	657000ef          	jal	ra,1eb4 <getdents>
	printf("getdents fd:%d\n", nread);
    1062:	85aa                	mv	a1,a0
	nread = getdents(fd, dirp64, 512);
    1064:	84aa                	mv	s1,a0
	printf("getdents fd:%d\n", nread);
    1066:	00001517          	auipc	a0,0x1
    106a:	f0250513          	addi	a0,a0,-254 # 1f68 <__clone+0x6a>
    106e:	30c000ef          	jal	ra,137a <printf>
	assert(nread != -1);
    1072:	57fd                	li	a5,-1
    1074:	04f48a63          	beq	s1,a5,10c8 <test_getdents+0xc4>
	printf("getdents success.\n%s\n", dirp64->d_name);
    1078:	00001597          	auipc	a1,0x1
    107c:	f7b58593          	addi	a1,a1,-133 # 1ff3 <buf+0x13>
    1080:	00001517          	auipc	a0,0x1
    1084:	f1850513          	addi	a0,a0,-232 # 1f98 <__clone+0x9a>
    1088:	2f2000ef          	jal	ra,137a <printf>
	    printf(  "%s\t", d->d_name);
	    bpos += d->d_reclen;
	}
	*/

    printf("\n");
    108c:	00001517          	auipc	a0,0x1
    1090:	f0450513          	addi	a0,a0,-252 # 1f90 <__clone+0x92>
    1094:	2e6000ef          	jal	ra,137a <printf>
    close(fd);
    1098:	8522                	mv	a0,s0
    109a:	417000ef          	jal	ra,1cb0 <close>
    TEST_END(__func__);
    109e:	00001517          	auipc	a0,0x1
    10a2:	f1250513          	addi	a0,a0,-238 # 1fb0 <__clone+0xb2>
    10a6:	2b2000ef          	jal	ra,1358 <puts>
    10aa:	00001517          	auipc	a0,0x1
    10ae:	13650513          	addi	a0,a0,310 # 21e0 <__func__.0>
    10b2:	2a6000ef          	jal	ra,1358 <puts>
}
    10b6:	6442                	ld	s0,16(sp)
    10b8:	60e2                	ld	ra,24(sp)
    10ba:	64a2                	ld	s1,8(sp)
    TEST_END(__func__);
    10bc:	00001517          	auipc	a0,0x1
    10c0:	e8450513          	addi	a0,a0,-380 # 1f40 <__clone+0x42>
}
    10c4:	6105                	addi	sp,sp,32
    TEST_END(__func__);
    10c6:	ac49                	j	1358 <puts>
	assert(nread != -1);
    10c8:	00001517          	auipc	a0,0x1
    10cc:	eb050513          	addi	a0,a0,-336 # 1f78 <__clone+0x7a>
    10d0:	534000ef          	jal	ra,1604 <panic>
    10d4:	b755                	j	1078 <test_getdents+0x74>

00000000000010d6 <main>:

int main(void){
    10d6:	1141                	addi	sp,sp,-16
    10d8:	e406                	sd	ra,8(sp)
    test_getdents();
    10da:	f2bff0ef          	jal	ra,1004 <test_getdents>
    return 0;
}
    10de:	60a2                	ld	ra,8(sp)
    10e0:	4501                	li	a0,0
    10e2:	0141                	addi	sp,sp,16
    10e4:	8082                	ret

00000000000010e6 <__start_main>:
#include <unistd.h>

extern int main();

int __start_main(long *p)
{
    10e6:	85aa                	mv	a1,a0
	int argc = p[0];
	char **argv = (void *)(p+1);

	exit(main(argc, argv));
    10e8:	4108                	lw	a0,0(a0)
{
    10ea:	1141                	addi	sp,sp,-16
	exit(main(argc, argv));
    10ec:	05a1                	addi	a1,a1,8
{
    10ee:	e406                	sd	ra,8(sp)
	exit(main(argc, argv));
    10f0:	fe7ff0ef          	jal	ra,10d6 <main>
    10f4:	423000ef          	jal	ra,1d16 <exit>
	return 0;
}
    10f8:	60a2                	ld	ra,8(sp)
    10fa:	4501                	li	a0,0
    10fc:	0141                	addi	sp,sp,16
    10fe:	8082                	ret

0000000000001100 <printint.constprop.0>:
    write(f, s, l);
}

static char digits[] = "0123456789abcdef";

static void printint(int xx, int base, int sign)
    1100:	7179                	addi	sp,sp,-48
    1102:	f406                	sd	ra,40(sp)
{
    char buf[16 + 1];
    int i;
    uint x;

    if (sign && (sign = xx < 0))
    1104:	12054b63          	bltz	a0,123a <printint.constprop.0+0x13a>

    buf[16] = 0;
    i = 15;
    do
    {
        buf[i--] = digits[x % base];
    1108:	02b577bb          	remuw	a5,a0,a1
    110c:	00001617          	auipc	a2,0x1
    1110:	0e460613          	addi	a2,a2,228 # 21f0 <digits>
    buf[16] = 0;
    1114:	00010c23          	sb	zero,24(sp)
        buf[i--] = digits[x % base];
    1118:	0005871b          	sext.w	a4,a1
    111c:	1782                	slli	a5,a5,0x20
    111e:	9381                	srli	a5,a5,0x20
    1120:	97b2                	add	a5,a5,a2
    1122:	0007c783          	lbu	a5,0(a5)
    } while ((x /= base) != 0);
    1126:	02b5583b          	divuw	a6,a0,a1
        buf[i--] = digits[x % base];
    112a:	00f10ba3          	sb	a5,23(sp)
    } while ((x /= base) != 0);
    112e:	1cb56363          	bltu	a0,a1,12f4 <printint.constprop.0+0x1f4>
        buf[i--] = digits[x % base];
    1132:	45b9                	li	a1,14
    1134:	02e877bb          	remuw	a5,a6,a4
    1138:	1782                	slli	a5,a5,0x20
    113a:	9381                	srli	a5,a5,0x20
    113c:	97b2                	add	a5,a5,a2
    113e:	0007c783          	lbu	a5,0(a5)
    } while ((x /= base) != 0);
    1142:	02e856bb          	divuw	a3,a6,a4
        buf[i--] = digits[x % base];
    1146:	00f10b23          	sb	a5,22(sp)
    } while ((x /= base) != 0);
    114a:	0ce86e63          	bltu	a6,a4,1226 <printint.constprop.0+0x126>
        buf[i--] = digits[x % base];
    114e:	02e6f5bb          	remuw	a1,a3,a4
    } while ((x /= base) != 0);
    1152:	02e6d7bb          	divuw	a5,a3,a4
        buf[i--] = digits[x % base];
    1156:	1582                	slli	a1,a1,0x20
    1158:	9181                	srli	a1,a1,0x20
    115a:	95b2                	add	a1,a1,a2
    115c:	0005c583          	lbu	a1,0(a1)
    1160:	00b10aa3          	sb	a1,21(sp)
    } while ((x /= base) != 0);
    1164:	0007859b          	sext.w	a1,a5
    1168:	12e6ec63          	bltu	a3,a4,12a0 <printint.constprop.0+0x1a0>
        buf[i--] = digits[x % base];
    116c:	02e7f6bb          	remuw	a3,a5,a4
    1170:	1682                	slli	a3,a3,0x20
    1172:	9281                	srli	a3,a3,0x20
    1174:	96b2                	add	a3,a3,a2
    1176:	0006c683          	lbu	a3,0(a3)
    } while ((x /= base) != 0);
    117a:	02e7d83b          	divuw	a6,a5,a4
        buf[i--] = digits[x % base];
    117e:	00d10a23          	sb	a3,20(sp)
    } while ((x /= base) != 0);
    1182:	12e5e863          	bltu	a1,a4,12b2 <printint.constprop.0+0x1b2>
        buf[i--] = digits[x % base];
    1186:	02e876bb          	remuw	a3,a6,a4
    118a:	1682                	slli	a3,a3,0x20
    118c:	9281                	srli	a3,a3,0x20
    118e:	96b2                	add	a3,a3,a2
    1190:	0006c683          	lbu	a3,0(a3)
    } while ((x /= base) != 0);
    1194:	02e855bb          	divuw	a1,a6,a4
        buf[i--] = digits[x % base];
    1198:	00d109a3          	sb	a3,19(sp)
    } while ((x /= base) != 0);
    119c:	12e86463          	bltu	a6,a4,12c4 <printint.constprop.0+0x1c4>
        buf[i--] = digits[x % base];
    11a0:	02e5f6bb          	remuw	a3,a1,a4
    11a4:	1682                	slli	a3,a3,0x20
    11a6:	9281                	srli	a3,a3,0x20
    11a8:	96b2                	add	a3,a3,a2
    11aa:	0006c683          	lbu	a3,0(a3)
    } while ((x /= base) != 0);
    11ae:	02e5d83b          	divuw	a6,a1,a4
        buf[i--] = digits[x % base];
    11b2:	00d10923          	sb	a3,18(sp)
    } while ((x /= base) != 0);
    11b6:	0ce5ec63          	bltu	a1,a4,128e <printint.constprop.0+0x18e>
        buf[i--] = digits[x % base];
    11ba:	02e876bb          	remuw	a3,a6,a4
    11be:	1682                	slli	a3,a3,0x20
    11c0:	9281                	srli	a3,a3,0x20
    11c2:	96b2                	add	a3,a3,a2
    11c4:	0006c683          	lbu	a3,0(a3)
    } while ((x /= base) != 0);
    11c8:	02e855bb          	divuw	a1,a6,a4
        buf[i--] = digits[x % base];
    11cc:	00d108a3          	sb	a3,17(sp)
    } while ((x /= base) != 0);
    11d0:	10e86963          	bltu	a6,a4,12e2 <printint.constprop.0+0x1e2>
        buf[i--] = digits[x % base];
    11d4:	02e5f6bb          	remuw	a3,a1,a4
    11d8:	1682                	slli	a3,a3,0x20
    11da:	9281                	srli	a3,a3,0x20
    11dc:	96b2                	add	a3,a3,a2
    11de:	0006c683          	lbu	a3,0(a3)
    } while ((x /= base) != 0);
    11e2:	02e5d83b          	divuw	a6,a1,a4
        buf[i--] = digits[x % base];
    11e6:	00d10823          	sb	a3,16(sp)
    } while ((x /= base) != 0);
    11ea:	10e5e763          	bltu	a1,a4,12f8 <printint.constprop.0+0x1f8>
        buf[i--] = digits[x % base];
    11ee:	02e876bb          	remuw	a3,a6,a4
    11f2:	1682                	slli	a3,a3,0x20
    11f4:	9281                	srli	a3,a3,0x20
    11f6:	96b2                	add	a3,a3,a2
    11f8:	0006c683          	lbu	a3,0(a3)
    } while ((x /= base) != 0);
    11fc:	02e857bb          	divuw	a5,a6,a4
        buf[i--] = digits[x % base];
    1200:	00d107a3          	sb	a3,15(sp)
    } while ((x /= base) != 0);
    1204:	10e86363          	bltu	a6,a4,130a <printint.constprop.0+0x20a>
        buf[i--] = digits[x % base];
    1208:	1782                	slli	a5,a5,0x20
    120a:	9381                	srli	a5,a5,0x20
    120c:	97b2                	add	a5,a5,a2
    120e:	0007c783          	lbu	a5,0(a5)
    1212:	4599                	li	a1,6
    1214:	00f10723          	sb	a5,14(sp)

    if (sign)
    1218:	00055763          	bgez	a0,1226 <printint.constprop.0+0x126>
        buf[i--] = '-';
    121c:	02d00793          	li	a5,45
    1220:	00f106a3          	sb	a5,13(sp)
        buf[i--] = digits[x % base];
    1224:	4595                	li	a1,5
    write(f, s, l);
    1226:	003c                	addi	a5,sp,8
    1228:	4641                	li	a2,16
    122a:	9e0d                	subw	a2,a2,a1
    122c:	4505                	li	a0,1
    122e:	95be                	add	a1,a1,a5
    1230:	297000ef          	jal	ra,1cc6 <write>
    i++;
    if (i < 0)
        puts("printint error");
    out(stdout, buf + i, 16 - i);
}
    1234:	70a2                	ld	ra,40(sp)
    1236:	6145                	addi	sp,sp,48
    1238:	8082                	ret
        x = -xx;
    123a:	40a0083b          	negw	a6,a0
        buf[i--] = digits[x % base];
    123e:	02b877bb          	remuw	a5,a6,a1
    1242:	00001617          	auipc	a2,0x1
    1246:	fae60613          	addi	a2,a2,-82 # 21f0 <digits>
    buf[16] = 0;
    124a:	00010c23          	sb	zero,24(sp)
        buf[i--] = digits[x % base];
    124e:	0005871b          	sext.w	a4,a1
    1252:	1782                	slli	a5,a5,0x20
    1254:	9381                	srli	a5,a5,0x20
    1256:	97b2                	add	a5,a5,a2
    1258:	0007c783          	lbu	a5,0(a5)
    } while ((x /= base) != 0);
    125c:	02b858bb          	divuw	a7,a6,a1
        buf[i--] = digits[x % base];
    1260:	00f10ba3          	sb	a5,23(sp)
    } while ((x /= base) != 0);
    1264:	06b86963          	bltu	a6,a1,12d6 <printint.constprop.0+0x1d6>
        buf[i--] = digits[x % base];
    1268:	02e8f7bb          	remuw	a5,a7,a4
    126c:	1782                	slli	a5,a5,0x20
    126e:	9381                	srli	a5,a5,0x20
    1270:	97b2                	add	a5,a5,a2
    1272:	0007c783          	lbu	a5,0(a5)
    } while ((x /= base) != 0);
    1276:	02e8d6bb          	divuw	a3,a7,a4
        buf[i--] = digits[x % base];
    127a:	00f10b23          	sb	a5,22(sp)
    } while ((x /= base) != 0);
    127e:	ece8f8e3          	bgeu	a7,a4,114e <printint.constprop.0+0x4e>
        buf[i--] = '-';
    1282:	02d00793          	li	a5,45
    1286:	00f10aa3          	sb	a5,21(sp)
        buf[i--] = digits[x % base];
    128a:	45b5                	li	a1,13
    128c:	bf69                	j	1226 <printint.constprop.0+0x126>
    128e:	45a9                	li	a1,10
    if (sign)
    1290:	f8055be3          	bgez	a0,1226 <printint.constprop.0+0x126>
        buf[i--] = '-';
    1294:	02d00793          	li	a5,45
    1298:	00f108a3          	sb	a5,17(sp)
        buf[i--] = digits[x % base];
    129c:	45a5                	li	a1,9
    129e:	b761                	j	1226 <printint.constprop.0+0x126>
    12a0:	45b5                	li	a1,13
    if (sign)
    12a2:	f80552e3          	bgez	a0,1226 <printint.constprop.0+0x126>
        buf[i--] = '-';
    12a6:	02d00793          	li	a5,45
    12aa:	00f10a23          	sb	a5,20(sp)
        buf[i--] = digits[x % base];
    12ae:	45b1                	li	a1,12
    12b0:	bf9d                	j	1226 <printint.constprop.0+0x126>
    12b2:	45b1                	li	a1,12
    if (sign)
    12b4:	f60559e3          	bgez	a0,1226 <printint.constprop.0+0x126>
        buf[i--] = '-';
    12b8:	02d00793          	li	a5,45
    12bc:	00f109a3          	sb	a5,19(sp)
        buf[i--] = digits[x % base];
    12c0:	45ad                	li	a1,11
    12c2:	b795                	j	1226 <printint.constprop.0+0x126>
    12c4:	45ad                	li	a1,11
    if (sign)
    12c6:	f60550e3          	bgez	a0,1226 <printint.constprop.0+0x126>
        buf[i--] = '-';
    12ca:	02d00793          	li	a5,45
    12ce:	00f10923          	sb	a5,18(sp)
        buf[i--] = digits[x % base];
    12d2:	45a9                	li	a1,10
    12d4:	bf89                	j	1226 <printint.constprop.0+0x126>
        buf[i--] = '-';
    12d6:	02d00793          	li	a5,45
    12da:	00f10b23          	sb	a5,22(sp)
        buf[i--] = digits[x % base];
    12de:	45b9                	li	a1,14
    12e0:	b799                	j	1226 <printint.constprop.0+0x126>
    12e2:	45a5                	li	a1,9
    if (sign)
    12e4:	f40551e3          	bgez	a0,1226 <printint.constprop.0+0x126>
        buf[i--] = '-';
    12e8:	02d00793          	li	a5,45
    12ec:	00f10823          	sb	a5,16(sp)
        buf[i--] = digits[x % base];
    12f0:	45a1                	li	a1,8
    12f2:	bf15                	j	1226 <printint.constprop.0+0x126>
    i = 15;
    12f4:	45bd                	li	a1,15
    12f6:	bf05                	j	1226 <printint.constprop.0+0x126>
        buf[i--] = digits[x % base];
    12f8:	45a1                	li	a1,8
    if (sign)
    12fa:	f20556e3          	bgez	a0,1226 <printint.constprop.0+0x126>
        buf[i--] = '-';
    12fe:	02d00793          	li	a5,45
    1302:	00f107a3          	sb	a5,15(sp)
        buf[i--] = digits[x % base];
    1306:	459d                	li	a1,7
    1308:	bf39                	j	1226 <printint.constprop.0+0x126>
    130a:	459d                	li	a1,7
    if (sign)
    130c:	f0055de3          	bgez	a0,1226 <printint.constprop.0+0x126>
        buf[i--] = '-';
    1310:	02d00793          	li	a5,45
    1314:	00f10723          	sb	a5,14(sp)
        buf[i--] = digits[x % base];
    1318:	4599                	li	a1,6
    131a:	b731                	j	1226 <printint.constprop.0+0x126>

000000000000131c <getchar>:
{
    131c:	1101                	addi	sp,sp,-32
    read(stdin, &byte, 1);
    131e:	00f10593          	addi	a1,sp,15
    1322:	4605                	li	a2,1
    1324:	4501                	li	a0,0
{
    1326:	ec06                	sd	ra,24(sp)
    char byte = 0;
    1328:	000107a3          	sb	zero,15(sp)
    read(stdin, &byte, 1);
    132c:	191000ef          	jal	ra,1cbc <read>
}
    1330:	60e2                	ld	ra,24(sp)
    1332:	00f14503          	lbu	a0,15(sp)
    1336:	6105                	addi	sp,sp,32
    1338:	8082                	ret

000000000000133a <putchar>:
{
    133a:	1101                	addi	sp,sp,-32
    133c:	87aa                	mv	a5,a0
    return write(stdout, &byte, 1);
    133e:	00f10593          	addi	a1,sp,15
    1342:	4605                	li	a2,1
    1344:	4505                	li	a0,1
{
    1346:	ec06                	sd	ra,24(sp)
    char byte = c;
    1348:	00f107a3          	sb	a5,15(sp)
    return write(stdout, &byte, 1);
    134c:	17b000ef          	jal	ra,1cc6 <write>
}
    1350:	60e2                	ld	ra,24(sp)
    1352:	2501                	sext.w	a0,a0
    1354:	6105                	addi	sp,sp,32
    1356:	8082                	ret

0000000000001358 <puts>:
{
    1358:	1141                	addi	sp,sp,-16
    135a:	e406                	sd	ra,8(sp)
    135c:	e022                	sd	s0,0(sp)
    135e:	842a                	mv	s0,a0
    r = -(write(stdout, s, strlen(s)) < 0);
    1360:	582000ef          	jal	ra,18e2 <strlen>
    1364:	862a                	mv	a2,a0
    1366:	85a2                	mv	a1,s0
    1368:	4505                	li	a0,1
    136a:	15d000ef          	jal	ra,1cc6 <write>
}
    136e:	60a2                	ld	ra,8(sp)
    1370:	6402                	ld	s0,0(sp)
    r = -(write(stdout, s, strlen(s)) < 0);
    1372:	957d                	srai	a0,a0,0x3f
    return r;
    1374:	2501                	sext.w	a0,a0
}
    1376:	0141                	addi	sp,sp,16
    1378:	8082                	ret

000000000000137a <printf>:
    out(stdout, buf, i);
}

// Print to the console. only understands %d, %x, %p, %s.
void printf(const char *fmt, ...)
{
    137a:	7131                	addi	sp,sp,-192
    137c:	f53e                	sd	a5,168(sp)
    va_list ap;
    int cnt = 0, l = 0;
    char *a, *z, *s = (char *)fmt, str;
    int f = stdout;

    va_start(ap, fmt);
    137e:	013c                	addi	a5,sp,136
{
    1380:	f0ca                	sd	s2,96(sp)
    1382:	ecce                	sd	s3,88(sp)
    1384:	e8d2                	sd	s4,80(sp)
    1386:	e4d6                	sd	s5,72(sp)
    1388:	e0da                	sd	s6,64(sp)
    138a:	fc5e                	sd	s7,56(sp)
    138c:	fc86                	sd	ra,120(sp)
    138e:	f8a2                	sd	s0,112(sp)
    1390:	f4a6                	sd	s1,104(sp)
    1392:	e52e                	sd	a1,136(sp)
    1394:	e932                	sd	a2,144(sp)
    1396:	ed36                	sd	a3,152(sp)
    1398:	f13a                	sd	a4,160(sp)
    139a:	f942                	sd	a6,176(sp)
    139c:	fd46                	sd	a7,184(sp)
    va_start(ap, fmt);
    139e:	e03e                	sd	a5,0(sp)
    for (;;)
    {
        if (!*s)
            break;
        for (a = s; *s && *s != '%'; s++)
    13a0:	02500913          	li	s2,37
        out(f, a, l);
        if (l)
            continue;
        if (s[1] == 0)
            break;
        switch (s[1])
    13a4:	07300a13          	li	s4,115
        case 'p':
            printptr(va_arg(ap, uint64));
            break;
        case 's':
            if ((a = va_arg(ap, char *)) == 0)
                a = "(null)";
    13a8:	00001b97          	auipc	s7,0x1
    13ac:	c18b8b93          	addi	s7,s7,-1000 # 1fc0 <__clone+0xc2>
        switch (s[1])
    13b0:	07800a93          	li	s5,120
    13b4:	06400b13          	li	s6,100
        buf[i++] = digits[x >> (sizeof(uint64) * 8 - 4)];
    13b8:	00001997          	auipc	s3,0x1
    13bc:	e3898993          	addi	s3,s3,-456 # 21f0 <digits>
        if (!*s)
    13c0:	00054783          	lbu	a5,0(a0)
    13c4:	16078c63          	beqz	a5,153c <printf+0x1c2>
    13c8:	862a                	mv	a2,a0
        for (a = s; *s && *s != '%'; s++)
    13ca:	19278463          	beq	a5,s2,1552 <printf+0x1d8>
    13ce:	00164783          	lbu	a5,1(a2)
    13d2:	0605                	addi	a2,a2,1
    13d4:	fbfd                	bnez	a5,13ca <printf+0x50>
    13d6:	84b2                	mv	s1,a2
        l = z - a;
    13d8:	40a6043b          	subw	s0,a2,a0
    write(f, s, l);
    13dc:	85aa                	mv	a1,a0
    13de:	8622                	mv	a2,s0
    13e0:	4505                	li	a0,1
    13e2:	0e5000ef          	jal	ra,1cc6 <write>
        if (l)
    13e6:	18041f63          	bnez	s0,1584 <printf+0x20a>
        if (s[1] == 0)
    13ea:	0014c783          	lbu	a5,1(s1)
    13ee:	14078763          	beqz	a5,153c <printf+0x1c2>
        switch (s[1])
    13f2:	1d478163          	beq	a5,s4,15b4 <printf+0x23a>
    13f6:	18fa6963          	bltu	s4,a5,1588 <printf+0x20e>
    13fa:	1b678363          	beq	a5,s6,15a0 <printf+0x226>
    13fe:	07000713          	li	a4,112
    1402:	1ce79c63          	bne	a5,a4,15da <printf+0x260>
            printptr(va_arg(ap, uint64));
    1406:	6702                	ld	a4,0(sp)
    buf[i++] = '0';
    1408:	03000793          	li	a5,48
    140c:	00f10423          	sb	a5,8(sp)
            printptr(va_arg(ap, uint64));
    1410:	631c                	ld	a5,0(a4)
    1412:	0721                	addi	a4,a4,8
    1414:	e03a                	sd	a4,0(sp)
    for (j = 0; j < (sizeof(uint64) * 2); j++, x <<= 4)
    1416:	00479f93          	slli	t6,a5,0x4
    141a:	00879f13          	slli	t5,a5,0x8
    141e:	00c79e93          	slli	t4,a5,0xc
    1422:	01079e13          	slli	t3,a5,0x10
    1426:	01479313          	slli	t1,a5,0x14
    142a:	01879893          	slli	a7,a5,0x18
    142e:	01c79713          	slli	a4,a5,0x1c
    1432:	02479813          	slli	a6,a5,0x24
    1436:	02879513          	slli	a0,a5,0x28
    143a:	02c79593          	slli	a1,a5,0x2c
    143e:	03079613          	slli	a2,a5,0x30
        buf[i++] = digits[x >> (sizeof(uint64) * 8 - 4)];
    1442:	03c7d293          	srli	t0,a5,0x3c
    1446:	01c7d39b          	srliw	t2,a5,0x1c
    for (j = 0; j < (sizeof(uint64) * 2); j++, x <<= 4)
    144a:	03479693          	slli	a3,a5,0x34
        buf[i++] = digits[x >> (sizeof(uint64) * 8 - 4)];
    144e:	03cfdf93          	srli	t6,t6,0x3c
    1452:	03cf5f13          	srli	t5,t5,0x3c
    1456:	03cede93          	srli	t4,t4,0x3c
    145a:	03ce5e13          	srli	t3,t3,0x3c
    145e:	03c35313          	srli	t1,t1,0x3c
    1462:	03c8d893          	srli	a7,a7,0x3c
    1466:	9371                	srli	a4,a4,0x3c
    1468:	03c85813          	srli	a6,a6,0x3c
    146c:	9171                	srli	a0,a0,0x3c
    146e:	91f1                	srli	a1,a1,0x3c
    1470:	9271                	srli	a2,a2,0x3c
    1472:	974e                	add	a4,a4,s3
    1474:	92f1                	srli	a3,a3,0x3c
    1476:	92ce                	add	t0,t0,s3
    1478:	9fce                	add	t6,t6,s3
    147a:	9f4e                	add	t5,t5,s3
    147c:	9ece                	add	t4,t4,s3
    147e:	9e4e                	add	t3,t3,s3
    1480:	934e                	add	t1,t1,s3
    1482:	98ce                	add	a7,a7,s3
    1484:	93ce                	add	t2,t2,s3
    1486:	984e                	add	a6,a6,s3
    1488:	954e                	add	a0,a0,s3
    148a:	95ce                	add	a1,a1,s3
    148c:	964e                	add	a2,a2,s3
    148e:	0002c283          	lbu	t0,0(t0)
    1492:	000fcf83          	lbu	t6,0(t6)
    1496:	000f4f03          	lbu	t5,0(t5)
    149a:	000ece83          	lbu	t4,0(t4)
    149e:	000e4e03          	lbu	t3,0(t3)
    14a2:	00034303          	lbu	t1,0(t1)
    14a6:	0008c883          	lbu	a7,0(a7)
    14aa:	00074403          	lbu	s0,0(a4)
    14ae:	0003c383          	lbu	t2,0(t2)
    14b2:	00084803          	lbu	a6,0(a6)
    14b6:	00054503          	lbu	a0,0(a0)
    14ba:	0005c583          	lbu	a1,0(a1)
    14be:	00064603          	lbu	a2,0(a2)
    14c2:	00d98733          	add	a4,s3,a3
    14c6:	00074683          	lbu	a3,0(a4)
    for (j = 0; j < (sizeof(uint64) * 2); j++, x <<= 4)
    14ca:	03879713          	slli	a4,a5,0x38
        buf[i++] = digits[x >> (sizeof(uint64) * 8 - 4)];
    14ce:	9371                	srli	a4,a4,0x3c
    14d0:	8bbd                	andi	a5,a5,15
    14d2:	00510523          	sb	t0,10(sp)
    14d6:	01f105a3          	sb	t6,11(sp)
    14da:	01e10623          	sb	t5,12(sp)
    14de:	01d106a3          	sb	t4,13(sp)
    14e2:	01c10723          	sb	t3,14(sp)
    14e6:	006107a3          	sb	t1,15(sp)
    14ea:	01110823          	sb	a7,16(sp)
    14ee:	00710923          	sb	t2,18(sp)
    14f2:	010109a3          	sb	a6,19(sp)
    14f6:	00a10a23          	sb	a0,20(sp)
    14fa:	00b10aa3          	sb	a1,21(sp)
    14fe:	00c10b23          	sb	a2,22(sp)
    buf[i++] = 'x';
    1502:	015104a3          	sb	s5,9(sp)
        buf[i++] = digits[x >> (sizeof(uint64) * 8 - 4)];
    1506:	008108a3          	sb	s0,17(sp)
    150a:	974e                	add	a4,a4,s3
    150c:	97ce                	add	a5,a5,s3
    150e:	00d10ba3          	sb	a3,23(sp)
    1512:	00074703          	lbu	a4,0(a4)
    1516:	0007c783          	lbu	a5,0(a5)
    write(f, s, l);
    151a:	4649                	li	a2,18
    151c:	002c                	addi	a1,sp,8
    151e:	4505                	li	a0,1
        buf[i++] = digits[x >> (sizeof(uint64) * 8 - 4)];
    1520:	00e10c23          	sb	a4,24(sp)
    1524:	00f10ca3          	sb	a5,25(sp)
    buf[i] = 0;
    1528:	00010d23          	sb	zero,26(sp)
    write(f, s, l);
    152c:	79a000ef          	jal	ra,1cc6 <write>
            // Print unknown % sequence to draw attention.
            putchar('%');
            putchar(s[1]);
            break;
        }
        s += 2;
    1530:	00248513          	addi	a0,s1,2
        if (!*s)
    1534:	00054783          	lbu	a5,0(a0)
    1538:	e80798e3          	bnez	a5,13c8 <printf+0x4e>
    }
    va_end(ap);
}
    153c:	70e6                	ld	ra,120(sp)
    153e:	7446                	ld	s0,112(sp)
    1540:	74a6                	ld	s1,104(sp)
    1542:	7906                	ld	s2,96(sp)
    1544:	69e6                	ld	s3,88(sp)
    1546:	6a46                	ld	s4,80(sp)
    1548:	6aa6                	ld	s5,72(sp)
    154a:	6b06                	ld	s6,64(sp)
    154c:	7be2                	ld	s7,56(sp)
    154e:	6129                	addi	sp,sp,192
    1550:	8082                	ret
        for (z = s; s[0] == '%' && s[1] == '%'; z++, s += 2)
    1552:	00064783          	lbu	a5,0(a2)
    1556:	84b2                	mv	s1,a2
    1558:	01278963          	beq	a5,s2,156a <printf+0x1f0>
    155c:	bdb5                	j	13d8 <printf+0x5e>
    155e:	0024c783          	lbu	a5,2(s1)
    1562:	0605                	addi	a2,a2,1
    1564:	0489                	addi	s1,s1,2
    1566:	e72799e3          	bne	a5,s2,13d8 <printf+0x5e>
    156a:	0014c783          	lbu	a5,1(s1)
    156e:	ff2788e3          	beq	a5,s2,155e <printf+0x1e4>
        l = z - a;
    1572:	40a6043b          	subw	s0,a2,a0
    write(f, s, l);
    1576:	85aa                	mv	a1,a0
    1578:	8622                	mv	a2,s0
    157a:	4505                	li	a0,1
    157c:	74a000ef          	jal	ra,1cc6 <write>
        if (l)
    1580:	e60405e3          	beqz	s0,13ea <printf+0x70>
    1584:	8526                	mv	a0,s1
    1586:	bd2d                	j	13c0 <printf+0x46>
        switch (s[1])
    1588:	05579963          	bne	a5,s5,15da <printf+0x260>
            printint(va_arg(ap, int), 16, 1);
    158c:	6782                	ld	a5,0(sp)
    158e:	45c1                	li	a1,16
    1590:	4388                	lw	a0,0(a5)
    1592:	07a1                	addi	a5,a5,8
    1594:	e03e                	sd	a5,0(sp)
    1596:	b6bff0ef          	jal	ra,1100 <printint.constprop.0>
        s += 2;
    159a:	00248513          	addi	a0,s1,2
    159e:	bf59                	j	1534 <printf+0x1ba>
            printint(va_arg(ap, int), 10, 1);
    15a0:	6782                	ld	a5,0(sp)
    15a2:	45a9                	li	a1,10
    15a4:	4388                	lw	a0,0(a5)
    15a6:	07a1                	addi	a5,a5,8
    15a8:	e03e                	sd	a5,0(sp)
    15aa:	b57ff0ef          	jal	ra,1100 <printint.constprop.0>
        s += 2;
    15ae:	00248513          	addi	a0,s1,2
    15b2:	b749                	j	1534 <printf+0x1ba>
            if ((a = va_arg(ap, char *)) == 0)
    15b4:	6782                	ld	a5,0(sp)
    15b6:	6380                	ld	s0,0(a5)
    15b8:	07a1                	addi	a5,a5,8
    15ba:	e03e                	sd	a5,0(sp)
    15bc:	c031                	beqz	s0,1600 <printf+0x286>
            l = strnlen(a, 200);
    15be:	0c800593          	li	a1,200
    15c2:	8522                	mv	a0,s0
    15c4:	40a000ef          	jal	ra,19ce <strnlen>
    write(f, s, l);
    15c8:	0005061b          	sext.w	a2,a0
    15cc:	85a2                	mv	a1,s0
    15ce:	4505                	li	a0,1
    15d0:	6f6000ef          	jal	ra,1cc6 <write>
        s += 2;
    15d4:	00248513          	addi	a0,s1,2
    15d8:	bfb1                	j	1534 <printf+0x1ba>
    return write(stdout, &byte, 1);
    15da:	4605                	li	a2,1
    15dc:	002c                	addi	a1,sp,8
    15de:	4505                	li	a0,1
    char byte = c;
    15e0:	01210423          	sb	s2,8(sp)
    return write(stdout, &byte, 1);
    15e4:	6e2000ef          	jal	ra,1cc6 <write>
    char byte = c;
    15e8:	0014c783          	lbu	a5,1(s1)
    return write(stdout, &byte, 1);
    15ec:	4605                	li	a2,1
    15ee:	002c                	addi	a1,sp,8
    15f0:	4505                	li	a0,1
    char byte = c;
    15f2:	00f10423          	sb	a5,8(sp)
    return write(stdout, &byte, 1);
    15f6:	6d0000ef          	jal	ra,1cc6 <write>
        s += 2;
    15fa:	00248513          	addi	a0,s1,2
    15fe:	bf1d                	j	1534 <printf+0x1ba>
                a = "(null)";
    1600:	845e                	mv	s0,s7
    1602:	bf75                	j	15be <printf+0x244>

0000000000001604 <panic>:
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void panic(char *m)
{
    1604:	1141                	addi	sp,sp,-16
    1606:	e406                	sd	ra,8(sp)
    puts(m);
    1608:	d51ff0ef          	jal	ra,1358 <puts>
    exit(-100);
}
    160c:	60a2                	ld	ra,8(sp)
    exit(-100);
    160e:	f9c00513          	li	a0,-100
}
    1612:	0141                	addi	sp,sp,16
    exit(-100);
    1614:	a709                	j	1d16 <exit>

0000000000001616 <isspace>:
#define HIGHS (ONES * (UCHAR_MAX / 2 + 1))
#define HASZERO(x) (((x)-ONES) & ~(x)&HIGHS)

int isspace(int c)
{
    return c == ' ' || (unsigned)c - '\t' < 5;
    1616:	02000793          	li	a5,32
    161a:	00f50663          	beq	a0,a5,1626 <isspace+0x10>
    161e:	355d                	addiw	a0,a0,-9
    1620:	00553513          	sltiu	a0,a0,5
    1624:	8082                	ret
    1626:	4505                	li	a0,1
}
    1628:	8082                	ret

000000000000162a <isdigit>:

int isdigit(int c)
{
    return (unsigned)c - '0' < 10;
    162a:	fd05051b          	addiw	a0,a0,-48
}
    162e:	00a53513          	sltiu	a0,a0,10
    1632:	8082                	ret

0000000000001634 <atoi>:
    return c == ' ' || (unsigned)c - '\t' < 5;
    1634:	02000613          	li	a2,32
    1638:	4591                	li	a1,4

int atoi(const char *s)
{
    int n = 0, neg = 0;
    while (isspace(*s))
    163a:	00054703          	lbu	a4,0(a0)
    return c == ' ' || (unsigned)c - '\t' < 5;
    163e:	ff77069b          	addiw	a3,a4,-9
    1642:	04c70d63          	beq	a4,a2,169c <atoi+0x68>
    1646:	0007079b          	sext.w	a5,a4
    164a:	04d5f963          	bgeu	a1,a3,169c <atoi+0x68>
        s++;
    switch (*s)
    164e:	02b00693          	li	a3,43
    1652:	04d70a63          	beq	a4,a3,16a6 <atoi+0x72>
    1656:	02d00693          	li	a3,45
    165a:	06d70463          	beq	a4,a3,16c2 <atoi+0x8e>
        neg = 1;
    case '+':
        s++;
    }
    /* Compute n as a negative number to avoid overflow on INT_MIN */
    while (isdigit(*s))
    165e:	fd07859b          	addiw	a1,a5,-48
    1662:	4625                	li	a2,9
    1664:	873e                	mv	a4,a5
    1666:	86aa                	mv	a3,a0
    int n = 0, neg = 0;
    1668:	4e01                	li	t3,0
    while (isdigit(*s))
    166a:	04b66a63          	bltu	a2,a1,16be <atoi+0x8a>
    int n = 0, neg = 0;
    166e:	4501                	li	a0,0
    while (isdigit(*s))
    1670:	4825                	li	a6,9
    1672:	0016c603          	lbu	a2,1(a3)
        n = 10 * n - (*s++ - '0');
    1676:	0025179b          	slliw	a5,a0,0x2
    167a:	9d3d                	addw	a0,a0,a5
    167c:	fd07031b          	addiw	t1,a4,-48
    1680:	0015189b          	slliw	a7,a0,0x1
    while (isdigit(*s))
    1684:	fd06059b          	addiw	a1,a2,-48
        n = 10 * n - (*s++ - '0');
    1688:	0685                	addi	a3,a3,1
    168a:	4068853b          	subw	a0,a7,t1
    while (isdigit(*s))
    168e:	0006071b          	sext.w	a4,a2
    1692:	feb870e3          	bgeu	a6,a1,1672 <atoi+0x3e>
    return neg ? n : -n;
    1696:	000e0563          	beqz	t3,16a0 <atoi+0x6c>
}
    169a:	8082                	ret
        s++;
    169c:	0505                	addi	a0,a0,1
    169e:	bf71                	j	163a <atoi+0x6>
    return neg ? n : -n;
    16a0:	4113053b          	subw	a0,t1,a7
    16a4:	8082                	ret
    while (isdigit(*s))
    16a6:	00154783          	lbu	a5,1(a0)
    16aa:	4625                	li	a2,9
        s++;
    16ac:	00150693          	addi	a3,a0,1
    while (isdigit(*s))
    16b0:	fd07859b          	addiw	a1,a5,-48
    16b4:	0007871b          	sext.w	a4,a5
    int n = 0, neg = 0;
    16b8:	4e01                	li	t3,0
    while (isdigit(*s))
    16ba:	fab67ae3          	bgeu	a2,a1,166e <atoi+0x3a>
    16be:	4501                	li	a0,0
}
    16c0:	8082                	ret
    while (isdigit(*s))
    16c2:	00154783          	lbu	a5,1(a0)
    16c6:	4625                	li	a2,9
        s++;
    16c8:	00150693          	addi	a3,a0,1
    while (isdigit(*s))
    16cc:	fd07859b          	addiw	a1,a5,-48
    16d0:	0007871b          	sext.w	a4,a5
    16d4:	feb665e3          	bltu	a2,a1,16be <atoi+0x8a>
        neg = 1;
    16d8:	4e05                	li	t3,1
    16da:	bf51                	j	166e <atoi+0x3a>

00000000000016dc <memset>:

void *memset(void *dest, int c, size_t n)
{
    char *p = dest;
    for (int i = 0; i < n; ++i, *(p++) = c)
    16dc:	16060d63          	beqz	a2,1856 <memset+0x17a>
    16e0:	40a007b3          	neg	a5,a0
    16e4:	8b9d                	andi	a5,a5,7
    16e6:	00778713          	addi	a4,a5,7
    16ea:	482d                	li	a6,11
    16ec:	0ff5f593          	andi	a1,a1,255
    16f0:	fff60693          	addi	a3,a2,-1
    16f4:	17076263          	bltu	a4,a6,1858 <memset+0x17c>
    16f8:	16e6ea63          	bltu	a3,a4,186c <memset+0x190>
    16fc:	16078563          	beqz	a5,1866 <memset+0x18a>
    1700:	00b50023          	sb	a1,0(a0)
    1704:	4705                	li	a4,1
    1706:	00150e93          	addi	t4,a0,1
    170a:	14e78c63          	beq	a5,a4,1862 <memset+0x186>
    170e:	00b500a3          	sb	a1,1(a0)
    1712:	4709                	li	a4,2
    1714:	00250e93          	addi	t4,a0,2
    1718:	14e78d63          	beq	a5,a4,1872 <memset+0x196>
    171c:	00b50123          	sb	a1,2(a0)
    1720:	470d                	li	a4,3
    1722:	00350e93          	addi	t4,a0,3
    1726:	12e78b63          	beq	a5,a4,185c <memset+0x180>
    172a:	00b501a3          	sb	a1,3(a0)
    172e:	4711                	li	a4,4
    1730:	00450e93          	addi	t4,a0,4
    1734:	14e78163          	beq	a5,a4,1876 <memset+0x19a>
    1738:	00b50223          	sb	a1,4(a0)
    173c:	4715                	li	a4,5
    173e:	00550e93          	addi	t4,a0,5
    1742:	12e78c63          	beq	a5,a4,187a <memset+0x19e>
    1746:	00b502a3          	sb	a1,5(a0)
    174a:	471d                	li	a4,7
    174c:	00650e93          	addi	t4,a0,6
    1750:	12e79763          	bne	a5,a4,187e <memset+0x1a2>
    1754:	00750e93          	addi	t4,a0,7
    1758:	00b50323          	sb	a1,6(a0)
    175c:	4f1d                	li	t5,7
    175e:	00859713          	slli	a4,a1,0x8
    1762:	8f4d                	or	a4,a4,a1
    1764:	01059e13          	slli	t3,a1,0x10
    1768:	01c76e33          	or	t3,a4,t3
    176c:	01859313          	slli	t1,a1,0x18
    1770:	006e6333          	or	t1,t3,t1
    1774:	02059893          	slli	a7,a1,0x20
    1778:	011368b3          	or	a7,t1,a7
    177c:	02859813          	slli	a6,a1,0x28
    1780:	40f60333          	sub	t1,a2,a5
    1784:	0108e833          	or	a6,a7,a6
    1788:	03059693          	slli	a3,a1,0x30
    178c:	00d866b3          	or	a3,a6,a3
    1790:	03859713          	slli	a4,a1,0x38
    1794:	97aa                	add	a5,a5,a0
    1796:	ff837813          	andi	a6,t1,-8
    179a:	8f55                	or	a4,a4,a3
    179c:	00f806b3          	add	a3,a6,a5
    17a0:	e398                	sd	a4,0(a5)
    17a2:	07a1                	addi	a5,a5,8
    17a4:	fed79ee3          	bne	a5,a3,17a0 <memset+0xc4>
    17a8:	ff837693          	andi	a3,t1,-8
    17ac:	00de87b3          	add	a5,t4,a3
    17b0:	01e6873b          	addw	a4,a3,t5
    17b4:	0ad30663          	beq	t1,a3,1860 <memset+0x184>
    17b8:	00b78023          	sb	a1,0(a5)
    17bc:	0017069b          	addiw	a3,a4,1
    17c0:	08c6fb63          	bgeu	a3,a2,1856 <memset+0x17a>
    17c4:	00b780a3          	sb	a1,1(a5)
    17c8:	0027069b          	addiw	a3,a4,2
    17cc:	08c6f563          	bgeu	a3,a2,1856 <memset+0x17a>
    17d0:	00b78123          	sb	a1,2(a5)
    17d4:	0037069b          	addiw	a3,a4,3
    17d8:	06c6ff63          	bgeu	a3,a2,1856 <memset+0x17a>
    17dc:	00b781a3          	sb	a1,3(a5)
    17e0:	0047069b          	addiw	a3,a4,4
    17e4:	06c6f963          	bgeu	a3,a2,1856 <memset+0x17a>
    17e8:	00b78223          	sb	a1,4(a5)
    17ec:	0057069b          	addiw	a3,a4,5
    17f0:	06c6f363          	bgeu	a3,a2,1856 <memset+0x17a>
    17f4:	00b782a3          	sb	a1,5(a5)
    17f8:	0067069b          	addiw	a3,a4,6
    17fc:	04c6fd63          	bgeu	a3,a2,1856 <memset+0x17a>
    1800:	00b78323          	sb	a1,6(a5)
    1804:	0077069b          	addiw	a3,a4,7
    1808:	04c6f763          	bgeu	a3,a2,1856 <memset+0x17a>
    180c:	00b783a3          	sb	a1,7(a5)
    1810:	0087069b          	addiw	a3,a4,8
    1814:	04c6f163          	bgeu	a3,a2,1856 <memset+0x17a>
    1818:	00b78423          	sb	a1,8(a5)
    181c:	0097069b          	addiw	a3,a4,9
    1820:	02c6fb63          	bgeu	a3,a2,1856 <memset+0x17a>
    1824:	00b784a3          	sb	a1,9(a5)
    1828:	00a7069b          	addiw	a3,a4,10
    182c:	02c6f563          	bgeu	a3,a2,1856 <memset+0x17a>
    1830:	00b78523          	sb	a1,10(a5)
    1834:	00b7069b          	addiw	a3,a4,11
    1838:	00c6ff63          	bgeu	a3,a2,1856 <memset+0x17a>
    183c:	00b785a3          	sb	a1,11(a5)
    1840:	00c7069b          	addiw	a3,a4,12
    1844:	00c6f963          	bgeu	a3,a2,1856 <memset+0x17a>
    1848:	00b78623          	sb	a1,12(a5)
    184c:	2735                	addiw	a4,a4,13
    184e:	00c77463          	bgeu	a4,a2,1856 <memset+0x17a>
    1852:	00b786a3          	sb	a1,13(a5)
        ;
    return dest;
}
    1856:	8082                	ret
    1858:	472d                	li	a4,11
    185a:	bd79                	j	16f8 <memset+0x1c>
    for (int i = 0; i < n; ++i, *(p++) = c)
    185c:	4f0d                	li	t5,3
    185e:	b701                	j	175e <memset+0x82>
    1860:	8082                	ret
    1862:	4f05                	li	t5,1
    1864:	bded                	j	175e <memset+0x82>
    1866:	8eaa                	mv	t4,a0
    1868:	4f01                	li	t5,0
    186a:	bdd5                	j	175e <memset+0x82>
    186c:	87aa                	mv	a5,a0
    186e:	4701                	li	a4,0
    1870:	b7a1                	j	17b8 <memset+0xdc>
    1872:	4f09                	li	t5,2
    1874:	b5ed                	j	175e <memset+0x82>
    1876:	4f11                	li	t5,4
    1878:	b5dd                	j	175e <memset+0x82>
    187a:	4f15                	li	t5,5
    187c:	b5cd                	j	175e <memset+0x82>
    187e:	4f19                	li	t5,6
    1880:	bdf9                	j	175e <memset+0x82>

0000000000001882 <strcmp>:

int strcmp(const char *l, const char *r)
{
    for (; *l == *r && *l; l++, r++)
    1882:	00054783          	lbu	a5,0(a0)
    1886:	0005c703          	lbu	a4,0(a1)
    188a:	00e79863          	bne	a5,a4,189a <strcmp+0x18>
    188e:	0505                	addi	a0,a0,1
    1890:	0585                	addi	a1,a1,1
    1892:	fbe5                	bnez	a5,1882 <strcmp>
    1894:	4501                	li	a0,0
        ;
    return *(unsigned char *)l - *(unsigned char *)r;
}
    1896:	9d19                	subw	a0,a0,a4
    1898:	8082                	ret
    return *(unsigned char *)l - *(unsigned char *)r;
    189a:	0007851b          	sext.w	a0,a5
    189e:	bfe5                	j	1896 <strcmp+0x14>

00000000000018a0 <strncmp>:

int strncmp(const char *_l, const char *_r, size_t n)
{
    const unsigned char *l = (void *)_l, *r = (void *)_r;
    if (!n--)
    18a0:	ce05                	beqz	a2,18d8 <strncmp+0x38>
        return 0;
    for (; *l && *r && n && *l == *r; l++, r++, n--)
    18a2:	00054703          	lbu	a4,0(a0)
    18a6:	0005c783          	lbu	a5,0(a1)
    18aa:	cb0d                	beqz	a4,18dc <strncmp+0x3c>
    if (!n--)
    18ac:	167d                	addi	a2,a2,-1
    18ae:	00c506b3          	add	a3,a0,a2
    18b2:	a819                	j	18c8 <strncmp+0x28>
    for (; *l && *r && n && *l == *r; l++, r++, n--)
    18b4:	00a68e63          	beq	a3,a0,18d0 <strncmp+0x30>
    18b8:	0505                	addi	a0,a0,1
    18ba:	00e79b63          	bne	a5,a4,18d0 <strncmp+0x30>
    18be:	00054703          	lbu	a4,0(a0)
        ;
    return *l - *r;
    18c2:	0005c783          	lbu	a5,0(a1)
    for (; *l && *r && n && *l == *r; l++, r++, n--)
    18c6:	cb19                	beqz	a4,18dc <strncmp+0x3c>
    18c8:	0005c783          	lbu	a5,0(a1)
    18cc:	0585                	addi	a1,a1,1
    18ce:	f3fd                	bnez	a5,18b4 <strncmp+0x14>
    return *l - *r;
    18d0:	0007051b          	sext.w	a0,a4
    18d4:	9d1d                	subw	a0,a0,a5
    18d6:	8082                	ret
        return 0;
    18d8:	4501                	li	a0,0
}
    18da:	8082                	ret
    18dc:	4501                	li	a0,0
    return *l - *r;
    18de:	9d1d                	subw	a0,a0,a5
    18e0:	8082                	ret

00000000000018e2 <strlen>:
size_t strlen(const char *s)
{
    const char *a = s;
    typedef size_t __attribute__((__may_alias__)) word;
    const word *w;
    for (; (uintptr_t)s % SS; s++)
    18e2:	00757793          	andi	a5,a0,7
    18e6:	cf89                	beqz	a5,1900 <strlen+0x1e>
    18e8:	87aa                	mv	a5,a0
    18ea:	a029                	j	18f4 <strlen+0x12>
    18ec:	0785                	addi	a5,a5,1
    18ee:	0077f713          	andi	a4,a5,7
    18f2:	cb01                	beqz	a4,1902 <strlen+0x20>
        if (!*s)
    18f4:	0007c703          	lbu	a4,0(a5)
    18f8:	fb75                	bnez	a4,18ec <strlen+0xa>
    for (w = (const void *)s; !HASZERO(*w); w++)
        ;
    s = (const void *)w;
    for (; *s; s++)
        ;
    return s - a;
    18fa:	40a78533          	sub	a0,a5,a0
}
    18fe:	8082                	ret
    for (; (uintptr_t)s % SS; s++)
    1900:	87aa                	mv	a5,a0
    for (w = (const void *)s; !HASZERO(*w); w++)
    1902:	6394                	ld	a3,0(a5)
    1904:	00000597          	auipc	a1,0x0
    1908:	6c45b583          	ld	a1,1732(a1) # 1fc8 <__clone+0xca>
    190c:	00000617          	auipc	a2,0x0
    1910:	6c463603          	ld	a2,1732(a2) # 1fd0 <__clone+0xd2>
    1914:	a019                	j	191a <strlen+0x38>
    1916:	6794                	ld	a3,8(a5)
    1918:	07a1                	addi	a5,a5,8
    191a:	00b68733          	add	a4,a3,a1
    191e:	fff6c693          	not	a3,a3
    1922:	8f75                	and	a4,a4,a3
    1924:	8f71                	and	a4,a4,a2
    1926:	db65                	beqz	a4,1916 <strlen+0x34>
    for (; *s; s++)
    1928:	0007c703          	lbu	a4,0(a5)
    192c:	d779                	beqz	a4,18fa <strlen+0x18>
    192e:	0017c703          	lbu	a4,1(a5)
    1932:	0785                	addi	a5,a5,1
    1934:	d379                	beqz	a4,18fa <strlen+0x18>
    1936:	0017c703          	lbu	a4,1(a5)
    193a:	0785                	addi	a5,a5,1
    193c:	fb6d                	bnez	a4,192e <strlen+0x4c>
    193e:	bf75                	j	18fa <strlen+0x18>

0000000000001940 <memchr>:

void *memchr(const void *src, int c, size_t n)
{
    const unsigned char *s = src;
    c = (unsigned char)c;
    for (; ((uintptr_t)s & ALIGN) && n && *s != c; s++, n--)
    1940:	00757713          	andi	a4,a0,7
{
    1944:	87aa                	mv	a5,a0
    c = (unsigned char)c;
    1946:	0ff5f593          	andi	a1,a1,255
    for (; ((uintptr_t)s & ALIGN) && n && *s != c; s++, n--)
    194a:	cb19                	beqz	a4,1960 <memchr+0x20>
    194c:	ce25                	beqz	a2,19c4 <memchr+0x84>
    194e:	0007c703          	lbu	a4,0(a5)
    1952:	04b70e63          	beq	a4,a1,19ae <memchr+0x6e>
    1956:	0785                	addi	a5,a5,1
    1958:	0077f713          	andi	a4,a5,7
    195c:	167d                	addi	a2,a2,-1
    195e:	f77d                	bnez	a4,194c <memchr+0xc>
            ;
        s = (const void *)w;
    }
    for (; n && *s != c; s++, n--)
        ;
    return n ? (void *)s : 0;
    1960:	4501                	li	a0,0
    if (n && *s != c)
    1962:	c235                	beqz	a2,19c6 <memchr+0x86>
    1964:	0007c703          	lbu	a4,0(a5)
    1968:	04b70363          	beq	a4,a1,19ae <memchr+0x6e>
        size_t k = ONES * c;
    196c:	00000517          	auipc	a0,0x0
    1970:	66c53503          	ld	a0,1644(a0) # 1fd8 <__clone+0xda>
        for (w = (const void *)s; n >= SS && !HASZERO(*w ^ k); w++, n -= SS)
    1974:	471d                	li	a4,7
        size_t k = ONES * c;
    1976:	02a58533          	mul	a0,a1,a0
        for (w = (const void *)s; n >= SS && !HASZERO(*w ^ k); w++, n -= SS)
    197a:	02c77a63          	bgeu	a4,a2,19ae <memchr+0x6e>
    197e:	00000897          	auipc	a7,0x0
    1982:	64a8b883          	ld	a7,1610(a7) # 1fc8 <__clone+0xca>
    1986:	00000817          	auipc	a6,0x0
    198a:	64a83803          	ld	a6,1610(a6) # 1fd0 <__clone+0xd2>
    198e:	431d                	li	t1,7
    1990:	a029                	j	199a <memchr+0x5a>
    1992:	1661                	addi	a2,a2,-8
    1994:	07a1                	addi	a5,a5,8
    1996:	02c37963          	bgeu	t1,a2,19c8 <memchr+0x88>
    199a:	6398                	ld	a4,0(a5)
    199c:	8f29                	xor	a4,a4,a0
    199e:	011706b3          	add	a3,a4,a7
    19a2:	fff74713          	not	a4,a4
    19a6:	8f75                	and	a4,a4,a3
    19a8:	01077733          	and	a4,a4,a6
    19ac:	d37d                	beqz	a4,1992 <memchr+0x52>
    19ae:	853e                	mv	a0,a5
    19b0:	97b2                	add	a5,a5,a2
    19b2:	a021                	j	19ba <memchr+0x7a>
    for (; n && *s != c; s++, n--)
    19b4:	0505                	addi	a0,a0,1
    19b6:	00f50763          	beq	a0,a5,19c4 <memchr+0x84>
    19ba:	00054703          	lbu	a4,0(a0)
    19be:	feb71be3          	bne	a4,a1,19b4 <memchr+0x74>
    19c2:	8082                	ret
    return n ? (void *)s : 0;
    19c4:	4501                	li	a0,0
}
    19c6:	8082                	ret
    return n ? (void *)s : 0;
    19c8:	4501                	li	a0,0
    for (; n && *s != c; s++, n--)
    19ca:	f275                	bnez	a2,19ae <memchr+0x6e>
}
    19cc:	8082                	ret

00000000000019ce <strnlen>:

size_t strnlen(const char *s, size_t n)
{
    19ce:	1101                	addi	sp,sp,-32
    19d0:	e822                	sd	s0,16(sp)
    const char *p = memchr(s, 0, n);
    19d2:	862e                	mv	a2,a1
{
    19d4:	842e                	mv	s0,a1
    const char *p = memchr(s, 0, n);
    19d6:	4581                	li	a1,0
{
    19d8:	e426                	sd	s1,8(sp)
    19da:	ec06                	sd	ra,24(sp)
    19dc:	84aa                	mv	s1,a0
    const char *p = memchr(s, 0, n);
    19de:	f63ff0ef          	jal	ra,1940 <memchr>
    return p ? p - s : n;
    19e2:	c519                	beqz	a0,19f0 <strnlen+0x22>
}
    19e4:	60e2                	ld	ra,24(sp)
    19e6:	6442                	ld	s0,16(sp)
    return p ? p - s : n;
    19e8:	8d05                	sub	a0,a0,s1
}
    19ea:	64a2                	ld	s1,8(sp)
    19ec:	6105                	addi	sp,sp,32
    19ee:	8082                	ret
    19f0:	60e2                	ld	ra,24(sp)
    return p ? p - s : n;
    19f2:	8522                	mv	a0,s0
}
    19f4:	6442                	ld	s0,16(sp)
    19f6:	64a2                	ld	s1,8(sp)
    19f8:	6105                	addi	sp,sp,32
    19fa:	8082                	ret

00000000000019fc <strcpy>:
char *strcpy(char *restrict d, const char *s)
{
    typedef size_t __attribute__((__may_alias__)) word;
    word *wd;
    const word *ws;
    if ((uintptr_t)s % SS == (uintptr_t)d % SS)
    19fc:	00b547b3          	xor	a5,a0,a1
    1a00:	8b9d                	andi	a5,a5,7
    1a02:	eb95                	bnez	a5,1a36 <strcpy+0x3a>
    {
        for (; (uintptr_t)s % SS; s++, d++)
    1a04:	0075f793          	andi	a5,a1,7
    1a08:	e7b1                	bnez	a5,1a54 <strcpy+0x58>
            if (!(*d = *s))
                return d;
        wd = (void *)d;
        ws = (const void *)s;
        for (; !HASZERO(*ws); *wd++ = *ws++)
    1a0a:	6198                	ld	a4,0(a1)
    1a0c:	00000617          	auipc	a2,0x0
    1a10:	5bc63603          	ld	a2,1468(a2) # 1fc8 <__clone+0xca>
    1a14:	00000817          	auipc	a6,0x0
    1a18:	5bc83803          	ld	a6,1468(a6) # 1fd0 <__clone+0xd2>
    1a1c:	a029                	j	1a26 <strcpy+0x2a>
    1a1e:	e118                	sd	a4,0(a0)
    1a20:	6598                	ld	a4,8(a1)
    1a22:	05a1                	addi	a1,a1,8
    1a24:	0521                	addi	a0,a0,8
    1a26:	00c707b3          	add	a5,a4,a2
    1a2a:	fff74693          	not	a3,a4
    1a2e:	8ff5                	and	a5,a5,a3
    1a30:	0107f7b3          	and	a5,a5,a6
    1a34:	d7ed                	beqz	a5,1a1e <strcpy+0x22>
            ;
        d = (void *)wd;
        s = (const void *)ws;
    }
    for (; (*d = *s); s++, d++)
    1a36:	0005c783          	lbu	a5,0(a1)
    1a3a:	00f50023          	sb	a5,0(a0)
    1a3e:	c785                	beqz	a5,1a66 <strcpy+0x6a>
    1a40:	0015c783          	lbu	a5,1(a1)
    1a44:	0505                	addi	a0,a0,1
    1a46:	0585                	addi	a1,a1,1
    1a48:	00f50023          	sb	a5,0(a0)
    1a4c:	fbf5                	bnez	a5,1a40 <strcpy+0x44>
        ;
    return d;
}
    1a4e:	8082                	ret
        for (; (uintptr_t)s % SS; s++, d++)
    1a50:	0505                	addi	a0,a0,1
    1a52:	df45                	beqz	a4,1a0a <strcpy+0xe>
            if (!(*d = *s))
    1a54:	0005c783          	lbu	a5,0(a1)
        for (; (uintptr_t)s % SS; s++, d++)
    1a58:	0585                	addi	a1,a1,1
    1a5a:	0075f713          	andi	a4,a1,7
            if (!(*d = *s))
    1a5e:	00f50023          	sb	a5,0(a0)
    1a62:	f7fd                	bnez	a5,1a50 <strcpy+0x54>
}
    1a64:	8082                	ret
    1a66:	8082                	ret

0000000000001a68 <strncpy>:
char *strncpy(char *restrict d, const char *s, size_t n)
{
    typedef size_t __attribute__((__may_alias__)) word;
    word *wd;
    const word *ws;
    if (((uintptr_t)s & ALIGN) == ((uintptr_t)d & ALIGN))
    1a68:	00b547b3          	xor	a5,a0,a1
    1a6c:	8b9d                	andi	a5,a5,7
    1a6e:	1a079863          	bnez	a5,1c1e <strncpy+0x1b6>
    {
        for (; ((uintptr_t)s & ALIGN) && n && (*d = *s); n--, s++, d++)
    1a72:	0075f793          	andi	a5,a1,7
    1a76:	16078463          	beqz	a5,1bde <strncpy+0x176>
    1a7a:	ea01                	bnez	a2,1a8a <strncpy+0x22>
    1a7c:	a421                	j	1c84 <strncpy+0x21c>
    1a7e:	167d                	addi	a2,a2,-1
    1a80:	0505                	addi	a0,a0,1
    1a82:	14070e63          	beqz	a4,1bde <strncpy+0x176>
    1a86:	1a060863          	beqz	a2,1c36 <strncpy+0x1ce>
    1a8a:	0005c783          	lbu	a5,0(a1)
    1a8e:	0585                	addi	a1,a1,1
    1a90:	0075f713          	andi	a4,a1,7
    1a94:	00f50023          	sb	a5,0(a0)
    1a98:	f3fd                	bnez	a5,1a7e <strncpy+0x16>
    1a9a:	4805                	li	a6,1
    1a9c:	1a061863          	bnez	a2,1c4c <strncpy+0x1e4>
    1aa0:	40a007b3          	neg	a5,a0
    1aa4:	8b9d                	andi	a5,a5,7
    1aa6:	4681                	li	a3,0
    1aa8:	18061a63          	bnez	a2,1c3c <strncpy+0x1d4>
    1aac:	00778713          	addi	a4,a5,7
    1ab0:	45ad                	li	a1,11
    1ab2:	18b76363          	bltu	a4,a1,1c38 <strncpy+0x1d0>
    1ab6:	1ae6eb63          	bltu	a3,a4,1c6c <strncpy+0x204>
    1aba:	1a078363          	beqz	a5,1c60 <strncpy+0x1f8>
    for (int i = 0; i < n; ++i, *(p++) = c)
    1abe:	00050023          	sb	zero,0(a0)
    1ac2:	4685                	li	a3,1
    1ac4:	00150713          	addi	a4,a0,1
    1ac8:	18d78f63          	beq	a5,a3,1c66 <strncpy+0x1fe>
    1acc:	000500a3          	sb	zero,1(a0)
    1ad0:	4689                	li	a3,2
    1ad2:	00250713          	addi	a4,a0,2
    1ad6:	18d78e63          	beq	a5,a3,1c72 <strncpy+0x20a>
    1ada:	00050123          	sb	zero,2(a0)
    1ade:	468d                	li	a3,3
    1ae0:	00350713          	addi	a4,a0,3
    1ae4:	16d78c63          	beq	a5,a3,1c5c <strncpy+0x1f4>
    1ae8:	000501a3          	sb	zero,3(a0)
    1aec:	4691                	li	a3,4
    1aee:	00450713          	addi	a4,a0,4
    1af2:	18d78263          	beq	a5,a3,1c76 <strncpy+0x20e>
    1af6:	00050223          	sb	zero,4(a0)
    1afa:	4695                	li	a3,5
    1afc:	00550713          	addi	a4,a0,5
    1b00:	16d78d63          	beq	a5,a3,1c7a <strncpy+0x212>
    1b04:	000502a3          	sb	zero,5(a0)
    1b08:	469d                	li	a3,7
    1b0a:	00650713          	addi	a4,a0,6
    1b0e:	16d79863          	bne	a5,a3,1c7e <strncpy+0x216>
    1b12:	00750713          	addi	a4,a0,7
    1b16:	00050323          	sb	zero,6(a0)
    1b1a:	40f80833          	sub	a6,a6,a5
    1b1e:	ff887593          	andi	a1,a6,-8
    1b22:	97aa                	add	a5,a5,a0
    1b24:	95be                	add	a1,a1,a5
    1b26:	0007b023          	sd	zero,0(a5)
    1b2a:	07a1                	addi	a5,a5,8
    1b2c:	feb79de3          	bne	a5,a1,1b26 <strncpy+0xbe>
    1b30:	ff887593          	andi	a1,a6,-8
    1b34:	9ead                	addw	a3,a3,a1
    1b36:	00b707b3          	add	a5,a4,a1
    1b3a:	12b80863          	beq	a6,a1,1c6a <strncpy+0x202>
    1b3e:	00078023          	sb	zero,0(a5)
    1b42:	0016871b          	addiw	a4,a3,1
    1b46:	0ec77863          	bgeu	a4,a2,1c36 <strncpy+0x1ce>
    1b4a:	000780a3          	sb	zero,1(a5)
    1b4e:	0026871b          	addiw	a4,a3,2
    1b52:	0ec77263          	bgeu	a4,a2,1c36 <strncpy+0x1ce>
    1b56:	00078123          	sb	zero,2(a5)
    1b5a:	0036871b          	addiw	a4,a3,3
    1b5e:	0cc77c63          	bgeu	a4,a2,1c36 <strncpy+0x1ce>
    1b62:	000781a3          	sb	zero,3(a5)
    1b66:	0046871b          	addiw	a4,a3,4
    1b6a:	0cc77663          	bgeu	a4,a2,1c36 <strncpy+0x1ce>
    1b6e:	00078223          	sb	zero,4(a5)
    1b72:	0056871b          	addiw	a4,a3,5
    1b76:	0cc77063          	bgeu	a4,a2,1c36 <strncpy+0x1ce>
    1b7a:	000782a3          	sb	zero,5(a5)
    1b7e:	0066871b          	addiw	a4,a3,6
    1b82:	0ac77a63          	bgeu	a4,a2,1c36 <strncpy+0x1ce>
    1b86:	00078323          	sb	zero,6(a5)
    1b8a:	0076871b          	addiw	a4,a3,7
    1b8e:	0ac77463          	bgeu	a4,a2,1c36 <strncpy+0x1ce>
    1b92:	000783a3          	sb	zero,7(a5)
    1b96:	0086871b          	addiw	a4,a3,8
    1b9a:	08c77e63          	bgeu	a4,a2,1c36 <strncpy+0x1ce>
    1b9e:	00078423          	sb	zero,8(a5)
    1ba2:	0096871b          	addiw	a4,a3,9
    1ba6:	08c77863          	bgeu	a4,a2,1c36 <strncpy+0x1ce>
    1baa:	000784a3          	sb	zero,9(a5)
    1bae:	00a6871b          	addiw	a4,a3,10
    1bb2:	08c77263          	bgeu	a4,a2,1c36 <strncpy+0x1ce>
    1bb6:	00078523          	sb	zero,10(a5)
    1bba:	00b6871b          	addiw	a4,a3,11
    1bbe:	06c77c63          	bgeu	a4,a2,1c36 <strncpy+0x1ce>
    1bc2:	000785a3          	sb	zero,11(a5)
    1bc6:	00c6871b          	addiw	a4,a3,12
    1bca:	06c77663          	bgeu	a4,a2,1c36 <strncpy+0x1ce>
    1bce:	00078623          	sb	zero,12(a5)
    1bd2:	26b5                	addiw	a3,a3,13
    1bd4:	06c6f163          	bgeu	a3,a2,1c36 <strncpy+0x1ce>
    1bd8:	000786a3          	sb	zero,13(a5)
    1bdc:	8082                	ret
            ;
        if (!n || !*s)
    1bde:	c645                	beqz	a2,1c86 <strncpy+0x21e>
    1be0:	0005c783          	lbu	a5,0(a1)
    1be4:	ea078be3          	beqz	a5,1a9a <strncpy+0x32>
            goto tail;
        wd = (void *)d;
        ws = (const void *)s;
        for (; n >= sizeof(size_t) && !HASZERO(*ws); n -= sizeof(size_t), ws++, wd++)
    1be8:	479d                	li	a5,7
    1bea:	02c7ff63          	bgeu	a5,a2,1c28 <strncpy+0x1c0>
    1bee:	00000897          	auipc	a7,0x0
    1bf2:	3da8b883          	ld	a7,986(a7) # 1fc8 <__clone+0xca>
    1bf6:	00000817          	auipc	a6,0x0
    1bfa:	3da83803          	ld	a6,986(a6) # 1fd0 <__clone+0xd2>
    1bfe:	431d                	li	t1,7
    1c00:	6198                	ld	a4,0(a1)
    1c02:	011707b3          	add	a5,a4,a7
    1c06:	fff74693          	not	a3,a4
    1c0a:	8ff5                	and	a5,a5,a3
    1c0c:	0107f7b3          	and	a5,a5,a6
    1c10:	ef81                	bnez	a5,1c28 <strncpy+0x1c0>
            *wd = *ws;
    1c12:	e118                	sd	a4,0(a0)
        for (; n >= sizeof(size_t) && !HASZERO(*ws); n -= sizeof(size_t), ws++, wd++)
    1c14:	1661                	addi	a2,a2,-8
    1c16:	05a1                	addi	a1,a1,8
    1c18:	0521                	addi	a0,a0,8
    1c1a:	fec363e3          	bltu	t1,a2,1c00 <strncpy+0x198>
        d = (void *)wd;
        s = (const void *)ws;
    }
    for (; n && (*d = *s); n--, s++, d++)
    1c1e:	e609                	bnez	a2,1c28 <strncpy+0x1c0>
    1c20:	a08d                	j	1c82 <strncpy+0x21a>
    1c22:	167d                	addi	a2,a2,-1
    1c24:	0505                	addi	a0,a0,1
    1c26:	ca01                	beqz	a2,1c36 <strncpy+0x1ce>
    1c28:	0005c783          	lbu	a5,0(a1)
    1c2c:	0585                	addi	a1,a1,1
    1c2e:	00f50023          	sb	a5,0(a0)
    1c32:	fbe5                	bnez	a5,1c22 <strncpy+0x1ba>
        ;
tail:
    1c34:	b59d                	j	1a9a <strncpy+0x32>
    memset(d, 0, n);
    return d;
}
    1c36:	8082                	ret
    1c38:	472d                	li	a4,11
    1c3a:	bdb5                	j	1ab6 <strncpy+0x4e>
    1c3c:	00778713          	addi	a4,a5,7
    1c40:	45ad                	li	a1,11
    1c42:	fff60693          	addi	a3,a2,-1
    1c46:	e6b778e3          	bgeu	a4,a1,1ab6 <strncpy+0x4e>
    1c4a:	b7fd                	j	1c38 <strncpy+0x1d0>
    1c4c:	40a007b3          	neg	a5,a0
    1c50:	8832                	mv	a6,a2
    1c52:	8b9d                	andi	a5,a5,7
    1c54:	4681                	li	a3,0
    1c56:	e4060be3          	beqz	a2,1aac <strncpy+0x44>
    1c5a:	b7cd                	j	1c3c <strncpy+0x1d4>
    for (int i = 0; i < n; ++i, *(p++) = c)
    1c5c:	468d                	li	a3,3
    1c5e:	bd75                	j	1b1a <strncpy+0xb2>
    1c60:	872a                	mv	a4,a0
    1c62:	4681                	li	a3,0
    1c64:	bd5d                	j	1b1a <strncpy+0xb2>
    1c66:	4685                	li	a3,1
    1c68:	bd4d                	j	1b1a <strncpy+0xb2>
    1c6a:	8082                	ret
    1c6c:	87aa                	mv	a5,a0
    1c6e:	4681                	li	a3,0
    1c70:	b5f9                	j	1b3e <strncpy+0xd6>
    1c72:	4689                	li	a3,2
    1c74:	b55d                	j	1b1a <strncpy+0xb2>
    1c76:	4691                	li	a3,4
    1c78:	b54d                	j	1b1a <strncpy+0xb2>
    1c7a:	4695                	li	a3,5
    1c7c:	bd79                	j	1b1a <strncpy+0xb2>
    1c7e:	4699                	li	a3,6
    1c80:	bd69                	j	1b1a <strncpy+0xb2>
    1c82:	8082                	ret
    1c84:	8082                	ret
    1c86:	8082                	ret

0000000000001c88 <open>:
#include <unistd.h>

#include "syscall.h"

int open(const char *path, int flags)
{
    1c88:	87aa                	mv	a5,a0
    1c8a:	862e                	mv	a2,a1
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
}

static inline long __syscall4(long n, long a, long b, long c, long d)
{
    register long a7 __asm__("a7") = n;
    1c8c:	03800893          	li	a7,56
    register long a0 __asm__("a0") = a;
    1c90:	f9c00513          	li	a0,-100
    register long a1 __asm__("a1") = b;
    1c94:	85be                	mv	a1,a5
    register long a2 __asm__("a2") = c;
    register long a3 __asm__("a3") = d;
    1c96:	4689                	li	a3,2
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3))
    1c98:	00000073          	ecall
    return syscall(SYS_openat, AT_FDCWD, path, flags, O_RDWR);
}
    1c9c:	2501                	sext.w	a0,a0
    1c9e:	8082                	ret

0000000000001ca0 <openat>:
    register long a7 __asm__("a7") = n;
    1ca0:	03800893          	li	a7,56
    register long a3 __asm__("a3") = d;
    1ca4:	18000693          	li	a3,384
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3))
    1ca8:	00000073          	ecall

int openat(int dirfd,const char *path, int flags)
{
    return syscall(SYS_openat, dirfd, path, flags, 0600);
}
    1cac:	2501                	sext.w	a0,a0
    1cae:	8082                	ret

0000000000001cb0 <close>:
    register long a7 __asm__("a7") = n;
    1cb0:	03900893          	li	a7,57
    __asm_syscall("r"(a7), "0"(a0))
    1cb4:	00000073          	ecall

int close(int fd)
{
    return syscall(SYS_close, fd);
}
    1cb8:	2501                	sext.w	a0,a0
    1cba:	8082                	ret

0000000000001cbc <read>:
    register long a7 __asm__("a7") = n;
    1cbc:	03f00893          	li	a7,63
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1cc0:	00000073          	ecall

ssize_t read(int fd, void *buf, size_t len)
{
    return syscall(SYS_read, fd, buf, len);
}
    1cc4:	8082                	ret

0000000000001cc6 <write>:
    register long a7 __asm__("a7") = n;
    1cc6:	04000893          	li	a7,64
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1cca:	00000073          	ecall

ssize_t write(int fd, const void *buf, size_t len)
{
    return syscall(SYS_write, fd, buf, len);
}
    1cce:	8082                	ret

0000000000001cd0 <getpid>:
    register long a7 __asm__("a7") = n;
    1cd0:	0ac00893          	li	a7,172
    __asm_syscall("r"(a7))
    1cd4:	00000073          	ecall

pid_t getpid(void)
{
    return syscall(SYS_getpid);
}
    1cd8:	2501                	sext.w	a0,a0
    1cda:	8082                	ret

0000000000001cdc <getppid>:
    register long a7 __asm__("a7") = n;
    1cdc:	0ad00893          	li	a7,173
    __asm_syscall("r"(a7))
    1ce0:	00000073          	ecall

pid_t getppid(void)
{
    return syscall(SYS_getppid);
}
    1ce4:	2501                	sext.w	a0,a0
    1ce6:	8082                	ret

0000000000001ce8 <sched_yield>:
    register long a7 __asm__("a7") = n;
    1ce8:	07c00893          	li	a7,124
    __asm_syscall("r"(a7))
    1cec:	00000073          	ecall

int sched_yield(void)
{
    return syscall(SYS_sched_yield);
}
    1cf0:	2501                	sext.w	a0,a0
    1cf2:	8082                	ret

0000000000001cf4 <fork>:
    register long a7 __asm__("a7") = n;
    1cf4:	0dc00893          	li	a7,220
    register long a0 __asm__("a0") = a;
    1cf8:	4545                	li	a0,17
    register long a1 __asm__("a1") = b;
    1cfa:	4581                	li	a1,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1cfc:	00000073          	ecall

pid_t fork(void)
{
    return syscall(SYS_clone, SIGCHLD, 0);
}
    1d00:	2501                	sext.w	a0,a0
    1d02:	8082                	ret

0000000000001d04 <clone>:

pid_t clone(int (*fn)(void *arg), void *arg, void *stack, size_t stack_size, unsigned long flags)
{
    1d04:	85b2                	mv	a1,a2
    1d06:	863a                	mv	a2,a4
    if (stack)
    1d08:	c191                	beqz	a1,1d0c <clone+0x8>
	stack += stack_size;
    1d0a:	95b6                	add	a1,a1,a3

    return __clone(fn, stack, flags, NULL, NULL, NULL);
    1d0c:	4781                	li	a5,0
    1d0e:	4701                	li	a4,0
    1d10:	4681                	li	a3,0
    1d12:	2601                	sext.w	a2,a2
    1d14:	a2ed                	j	1efe <__clone>

0000000000001d16 <exit>:
    register long a7 __asm__("a7") = n;
    1d16:	05d00893          	li	a7,93
    __asm_syscall("r"(a7), "0"(a0))
    1d1a:	00000073          	ecall
    //return syscall(SYS_clone, fn, stack, flags, NULL, NULL, NULL);
}
void exit(int code)
{
    syscall(SYS_exit, code);
}
    1d1e:	8082                	ret

0000000000001d20 <waitpid>:
    register long a7 __asm__("a7") = n;
    1d20:	10400893          	li	a7,260
    register long a3 __asm__("a3") = d;
    1d24:	4681                	li	a3,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3))
    1d26:	00000073          	ecall

int waitpid(int pid, int *code, int options)
{
    return syscall(SYS_wait4, pid, code, options, 0);
}
    1d2a:	2501                	sext.w	a0,a0
    1d2c:	8082                	ret

0000000000001d2e <exec>:
    register long a7 __asm__("a7") = n;
    1d2e:	0dd00893          	li	a7,221
    __asm_syscall("r"(a7), "0"(a0))
    1d32:	00000073          	ecall

int exec(char *name)
{
    return syscall(SYS_execve, name);
}
    1d36:	2501                	sext.w	a0,a0
    1d38:	8082                	ret

0000000000001d3a <execve>:
    register long a7 __asm__("a7") = n;
    1d3a:	0dd00893          	li	a7,221
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1d3e:	00000073          	ecall

int execve(const char *name, char *const argv[], char *const argp[])
{
    return syscall(SYS_execve, name, argv, argp);
}
    1d42:	2501                	sext.w	a0,a0
    1d44:	8082                	ret

0000000000001d46 <times>:
    register long a7 __asm__("a7") = n;
    1d46:	09900893          	li	a7,153
    __asm_syscall("r"(a7), "0"(a0))
    1d4a:	00000073          	ecall

int times(void *mytimes)
{
	return syscall(SYS_times, mytimes);
}
    1d4e:	2501                	sext.w	a0,a0
    1d50:	8082                	ret

0000000000001d52 <get_time>:

int64 get_time()
{
    1d52:	1141                	addi	sp,sp,-16
    register long a7 __asm__("a7") = n;
    1d54:	0a900893          	li	a7,169
    register long a0 __asm__("a0") = a;
    1d58:	850a                	mv	a0,sp
    register long a1 __asm__("a1") = b;
    1d5a:	4581                	li	a1,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1d5c:	00000073          	ecall
    TimeVal time;
    int err = sys_get_time(&time, 0);
    if (err == 0)
    1d60:	2501                	sext.w	a0,a0
    1d62:	ed09                	bnez	a0,1d7c <get_time+0x2a>
    {
        return ((time.sec & 0xffff) * 1000 + time.usec / 1000);
    1d64:	67a2                	ld	a5,8(sp)
    1d66:	3e800713          	li	a4,1000
    1d6a:	00015503          	lhu	a0,0(sp)
    1d6e:	02e7d7b3          	divu	a5,a5,a4
    1d72:	02e50533          	mul	a0,a0,a4
    1d76:	953e                	add	a0,a0,a5
    }
    else
    {
        return -1;
    }
}
    1d78:	0141                	addi	sp,sp,16
    1d7a:	8082                	ret
        return -1;
    1d7c:	557d                	li	a0,-1
    1d7e:	bfed                	j	1d78 <get_time+0x26>

0000000000001d80 <sys_get_time>:
    register long a7 __asm__("a7") = n;
    1d80:	0a900893          	li	a7,169
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1d84:	00000073          	ecall

int sys_get_time(TimeVal *ts, int tz)
{
    return syscall(SYS_gettimeofday, ts, tz);
}
    1d88:	2501                	sext.w	a0,a0
    1d8a:	8082                	ret

0000000000001d8c <time>:
    register long a7 __asm__("a7") = n;
    1d8c:	42600893          	li	a7,1062
    __asm_syscall("r"(a7), "0"(a0))
    1d90:	00000073          	ecall

int time(unsigned long *tloc)
{
    return syscall(SYS_time, tloc);
}
    1d94:	2501                	sext.w	a0,a0
    1d96:	8082                	ret

0000000000001d98 <sleep>:

int sleep(unsigned long long time)
{
    1d98:	1141                	addi	sp,sp,-16
    TimeVal tv = {.sec = time, .usec = 0};
    1d9a:	e02a                	sd	a0,0(sp)
    register long a0 __asm__("a0") = a;
    1d9c:	850a                	mv	a0,sp
    1d9e:	e402                	sd	zero,8(sp)
    register long a7 __asm__("a7") = n;
    1da0:	06500893          	li	a7,101
    register long a1 __asm__("a1") = b;
    1da4:	85aa                	mv	a1,a0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1da6:	00000073          	ecall
    if (syscall(SYS_nanosleep, &tv, &tv)) return tv.sec;
    1daa:	e501                	bnez	a0,1db2 <sleep+0x1a>
    return 0;
    1dac:	4501                	li	a0,0
}
    1dae:	0141                	addi	sp,sp,16
    1db0:	8082                	ret
    if (syscall(SYS_nanosleep, &tv, &tv)) return tv.sec;
    1db2:	4502                	lw	a0,0(sp)
}
    1db4:	0141                	addi	sp,sp,16
    1db6:	8082                	ret

0000000000001db8 <set_priority>:
    register long a7 __asm__("a7") = n;
    1db8:	08c00893          	li	a7,140
    __asm_syscall("r"(a7), "0"(a0))
    1dbc:	00000073          	ecall

int set_priority(int prio)
{
    return syscall(SYS_setpriority, prio);
}
    1dc0:	2501                	sext.w	a0,a0
    1dc2:	8082                	ret

0000000000001dc4 <mmap>:
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4))
}

static inline long __syscall6(long n, long a, long b, long c, long d, long e, long f)
{
    register long a7 __asm__("a7") = n;
    1dc4:	0de00893          	li	a7,222
    register long a1 __asm__("a1") = b;
    register long a2 __asm__("a2") = c;
    register long a3 __asm__("a3") = d;
    register long a4 __asm__("a4") = e;
    register long a5 __asm__("a5") = f;
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4), "r"(a5))
    1dc8:	00000073          	ecall

void *mmap(void *start, size_t len, int prot, int flags, int fd, off_t off)
{
    return syscall(SYS_mmap, start, len, prot, flags, fd, off);
}
    1dcc:	8082                	ret

0000000000001dce <munmap>:
    register long a7 __asm__("a7") = n;
    1dce:	0d700893          	li	a7,215
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1dd2:	00000073          	ecall

int munmap(void *start, size_t len)
{
    return syscall(SYS_munmap, start, len);
}
    1dd6:	2501                	sext.w	a0,a0
    1dd8:	8082                	ret

0000000000001dda <wait>:

int wait(int *code)
{
    1dda:	85aa                	mv	a1,a0
    register long a7 __asm__("a7") = n;
    1ddc:	10400893          	li	a7,260
    register long a0 __asm__("a0") = a;
    1de0:	557d                	li	a0,-1
    register long a2 __asm__("a2") = c;
    1de2:	4601                	li	a2,0
    register long a3 __asm__("a3") = d;
    1de4:	4681                	li	a3,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3))
    1de6:	00000073          	ecall
    return waitpid((int)-1, code, 0);
}
    1dea:	2501                	sext.w	a0,a0
    1dec:	8082                	ret

0000000000001dee <spawn>:
    register long a7 __asm__("a7") = n;
    1dee:	19000893          	li	a7,400
    __asm_syscall("r"(a7), "0"(a0))
    1df2:	00000073          	ecall

int spawn(char *file)
{
    return syscall(SYS_spawn, file);
}
    1df6:	2501                	sext.w	a0,a0
    1df8:	8082                	ret

0000000000001dfa <mailread>:
    register long a7 __asm__("a7") = n;
    1dfa:	19100893          	li	a7,401
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1dfe:	00000073          	ecall

int mailread(void *buf, int len)
{
    return syscall(SYS_mailread, buf, len);
}
    1e02:	2501                	sext.w	a0,a0
    1e04:	8082                	ret

0000000000001e06 <mailwrite>:
    register long a7 __asm__("a7") = n;
    1e06:	19200893          	li	a7,402
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1e0a:	00000073          	ecall

int mailwrite(int pid, void *buf, int len)
{
    return syscall(SYS_mailwrite, pid, buf, len);
}
    1e0e:	2501                	sext.w	a0,a0
    1e10:	8082                	ret

0000000000001e12 <fstat>:
    register long a7 __asm__("a7") = n;
    1e12:	05000893          	li	a7,80
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1e16:	00000073          	ecall

int fstat(int fd, struct kstat *st)
{
    return syscall(SYS_fstat, fd, st);
}
    1e1a:	2501                	sext.w	a0,a0
    1e1c:	8082                	ret

0000000000001e1e <sys_linkat>:
    register long a4 __asm__("a4") = e;
    1e1e:	1702                	slli	a4,a4,0x20
    register long a7 __asm__("a7") = n;
    1e20:	02500893          	li	a7,37
    register long a4 __asm__("a4") = e;
    1e24:	9301                	srli	a4,a4,0x20
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4))
    1e26:	00000073          	ecall

int sys_linkat(int olddirfd, char *oldpath, int newdirfd, char *newpath, unsigned int flags)
{
    return syscall(SYS_linkat, olddirfd, oldpath, newdirfd, newpath, flags);
}
    1e2a:	2501                	sext.w	a0,a0
    1e2c:	8082                	ret

0000000000001e2e <sys_unlinkat>:
    register long a2 __asm__("a2") = c;
    1e2e:	1602                	slli	a2,a2,0x20
    register long a7 __asm__("a7") = n;
    1e30:	02300893          	li	a7,35
    register long a2 __asm__("a2") = c;
    1e34:	9201                	srli	a2,a2,0x20
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1e36:	00000073          	ecall

int sys_unlinkat(int dirfd, char *path, unsigned int flags)
{
    return syscall(SYS_unlinkat, dirfd, path, flags);
}
    1e3a:	2501                	sext.w	a0,a0
    1e3c:	8082                	ret

0000000000001e3e <link>:

int link(char *old_path, char *new_path)
{
    1e3e:	87aa                	mv	a5,a0
    1e40:	86ae                	mv	a3,a1
    register long a7 __asm__("a7") = n;
    1e42:	02500893          	li	a7,37
    register long a0 __asm__("a0") = a;
    1e46:	f9c00513          	li	a0,-100
    register long a1 __asm__("a1") = b;
    1e4a:	85be                	mv	a1,a5
    register long a2 __asm__("a2") = c;
    1e4c:	f9c00613          	li	a2,-100
    register long a4 __asm__("a4") = e;
    1e50:	4701                	li	a4,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4))
    1e52:	00000073          	ecall
    return sys_linkat(AT_FDCWD, old_path, AT_FDCWD, new_path, 0);
}
    1e56:	2501                	sext.w	a0,a0
    1e58:	8082                	ret

0000000000001e5a <unlink>:

int unlink(char *path)
{
    1e5a:	85aa                	mv	a1,a0
    register long a7 __asm__("a7") = n;
    1e5c:	02300893          	li	a7,35
    register long a0 __asm__("a0") = a;
    1e60:	f9c00513          	li	a0,-100
    register long a2 __asm__("a2") = c;
    1e64:	4601                	li	a2,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1e66:	00000073          	ecall
    return sys_unlinkat(AT_FDCWD, path, 0);
}
    1e6a:	2501                	sext.w	a0,a0
    1e6c:	8082                	ret

0000000000001e6e <uname>:
    register long a7 __asm__("a7") = n;
    1e6e:	0a000893          	li	a7,160
    __asm_syscall("r"(a7), "0"(a0))
    1e72:	00000073          	ecall

int uname(void *buf)
{
    return syscall(SYS_uname, buf);
}
    1e76:	2501                	sext.w	a0,a0
    1e78:	8082                	ret

0000000000001e7a <brk>:
    register long a7 __asm__("a7") = n;
    1e7a:	0d600893          	li	a7,214
    __asm_syscall("r"(a7), "0"(a0))
    1e7e:	00000073          	ecall

int brk(void *addr)
{
    return syscall(SYS_brk, addr);
}
    1e82:	2501                	sext.w	a0,a0
    1e84:	8082                	ret

0000000000001e86 <getcwd>:
    register long a7 __asm__("a7") = n;
    1e86:	48c5                	li	a7,17
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1e88:	00000073          	ecall

char *getcwd(char *buf, size_t size){
    return syscall(SYS_getcwd, buf, size);
}
    1e8c:	8082                	ret

0000000000001e8e <chdir>:
    register long a7 __asm__("a7") = n;
    1e8e:	03100893          	li	a7,49
    __asm_syscall("r"(a7), "0"(a0))
    1e92:	00000073          	ecall

int chdir(const char *path){
    return syscall(SYS_chdir, path);
}
    1e96:	2501                	sext.w	a0,a0
    1e98:	8082                	ret

0000000000001e9a <mkdir>:

int mkdir(const char *path, mode_t mode){
    1e9a:	862e                	mv	a2,a1
    1e9c:	87aa                	mv	a5,a0
    register long a2 __asm__("a2") = c;
    1e9e:	1602                	slli	a2,a2,0x20
    register long a7 __asm__("a7") = n;
    1ea0:	02200893          	li	a7,34
    register long a0 __asm__("a0") = a;
    1ea4:	f9c00513          	li	a0,-100
    register long a1 __asm__("a1") = b;
    1ea8:	85be                	mv	a1,a5
    register long a2 __asm__("a2") = c;
    1eaa:	9201                	srli	a2,a2,0x20
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1eac:	00000073          	ecall
    return syscall(SYS_mkdirat, AT_FDCWD, path, mode);
}
    1eb0:	2501                	sext.w	a0,a0
    1eb2:	8082                	ret

0000000000001eb4 <getdents>:
    register long a7 __asm__("a7") = n;
    1eb4:	03d00893          	li	a7,61
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1eb8:	00000073          	ecall

int getdents(int fd, struct linux_dirent64 *dirp64, unsigned long len){
    //return syscall(SYS_getdents64, fd, dirp64, len);
    return syscall(SYS_getdents64, fd, dirp64, len);
}
    1ebc:	2501                	sext.w	a0,a0
    1ebe:	8082                	ret

0000000000001ec0 <pipe>:
    register long a7 __asm__("a7") = n;
    1ec0:	03b00893          	li	a7,59
    register long a1 __asm__("a1") = b;
    1ec4:	4581                	li	a1,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1ec6:	00000073          	ecall

int pipe(int fd[2]){
    return syscall(SYS_pipe2, fd, 0);
}
    1eca:	2501                	sext.w	a0,a0
    1ecc:	8082                	ret

0000000000001ece <dup>:
    register long a7 __asm__("a7") = n;
    1ece:	48dd                	li	a7,23
    __asm_syscall("r"(a7), "0"(a0))
    1ed0:	00000073          	ecall

int dup(int fd){
    return syscall(SYS_dup, fd);
}
    1ed4:	2501                	sext.w	a0,a0
    1ed6:	8082                	ret

0000000000001ed8 <dup2>:
    register long a7 __asm__("a7") = n;
    1ed8:	48e1                	li	a7,24
    register long a2 __asm__("a2") = c;
    1eda:	4601                	li	a2,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2))
    1edc:	00000073          	ecall

int dup2(int old, int new){
    return syscall(SYS_dup3, old, new, 0);
}
    1ee0:	2501                	sext.w	a0,a0
    1ee2:	8082                	ret

0000000000001ee4 <mount>:
    register long a7 __asm__("a7") = n;
    1ee4:	02800893          	li	a7,40
    __asm_syscall("r"(a7), "0"(a0), "r"(a1), "r"(a2), "r"(a3), "r"(a4))
    1ee8:	00000073          	ecall

int mount(const char *special, const char *dir, const char *fstype, unsigned long flags, const void *data)
{
        return syscall(SYS_mount, special, dir, fstype, flags, data);
}
    1eec:	2501                	sext.w	a0,a0
    1eee:	8082                	ret

0000000000001ef0 <umount>:
    register long a7 __asm__("a7") = n;
    1ef0:	02700893          	li	a7,39
    register long a1 __asm__("a1") = b;
    1ef4:	4581                	li	a1,0
    __asm_syscall("r"(a7), "0"(a0), "r"(a1))
    1ef6:	00000073          	ecall

int umount(const char *special)
{
        return syscall(SYS_umount2, special, 0);
}
    1efa:	2501                	sext.w	a0,a0
    1efc:	8082                	ret

0000000000001efe <__clone>:

.global __clone
.type  __clone, %function
__clone:
	# Save func and arg to stack
	addi a1, a1, -16
    1efe:	15c1                	addi	a1,a1,-16
	sd a0, 0(a1)
    1f00:	e188                	sd	a0,0(a1)
	sd a3, 8(a1)
    1f02:	e594                	sd	a3,8(a1)

	# Call SYS_clone
	mv a0, a2
    1f04:	8532                	mv	a0,a2
	mv a2, a4
    1f06:	863a                	mv	a2,a4
	mv a3, a5
    1f08:	86be                	mv	a3,a5
	mv a4, a6
    1f0a:	8742                	mv	a4,a6
	li a7, 220 # SYS_clone
    1f0c:	0dc00893          	li	a7,220
	ecall
    1f10:	00000073          	ecall

	beqz a0, 1f
    1f14:	c111                	beqz	a0,1f18 <__clone+0x1a>
	# Parent
	ret
    1f16:	8082                	ret

	# Child
1:      ld a1, 0(sp)
    1f18:	6582                	ld	a1,0(sp)
	ld a0, 8(sp)
    1f1a:	6522                	ld	a0,8(sp)
	jalr a1
    1f1c:	9582                	jalr	a1

	# Exit
	li a7, 93 # SYS_exit
    1f1e:	05d00893          	li	a7,93
	ecall
    1f22:	00000073          	ecall
