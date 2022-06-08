/*
   https://worldofspectrum.org/ZXBasicManual/zxmanappd.html
   Converted to C by Ewan Parker 25th May 2022.
*/

#include <string.h>
#include <stdio.h>

// 2000 REM initial animals
typedef struct
{
  char qa[51]; int yes; int no;
} qadata_t;

void main()
{
  qadata_t qadata[7];
  // 2010 DATA "Does it live in the sea",4,2
  strncpy(qadata[0].qa, "Does it live in the sea", 51);
  qadata[0].yes = 3; qadata[0].no = 1;
  // 2020 DATA "Is it scaly",3,5
  strncpy(qadata[1].qa, "Is it scaly", 51); qadata[1].yes = 2; qadata[1].no = 4;
  // 2030 DATA "Does it eat ants",6,7
  strncpy(qadata[2].qa, "Does it eat ants", 51);
  qadata[2].yes = 5; qadata[2].no = 6;
  // 2040 DATA "a whale", "a blancmange", "a pangolin", "an ant"
  strncpy(qadata[3].qa, "a whale", 51);
  strncpy(qadata[4].qa, "a blancmange", 51);
  strncpy(qadata[5].qa, "a pangolin", 51);
  strncpy(qadata[6].qa, "an ant", 51);

  //    5 REM Pangolins
  //   10 LET nq=100: REM number of questions and animals
  int nq = 100;
  //   15 DIM q$(nq,50): DIM a(nq,2): DIM r$(1)
  char q[nq][51]; int a[nq][2]; char r[1];
  //   20 LET qf=8
  int qf = 8;
  //   30 FOR n=1 TO qf/2-1
  int n;
  for (n = 0; n < qf/2 - 1; n++)
  {
    //   40 READ q$(n): READ a(n,1): READ a(n,2)
    strncpy(q[n], qadata[n].qa, 51);
    a[n][0] = qadata[n].yes; a[n][1] = qadata[n].no;
    //   50 NEXT n
  }
  //   60 FOR n=n TO qf-1
  for (; n < qf - 1; n++)
  {
    //   70 READ q$(n): NEXT n
    strncpy(q[n], qadata[n].qa, 51);
  }

  line100:
  //  100 REM start playing
  //  110 PRINT "Think of an animal.","Press any key to continue."
  printf("Think of an animal.\nPress any key to continue.\n");
  //  120 PAUSE 0
  r[0] = getchar();
  //  130 LET c=1: REM start with 1st question
  int c = 0;
  line140:
  //  140 IF a(c,1)=0 THEN GO TO 300
  if (!a[c][0]) goto line300;
  line150:
  //  150 LET p$=q$(c): GO SUB 910
  //  160 PRINT "?": GO SUB 1000
  printf("%s?\n", q[c]);
  r[0] = getchar(); getchar();
  //  170 LET in=1: IF r$="y" THEN GO TO 210
  int in = 0;
  //  180 IF r$="Y" THEN GO TO 210
  if (r[0] == 'y' || r[0] == 'Y') goto line210;
  //  190 LET in=2: IF r$="n" THEN GO TO 210
  in = 1;
  if (r[0] == 'n') goto line210;
  //  200 IF r$<>"N" THEN GO TO 150
  if (r[0] != 'N') goto line150;
  line210:
  //  210 LET c=a(c,in): GO TO 140
  c = a[c][in];
  goto line140;

  //  300 REM animal
  line300:
  //  310 PRINT "Are you thinking of"
  //  320 LET P$=q$(c): GO SUB 900: PRINT "?"
  printf("Are you thinking of %s?\n", q[c]);
  //  330 GO SUB 1000
  r[0] = getchar(); getchar();
  //  340 IF r$="y" THEN GO TO 400
  //  350 IF r$="Y" THEN GO TO 400
  if (r[0] == 'y' || r[0] == 'Y') goto line400;
  //  360 IF r$="n" THEN GO TO 500
  //  370 IF r$="N" THEN GO TO 500
  if (r[0] == 'n' || r[0] == 'N') goto line500;
  //  380 PRINT "Answer me properly when I'm","talking to you.": GO TO 300
  printf("Answer me properly when I'm talking to you.\n");
  goto line300;

  //  400 REM guessed it
  line400:
  //  410 PRINT "I thought as much.": GO TO 800
  printf("I thought as much.\n");
  goto line800;

  //  500 REM new animal 
  line500:
  //  510 IF qf>nq-1 THEN PRINT "I'm sure your animal is very", "interesting, 
  //           but I don't have","room for it just now.": GO TO 800 
  if (qf>nq-1)
  {
    printf("I'm sure your animal is very interesting, but I don't have room for\nit just now.\n");
    goto line800;
  }
  //  520 LET q$(qf)=q$(c): REM move old animal 
  strncpy(q[qf], q[c], 51);
  //  530 PRINT "What is it, then?": INPUT q$(qf+1) 
  printf("What is it, then?\n");
  fgets(q[qf + 1], 51, stdin);
  if (strnlen(q[qf + 1], 51)) q[qf + 1][strnlen(q[qf + 1], 51) - 1] = '\0';
  //  540 PRINT "Tell me a question which dist ","inguishes between " 
  //  550 LET p$=q$(qf): GO SUB 900: PRINT " and" 
  //  560 LET p$=q$(qf+1): GO SUB 900: PRINT " " 
  printf("Tell me a question which distinguishes between %s and %s.\n",
    q[qf], q[qf + 1]);
  //  570 INPUT s$: LET b=LEN s$ 
  char s[51]; fgets(s, 51, stdin);
  if (strnlen(s, 51)) s[strnlen(s, 51) - 1] = '\0';
  int b = strnlen(s, 51) - 1;
  //  580 IF s$(b)="?" THEN LET b=b-1 
  if (s[b] == '?') s[b] = '\0';
  //  590 LET q$(c)=s$(TO b): REM insert question 
  strncpy(q[c], s, 51);
  line600:
  //  600 PRINT "What is the answer for" 
  //  610 LET p$=q$(qf+1): GO SUB 900: PRINT "?" 
  printf("What is the answer for %s?\n", q[qf + 1]);
  //  620 GO SUB 1000 
  r[0] = getchar(); getchar();
  //  630 LET in=1: LET io=2: REM answers for new and old animals 
  in = 0; int io = 1;
  //  640 IF r$="y" THEN GO T0 700 
  //  650 IF r$="Y" THEN GO TO 700 
  if (r[0] == 'y' || r[0] == 'Y') goto line700;
  //  660 LET in=2: LET io=1 
  in = 1; io = 0;
  //  670 IF r$="n" THEN GO TO 700 
  //  680 IF r$="N" THEN GO TO 700
  if (r[0] == 'n' || r[0] == 'N') goto line700;
  //  690 PRINT "That's no good. ": GO TO 600
  printf("That's no good.\n");
  goto line600;

  //  700 REM update answers 
  line700:
  //  710 LET a(c,in)=qf+1: LET a(c,io)=qf
  a[c][in] = qf + 1; a[c][io] = qf;
  //  720 LET qf=qf+2: REM next free animal space 
  qf = qf + 2;
  //  730 PRINT "That fooled me."
  printf("That fooled me.\n");
  //  800 REM again?
  line800:
  //  810 PRINT "Do you want another go?": GO SUB 1000
  printf("Do you want another go?\n");
  r[0] = getchar(); getchar();
  //  820 IF r$="y" THEN GO TO 100
  //  830 IF r$="Y" THEN GO TO 100
  if (r[0] == 'y' || r[0] == 'Y') goto line100;
  //  840 STOP
  //  900 REM print without trailing spaces
  //  905 PRINT " ";
  //  910 FOR n=50 TO 1 STEP -1
  //  920 IF p$(n)<>" " THEN GO TO 940
  //  930 NEXT n
  //  940 PRINT p$(TO n);: RETURN
  // 1000 REM get reply
  // 1010 INPUT r$: IF r$="" THEN RETURN
  // 1020 LET r$=r$(1): RETURN
}
